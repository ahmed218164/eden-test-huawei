# 🔄 LIBRARY UPDATE - CGKit Plugin Migration

**Date**: 2025-12-28 13:50 UTC  
**Change**: Switched from `libthirdpartyengine_plugin_offlineSupRes.so` to `libcgkit_plugin_offlineSupRes.so`  
**Status**: ✅ **UPDATED**

---

## 📝 CHANGES SUMMARY

### Library Name Change

**Old Library**: `libthirdpartyengine_plugin_offlineSupRes.so` (Third-Party Engine version)  
**New Library**: `libcgkit_plugin_offlineSupRes.so` (CGKit SDK version)

### Why the Change?

The Huawei SDK provides **two versions** of the Offline Super-Resolution plugin:

1. **`pkg-for-thirdpartyengine/`** → `libthirdpartyengine_plugin_offlineSupRes.so`
   - Designed for integration into non-CGKit engines (Unity, Unreal, etc.)
   - Standalone version with minimal dependencies

2. **`pkg-for-cgsdk/`** → `libcgkit_plugin_offlineSupRes.so` ⭐ **NOW USING THIS**
   - Designed for use with CGKit rendering framework
   - Potentially better integration with Huawei's ecosystem
   - May have better optimization for Kirin chipsets

---

## 🔧 CHANGES MADE

### File: `src/android/app/src/main/jni/CMakeLists.txt`

#### Updated Lines 7-23

**Before**:
```cmake
# =========================================================
# Huawei Kirin NPU Integration (Fixed)
# =========================================================

# Define the library using the CORRECT filename found in jniLibs
add_library(huawei_osr SHARED IMPORTED)

# Set the location relative to the CMake file
set_target_properties(huawei_osr PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libthirdpartyengine_plugin_offlineSupRes.so
)
```

**After**:
```cmake
# =========================================================
# Huawei Kirin NPU Integration - CGKit Plugin
# =========================================================

# Define the library using the CORRECT filename found in jniLibs
# Using pkg-for-cgsdk version (libcgkit_plugin_offlineSupRes.so)
add_library(huawei_osr SHARED IMPORTED)

# Set the location relative to the CMake file
set_target_properties(huawei_osr PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libcgkit_plugin_offlineSupRes.so
)
```

#### Linking Status (Lines 40-43)

**Still Disabled for Safe Loading**:
```cmake
target_link_libraries(yuzu-android PRIVATE audio_core common core input_common frontend_common video_core)
# TEMPORARILY DISABLED: Huawei OSR library causes SIGSEGV on startup
# Will be loaded dynamically with dlopen() when needed
# target_link_libraries(yuzu-android PRIVATE huawei_osr)
```

---

## 📦 REQUIRED FILE UPDATE

### You Need to Copy the New Library

**Source** (from Huawei SDK):
```
huawei_raw/cgsdk-plugin-6.1.0.300/
  └── cgsdk-plugin-offlinesuperresolution-5.0.4.301/
      └── cgsdk-plugin-offlinesuperresolution/
          └── pkg-for-cgsdk/
              └── libs/
                  └── arm64-v8a/
                      └── libcgkit_plugin_offlineSupRes.so  ← COPY THIS
```

**Destination**:
```
src/android/app/src/main/jniLibs/arm64-v8a/libcgkit_plugin_offlineSupRes.so
```

### PowerShell Command to Copy

```powershell
# Copy the new library
Copy-Item `
    "c:/Users/ELBOSTAN/Desktop/eden/huawei_raw/cgsdk-plugin-6.1.0.300/cgsdk-plugin-offlinesuperresolution-5.0.4.301/cgsdk-plugin-offlinesuperresolution/pkg-for-cgsdk/libs/arm64-v8a/libcgkit_plugin_offlineSupRes.so" `
    "c:/Users/ELBOSTAN/Desktop/eden/src/android/app/src/main/jniLibs/arm64-v8a/libcgkit_plugin_offlineSupRes.so"

# Verify the copy
Get-ChildItem "c:/Users/ELBOSTAN/Desktop/eden/src/android/app/src/main/jniLibs/arm64-v8a" | Format-Table Name, Length -AutoSize
```

### Expected File Size

- **`libcgkit_plugin_offlineSupRes.so`**: ~714 KB (714,584 bytes)

---

## 🔍 LIBRARY COMPARISON

| Feature | Third-Party Engine Version | CGKit Version ⭐ |
|---------|---------------------------|-----------------|
| **Filename** | `libthirdpartyengine_plugin_offlineSupRes.so` | `libcgkit_plugin_offlineSupRes.so` |
| **Size** | 993 KB | 714 KB |
| **Target** | Unity, Unreal, Custom Engines | CGKit Framework |
| **Dependencies** | Standalone | May require CGKit base |
| **Optimization** | Generic | Kirin-optimized |
| **API** | Same (OSRPluginInterface.h) | Same (OSRPluginInterface.h) |

---

## ⚠️ IMPORTANT NOTES

### 1. Safe Loading Still Active

The library is **still disabled** in the linking configuration to prevent startup crashes:

```cmake
# TEMPORARILY DISABLED: Huawei OSR library causes SIGSEGV on startup
# Will be loaded dynamically with dlopen() when needed
# target_link_libraries(yuzu-android PRIVATE huawei_osr)
```

**Why**: We need to:
1. First get the app to start successfully
2. Then implement Maleoon GPU detection
3. Only load the library on compatible hardware

### 2. Headers Remain the Same

The API is identical, so no changes needed to:
- `include/huawei/osr/OSRPluginInterface.h`
- `include/huawei/osr/OSRPluginCommon.h`

### 3. Assets May Differ

Check if the CGKit version uses different asset files:

**Old Assets** (third-party engine):
```
assets/huawei_osr/ie_data.bin  (461 KB)
```

**New Assets** (CGKit):
```
huawei_raw/cgsdk-plugin-6.1.0.300/
  └── cgsdk-plugin-offlinesuperresolution-5.0.4.301/
      └── cgsdk-plugin-offlinesuperresolution/
          └── pkg-for-cgsdk/
              └── assets/
                  └── [Check contents]
```

---

## 🚀 NEXT STEPS

### Step 1: Copy the New Library

```powershell
Copy-Item `
    "c:/Users/ELBOSTAN/Desktop/eden/huawei_raw/cgsdk-plugin-6.1.0.300/cgsdk-plugin-offlinesuperresolution-5.0.4.301/cgsdk-plugin-offlinesuperresolution/pkg-for-cgsdk/libs/arm64-v8a/libcgkit_plugin_offlineSupRes.so" `
    "c:/Users/ELBOSTAN/Desktop/eden/src/android/app/src/main/jniLibs/arm64-v8a/libcgkit_plugin_offlineSupRes.so"
```

### Step 2: (Optional) Remove Old Library

```powershell
# Remove the old third-party engine version
Remove-Item "c:/Users/ELBOSTAN/Desktop/eden/src/android/app/src/main/jniLibs/arm64-v8a/libthirdpartyengine_plugin_offlineSupRes.so"
```

### Step 3: Check Assets

```powershell
# List assets from CGKit version
Get-ChildItem "c:/Users/ELBOSTAN/Desktop/eden/huawei_raw/cgsdk-plugin-6.1.0.300/cgsdk-plugin-offlinesuperresolution-5.0.4.301/cgsdk-plugin-offlinesuperresolution/pkg-for-cgsdk/assets"
```

### Step 4: Build and Test

```bash
cd src/android
./gradlew clean
./gradlew assembleMainlineDebug
```

---

## 🔧 FUTURE: SAFE LOADING IMPLEMENTATION

When ready to enable the library, implement GPU detection:

### Option 1: Check GPU Model

```cpp
#include <vulkan/vulkan.h>

bool IsMaleonGPU() {
    // Get Vulkan device properties
    VkPhysicalDeviceProperties props;
    vkGetPhysicalDeviceProperties(physical_device, &props);
    
    // Check for Maleoon 910 (Kirin 9000WE)
    // Vendor ID: 0x??? (Huawei/HiSilicon)
    // Device ID: 0x??? (Maleoon 910)
    
    const char* deviceName = props.deviceName;
    
    // Check if device name contains "Maleoon" or "Mali-G78"
    if (strstr(deviceName, "Maleoon") || strstr(deviceName, "Mali-G78")) {
        return true;
    }
    
    return false;
}
```

### Option 2: Check System Properties

```cpp
#include <sys/system_properties.h>

bool IsHuaweiKirin9000() {
    char value[PROP_VALUE_MAX];
    
    // Check chipset
    __system_property_get("ro.board.platform", value);
    if (strcmp(value, "kirin9000") == 0) {
        return true;
    }
    
    // Check manufacturer
    __system_property_get("ro.product.manufacturer", value);
    if (strcmp(value, "HUAWEI") == 0 || strcmp(value, "HONOR") == 0) {
        // Additional checks for specific model
        return true;
    }
    
    return false;
}
```

### Option 3: Dynamic Loading with Error Handling

```cpp
bool LoadHuaweiOSRSafely() {
    // Only load on compatible hardware
    if (!IsMaleonGPU() && !IsHuaweiKirin9000()) {
        LOG_INFO(Frontend, "Huawei OSR: Incompatible GPU, skipping");
        return false;
    }
    
    LOG_INFO(Frontend, "Huawei OSR: Compatible GPU detected, loading...");
    
    // Try to load the library
    void* handle = dlopen("libcgkit_plugin_offlineSupRes.so", RTLD_NOW | RTLD_LOCAL);
    if (!handle) {
        LOG_ERROR(Frontend, "Huawei OSR: Failed to load: {}", dlerror());
        return false;
    }
    
    LOG_INFO(Frontend, "Huawei OSR: Loaded successfully!");
    return true;
}
```

---

## 📊 STATUS SUMMARY

| Item | Status | Notes |
|------|--------|-------|
| **CMakeLists.txt** | ✅ Updated | Now references `libcgkit_plugin_offlineSupRes.so` |
| **Library File** | ⏳ Pending | Need to copy from `pkg-for-cgsdk/` |
| **Linking** | ❌ Disabled | Safe loading - prevents startup crash |
| **Headers** | ✅ Compatible | Same API, no changes needed |
| **Assets** | ⏳ Check | Verify if CGKit version needs different assets |

---

## ✅ CHECKLIST

- [x] Update CMakeLists.txt library name
- [x] Keep safe loading disabled
- [ ] Copy `libcgkit_plugin_offlineSupRes.so` to `jniLibs/arm64-v8a/`
- [ ] Verify asset files compatibility
- [ ] (Optional) Remove old `libthirdpartyengine_plugin_offlineSupRes.so`
- [ ] Build and test
- [ ] Implement GPU detection for safe loading
- [ ] Re-enable linking when ready

---

**Next Action**: Copy the new library file to `jniLibs/arm64-v8a/` and verify it's the correct version (714 KB).
