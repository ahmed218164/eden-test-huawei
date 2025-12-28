/*
 * Copyright (c) Hisilicon Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: Dynamic array, which can be adjusted based on the element size to release resources.
 */

#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include "Core/Types.h"

NS_CG_BEGIN

template<class T>
class DynamicArray {
public:
    /* constructor */
    DynamicArray()
        : DynamicArray(8)
    {
    }

    /* Constructor with parameters */
    DynamicArray(u32 capacity)
        : m_size(0),
          m_capacity(capacity),
          m_step(capacity / 2),
          m_stride(sizeof(T)),
          m_data(static_cast<T*>(NewData(m_capacity * m_stride)))
    {
    }

    /* Delete copy constructor */
    DynamicArray(const DynamicArray& dynamicArray) = delete;

    /* Delete Assignment Action */
    DynamicArray& operator = (const DynamicArray& dynamicArray) = delete;

    /* Add move constructor */
    DynamicArray(DynamicArray&& dynamicArray): m_size(dynamicArray.m_size),
        m_capacity(dynamicArray.m_capacity),
        m_step(dynamicArray.m_step),
        m_stride(dynamicArray.m_stride),
        m_data(dynamicArray.m_data) {
        dynamicArray.m_data = nullptr;
        dynamicArray.m_capacity = 0;
        dynamicArray.m_size = 0;
    };

    /* Add move Assignment Action */
    DynamicArray& operator = (DynamicArray&& dynamicArray)
    {
        m_size = dynamicArray.m_size;
        m_capacity = dynamicArray.m_capacity;
        m_step = dynamicArray.m_step;
        m_stride = dynamicArray.m_stride;
        m_data = dynamicArray.m_data;
        dynamicArray.m_data = nullptr;
        dynamicArray.m_capacity = 0;
        dynamicArray.m_size = 0;
        return *this;
    };

    /* Destructor function, which releases memory. */
    ~DynamicArray()
    {
        Destroy(m_data, m_size);
        m_data = nullptr;
    }

    /* array size function */
    u32 Size() const
    {
        return m_size;
    }

    /* Check whether the array is empty. */
    u32 Empty() const
    {
        return m_size == 0;
    }

    /* Clear array elements. */
    void Clear()
    {
        for (u32 i = 0; i < m_size; i++) {
            m_data[i].~T();
        }
        m_size = 0;
    }

    /* Obtain the corresponding element through the subscript operator. */
    T& operator[](u32 index)
    {
        ASSERT(index < m_size);
        return m_data[index];
    }

    /* Obtain the const corresponding element through the subscript operator.*/
    const T& operator[](u32 index) const
    {
        ASSERT(index < m_size);
        return m_data[index];
    }

    /* Resize Arrays */
    void Resize(u32 size)
    {
        if (size <= m_size) {
            return;
        }

        if (size > m_capacity) {
            Extension(size - m_capacity);
        }

        for (u32 i = m_size; i < size; i++) {
            NewValue(m_data, i);
        }

        m_size = size;
    }

    /* The const element is added to the array. */
    void PushBack(const T& value)
    {
        if (m_size == m_capacity) {
            Extension(m_step);
        }
        NewValue(m_data, m_size++, value);
    }

    /* The element is added to the array. */
    void PushBack(T&& value)
    {
        if (m_size == m_capacity) {
            Extension(m_step);
        }
        NewValue(m_data, m_size++, std::forward<T>(value));
    }

    /* Obtains the data of an array. */
    const T* Data() const
    {
        if (Empty()) {
            return nullptr;
        }
        return m_data;
    }

private:
    /* Create Data */
    inline void* NewData(u32 size)
    {
        return operator new(size);
    }

    /* Delete Data */
    inline void DeleteData(void* data)
    {
        operator delete (data);
    }

    /* Create Value */
    inline T* NewValue(T* ptr, u32 index)
    {
        return new(&ptr[index]) T;
    }

    /* Create Value */
    inline T* NewValue(T* ptr, u32 index, const T& value)
    {
        return new(&ptr[index]) T(value);
    }

    /* Create Value */
    inline T* NewValue(T* ptr, u32 index, T&& value)
    {
        return new(&ptr[index]) T(std::forward<T>(value));
    }

    /* Destroy data.*/
    void Destroy(T* data, u32 size)
    {
        if (data == nullptr) {
            return;
        }

        for (u32 i = 0; i < size; i++) {
            data[i].~T();
        }

        DeleteData(data);
    }

    /* Array Extension */
    void Extension(u32 step)
    {
        u32 newCapacity = m_capacity + step;

        T* newData = static_cast<T*>(NewData(newCapacity * m_stride));
        for (u32 i = 0; i < m_size; i++) {
            NewValue(newData, i, m_data[i]);
            m_data[i].~T();
        }
        DeleteData(m_data);

        m_data = newData;
        m_capacity = newCapacity;
    }

private:
    u32 m_size;
    u32 m_capacity;
    u32 m_step;
    u32 m_stride;
    T* m_data;
};

NS_CG_END
#endif
