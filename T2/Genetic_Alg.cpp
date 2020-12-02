	#include <math.h>
	#include <iostream>
	#include "Bits.h"
	#include "Random.h"
	#include "Functions.h"
	#include <chrono>
	#include <random>
	#include <algorithm> 
	#define MUTATE_CHENCE 0.1
	#define CROSS_NUMBER 10
	using namespace std;

	void generate_population(bool population[][33], int dimensions,int &pop_length)
	{
		pop_length = 0;
		bool vect_bits[33];
		for (int unit = 0; unit < 100; unit++)
		{
			
			for (int i = 0; i < dimensions; i++)
			{
				generate_number(population[pop_length++]);
			}
		}
		
	}

	void population_grade(bool population[][33], double chance[],int dimensions,int pop_length,double lower,double upper, double (*mathFct)(double *, int))
	{
		double vect_dimensions[33], vect_value[101],ok_min=0,mini,maxi,sum_score = 0, score[101];
		int cont_value = 0,i=0;
		for (int unit = 0; unit < pop_length; unit++)
		{
			vect_dimensions[i++]=bittodouble(population[unit], 32, upper, lower);
			if ((unit+1) % dimensions == 0)
			{
				i = 0;
				vect_value[cont_value] = mathFct(vect_dimensions, dimensions);
				if (ok_min == 0)
				{
					mini = vect_value[0];
					maxi = vect_value[0];
					ok_min = 1;
				}
				else
				{
					mini = min(mini, vect_value[cont_value]);
					maxi = max(maxi, vect_value[cont_value]);
				}
				cont_value++;
			}
			
		}
		//cout << mini<<" "<<maxi;
		for (int unit = 0; unit < 100; unit++)
		{
			score[unit] = grade(vect_value[unit], maxi, mini);
			sum_score += score[unit];
		}//imi pun scoruri
		for (int unit = 0; unit < 100; unit++)
		{
			chance[unit] = score[unit] / sum_score;
			if (unit >= 1)chance[unit] += chance[unit - 1];
		}//calculez sansele
	}

	void select(bool population[][33],double chance[],int pop_length,int dimensions)
	{
		static bool new_population[30001][33];
		float wheel_of_fortune;
		int cont_new = 0;
		for (int k = 0; k < 100; k++)
		{
			wheel_of_fortune = rand_number_subunitary();
			for (int unit = 0; unit < 100; unit++)
			{
				if (chance[unit] <= wheel_of_fortune && wheel_of_fortune <= chance[unit + 1])
				{
					for (int j = dimensions * unit; j < dimensions * (unit + 1); j++)
					{
						for (int k = 0; k < 32; k++)
						{
							new_population[cont_new][k] = population[j][k];
						}
						cont_new++;
					}
					
					break;
					//iau cromozomul
				}
			}
		}
		for (int i = 0; i < pop_length; i++)
		{
			for (int j = 0; j < 32; j++)
			{
				population[i][j] = new_population[i][j];
			}
		}
	}

	void mutate(bool population_bits[][33], float mut_chance,int dimensions,int pop_length)
	{
		for (int i = 0; i <pop_length; i++)
		{
			for(int j = 0; j < 31; j++)
			{
				double dice_roll = rand_number_subunitary();
				if (dice_roll < mut_chance)
					population_bits[i][j] = !population_bits[i][j];
			}
		}
	}

	void cross(bool candidat1[],bool candidat2[],int dimensions)
	{
		bool cross_vect[33];
		generate_number(cross_vect);
		for (int i = 0; i < dimensions; i++)
		{
			if (cross_vect[i] == 1)
			{
				swap(candidat1[i], candidat2[i]);
			}
		}
	}

	void crossover(bool population[][33],int dimensions,int pop_length)
	{
		int  dice_roll1, dice_roll2;
		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < dimensions; j++)
			{
				cross(population[i*dimensions+j], population[(i + 1)*dimensions+j], dimensions);
			}
		}
	}

	void Genetic(double (*mathFct)(double *, int), int dimensions, double lower, double upper)
	{
		bool curent_population[30001][33];
		double chance[100];
		int pop_length;

		generate_population(curent_population,dimensions,pop_length);//prima generare
		//cout <<"Generate: done"<<endl;

		population_grade(curent_population,chance,dimensions,pop_length,lower,upper,mathFct);//imi dau scoruri la populatie
		//cout << "pop_grade: done" << endl;
		int generation = 1;
	
		while (generation <= 1000)
		{

			//cout <<"generation:" <<generation<<endl;
			select(curent_population,chance,pop_length,dimensions);//selectez cat imi trebuie
			//cout << "selected: done"<< endl;
			mutate(curent_population, pop_length, dimensions,pop_length);
			//cout << "mutate: done" << endl;

			crossover(curent_population, dimensions, CROSS_NUMBER);
			//cout << "crossover: done" << endl;
			population_grade(curent_population, chance, dimensions, pop_length, lower, upper, mathFct);//imi dau scoruri la populatie
			//cout << "pop_grade: done" << endl;
			generation++;
			//cout << endl;
		}
		double vect_dimensions[33],vect_value[100],mini;
		int i = 0,cont_value=0,ok_min=0;
		for (int unit = 0; unit < pop_length; unit++)
		{
			vect_dimensions[i++] = bittodouble(curent_population[unit], 32, upper, lower);
			if ((unit + 1) % dimensions == 0)
			{
				i = 0;
				vect_value[cont_value] = mathFct(vect_dimensions, dimensions);
				if (ok_min == 0)
				{
					mini = vect_value[0];
					ok_min = 1;
				}
				else
				{
					mini = min(mini, vect_value[cont_value]);
				}
				cont_value++;
			}

		}
		cout << mini<< " ";
	}
