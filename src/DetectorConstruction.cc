#include "DetectorConstruction.hh"
#include "SensitiveDetector.hh"
#include <G4SystemOfUnits.hh>
#include <G4PVReplica.hh>
#include <G4VisAttributes.hh>
#include <G4Colour.hh>
#include<G4Tubs.hh>
#include<G4SDManager.hh>
#include<G4VisAttributes.hh>
#include <G4Cons.hh>
#include <G4Orb.hh>
#include <G4EllipticalTube.hh>
#include <G4Transform3D.hh>
#include <G4Trd.hh>
#include <G4UnionSolid.hh>
#include <G4PropagatorInField.hh>
#include <G4UniformMagField.hh>
#include <G4Mag_UsualEqRhs.hh>
#include <G4HelixHeum.hh>
#include <G4MagIntegratorDriver.hh>
#include <G4ChordFinder.hh>
#include <G4FieldManager.hh>
#include <G4QuadrupoleMagField.hh>
#include <G4RotationMatrix.hh>
#include <G4GlobalMagFieldMessenger.hh>
#include <G4MagIntegratorStepper.hh>
#include <G4ClassicalRK4.hh>
#include <globals.hh>
#include <G4SubtractionSolid.hh>
#include <G4OpticalSurface.hh>
#include <G4LogicalBorderSurface.hh>
#include <G4LogicalSkinSurface.hh>
#include <G4SubtractionSolid.hh>
#include <G4UniformElectricField.hh>
#include <G4EqMagElectricField.hh>
#include <G4TransportationManager.hh>
#include "G4Sphere.hh"
#include <G4VSolid.hh>
#include "CADMesh.hh"
#include <iostream>
#include <vector>
#include <string>
#include "G4AutoDelete.hh"
#include "G4RegionStore.hh"
#include "G4Region.hh"

using namespace std;

DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction()
{

    G4double size = 5000000*m;

    nist = G4NistManager::Instance();
    world_mat = nist->FindOrBuildMaterial("G4_Galactic");

    world = new G4Box("world", size/2, size/2, size/2);
    log_world = new G4LogicalVolume(world, world_mat, "world_log");
    phys_world = new G4PVPlacement(0, G4ThreeVector(), log_world, "1001", 0, false, 0);

}

DetectorConstruction::~DetectorConstruction()
{
    
    delete world;
    delete log_world;
    delete phys_world;

}


G4VPhysicalVolume* DetectorConstruction::Construct()
{




    G4Material *vac = nist->FindOrBuildMaterial("G4_Galactic");
    G4Material *aaa = nist->FindOrBuildMaterial("G4_AIR");
    G4Material *Pb = nist->FindOrBuildMaterial("G4_Pb");


    G4double a, z, density;
    G4int nelements, natoms;


    G4Element* N = new G4Element("Nitrogen", "N", z=7 , a=14.01*g/mole);
    G4Element* O = new G4Element("Oxygen"  , "O", z=8 , a=16.00*g/mole);
    G4Element* Ar = new G4Element("Argon"  , "Ar", z=18 , a=39.948*g/mole);



    G4Material* O2 = new G4Material("O2", density = 1.429 * g / cm3, nelements = 1);
    O2->AddElement(O, natoms=2);

    G4Material* N2 = new G4Material("N2", density = 0.0012506 * g / cm3, nelements = 1);
    N2->AddElement(N, natoms=2);

    G4Material* Argon = new G4Material("Argon", density = 1.784 * g / cm3, nelements = 1);
    Argon->AddElement(Ar, natoms=1);




    double h[42] = {1050, 1100, 950, 1100, 950, 
                    950, 950, 900, 900, 850,
                    850, 750, 700, 650, 650, 
                    700, 700, 600, 700, 700, 
                    600, 700, 700, 700, 600, 
                    650, 650, 650, 650, 650, 
                    700, 650, 700, 650, 650, 
                    700, 600, 700, 700, 700, 
                    700, 700};

    double rho[42] = {1.16375, 1.0473750000000002, 0.9426375, 0.8483737500000001, 0.7635363750000002, 
                    0.6871827375000001, 0.6184644637500001, 0.5566180173750002, 0.5009562156375001, 0.4508605940737501, 
                    0.40577453466637514, 0.36519708119973765, 0.3286773730797639, 0.29580963577178754, 0.2662286721946088, 
                    0.23960580497514794, 0.21564522447763315, 0.19408070202986982, 0.17467263182688286, 0.15720536864419454, 
                    0.1414848317797751, 0.1273363486017976, 0.11460271374161783, 0.10314244236745605, 0.09282819813071044, 
                    0.08354537831763942, 0.07519084048587547, 0.06767175643728793, 0.060904580793559135, 0.05481412271420323, 
                    0.04933271044278291, 0.04439943939850462, 0.039959495458654154, 0.03596354591278875, 0.03236719132150987, 
                    0.029130472189358884, 0.026217424970422995, 0.023595682473380696, 0.021236114226042626, 0.019112502803438364, 
                    0.01720125252309453, 0.015481127270785077};


    double pressure[42] = {1.0, 0.83, 0.73, 0.64, 0.56, 
                            0.5, 0.43, 0.38, 0.33, 0.29,
                            0.26, 0.23, 0.2, 0.18, 0.16, 
                            0.15, 0.13, 0.12, 0.11, 0.09, 
                            0.09, 0.08, 0.07, 0.06, 0.06, 
                            0.05, 0.05, 0.04, 0.04, 0.03, 
                            0.03, 0.03, 0.03, 0.02, 0.02, 
                            0.02, 0.02, 0.02, 0.02, 0.02, 
                            0.01, 0.01};


    double temperature[42] = {284.737, 277.75, 271.087, 264.425, 257.762, 
                            251.587, 245.412, 238.397, 233.547, 228,
                            222, 217, 216, 216, 216, 
                            216, 216, 216, 216, 216, 
                            216, 216, 216, 216, 216, 
                            216, 216, 220, 220, 220, 
                            220, 220, 220, 220, 220, 
                            220, 220, 228, 228, 228, 
                            228, 228};

    double r = 1000;
    double center[42]{};


    double s = 0.0;
    for (int i = 0; i < 42; i++)
    {
        center[i] = s + h[i] / 2.0;

        s = s + h[i];

    }



	for (int i = 0; i < 42; i++)
    {
    	air[i] = new G4Material("Air" + to_string(i), density=rho[i]*kg/m3, nelements=3);
        air[i]->AddElement(nist->FindOrBuildElement("N"), 78.*perCent);
        air[i]->AddElement(nist->FindOrBuildElement("O"), 21.*perCent);
        air[i]->AddElement(nist->FindOrBuildElement("Ar"), 1.*perCent);
    }

    for (int i = 0; i < 42; i++)
    {


        G4Tubs* layer = new G4Tubs("layer", 0*m, r*km, (h[i] / 2)*m, 0*deg, 360*deg);
        G4LogicalVolume *log_layer = new G4LogicalVolume(layer, air[i], "log_layer");
        new G4PVPlacement(0, G4ThreeVector(0*m, 0.0*m, center[i]*m), log_layer,
                                                    "layer", log_world, true, 0);

    }


    G4Tubs* det = new G4Tubs("det_shape", 0*m, 1000*km, 0.1*mm, 0*deg, 360*deg);
    log_det = new G4LogicalVolume(det, vac, "log_det");
    new G4PVPlacement(0, G4ThreeVector(0*m, 0.0*m,-0.1*mm), log_det,
                                                "det", log_world, true, 0);

    log_world->SetVisAttributes (G4VisAttributes::GetInvisible());

    return phys_world;

}


void DetectorConstruction::ConstructSDandField()
{

    // G4SDManager* SDman = G4SDManager::GetSDMpointer();
    // SensitiveDetector *detector = new SensitiveDetector("detector");
    // SDman->AddNewDetector(detector);
    // SetSensitiveDetector("log_det", detector);

}



