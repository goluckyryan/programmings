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
// $Id: B5DetectorConstruction.cc 77656 2013-11-27 08:52:57Z gcosmo $
//
/// \file B5DetectorConstruction.cc
/// \brief Implementation of the B5DetectorConstruction class

#include "B5DetectorConstruction.hh"
#include "B5HodoscopeSD.hh"

#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4Mag_UsualEqRhs.hh"
#include "G4AutoDelete.hh"

#include "G4Material.hh"
#include "G4Element.hh"
#include "G4MaterialTable.hh"
#include "G4NistManager.hh"

#include "G4VSolid.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4PVReplica.hh"
#include "G4UserLimits.hh"

#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"
#include "G4RunManager.hh"
#include "G4GenericMessenger.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4ios.hh"
#include "G4SystemOfUnits.hh"
    
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B5DetectorConstruction::B5DetectorConstruction()
: G4VUserDetectorConstruction(), 
  fHodoscope1Logical(0),// fHodoscope2Logical(0),
  fVisAttributes()
{  
   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B5DetectorConstruction::~B5DetectorConstruction()
{
    
    for (G4int i=0; i<G4int(fVisAttributes.size()); ++i) 
    {
      delete fVisAttributes[i];
    }  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B5DetectorConstruction::Construct()
{
    // Construct materials
    ConstructMaterials();
    G4Material* air = G4Material::GetMaterial("B5_AIR");
    //G4Material* argonGas = G4Material::GetMaterial("B5_Ar");
//    G4Material* argonGas = G4Material::GetMaterial("G4_Ar");
    G4Material* scintillator = G4Material::GetMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
//    G4Material* csI = G4Material::GetMaterial("G4_CESIUM_IODIDE");
//    G4Material* lead = G4Material::GetMaterial("G4_Pb");
    
    G4String name, symbol;
    G4double z, a;
	G4int natoms;
    G4int ncomponents;

    G4Element* e1C = new G4Element(name="Carbon", symbol="C", z=6, a=12.01*g/mole);
    G4Element* e1H = new G4Element(name="Hydrogen", symbol="H", z=1, a=1.01*g/mole);
	
    G4double density = 0.79867*g/cm3;
	G4Material* CH2 = new G4Material(name="AAAA", density, ncomponents=2);
    CH2->AddElement(e1H, natoms=2); 
    CH2->AddElement(e1C, natoms=1); 
	
    G4Element* Li6 =new G4Element(name="Li6", symbol="6Li", z=3., a=  6.02*g/mole);
    G4Element* Li7 =new G4Element(name="Li7", symbol="7Li", z=3., a=  7.02*g/mole);
	G4Material* enLi=new G4Material("enrichLi", density=0.467*g/cm3 ,ncomponents=2);
    enLi->AddElement(Li6, 95.*perCent);
    enLi->AddElement(Li7,  5.*perCent);
	
    //G4Material* tarM = G4Material::GetMaterial("G4_Li");
    //G4Material* tarM = enLi;
    
    // Option to switch on/off checking of volumes overlaps
    //
    G4bool checkOverlaps = true;

    // geometries --------------------------------------------------------------
    // experimental hall (world volume)
    G4VSolid* worldSolid = new G4Box("worldBox",500.*mm/2, 500.*mm/2, 500.*mm/2);
    G4LogicalVolume* worldLogical = new G4LogicalVolume(worldSolid,air,"worldLogical");
    G4VPhysicalVolume* worldPhysical = new G4PVPlacement(0,G4ThreeVector(),worldLogical,"worldPhysical",0, false,0,checkOverlaps);
    
    //// target
    G4Tubs* targetSolid = new G4Tubs("targetSolid", 0, 20*mm, 2*mm, 0, 360*deg);
//    G4LogicalVolume* targetLogical = new G4LogicalVolume(targetSolid, enLi,"targetLogical");
    G4LogicalVolume* targetLogical = new G4LogicalVolume(targetSolid, CH2,"targetLogical");
    new G4PVPlacement(0,G4ThreeVector(0., 0., -150*mm),targetLogical,"targetPhysical",worldLogical, false,0,checkOverlaps);

    // hodoscopes 
    G4VSolid* hodoscope1Solid 
      = new G4Box("hodoscope1Box",200.*mm/2,20.*mm/2, 1*mm/2);
    fHodoscope1Logical
      = new G4LogicalVolume(hodoscope1Solid,scintillator,"hodoscope1Logical");
    for (G4int i=0;i<9;i++)
    {
        G4double y1 = (i-4)*21.*mm;
        new G4PVPlacement(0,G4ThreeVector(0., y1,100*mm),fHodoscope1Logical,
                          "hodoscope1Physical", worldLogical, 
                          false,i,checkOverlaps);
    }

    G4VSolid* hodoscope2Solid
      = new G4Box("hodoscope2Box",20.*mm/2,200.*mm/2, 5*mm/2);
    fHodoscope2Logical
      = new G4LogicalVolume(hodoscope2Solid,scintillator,"hodoscope2Logical");
    for (G4int i=0;i<9;i++)
    {
        G4double x1 = (i-4)*21.*mm;
        new G4PVPlacement(0,G4ThreeVector(x1, 0.,150*mm),fHodoscope2Logical,
                          "hodoscope2Physical", worldLogical,
                          false,i,checkOverlaps);
    }    
    // visualization attributes ------------------------------------------------
    
    G4VisAttributes* visAttributes = new G4VisAttributes(G4Colour(1.0,1.0,1.0));
    visAttributes->SetVisibility(false);
    worldLogical->SetVisAttributes(visAttributes);
    fVisAttributes.push_back(visAttributes);
    

    visAttributes = new G4VisAttributes(G4Colour(0.8888,0.0,0.0));
    fHodoscope1Logical->SetVisAttributes(visAttributes);
    fVisAttributes.push_back(visAttributes);
    
    visAttributes = new G4VisAttributes(G4Colour(0.8888,0.0,0.9));
    fHodoscope2Logical->SetVisAttributes(visAttributes);
    fVisAttributes.push_back(visAttributes);

    // return the world physical volume ----------------------------------------
    
    return worldPhysical;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B5DetectorConstruction::ConstructSDandField()
{
    // sensitive detectors -----------------------------------------------------
    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    G4String SDname;
    
    G4VSensitiveDetector* hodoscope1 
      = new B5HodoscopeSD(SDname="/hodoscope1");
    SDman->AddNewDetector(hodoscope1);
    fHodoscope1Logical->SetSensitiveDetector(hodoscope1);

    G4VSensitiveDetector* hodoscope2 
      = new B5HodoscopeSD(SDname="/hodoscope2");
    SDman->AddNewDetector(hodoscope2);
    fHodoscope2Logical->SetSensitiveDetector(hodoscope2);
    

}    

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B5DetectorConstruction::ConstructMaterials()
{
    G4NistManager* nistManager = G4NistManager::Instance();

    // Air 
    nistManager->FindOrBuildMaterial("G4_AIR");
    
    G4double density = 1e-10*g/cm3; 
    G4double temperature = 273*kelvin;
    G4double pressure = 1e-6*bar;
    nistManager->BuildMaterialWithNewDensity("B5_AIR","G4_AIR",density, temperature, pressure);
  
    // Argon gas
    nistManager->FindOrBuildMaterial("G4_Ar");
    // With a density different from the one defined in NIST
    // G4double density = 1.782e-03*g/cm3; 
    // nistManager->BuildMaterialWithNewDensity("B5_Ar","G4_Ar",density);
    // !! cases segmentation fault

    // Scintillator
    // (PolyVinylToluene, C_9H_10)
    nistManager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    
    // CsI
    nistManager->FindOrBuildMaterial("G4_CESIUM_IODIDE");
    
    // Lead
    nistManager->FindOrBuildMaterial("G4_Pb");
    
    // Li
    nistManager->FindOrBuildMaterial("G4_Li");
	
	//G4double density;
    //G4int ncomponents;
    //G4double fractionmass;
    std::vector<G4int> natoms;
    std::vector<G4double> fractionMass;
    std::vector<G4String> elements;

	// CH2
	elements.push_back("C");     natoms.push_back(1);
    elements.push_back("H");     natoms.push_back(2);
    density = 0.79867*g/cm3;
	nistManager->ConstructNewMaterial("CH2", elements, natoms, density);
    
	// enriched Li6
	elements.clear(); natoms.clear();
	
	G4Isotope* Li6 = new G4Isotope("Li6",3,6,6.015*g/mole);
	G4Isotope* Li7 = new G4Isotope("Li7",3,7,7.015*g/mole);
	G4Element* enrichLi  = new G4Element("enriched Lithium","enLi",2);
	enrichLi->AddIsotope(Li6,0.95*perCent);
	enrichLi->AddIsotope(Li7,0.05*perCent);

	nistManager->FindOrBuildMaterial("enLi");
	
    // Vacuum "Galactic"
    // nistManager->FindOrBuildMaterial("G4_Galactic");

    G4cout << G4endl << "The materials defined are : " << G4endl << G4endl;
    G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}



