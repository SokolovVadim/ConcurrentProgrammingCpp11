# Future & Promise

The code to get factorial and print it in another thread is too massive

```
std::mutex mu;
std::condition_variable cond;


void factorial(int N, int & x)
{
	int res(1);
	for(int i(N); i > 1; i--)
		res *= i;
	std::cout << "Result is: " << res << std::endl;
	x = res;
}

int main()
{
	int x;
	std::thread t1(factorial, 4, std::ref(x));

	t1.join();
	return 0;
}
```
## Async()

Solution from std: 

```
int factorial(int N)
{
	int res(1);
	for(int i(N); i > 1; i--)
		res *= i;
	std::cout << "Result is: " << res << std::endl;
	return res;
}

int main()
{
	std::future<int> fu = std::async(factorial, 4);
	int x = fu.get();
	
	return 0;
}
```

## Future & promise

```
int factorial(std::future<int> & f)
{
	int res(1);
	int N = f.get();
	for(int i(N); i > 1; i--)
		res *= i;
	std::cout << "Result is: " << res << std::endl;
	return res;
}

int main()
{
	std::promise<int> p;
	std::future<int> f = p.get_future();
	// std::launch::deferred -- doesn't create another thread
	// std::future<int> fu = std::async(std::launch::async | std::launch::deferred, factorial, 4);
	
	std::future<int> fu = std::async(std::launch::async, factorial, std::ref(f));

	// do smth else
	std::this_thread::sleep_for(std::chrono::seconds(1));
	p.set_value(4);

	int x = fu.get();
	std::cout << "Get from child: " << x << std::endl;
	return 0;
}
```

## Exception on error

```
int factorial(std::future<int> & f)
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
	
	std::future<int> fu = std::async(std::launch::async, factorial, std::ref(f));

	// do smth else
	std::this_thread::sleep_for(std::chrono::seconds(1));
	p.set_exception(std::make_exception_ptr(std::runtime_error("Error is you")));


	return 0;
}
```

## Shared future

```
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
```