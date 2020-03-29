# Unique lock and Lazy initialization

## Unique lock

```
class LogFile{
	// ...
void shared_print(std::string msg, int value)
	{
		std::unique_lock<std::mutex> guard(mutex_, std::defer_lock);

		// do smth that doesn't require fout_

		guard.lock();
		fout_ << msg << ": " << value << std::endl;
		guard.unlock();

		// do smth that doesn't require fout_

		guard.lock();

		std::unique_lock<std::mutex> guard2 = std::move(guard); // it's only allowed to move lock neither copy
	}
private:
	std::mutex    mutex_;
	std::ofstream fout_;
};
```

## Lazy initialization  

```
if(!fout_.is_open())
		{
			std::unique_lock<std::mutex> guard2(mutex_open_);
			fout_.open("log.txt");
		}
```

But it isn't thread safe yet  
There is std solution: `std::once_flag`  

```
class LogFile{
	void shared_print(std::string msg, int value)
	{
		// file will be opened only once by one thread
		std::call_once(flag_, [&](){ fout_.open("log.txt"); });

		std::unique_lock<std::mutex> guard(mutex_, std::defer_lock);
		
		mutex_.lock();
		fout_ << msg << ": " << value << std::endl;
		mutex_.unlock();
	}

private:
	std::once_flag flag_;
	std::mutex     mutex_;
	std::ofstream  fout_;
};
```


