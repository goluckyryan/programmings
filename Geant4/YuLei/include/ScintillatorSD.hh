#ifndef SCINTILLATORSD_HH
#define SCINTILLATORSD_HH
 
#include "G4VSensitiveDetector.hh"
#include "CalHit.hh"

class ScintillatorSD : public G4VSensitiveDetector
{
public:
  ScintillatorSD(G4String name);
  virtual ~ScintillatorSD();

  G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* );
  void Initialize(G4HCofThisEvent* HCTE);
  void EndOfEvent(G4HCofThisEvent* HCTE);

private:
  CalHitsCollection* hitsCollection;
  G4double edepbuf[100];
  G4double tdepbuf[100];
};

#endif
