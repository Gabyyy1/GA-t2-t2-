#include "Random.h"
#include <math.h>
void generate_number(bool sol[])
{
	for (int i = 0; i <= 31; i++)
	{
		sol[i] = rand_bit();
	}
}

double bittodouble(bool sol[], int length, double upper, double lower)
{
	double res = lower, val_bit = (upper - lower) / pow(2, length);
	for (int i = 0; i < length; i++)
	{
		if (sol[i])
		{
			res += val_bit;
		}
		val_bit *= 2;
	}
	return res;
}