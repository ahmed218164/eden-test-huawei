/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: Timer manager for schedule tasks.
 */

#ifndef TIMER_MANAGER_H
#define TIMER_MANAGER_H

#include "Core/Singleton.h"

NS_CG_BEGIN

class Timer;

using CallbackFunc = std::function<void()>;

struct ScheduleInfo {
    CallbackFunc callback;
    void* target;
    f32 delaySeconds;
    u32 repeatTimes;
    f32 repeatIntervalSeconds;
    String key;

    ScheduleInfo(const CallbackFunc& inCallback, void* inTarget, f32 inDelaySeconds, u32 inRepeatTimes,
        f32 inRepeatIntervalSeconds, const String& inKey)
        : callback(inCallback),
          target(inTarget),
          delaySeconds(inDelaySeconds),
          repeatTimes(inRepeatTimes),
          repeatIntervalSeconds(inRepeatIntervalSeconds),
          key(inKey)
    {
    }
};

class CGKIT_EXPORT TimerManager : public Singleton<TimerManager> {
    friend class Singleton<TimerManager>;
    friend class BaseApplication;

public:
    /*
     * Schedule a function on target, which will be executed after delaySeconds.
     * if repeatTimes is not 0, it will be repeated repeatTimes with repeatIntervalSeconds.
     * if repeatTimes is 0, it will be executed forever.
     * ScheduleInfo scheduleInfo(std::bind(&BaseApplication::TestCaller, this, 12, 14.f),
       this, 3.f, 3, 1.f, "TestCaller");
     * gTimerManager.Schedule(scheduleInfo);
     */
    void Schedule(const ScheduleInfo& scheduleInfo);
    void Unschedule(void* target, const String& key);

private:
    TimerManager();
    ~TimerManager();

    void Initialize();
    void Uninitialize();
    void Pause();
    void Resume();
    void Update(f32 deltaTimeSeconds);
    bool IsValid(const ScheduleInfo& scheduleInfo);

    struct TimerInfo {
        std::vector<Timer*> timers;
        void* target;
    };

    std::unordered_map<void*, TimerInfo*> m_timerInfos;
    bool m_runing;
};

#define gTimerManager TimerManager::GetSingleton()

NS_CG_END

#endif
