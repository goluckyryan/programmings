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
// $Id: B5RunAction.cc 74204 2013-10-01 07:04:43Z ihrivnac $
//
/// \file B5RunAction.cc
/// \brief Implementation of the B5RunAction class

#include "B5RunAction.hh"
#include "B5EventAction.hh"
#include "B5Analysis.hh"

#include "G4Run.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B5RunAction::B5RunAction(B5EventAction* eventAction)
 : G4UserRunAction(),
   fEventAction(eventAction)
{ 
  // Create analysis manager
  // The choice of analysis technology is done via selectin of a namespace
  // in B5Analysis.hh
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  G4cout << "==================Using " << analysisManager->GetType() << G4endl;

  // Default settings
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFileName("B5");

  // Book histograms, ntuple
  //
  
  // Creating 1D histograms
//  analysisManager
//    ->CreateH1("Chamber1","Drift Chamber 1 # Hits", 50, 0., 50); // h1 Id = 0
//  analysisManager
//    ->CreateH1("Chamber2","Drift Chamber 2 # Hits", 50, 0., 50); // h1 Id = 1
  
  // Creating 2D histograms
  analysisManager->CreateH2("Hodo_Et","Hodo E vs time", 50, 0., 100, 50, 0., 10.);


  // Creating ntuple
  //
  if ( fEventAction ) {
    analysisManager->CreateNtuple("B5", "Hits");
    analysisManager->CreateNtupleDColumn("x");    // column Id = 0
    analysisManager->CreateNtupleDColumn("y");    // column Id = 1
    analysisManager->CreateNtupleDColumn("z");    // column Id = 2
    analysisManager->CreateNtupleDColumn("orgE");    // column Id = 3
    
    //std::vector<double> vec;
    analysisManager->CreateNtupleDColumn("id1");    // column Id = 4
    analysisManager->CreateNtupleDColumn("t1");    // column Id = 5
    analysisManager->CreateNtupleDColumn("e1");    // column Id = 6

    analysisManager->CreateNtupleDColumn("id2");    // column Id = 7
    analysisManager->CreateNtupleDColumn("t2");    // column Id = 8
    analysisManager->CreateNtupleDColumn("e2");    // column Id = 9
    analysisManager->FinishNtuple();
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B5RunAction::~B5RunAction()
{
  delete G4AnalysisManager::Instance();  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B5RunAction::BeginOfRunAction(const G4Run* /*run*/)
{ 
  //inform the runManager to save random number seed
  //G4RunManager::GetRunManager()->SetRandomNumberStore(true);
  
  // Get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // Open an output file 
  // The default file name is set in B5RunAction::B5RunAction(),
  // it can be overwritten in a macro
  analysisManager->OpenFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B5RunAction::EndOfRunAction(const G4Run* /*run*/)
{
  // save histograms & ntuple
  //
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
