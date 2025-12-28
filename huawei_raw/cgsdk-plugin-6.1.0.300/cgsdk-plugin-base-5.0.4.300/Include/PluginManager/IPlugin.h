/*
* Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
* Description:
*/

#ifndef PLUGIN_H
#define PLUGIN_H

#include "Utils/Param.h"

NS_CG_BEGIN

/**
 * @brief Base class of Plugin.
 */
class IPlugin {
friend class PluginManager;
public:
    IPlugin();

    virtual ~IPlugin() = 0;

    virtual const String& GetPluginInfo() const = 0;

    /*
     * @brief execute super.
     *
     * @param[in]      paramIn
     * @param[in]      paramOut
     * @return @c true if super sampling is sucess, @c false otherwise.
     */
    virtual bool Execute(const Param& paramIn, Param& paramOut) = 0;

    virtual void Update(f32 dt);

    virtual void Render();

    bool IsPluginActive() const;

private:
    /*
     * @brief Initialize the plugin.
     */
    virtual bool Initialize() = 0;
    /*
     * @brief Uninitialize the plugin.
     */
    virtual void Uninitialize() = 0;
    const String& GetPluginName() const;
    void SetPluginName(const String& name);
    void SetPluginActive(bool active);
    void* GetPluginLib() const;
    void SetPluginLib(void* pLib);
    String m_pluginName;
    void* m_pluginLib {nullptr};
    bool m_active {false};
};

NS_CG_END

#endif
