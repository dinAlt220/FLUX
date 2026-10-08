#include <iostream>
#include "Functions.hh"
#include <vector>
#include <map>
#include <string>
#include <math.h>

using namespace std;

class Generator
{
public:

	/*
	Constructor for calculation of normolized time
	(radius of area [cm], cut-off energy [GeV])
	*/
	Generator();


	Functions *inst = new Functions();
	double flux_velocity;
	double cut_energy;
	double theta;
	double R0;
	int cout_temp = 0;
	int cout = 0;

	int E1 = 15;
	int E2 = 100000;


	map<double, vector<double>> myMap_I;
	map<double, vector<double>> myMap_edges;

	vector<double> myVec_en;

	// for theta generator
	vector<double> myTheta_edges;
	vector<double> myTheta;
	vector<double> myTheta_I;

	
	/*
	Get energy by Newton's method
	*/
	double get_E();

	/*
	Get direction of muons taking into account azimut angle distribution
	*/
	vector <double> get_dir();



};