#include "SteppingAction.hh"
#include "DetectorConstruction.hh"
#include "G4Step.hh"
#include "G4RunManager.hh"
#include <G4Step.hh>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <G4SystemOfUnits.hh>
#include <thread>
#include <mutex>
#include <G4VProcess.hh>

using namespace std;

SteppingAction::SteppingAction(
                      const DetectorConstruction* detectorConstruction)
  : G4UserSteppingAction(),
    fDetConstruction(detectorConstruction)
{}

void SteppingAction::UserSteppingAction(const G4Step* step)
{

G4String p_name = step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName();

	G4Track* track = step->GetTrack(); 
	G4double kinEnergy = track->GetKineticEnergy()/GeV; 

	if (kinEnergy <= 0.003)
	{
		step->GetTrack()->SetTrackStatus(fStopAndKill);
	}


  // 	if (kinEnergy < 0.3 and p_name != "gamma" and p_name != "e-" and p_name != "e+" and p_name != "pi0")
	// {
	// 	step->GetTrack()->SetTrackStatus(fStopAndKill);
	// }


	// if (p_name == "e-" and kinEnergy < 0.003)
	// {
	// 	step->GetTrack()->SetTrackStatus(fStopAndKill);
	// }

	// if (p_name == "e+" and kinEnergy < 0.003)
	// {
	// 	step->GetTrack()->SetTrackStatus(fStopAndKill);
	// }

	// if (p_name == "gamma" and kinEnergy < 0.003)
	// {
	// 	step->GetTrack()->SetTrackStatus(fStopAndKill);
	// }

	// if (p_name == "pi0" and kinEnergy < 0.003)
	// {
	// 	step->GetTrack()->SetTrackStatus(fStopAndKill);
	// }


	// if (p_name == "mu-" and kinEnergy < 0.3)
	// {
	// 	step->GetTrack()->SetTrackStatus(fStopAndKill);
	// }

	// 	if (p_name == "mu+" and kinEnergy < 0.3)
	// {
	// 	step->GetTrack()->SetTrackStatus(fStopAndKill);
	// }



	
	G4StepPoint* prePoint = step->GetPreStepPoint();
	G4TouchableHandle touch1 = prePoint->GetTouchableHandle();
	G4VPhysicalVolume* volume = touch1->GetVolume();
	G4String vname = volume->GetName();



	// if (vname == "1001")
	// {
	// 	step->GetTrack()->SetTrackStatus(fStopAndKill);
	// }


	if (vname == "det")
	{

		G4StepPoint* point1 = step->GetPreStepPoint();
		G4ThreeVector pos1 = point1->GetPosition();

		const G4AffineTransform transformation = point1->GetTouchable()->GetHistory()->GetTopTransform();
		G4ThreeVector localPosition = transformation.TransformPoint(pos1);


		double X = localPosition.x()/km;
		double Y = localPosition.y()/km;

		double R = sqrt(pow(X,2) + pow(Y,2));

		// cout << R << endl;
		int evID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();



		if (count == 0 and vname == "det")
		{
			double seed = clock(  );
			G4double a = -(1000000)+2*1000000*G4UniformRand();
			double par = G4Threading::G4GetThreadId() + a;
			G4Random::setTheSeed( seed, par);
			p = 1000000000 * G4UniformRand();
		}
		count++;


		G4int trackID = step->GetTrack()->GetTrackID();

		G4String p_name = step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName();


		G4Track* track = step->GetTrack(); 
		G4double kinEnergy = track->GetKineticEnergy()/GeV; 

		if ((p_name == "mu-" or p_name == "mu+") and R < 1000)
		{


			ofstream file1("muon_data_nocos.txt", ios::app);

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



		if ((p_name == "e-" or p_name == "e+") and R < 1000)
		{


			ofstream file2("electron_data_nocos.txt", ios::app);

			G4Track* track = step->GetTrack(); 
			G4ThreeVector momentum = track->GetMomentumDirection(); 
			G4double kinEnergy = track->GetKineticEnergy()/GeV; 

			double cx = momentum.x();
			double cy = momentum.y();
			double cz = momentum.z();

			if (cz < 0.0) 
			{
				EL++;
				file2<< kinEnergy << "\t" << cx << "\t" << cy << "\t" << cz << "\t" << evID << "\t" << X << "\t" << Y << endl;
			}
			else
			{
				step->GetTrack()->SetTrackStatus(fStopAndKill);
			}


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


			ofstream file5("gamma_data_" + to_string(p) + ".txt", ios::app);

			G4Track* track = step->GetTrack(); 
			G4ThreeVector momentum = track->GetMomentumDirection(); 
			G4double kinEnergy = track->GetKineticEnergy()/GeV; 

			double cx = momentum.x();
			double cy = momentum.y();
			double cz = momentum.z();

			file5 << kinEnergy << "\t" << cx << "\t" << cy << "\t" << cz << "\t" << evID << "\t" << X << "\t" << Y << endl;

			step->GetTrack()->SetTrackStatus(fStopAndKill);

		}	


	  step->GetTrack()->SetTrackStatus(fStopAndKill);

	}



}

SteppingAction::~SteppingAction()
{
}