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
// $Id: B5EventAction.cc 94486 2015-11-19 08:33:37Z gcosmo $
//
/// \file B5EventAction.cc
/// \brief Implementation of the B5EventAction class

#include "B5EventAction.hh"
#include "B5HodoscopeHit.hh"
#include "B5Analysis.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B5EventAction::B5EventAction()
: G4UserEventAction(), 
  fHHC1ID(-1),
  fHHC2ID(-1)
{
  // set printing per each event
  G4RunManager::GetRunManager()->SetPrintProgress(1);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B5EventAction::~B5EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B5EventAction::BeginOfEventAction(const G4Event*)
{
    if (fHHC1ID==-1) {
      G4SDManager* sdManager = G4SDManager::GetSDMpointer();
      fHHC1ID = sdManager->GetCollectionID("hodoscope1/hodoscopeColl");
      fHHC2ID = sdManager->GetCollectionID("hodoscope2/hodoscopeColl");

    }
}     

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B5EventAction::EndOfEventAction(const G4Event* event)
{
    G4HCofThisEvent* hce = event->GetHCofThisEvent();
    if (!hce) 
    {
        G4ExceptionDescription msg;
        msg << "No hits collection of this event found." << G4endl; 
        G4Exception("B5EventAction::EndOfEventAction()",
                    "B5Code001", JustWarning, msg);
        return;
    }   


    // Get hits collections 
    B5HodoscopeHitsCollection* hHC1 
      = static_cast<B5HodoscopeHitsCollection*>(hce->GetHC(fHHC1ID));
      
    B5HodoscopeHitsCollection* hHC2 
      = static_cast<B5HodoscopeHitsCollection*>(hce->GetHC(fHHC2ID));
      

    if ( (!hHC1) || (!hHC2) ) 
    {
        G4ExceptionDescription msg;
        msg << "Some of hits collections of this event not found." << G4endl; 
        G4Exception("B5EventAction::EndOfEventAction()",
                    "B5Code001", JustWarning, msg);
        return;
    }   
    
    //
    // Fill histograms & ntuple
    // 
    
    // Get analysis manager
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
 
    // Fill histograms
 
    G4int n_hit = hHC1->entries();
    for (G4int i=0;i<n_hit;i++)
    {
       analysisManager->FillH2(0, (*hHC1)[i]->GetEnergy(), (*hHC1)[i]->GetTime());
    }
    
    // Fill ntuple

    G4ThreeVector primary3V = event->GetPrimaryVertex(0)->GetPosition();
    G4double x = primary3V.getX();
    G4double y = primary3V.getY();
    analysisManager->FillNtupleDColumn(0,x);
    analysisManager->FillNtupleDColumn(1,y);
    
    G4PrimaryParticle* primary = event->GetPrimaryVertex(0)->GetPrimary(0);
    G4double momt = (primary->GetMomentum()).getR();
    G4double mass = primary->GetMass();
    G4double energy = sqrt(mass*mass+momt*momt)-mass;
    //printf("%f \n", momt);
    analysisManager->FillNtupleDColumn(2, energy);
    
    // Hodo 1
//    std::vector<double> vec;

    for (G4int i=0;i<hHC1->entries();i++)
    {
      analysisManager->FillNtupleDColumn(3,(*hHC1)[i]->GetID());

//      vec.push_back((*hHC1)[i]->GetID());
      analysisManager->FillNtupleDColumn(4,(*hHC1)[i]->GetTime());
      analysisManager->FillNtupleDColumn(5,(*hHC1)[i]->GetEnergy());
      if( (*hHC1)[i]->GetID() !=0) break; // only for the first hit
    }

//      analysisManager->FillNtupleDColumn(3, vec);
    
    for (G4int i=0;i<hHC2->entries();i++)
    {
      analysisManager->FillNtupleDColumn(6,(*hHC2)[i]->GetID());
      analysisManager->FillNtupleDColumn(7,(*hHC2)[i]->GetTime());
      analysisManager->FillNtupleDColumn(8,(*hHC2)[i]->GetEnergy());   
      if( (*hHC2)[i]->GetID() !=0) break;
    }
      
    analysisManager->AddNtupleRow(); 
    
    //
    // Print diagnostics
    // 
    
    G4int printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
    if ( printModulo==0 || event->GetEventID() % printModulo != 0) return;
    
    
    //G4PrimaryParticle* primary = event->GetPrimaryVertex(0)->GetPrimary(0);
    G4cout << G4endl
           << ">>> Event " << event->GetEventID() << " >>> Simulation truth : "
           << primary->GetG4code()->GetParticleName()
           << " " << primary3V << ", " << energy << " MeV" << G4endl;
    
    printf(" %f, %f %f\n", mass, momt, energy);
    
    // Hodoscope 1
    n_hit = hHC1->entries();
    G4cout << "Hodoscope 1 has " << n_hit << " hits." << G4endl;
    for (G4int i=0;i<n_hit;i++)
    {
        B5HodoscopeHit* hit = (*hHC1)[i];
        hit->Print();
    }

    // Hodoscope 2
    n_hit = hHC2->entries();
    G4cout << "Hodoscope 2 has " << n_hit << " hits." << G4endl;
    for (G4int i=0;i<n_hit;i++)
    {
        B5HodoscopeHit* hit = (*hHC2)[i];
        hit->Print();
    }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
