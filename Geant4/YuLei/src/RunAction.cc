//
/// \file electromagnetic/TestEm4/src/RunAction.cc
/// \brief Implementation of the RunAction class
//
// $Id$
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#define G4NTUPLE
#include "RunAction.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

#include "PrimaryGeneratorAction.hh"
#include "G4UnitsTable.hh"
#include "G4PhysicalConstants.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
{
  // Create analysis manager
  // The choice of analysis technology is done via selection of a namespace
  //
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // Create directories 
  //analysisManager->SetHistoDirectoryName("histo");
  //analysisManager->SetNtupleDirectoryName("ntuple");
  
  // Open an output file
  //
  G4String fileName = "neutron";
  analysisManager->OpenFile(fileName);    
  analysisManager->SetVerboseLevel(1);
  G4String extension = analysisManager->GetFileType();
  fileName = fileName + "." + extension;

  // Creating histograms
  //
  analysisManager->SetFirstHistoId(1);  

  analysisManager->CreateH1("Hist1","energy (MeV) of neutron ",1000,0.01,100.01);
  analysisManager->CreateH1("Hist2","energy (MeV) of gamma   ",1000,0.01,100.01);
  analysisManager->CreateH1("Hist3","energy (MeV) of e+/e-   ",1000,0.01,100.01);
  analysisManager->CreateH1("Hist4","energy (MeV) of Triton  ",1000,0.01,100.01);
  analysisManager->CreateH1("Hist5","energy (MeV) of Alpha   ",1000,0.01,100.01);
  analysisManager->CreateH1("Hist6","energy (MeV) of Proton  ",1000,0.01,100.01);
  analysisManager->CreateH1("Hist7","energy (MeV) of HI      ",1000,0.01,100.01);
  analysisManager->CreateH1("Hist8","energy (MeV) of neutrino",1000,0.01,100.01);
  analysisManager->CreateH1("Hist9","energy (MeV) of Others  ",1000,0.01,100.01);
  analysisManager->CreateH1("Hist10","energy (MeV) in Scinti ",1000,0.01,100.01);
  analysisManager->CreateH1("Hist11","energy (MeV) in Active ",1000,0.01,100.01);
  analysisManager->CreateH1("Hist12","energy (MeV) in Passive",1000,0.01,100.01);
  analysisManager->CreateH1("Hist13","DecayTime (nsec) ",1000,0.,10.);
  analysisManager->CreateH1("Hist14","TotalTime (hours)",1000,0.,10.);

  analysisManager->CreateH1("Hist15","Passive/Active",200,-1.1,1.1);
  analysisManager->CreateH1("Hist16","energy (MeV) in Si     ",1000,0.01,100.01);
  analysisManager->CreateH1("Hist17","energy (MeV) in CsI    ",1000,0.01,100.01);
  analysisManager->CreateH2("Hist201","Passive/Active"
			    ,200,-1.1,1.1,200,0.01,100.01);
  analysisManager->CreateH2("Hist202","Si-CsI"
			    ,200,0.01,10.01,200,0.01,100.01);

  G4cout << "\n----> Histogram file is opened in " << fileName << G4endl;

#ifdef G4NTUPLE
  analysisManager->CreateNtuple("ND", "Edep and Time");
  char name[10];
  for(G4int i=0; i<36; i++){
    sprintf(name,"Edep%d",i+1);
    analysisManager->CreateNtupleDColumn(name);
  }
  for(G4int i=0; i<36; i++){
    sprintf(name,"Tdep%d",i+1);
    analysisManager->CreateNtupleDColumn(name);
  }

  /*
  analysisManager->CreateNtupleDColumn("Edep1");
  analysisManager->CreateNtupleDColumn("Edep2");
  analysisManager->CreateNtupleDColumn("Edep3");
  analysisManager->CreateNtupleDColumn("Edep4");
  analysisManager->CreateNtupleDColumn("Edep5");
  analysisManager->CreateNtupleDColumn("Tdep1");
  analysisManager->CreateNtupleDColumn("Tdep2");
  analysisManager->CreateNtupleDColumn("Tdep3");
  analysisManager->CreateNtupleDColumn("Tdep4");
  analysisManager->CreateNtupleDColumn("Tdep5");
  */
  analysisManager->FinishNtuple();
#endif

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  
  analysisManager->Write();
  analysisManager->CloseFile();

  delete G4AnalysisManager::Instance();    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void RunAction::BeginOfRunAction(const G4Run* aRun)
{
  G4cout << "\n ### Run " << aRun->GetRunID() << " start." << G4endl;

  // save Rndm status
  //G4RunManager::GetRunManager()->SetRandomNumberStore(true);
  CLHEP::HepRandom::showEngineStatus();

}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::ParticleCount(G4String name, G4double Ekin)
{
  fParticleCount[name]++;
  fEmean[name] += Ekin;
  //update min max
  if (fParticleCount[name] == 1) fEmin[name] = fEmax[name] = Ekin;
  if (Ekin < fEmin[name]) fEmin[name] = Ekin;
  if (Ekin > fEmax[name]) fEmax[name] = Ekin;  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::Balance(G4double Ekin, G4double Pbal)
{
  fDecayCount++;
  fEkinTot[0] += Ekin;
  //update min max  
  if (fDecayCount == 1) fEkinTot[1] = fEkinTot[2] = Ekin;
  if (Ekin < fEkinTot[1]) fEkinTot[1] = Ekin;
  if (Ekin > fEkinTot[2]) fEkinTot[2] = Ekin;
  
  fPbalance[0] += Pbal;
  //update min max   
  if (fDecayCount == 1) fPbalance[1] = fPbalance[2] = Pbal;  
  if (Pbal < fPbalance[1]) fPbalance[1] = Pbal;
  if (Pbal > fPbalance[2]) fPbalance[2] = Pbal;    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EventTiming(G4double time)
{
  fTimeCount++;  
  fEventTime[0] += time;
  if (fTimeCount == 1) fEventTime[1] = fEventTime[2] = time;  
  if (time < fEventTime[1]) fEventTime[1] = time;
  if (time > fEventTime[2]) fEventTime[2] = time;             
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void RunAction::PrimaryTiming(G4double ptime)
{
  fPrimaryTime += ptime;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...
  
void RunAction::EndOfRunAction(const G4Run* aRun)
{
  G4cout << "\n ### Run " << aRun->GetRunID() << " ended." << G4endl;

  G4int nbEvents = aRun->GetNumberOfEvent();
  if (nbEvents == 0) { return; }
 

  //G4ParticleDefinition* particle = fPrimary->GetParticleGun()
  //->GetParticleDefinition();
  //G4String partName = particle->GetParticleName();
  //G4double eprimary = fPrimary->GetParticleGun()->GetParticleEnergy();
 
  G4cout << "\n ======================== run summary ======================";  
  //G4cout << "\n The run was " << nbEvents << " " << partName << " of "
  //  << G4BestUnit(eprimary,"Energy");
  G4cout << "\n ===========================================================\n";
  G4cout << G4endl;

  G4int prec = 4, wid = prec + 2;
  G4int dfprec = G4cout.precision(prec);

  //particle count
  //
  G4cout << " Nb of generated particles: \n" << G4endl;
     
  std::map<G4String,G4int>::iterator it;               
  for (it = fParticleCount.begin(); it != fParticleCount.end(); it++) { 
    G4String name = it->first;
    G4int count   = it->second;
    G4double eMean = fEmean[name]/count;
    G4double eMin = fEmin[name], eMax = fEmax[name];    
         
    G4cout << "  " << std::setw(13) << name << ": " << std::setw(7) << count
           << "  Emean = " << std::setw(wid) << G4BestUnit(eMean, "Energy")
           << "\t( "  << G4BestUnit(eMin, "Energy")
           << " --> " << G4BestUnit(eMax, "Energy") 
           << ")" << G4endl;           
  }
 
  // show Rndm status
  CLHEP::HepRandom::showEngineStatus();         
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
