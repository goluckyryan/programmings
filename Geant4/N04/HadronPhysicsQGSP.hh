#ifndef HadronPhysicsQGSP_h
#define HadronPhysicsQGSP_h 1

#include "globals.hh"
#include "G4ios.hh"

#include "G4VPhysicsConstructor.hh"
#include "G4MiscBuilder.hh"

#include "G4PiKBuilder.hh"
#include "G4LEPPiKBuilder.hh"
#include "G4QGSPPiKBuilder.hh"

#include "G4ProtonBuilder.hh"
#include "G4LEPProtonBuilder.hh"
#include "G4QGSPProtonBuilder.hh"

#include "G4NeutronBuilder.hh"
#include "G4LEPNeutronBuilder.hh"
#include "G4QGSPNeutronBuilder.hh"

class HadronPhysicsQGSP : public G4VPhysicsConstructor
{
  public: 
    HadronPhysicsQGSP(G4int verbose =1);
    HadronPhysicsQGSP(const G4String& name, G4bool quasiElastic=true);
    virtual ~HadronPhysicsQGSP();

  public: 
    virtual void ConstructParticle();
    virtual void ConstructProcess();
    
    void SetQuasiElastic(G4bool value) {QuasiElastic = value;}; 
    void SetProjectileDiffraction(G4bool value) {ProjectileDiffraction = value;}; 

  private:
    void CreateModels();
    G4NeutronBuilder * theNeutrons;
    G4LEPNeutronBuilder * theLEPNeutron;
    G4QGSPNeutronBuilder * theQGSPNeutron;
    
    G4PiKBuilder * thePiK;
    G4LEPPiKBuilder * theLEPPiK;
    G4QGSPPiKBuilder * theQGSPPiK;
    
    G4ProtonBuilder * thePro;
    G4LEPProtonBuilder * theLEPPro;
    G4QGSPProtonBuilder * theQGSPPro;    
    
    G4MiscBuilder * theMisc;
    
    G4bool QuasiElastic;
    G4bool ProjectileDiffraction;
};

#endif
