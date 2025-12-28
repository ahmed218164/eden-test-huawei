/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: PluginManager utils.
 */

#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include "IPlugin.h"
#include "Core/Types.h"
#include "Core/Singleton.h"
#include "nlohmann/json.hpp"

NS_CG_BEGIN

class CGKIT_EXPORT PluginManager : public Singleton<PluginManager> {
    friend class Singleton<PluginManager>;

public:
    /*
     * Initialize the plugin manager and all the plugins in the manager.
     */
    void Initialize();

    /*
     * Unloads the plugin manager and all plugins.
     */
    void Uninitialize();

    /*
     * Obtains all plugin types supported by the plugin manager.
     */
    const std::vector<String>& GetPluginList();

    /*
     * Loads a plugin and returns the plugin pointer.
     */
    IPlugin* LoadPlugin(const String& pluginName);

    /*
     * Unloads a plugin.
     */
    void UnloadPlugin(const String& pluginName);

    /*
     * Obtains the plugin directory.
     */
    const String& GetConfigFile() const;

    /*
     * Sets the directory of a plugin.
     */
    void SetConfigFile(const String& configFile);

private:
    PluginManager();
    ~PluginManager();

    void ParseConfig(const String& strFileName);
    void GetPluginListFromFile(const String& filePath);
    void ActivePlugin(IPlugin* plugin);
    void DectivePlugin(IPlugin* plugin);
    IPlugin *InitPlugin(const String& libName);
    bool UninitPlugin(IPlugin* plugin);
    void RegisterPlugin(IPlugin* plugin);
    void UnRegisterPlugin(IPlugin* plugin);
    void SetConfigChanged(bool status);
    bool GetConfigChanged() const;
    void SetInitialized(bool status);
    bool GetInitialized() const;
    bool m_pmInit {false};
    bool m_configChanged {false};
    std::map<String, IPlugin *> m_pluginMap;
    std::map<String, String> m_pluginPathMap;
    std::vector<String> m_pluginNameList;
    static String m_ConfigFile;
};

#define gPluginManager PluginManager::GetSingleton()

NS_CG_END

#endif