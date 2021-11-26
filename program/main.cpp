#include "MonteCarlo.h"
#include <chrono>




int main(int argc, char* argv[])
{
	auto y = []() { std::cout << "---------------------------------------------------\n"; };
	counter_h throws = std::stoi(argv[1]);
	MonteCarlo monte(throws);

	for (int i = 0; i < 10; ++i) {
		auto start = std::chrono::high_resolution_clock::now();
		double pi = monte.calculatePI();
		auto finish = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double, std::milli> elapsed = finish - start;
		std::cout << "Pi: " << pi << " for n=" << throws << " time " << elapsed.count() << std::endl;


		start = std::chrono::high_resolution_clock::now();
		pi = monte.calculatePI_with_threads();
		finish = std::chrono::high_resolution_clock::now();

		elapsed = finish - start;
		std::cout << "Pi: " << pi << " for n=" << throws << " time " << elapsed.count() << std::endl;
		throws *= 10;

		y();
	}
	/*
	auto x = [](auto a, auto b) { return a * b; };
	auto y = [](auto a, auto b) { std::cout <<  a * b; };

	std::cout << x(2, 3) << std::endl;
	y(2, 3);
	*/

	return 0;
}

 