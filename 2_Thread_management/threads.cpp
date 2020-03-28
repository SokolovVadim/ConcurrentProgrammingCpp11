#include <thread>
#include <iostream>
#include <string>


void worker(){
	std::cout << "It's corona time" << std::endl;
}


// Lambda
class Functor1
{
public:
	void operator()(){
		for(int i(0); i > -100; i--)
			std::cout << "job from t1 " << i << std::endl;
	}
};

class Functor2
{
public:
	void operator()(std::string & msg){
		std::cout << "t1 says: " << msg << std::endl;
		msg = "t1 washed up its hands";
	}
};

int main()
{
	// Functor fct;
	// std::thread thread_1(fct);
	
	// std::thread thread_1(Functor()); This line isn't compilable
	// std::thread thread_1((Functor1())); it works

	std::string msg = "Watch out and wash hands";

	std::cout << std::this_thread::get_id() << std::endl;

	std::thread thread_1((Functor2()), std::ref(msg));
	std::cout << thread_1.get_id() << std::endl;

	std::thread thread_2 = std::move(thread_1);

	thread_2.join();

	std::cout << "job from main: " << msg << std::endl;

	// std::thread thread_1(worker); // t1 starts running
	// using RAII
	// Wrapper
	/*try{
		std::cout << "job from main: " << std::endl;
	} catch(...){
		thread_1.join();
		throw;
	}*/
	return 0;
}
