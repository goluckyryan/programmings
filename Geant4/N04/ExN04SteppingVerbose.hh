class ExN04SteppingVerbose;

#ifndef ExN04SteppingVerbose_h
#define ExN04SteppingVerbose_h 1

#include "G4SteppingVerbose.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class ExN04SteppingVerbose : public G4SteppingVerbose 
{
 public:
   
  ExN04SteppingVerbose();
 ~ExN04SteppingVerbose();

  void StepInfo();
  void TrackingStarted();

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
