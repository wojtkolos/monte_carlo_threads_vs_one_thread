#include "MonteCarlo.h"

MonteCarlo::MonteCarlo(const counter_h _throws, double min, double max) 
	: throws(_throws), 
	gen(std::random_device{}()), 
	rand(std::uniform_real_distribution<double>(min, max))
{}



void MonteCarlo::seed(double min, double max)
{
	this->rand( this->gen, param_type(min, max) );
}

bool MonteCarlo::genRand() {
	//this->seed();
	double x = rand(gen);
	double y = rand(gen);
	return (x * x + y * y <= 1)? 1 : 0;
}

void MonteCarlo::setNumberOfHits(const counter_h throws) {
	this->throws = throws;
}

counter_h MonteCarlo::calculate_hits()
{
	counter_h hits = 0;
	for (counter_h i = 0; i < throws; ++i)
	{
		if (genRand()) ++hits;
	}
	return hits;
}

counter_h MonteCarlo::calculate_hits(unsigned long long throws_per_thread)
{
	counter_h hits = 0;
	for (counter_h i = 0; i < throws_per_thread; ++i)
	{
		if (genRand()) ++hits;
	}
	return hits;
}

counter_h MonteCarlo::calculate_hits_with_threads() {
	auto hardware_threads_count = std::max(std::thread::hardware_concurrency(), 1u);
	auto throws_per_thread = this->throws / hardware_threads_count;

	std::vector<std::thread> threads;
	std::vector<counter_h> hits(hardware_threads_count);

	for (unsigned int i = 0; i < hardware_threads_count; ++i)
	{
		threads.emplace_back([&hits, i, throws_per_thread, this] { hits[i] = this->calculate_hits(throws_per_thread); });
	}


	for (auto& thd : threads)
		thd.join();

	double pi = 4. * std::accumulate(hits.begin(), hits.end(), 0.0) / this->throws;
	return 0;
}

double MonteCarlo::calculatePI()
{
	return 4. * calculate_hits() / this->throws;
}

double MonteCarlo::calculatePI_with_threads()
{
	return 4. * calculate_hits() / this->throws;
}
