#include "Action.hh"
#include "PrimaryParticles.hh"
#include "DetectorConstruction.hh"
#include "SteppingAction.hh"

Action::Action(){

}

Action::~Action(){

}

void Action::Build() const{

    SetUserAction(new PrimaryParticles);
    SetUserAction(new SteppingAction(fDetConstruction));


}