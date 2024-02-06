#include <time.h>
#include <sys/epoll.h>
#include <sys/timerfd.h>
#include <unistd.h>

#include <chrono>
#include <set>
#include <memory>
#include <iostream>
#include <functional>

// 节点基类
struct TimerNodeBass
{
    time_t expire; // 执行时间
    uint64_t id;   // 唯一id
};

// 节点
struct TimerNode : TimerNodeBass
{
    // 执行函数
    using Callback = std::function<void(const TimerNode &node)>;
    TimerNode::Callback func;
    TimerNode(time_t expire, uint64_t id, TimerNode::Callback func);
};

// 重载小于
bool operator<(const TimerNodeBass &ln, const TimerNodeBass &rn);

class Timer
{
private:
    static uint64_t gid;                       // id
    static inline uint64_t GenID();            // 获取id
    std::set<TimerNode, std::less<>> timeouts; // 存储Node
public:
    static inline time_t GetTick();                             // 获取毫秒
    TimerNodeBass AddTimer(int time, TimerNode::Callback func); // 添加任务
    bool DelTimer(TimerNodeBass &node);                         // 删除任务
    bool CheckTimer();                                          // 更新计时器
    time_t TimeToSleep();                                       // 返回最近任务触发时间
};
