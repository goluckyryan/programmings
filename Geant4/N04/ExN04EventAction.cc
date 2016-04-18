#include "ExN04EventAction.hh"

#include "ExN04TrackerHit.hh"
#include "ExN04CalorimeterHit.hh"
#include "ExN04MuonHit.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4SDManager.hh"
#include "G4UImanager.hh"
#include "G4ios.hh"

ExN04EventAction::ExN04EventAction()
{
  trackerCollID = -1;
  calorimeterCollID = -1;
  muonCollID = -1;
}

ExN04EventAction::~ExN04EventAction()
{;}

void ExN04EventAction::BeginOfEventAction(const G4Event*)
{
  G4SDManager * SDman = G4SDManager::GetSDMpointer();
  if(trackerCollID<0||calorimeterCollID<0||muonCollID<0)
  {
    G4String colNam;
    trackerCollID = SDman->GetCollectionID(colNam="trackerCollection");
    calorimeterCollID = SDman->GetCollectionID(colNam="calCollection");
    muonCollID = SDman->GetCollectionID(colNam="muonCollection");
  }
}

void ExN04EventAction::EndOfEventAction(const G4Event* evt)
{
  G4cout << ">>> Event " << evt->GetEventID() << G4endl;
  
  if(trackerCollID<0||calorimeterCollID<0||muonCollID<0) return;

  G4HCofThisEvent * HCE = evt->GetHCofThisEvent();
  ExN04TrackerHitsCollection* THC = 0;
  ExN04CalorimeterHitsCollection* CHC = 0;
  ExN04MuonHitsCollection* MHC = 0;
  if(HCE)
  {
    THC = (ExN04TrackerHitsCollection*)(HCE->GetHC(trackerCollID));
    CHC = (ExN04CalorimeterHitsCollection*)(HCE->GetHC(calorimeterCollID));
    MHC = (ExN04MuonHitsCollection*)(HCE->GetHC(muonCollID));
  }

  if(THC)
  {
    int n_hit = THC->entries();
    G4cout << "     " << n_hit
         << " hits are stored in ExN04TrackerHitsCollection." << G4endl;
  }
  if(CHC)
  {
    int n_hit = CHC->entries();
    G4cout << "     " << n_hit
         << " hits are stored in ExN04CalorimeterHitsCollection." << G4endl;
    G4double totE = 0;
    for(int i=0;i<n_hit;i++)
    { totE += (*CHC)[i]->GetEdep(); }
    G4cout << "     Total energy deposition in calorimeter : "
         << totE / GeV << " (GeV)" << G4endl;
  }
  if(MHC)
  {
    int n_hit = MHC->entries();
    G4cout << "     " << n_hit
         << " hits are stored in ExN04MuonHitsCollection." << G4endl;
  }
}
