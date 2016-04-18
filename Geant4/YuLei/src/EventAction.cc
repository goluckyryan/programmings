//
/// \file electromagnetic/TestEm4/src/EventAction.cc
/// \brief Implementation of the EventAction class
//
// $Id$
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#define G4NTUPLE
#include "EventAction.hh"

#include "RunAction.hh"
#include "EventActionMessenger.hh"

#include "G4Event.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

#include "G4SDManager.hh"
#include "CalHit.hh"

#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction(RunAction* run)
:fRun(run),fDrawFlag("none"),fPrintModulo(10000),fEventMessenger(NULL)
{
  fEventMessenger = new EventActionMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{
  delete fEventMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction( const G4Event* evt)
{
 G4int evtNb = evt->GetEventID();

 //printing survey
 if (evtNb%fPrintModulo == 0) 
    G4cout << "\n---> Begin of Event: " << evtNb << G4endl;  
 
 //additional initializations   
 fTotalEnergyDeposit = 0.;
 fTotalActiveDeposit = 0.;
 fTotalPassivDeposit = 0.;
 fTotalSiDeposit = 0.;
 fTotalCsIDeposit = 0.;
 fFastTiming = DBL_MAX;

 fDecayChain = " ";
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction( const G4Event* evt)
{      
  //if (fDrawFlag != "none") 
  /*
    G4cout << " Energy deposit: " 
           << G4BestUnit(fTotalEnergyDeposit,"Energy") << G4endl;
    G4cout << " Energy deposit(Active): " 
           << G4BestUnit(fTotalActiveDeposit,"Energy") << G4endl;
    G4cout << " Energy deposit(Passive): " 
           << G4BestUnit(fTotalPassivDeposit,"Energy") << G4endl;
    G4cout << " Energy deposit(Si): " 
           << G4BestUnit(fTotalSiDeposit,"Energy") << G4endl;
    G4cout << " Energy deposit(CsI): " 
           << G4BestUnit(fTotalCsIDeposit,"Energy") << G4endl;
  */

  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  G4double Mean, Sigma, SumGauss;
  Mean = fTotalEnergyDeposit;
  Sigma = 26.*sqrt(fTotalEnergyDeposit*63000)/63000; //GSx0
  //G4double Sigma = 0.26*sqrt(fTotalEnergyDeposit*10)/10; //PWO
  SumGauss = G4RandGauss::shoot(Mean,Sigma);
  //analysisManager->FillH1(10,  SumGauss/MeV);

  G4double Mean1, Sigma1, SumGauss1;
  Mean1= fTotalActiveDeposit;
  Sigma1= 26.*sqrt(fTotalActiveDeposit*63000)/63000; //GS20
  //Sigma = 0.26*sqrt(fTotalActiveDeposit*10)/10; //PWO
  SumGauss1= G4RandGauss::shoot(Mean1,Sigma1);
  analysisManager->FillH1(11, SumGauss1/MeV);

  G4double Mean2, Sigma2, SumGauss2;
  Mean2= fTotalPassivDeposit;
  Sigma2= 26.*sqrt(fTotalPassivDeposit*63000)/63000; //GS10
  SumGauss2= G4RandGauss::shoot(Mean2,Sigma2);
  analysisManager->FillH1(12, SumGauss2/MeV);

  analysisManager->FillH1(10, (SumGauss1+SumGauss2)/MeV);
  analysisManager->FillH1(13, fFastTiming);

  G4double Mean3, Sigma3, SumGauss3;
  Mean3= fTotalSiDeposit;
  Sigma3= 26.*sqrt(fTotalSiDeposit*63000)/63000; //
  SumGauss3= G4RandGauss::shoot(Mean3,Sigma3);
  analysisManager->FillH1(16, SumGauss3/MeV);

  G4double Mean4, Sigma4, SumGauss4;
  Mean4= fTotalCsIDeposit;
  Sigma4= 26.*sqrt(fTotalCsIDeposit*63000)/63000; //
  SumGauss4= G4RandGauss::shoot(Mean4,Sigma4);
  analysisManager->FillH1(17, SumGauss4/MeV);

  analysisManager->FillH2(2,SumGauss3/MeV,SumGauss4/MeV);
  /*
  G4cout<<fTotalSiDeposit<<G4endl;
  G4cout<<fTotalCsIDeposit<<G4endl;
  G4cout<<fTotalEnergyDeposit<<G4endl;
  */

  if(SumGauss1+SumGauss2>0){
    analysisManager->FillH1(15,(SumGauss1-SumGauss2)
			    /(SumGauss1+SumGauss2));
    analysisManager->FillH2(1,(SumGauss1-SumGauss2)
			    /(SumGauss1+SumGauss2)
			    ,SumGauss1+SumGauss2);
  //G4cout<<"Corr:"<<fTotalActiveDeposit/MeV<<":"<<fTotalPassivDeposit/MeV<<G4endl;
  }

  //Get Informatin of SD

  G4SDManager* SDManager= G4SDManager::GetSDMpointer();

  // get "Hit Collection of This Event"
  G4HCofThisEvent* HCTE= evt-> GetHCofThisEvent();
  if(! HCTE) return;

  // get a hit collection
  static G4int idcal= -1;
  if(idcal<0)  idcal= SDManager-> GetCollectionID("scintillator");
  CalHitsCollection* hccal= (CalHitsCollection*)HCTE-> GetHC(idcal);
  if (!hccal) return; // no hit collection

  // get hits
  G4double energy[100];
  G4double timing[100];
  for(G4int i=0; i<100; i++) energy[i]=0.0;
  for(G4int i=0; i<100; i++) timing[i]=0.0;

  G4int nhits= hccal-> entries();
  //G4cout<<"MON::"<<nhits<<G4endl;
  for(G4int idx=0; idx< nhits; idx++) {
    G4int ich= (*hccal)[idx]-> GetID();
    G4double edep= (*hccal)[idx]-> GetEdep();
    G4double tdep= (*hccal)[idx]-> GetTdep();

    energy[ich]= edep;
    timing[ich]= tdep;

    /*
    // fill a histogram
    TH1D* hist_shower= (TH1D*)gROOT-> FindObject("shower");
    hist_shower-> Fill(ich, edep/MeV);
    */
    //G4cout<<"EVENT@"<<idx<<":"<<ich<<":"<<edep<<G4endl;
  }

  #ifdef G4NTUPLE
  /*
  G4cout<<"MON"<<energy[0]<<":"<<energy[1]<<":"
	<<energy[2]<<":"<<energy[3]<<":"<<energy[4]<<G4endl;
  */

  //for(G4int i=0; i<100; i++){
  for(G4int i=0; i<36; i++){
    analysisManager->FillNtupleDColumn(   i, energy[i]);
    analysisManager->FillNtupleDColumn(i+36, timing[i]);
  }
  analysisManager->AddNtupleRow();  
  #endif

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


