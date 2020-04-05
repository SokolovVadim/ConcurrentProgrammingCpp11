# Callable Objects

## Different callable objects

```
Functor functor;
	std::thread t1(functor, 6);
	std::async(std::launch::async, functor, 6);
	std::bind(functor, 6);
	std::call_once(std::once_flag, functor, 6);
```

## std::thread example

```
	Functor functor;
	std::thread t1((functor), 6); // copy of functor
	std::thread t2(std::ref(functor), 6); // functor() in a thread
	std::thread t3((Functor()), 6); // temp Functor
	std::thread t4([](int x){return x * x;}, 6);
	std::thread t5(foo, 7);

	std::thread t6(&Functor::func, functor, 8, 'w'); // copy of functor.func(8, 'w')
	std::thread t7(&Functor::func, &functor, 8, 'w'); // functor.func(8, 'w')
	std::thread t8(std::move(functor), 6); // functor is no longer usable in parent thread

	// join ... 
```

