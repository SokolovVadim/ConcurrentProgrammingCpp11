# Data Race & Mutex

## Data race  
## Mutex
```
std::mutex mtx;

void shared_print(std::string msg, int id)
{
	mtx.lock();
	std::cout << msg << id << std::endl;
	mtx.unlock();
}
```

## RAII  
```
lass LogFile{
public:
	...
	void shared_print(std::string msg, int value)
	{
		std::lock_guard<std::mutex> guard(mutex_);
		fout_ << msg << ": " << value << std::endl;
	}
private:
	std::mutex    mutex_;
	std::ofstream fout_;
};
```
Never return fout to the outside workspace  

`ofstream& getStream() {return fout;}`

Never pass fout as an argument to user provided functions

```
void processf(void fun(ofstream&)){
	fun(fout); // it can do anything with fout (close, copy etc)
}
```
## Is this thread safe?

```
class stack{
public:
	// void pop(); // - is not thread safe
	int pop(); // it is thread safe
	int top();
private:
	int* data;
	std::mutex _mu;
}

void func(stack & stk){
	int v = stk.pop();
	process(v);
}

```

## Avoiding data race


- Use mutex to syncrhronize data access  

- Never leak a handle of data to outside  

- Design interface appropriately  
