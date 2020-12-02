#include <random>
#include <chrono>
#include <math.h>

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator(seed);

bool rand_bit()
{
	std::uniform_real_distribution<double> distribution(0, 1);
	return round(distribution(generator));
}

double rand_number_subunitary()
{
	std::uniform_real_distribution<double> distribution(0, 1);
	return distribution(generator);
}
double rand_integer_in_interval(float a,float b)
{
	std::uniform_real_distribution<double> distribution(a, b);
	return distribution(generator);
}