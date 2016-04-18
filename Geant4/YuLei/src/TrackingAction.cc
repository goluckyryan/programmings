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
/// \file radioactivedecay/rdecay01/src/TrackingAction.cc
/// \brief Implementation of the TrackingAction class
//
//
// $Id$
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 

#include "TrackingAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "TrackingMessenger.hh"

#include "G4Track.hh"
#include "G4ParticleTypes.hh"
#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackingAction::TrackingAction(RunAction* RA, EventAction* EA)
:fRun(RA),fEvent(EA)
{
  fullChain = false;
  fTrackMessenger = new TrackingMessenger(this);   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackingAction::~TrackingAction()
{
  delete fTrackMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackingAction::PreUserTrackingAction(const G4Track* track)
{
  G4ParticleDefinition* particle = track->GetDefinition();
  G4String name   = particle->GetParticleName();
  fCharge = particle->GetPDGCharge();
  fMass   = particle->GetPDGMass();  
    
  G4double Ekin = track->GetKineticEnergy();
  G4int ID      = track->GetTrackID();
  
  G4bool condition = false;  

  //count particles
  //
  //fRun->ParticleCount(name, Ekin);
  
  //energy spectrum
  //
  G4int ih = 0;
  if (particle == G4Neutron::Neutron()){ ih = 0;}
  else if (particle == G4Gamma::Gamma()){ ih = 1;}
  else if (particle == G4Electron::Electron()||
	   particle == G4Positron::Positron()){  ih = 2;}
  else if (particle == G4Triton::Triton()){ ih = 3;}
  else  if (particle == G4Alpha::Alpha()){ ih = 4;}
  else if (particle == G4Proton::Proton()){ ih = 5;}
  else if (fCharge > 2.){ ih = 6;}
  else if (particle == G4NeutrinoE::NeutrinoE()||
	   particle == G4AntiNeutrinoE::AntiNeutrinoE()){ ih = 7;}
  else{ ih =8; }
  //G4cout<< "TAG:"<< ih <<G4endl;

  G4double Mean = Ekin;
  //G4double Sigma = 2.59*sqrt(Ekin*63000)/63000; //LaBr3
  G4double Sigma = 2.59*sqrt(Ekin*63000)/63000; //GS20
  G4double SumGauss = G4RandGauss::shoot(Mean,Sigma);

  if (ih<=8) G4AnalysisManager::Instance()->FillH1(ih+1, SumGauss);

  //fullChain: stop ion and print decay chain
  //
  if (fCharge > 2.) {
    G4Track* tr = (G4Track*) track;
    if (fullChain) tr->SetTrackStatus(fStopButAlive);
    /*
      if (ID == 1) fEvent->AddDecayChain(name);
      else       fEvent->AddDecayChain(" ---> " + name); 
    */
  }
  
  //example of saving random number seed of this fEvent, under condition
  //
  ////condition = (ih == 3);
  if (condition) G4RunManager::GetRunManager()->rndmSaveThisEvent();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackingAction::PostUserTrackingAction(const G4Track* track)
{
  //keep only ions
  //
  if (fCharge < 3. ) return;

  G4AnalysisManager* analysis = G4AnalysisManager::Instance();
  
  //get time
  //   
  G4double time = track->GetGlobalTime();
  G4int ID = track->GetTrackID();
  if (ID == 1) fRun->PrimaryTiming(time);     //time of life of primary ion  
      
  //energy and momentum balance (from secondaries)
  //
  G4TrackVector* secondaries = fpTrackingManager->GimmeSecondaries();
  size_t nbtrk = (*secondaries).size();
  if (nbtrk) {
    //there are secondaries --> it is a decay
    //
    //force 'single' decay
    if ((!fullChain)&&(ID > 1)) G4RunManager::GetRunManager()->AbortEvent();
    //
    //balance    
    G4double EkinTot = 0.;
    G4ThreeVector Pbalance = - track->GetMomentum();
    for (size_t itr=0; itr<nbtrk; itr++) {
       G4Track* trk = (*secondaries)[itr];
       EkinTot += trk->GetKineticEnergy();
       //exclude gamma desexcitation from momentum balance
       if (trk->GetDefinition() != G4Gamma::Gamma())         
         Pbalance += trk->GetMomentum();                 
    }
    G4double Pbal = Pbalance.mag();  
    fRun->Balance(EkinTot,Pbal);  

    fRun->EventTiming(time);                     //total time of life
    //time = time/3600/1000000000/24/365;//Year
    //G4AnalysisManager::Instance()->FillH1(11, time);
  }
  
  //no secondaries --> end of chain    
  //  
  if (!nbtrk) {
    //G4cout<<"ENDofCHAIN:"<<time<<G4endl;
    fRun->EventTiming(time);                     //total time of life
    //time = time/3600/1000000000/24/365;//Year
    time = time/1000000000/3600;//Hours
    analysis->FillH1(14,time);
    //G4AnalysisManager::Instance()->FillH1(5, time);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

