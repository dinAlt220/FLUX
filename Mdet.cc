#include "DetectorConstruction.hh"
#include <QGSP_BIC_HP.hh>
#include <G4UImanager.hh>
#include <G4UIExecutive.hh>
#include "Action.hh"
#include "G4UIcommand.hh"
#include "Randomize.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include <G4EmLivermorePhysics.hh>
#include "G4RunManager.hh"
#include <unistd.h>
#include "time.h"
#include "G4EmLivermorePhysics.hh"
#include "MyParallelWorld.hh"
#include "G4ParallelWorldPhysics.hh"
#include "G4VisExecutive.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4DecayPhysics.hh"
#include "G4ParticleHPManager.hh"

#include "G4RunManagerFactory.hh"
#include "G4PhysListFactory.hh"

#include "G4VModularPhysicsList.hh"

using namespace std;

int main(int argc,char** argv)
{

    // G4Random::setTheEngine(new CLHEP::RanecuEngine);

    G4RunManager *run = new G4RunManager;

    DetectorConstruction *geom = new DetectorConstruction();

    G4String paraWorldName = "ParallelWorld";
    geom->RegisterParallelWorld(new MyParallelWorld(paraWorldName));

    run->SetUserInitialization(geom);



    // G4PhysListFactory factory;
    // G4VModularPhysicsList* phys = factory.GetReferencePhysList("Shielding_HPT");

    QGSP_BIC_HP *phys = new QGSP_BIC_HP;

    // UrQMD *phys = new UrQMD;

    // PhysicsList* phys = new PhysicsList();
    // phys->AddPhysicsList("FTFP_BERT_CRMC_EPOS199");

    // phys->ReplacePhysics(new G4EmStandardPhysics_option4());
    //phys->RegisterPhysics(new G4ChargeExchangePhysics());
    // phys->ReplacePhysics(new G4EmStandardPhysics_option4());
    // phys->RegisterPhysics(new G4EmLivermorePhysics);
    // phys->RegisterPhysics(new G4RadioactiveDecayPhysics());
    phys->RegisterPhysics(new G4ParallelWorldPhysics(paraWorldName));
    run->SetUserInitialization(phys);





    Action *act = new Action;
    run->SetUserInitialization(act);

    G4VisExecutive *vis = new G4VisExecutive;
    vis->Initialize();

    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);

    UImanager->ApplyCommand("/control/verbose 2");
    UImanager->ApplyCommand("/run/verbose 2");
    UImanager->ApplyCommand("/run/setCut 1 km");
    UImanager->ApplyCommand("/process/had/rdm/thresholdForVeryLongDecayTime 1e+60 year");

    // UImanager->ApplyCommand("/run/setCutForAGivenParticle gamma 1.0 m");
    // UImanager->ApplyCommand("/run/setCutForAGivenParticle e- 0.1 m");
    // UImanager->ApplyCommand("/run/setCutForAGivenParticle e+ 0.1 m");
    // UImanager->ApplyCommand("/run/setCutForAGivenParticle proton 3 m");


    bool lowelectro = false;
    
    if (lowelectro == true){

        UImanager->ApplyCommand("/process/em/fluo true");
        UImanager->ApplyCommand("/process/em/auger true");
        UImanager->ApplyCommand("/process/em/augerCascade true");
        UImanager->ApplyCommand("/process/em/pixe true");
        UImanager->ApplyCommand("/process/em/pixeElecXSmodel Penelope");
    }

    
    UImanager->ApplyCommand("/run/initialize");

    bool visual = false;
    
    if (visual == true){

        UImanager->ApplyCommand("/vis/verbose 2");
        UImanager->ApplyCommand("/tracking/verbose 0");
        UImanager->ApplyCommand("/vis/scene/create");
        UImanager->ApplyCommand("/vis/open VRML2FILE");
        //UImanager->ApplyCommand("/vis/drawVolume");

        UImanager->ApplyCommand("/vis/drawVolume worlds");
        // UImanager->ApplyCommand("/vis/filtering/trajectories/create/particleFilter");
        // UImanager->ApplyCommand("/vis/filtering/trajectories/particleFilter-0/add e-");
        // UImanager->ApplyCommand("/vis/filtering/trajectories/particleFilter-0/add e+");
        // UImanager->ApplyCommand("/vis/filtering/trajectories/particleFilter-0/add mu-");
        // UImanager->ApplyCommand("/vis/filtering/trajectories/particleFilter-0/add mu+");

        // UImanager->ApplyCommand("/vis/filtering/trajectories/mode hard");
        // UImanager->ApplyCommand("/vis/filtering/trajectories/create/originVolumeFilter");
        // UImanager->ApplyCommand("/vis/filtering/trajectories/originVolumeFilter-0/add log_det");
        //  UImanager->ApplyCommand("/vis/filtering/trajectories/originVolumeFilter-0/add log_layer1");
        //  UImanager->ApplyCommand("/vis/filtering/trajectories/originVolumeFilter-0/add world_log");
        // UImanager->ApplyCommand("/vis/filtering/trajectories/originVolumeFilter-0/verbose false");

        UImanager->ApplyCommand("/vis/viewer/set/viewpointThetaPhi 90. 90");
        UImanager->ApplyCommand("/vis/scene/add/trajectories");

        UImanager->ApplyCommand("/vis/scene/add/hits");
        UImanager->ApplyCommand("/vis/modeling/trajectories/create/drawByCharge");
        UImanager->ApplyCommand("/vis/modeling/trajectories/drawByCharge-0/default/setStepPtsSize 2");
        UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate");
        
    }

    // UImanager->ApplyCommand("/process/had/rdm/thresholdForVeryLongDecayTime 1.0e+100 year");
    // UImanager->ApplyCommand("/process/had/enableCRCoalescence true");

    double seed1 = clock(  );
    G4double a1 = -(1000000)+2*1000000*G4UniformRand();
    double par1 = G4Threading::G4GetThreadId() + a1;
    G4Random::setTheSeed( seed1, par1);

    int number = 10000;
    UImanager->ApplyCommand("/run/beamOn " + std::to_string(number));
    
    delete ui;
    delete vis;
    delete run;

}
