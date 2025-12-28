# Huawei SDK Smart Installer

## Quick Start

Run the installer from the project root:

```bash
python huawei_install_smart.py
```

## What It Does

The script automatically:

1. **Detects Android Project Structure**
   - Searches for `AndroidManifest.xml` recursively
   - Finds the `src/main` directory automatically
   - Locates `CMakeLists.txt` for C++ code

2. **Verifies SDK Files**
   - Checks all required Huawei SDK files exist
   - Displays file sizes for verification

3. **Creates Directory Structure**
   - `jniLibs/arm64-v8a/` - Native libraries
   - `assets/huawei_osr/` - AI model files
   - `jni/include/huawei/osr/` - C++ headers

4. **Copies Files**
   - Headers: `OSRPluginCommon.h`, `OSRPluginInterface.h`
   - Library: `libthirdpartyengine_plugin_offlineSupRes.so` (993 KB)
   - Asset: `ie_data.bin` (461 KB AI model)

5. **Generates Integration Files**
   - `huawei_cmake_snippet.txt` - CMake configuration
   - `HUAWEI_INTEGRATION_GUIDE.md` - Step-by-step guide

## Output

After successful installation:

```
✓ Found AndroidManifest.xml at: src/android/app/src/main
✓ Found CMakeLists.txt at: src/android/app/src/main/jni
✓ Copied Header: OSRPluginCommon.h
✓ Copied Header: OSRPluginInterface.h
✓ Copied Library: libthirdpartyengine_plugin_offlineSupRes.so (0.97 MB)
✓ Copied Asset: ie_data.bin (0.45 MB)
✓ Created integration guide: HUAWEI_INTEGRATION_GUIDE.md
```

## Next Steps

1. Review `HUAWEI_INTEGRATION_GUIDE.md`
2. Add CMake snippet to your `CMakeLists.txt`
3. Include headers in your C++ code
4. Initialize and use the API

## Requirements

- Python 3.6+
- `huawei_raw/` directory with extracted SDK

## Troubleshooting

**Error: "huawei_raw directory not found"**
- Ensure SDK is extracted to `huawei_raw` folder in project root

**Error: "Could not find AndroidManifest.xml"**
- Ensure you're running from the Eden project root
- Verify this is an Android project

**Error: "Some required SDK files are missing"**
- Re-extract the Huawei SDK
- Check all files are present in `huawei_raw/`
