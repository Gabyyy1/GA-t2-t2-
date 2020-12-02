#include <iostream>
#include "Functions.h"
#include "Genetic_Alg.h"
double pi = 3.1415;
using namespace std;
struct data {
	double lower, upper, precision;
}sphere, schwefel, rastrigin, michalewicz;

void initalizaton() {
	michalewicz.upper = pi;
	michalewicz.lower = 0;
	michalewicz.precision = 0.001;

	rastrigin.upper = 5.12;
	rastrigin.lower = -5.12;
	rastrigin.precision = 0.001;

	sphere.upper = 5.12;
	sphere.lower = -5.12;
	sphere.precision = 0.001;

	schwefel.upper = 500;
	schwefel.lower = -500;
	schwefel.precision = 0.1;
}
int main()
{
	//bool sol[1001];
	//grayGen(3, sol);
	/*for (int i = 0; i < 9; i++)
	{
		//cout << sol[i];
		if ((i + 1) % 3 == 0)
			cout << endl;
	}*/
	initalizaton();
	for(int i=0;i<5;i++)
	Genetic(Michalewicz, 30, michalewicz.lower, michalewicz.upper);
	return 0;
}