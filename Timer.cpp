#include "Timer.h"
#include <iostream>

Timer::Timer()
{
	start = std::chrono::system_clock::now();
}

Timer::~Timer()
{
	stop = std::chrono::system_clock::now();
	long long total = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
	std::cout << " time: " << total << " microseconds\n";
}

