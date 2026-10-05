#include "SensitiveDetector.hh"
#include <G4Step.hh>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <G4SystemOfUnits.hh>
#include <thread>
#include <mutex>
#include "Randomize.hh"
#include "time.h"
#include "G4RunManager.hh"

using namespace std;

SensitiveDetector::SensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{


}

G4bool SensitiveDetector::ProcessHits(G4Step *step, G4TouchableHistory*)
{


	if (count == 0)
	{
		double seed = clock(  );
	    G4double a = -(1000000)+2*1000000*G4UniformRand();
	    double par = G4Threading::G4GetThreadId() + a;
	    G4Random::setTheSeed( seed, par);
		p = 1000000000 * G4UniformRand();
	}
	count++;

	
	//cout << "here" << endl;
	
	G4StepPoint* point1 = step->GetPreStepPoint();
	G4ThreeVector pos1 = point1->GetPosition();

	const G4AffineTransform transformation = point1->GetTouchable()->GetHistory()->GetTopTransform();
	G4ThreeVector localPosition = transformation.TransformPoint(pos1);


	double X = localPosition.x()/km;
	double Y = localPosition.y()/km;

	double R = sqrt(pow(X,2) + pow(Y,2));

	// cout << R << endl;
	int evID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

	G4StepPoint* prePoint = step->GetPostStepPoint();
	G4TouchableHandle touch1 = prePoint->GetTouchableHandle();
	G4VPhysicalVolume* volume = touch1->GetVolume();
	G4String vname = volume->GetName();


	G4int trackID = step->GetTrack()->GetTrackID();


	G4String p_name = step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName();


	G4Track* track = step->GetTrack(); 
	G4double kinEnergy = track->GetKineticEnergy()/GeV; 

	if ((p_name == "mu-" or p_name == "mu+") and R < 1000)
	{

		ofstream file1("muon_data_" + to_string(p) + ".txt", ios::app);

		MU++;
		G4Track* track = step->GetTrack(); 
	    G4ThreeVector momentum = track->GetMomentumDirection(); 
	    G4double kinEnergy = track->GetKineticEnergy()/GeV; 

	    double cx = momentum.x();
	    double cy = momentum.y();
		double cz = momentum.z();

		file1<< kinEnergy << "\t" << cx << "\t" << cy << "\t" << cz << "\t" << evID << "\t" << X << "\t" << Y << endl;

		step->GetTrack()->SetTrackStatus(fStopAndKill);

	}


	if (p_name == "e-" and R < 1000)
	{
		EL++;

		ofstream file2("electron_data_" + to_string(p) + ".txt", ios::app);

		G4Track* track = step->GetTrack(); 
	    G4ThreeVector momentum = track->GetMomentumDirection(); 
	    G4double kinEnergy = track->GetKineticEnergy()/GeV; 

	    double cx = momentum.x();
	    double cy = momentum.y();
		double cz = momentum.z();

		// cout << trackID << endl;

		file2<< kinEnergy << "\t" << cx << "\t" << cy << "\t" << cz << "\t" << evID << "\t" << X << "\t" << Y << endl;

		step->GetTrack()->SetTrackStatus(fStopAndKill);

	}

	if (p_name == "e+" and R < 1000)
	{

		EL++;

		ofstream file4("positron_data_" + to_string(p) + ".txt", ios::app);

		G4Track* track = step->GetTrack(); 
	    G4ThreeVector momentum = track->GetMomentumDirection(); 
	    G4double kinEnergy = track->GetKineticEnergy()/GeV; 

	    double cx = momentum.x();
	    double cy = momentum.y();
		double cz = momentum.z();

		file4<< kinEnergy << "\t" << cx << "\t" << cy << "\t" << cz << "\t" << evID << "\t" << X << "\t" << Y << endl;

		step->GetTrack()->SetTrackStatus(fStopAndKill);

	}


	if (p_name == "proton" and R < 1000)
	{

		ofstream file3("proton_data_" + to_string(p) + ".txt", ios::app);

		G4Track* track = step->GetTrack(); 
	    G4ThreeVector momentum = track->GetMomentumDirection(); 
	    G4double kinEnergy = track->GetKineticEnergy()/GeV; 

	    double cx = momentum.x();
	    double cy = momentum.y();
		double cz = momentum.z();

		file3<< kinEnergy << "\t" << cx << "\t" << cy << "\t" << cz << "\t" << evID << "\t" << X << "\t" << Y << endl;

	}



	if (p_name == "gamma" and R < 1000)
	{

		// EL++;

		ofstream file5("gamma_data_" + to_string(p) + ".txt", ios::app);

		G4Track* track = step->GetTrack(); 
	    G4ThreeVector momentum = track->GetMomentumDirection(); 
	    G4double kinEnergy = track->GetKineticEnergy()/GeV; 

	    double cx = momentum.x();
	    double cy = momentum.y();
		double cz = momentum.z();

		file5 << kinEnergy << "\t" << cx << "\t" << cy << "\t" << cz << "\t" << evID << "\t" << X << "\t" << Y << endl;

	}	

	// cout << EL / MU << endl;

    step->GetTrack()->SetTrackStatus(fStopAndKill);
    
    return true;

}


SensitiveDetector::~SensitiveDetector()
{

}
