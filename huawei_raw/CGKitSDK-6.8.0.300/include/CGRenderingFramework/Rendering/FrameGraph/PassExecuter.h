#ifndef FGPASS_H
#define FGPASS_H

#include "Core/Global.h"
#include "Rendering/FrameGraph/FGCommon.h"
#include "Rendering/Graphics/CommandBuffer.h"

NS_CG_BEGIN

class CGKIT_EXPORT IPassExecuter {
public:
    virtual ~IPassExecuter();

    /*
     * execute callBack function
     */
    virtual void Execute(PassExecuteParam& param) = 0;
};

template<typename Data, typename Executer>
class PassExecutor : public IPassExecuter {
public:
    virtual ~PassExecutor() {};
    explicit PassExecutor(Executer&& execute) : m_execute(std::move(execute))
    {}

    virtual void Execute(PassExecuteParam& param) override
    {
        m_execute(param, m_data);
    }

    Data const& GetData() const
    {
        return m_data;
    }

private:
    Executer m_execute;
    Data m_data;
};

NS_CG_END

#endif
