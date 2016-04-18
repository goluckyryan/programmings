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
//
//
// $Id$
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "PhysicsList.hh"
#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"

#include "G4SystemOfUnits.hh"
#include "G4Scintillation.hh"

#include "G4IonConstructor.hh"
#include "G4UAtomicDeexcitation.hh"
#include "G4LossTableManager.hh"

#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4EmExtraPhysics.hh"
//#include "G4IonInclAblaPhysics.hh"
#include "G4IonBinaryCascadePhysics.hh"
#include "G4QStoppingPhysics.hh"
#include "HadronPhysicsQGSP_INCLXX.hh"
#include "HadronPhysicsQGSP_BIC_HP.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronElasticPhysicsHP.hh"
#include "G4NeutronTrackingCut.hh"

#include "G4RadioactiveDecayPhysics.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysicsList::PhysicsList()
: G4VModularPhysicsList()
{
  defaultCutValue = 1.0*mm;
  SetVerboseLevel(1);

  G4Scintillation* theScintiProcess = new G4Scintillation("Scintillation");
  theScintiProcess->SetTrackSecondariesFirst(true);
  theScintiProcess->SetScintillationYieldFactor(1.0);

  // EM Physics
  RegisterPhysics( new G4EmStandardPhysics() );
  //RegisterPhysics( new G4EmStandardPhysics_option3() );

  //  // Synchroton Radiation & GN Physics
  RegisterPhysics( new G4EmExtraPhysics() );

  //  // Decays
  RegisterPhysics( new G4DecayPhysics() );

  //  // Hadron Elastic scattering
  //  RegisterPhysics( new G4HadronElasticPhysics() );
  RegisterPhysics( new G4HadronElasticPhysicsHP() );

  //  // Hadron Physics
  RegisterPhysics( new HadronPhysicsQGSP_INCLXX());
  //RegisterPhysics( new HadronPhysicsQGSP_BIC_HP());

  //  // Stopping Physics
  RegisterPhysics( new G4QStoppingPhysics() );

  //  // Ion Physics
  //  RegisterPhysics( new G4IonInclAblaPhysics());
  RegisterPhysics( new G4IonBinaryCascadePhysics());

  // Radioactive decay
  RegisterPhysics( new G4RadioactiveDecayPhysics());

  //AddStepMax();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysicsList::~PhysicsList()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/*
void PhysicsList::ConstructParticle()
{
  // pseudo-particles
  //G4Geantino::GeantinoDefinition();
  
  // gamma
  G4Gamma::GammaDefinition();

  // leptons
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();

  G4NeutrinoE::NeutrinoEDefinition();
  G4AntiNeutrinoE::AntiNeutrinoEDefinition();
  
  // baryons
  G4Proton::ProtonDefinition();
  G4Neutron::NeutronDefinition();  

  // ions
  //G4IonConstructor iConstructor;
  //iConstructor.ConstructParticle();  
}
*/

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/*
#include "G4StepLimiter.hh"
#include "G4UserSpecialCuts.hh"

void PhysicsList::AddStepMax()
{
  // Step limitation seen as a process
  G4StepLimiter* stepLimiter = new G4StepLimiter();
  ////G4UserSpecialCuts* userCuts = new G4UserSpecialCuts();
  
  theParticleIterator->reset();
  while ((*theParticleIterator)()){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();

    if (particle->GetPDGCharge() != 0.0)
      {
	pmanager ->AddDiscreteProcess(stepLimiter);
	////pmanager ->AddDiscreteProcess(userCuts);
      }
  }
}
*/

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void PhysicsList::SetCuts()
{
  /*
  if (verboseLevel >0){
    G4cout << "PhysicsList::SetCuts:";
    G4cout << "CutLength : " << defaultCutValue/mm << " (mm)" << G4endl;
  }
  */
     
  // set cut values for gamma at first and for e- second and next for e+,
  // because some processes for e+/e- need cut values for gamma 
  SetCutsWithDefault();

  /*
  SetCutValue(defaultCutValue, "gamma");
  SetCutValue(defaultCutValue, "e-");
  SetCutValue(defaultCutValue, "e+");
  SetCutValue(0.0001*mm, "triton");
  SetCutValue(0.0001*mm, "proton");
  SetCutValue(0.0001*mm, "alpha");
  */

  //G4VUserPhysicsList::SetCutsWithDefault method sets 
  //the default cut value for all particle types 
  //
  /*
    SetCutsWithDefault();
  if (verboseLevel>0) DumpCutValuesTable();
  */
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......




