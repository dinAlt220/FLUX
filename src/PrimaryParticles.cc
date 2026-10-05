#include "PrimaryParticles.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "time.h"
#include "G4Geantino.hh"
#include "G4IonTable.hh"
#include "G4ChargedGeantino.hh"
#include "G4NuclideTable.hh"
#include "G4VIsotopeTable.hh"
#include "G4Ions.hh"
#include "vector"
#include "string"
#include <fstream>
#include <iostream>
#include <vector>
#include "Randomize.hh"

using namespace std;


PrimaryParticles::PrimaryParticles(){


    G4int nofParticles = 1;
    fParticleGun = new G4ParticleGun(nofParticles);

    auto particleDefinition
    = G4ParticleTable::GetParticleTable()->FindParticle("proton");
    fParticleGun->SetParticleDefinition(particleDefinition);

    gen = new Generator();

}


void PrimaryParticles::GeneratePrimaries(G4Event* event){

    ac = ac + 1;

    if (ac == 100*n)
    {     
        n++;
        cout << ac << endl;
    }

    double seed = clock(  );
    G4double a = -(1000000)+2*1000000*G4UniformRand();
    double par = G4Threading::G4GetThreadId() + a;
    G4Random::setTheSeed( seed, par);
    
    vec_dir = gen->get_dir();
    double E = gen->get_E();


    G4double phi =  2 * M_PI * G4UniformRand();
    G4double costheta = 1.0 * G4UniformRand();
    G4double theta =  acos(costheta);

    double r = 1000.0 * sqrt(G4UniformRand());
	double phi1 = 2 * M_PI * G4UniformRand();
	double x = r * cos(phi1);
	double y = r * sin(phi1);

	cout << E << endl;

    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(vec_dir[0], vec_dir[1], vec_dir[2]) );
    fParticleGun->SetParticleEnergy(E*GeV);
    fParticleGun->SetParticlePosition(G4ThreeVector(0*km, 0*km, 31399*m));

    fParticleGun->GeneratePrimaryVertex(event); 


	

		
	}




PrimaryParticles::~PrimaryParticles()
{
    delete fParticleGun;
}
