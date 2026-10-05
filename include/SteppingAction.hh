#include "G4UserSteppingAction.hh"
#include <G4SystemOfUnits.hh>
#include <stdio.h>
#include <string>
#include <G4NistManager.hh>
#include <G4Material.hh>

using namespace std;


class DetectorConstruction;


class SteppingAction : public G4UserSteppingAction
{
public:
	SteppingAction(const DetectorConstruction* detectorConstruction);
	virtual ~SteppingAction();

	virtual void UserSteppingAction(const G4Step* step);

	double MU = 1;
	double EL = 0;


	double a = 0;
	double b = 0;

	double p = 0;
	int count = 0;

private:
	const DetectorConstruction* fDetConstruction;
};


