# Thread management
Running threads in limited scope  
## Thread management

- Thread management using wrapper

```
class Functor
{
public:
	void operator()(std::string & msg){
		std::cout << "t1 says: " << msg << std::endl;
		msg = "t1 washed up its hands";
	}
};
```
`std::thread thread_1(Functor())`
- Thread management using RAII  

## Passing parameter  
`std::thread thread_1((Functor2()), std::ref(msg));`  
std::thread does not allow copying  
therefore move semantics is suitable there  
`std::thread thread_2 = std::move(thread_1);`
