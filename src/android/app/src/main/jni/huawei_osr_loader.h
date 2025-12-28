// SPDX-FileCopyrightText: Copyright 2025 Eden Emulator Project
// SPDX-License-Identifier: GPL-3.0-or-later

/**
 * Huawei OSR Dynamic Loader
 * Handles safe loading of Huawei CGKit libraries with proper namespace handling
 */

#pragma once

#include <dlfcn.h>
#include <android/log.h>
#include <string>

#define LOG_TAG "HuaweiOSR"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

namespace HuaweiOSR {

// Function pointer types
typedef void (*CInitialize_t)();
typedef void (*CUninitialize_t)();
typedef void (*CSetAssetsDir_t)(const char*);
typedef const char* (*CGetAssetsDir_t)();
typedef bool (*CSuperSamplingSyncExecute_t)(const void*, const void*, int);
typedef bool (*CSuperSamplingAsyncExecute_t)(const void*, const void*, void*);

class DynamicLoader {
private:
    void* m_cgkit_handle = nullptr;
    void* m_igraphics_handle = nullptr;
    
    // Function pointers
    CInitialize_t m_CInitialize = nullptr;
    CUninitialize_t m_CUninitialize = nullptr;
    CSetAssetsDir_t m_CSetAssetsDir = nullptr;
    CGetAssetsDir_t m_CGetAssetsDir = nullptr;
    CSuperSamplingSyncExecute_t m_CSuperSamplingSyncExecute = nullptr;
    CSuperSamplingAsyncExecute_t m_CSuperSamplingAsyncExecute = nullptr;
    
    bool m_initialized = false;

    /**
     * Try to load a library from multiple possible paths
     * Uses RTLD_GLOBAL for symbol sharing with dependent libraries
     */
    void* TryLoadLibrary(const char* libname, const char** search_paths, int num_paths, bool use_global = false) {
        void* handle = nullptr;
        const char* actual_libname = libname;
        
        // ========================================================================
        // FORCE REDIRECT: libiGraphicsCore.huawei.so → libigs_client.so
        // The CGKit plugin may request the non-public library, but we redirect
        // to the official public library that provides the same functionality
        // ========================================================================
        if (strcmp(libname, "libiGraphicsCore.huawei.so") == 0) {
            LOGI("⚠️  REDIRECT: %s → libigs_client.so (using official public library)", libname);
            actual_libname = "libigs_client.so";
        }
        
        // Determine dlopen flags
        int flags = RTLD_NOW;
        if (use_global) {
            flags |= RTLD_GLOBAL;  // Share symbols with other libraries
            LOGI("Loading %s with RTLD_GLOBAL (symbol sharing enabled)", actual_libname);
        } else {
            flags |= RTLD_LOCAL;   // Keep symbols private
        }
        
        // Clear any previous errors
        dlerror();
        
        // First try without path (system will search standard locations)
        handle = dlopen(actual_libname, flags);
        if (handle) {
            LOGI("✓ Loaded %s from system paths", actual_libname);
            return handle;
        } else {
            const char* error = dlerror();
            LOGW("Failed to load %s from system paths: %s", actual_libname, error ? error : "unknown error");
        }
        
        // Try each search path
        for (int i = 0; i < num_paths; i++) {
            std::string full_path = std::string(search_paths[i]) + "/" + actual_libname;
            
            dlerror();  // Clear previous error
            handle = dlopen(full_path.c_str(), flags);
            
            if (handle) {
                LOGI("✓ Loaded %s from %s", actual_libname, search_paths[i]);
                return handle;
            } else {
                const char* error = dlerror();
                LOGW("Failed to load %s from %s: %s", actual_libname, search_paths[i], error ? error : "unknown error");
            }
        }
        
        // Final error report
        const char* final_error = dlerror();
        LOGE("❌ FAILED to load %s from any location", actual_libname);
        LOGE("   Last error: %s", final_error ? final_error : "unknown error");
        LOGE("   Searched paths:");
        LOGE("     - System default paths");
        for (int i = 0; i < num_paths; i++) {
            LOGE("     - %s", search_paths[i]);
        }
        
        return nullptr;
    }

public:
    DynamicLoader() = default;
    ~DynamicLoader() {
        Unload();
    }

    /**
     * Load Huawei libraries with proper namespace handling
     * Uses OFFICIAL public libraries from /vendor/etc/public.libraries.txt
     */
    bool Load() {
        if (m_initialized) {
            LOGI("Already loaded");
            return true;
        }
        
        LOGI("Starting Huawei OSR library loading...");
        LOGI("Using OFFICIAL Huawei public libraries for namespace priming");
        
        // System library search paths for Huawei dependencies
        const char* system_paths[] = {
            "/system/lib64",
            "/vendor/lib64",
            "/vendor/lib64/hw",
            "/system/vendor/lib64",
        };
        
        // ========================================================================
        // STEP 1: Prime the namespace with OFFICIAL Huawei public libraries
        // These are listed in /vendor/etc/public.libraries.txt
        // ========================================================================
        
        LOGI("Priming namespace with official Huawei libraries...");
        
        // Load IGS (Intelligent Graphics System) Client
        // Use RTLD_GLOBAL to share symbols with CGKit plugin
        LOGI("Loading libigs_client.so (Huawei Graphics Core)...");
        void* igs_handle = TryLoadLibrary("libigs_client.so", system_paths, 4, true);  // ← RTLD_GLOBAL
        
        if (igs_handle) {
            LOGI("✓ Huawei Graphics Core link established (libigs_client.so loaded)");
            m_igraphics_handle = igs_handle;
        } else {
            LOGW("libigs_client.so not found - may not be available on this device");
        }
        
        // Load AI Client (for NPU acceleration)
        // Use RTLD_GLOBAL to share symbols with CGKit plugin
        LOGI("Loading libai_client.so (Huawei AI Core)...");
        void* ai_handle = TryLoadLibrary("libai_client.so", system_paths, 4, true);  // ← RTLD_GLOBAL
        
        if (ai_handle) {
            LOGI("✓ Huawei AI Core link established (libai_client.so loaded)");
            // Keep handle open to maintain namespace link
        } else {
            LOGW("libai_client.so not found - may not be available on this device");
        }
        
        // Load AI Infrastructure (optional)
        // Use RTLD_GLOBAL to share symbols
        LOGI("Loading libai_infra.so (Huawei AI Infrastructure)...");
        void* ai_infra_handle = TryLoadLibrary("libai_infra.so", system_paths, 4, true);  // ← RTLD_GLOBAL
        
        if (ai_infra_handle) {
            LOGI("✓ Huawei AI Infrastructure link established (libai_infra.so loaded)");
        } else {
            LOGW("libai_infra.so not found - optional library");
        }
        
        // Check if we have at least one Huawei library loaded
        if (!igs_handle && !ai_handle) {
            LOGE("No Huawei public libraries found - this may not be a Huawei device");
            LOGE("CGKit plugin may not work without Huawei system libraries");
            // Continue anyway - the plugin might still load
        }
        
        // ========================================================================
        // STEP 2: Load the CGKit plugin library
        // Namespace is now primed with official Huawei libraries
        // ========================================================================
        
        LOGI("Namespace primed successfully, loading CGKit OSR plugin...");
        
        // For app libraries, also check the app's lib directory
        const char* app_paths[] = {
            "/data/app/~~*/dev.eden.eden_emulator*/lib/arm64",
            "/data/data/dev.eden.eden_emulator/lib",
        };
        
        m_cgkit_handle = TryLoadLibrary("libcgkit_plugin_offlineSupRes.so", app_paths, 2);
        
        if (!m_cgkit_handle) {
            LOGE("Failed to load libcgkit_plugin_offlineSupRes.so");
            Unload();
            return false;
        }
        
        LOGI("✓ CGKit plugin loaded successfully");
        
        // Step 3: Load function pointers
        LOGI("Loading function pointers...");
        
        m_CInitialize = (CInitialize_t)dlsym(m_cgkit_handle, "CInitialize");
        m_CUninitialize = (CUninitialize_t)dlsym(m_cgkit_handle, "CUninitialize");
        m_CSetAssetsDir = (CSetAssetsDir_t)dlsym(m_cgkit_handle, "CSetAssetsDir");
        m_CGetAssetsDir = (CGetAssetsDir_t)dlsym(m_cgkit_handle, "CGetAssetsDir");
        m_CSuperSamplingSyncExecute = (CSuperSamplingSyncExecute_t)dlsym(m_cgkit_handle, "CSuperSamplingSyncExecute");
        m_CSuperSamplingAsyncExecute = (CSuperSamplingAsyncExecute_t)dlsym(m_cgkit_handle, "CSuperSamplingAsyncExecute");
        
        if (!m_CInitialize || !m_CSetAssetsDir || !m_CSuperSamplingSyncExecute) {
            LOGE("Failed to load required function pointers");
            Unload();
            return false;
        }
        
        LOGI("Function pointers loaded successfully");
        
        // Step 4: Initialize the plugin
        LOGI("Initializing Huawei OSR plugin...");
        
        try {
            m_CInitialize();
            LOGI("CInitialize() completed");
            
            // Set assets directory
            const char* assets_path = "/data/data/dev.eden.eden_emulator/assets/huawei_osr";
            m_CSetAssetsDir(assets_path);
            LOGI("CSetAssetsDir(%s) completed", assets_path);
            
            m_initialized = true;
            LOGI("Huawei OSR plugin initialized successfully!");
            return true;
            
        } catch (...) {
            LOGE("Exception during initialization");
            Unload();
            return false;
        }
    }

    /**
     * Unload libraries
     */
    void Unload() {
        if (m_CUninitialize && m_initialized) {
            try {
                m_CUninitialize();
                LOGI("CUninitialize() completed");
            } catch (...) {
                LOGE("Exception during uninitialization");
            }
        }
        
        if (m_cgkit_handle) {
            dlclose(m_cgkit_handle);
            m_cgkit_handle = nullptr;
            LOGI("CGKit plugin unloaded");
        }
        
        if (m_igraphics_handle) {
            dlclose(m_igraphics_handle);
            m_igraphics_handle = nullptr;
            LOGI("iGraphicsCore unloaded");
        }
        
        m_initialized = false;
        m_CInitialize = nullptr;
        m_CUninitialize = nullptr;
        m_CSetAssetsDir = nullptr;
        m_CGetAssetsDir = nullptr;
        m_CSuperSamplingSyncExecute = nullptr;
        m_CSuperSamplingAsyncExecute = nullptr;
    }

    /**
     * Check if library is loaded and initialized
     */
    bool IsAvailable() const {
        return m_initialized && m_CSuperSamplingSyncExecute != nullptr;
    }

    /**
     * Execute super-sampling (synchronous)
     */
    bool SuperSample(const void* inBuffer, const void* outBuffer, int timeout) {
        if (!IsAvailable()) {
            LOGE("Huawei OSR not available");
            return false;
        }
        
        return m_CSuperSamplingSyncExecute(inBuffer, outBuffer, timeout);
    }

    /**
     * Execute super-sampling (asynchronous)
     */
    bool SuperSampleAsync(const void* inBuffer, const void* outBuffer, void* callback) {
        if (!IsAvailable() || !m_CSuperSamplingAsyncExecute) {
            LOGE("Huawei OSR async not available");
            return false;
        }
        
        return m_CSuperSamplingAsyncExecute(inBuffer, outBuffer, callback);
    }
};

// Global instance
static DynamicLoader g_loader;

/**
 * Public API
 */
inline bool LoadHuaweiOSR() {
    return g_loader.Load();
}

inline void UnloadHuaweiOSR() {
    g_loader.Unload();
}

inline bool IsHuaweiOSRAvailable() {
    return g_loader.IsAvailable();
}

inline bool HuaweiSuperSample(const void* inBuffer, const void* outBuffer, int timeout = 5000) {
    return g_loader.SuperSample(inBuffer, outBuffer, timeout);
}

} // namespace HuaweiOSR
