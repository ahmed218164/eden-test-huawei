# 🔍 SANITY CHECK REPORT: Pre-built Library Integration
## Eden Emulator Android - Library Packaging Analysis

**Date**: 2025-12-27  
**Target Library**: `libhuawei_ai.so`  
**Project**: Eden Emulator (Yuzu Fork)  

---

## 📊 EXECUTIVE SUMMARY

**Status**: ❌ **LIBRARY NOT FOUND**  
**Issue**: The library `libhuawei_ai.so` does not exist in your project  
**Current Setup**: You have `libthirdpartyengine_plugin_offlineSupRes.so` (Huawei OSR) configured correctly  
**Action Required**: Clarify library name or create/copy the missing library  

---

## 🔎 STEP 1: SEARCH FOR THE LIBRARY

### Search Results for `libhuawei_ai.so`

```
❌ NOT FOUND in src/android directory
```

**Searched**: Entire `src/android` directory tree  
**Result**: 0 matches  

### Alternative: Found Huawei Library

```
✅ FOUND: libthirdpartyengine_plugin_offlineSupRes.so
```

**Locations**:
1. **Source** (correct): `src/android/app/src/main/jniLibs/arm64-v8a/libthirdpartyengine_plugin_offlineSupRes.so` (993 KB)
2. **Build intermediates** (4 copies in build cache - normal)

---

## 📁 STEP 2: CHECK STANDARD PATH

### Path Verification

**Path**: `src/android/app/src/main/jniLibs/arm64-v8a`

```
✅ EXISTS
```

**Contents**:
```
src/android/app/src/main/jniLibs/
├── arm64-v8a/
│   ├── libthirdpartyengine_plugin_offlineSupRes.so  (993 KB)   ✅
│   └── libVkLayer_khronos_validation.so             (23.7 MB)  ✅
└── x86_64/
    └── (empty)
```

**Analysis**:
- ✅ Standard Android `jniLibs` structure is correct
- ✅ `arm64-v8a` directory exists
- ✅ Huawei OSR library is in the correct location
- ❌ `libhuawei_ai.so` is missing

---

## 📄 STEP 3: ANALYZE build.gradle.kts

### File: `src/android/app/build.gradle.kts`

#### jniLibs Configuration

**Line 55**: 
```kotlin
jniLibs.useLegacyPackaging = true
```

**Analysis**: ✅ **CORRECT**
- Legacy packaging is enabled (required for custom driver loading)
- This ensures `.so` files are extracted at install time

#### sourceSets Block

**Search Result**: ❌ **NOT FOUND**

**Analysis**: ✅ **THIS IS NORMAL**
- Gradle automatically picks up libraries from `src/main/jniLibs/` by default
- No explicit `sourceSets` configuration is needed
- The default behavior is:
  ```kotlin
  // Implicit default (you don't need to add this)
  sourceSets {
      main {
          jniLibs.srcDirs = ["src/main/jniLibs"]
      }
  }
  ```

#### ABI Filters

**Lines 92, 97**:
```kotlin
externalNativeBuild {
    cmake {
        abiFilters("arm64-v8a")  // ✅ Correct
    }
}

ndk {
    abiFilters += listOf("arm64-v8a")  // ✅ Correct
}
```

**Analysis**: ✅ **CORRECT**
- Only building for arm64-v8a (Huawei Kirin 9000WE)
- Prevents unnecessary x86_64 builds

---

## 🔧 STEP 4: ANALYZE CMakeLists.txt

### File: `src/android/app/src/main/jni/CMakeLists.txt`

#### Huawei Library Configuration (Lines 11-15)

```cmake
# Add Huawei OSR library
add_library(huawei_osr SHARED IMPORTED)
set_target_properties(huawei_osr PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libthirdpartyengine_plugin_offlineSupRes.so
)
```

**Analysis**: ✅ **CORRECT** (after your fix)

**Path Type**: ✅ **RELATIVE** (using `CMAKE_CURRENT_SOURCE_DIR`)

**Path Resolution**:
```
${CMAKE_CURRENT_SOURCE_DIR} = src/android/app/src/main/jni
../jniLibs/${ANDROID_ABI}   = src/android/app/src/main/jniLibs/arm64-v8a
Full path                   = src/android/app/src/main/jniLibs/arm64-v8a/libthirdpartyengine_plugin_offlineSupRes.so
```

**Your Fix**: ✅ **GOOD**
- Changed from `CMAKE_SOURCE_DIR` to `CMAKE_CURRENT_SOURCE_DIR`
- This is more robust for multi-module projects

#### Linking Configuration (Line 38)

```cmake
target_link_libraries(yuzu-android PRIVATE audio_core common core input_common frontend_common video_core huawei_osr)
```

**Analysis**: ✅ **CORRECT**
- `huawei_osr` is linked to the main `yuzu-android` target
- Will be included in the APK

---

## 🚨 PROBLEM DIAGNOSIS

### Issue: `libhuawei_ai.so` Not Found

**Possible Scenarios**:

#### Scenario 1: Wrong Library Name
You mentioned `libhuawei_ai.so`, but your project uses `libthirdpartyengine_plugin_offlineSupRes.so`.

**Question**: Are these the same library with different names?

#### Scenario 2: Library Not Yet Copied
You have the library elsewhere but haven't copied it to `jniLibs/` yet.

**Question**: Do you have `libhuawei_ai.so` somewhere else on your system?

#### Scenario 3: Different Huawei Library
You want to add a **second** Huawei library in addition to the OSR plugin.

**Question**: Are you trying to add a different Huawei AI library?

---

## ✅ CURRENT STATUS: What's Working

### Huawei OSR Library (libthirdpartyengine_plugin_offlineSupRes.so)

**Status**: ✅ **CORRECTLY CONFIGURED**

1. ✅ Library exists in correct location: `jniLibs/arm64-v8a/`
2. ✅ CMakeLists.txt imports it correctly
3. ✅ Linked to main target
4. ✅ Will be packaged in APK
5. ✅ Gradle will include it automatically

**Verification**:
```bash
# After building, check APK contents:
unzip -l app-mainline-debug.apk | grep libthirdpartyengine

# Should show:
# lib/arm64-v8a/libthirdpartyengine_plugin_offlineSupRes.so
```

---

## 🛠️ REQUIRED ACTIONS

### Option A: If `libhuawei_ai.so` is the OSR Library (Just Renamed)

**No action needed** - Your library is already integrated as `libthirdpartyengine_plugin_offlineSupRes.so`

### Option B: If You Have `libhuawei_ai.so` Elsewhere

**Step 1**: Copy the library to the correct location

```powershell
# Create directory if needed (already exists)
New-Item -ItemType Directory -Force -Path "c:/Users/ELBOSTAN/Desktop/eden/src/android/app/src/main/jniLibs/arm64-v8a"

# Copy your library (replace SOURCE_PATH with actual path)
Copy-Item "SOURCE_PATH/libhuawei_ai.so" "c:/Users/ELBOSTAN/Desktop/eden/src/android/app/src/main/jniLibs/arm64-v8a/libhuawei_ai.so"

# Verify
Get-ChildItem "c:/Users/ELBOSTAN/Desktop/eden/src/android/app/src/main/jniLibs/arm64-v8a"
```

**Step 2**: Add to CMakeLists.txt

Add after the existing Huawei OSR configuration:

```cmake
# Add Huawei AI library
add_library(huawei_ai SHARED IMPORTED)
set_target_properties(huawei_ai PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libhuawei_ai.so
)

# Link it
target_link_libraries(yuzu-android PRIVATE huawei_ai)
```

**Step 3**: Clean and rebuild

```bash
cd src/android
./gradlew clean
./gradlew assembleMainlineDebug
```

### Option C: If the Library Doesn't Exist Yet

**You need to**:
1. Obtain `libhuawei_ai.so` from Huawei SDK or build it
2. Follow Option B steps above

---

## 📋 VERIFICATION CHECKLIST

After adding the library, verify:

- [ ] Library exists in `jniLibs/arm64-v8a/`
- [ ] CMakeLists.txt imports it with `add_library(... IMPORTED)`
- [ ] CMakeLists.txt links it with `target_link_libraries()`
- [ ] Build completes without errors
- [ ] APK contains the library in `lib/arm64-v8a/`
- [ ] App doesn't crash on startup

---

## 🔍 APK VERIFICATION COMMANDS

### Check if Library is Packaged

```powershell
# Find the APK
Get-ChildItem -Recurse -Filter "*.apk" "c:/Users/ELBOSTAN/Desktop/eden/src/android/app/build/outputs"

# Extract and check contents (replace with actual APK path)
Add-Type -AssemblyName System.IO.Compression.FileSystem
$apk = [System.IO.Compression.ZipFile]::OpenRead("path/to/app-mainline-debug.apk")
$apk.Entries | Where-Object { $_.FullName -like "lib/arm64-v8a/*.so" } | Select-Object FullName, Length
$apk.Dispose()
```

### Expected Output

```
FullName                                                    Length
--------                                                    ------
lib/arm64-v8a/libyuzu-android.so                           [size]
lib/arm64-v8a/libthirdpartyengine_plugin_offlineSupRes.so  993272
lib/arm64-v8a/libhuawei_ai.so                              [size]  ← Should appear here
lib/arm64-v8a/libadrenotools.so                            [size]
```

---

## 🎯 SUMMARY

| Item | Status | Notes |
|------|--------|-------|
| **libhuawei_ai.so** | ❌ Not Found | Library doesn't exist in project |
| **jniLibs/arm64-v8a/** | ✅ Exists | Correct structure |
| **build.gradle.kts** | ✅ Correct | No sourceSets needed (using defaults) |
| **CMakeLists.txt** | ✅ Correct | Relative path, properly linked |
| **Huawei OSR Library** | ✅ Working | Already integrated correctly |

---

## 🤔 NEXT STEP: PLEASE CLARIFY

**Question 1**: Is `libhuawei_ai.so` the same as `libthirdpartyengine_plugin_offlineSupRes.so`?
- If YES → No action needed, library is already integrated
- If NO → Where is `libhuawei_ai.so` located?

**Question 2**: What is the exact crash error?
- Check logcat: `adb logcat | grep -i "huawei\|dlopen\|FATAL"`
- This will tell us if it's a missing library or a different issue

**Question 3**: Are you trying to add a second Huawei library?
- If YES → Provide the library file and I'll help integrate it
- If NO → The current setup should work

---

**Report Generated**: 2025-12-27 23:31 UTC  
**Status**: Awaiting clarification on library name/location
