# Linux实现定时器

## 源码来自于网上教程，还有许多不太清楚的地方

## 简单食用例子
```shell
cd Timer
mkdir build
cd build
cmake ..
make
../bin/app
```

### 输出
```
1000ms -->i:1 || node.expire -->20858677 || node.id -->1
1500ms -->i:2 || node.expire -->20859178 || node.id -->2
2000ms -->i:2 || node.expire -->20859677 || node.id -->0
1500ms -->i:3 || node.expire -->20860179 || node.id -->3
1500ms -->i:4 || node.expire -->20861181 || node.id -->4
1500ms -->i:5 || node.expire -->20862182 || node.id -->5
1500ms -->i:6 || node.expire -->20863184 || node.id -->6
1500ms -->i:7 || node.expire -->20864186 || node.id -->7
1500ms -->i:8 || node.expire -->20865187 || node.id -->8
1500ms -->i:9 || node.expire -->20866189 || node.id -->9
```
## 1.通过cmake编译(VERSION 3.15)
```cmake
cmake_minimum_required(VERSION 3.15)                    #cmake版本
project(TIMER)                                          #名称
include_directories(${PROJECT_SOURCE_DIR}/include)      #包含头文件
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)   #输出目录
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC)     #源文件目录
add_executable(app ${SRC})                              #可执行文件名称
```
## 2.timer.h
```c++
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
//定时器类
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
```
## 3.调用方法
```c++
    /*一堆不太清楚的设置*/
    int epfd = epoll_create(1);
    int timerfd = timerfd_create(CLOCK_MONOTONIC, 0);
    struct epoll_event ev = {.events = EPOLLIN | EPOLLET};
    epoll_ctl(epfd, EPOLL_CTL_ADD, timerfd, &ev);
    /*智能指针创建定时器*/
    unique_ptr<Timer> timer = make_unique<Timer>();
    /*添加定时任务*/
    int i;
    timer->AddTimer(2000, [&](const TimerNode &node)
                { cout << "2000ms -->i:" << i
                        << " || node.expire -->" << node.expire << " || node.id -->" << node.id << endl; });
    /*构建数组*/
    struct epoll_event evs[64] = {0};
    while (1)
    {
        /*循环等待结果*/
        int n = epoll_wait(epfd, evs, 64, 1);
        /*更新计时器*/
        while (timer->CheckTimer());
        i++;
        timer->AddTimer(1500, [&](const TimerNode &node)
                        { cout << "1500ms -->i:" << i
                               << " || node.expire -->" << node.expire << " || node.id -->" << node.id << endl; });
        sleep(1);
    }
```
