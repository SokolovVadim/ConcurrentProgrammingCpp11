#include <thread>
#include <iostream>
#include <string>
#include <mutex>


std::mutex mtx;

void shared_print(std::string msg, int id)
{
	mtx.lock();
	std::cout << msg << id << std::endl;
	mtx.unlock();
}

void worker(){
	for(int i(0); i > -100; i--)
		shared_print(std::string("job from t1 "), i);
}

int main()
{
	std::thread t1(worker);
	for(int i(0); i < 100; ++i)
		shared_print(std::string("From main: "), i);
	t1.join();
	return 0;
}
