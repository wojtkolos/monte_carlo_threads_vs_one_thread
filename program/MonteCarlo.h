#pragma once
#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <random>
#include <thread>
#include <numeric>


using counter_h = unsigned long long int;
using Generator = std::mt19937;
typedef typename std::uniform_real_distribution<double>::param_type param_type;


class MonteCarlo {
public:
	MonteCarlo(const counter_h, double min = -1., double max = 1.);

	void setNumberOfHits(const counter_h);
	double calculatePI();
	double calculatePI_with_threads();
private:
	

	void seed(double min = -1., double max = 1.);
	counter_h calculate_hits();
	counter_h calculate_hits(unsigned long long);

	counter_h calculate_hits_with_threads();
	bool genRand();


	Generator gen;
	std::uniform_real_distribution<double> rand;
	counter_h throws;
};