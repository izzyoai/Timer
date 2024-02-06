#include "timer.h"
using namespace std;

int main()
{
    int epfd = epoll_create(1);
    int timerfd = timerfd_create(CLOCK_MONOTONIC, 0);
    struct epoll_event ev = {.events = EPOLLIN | EPOLLET};
    epoll_ctl(epfd, EPOLL_CTL_ADD, timerfd, &ev);

    unique_ptr<Timer> timer = make_unique<Timer>();

    int i = 0;

    timer->AddTimer(2000, [&](const TimerNode &node)
                    { cout << "2000ms -->i:" << i
                           << " || node.expire -->" << node.expire << " || node.id -->" << node.id << endl; });

    timer->AddTimer(1000, [&](const TimerNode &node)
                    { cout << "1000ms -->i:" << i
                           << " || node.expire -->" << node.expire << " || node.id -->" << node.id << endl; });

    struct epoll_event evs[64] = {0};
    while (1)
    {
        int n = epoll_wait(epfd, evs, 64, 1);
        while (timer->CheckTimer());
        i++;
        timer->AddTimer(1500, [&](const TimerNode &node)
                        { cout << "1500ms -->i:" << i
                               << " || node.expire -->" << node.expire << " || node.id -->" << node.id << endl; });
        sleep(1);
    }
    return 0;
}