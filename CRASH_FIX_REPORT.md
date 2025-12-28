# 🛡️ CRASH FIX APPLIED - Huawei Library Made Optional

**Date**: 2025-12-28 00:30 UTC  
**Issue**: SIGSEGV crash during app startup in `libthirdpartyengine_plugin_offlineSupRes.so`  
**Solution**: Disabled automatic library linking to prevent crash  

---

## ⚠️ PROBLEM IDENTIFIED

### Crash Details
- **Signal**: SIGSEGV (Segmentation Fault)
- **Location**: Inside `libthirdpartyengine_plugin_offlineSupRes.so`
- **When**: During initial device info logging (app startup)
- **Cause**: Library initialization code (constructor functions) crashing before `main()` even runs

### Why This Happens

When a shared library is linked with `target_link_libraries()`, it's loaded **automatically** when the app starts, before any of your code runs. The library's constructor functions (`__attribute__((constructor))`) execute immediately, and if they crash, your entire app crashes.

---

## ✅ SOLUTION APPLIED

### Changes Made to CMakeLists.txt

**File**: `src/android/app/src/main/jni/CMakeLists.txt`

**Before** (Line 40):
```cmake
target_link_libraries(yuzu-android PRIVATE audio_core common core input_common frontend_common video_core huawei_osr)
```

**After** (Lines 40-43):
```cmake
target_link_libraries(yuzu-android PRIVATE audio_core common core input_common frontend_common video_core)
# TEMPORARILY DISABLED: Huawei OSR library causes SIGSEGV on startup
# Will be loaded dynamically with dlopen() when needed
# target_link_libraries(yuzu-android PRIVATE huawei_osr)
```

### What This Does

✅ **Prevents automatic loading** of the Huawei library  
✅ **App will start successfully** without crashing  
✅ **Library still packaged in APK** (in `lib/arm64-v8a/`)  
✅ **Can be loaded later** using `dlopen()` when actually needed  

---

## 🚀 NEXT STEPS

### Step 1: Build and Test

```bash
cd src/android
./gradlew clean
./gradlew assembleMainlineDebug
adb install -r app/build/outputs/apk/mainline/debug/app-mainline-debug.apk
```

**Expected Result**: App should start without crashing! 🎉

### Step 2: Verify App Reaches Main Menu

```bash
adb logcat -c
adb logcat | grep -E "yuzu|Eden|Frontend"
```

**Look for**:
- ✅ "eden Version:" log message
- ✅ "Host OS: Android API level" log message
- ✅ Main menu appears
- ❌ No SIGSEGV or FATAL errors

---

## 🔧 FUTURE: DYNAMIC LOADING (Optional)

If you want to use the Huawei library later, you can load it dynamically:

### Option A: Load at Runtime (Recommended)

Create `src/android/app/src/main/jni/huawei_osr_loader.cpp`:

```cpp
#include <dlfcn.h>
#include <android/log.h>

#define LOG_TAG "HuaweiOSR"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

// Function pointers
typedef void (*CInitialize_t)();
typedef void (*CSetAssetsDir_t)(const char*);
typedef bool (*CSuperSamplingSyncExecute_t)(const void*, const void*, int);

static void* g_huawei_handle = nullptr;
static CInitialize_t g_CInitialize = nullptr;
static CSetAssetsDir_t g_CSetAssetsDir = nullptr;
static CSuperSamplingSyncExecute_t g_CSuperSamplingSyncExecute = nullptr;

bool LoadHuaweiOSRLibrary() {
    if (g_huawei_handle) {
        LOGI("Huawei OSR library already loaded");
        return true;
    }
    
    LOGI("Attempting to load Huawei OSR library...");
    
    // Try to load the library
    g_huawei_handle = dlopen("libthirdpartyengine_plugin_offlineSupRes.so", RTLD_NOW | RTLD_LOCAL);
    if (!g_huawei_handle) {
        LOGE("Failed to load Huawei OSR library: %s", dlerror());
        return false;
    }
    
    LOGI("Huawei OSR library loaded successfully");
    
    // Load function pointers
    g_CInitialize = (CInitialize_t)dlsym(g_huawei_handle, "CInitialize");
    g_CSetAssetsDir = (CSetAssetsDir_t)dlsym(g_huawei_handle, "CSetAssetsDir");
    g_CSuperSamplingSyncExecute = (CSuperSamplingSyncExecute_t)dlsym(g_huawei_handle, "CSuperSamplingSyncExecute");
    
    if (!g_CInitialize || !g_CSetAssetsDir || !g_CSuperSamplingSyncExecute) {
        LOGE("Failed to load Huawei OSR functions");
        dlclose(g_huawei_handle);
        g_huawei_handle = nullptr;
        return false;
    }
    
    LOGI("Huawei OSR functions loaded successfully");
    
    // Initialize the library
    try {
        g_CInitialize();
        g_CSetAssetsDir("/data/data/dev.eden.eden_emulator/assets/huawei_osr");
        LOGI("Huawei OSR initialized successfully");
        return true;
    } catch (...) {
        LOGE("Huawei OSR initialization failed");
        dlclose(g_huawei_handle);
        g_huawei_handle = nullptr;
        return false;
    }
}

bool IsHuaweiOSRAvailable() {
    return g_huawei_handle != nullptr && g_CSuperSamplingSyncExecute != nullptr;
}

bool HuaweiSuperSample(const void* inBuffer, const void* outBuffer, int timeout) {
    if (!IsHuaweiOSRAvailable()) {
        LOGE("Huawei OSR not available");
        return false;
    }
    
    return g_CSuperSamplingSyncExecute(inBuffer, outBuffer, timeout);
}

void UnloadHuaweiOSRLibrary() {
    if (g_huawei_handle) {
        dlclose(g_huawei_handle);
        g_huawei_handle = nullptr;
        g_CInitialize = nullptr;
        g_CSetAssetsDir = nullptr;
        g_CSuperSamplingSyncExecute = nullptr;
        LOGI("Huawei OSR library unloaded");
    }
}
```

### Option B: Try-Catch in Java (Simpler)

In `NativeLibrary.kt`, add:

```kotlin
object HuaweiOSR {
    private var isAvailable = false
    
    init {
        try {
            System.loadLibrary("thirdpartyengine_plugin_offlineSupRes")
            isAvailable = true
            Log.info("[HuaweiOSR] Library loaded successfully")
        } catch (e: UnsatisfiedLinkError) {
            Log.warning("[HuaweiOSR] Library not available: ${e.message}")
            isAvailable = false
        }
    }
    
    fun isAvailable(): Boolean = isAvailable
}
```

---

## 📊 COMPARISON

### Before (Automatic Loading)
```
App Start
    ↓
Load libyuzu-android.so
    ↓
Load libthirdpartyengine_plugin_offlineSupRes.so  ← CRASH HERE
    ↓
Run library constructors  ← SIGSEGV!
    ↓
❌ App never reaches main()
```

### After (Disabled Loading)
```
App Start
    ↓
Load libyuzu-android.so
    ↓
✅ Skip Huawei library
    ↓
Run main()
    ↓
✅ App starts successfully!
    ↓
(Optional) Load Huawei library later with dlopen()
```

---

## 🔍 WHY THE LIBRARY CRASHES

Possible reasons for the SIGSEGV:

1. **Missing Dependencies**: Library expects certain system libraries that aren't available
2. **Hardware Detection**: Library tries to access Huawei-specific hardware/drivers
3. **OpenGL Context**: Library tries to create GL context before window is ready
4. **Asset Files**: Library tries to load `ie_data.bin` but can't find it
5. **Incompatible Device**: Library only works on specific Huawei chipsets

### Investigation Needed

To find the exact cause, we'd need to:
1. Run with `adb logcat` to see the crash stack trace
2. Use `gdb` or `lldb` to debug the crash
3. Check if the library has device/chipset requirements

---

## ✅ CURRENT STATUS

| Item | Status | Notes |
|------|--------|-------|
| **Library Linking** | ❌ Disabled | Commented out in CMakeLists.txt |
| **Library in APK** | ✅ Still Packaged | In `lib/arm64-v8a/` |
| **App Startup** | ✅ Should Work | No automatic loading |
| **Huawei Features** | ❌ Disabled | Can be enabled later with dlopen() |

---

## 🎯 IMMEDIATE ACTION

### Build and Test

```bash
cd src/android
./gradlew clean
./gradlew assembleMainlineDebug
adb install -r app/build/outputs/apk/mainline/debug/app-mainline-debug.apk
```

### Monitor Logs

```bash
adb logcat -c
adb logcat | grep -E "yuzu|Eden|FATAL|SIGSEGV"
```

**Success Criteria**:
- ✅ App starts without crash
- ✅ Reaches main menu
- ✅ Can browse games
- ✅ No SIGSEGV errors

---

## 📝 NOTES

1. **The library is still in the APK** - It's just not loaded automatically
2. **You can re-enable it later** - Uncomment the line in CMakeLists.txt
3. **Dynamic loading is safer** - Allows graceful fallback if library fails
4. **This is a temporary fix** - Investigate the root cause when you have time

---

## 🔄 TO RE-ENABLE (After Fixing Root Cause)

1. Uncomment line 43 in CMakeLists.txt:
   ```cmake
   target_link_libraries(yuzu-android PRIVATE huawei_osr)
   ```

2. Rebuild:
   ```bash
   ./gradlew clean
   ./gradlew assembleMainlineDebug
   ```

---

**Status**: ✅ **FIX APPLIED - READY TO BUILD**  
**Next**: Build and test to verify app starts without crashing
