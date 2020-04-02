#include <thread>
#include <iostream>
#include <string>
#include <mutex>
#include <fstream>
#include <deque>

std::deque<int> q;

void function1()
{

}

void function2()
{

}

int main()
{
	std::thread t1(function1);
	std::thread t2(function2);
	t1.join();
	t2.join();
	return 0;
}
