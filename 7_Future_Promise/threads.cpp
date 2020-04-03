#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <future>


int factorial(std::shared_future<int> f)
{
	int res(1);
	int N = f.get(); // broken promise
	for(int i(N); i > 1; i--)
		res *= i;
	std::cout << "Result is: " << res << std::endl;
	return res;
}

int main()
{
	std::promise<int> p;
	std::future<int> f = p.get_future();
	std::shared_future<int> sf = f.share();
	
	std::future<int> fu = std::async(std::launch::async, factorial, sf);
	std::future<int> fu1 = std::async(std::launch::async, factorial, sf);
	std::future<int> fu2 = std::async(std::launch::async, factorial, sf);

	// 10 threads

	p.set_value(4);


	return 0;
}
