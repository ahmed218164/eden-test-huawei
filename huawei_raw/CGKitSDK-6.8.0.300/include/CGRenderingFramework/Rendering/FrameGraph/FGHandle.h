#ifndef FG_HANDLE_H
#define FG_HANDLE_H

#include "Core/Global.h"
#include "Core/Types.h"

NS_CG_BEGIN

using Handle = u32;

template<typename T>
class  FGHandle  {
public:
    using Type = T;
    static const Handle UNINITIALIZED = std::numeric_limits<Handle>::max();
    Handle m_handle = UNINITIALIZED;

    Handle GetHandle() const
    {
        return m_handle;
    }

    /*
     * is valid or not
     */
    bool IsValid() const
    {
        return m_handle != UNINITIALIZED;
    }
};

NS_CG_END

#endif
