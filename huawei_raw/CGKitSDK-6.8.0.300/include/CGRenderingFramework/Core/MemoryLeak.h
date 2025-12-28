/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: Define memory leak operations.
 */

#ifndef MEMORY_LEAK_H
#define MEMORY_LEAK_H

#include <new>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <utility>
#include "Core/Global.h"

NS_CG_BEGIN

namespace MemoryLeak {
#define HASHFTABLE_SIZE         (16384)
    using std::size_t;

    struct MemoryNode {
        const char*         file;
        size_t              line;
        size_t              size;
        MemoryNode*         next;
        std::chrono::high_resolution_clock::time_point start;
        void* pointer;
    };

    void DetectMemoryLeaks();
    MemoryNode* GetMemoryNode(size_t index);
    void SetMemoryNode(size_t index, MemoryNode* memoryNode);
    void LogNewPoint(const char* msg, const char* fileName, int line);
    void LogDeletePoint(const char* msg, long long int lifeCycle, unsigned int size, const char* fileName, int line);

    template<class T, class... Args>
    T* DebugNew(const char* file, int line, Args&&... args)
    {
        MemoryNode* ptr = new (std::nothrow) MemoryNode();
        if (ptr == nullptr) {
            return nullptr;
        }

        T* pointer = new T(std::forward<Args>(args)...);
        if (pointer == nullptr) {
            delete(ptr);
            return nullptr;
        }

        size_t hashindex = (((uint64_t)(pointer) >> 8) % HASHFTABLE_SIZE);
        ptr->next = GetMemoryNode(hashindex);
        ptr->file = file;
        ptr->line = line;
        ptr->size = sizeof(T);
        ptr->pointer = pointer;
        ptr->start = std::chrono::high_resolution_clock::now();

        SetMemoryNode(hashindex, ptr);
        LogNewPoint("MemoryLeak--- new construct", file, line);
        return pointer;
    }

    template<class T>
    T* DebugNewDefault(const char* file, int line)
    {
        MemoryNode* ptr = new (std::nothrow) MemoryNode();
        if (ptr == nullptr) {
            return nullptr;
        }

        T* pointer = new T();
        if (pointer == nullptr) {
            delete(ptr);
            return nullptr;
        }

        size_t hashindex = (((uint64_t)(pointer) >> 8) % HASHFTABLE_SIZE);

        ptr->next = GetMemoryNode(hashindex);
        ptr->file = file;
        ptr->line = line;
        ptr->size = sizeof(T);
        ptr->pointer = pointer;
        ptr->start = std::chrono::high_resolution_clock::now();

        SetMemoryNode(hashindex, ptr);
        LogNewPoint("MemoryLeak--- new default construct", file, line);
        return pointer;
    }

    template<class T>
    void DebugDelete(const char* file, int line, T* p)
    {
        size_t hashindex = (((uint64_t)(p) >> 8) % HASHFTABLE_SIZE);
        MemoryNode* ptr = GetMemoryNode(hashindex);
        MemoryNode* ptr_last = nullptr;
        auto lifeCycle = (ptr != nullptr) ?
            std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - ptr->start).count() : 0;
        auto size = (ptr != nullptr ? ptr->size : 0);
        LogDeletePoint("MemoryLeak--- delete", lifeCycle, size, file, line);
        while (ptr != nullptr) {
            if ((T*)ptr->pointer == p) {
                if (ptr_last == nullptr) {
                    SetMemoryNode(hashindex, ptr->next);
                } else {
                    ptr_last->next = ptr->next;
                }

                delete (p);
                p = nullptr;
                return;
            }
            ptr_last = ptr;
            ptr = ptr->next;
        }
        if (p != nullptr) {
            delete p;
            p = nullptr;
        }
    }

    template<class T>
    T* DebugNewArray(const char* file, int line, size_t size)
    {
        MemoryNode* ptr = new (std::nothrow) MemoryNode();
        if (ptr == nullptr) {
            return nullptr;
        }

        if (size <= 0) {
            return nullptr;
        }
        T* p = new T[size];
        if (p == nullptr) {
            delete(ptr);
            return nullptr;
        }
        size_t hashindex = (((uint64_t)(p) >> 8) % HASHFTABLE_SIZE);
        LogNewPoint("MemoryLeak--- new array", file, line);
        ptr->next = GetMemoryNode(hashindex);
        ptr->file = file;
        ptr->line = line;
        ptr->size = size * sizeof(T);
        ptr->pointer = p;
        ptr->start = std::chrono::high_resolution_clock::now();

        SetMemoryNode(hashindex, ptr);
        return p;
    }

    template<class T>
    void DebugDeleteArray(const char* file, int line, T* p)
    {
        size_t hashindex = (((uint64_t)(p) >> 8) % HASHFTABLE_SIZE);
        MemoryNode* ptr = GetMemoryNode(hashindex);
        MemoryNode* ptr_last = nullptr;
        auto lifeCycle = (ptr != nullptr) ?
            std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - ptr->start).count() : 0;
        auto size = (ptr != nullptr ? ptr->size : 0);
        LogDeletePoint("MemoryLeak--- delete array", lifeCycle, size, file, line);
        while (ptr != nullptr) {
            if ((T*) (ptr->pointer) == p) {
                if (ptr_last == nullptr) {
                    SetMemoryNode(hashindex, ptr->next);
                } else {
                    ptr_last->next = ptr->next;
                }
                delete[] p;
                p = nullptr;
                return;
            }
            ptr_last = ptr;
            ptr = ptr->next;
        }
        delete[] p;
        p = nullptr;
    }
}

#ifdef MEMORY_LEAK_DEBUG
#define CG_NEW(T, ...) MemoryLeak::DebugNew<T>(__FILE__, __LINE__, __VA_ARGS__)
#define CG_NEW_DEFAULT(T) MemoryLeak::DebugNewDefault<T>(__FILE__, __LINE__)
#define CG_DELETE(p) MemoryLeak::DebugDelete(__FILE__, __LINE__, p)
#define CG_NEW_ARRAY(T, size) MemoryLeak::DebugNewArray<T>(__FILE__, __LINE__, size)
#define CG_DELETE_ARRAY(T, p) MemoryLeak::DebugDeleteArray<T>(__FILE__, __LINE__, p)
#else
#define CG_NEW(T, ...) new (std::nothrow) T(__VA_ARGS__)
#define CG_NEW_DEFAULT(T) new (std::nothrow) T()
#define CG_DELETE(p) {delete(p); (p) = nullptr;}
#define CG_NEW_ARRAY(T, size) {new (std::nothrow) T[size]}
#define CG_DELETE_ARRAY(T, p) {delete[] (p); (p) = nullptr;}
#endif

#define CG_SAFE_DELETE_ARRAY(T, p) if ((p)) {           \
        CG_DELETE_ARRAY(T, p);                          \
    }

#define CG_SAFE_DELETE(p) if ((p)) {           \
        CG_DELETE(p);                          \
    }

NS_CG_END

#endif
