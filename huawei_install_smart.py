#!/usr/bin/env python3
"""
Huawei SDK Smart Installer for Eden Emulator
Automatically detects Android project structure and installs SDK files
"""

import os
import shutil
import sys
from pathlib import Path
from typing import Optional, Tuple

# ANSI color codes for pretty output
class Colors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

def print_header(text: str):
    print(f"\n{Colors.HEADER}{Colors.BOLD}{'='*70}{Colors.ENDC}")
    print(f"{Colors.HEADER}{Colors.BOLD}{text.center(70)}{Colors.ENDC}")
    print(f"{Colors.HEADER}{Colors.BOLD}{'='*70}{Colors.ENDC}\n")

def print_success(text: str):
    print(f"{Colors.OKGREEN}✓ {text}{Colors.ENDC}")

def print_info(text: str):
    print(f"{Colors.OKCYAN}ℹ {text}{Colors.ENDC}")

def print_warning(text: str):
    print(f"{Colors.WARNING}⚠ {text}{Colors.ENDC}")

def print_error(text: str):
    print(f"{Colors.FAIL}✗ {text}{Colors.ENDC}")

def find_android_manifest(project_root: Path) -> Optional[Path]:
    """
    Recursively search for AndroidManifest.xml
    Returns the directory containing it (typically src/main)
    """
    print_info("Searching for AndroidManifest.xml...")
    
    for manifest_path in project_root.rglob("AndroidManifest.xml"):
        # Return the parent directory (should be src/main)
        target_root = manifest_path.parent
        print_success(f"Found AndroidManifest.xml at: {target_root}")
        return target_root
    
    return None

def find_cmake_lists(android_root: Path) -> Optional[Path]:
    """
    Find CMakeLists.txt near the Android files
    Typically in src/main/jni/ or src/main/cpp/
    """
    print_info("Searching for CMakeLists.txt near Android files...")
    
    # Search in common locations relative to android_root
    search_dirs = [
        android_root / "jni",
        android_root / "cpp",
        android_root / "jni" / "src",
        android_root / "cpp" / "src",
    ]
    
    for search_dir in search_dirs:
        cmake_path = search_dir / "CMakeLists.txt"
        if cmake_path.exists():
            print_success(f"Found CMakeLists.txt at: {cmake_path}")
            return cmake_path.parent
    
    # If not found in standard locations, search recursively
    for cmake_path in android_root.rglob("CMakeLists.txt"):
        if "jni" in str(cmake_path) or "cpp" in str(cmake_path):
            print_success(f"Found CMakeLists.txt at: {cmake_path}")
            return cmake_path.parent
    
    return None

def verify_source_files(huawei_raw: Path) -> Tuple[bool, dict]:
    """
    Verify that all required Huawei SDK files exist
    Returns (success, file_paths)
    """
    print_info("Verifying Huawei SDK source files...")
    
    files = {
        'header_common': huawei_raw / "cgsdk-plugin-6.1.0.300" / "cgsdk-plugin-offlinesuperresolution-5.0.4.301" / 
                        "cgsdk-plugin-offlinesuperresolution" / "pkg-for-thirdpartyengine" / "include" / "OSRPluginCommon.h",
        'header_interface': huawei_raw / "cgsdk-plugin-6.1.0.300" / "cgsdk-plugin-offlinesuperresolution-5.0.4.301" / 
                           "cgsdk-plugin-offlinesuperresolution" / "pkg-for-thirdpartyengine" / "include" / "OSRPluginInterface.h",
        'library': huawei_raw / "cgsdk-plugin-6.1.0.300" / "cgsdk-plugin-offlinesuperresolution-5.0.4.301" / 
                  "cgsdk-plugin-offlinesuperresolution" / "pkg-for-thirdpartyengine" / "libs" / "arm64-v8a" / 
                  "libthirdpartyengine_plugin_offlineSupRes.so",
        'asset': huawei_raw / "cgsdk-plugin-6.1.0.300" / "cgsdk-plugin-offlinesuperresolution-5.0.4.301" / 
                "cgsdk-plugin-offlinesuperresolution" / "pkg-for-thirdpartyengine" / "assets" / "ie_data.bin",
    }
    
    all_exist = True
    for name, path in files.items():
        if path.exists():
            size_mb = path.stat().st_size / (1024 * 1024)
            print_success(f"Found {name}: {path.name} ({size_mb:.2f} MB)")
        else:
            print_error(f"Missing {name}: {path}")
            all_exist = False
    
    return all_exist, files

def create_directory_structure(target_root: Path, cpp_root: Optional[Path]) -> dict:
    """
    Create necessary directory structure
    Returns dict of destination paths
    """
    print_info("Creating directory structure...")
    
    destinations = {
        'libs': target_root / "jniLibs" / "arm64-v8a",
        'assets': target_root / "assets" / "huawei_osr",
        'headers': (cpp_root / "include" / "huawei" / "osr") if cpp_root else (target_root / "cpp" / "include" / "huawei" / "osr"),
    }
    
    for name, path in destinations.items():
        path.mkdir(parents=True, exist_ok=True)
        print_success(f"Created {name} directory: {path}")
    
    return destinations

def copy_files(source_files: dict, destinations: dict) -> bool:
    """
    Copy SDK files to destination directories
    Returns True if all copies successful
    """
    print_info("Copying Huawei SDK files...")
    
    copy_operations = [
        (source_files['header_common'], destinations['headers'] / "OSRPluginCommon.h", "Header: OSRPluginCommon.h"),
        (source_files['header_interface'], destinations['headers'] / "OSRPluginInterface.h", "Header: OSRPluginInterface.h"),
        (source_files['library'], destinations['libs'] / "libthirdpartyengine_plugin_offlineSupRes.so", "Library: libthirdpartyengine_plugin_offlineSupRes.so"),
        (source_files['asset'], destinations['assets'] / "ie_data.bin", "Asset: ie_data.bin"),
    ]
    
    all_success = True
    for src, dst, description in copy_operations:
        try:
            shutil.copy2(src, dst)
            size_mb = dst.stat().st_size / (1024 * 1024)
            print_success(f"Copied {description} ({size_mb:.2f} MB)")
        except Exception as e:
            print_error(f"Failed to copy {description}: {e}")
            all_success = False
    
    return all_success

def generate_cmake_snippet(destinations: dict, cmake_path: Optional[Path]) -> str:
    """
    Generate CMakeLists.txt snippet for linking Huawei library
    """
    snippet = f"""
# ============================================================================
# Huawei Offline Super-Resolution Plugin Integration
# Auto-generated by install_smart.py
# ============================================================================

# Add Huawei OSR library
add_library(huawei_osr SHARED IMPORTED)
set_target_properties(huawei_osr PROPERTIES
    IMPORTED_LOCATION ${{CMAKE_SOURCE_DIR}}/../jniLibs/${{ANDROID_ABI}}/libthirdpartyengine_plugin_offlineSupRes.so
)

# Add Huawei include directory
include_directories({destinations['headers'].relative_to(cmake_path.parent) if cmake_path else 'include/huawei/osr'})

# Link Huawei OSR to your target (replace 'your_target_name' with actual target)
# target_link_libraries(your_target_name PRIVATE huawei_osr)

# ============================================================================
"""
    return snippet

def save_cmake_snippet(snippet: str, project_root: Path):
    """
    Save CMakeLists.txt snippet to a file for manual integration
    """
    snippet_file = project_root / "huawei_cmake_snippet.txt"
    with open(snippet_file, 'w') as f:
        f.write(snippet)
    print_success(f"Saved CMakeLists.txt snippet to: {snippet_file}")
    print_warning("Please manually add this snippet to your CMakeLists.txt")

def create_integration_guide(project_root: Path, destinations: dict):
    """
    Create a quick integration guide
    """
    guide_file = project_root / "HUAWEI_INTEGRATION_GUIDE.md"
    
    guide_content = f"""# Huawei SDK Integration Guide

## Installation Complete! ✓

The Huawei Offline Super-Resolution SDK has been installed to:

### Files Copied:
- **Headers**: `{destinations['headers']}`
  - OSRPluginCommon.h
  - OSRPluginInterface.h

- **Library**: `{destinations['libs']}`
  - libthirdpartyengine_plugin_offlineSupRes.so (993 KB)

- **Assets**: `{destinations['assets']}`
  - ie_data.bin (461 KB AI model)

---

## Next Steps:

### 1. Update CMakeLists.txt

Add the following to your `CMakeLists.txt` (see `huawei_cmake_snippet.txt`):

```cmake
# Add Huawei OSR library
add_library(huawei_osr SHARED IMPORTED)
set_target_properties(huawei_osr PROPERTIES
    IMPORTED_LOCATION ${{CMAKE_SOURCE_DIR}}/../jniLibs/${{ANDROID_ABI}}/libthirdpartyengine_plugin_offlineSupRes.so
)

# Link to your target
target_link_libraries(yuzu-android PRIVATE huawei_osr)
```

### 2. Include Headers in Your Code

```cpp
#include "huawei/osr/OSRPluginInterface.h"
#include "huawei/osr/OSRPluginCommon.h"
```

### 3. Initialize the Plugin

```cpp
// In your initialization code
CInitialize();
CSetAssetsDir("/data/data/your.package.name/assets/huawei_osr");
```

### 4. Use Super-Resolution

```cpp
// Example: Upscale a texture
CGKit::BufferDescriptor inBuffer = {{
    .addr = inputRGBA8Data,
    .len = width * height * 4,
    .width = width,
    .height = height,
    .format = CGKit::PIXEL_FORMAT_R8G8B8A8_UNORM
}};

CGKit::BufferDescriptor outBuffer = {{
    .addr = outputRGBA8Data,
    .len = (width * 2) * (height * 2) * 4,
    .width = width * 2,
    .height = height * 2,
    .format = CGKit::PIXEL_FORMAT_R8G8B8A8_UNORM
}};

bool success = CSuperSamplingSyncExecute(&inBuffer, &outBuffer, 5000); // 5s timeout
```

### 5. Integration Points in Eden Emulator

Recommended location: `src/video_core/texture_cache/util.cpp`

In the `ConvertImage()` function, after BCn decompression:

```cpp
// After: DecompressBCn(input_offset, output.subspan(output_offset), copy, info.format);

// Add Huawei upscaling
if (device.IsHuaweiKirin9000WE()) {{
    CGKit::BufferDescriptor inBuf = /* ... */;
    CGKit::BufferDescriptor outBuf = /* ... */;
    CSuperSamplingSyncExecute(&inBuf, &outBuf, 5000);
}}
```

---

## API Reference:

### Initialization
- `void CInitialize()` - Initialize plugin
- `void CUninitialize()` - Cleanup plugin
- `void CSetAssetsDir(const char *assetsPath)` - Set AI model path

### Super-Resolution
- `bool CSuperSamplingSyncExecute(...)` - Synchronous upscaling
- `bool CSuperSamplingAsyncExecute(...)` - Asynchronous upscaling
- `void CQuerySuperSamplingPluginConfig(...)` - Query capabilities

### Image Enhancement
- `bool CImageEnhancingSyncExecute(...)` - Sync enhancement with sharpening
- `bool CImageEnhancingAsyncExecute(...)` - Async enhancement

---

## Troubleshooting:

### Library Not Found
- Ensure `libthirdpartyengine_plugin_offlineSupRes.so` is in `jniLibs/arm64-v8a/`
- Check CMakeLists.txt has correct IMPORTED_LOCATION path

### Asset Not Found
- Verify `ie_data.bin` is in `assets/huawei_osr/`
- Check `CSetAssetsDir()` points to correct path at runtime

### Crashes on Initialization
- Ensure `CInitialize()` is called before any other API calls
- Check logcat for Huawei plugin error messages

---

For full architectural analysis, see: `HUAWEI_SDK_ANALYSIS.md`
"""
    
    with open(guide_file, 'w') as f:
        f.write(guide_content)
    
    print_success(f"Created integration guide: {guide_file}")

def main():
    print_header("Huawei SDK Smart Installer for Eden Emulator")
    
    # Get project root (script should be in project root)
    project_root = Path(__file__).parent.resolve()
    print_info(f"Project root: {project_root}")
    
    # Verify huawei_raw exists
    huawei_raw = project_root / "huawei_raw"
    if not huawei_raw.exists():
        print_error(f"huawei_raw directory not found at: {huawei_raw}")
        print_error("Please ensure the Huawei SDK is extracted to 'huawei_raw' folder")
        sys.exit(1)
    
    print_success(f"Found huawei_raw directory: {huawei_raw}")
    
    # Step 1: Verify source files
    files_exist, source_files = verify_source_files(huawei_raw)
    if not files_exist:
        print_error("Some required SDK files are missing!")
        sys.exit(1)
    
    # Step 2: Find Android project structure
    android_root = find_android_manifest(project_root)
    if not android_root:
        print_error("Could not find AndroidManifest.xml!")
        print_error("Please ensure this is an Android project")
        sys.exit(1)
    
    # Step 3: Find CMakeLists.txt for C++ code
    cpp_root = find_cmake_lists(android_root)
    if not cpp_root:
        print_warning("Could not find CMakeLists.txt, using default cpp/ directory")
    
    # Step 4: Create directory structure
    destinations = create_directory_structure(android_root, cpp_root)
    
    # Step 5: Copy files
    print_header("Installing Huawei SDK Files")
    success = copy_files(source_files, destinations)
    
    if not success:
        print_error("Some files failed to copy!")
        sys.exit(1)
    
    # Step 6: Generate CMake snippet
    print_header("Generating Integration Files")
    cmake_snippet = generate_cmake_snippet(destinations, cpp_root / "CMakeLists.txt" if cpp_root else None)
    save_cmake_snippet(cmake_snippet, project_root)
    
    # Step 7: Create integration guide
    create_integration_guide(project_root, destinations)
    
    # Success summary
    print_header("Installation Complete!")
    print_success("Huawei Offline Super-Resolution SDK installed successfully!")
    print_info("\nInstalled to:")
    print(f"  • Headers:  {destinations['headers']}")
    print(f"  • Library:  {destinations['libs']}")
    print(f"  • Assets:   {destinations['assets']}")
    
    print_info("\nNext steps:")
    print("  1. Review HUAWEI_INTEGRATION_GUIDE.md")
    print("  2. Add CMake snippet from huawei_cmake_snippet.txt to your CMakeLists.txt")
    print("  3. Include headers in your C++ code")
    print("  4. Call CInitialize() and CSetAssetsDir() at startup")
    print("  5. Integrate CSuperSamplingSyncExecute() into texture pipeline")
    
    print(f"\n{Colors.OKGREEN}{Colors.BOLD}Ready to build! 🚀{Colors.ENDC}\n")

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print_error("\nInstallation cancelled by user")
        sys.exit(1)
    except Exception as e:
        print_error(f"Unexpected error: {e}")
        import traceback
        traceback.print_exc()
        sys.exit(1)
