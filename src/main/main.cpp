#include "timer/timer.h"

using namespace std;

int main() {
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
	return 0;
}