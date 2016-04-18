//
// ********************************************************************
// * License Disclaimer                                           *
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
/// \file electromagnetic/TestEm4/src/DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class
//
//
// $Id$
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Trd.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4SystemOfUnits.hh"

#include "G4UserLimits.hh"

#include "ScintillatorSD.hh"
#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  //
  // define a material from its elements.   case 1: chemical molecule
  // 
  G4double a, z, n;
  G4double density;  
  G4int ncomponents, natoms;
  G4double abundance, fractionmass;

  G4Element* Li =new G4Element("Lithium" ,"Li" ,z= 3., a=  6.94*g/mole);
  G4Element* C = new G4Element("Carbon"  ,"C" , z= 6., a= 12.01*g/mole);
  G4Element* N = new G4Element("Nitrogen","N" , z= 7., a= 14.01*g/mole);
  G4Element* O = new G4Element("Oxygen"  ,"O" , z= 8., a= 16.00*g/mole);
  G4Element* F = new G4Element("Fluorine","F" , z= 9., a= 18.99*g/mole);
  G4Element* Na= new G4Element("Sodium"  ,"Na", z=11., a= 22.99*g/mole);
  G4Element* Mg= new G4Element("Magnesium","Mg",z=12., a= 24.30*g/mole);
  G4Element* Al= new G4Element("Aluminium","Al",z=13., a= 26.98*g/mole);
  G4Element* Si= new G4Element("Silicon" ,"Si", z=14., a= 28.09*g/mole);
  G4Element* Ge= new G4Element("Germanium","Ge",z=32., a= 72.59*g/mole);
  G4Element* Br= new G4Element("Bromine" ,"Br", z=35., a= 79.90*g/mole);
  G4Element* I = new G4Element("Iodine"  ,"I" , z=53., a= 126.9*g/mole);
  G4Element* La= new G4Element("Lanthanum","La",z=57., a=138.90*g/mole);
  G4Element* Ce= new G4Element("Cerium"  ,"Ce", z=58., a=140.11*g/mole);
  G4Element* Pb= new G4Element("Lead"    ,"Pb", z=82., a=207.20*g/mole);
  G4Element* Bi= new G4Element("Bismuth" ,"Bi", z=83., a=208.98*g/mole);
 
  G4Isotope* Li6 =new G4Isotope("Li6"    , z=3., a=6., a=  6.02*g/mole);
  G4Isotope* Li7 =new G4Isotope("Li7"    , z=3., a=7., a=  7.02*g/mole);

  G4Element* enLi=new G4Element("enrichLi","enLi",ncomponents=2);
  enLi->AddIsotope(Li6, 95.*perCent);
  enLi->AddIsotope(Li7,  5.*perCent);

  G4Element* enLi2=new G4Element("enrichLi2","enLi2",ncomponents=2);
  enLi2->AddIsotope(Li6,  0.01*perCent);
  enLi2->AddIsotope(Li7, 99.99*perCent);

  

  G4Material* Alum=  new G4Material("Alum", z=13., a= 26.98*g/mole, 
				    density= 2.700*g/cm3);
  G4cout << Alum << G4endl;

  G4Material* Lead = new G4Material("Lead", density= 11.35*g/cm3, ncomponents=1);
  Lead->AddElement(Pb, fractionmass=1.0);
  G4cout << Lead << G4endl;

  G4Material* C6F6 = 
  new G4Material("FluorCarbonate", density= 1.61*g/cm3, ncomponents=2);
  C6F6->AddElement(C, natoms=6);
  C6F6->AddElement(F, natoms=6);
  
  G4cout << C6F6 << G4endl;

  //NaI
  const G4int numentriesnai = 6;
  G4double naienergies[numentriesnai]={1.2*eV,3.25*eV,3.26*eV,3.27*eV,3.28*eV,6.5*eV};
  G4double naifastcomp[numentriesnai]={ 0.0, 0., 1.0, 1.0, 0., 0.0 };
  G4double naislowcomp[numentriesnai]={ 0.0, 0., 1.0, 1.0, 0., 0.0 };
  G4double nairindices[numentriesnai]={ 1.9, 1.9, 1.9, 1.9, 1.9, 1.9 };
  G4double naiabsorptionlength[numentriesnai]={1.0*m,1.0*m,1.0*m,1.0*m,1.0*m,1.0*m};

  /*
  G4Material* NaI = 
    new G4Material("NaI", density= 3.67*g/cm3, ncomponents=2);
  NaI->AddElement(Na,natoms=1);
  NaI->AddElement(I, natoms=1);

  G4MaterialPropertiesTable* NaI_tb = new G4MaterialPropertiesTable();
  NaI_tb->AddProperty("FASTCOMPONENT",naienergies, naifastcomp, numentriesnai);
  NaI_tb->AddProperty("SLOWCOMPONENT",naienergies, naislowcomp, numentriesnai);
  NaI_tb->AddProperty("RINDEX",       naienergies, nairindices, numentriesnai);
  NaI_tb->AddProperty("ABSLENGTH",    naienergies, naiabsorptionlength, numentriesnai);
  NaI_tb->AddConstProperty("SCINTILLATIONYIELD",38.0/keV); 
  NaI_tb->AddConstProperty("RESOLUTIONSCALE",1.0);
  NaI_tb->AddConstProperty("FASTTIMECONSTANT",250.0*ns); 
  NaI_tb->AddConstProperty("SLOWTIMECONSTANT",250.0*ns); 
  NaI_tb->AddConstProperty("SLOWSCINTILLATIONRISETIME",27.0*ns); 
  NaI_tb->AddConstProperty("YIELDRATIO",0.5);
  NaI->SetMaterialPropertiesTable(NaI_tb);
  G4cout << NaI << G4endl;
  */

  //CsI
  /*
  G4Material* CsI = 
    new G4Material("CsI", density= 4.51*g/cm3, ncomponents=2);
  CsI->AddElement(Cs,natoms=1);
  CsI->AddElement(I, natoms=1);
  */

  //BGO
  /*
  G4Material* BGO = 
    new G4Material("BGO", density= 7.10*g/cm3, ncomponents=3);
  BGO->AddElement(O, natoms=12);
  BGO->AddElement(Ge, natoms=3);
  BGO->AddElement(Bi, natoms=4);
  G4cout << BGO << G4endl;
  */

  //LaBr
  const G4int numentrieslabr = 6;
  G4double labrenergies[numentrieslabr]={1.2*eV,3.25*eV,3.26*eV,3.27*eV,3.28*eV,6.5*eV};
  G4double labrfastcomp[numentrieslabr]={ 0.0, 0., 1.0, 1.0, 0., 0.0 };
  G4double labrrindices[numentrieslabr]={ 1.9, 1.9, 1.9, 1.9, 1.9, 1.9 };
  G4double labrabsorptionlength[numentrieslabr]={1.0*m,1.0*m,1.0*m,1.0*m,1.0*m,1.0*m};
  G4Material* LaBr = 
  new G4Material("LaBr", density= 5.08*g/cm3, ncomponents=3);
  /*
    LaBr->AddElement(La, 36.62*perCent);
    LaBr->AddElement(Br, 63.19*perCent);
    LaBr->AddElement(Ce,  0.19*perCent);
  */
    LaBr->AddElement(La, natoms=36.62);
    LaBr->AddElement(Br, natoms=63.19);
    LaBr->AddElement(Ce, natoms= 0.19);

  G4MaterialPropertiesTable* LaBr_tb = new G4MaterialPropertiesTable();
  LaBr_tb->AddProperty("FASTCOMPONENT",labrenergies,labrfastcomp, numentrieslabr);
  LaBr_tb->AddProperty("RINDEX",       labrenergies,labrrindices, numentrieslabr);
  LaBr_tb->AddProperty("ABSLENGTH",   labrenergies,labrabsorptionlength,numentrieslabr);
  LaBr_tb->AddConstProperty("SCINTILLATIONYIELD",63.0/keV); // saint-gobain
  LaBr_tb->AddConstProperty("RESOLUTIONSCALE",100.0);
  LaBr_tb->AddConstProperty("FASTTIMECONSTANT",16.0*ns); // saint-gobain
  LaBr_tb->AddConstProperty("YIELDRATIO",1.0);
  LaBr->SetMaterialPropertiesTable(LaBr_tb);

  //G4cout<<*(G4Material::GetMaterialTable)<<G4endl;
  G4cout << LaBr << G4endl;

  //Teflon
  G4Material* Teflon = 
    new G4Material("Teflon", density= 2.20*g/cm3, ncomponents=2);
  Teflon->AddElement(C, natoms=2);
  Teflon->AddElement(F, natoms=4);

  G4cout << Teflon << G4endl;

  G4Material* Air = 
    new G4Material("Air"  , density= 1.290*mg/cm3, ncomponents=2, 
		   kStateGas, 294*kelvin, 100*pascal);
  Air->AddElement(N, fractionmass=0.7);
  Air->AddElement(O, fractionmass=0.3);
  G4cout << Air << G4endl;

  G4Material* Vacuum =
    new G4Material("Vacuum", z=1., a=1.01*g/mole,
		   density= universe_mean_density,
		   kStateGas, 2.73*kelvin, 3.e-18*pascal);
  G4cout << Vacuum << G4endl;

  G4Material* GS10 = 
  new G4Material("GS10", density= 2.44*g/cm3, ncomponents=6);
  /*
  GS10->AddElement(Li,  natoms=20.8);
  GS10->AddElement(O,   natoms=54.6);
  GS10->AddElement(Al,  natoms= 6.2);
  GS10->AddElement(Mg,  natoms= 1.7);
  GS10->AddElement(Si,  natoms=16.3);
  GS10->AddElement(Ce,  natoms= 0.4);
  */
  GS10->AddElement(Li,  natoms=208);
  GS10->AddElement(O,   natoms=546);
  GS10->AddElement(Al,  natoms= 62);
  GS10->AddElement(Mg,  natoms= 17);
  GS10->AddElement(Si,  natoms=163);
  GS10->AddElement(Ce,  natoms= 04);

  G4cout << GS10 << G4endl;

  G4Material* GS20 = 
  new G4Material("GS20", density= 2.44*g/cm3, ncomponents=6);
  /*
  GS20->AddElement(enLi,natoms=20.8);
  GS20->AddElement(O,   natoms=54.6);
  GS20->AddElement(Al,  natoms= 6.2);
  GS20->AddElement(Mg,  natoms= 1.7);
  GS20->AddElement(Si,  natoms=16.3);
  GS20->AddElement(Ce,  natoms= 0.4);
  */
  GS20->AddElement(enLi,natoms=208);
  GS20->AddElement(O,   natoms=546);
  GS20->AddElement(Al,  natoms= 62);
  GS20->AddElement(Mg,  natoms= 17);
  GS20->AddElement(Si,  natoms=163);
  GS20->AddElement(Ce,  natoms= 04);
  G4cout << GS20 << G4endl;

  G4Material* GS30 = 
  new G4Material("GS30", density= 2.44*g/cm3, ncomponents=6);
  /*
  GS30->AddElement(enLi2,natoms=20.8);
  GS30->AddElement(O,   natoms=54.6);
  GS30->AddElement(Al,  natoms= 6.2);
  GS30->AddElement(Mg,  natoms= 1.7);
  GS30->AddElement(Si,  natoms=16.3);
  GS30->AddElement(Ce,  natoms= 0.4);
  */
  GS30->AddElement(enLi2,natoms=208);
  GS30->AddElement(O,   natoms=546);
  GS30->AddElement(Al,  natoms= 62);
  GS30->AddElement(Mg,  natoms= 17);
  GS30->AddElement(Si,  natoms=163);
  GS30->AddElement(Ce,  natoms= 04);
  G4cout << GS30 << G4endl;

  G4NistManager* man = G4NistManager::Instance();
  man->SetVerbose(1);
  G4Material* Sci  = man->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
  G4cout << Sci << G4endl;

  G4Material* PWO  = man->FindOrBuildMaterial("G4_PbWO4");
  G4cout << PWO << G4endl;

  G4Material* NaI  = man->FindOrBuildMaterial("G4_SODIUM_IODIDE");
  G4cout << NaI << G4endl;

  G4Material* CsI  = man->FindOrBuildMaterial("G4_CESIUM_IODIDE");
  G4cout << CsI << G4endl;

  G4Material* BGO  = man->FindOrBuildMaterial("G4_BGO");
  G4cout << BGO << G4endl;

  G4Material* Sili = new G4Material("Sili", density= 2.33*g/cm3, ncomponents=1);
  Sili->AddElement(Si, fractionmass=1.0);
  G4cout << Sili << G4endl;

  G4Material* Mylar  = man->FindOrBuildMaterial("G4_MYLAR");
  G4cout << Mylar << G4endl;


  //     
  // World
  //  
  solidWorld = new G4Box("World",                //its name
			 20*cm, 20*cm, 28*cm);   //its size
  //10*cm, 10*cm, 10*cm);   //its size
  logicWorld = new G4LogicalVolume(solidWorld,   //its solid
				   //Air,          //its material
				   Vacuum,       //its material
				   "World");     //its name
  physiWorld = new G4PVPlacement(0,              //no rotation
				 G4ThreeVector(),//at (0,0,0)
				 logicWorld,     //its logical volume   
				 "World",        //its name
				 0,              //its mother  volume
				 false,          //no boolean operation
				 0);             //copy number
  //     
  // Scintillator
  //  
  //NbOfLayers=5;
  //LayerThickness = 1.0*cm;
  //TotalThickness = 5.0*cm;
  //NbOfLayers=10;
  //LayerThickness    = 0.6*cm;
  //RadiatorThickness = 0.3*cm;
  //TotalThickness    = 6.0*cm;
  //NbOfLayers=16;
  //LayerThickness    = 0.5*cm;
  //TotalThickness    = 8.0*cm;
  NbOfLayers=36;
  LayerThickness    = 0.2*cm;
  //RadiatorThickness = 0.3*cm;
  TotalThickness    = 7.2*cm;
  ReflectorThickness= 0.001*cm;
  //ReflectorThickness= 0.00*cm;
  
  //solidWorld1 = new G4Box("Scinti",6.0*cm, 6.0*cm, TotalThickness/2);
  solidWorld1 = new G4Box("Scinti",4.0*cm, 4.0*cm, TotalThickness/2);
  logicWorld1 = new G4LogicalVolume(solidWorld1, Vacuum, "Scinti");
  physiWorld1 = new G4PVPlacement(0, G4ThreeVector(0,0,+18*cm), logicWorld1, 
				    "Scinti", logicWorld, false, 0);
  // PWO
  //solidWorld2 = new G4Box("PWO",2.5*cm, 2.5*cm, LayerThickness/2);
  //logicWorld2 = new G4LogicalVolume(solidWorld2, PWO, "PWO");
  solidWorld2 = new G4Box("Scinti",4.0*cm, 4.0*cm, LayerThickness/2);
  ////solidWorld2 = new G4Box("Scinti",4.0*cm, 4.0*cm, LayerThickness/4);
  logicWorld2 = new G4LogicalVolume(solidWorld2, Sci, "Scinti1");
  if (NbOfLayers > 1){
    //physiWorld2 = new G4PVReplica("PWO", logicWorld2,logicWorld1,
    //physiWorld2 = new G4PVReplica("Scinti1", logicWorld2,logicWorld1,
    //kZAxis,NbOfLayers,LayerThickness);
    //G4ThreeVector target_pos(0., 0., -3.75*cm) ;
    //G4ThreeVector target_pos_shift(0., 0., 0.5*cm);
    G4ThreeVector target_pos(0., 0., -3.5*cm) ;
    G4ThreeVector target_pos_shift(0., 0., 0.2*cm);
    G4String target_name("Scinti");
    for(G4int i=0;i<36;i++){
      std::ostringstream os;
      os << target_name << i;
      physiWorld2 =new G4PVPlacement(0,  target_pos,logicWorld2, os.str(), logicWorld1, false, i);
      target_pos += target_pos_shift;
    }
  }else{
    physiWorld2 = new G4PVPlacement(0, G4ThreeVector(0,0,+18*cm),logicWorld2, 
				    //"PWO", logicWorld1, false, 0);
				    "Scinti1", logicWorld1, false, 0);
  }
  // Another Scinti sandwich
  /* 
  if(RadiatorThickness>0.){
    //solidWorld3 = new G4Box("Lead",2.5*cm, 2.5*cm, RadiatorThickness);
    solidWorld3 = new G4Box("Scinti2",4.0*cm, 4.0*cm, RadiatorThickness);
    //logicWorld3 = new G4LogicalVolume(solidWorld3, Lead, "Lead");
    logicWorld3 = new G4LogicalVolume(solidWorld3, Sci, "Scinti2");//Plastic
    physiWorld3 = new G4PVPlacement(0, G4ThreeVector(0,0,-LayerThickness/2), 
				    logicWorld3, "Scinti2", logicWorld2, false, 0);
  }
  */
  //Reflector
  if(ReflectorThickness>0.){
    solidWorld4 = new G4Box("Refl",4.0*cm, 4.0*cm, ReflectorThickness);
    logicWorld4 = new G4LogicalVolume(solidWorld4, Mylar, "Refl");//Mylar
    //physiWorld4 = new G4PVPlacement(0, G4ThreeVector(0,0,+0.0*cm), 
    physiWorld4 = new G4PVPlacement(0, G4ThreeVector(0,0,-LayerThickness/2+ReflectorThickness), 
	    ///physiWorld4 = new G4PVPlacement(0, G4ThreeVector(0,0,-LayerThickness/4), 
				    logicWorld4, "Refl", logicWorld2, false, 0);
    /*
    solidWorld4 = new G4Box("Refl",4.0*cm, 4.0*cm, ReflectorThickness/2);
    logicWorld4 = new G4LogicalVolume(solidWorld4, Sci, "Refl");
    physiWorld4 = new G4PVReplica("Refl", logicWorld4,logicWorld1,
				  kZAxis,2*NbOfLayers-1,RadiatorThickness);
    */

  }

  /*
  // Pb Plate
  solidWorld4 = new G4Box("Lead",2.5*cm, 2.5*cm, 0.5*cm);
  //solidWorld4 = new G4Box("Lead",2.5*cm, 2.5*cm, 10*cm);
  logicWorld4 = new G4LogicalVolume(solidWorld4, Lead, "Lead");
  //physiWorld4 = new G4PVPlacement(0, G4ThreeVector(0,0,-14.*cm), logicWorld4, 
  physiWorld4 = new G4PVPlacement(0, G4ThreeVector(0,0,-4.*cm), logicWorld4, 
				  "Lead", logicWorld, false, 0);
  */


  /* Si for telescope 10cmx10cmx300um*/
  /*
  solidWorld6 = new G4Box("Si",5.0*cm, 5.0*cm, 0.015*cm);
  logicWorld6 = new G4LogicalVolume(solidWorld6, Sili, "Si");
  physiWorld6 = new G4PVPlacement(0, G4ThreeVector(0,0,-10.*cm), logicWorld6, 
				  "Si", logicWorld, false, 0);
  */

  /* CsI for telescope */
  /*
  if(1){ 
    solidWorld7 = new G4Box("CsI1",5.0*cm, 5.0*cm, 1.25*cm);//2.5cm
    logicWorld7 = new G4LogicalVolume(solidWorld7, CsI, "CsI1");
    physiWorld7 = new G4PVPlacement(0, G4ThreeVector(0,0,-8.5*cm), logicWorld7, 
				    "CsI1", logicWorld, false, 0);
  }else{
    solidWorld7 = new G4Box("CsI",5.0*cm, 5.0*cm, 2.75*cm);//5.5cm
    logicWorld7 = new G4LogicalVolume(solidWorld7, CsI, "CsI");
    physiWorld7 = new G4PVPlacement(0, G4ThreeVector(0,0,-7.*cm), logicWorld7, 
				    "CsI", logicWorld, false, 0);
  }

  if(1){ 
    solidWorld8 = new G4Trd("CsI",2.5*cm, 1.4*cm, 2.5*cm, 1.4*cm, 1.5*cm);//3.0cm
    logicWorld8 = new G4LogicalVolume(solidWorld8, CsI, "CsI2");
    for(int i=0;i<4;i++){
      physiWorld8 = new G4PVPlacement(0, G4ThreeVector((-2.5+5.0*(i/2))*cm,
						       (-2.5+5.0*(i%2))*cm,-5.75*cm),
				      logicWorld8, "CsI2",
				      logicWorld, false, i);
    }
  }else{
    solidWorld8 = new G4Trd("CsI2",5.0*cm, 2.8*cm, 5.0*cm, 2.8*cm, 1.5*cm);//3.0cm
    logicWorld8 = new G4LogicalVolume(solidWorld8, CsI, "CsI2");
    physiWorld8 = new G4PVPlacement(0, G4ThreeVector(0,0,-5.75*cm), logicWorld8, 
				    "CsI2", logicWorld, false, 0);
  }
  */
  
  // add SD
  if(!fScintillatorSD){
    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    fScintillatorSD = new ScintillatorSD("/ScintillatorSD");
    SDman->AddNewDetector(fScintillatorSD);
  }
  logicWorld2->SetSensitiveDetector(fScintillatorSD);

  /*
    G4double maxStep = 0.00001*mm;
    stepLimit = new G4UserLimits(maxStep);
    logicWorld1->SetUserLimits(stepLimit);
  */

  //
  //always return the physical World
  //  
  return physiWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
