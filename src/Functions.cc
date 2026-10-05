#include <iostream>
#include <math.h>
#include <random>
#include "Functions.hh"
#include <fstream>
#include "Randomize.hh"

using namespace std;


Functions::Functions()
{
}


double Functions::dIdp(double theta, double E)
{	
	double A = 18000.0;
	double B = 1.265;
	double alpha = -3.915;
	double beta = 1.165;

	return A * pow((E + B), alpha) * pow(E, beta) * sin(theta) * cos(theta);
}


double Functions::gen_theta(vector<double> myTheta, vector<double> myTheta_I, vector<double> myTheta_edges)
{	

	double x1;
	double x2;

	double y1;
	double y2; 

	double theta = 0.0;

	vector<double> x_new = myTheta;
	vector<double> y_new = myTheta_I;
	vector<double> edges = myTheta_edges;


	double rnd = edges[0] + (edges[1] - edges[0]) * G4UniformRand();

	for (int i = 0; i < y_new.size()-1; i++)
	{
		if (rnd >= y_new[i] and rnd < y_new[i+1])
		{
			x1 = y_new[i];
			x2 = y_new[i+1];

			y1 = x_new[i];
			y2 = x_new[i+1];
		}
	}


	double b;
	double k;

	if (x1 != 0)
	{
		b = (y2 * x1 - y1 * x2) / (x1 - x2);
		k = (y1 - b) / x1;
	}
	else
	{
		b = y1;
		k = (y2 - y1) / x2;
	}

	theta = k * rnd + b;

	theta = theta * M_PI / 180.0;

	return theta;

}

