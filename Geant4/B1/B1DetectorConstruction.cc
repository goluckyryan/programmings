//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: B1DetectorConstruction.cc 94307 2015-11-11 13:42:46Z gcosmo $
//
/// \file B1DetectorConstruction.cc
/// \brief Implementation of the B1DetectorConstruction class

#include "B1DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::B1DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::~B1DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
   
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //     
  // World
  //
  G4double world_sizeXY = 30*cm;
  G4double world_sizeZ  = 50*cm;
  //G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  
  G4String name, symbol;
  G4double z, a, fractionMass;
  G4int ncomponents;

  G4Element* e1Ar = new G4Element(name="Argon", symbol="H", z=16., a=20*g/mole);
  G4Element* e1N = new G4Element(name="Nitrogon"  , symbol="C", z=7., a=14.1*g/mole);
  G4Element* e1O = new G4Element(name="Oxygen"  , symbol="C", z=8., a=16.*g/mole);
  
  G4double density = 1e-10*g/cm3;
  G4Material* world_mat = new G4Material(name="Vaccum", density, ncomponents=3);
  world_mat->AddElement(e1Ar, fractionMass=1*perCent); 
  world_mat->AddElement(e1N, fractionMass=70*perCent); 
  world_mat->AddElement(e1O, fractionMass=29*perCent); 
  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
                     
  //     
  // beam Envelope
  //
  //G4double env_sizeXY = 1*cm, env_sizeZ = 0.8*world_sizeZ;
  //G4Material* env_mat = nist->FindOrBuildMaterial("G4_AIR");
  //G4Box* solidEnv =    
  //  new G4Box("Envelope",                    //its name
  //      0.5*env_sizeXY, 0.5*env_sizeXY, 0.5*env_sizeZ); //its size
  //    
  //G4LogicalVolume* logicEnv =                         
  //  new G4LogicalVolume(solidEnv,            //its solid
  //                      env_mat,             //its material
  //                      "Envelope");         //its name
  //             
  //new G4PVPlacement(0,                       //no rotation
  //                  G4ThreeVector(),         //at (0,0,0)
  //                  logicEnv,                //its logical volume
  //                  "Envelope",              //its name
  //                  logicWorld,              //its mother  volume
  //                  false,                   //no boolean operation
  //                  0,                       //copy number
  //                  checkOverlaps);          //overlaps checking
  
  
  ////target
  G4Material* target_mat = nist->FindOrBuildMaterial("G4_Li");
  //G4Box* targetShape = new G4Box("target", 0.5*20*mm, 0.5*20*mm,  10*mm);

  G4Tubs* targetShape = new G4Tubs("target", 0, 0.5*20*mm, 1*mm, 0, 360.*deg);
  
  G4LogicalVolume* logicTarget=                         
    new G4LogicalVolume(targetShape,         //its solid
                        target_mat,          //its material
                        "taget");           //its name 
                        
  new G4PVPlacement(0, G4ThreeVector(0, 0, -150*mm), logicTarget, "target", logicWorld, false, 0, checkOverlaps); 

  //beamStopper
  //G4Material* stopper_mat = nist->FindOrBuildMaterial("G4_Pb");
  //G4Box* stopperShape = new G4Box("stopper", 0.5*20*mm, 0.5*20*mm,  5*mm);
  //
  //G4LogicalVolume* logicStopper=                         
  //  new G4LogicalVolume(stopperShape,         //its solid
  //                      stopper_mat,          //its material
  //                      "stopper");           //its name 
  //                      
  //new G4PVPlacement(0, G4ThreeVector(0, 0, 130*mm), logicStopper, "stopper", logicWorld, false, 0, checkOverlaps); 
 
  // simple box
  G4int natoms;

  G4Element* e1H = new G4Element(name="Hydrogen", symbol="H", z=1., a=1.01*g/mole);
  G4Element* e1C = new G4Element(name="Carbon"  , symbol="C", z=6., a=12.*g/mole);
  
  density = 1.2*g/cm3;
  G4Material* shape_mat = new G4Material(name="PLSci", density, ncomponents=2);
  shape_mat->AddElement(e1H, natoms=9); 
  shape_mat->AddElement(e1C, natoms=10); 
  
  //G4Material* shape_mat = nist->FindOrBuildMaterial("G4_C");

  G4Box* solidShape1 = new G4Box("Shape1", 0.5*200*mm, 0.5*20*mm,  1*mm);
  G4Box* solidShape2 = new G4Box("Shape2", 0.5*20*mm, 0.5*200*mm,  5*mm);

  G4LogicalVolume* logicShape1 =                         
    new G4LogicalVolume(solidShape1,         //its solid
                        shape_mat,          //its material
                        "Shape1");           //its name
                  
  G4LogicalVolume* logicShape2 =                         
    new G4LogicalVolume(solidShape2,         //its solid
                        shape_mat,          //its material
                        "Shape2");           //its name
               
//  new G4PVPlacement(0, G4ThreeVector(0,  0*21*mm, 120*mm), logicShape1, "Shape00", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, G4ThreeVector(0,  1*21*mm, 120*mm), logicShape1, "Shape01", logicWorld, false, 1, checkOverlaps);
  new G4PVPlacement(0, G4ThreeVector(0,  2*21*mm, 120*mm), logicShape1, "Shape02", logicWorld, false, 2, checkOverlaps);
  new G4PVPlacement(0, G4ThreeVector(0,  3*21*mm, 120*mm), logicShape1, "Shape03", logicWorld, false, 3, checkOverlaps);
  new G4PVPlacement(0, G4ThreeVector(0,  4*21*mm, 120*mm), logicShape1, "Shape04", logicWorld, false, 4, checkOverlaps);
  new G4PVPlacement(0, G4ThreeVector(0, -1*21*mm, 120*mm), logicShape1, "Shape11", logicWorld, false, 5, checkOverlaps);
  new G4PVPlacement(0, G4ThreeVector(0, -2*21*mm, 120*mm), logicShape1, "Shape12", logicWorld, false, 6, checkOverlaps);
  new G4PVPlacement(0, G4ThreeVector(0, -3*21*mm, 120*mm), logicShape1, "Shape13", logicWorld, false, 7, checkOverlaps);
  new G4PVPlacement(0, G4ThreeVector(0, -4*21*mm, 120*mm), logicShape1, "Shape14", logicWorld, false, 8, checkOverlaps);

//  new G4PVPlacement(0, G4ThreeVector( 0*21*mm, 0, 170*mm), logicShape2, "Shape20", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, G4ThreeVector( 1*21*mm, 0, 170*mm), logicShape2, "Shape21", logicWorld, false, 1, checkOverlaps);
  new G4PVPlacement(0, G4ThreeVector( 2*21*mm, 0, 170*mm), logicShape2, "Shape22", logicWorld, false, 2, checkOverlaps);
  new G4PVPlacement(0, G4ThreeVector( 3*21*mm, 0, 170*mm), logicShape2, "Shape23", logicWorld, false, 3, checkOverlaps);
  new G4PVPlacement(0, G4ThreeVector( 4*21*mm, 0, 170*mm), logicShape2, "Shape24", logicWorld, false, 4, checkOverlaps);
  new G4PVPlacement(0, G4ThreeVector(-1*21*mm, 0, 170*mm), logicShape2, "Shape31", logicWorld, false, 5, checkOverlaps);
  new G4PVPlacement(0, G4ThreeVector(-2*21*mm, 0, 170*mm), logicShape2, "Shape32", logicWorld, false, 6, checkOverlaps);
  new G4PVPlacement(0, G4ThreeVector(-3*21*mm, 0, 170*mm), logicShape2, "Shape33", logicWorld, false, 7, checkOverlaps);
  new G4PVPlacement(0, G4ThreeVector(-4*21*mm, 0, 170*mm), logicShape2, "Shape34", logicWorld, false, 8, checkOverlaps);

  // Set Shape2 as scoring volume
  //
  fScoringVolume = logicShape2;

  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
