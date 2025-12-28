/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: Singleton for class operations.
 */

#ifndef SINGLETON_H
#define SINGLETON_H

#include "Core/Types.h"
#include "Log/Log.h"

NS_CG_BEGIN

template <typename T>
class CGKIT_EXPORT Singleton {
public:
    /*
     * Obtains the reference to a singleton object of the T type.
     */
    static T& GetSingleton()
    {
        static T m_singleton;
        return m_singleton;
    }

protected:
    Singleton() {}
    virtual ~Singleton() {}
    Singleton(const Singleton&) {}
    Singleton& operator=(const Singleton&) { return *this; }
};

NS_CG_END

#endif