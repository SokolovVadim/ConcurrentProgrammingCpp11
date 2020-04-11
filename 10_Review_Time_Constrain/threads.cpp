#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <chrono>

int factorial(int N)
{
	int res(1);
	for(int i(N); i > 1; --i)
		res *= i;
	std::cout << "Result is: " << res << std::endl;
	return res;
}

int main()
{
	// thread
	std::thread t1(factorial, 6);
	std::this_thread::sleep_for(std::chrono::milliseconds(3));
	std::chrono::steady_clock::time_point tp = std::chrono::steady_clock::now() + std::chrono::milliseconds(4);
	std::this_thread::sleep_until(tp);
	t1.join();
	// mutex
	std::mutex mu;
	std::lock_guard<std::mutex> locker(mu);
	std::unique_lock<std::mutex> ulocker(mu);
	ulocker.try_lock();
	ulocker.try_lock_for(std::chrono::nanosecons(500));
	ulocker.try_lock_until(tp);

	// condition variable
	std::condition_variable cond;
	cond.wait_for(std::chrono::microseconds(2));
	cond.wait_until(ulocker, tp);

	// future and promise
	std::chrono::steady_clock::time_point tp = std::chrono::steady_clock::now() + std::chrono::milliseconds(4);
	std::promise<int> p;
	std::future<int> f = p.get_future();
	f.get();
	f.wait();
	f.wait_for(std::chrono::milliseconds(2));
	f.wait_until(tp);

	// async()
	std::future<int> fu = std::async(factorial, 6);

	// packaged task
	std::packaged_task<int(int)> t(factorial);
	std::future<int> fu2 = t.get_future();
	t(6);
	
	return 0;
}
