/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: IPlugin utils.
 */

#ifndef PLUGIN_H
#define PLUGIN_H

#include "Utils/Param.h"

NS_CG_BEGIN

class IPlugin {
friend class PluginManager;
public:
    IPlugin();
    virtual ~IPlugin() = 0;

    /*
     * A virtual function that obtains the plugin information.
     */
    virtual const String& GetPluginInfo() const = 0;

    /*
     * A virtual function that calls and executes plugins.
     */
    virtual bool Execute(const Param& paramIn, Param& paramOut) = 0;

    /*
     * Performs update.
     */
    virtual void Update(f32 dt);

    /*
     * Performs rendering.
     */
    virtual void Render();

    /*
     * Returns true if a plugin is activated.
     */
    bool IsPluginActive() const;

private:
    virtual bool Initialize() = 0;
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