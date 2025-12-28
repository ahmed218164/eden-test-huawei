/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: Define general macros.
 */

#ifndef MACRO_H
#define MACRO_H

#include <assert.h>
#include <stdio.h>
#include <exception>
#include <typeinfo>

#define LEN_OF_ARRAY(array) s32(sizeof(array) / sizeof((array)[0]))
#define FAIL_RET_X(act, x) if (!(act))            \
        return x;
#define FAIL_RET_VOID(act) if (!(act))            \
        return;
#define FAIL_RET(act) FAIL_RET_X(act, false);
#define FAIL_BREAK(act) if (!(act))               \
        break;
#define SUCC_RET_X(act, x) if (act)               \
        return x;
#define SUCC_RET_VOID(act) if (act)               \
        return;
#define ASSERT(expression) assert(expression)
#define ASSERT_MSG(cond, msg) assert((cond) && ("Reason: " msg));
#define ASSERT_MSG_RET(cond, msg) ASSERT_MSG(cond, msg);          \
    FAIL_RET(cond);
#define ASSERT_MSG_RET_X(cond, msg, x) ASSERT_MSG(cond, msg);     \
    FAIL_RET_X(cond, x);
#define ASSERT_MSG_RET_VOID(cond, msg) ASSERT_MSG(cond, msg);     \
    FAIL_RET_VOID(cond);
#define CLR_BIT(var, bit) ((var) &= (~(bit)))
#define SET_BIT(var, bit) ((var) |= (bit))

#define CG_DEBUG_BREAK_IF(cond) if (cond) {    \
    }

#define CG_UNUSED(a) (void)a

#ifdef __clang__
#define PUSH_DISABLE_OVERRIDE_WARNING \
    _Pragma("clang diagnostic push") \
    _Pragma("clang diagnostic ignored \"-Winconsistent-missing-override\"")
#define POP_DISABLE_OVERRIDE_WARNING \
    _Pragma("clang diagnostic pop")
#define PUSH_DISABLE_FORMAT_WARNING \
    _Pragma("clang diagnostic push") \
    _Pragma("clang diagnostic ignored \"-Wformat-nonliteral\"")
#define POP_DISABLE_FORMAT_WARNING \
    _Pragma("clang diagnostic pop")
#else
#define PUSH_DISABLE_OVERRIDE_WARNING
#define POP_DISABLE_OVERRIDE_WARNING
#define PUSH_DISABLE_FORMAT_WARNING
#define POP_DISABLE_FORMAT_WARNING
#endif

using RTTIType = std::type_info;

#define RTTI_DEFINE(CLASS)                                         \
public:                                                            \
    PUSH_DISABLE_OVERRIDE_WARNING                                  \
    static const inline RTTIType& RTTITypeId()                     \
    {                                                              \
        static const RTTIType& RTTI_TYPE = typeid(CLASS);          \
        return RTTI_TYPE;                                          \
    }                                                              \
    virtual const inline RTTIType& RTTIGetTypeId() const           \
    {                                                              \
        return CLASS::RTTITypeId();                                \
    }                                                              \
    virtual inline bool RTTIIsTypeOf(const RTTIType& typeId) const \
    {                                                              \
        return typeId == CLASS::RTTITypeId();                      \
    }                                                              \
    POP_DISABLE_OVERRIDE_WARNING

#define CG_DELETE_COPY_CONSTRUCTOR(CLASS)                         \
    CLASS(const CLASS&) = delete;                                 \
    CLASS& operator=(const CLASS&) = delete;

#define CG_DELETE_MOVE_CONSTRUCTOR(CLASS)                         \
    CLASS(CLASS&&) = delete;                                      \
    CLASS& operator=(CLASS&&) = delete;

#define CG_DELETE_COPY_AND_MOVE_CONSTRUCTOR(CLASS)                \
        CG_DELETE_COPY_CONSTRUCTOR(CLASS)                         \
        CG_DELETE_MOVE_CONSTRUCTOR(CLASS)
#endif

#define CHECK_NULL_RETURN_NULL(p) \
    {                             \
        if (nullptr == (p)) {        \
            return nullptr;          \
        }                         \
    }
#define CHECK_NULL_RETURN_VALUE(p, value) \
    {                                   \
        if (nullptr == (p)) {              \
            return value;               \
        }                               \
    }
#define CHECK_NULL_RETURN_VOID(p) \
    {                             \
        if (nullptr == (p)) {        \
            return;               \
        }                         \
    }
