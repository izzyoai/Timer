# 实现定时器

## 源码来自于网上教程

## 简单食用例子
```shell
#linux
cd Timer
mkdir build
cd build
cmake ..
make
../bin/app

#windows MinGW
cd Timer
mkdir build
cmake .. -G "MinGW Makefiles"
mingw32-make
```

### 输出
```
id:3 expire:41507466 i:2284302793
id:2 expire:41508466 i:4566152309
id:1 expire:41509466 i:6839294488
id:0 expire:41511466 i:11428686297
```
## 1.通过cmake编译(VERSION 3.15)
```cmake
cmake_minimum_required(VERSION 3.15)                    #cmake版本
project(TIMER)                                          #名称
include_directories(${PROJECT_SOURCE_DIR}/include)      #包含头文件
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)   #输出目录
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC)     #源文件目录
#linux g++ 编译需要以下指令 -lpthread
set(CMAKE_CXX_FLAGS -lpthread)
add_executable(app ${SRC})                              #可执行文件名称
```
## 2.timer.h
```c++
#ifndef TIMER_H
#define TIMER_H

#include<iostream>
#include<set>
#include<functional>
#include<thread>
#include<atomic>
#include<chrono>
#include<mutex>
#include<condition_variable>

/*Debug*/
//#define _DEBUG_

/*Timer Task Bass Class*/
struct TimerNodeBass
{
	uint64_t id;
	time_t expire;
};

/*Timer Task Bass Class*/
struct TimerNode : public TimerNodeBass
{
	using Callback = std::function<void(const TimerNode& node)>;
	Callback func;
	TimerNode(uint64_t id, time_t expire, TimerNode::Callback func);
};

/*Overload less than*/
bool operator<(const TimerNodeBass& ln, const TimerNodeBass rn);

/*Timer Class*/
class Timer
{
private:
	std::thread m_worker;
	std::set<TimerNode, std::less<>> m_task;
	std::atomic<bool> m_stop;
	std::mutex m_task_mutex;
	std::condition_variable m_condition;
	static uint64_t gid;
	static inline uint64_t GenID();
	void run();
public:
	Timer();
	~Timer();
	/*Return Tick*/
	static inline time_t GetTick();
	TimerNodeBass AddTimer(int time,TimerNode::Callback func);
	bool DelTimer(TimerNodeBass& node);
	/*Return Recent Task Time*/
	time_t TimeToSellp();
};

#endif




```
## 3.调用方法
```c++
	unique_ptr<Timer> timer = make_unique<Timer>();
	uint64_t i = 0;
	timer->AddTimer(5000, [&](const TimerNode& node) {
		cout << "id:" << node.id << " expire:" << node.expire << " i:" << i << endl;
		});
	timer->AddTimer(3000, [&](const TimerNode& node) {
		cout << "id:" << node.id << " expire:" << node.expire << " i:" << i << endl;
		});	
	timer->AddTimer(2000, [&](const TimerNode& node) {
		cout << "id:" << node.id << " expire:" << node.expire << " i:" << i << endl;
		});
	timer->AddTimer(1000, [&](const TimerNode& node) {
		cout << "id:" << node.id << " expire:" << node.expire << " i:" << i << endl;
		});

	while (true) {
		i++;
	}
```
