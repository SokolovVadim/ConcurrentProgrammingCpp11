#include <thread>
#include <iostream>
#include <string>
#include <mutex>
#include <fstream>
#include <deque>
#include <condition_variable>

std::deque<int> q;
std::mutex mu;
std::condition_variable cond;

void function1()
{
	int count(10);
	while(count > 0)
	{
		std::unique_lock<std::mutex> locker(mu);
		q.push_front(count);
		locker.unlock();
		// cond.notify_one(); // Notify one waiting thread, if there is one
		cond.notify_all();
		std::this_thread::sleep_for(std::chrono::seconds(1));
		count--;
	}
}

void function2()
{
	int data = 0;
	while(data != 1)
	{
		std::unique_lock<std::mutex> locker(mu);
		cond.wait(locker, [](){return !q.empty();}); // spurious wake
		data = q.back();
		q.pop_back();
		locker.unlock();
		std::cout << "t2 got a value from t1: " << data << std::endl;
	}
}

int main()
{
	std::thread t1(function1);
	std::thread t2(function2);
	t1.join();
	t2.join();
	return 0;
}
