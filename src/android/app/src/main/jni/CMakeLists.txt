# SPDX-FileCopyrightText: Copyright 2025 Eden Emulator Project
# SPDX-License-Identifier: GPL-3.0-or-later

# SPDX-FileCopyrightText: 2023 yuzu Emulator Project
# SPDX-License-Identifier: GPL-3.0-or-later

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

# Add Huawei include directory
include_directories(include/huawei/osr)

# Add system library paths for Huawei dependencies
# This allows the linker to find libiGraphicsCore.huawei.so
if (ANDROID)
    # Add Huawei system library paths
    link_directories(
        /system/lib64
        /vendor/lib64
        /vendor/lib64/hw
    )
endif()

# =========================================================

add_library(yuzu-android SHARED
    emu_window/emu_window.cpp
    emu_window/emu_window.h
    native.cpp
    native.h
    native_config.cpp
    android_settings.cpp
    game_metadata.cpp
    native_log.cpp
    android_config.cpp
    android_config.h
    native_input.cpp
)

set_property(TARGET yuzu-android PROPERTY IMPORTED_LOCATION ${FFmpeg_LIBRARY_DIR})

target_link_libraries(yuzu-android PRIVATE audio_core common core input_common frontend_common video_core)
# TEMPORARILY DISABLED: Huawei OSR library causes SIGSEGV on startup
# Will be loaded dynamically with dlopen() when needed
# target_link_libraries(yuzu-android PRIVATE huawei_osr)
target_link_libraries(yuzu-android PRIVATE android camera2ndk EGL glad jnigraphics log)
if (ARCHITECTURE_arm64)
    target_link_libraries(yuzu-android PRIVATE adrenotools)
endif()

if (ENABLE_OPENSSL OR ENABLE_WEB_SERVICE)
    target_link_libraries(yuzu-android PRIVATE OpenSSL::SSL cpp-jwt::cpp-jwt)
endif()

if (ENABLE_UPDATE_CHECKER)
    target_compile_definitions(yuzu-android PUBLIC ENABLE_UPDATE_CHECKER)
endif()

set(CPACK_PACKAGE_EXECUTABLES ${CPACK_PACKAGE_EXECUTABLES} yuzu-android)
