/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2022. All rights reserved.
 * Description: Pipeline
 */
#ifndef PIPELINE_H
#define PIPELINE_H

#include "Rendering/Graphics/PipelineCreateInfo.h"

NS_CG_BEGIN

class CGKIT_EXPORT Pipeline {
public:
    /**
     * Default constructor.
     */
    Pipeline() = default;

    /**
     * Default destructor.
     */
    virtual ~Pipeline();

    /**
     * Delete function is used to prevent the copy and assignment of the class.
     */
    CG_DELETE_COPY_CONSTRUCTOR(Pipeline);

    /**
     * Create a Pipeline object based on the creation information.
     */
    bool Create(const PipelineCreateInfo& pipelineCreateInfo);

    /**
     * Acquire the creation information of the Pipeline object.
     */
    const PipelineCreateInfo& GetPipelineCreateInfo() const { return m_baseInfo; }

protected:
    virtual bool CreateImpl(const PipelineCreateInfo& pipelineCreateInfo) = 0;
private:
    PipelineCreateInfo m_baseInfo;
};

NS_CG_END

#endif