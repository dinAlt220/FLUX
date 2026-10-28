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

		G4ThreeVector stepPos = point1->GetPosition();

		G4int trackID = step->GetTrack()->GetTrackID();

		G4String p_name = step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName();
		
		string jobid = getenv("PBS_JOBID") ? getenv("PBS_JOBID") : "local";





		G4Track* track = step->GetTrack(); 
		G4double kinEnergy = track->GetKineticEnergy()/GeV; 

		if ((p_name == "mu-" or p_name == "mu+"))
		{


			const G4VTouchable *touchable = point1->GetTouchable();
			const G4RotationMatrix *rot = touchable->GetRotation();
			G4RotationMatrix rotInv = rot->inverse();
			G4ThreeVector transl = touchable->GetTranslation();
			G4VSolid *sector = touchable->GetSolid();
			G4ThreeVector posLoc = *rot * (stepPos - transl);
			G4ThreeVector norm = sector->SurfaceNormal(posLoc);
			G4ThreeVector normGlob = rotInv * norm;


			ofstream file1("data/muon_data_" + jobid + ".txt", ios::app);

			MU++;
			G4Track* track = step->GetTrack(); 
			G4ThreeVector momentum = track->GetMomentumDirection(); 
			G4double kinEnergy = track->GetKineticEnergy()/GeV; 

			double cx = momentum.x();
			double cy = momentum.y();
			double cz = -momentum.z();


			double numem = cx * normGlob.x() + cy * normGlob.y() + cz * normGlob.z();
			double denum = sqrt(pow(cx, 2) + pow(cy, 2) + pow(cz, 2)) * sqrt(pow(normGlob.x(), 2) + pow(normGlob.y(), 2) + pow(normGlob.z(), 2));
			double ang_inc = acos(numem / denum) * 180.0 / M_PI;



			file1<< kinEnergy << "\t" << ang_inc << endl;

			step->GetTrack()->SetTrackStatus(fStopAndKill);

		}


		if ((p_name == "e-" or p_name == "e+"))
		{


			const G4VTouchable *touchable = point1->GetTouchable();
			const G4RotationMatrix *rot = touchable->GetRotation();
			G4RotationMatrix rotInv = rot->inverse();
			G4ThreeVector transl = touchable->GetTranslation();
			G4VSolid *sector = touchable->GetSolid();
			G4ThreeVector posLoc = *rot * (stepPos - transl);
			G4ThreeVector norm = sector->SurfaceNormal(posLoc);
			G4ThreeVector normGlob = rotInv * norm;

			G4Track* track = step->GetTrack(); 
			G4double kinEnergy = track->GetKineticEnergy()/GeV; 

			ofstream file2("data/electron_data_" + jobid + ".txt", ios::app);

			G4ThreeVector momentum = track->GetMomentumDirection(); 

			double cx = momentum.x();
			double cy = momentum.y();
			double cz = -momentum.z();

			if (cz > 0.0) 
			{


				double numem = cx * normGlob.x() + cy * normGlob.y() + cz * normGlob.z();
				double denum = sqrt(pow(cx, 2) + pow(cy, 2) + pow(cz, 2)) * sqrt(pow(normGlob.x(), 2) + pow(normGlob.y(), 2) + pow(normGlob.z(), 2));
				double ang_inc = acos(numem / denum) * 180.0 / M_PI;

				EL++;
				file2<< kinEnergy << "\t" << ang_inc << endl;
			}
			else
			{
				step->GetTrack()->SetTrackStatus(fStopAndKill);
			}


			step->GetTrack()->SetTrackStatus(fStopAndKill);
		

		}
	
	  step->GetTrack()->SetTrackStatus(fStopAndKill);
	}



}

SteppingAction::~SteppingAction()
{
}
