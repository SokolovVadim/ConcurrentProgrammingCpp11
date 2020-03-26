#include <iostream>
#include <thread>

void pretty_function(){
	// shared resourse is stdout
	std::cout << "You are pseudorandom\n";
}


int main()
{
	std::thread thread1(pretty_function); // t1 starts running
	// thread1.join(); // main thread waits for t1 to finish
	// thread1.detach(); // t1 is freely on its own -- daemon process
	// thread1.join(); // crash after detach -- once detached == forever detached!
	if(thread1.joinable())
		thread1.join();

	return 0;
}