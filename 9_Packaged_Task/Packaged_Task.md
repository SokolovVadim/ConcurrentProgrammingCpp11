# Packaged task

```
	std::packaged_task<int(int)> task(factorial);
	task(6); // in a different context
	auto x = task.get_future();
```

```
	std::thread t1(factorial, 6);
	std::packaged+task<int()> task(std::bind(factorial, 6));
	task();
```

```
	auto t = std::bind(factorial, 6);
	t();
```
## Main advantage

The main advantage of a packaged tassk is that  
it can link a callable object to a future

```

std::deque<std::packaged_task<int()> > task_q;
std::mutex mu;
std::condition_variable cond;

void thread_1(){
	std::packaged_task<int()> t;
	{
		std::lock_guard<std::mutex> locker(mu);
		t = std::move(task_q.front());
		task_q.pop_front();
	}
	
	t();
}


int main()
{
	std::thread t1(thread_1);
	std::packaged_task<int()> task(std::bind(factorial, 6));
	std::future<int> fu = task.get_future();
	{
		std::lock_guard<std::mutex> locker(mu);
		task_q.push_back(std::move(task));
	}
	
	t1.join();
	
	return 0;
}
```

```
void thread_1(){
	std::packaged_task<int()> t;
	{
		std::unique_lock<std::mutex> locker(mu);
		cond.wait(locker, [](){return !task_q.empty();});
		t = std::move(task_q.front());
		task_q.pop_front();
	}
	t();
}


int main()
{
	std::thread t1(thread_1);
	std::packaged_task<int()> task(std::bind(factorial, 6));
	std::future<int> fu = task.get_future();
	{
		std::lock_guard<std::mutex> locker(mu);
		task_q.push_back(std::move(task));
	}
	cond.notify_one();

	std::cout << fu.get() << std::endl;
	
	t1.join();
	
	return 0;
}

```


## Summary

#### 3 ways to get future:

 - promise::get_future()
 - packaged_task::get_future()
 - async() returns a future