/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: Define custom types.
 */

#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include "Core/Global.h"

NS_CG_BEGIN

#define HashMap ::std::unordered_map
#define HashMultiMap ::std::unordered_multimap
#define HashSet ::std::unordered_set
#define HashMultiSet ::std::unordered_multiset

using u8 = uint8_t;
using s8 = int8_t;

using u16 = uint16_t;
using s16 = int16_t;

using u32 = uint32_t;
using s32 = int32_t;

using u64 = uint64_t;
using s64 = int64_t;

using f32 = float;
using f64 = double;
using c8 = char;

NS_CG_END

#ifdef CG_ANDROID_PLATFORM
#include <unistd.h>
#include <android/log.h>
#ifndef CGKIT_PLUGIN
#include <android_native_app_glue.h>
#endif
#endif
using String = std::string;
using StringStream = std::basic_stringstream<char, std::char_traits<char>, std::allocator<char>>;
using StringVector = std::vector<String>;

NS_CG_BEGIN
template <typename T>
using BindingMap = std::map<u32, std::map<u32, T>>;

template<typename T>
using ValueGetter = std::function<T()>;

template<typename T>
using ValueSetter = std::function<void(T)>;
NS_CG_END

#if defined API_GRAPHICS_VULKAN
#ifndef CGKIT_PLUGIN
#ifdef CG_WINDOWS_PLATFORM
#define VK_USE_PLATFORM_WIN32_KHR
#elif defined CG_ANDROID_PLATFORM
#define VK_USE_PLATFORM_ANDROID_KHR
#endif
#include <vulkan/vulkan.h>
#endif
#endif

#ifdef CG_WINDOWS_PLATFORM
#include <windows.h>
#endif

#include "Core/MemoryLeak.h"

#endif