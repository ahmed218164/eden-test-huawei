#ifndef MEMORY_ALLOCATOR_H
#define MEMORY_ALLOCATOR_H

#include "Core/Global.h"
#include "Core/Types.h"

NS_CG_BEGIN

template<typename T>
static inline T* AlignAddress(T* p, u64 alignment)
{
    return (T*) ((uintptr_t(p) + alignment - 1) & ~(alignment - 1));
}

template<typename T>
static inline T AlignArbitrary(T val, u64 alignment)
{
    ASSERT(alignment != 0);
    return (T) ((((u64) val + alignment - 1) / alignment) * alignment);
}

class CGKIT_EXPORT MemoryAllocator {
public:
    MemoryAllocator();

    ~MemoryAllocator();

    /*
     * allocate alignment memory
     */
    void* Alloc(u64 size, u64 alignment = alignof(f64))
    {
        if (alignment == 0) {
            alignment = alignof(f64);
        }

        u8* result = (u8*) AlignAddress(m_top, alignment);
        u8* newTop = result + size;

        if (newTop <= m_end) {
            m_top = newTop;
        } else {
            AllocateNewChunk(size + alignment);
            result = (u8*) AlignAddress(m_top, alignment);
            newTop = result + size;
            m_top = newTop;
        }
        return result;
    }

    /*
     * free memory
     */
    inline void Flush()
    {
        FreeChunks(nullptr);
    }

    /*
     * allocate memory and init object
     */
    template<typename T, u64 ALIGN = alignof(T), typename... ARGS>
    T* Allocate(ARGS&& ... args)
    {
        void* const pTmp = this->Alloc(sizeof(T), ALIGN);
        T* p = pTmp ? new(pTmp) T(std::forward<ARGS>(args)...) : nullptr;
        return p;
    }

    /*
     * free resource
     */
    void Free(void* p, u64 size)
    {
        CG_UNUSED(p);
        CG_UNUSED(size);
        return;
    }

private:
    struct TaggedMemory {
        TaggedMemory* next = nullptr;
        u64 dataSize = 0;

        u8* Data() const
        {
            return ((u8*) this) + sizeof(TaggedMemory);
        }
    };
    void AllocateNewChunk(u64 memSize);

    void FreeChunks(TaggedMemory* newTopChunk);

    u8* m_top = nullptr;
    u8* m_end = nullptr;
    TaggedMemory* m_topChunk = nullptr;
};

template<typename TYPE, typename MemAllocator>
class STLAllocator {
public:
    using value_type = TYPE;
    using pointer = TYPE*;
    using const_pointer = const TYPE*;
    using reference = TYPE&;
    using const_reference = const TYPE&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using propagate_on_container_move_assignment = std::true_type;
    using is_always_equal = std::true_type;

    template<typename OTHER>
    struct rebind {
        using other = STLAllocator<OTHER, MemAllocator>;
    };

public:
    STLAllocator(MemAllocator& memAllocator) : m_memAllocator(memAllocator)
    {}

    template<typename U>
    explicit STLAllocator(STLAllocator<U, MemAllocator> const& rhs) : m_memAllocator(rhs.m_memAllocator)
    {}

    ~STLAllocator() {}

    TYPE* allocate(std::size_t n)
    {
        auto p = static_cast<TYPE*>(m_memAllocator.Alloc(n * sizeof(TYPE), alignof(TYPE)));
        return p;
    }

    void deallocate(TYPE* p, std::size_t n)
    {
        m_memAllocator.Free(p, n * sizeof(TYPE));
    }

    template<typename U, typename A>
    bool operator==(const STLAllocator<U, A>& rhs) const
    {
        return std::addressof(m_memAllocator) == std::addressof(rhs.m_memAllocator);
    }

    template<typename U, typename A>
    bool operator!=(const STLAllocator<U, A>& rhs) const
    {
        return !operator==(rhs);
    }

private:
    template<typename U, typename A>
    friend
    class STLAllocator;

    MemAllocator& m_memAllocator;
};

template<typename T> using Allocator = STLAllocator<T, MemoryAllocator>;
template<typename T> using Vector = std::vector<T, Allocator<T>>;

NS_CG_END

#endif