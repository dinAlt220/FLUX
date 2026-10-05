#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4Event.hh"
#include "vector"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"

#include "Generator.hh"

using namespace std;

class PrimaryParticles : public G4VUserPrimaryGeneratorAction{
    public:

        PrimaryParticles();
        ~PrimaryParticles();

        G4ParticleTable* particleTable;

        virtual void GeneratePrimaries(G4Event* event);
        
        int ac = 0;
        int n = 1;

        double EN = 0.0;

        double SP[34] = {1000, 2000, 3000, 4000, 5000, 6000,
    7000, 8000, 9000, 10000, 11000, 12000,
    13000, 14000, 15000, 25118.9, 39810.7, 63095.7,
    100000, 158489, 251189, 398107, 630957, 1000000,
    1.58489e+06, 2.51189e+06, 3.98107e+06, 6.30957e+06, 10000000, 1.58489e+07,
    2.51189e+07, 3.98107e+07, 6.30957e+07, 100000000 };

        vector <double> vec_dir;

        int N = 0;
        int j = 5;

        Generator *gen;


    private:

        G4ParticleGun* fParticleGun;
        
};
