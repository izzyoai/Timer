#include "timer.h"

bool operator<(const TimerNodeBass &ln, const TimerNodeBass &rn)
{
    if (ln.expire < rn.expire)
    {
        return true;
    }
    else if (ln.expire > rn.expire)
    {
        return false;
    }
    else
    {
        return ln.id < rn.id;
    }
}

TimerNode::TimerNode(time_t expire, uint64_t id, TimerNode::Callback func) : func(std::move(func))
{
    this->expire = expire;
    this->id = id;
}

uint64_t Timer::gid = 0;

uint64_t Timer::GenID()
{
    return gid++;
}

inline time_t Timer::GetTick()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}

TimerNodeBass Timer::AddTimer(int time, TimerNode::Callback func)
{
    time_t expire = GetTick() + time;
    auto pairs = timeouts.emplace(expire, GenID(), std::move(func));
    return static_cast<TimerNodeBass>(*pairs.first);
}

bool Timer::DelTimer(TimerNodeBass &node)
{
    auto iter = timeouts.find(node);
    if (iter != timeouts.end())
    {
        timeouts.erase(iter);
        return true;
    }
    return false;
}

bool Timer::CheckTimer()
{
    auto iter = timeouts.begin();
    if (iter != timeouts.end() && iter->expire <= GetTick())
    {
        // 触发定时器任务
        iter->func(*iter);
        // 删除任务
        timeouts.erase(iter);
        return true;
    }
    return false;
}

time_t Timer::TimeToSleep()
{
    auto iter = timeouts.cbegin();
    if (iter == timeouts.cend())
    {
        return -1;
    }
    time_t diss = iter->expire - GetTick();
    return diss > 0 ? diss : 0;
}
