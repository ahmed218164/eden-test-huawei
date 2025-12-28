/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: Reference count of resoruce.
 */

#ifndef RESOURCE_RERCOUNT_H
#define RESOURCE_RERCOUNT_H

#include "Core/Types.h"

NS_CG_BEGIN

/*
 * Class RefCount
 * A resource reference counter class used to increase or decrease the reference counter value
 * of a resource and determine if a resource can be destroyed.
 */
class CGKIT_EXPORT RefCount
{
public:
    RefCount() {}
    virtual ~RefCount() {}

    /*
     * Increases the reference counter value of a resource by 1.
     */
    void IncRef() { m_count++; }

    /*
     * Decreases the reference counter value of a resource by 1.
     */
    void DecRef() { m_count--; }

    /*
     * Determines if a resource can be destroyed.
     * If the reference counter value is 0, true is returned. Otherwise, false is returned.
     */
    bool CanDestroy() { return m_count <= 0; }

    /*
     * Obtains the reference counter value of a resource.
     */
    s32 GetRef() { return m_count; }

private:
    s32 m_count = 1; // when create, the reference count is 1
};

NS_CG_END

#endif