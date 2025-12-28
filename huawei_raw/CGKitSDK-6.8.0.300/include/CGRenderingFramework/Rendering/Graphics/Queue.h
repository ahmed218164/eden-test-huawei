/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2022-2022. All rights reserved.
 * Description: Queue
 */
#ifndef QUEUE_H
#define QUEUE_H

#include "QueueCreateInfo.h"

NS_CG_BEGIN

class CGKIT_EXPORT Queue {
public:
    Queue() = default;

    Queue(const Queue& queue) = delete;

    Queue& operator=(const Queue& queue) = delete;

    virtual ~Queue() = default;

    bool Create(const QueueCreateInfo& createInfo);

    const QueueCreateInfo& GetQueueCreateInfo() const;

protected:
    virtual bool CreateImpl(const QueueCreateInfo& createInfo) = 0;

    QueueCreateInfo m_createInfo{};
};

NS_CG_END

#endif