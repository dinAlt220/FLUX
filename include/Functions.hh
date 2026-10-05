//Minimun requared function to generate muons flux

using namespace std;

class Functions
{
public:


	Functions();
	
	/*
	muon flux distribution function 
	(azimun angle, energy of muons)
	*/
	double dIdp(double, double);

	/*
	generate of random azimut angle according to ~ 2*pi*sin(theta)*cos^2(theta)
	*/
	double gen_theta(vector<double>, vector<double>, vector<double>);

};