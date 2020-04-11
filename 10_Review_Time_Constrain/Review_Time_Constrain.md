# Review and Time Constrain

## Review

```
int factorial(int N){...}

int main()
{
	// thread
	std::thread t1(factorial, 6);
	t1.join();
	
	// mutex
	std::mutex mu;
	std::lock_guard<mutex> locker(mu);
	std::unique_lock<mutex> ulocker(mu);

	// condition variable
	std::condition_variable cond;

	// future and promise
	std::promise<int> p;
	std::future<int> f = p.get_future();

	// async()
	std::future<int> fu = async(factorial, 6);

	// packaged task
	std::packaged_task<int(int)> t(factorial);
	std::future<int> fu2 = t.get_future();
	t(6);
	
	return 0;
}
```

## Chrono

#### Thread

```
	// thread
	std::thread t1(factorial, 6);
	std::this_thread::sleep_for(std::chrono::milliseconds(3));
	std::chrono::steady_clock::time_point tp = std::chrono::steady_clock::now() + std::chrono::milliseconds(4);
	std::this_thread::sleep_until(tp);
	t1.join();
```

#### Mutex 

```
std::mutex mu;
	std::lock_guard<std::mutex> locker(mu);
	std::unique_lock<std::mutex> ulocker(mu);
	ulocker.try_lock();
	ulocker.try_lock_for(std::chrono::nanosecons(500));
	ulocker.try_lock_until(tp);
```

#### Conditional variable

```
	// condition variable
	std::condition_variable cond;
	cond.wait_for(std::chrono::microseconds(2));
	cond.wait_until(ulocker, tp);
```

#### Future

```
	// future and promise
	std::promise<int> p;
	std::future<int> f = p.get_future();
	f.get();
	f.wait();
	f.wait_for(std::chrono::milliseconds(2));
	f.wait_until(tp);
```
