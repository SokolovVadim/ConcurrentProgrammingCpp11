# Deadlock

## Typical deadlock situation

```
class LogFile{
void shared_print(std::string msg, int value)
	{
		std::lock_guard<std::mutex> guard(mutex_);
		std::lock_guard<std::mutex> guard2(mutex2_);
		std::cout << msg << ": " << value << std::endl;
	}
	void shared_print2(std::string msg, int value)
	{
		std::lock_guard<std::mutex> guard2(mutex2_);
		std::lock_guard<std::mutex> guard(mutex_);
		std::cout << msg << ": " << value << std::endl;
	}
private:
	std::mutex     mutex_;
	std::mutex 	   mutex2_;
	std::ofstream  fout_;
};
```

## Simple solution:

Put locking the mutexes in the same order

```
void shared_print(std::string msg, int value)
	{
		std::lock_guard<std::mutex> guard(mutex_);
		std::lock_guard<std::mutex> guard2(mutex2_);
		std::cout << msg << ": " << value << std::endl;
	}
	void shared_print2(std::string msg, int value)
	{
		std::lock_guard<std::mutex> guard(mutex_);
		std::lock_guard<std::mutex> guard2(mutex2_);
		std::cout << msg << ": " << value << std::endl;
	}
```

## STL solution

```
	void shared_print(std::string msg, int value)
	{
		std::lock(mutex_, mutex2_);
		std::lock_guard<std::mutex> guard(mutex_, std::adopt_lock);
		std::lock_guard<std::mutex> guard2(mutex2_, std::adopt_lock);
		std::cout << msg << ": " << value << std::endl;
	}
```

## Avoiding deadlock

1. Prefer locking single mutex

2. Avoid locking a mutex and then calling a user provided function

3. Use std:lock() to lock more than one mutex

4. Lock the mutex in same order for all threads

## Locking Granularity  

- Fine-grained lock: protects small amount of data

- Coarse-grained lock: protects big amount of data