#include "MyParallelWorld.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "SensitiveDetector.hh"
#include <G4SystemOfUnits.hh>
#include<G4SDManager.hh>
#include <G4NistManager.hh>
#include <G4PVReplica.hh>
#include "G4VSolid.hh"
#include "G4Sphere.hh"
#include "G4SubtractionSolid.hh"
#include <G4Tubs.hh>
#include <G4VisAttributes.hh>
using namespace std;


MyParallelWorld::MyParallelWorld(G4String worldName):G4VUserParallelWorld(worldName)
{


}
MyParallelWorld::~MyParallelWorld()
{;}


void MyParallelWorld::Construct()
{

    G4VPhysicalVolume* ghostWorld = GetWorld();
    G4LogicalVolume* worldLogical = ghostWorld->GetLogicalVolume();



    // G4Tubs* det = new G4Tubs("det", 0*m, 1000*km, 100*m, 0*deg, 360*deg);
    // G4LogicalVolume *log_det = new G4LogicalVolume(det, 0, "log_det");
    // new G4PVPlacement(0, G4ThreeVector(0*m, 0.0*m, -100*mm), log_det,
    //                                             "det", worldLogical, 0, 0);



    worldLogical->SetVisAttributes (G4VisAttributes::GetInvisible());

}


void MyParallelWorld::ConstructSD()
{

    // G4SDManager* SDman = G4SDManager::GetSDMpointer();
    // SensitiveDetector *detector = new SensitiveDetector("detector");
    // SDman->AddNewDetector(detector);
    // SetSensitiveDetector("log_det", detector);

}
