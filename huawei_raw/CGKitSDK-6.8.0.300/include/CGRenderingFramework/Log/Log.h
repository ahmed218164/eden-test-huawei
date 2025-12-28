/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: Log utils.
 */

#ifndef LOG_H
#define LOG_H

#include "Log/LogCommon.h"

NS_CG_BEGIN

#ifdef CGKIT_LOG
#define LOGVERBOSE(...)                                                                     \
    CGKit::Log::WriteLog(CGKit::LogType::LOG_VERBOSE, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__)
#define LOGDEBUG(...)                                                                       \
    CGKit::Log::WriteLog(CGKit::LogType::LOG_DEBUG, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__)
#define LOGINFO(...)                                                                        \
    CGKit::Log::WriteLog(CGKit::LogType::LOG_INFO, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__)
#define LOGWARNING(...)                                                                     \
    CGKit::Log::WriteLog(CGKit::LogType::LOG_WARNING, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__)
#define LOGERROR(...)                                                                       \
    CGKit::Log::WriteLog(CGKit::LogType::LOG_ERROR, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_ALLOC_NULL(...) {                                                             \
        CGKit::Log::WriteLog(CGKit::LogType::LOG_ERROR, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__); \
    }
#define LOG_ALLOC_ERROR(...) {                                                            \
        CGKit::Log::WriteLog(CGKit::LogType::LOG_ERROR, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__); \
    }
#else
#define LOGVERBOSE(...)
#define LOGDEBUG(...)
#define LOGINFO(...)
#define LOGWARNING(...)
#define LOGERROR(...)
#define LOG_ALLOC_ERROR(...)
#define LOG_ALLOC_NULL(...)
#endif

struct LogCmd;
class ILogger;

class CGKIT_EXPORT Log {
public:
    /*
     * A constructor.
     */
    Log() = default;
    /*
     * A destructor.
     */
    ~Log() = default;

    /*
     * Initializes the logger, including registering and enabling the logger.
     */
    static void Initialize();

    /*
     * Deinitializes the logger and clears the log mapping table.
     */
    static void Uninitialize();

    /*
     * static void SetLogLevel(LogType logType);
     */
    static void SetLogLevel(LogType logType);

    /*
     * Writes log to the log buffer.
     */
    static void WriteLog(LogType type, String func, String file, int line, const char* fmt, ...);

    /*
     * Adds a timestamp to text the character array type and writes the text to the log buffer.
     */
    static void Write(LogType type, const char* text);

private:
    /*
     * Register logger.
     */
    static void RegisterLogger(LogPathType logPathType, ILogger* logger);

    /*
     * Unregister Logger.
     */
    static void UnregisterLogger(LogPathType logPathType);

    /*
     * Enable logger.
     */
    static void EnableLogger(LogPathType logPathType, bool bEnable);

    /*
     * Get timestamp.
     */
    static String GetTimestamp();

    /*
     * Flush the log to buffer.
     */
    static void Flush();

    /*
     * Get if the log level enable or not.
     */
    static bool IsLogLevelEnabled(LogType logType);

    /*
     * Get file name.
     */
    static char* GetFileName(const char* file);

private:
    static std::map<LogPathType, ILogger*> m_loggerMap;
    static std::vector<LogCmd> m_logBuffer;
    static std::mutex m_mutex;
    static bool m_initialized;
};

NS_CG_END

#endif
