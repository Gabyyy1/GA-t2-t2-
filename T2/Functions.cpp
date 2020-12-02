#include <math.h>
#include <algorithm>
#include <vector>
#include <string>
#include "Functions.h"

using namespace std;
double Sphere(double x[], int d)
{
	double res = 0;
	for (int i = 0; i < d; i++)
	{
		res += pow(x[i], 2);
	}
	return res;
}//sphere

double Schwefel(double x[], int d)
{
	double res = 418.9829*d,sum=0, nr;
	for (int i = 0; i < d; i++)
	{
		sum += x[i] * sin(sqrt(abs(x[i])));
	}
	return res-sum;
}

double Rastrigin(double x[], int d)
{
	double res = 10.0 * d,pi=3.1415;

	for (int i = 0; i < d; i++)
	{
		res += (pow(x[i], 2) - 10 * cos(2 * pi * x[i]));
	}
	return res;
}

double Michalewicz(double x[], int d)
{
	double res = 0;
	double nr, pi = 3.1415;
	int m = 10;
	for (int i = 0; i < d; i++)
	{
		nr = i + 1;
		res -= (sin(x[i]) * pow(sin((nr * x[i] * x[i]) / pi), 20));
	}
	return res;
}

double grade(double val,double maxi, double mini)
{
	return (maxi - val) / (maxi - mini);
}

void grayGen(int length,bool sol[])
{
	if (length > 0)
	{
		vector<string> arr;

		arr.push_back("0");
		arr.push_back("1");

		int i, j;
		for (i = 2; i < (1 << length); i = i << 1)
		{
			for (j = i - 1; j >= 0; j--)
				arr.push_back(arr[j]);

			for (j = 0; j < i; j++)
				arr[j] = "0" + arr[j];

			for (j = i; j < 2 * i; j++)
				arr[j] = "1" + arr[j];
		}
		for (i = 0; i < arr.size(); i++)
		{
			if (arr[i] == "0")
				sol[i] = 0;
			else if(arr[i]=="1")
				sol[i] = 1;
		}
	}
}

