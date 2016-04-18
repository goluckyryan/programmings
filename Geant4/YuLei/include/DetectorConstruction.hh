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
/// \file electromagnetic/TestEm4/include/DetectorConstruction.hh
/// \brief Definition of the DetectorConstruction class
//
//
// $Id$
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4VSensitiveDetector.hh"
#include "globals.hh"

class G4Box;
class G4Trd;
class G4Tubs;
class G4LogicalVolume;
class G4Material;
class G4UserLimits;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
  
    DetectorConstruction();
   ~DetectorConstruction();
     
    virtual G4VPhysicalVolume* Construct();

  public:
    const G4VPhysicalVolume* GetphysiWorld() {return physiWorld;};           
    const G4VPhysicalVolume* GetScinti()   {return physiWorld1;};

    const G4VPhysicalVolume* GetAct()      {return physiWorld2;};
    const G4VPhysicalVolume* GetPas()      {return physiWorld3;};
    const G4VPhysicalVolume* GetSil()      {return physiWorld6;};
    const G4VPhysicalVolume* GetCsI1()     {return physiWorld7;};
    const G4VPhysicalVolume* GetCsI2()     {return physiWorld8;};


  private:
  G4Box*  solidWorld;
  G4LogicalVolume* logicWorld;
  G4VPhysicalVolume* physiWorld;

  G4Box*  solidWorld1;
  G4LogicalVolume* logicWorld1;
  G4VPhysicalVolume* physiWorld1;

  G4Box*  solidWorld2;
  G4LogicalVolume* logicWorld2;
  G4VPhysicalVolume* physiWorld2;

  G4Box*  solidWorld3;
  G4LogicalVolume* logicWorld3;
  G4VPhysicalVolume* physiWorld3;

  G4Box*  solidWorld4;
  G4LogicalVolume* logicWorld4;
  G4VPhysicalVolume* physiWorld4;

  G4Tubs*  solidWorld5;
  G4LogicalVolume* logicWorld5;
  G4VPhysicalVolume* physiWorld5;

  G4Box*  solidWorld6;
  G4LogicalVolume* logicWorld6;
  G4VPhysicalVolume* physiWorld6;

  G4Box*  solidWorld7;
  G4LogicalVolume* logicWorld7;
  G4VPhysicalVolume* physiWorld7;

  G4Trd*  solidWorld8;
  G4LogicalVolume* logicWorld8;
  G4VPhysicalVolume* physiWorld8;

  G4UserLimits* stepLimit;

  G4int              NbOfLayers;
  G4double           LayerThickness;
  G4double           TotalThickness;
  G4double           RadiatorThickness;
  G4double           ReflectorThickness;
  
  G4VSensitiveDetector* fScintillatorSD;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

