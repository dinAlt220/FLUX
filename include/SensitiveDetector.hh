#include<G4VSensitiveDetector.hh>
#include <G4SystemOfUnits.hh>
#include <stdio.h>
#include <string>
#include <G4NistManager.hh>
#include <G4Material.hh>

using namespace std;

class SensitiveDetector : public G4VSensitiveDetector{

    public:

        SensitiveDetector(G4String);
        ~SensitiveDetector();

        double p = 0;
        int count = 0;

        G4bool ProcessHits(G4Step *step, G4TouchableHistory*);

        double MU = 1;
        double EL = 0;

};
