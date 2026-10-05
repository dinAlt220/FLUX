#include <iostream>
#include <random>
#include "Generator.hh"
#include <fstream>
#include "Randomize.hh"

using namespace std;

Generator::Generator()
{

	for (int i = E1; i < E2; i++)
	{
		myVec_en.push_back(i);
	}

	// for theta generator

	vector<double> myTheta_I0;

	for (int i = 0; i < 91; i++)
	{
		myTheta.push_back(i);
	}

	for (int t = 0; t < 91; t++)
	{
		double s = 0.0;

		double the = t * M_PI / 180.0;

		for (int e = E1; e < E2; e++)
		{
			s = s + 0.5 * (inst->dIdp(the, e) + inst->dIdp(the, e + 1.0));
		}
		myTheta_I0.push_back(s);
	}

	myTheta_I.push_back(0.0);
	myTheta_edges.push_back(0.0);

	double K = 0.0;

	for (int i = 0; i < myTheta_I0.size() - 1; i++)
	{

		K = K + 0.5 * (myTheta_I0[i] + myTheta_I0[i+1]);
		myTheta_I.push_back(K);

	}

	myTheta_edges.push_back(K);



}


double Generator::get_E()
{

	vector<double> myVec_I;
	vector<double> myVec_edges;

	double x1 = 0;
	double x2 = 0;

	double y1 = 0;
	double y2 = 0; 

	double E = 0;

	double theta_map = ceilf((theta * 180.0 / M_PI) * 1.0) / 1.0;


	auto res = myMap_I.find(theta_map);

	if (res == myMap_I.end())
	{

		double s = 0.0;
		myVec_I.push_back(s);

		for (int eni = E1; eni < E2; eni++)
		{
			s = s + 0.5 * (inst->dIdp(theta, eni) + inst->dIdp(theta, eni + 1.0));
			myVec_I.push_back(s);


			if (eni == myVec_en.size() - 1)
			{
				myVec_edges.push_back(0.0);
				myVec_edges.push_back(s);
			}
		}

		myMap_I.emplace(theta_map, myVec_I);
		myMap_edges.emplace(theta_map, myVec_edges);

	}


	auto res_I = myMap_I.find(theta_map);
	auto res_edges = myMap_edges.find(theta_map);

	vector<double> &x_new = myVec_en;
	vector<double> &y_new = res_I->second;
	vector<double> &edges = res_edges->second;

	double rnd = edges[0] + (edges[1] - edges[0]) * G4UniformRand();

	for (int i = 0; i < myVec_en.size() - 1; i++)
	{
		if (rnd >= y_new[i] and rnd < y_new[i+1])
		{
			x1 = y_new[i];
			x2 = y_new[i+1];

			y1 = x_new[i];
			y2 = x_new[i+1];
			break;
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

	E = k * rnd + b;
	
	return E;
}


vector <double> Generator::get_dir()
{


	theta = inst->gen_theta(myTheta, myTheta_I, myTheta_edges);

	double phi = 2.0 * M_PI * G4UniformRand();

	double xd = sin(M_PI-theta) * cos(phi);
	double yd = sin(M_PI-theta) * sin(phi);
	double zd = cos(M_PI-theta);

	vector <double> vec{xd, yd, zd};

	return vec;
}
