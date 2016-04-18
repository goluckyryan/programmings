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
/// \file electromagnetic/TestEm4/src/SteppingAction.cc
/// \brief Implementation of the SteppingAction class
//
//
// $Id$
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "DetectorConstruction.hh"
#include "SteppingAction.hh"
#include "EventAction.hh"
#include "G4SteppingManager.hh"
#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(DetectorConstruction* DetCons
			       ,EventAction* EvAct)
 :detector(DetCons), fEventAction(EvAct)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//#include "G4Scintillation.hh"

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{
  // get volume of the current step
  G4VPhysicalVolume* volume
    = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();

  /*
  const G4Material* aMaterial = aTrack.GetMaterial();
  G4MaterialTable* aMaterial_PropertiesTable =
    aMaterial->GetMaterialPropertiesTable();
  G4double ScintillationYield = 0.;
  ScintillationYield = 
    aMaterialPropertiesTable->GetConstProperty("SCINTILLATIONYIELD")
  
  */

  const G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
  G4double kE = preStepPoint->GetKineticEnergy();
  G4ParticleDefinition* pd = aStep->GetTrack()->GetDefinition();
  G4String particlename = pd->GetParticleName();

  G4double EdepStep = aStep->GetTotalEnergyDeposit();
  G4double TimeFast = aStep->GetPreStepPoint()->GetGlobalTime();

  //G4cout<<particlename<<":"<<kE<<":"<<EdepStep<<G4endl;

  //G4double ActStep, PasStep;
  G4double TmpStep, TmpTime, aE;
  //G4double EdepstMean = aStep->GetTotalEnergyDeposit();
    
  //if (EdepStep > 0.&& volume == detector->GetScinti()){
  //if(TimeFast>200&&TimeFast<10000)//for Isomer
  //if (EdepStep > 0.&&( volume == detector->GetAct()||
  //volume == detector->GetPas())){
  if (EdepStep > 0.&&( volume == detector->GetAct()||
		       volume == detector->GetPas()||
		       volume == detector->GetSil()||
		       volume == detector->GetCsI1()||
		       volume == detector->GetCsI2())){
    fEventAction->addEdep(EdepStep);
    fEventAction->convTime(TimeFast);
    //G4cout<<"Energy:"<<EdepStep<<G4endl;
    //G4cout<<"Timing:"<<TimeFast<<G4endl;
    
    preStepPoint = aStep->GetPreStepPoint();
    kE = preStepPoint->GetKineticEnergy();
    pd = aStep->GetTrack()->GetDefinition();
    particlename = pd->GetParticleName();
    TmpStep= aStep->GetTotalEnergyDeposit();
    TmpTime= aStep->GetPreStepPoint()->GetGlobalTime();
    aE=kE-TmpStep;
    
    if(1){//ON
      //G4cout<<particlename<<G4endl;
    if(particlename == "neutron"||particlename == "gamma"){
      //G4cout<<"Neutral"<<G4endl;
    }
    else if(particlename == "e-"||particlename == "e+"){
      //G4cout<<"No Quence"<<G4endl;
    }
    else if(particlename == "proton"|| particlename == "deuteron"
	    ||particlename == "triton"){
      //G4cout<<"Quence:Z=1"<<G4endl;
      TmpStep=(0.95*kE-8.0*(1-exp(-0.1*pow(kE,0.9))))
	-(0.95*aE-8.0*(1-exp(-0.1*pow(aE,0.9))));
    }
    else if(particlename == "alpha"||particlename == "He3"){
      //G4cout<<"Quence:Z=2"<<G4endl;
      TmpStep=(0.41*kE-5.9*(1-exp(-0.065*pow(kE,1.01))))
	-(0.41*aE-5.9*(1-exp(-0.065*pow(aE,1.01))));
    }
    else {
      //G4cout<<"Quence:Z>3"<<G4endl;
      TmpStep=(0.29*kE-37.492*(1-exp(-0.01*pow(kE,0.874))))
	-(0.29*aE-37.492*(1-exp(-0.01*pow(aE,0.874))));
    }
    }
    /* sandwich calrimeter*/
    if (volume == detector->GetAct()){
      fEventAction->addAdep(TmpStep);
      //G4cout<<"Active:"<<TmpStep<<G4endl;
    }
    if (volume == detector->GetPas()){
      fEventAction->addPdep(TmpStep);
      //G4cout<<"Passive:"<<TmpStep<<G4endl;
    }
    if (volume == detector->GetAct()||volume == detector->GetPas())
      fEventAction->convTime1(TmpTime);

    /* Telescope */
    if (volume == detector->GetSil()){
      fEventAction->addSdep(TmpStep);
      //G4cout<<"Si:"<<TmpStep<<G4endl;
    }
    if (volume == detector->GetCsI1()||
	volume == detector->GetCsI2()){
      fEventAction->addCdep(TmpStep);
      //G4cout<<"CsI:"<<TmpStep<<G4endl;
    }
    if (volume == detector->GetCsI1()||volume == detector->GetCsI2())
      fEventAction->convTime2(TmpTime);
  }

  /*
  G4double MeanNumberOfPhotons;
  MeanNumberOfPhotons = ScintillationYield * EdepStep;
  if(MeanNumberOfPhotons>10){
    G4double sigma = ResolutionScale * std::sqrt(MeanNumberOfPhotons);
    NumPhotons = G4int(G4RandGauss::shoot(MeanNumberOfPhotons,sigma)+0.5);
  }else{
    NumPhotons = G4int(G4Poisson(MeanNumberOfPhotons));
  }
  */
  
 //example of saving random number seed of this event, under condition
 //// if (condition) G4RunManager::GetRunManager()->rndmSaveThisEvent();  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


