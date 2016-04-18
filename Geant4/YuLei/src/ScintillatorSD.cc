#include "ScintillatorSD.hh"

#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4VProcess.hh"
#include "G4ParticleDefinition.hh"
#include "G4PrimaryParticle.hh"

#include "DetectorConstruction.hh"

//ScintillatorSD::ScintillatorSD(G4String name) : G4VSensitiveDetector(name)
ScintillatorSD::ScintillatorSD(G4String name) : G4VSensitiveDetector(name)
{
  collectionName.insert("scintillator");
}

ScintillatorSD::~ScintillatorSD()
{;}

void ScintillatorSD::Initialize(G4HCofThisEvent* HCTE)
{
  // create hit collection(s)
  hitsCollection= new CalHitsCollection(SensitiveDetectorName,
                                        collectionName[0]); 
  
  // push H.C. to "Hit Collection of This Event"
  G4int hcid= GetCollectionID(0);
  HCTE-> AddHitsCollection(hcid, hitsCollection);

  // clear energy deposit buffer
  for (G4int i=0; i<100; i++) edepbuf[i]=0.;
  for (G4int i=0; i<100; i++) tdepbuf[i]=0.;
}

G4bool ScintillatorSD::ProcessHits(G4Step* aStep, G4TouchableHistory* )
{
  G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
  G4StepPoint* postStepPoint = aStep->GetPostStepPoint();

  const G4DynamicParticle* dynamicParticle 
    = aStep->GetTrack()->GetDynamicParticle();
  const G4ParticleDefinition* particleDefinition 
    = aStep->GetTrack()->GetParticleDefinition();
  const G4VProcess* postProcess = postStepPoint->GetProcessDefinedStep();

  G4double hitTime = preStepPoint->GetGlobalTime();
  G4double hitEnergyDeposit = aStep->GetTotalEnergyDeposit();
  /*
  Double_t hitTime = preStepPoint->GetGlobalTime();
  Double_t hitEnergyDeposit = aStep->GetTotalEnergyDeposit();
  Double_t hitKineticEnergy = preStepPoint->GetKineticEnergy();
  TVector3 hitPosition(preStepPoint->GetPosition().x(),
		       preStepPoint->GetPosition().y(),
		       preStepPoint->GetPosition().z());
  TVector3 hitMomentum(preStepPoint->GetMomentum().x(),
		       preStepPoint->GetMomentum().y(),
		       preStepPoint->GetMomentum().z());

  G4int primaryParticleID = 0;  
  // particle ID needs to simulate more than 1 particle injection, but not yet
  G4int pdgCode = dynamicParticle->GetPDGcode();

  TString particleName(particleDefinition->GetParticleName().data());
  TString processName;
  if(postProcess) processName = postProcess->GetProcessName().data();
  */

  G4TouchableHistory* theTouchable = 
    (G4TouchableHistory*)(preStepPoint->GetTouchable());


  G4int copyNo = theTouchable->GetVolume()->GetCopyNo();
  G4int motherCopyNo = theTouchable->GetVolume(1)->GetCopyNo();
  G4int grandMotherCopyNo = theTouchable->GetVolume(2)->GetCopyNo();

  if(hitEnergyDeposit>0){
    if(edepbuf[copyNo]<=0.)
      tdepbuf[copyNo] = hitTime;
    edepbuf[copyNo] += hitEnergyDeposit;
    //G4cout << "SD:"<<copyNo<<":" << hitTime<<":"<<hitEnergyDeposit<<G4endl;
  }


  //std::vector<Int_t> moduleID;
  for(G4int i=0; i<theTouchable->GetHistoryDepth(); ++i){
    G4int depth = i;//0:self, 1:mother, 2:grandmother, ....
  }

  return true;
}

void ScintillatorSD::EndOfEvent(G4HCofThisEvent* /*HCTE*/)
{
  // make hits and push them to "Hit Coleltion"
  for (G4int id=0; id< 100; id++) {
    if(edepbuf[id] > 0. ) {
      CalHit* ahit= new CalHit(id, edepbuf[id], tdepbuf[id]);
      hitsCollection-> insert(ahit);
    }
  }
}
