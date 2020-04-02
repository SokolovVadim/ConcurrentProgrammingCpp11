# Conditional variables

## producer-consumer
```
std::deque<int> q;
std::mutex mu;

void function1()
{
	int count(10);
	while(count > 0)
	{
		std::unique_lock<std::mutex> locker(mu);
		q.push_front(count);
		locker.unlock();
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
		if(!q.empty())
		{
			data = q.back();
			q.pop_back();
			locker.unlock();
			std::cout << "t2 got a value from t1: " << data << std::endl;
		}
		else
			locker.unlock();
	}
}
```
## BUT!

There is a busy wait state on thread2

Simple solution: additional sleep to avoid cycling

```
	locker.unlock();
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
```

## Conditional variable

```
		locker.unlock();
		cond.notidy_one(); // Notify one waiting thread, if there is one
		std::this_thread::sleep_for(std::chrono::seconds(1));
```

```
		std::unique_lock<std::mutex> locker(mu);
		cond.wait(locker);
		data = q.back();
		q.pop_back();
		locker.unlock();
		std::cout << "t2 got a value from t1: " << data << std::endl;
```

Thread 2 can wake up as itself!

```
		cond.wait(locker, [](){return !q.empty();}); // spurious wake
```
