#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>

class Functor
{
public:
	void func(int x, char c){}
	long g(double x){ return 0; }
	int operator()(int N){ return 0; }
};

void foo(int x){}

int main()
{
	Functor functor;
	std::thread t1((functor), 6); // copy of functor
	std::thread t2(std::ref(functor), 6); // functor() in a thread
	std::thread t3((Functor()), 6); // temp Functor
	std::thread t4([](int x){return x * x;}, 6);
	std::thread t5(foo, 7);

	std::thread t6(&Functor::func, functor, 8, 'w'); // copy of functor.func(8, 'w')
	std::thread t7(&Functor::func, &functor, 8, 'w'); // functor.func(8, 'w')
	std::thread t8(std::move(functor), 6); // functor is no longer usable in parent thread
	
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();
	t8.join();
	return 0;
}
