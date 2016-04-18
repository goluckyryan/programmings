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
// $Id: B5PrimaryGeneratorAction.cc 77781 2013-11-28 07:54:07Z gcosmo $
//
/// \file B5PrimaryGeneratorAction.cc
/// \brief Implementation of the B5PrimaryGeneratorAction class

#include "B5PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4GenericMessenger.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B5PrimaryGeneratorAction::B5PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),     
  fParticleGun(0), fMessenger(0), 
  fProton(0),
  //fPositron(0), fMuon(0), fPion(0), fKaon(0), fProton(0),
  fKineticEnergy(100.*MeV),
  fSigmaKineticEnergy(50.*MeV),
  fSigmaRadius(30.*mm),
  fRandomizePrimary(true)
{
    G4int n_particle = 1;
    fParticleGun  = new G4ParticleGun(n_particle);
    
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName;
    
    //fPositron = particleTable->FindParticle(particleName="e+");
    //fMuon = particleTable->FindParticle(particleName="mu+");
    //fPion = particleTable->FindParticle(particleName="pi+");
    //fKaon = particleTable->FindParticle(particleName="kaon+");
    fProton = particleTable->FindParticle(particleName="proton");
    
    // default particle momentum
    fParticleGun->SetParticleDefinition(fProton);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
    fParticleGun->SetParticleEnergy(fKineticEnergy);
    
    // default particle kinematics
    //fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,-150.*mm));
    //fParticleGun->SetParticleDefinition(fPositron);
    
    // define commands for this class
    DefineCommands();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B5PrimaryGeneratorAction::~B5PrimaryGeneratorAction()
{
    delete fParticleGun;
    delete fMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B5PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
    //G4ParticleDefinition* particle;
    //
    //if (fRandomizePrimary)
    //{
    //    G4int i = (int)(5.*G4UniformRand());
    //    switch(i)
    //    {
    //        case 0:
    //            particle = fPositron;
    //            break;
    //        case 1:
    //            particle = fMuon;
    //            break;
    //        case 2:
    //            particle = fPion;
    //            break;
    //        case 3:
    //            particle = fKaon;
    //            break;
    //        default:
    //            particle = fProton;
    //            break;
    //    }
    //    particle = fProton;
    //    fParticleGun->SetParticleDefinition(particle);
    //}
    //else
    //{
    //    particle = fParticleGun->GetParticleDefinition();
    //}
    
    G4double KE = fKineticEnergy + (G4UniformRand()-0.5)*fSigmaKineticEnergy;
    //G4double mass = particle->GetPDGMass();
    //G4double Ekin = std::sqrt(pp*pp+mass*mass)-mass;
    fParticleGun->SetParticleEnergy(KE);
    
    G4double radius = sqrt(2*G4UniformRand())*fSigmaRadius;
    G4double theta = G4UniformRand()*360*deg;
    fParticleGun->SetParticlePosition(G4ThreeVector(radius*cos(theta),radius*sin(theta),-200.*mm));
    
    //fParticleGun->SetParticleMomentumDirection(G4ThreeVector(std::sin(angle)*std::cos(angle2),
    //                                                         std::sin(angle)*std::sin(angle2),
    //                                                         std::cos(angle)));
    
    fParticleGun->GeneratePrimaryVertex(event);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B5PrimaryGeneratorAction::DefineCommands()
{
    // Define /B5/generator command directory using generic messenger class
    fMessenger 
      = new G4GenericMessenger(this, 
                               "/B5/generator/", 
                               "Primary generator control");
              
    // kinetic enegry command
    G4GenericMessenger::Command& kineticCmd
      = fMessenger->DeclarePropertyWithUnit("KE", "MeV", fKineticEnergy, 
                                    "Mean kinetic Energy of primaries.");
    kineticCmd.SetParameterName("T", true);
    kineticCmd.SetRange("T>=0.");                                
    kineticCmd.SetDefaultValue("100.");                       
    
    // sigma kinetic energy command
    G4GenericMessenger::Command& sigmaKineticCmd
      = fMessenger->DeclarePropertyWithUnit("sigmaKE",
          "MeV", fSigmaKineticEnergy, "Sigma kinetic Energy of primaries.");
    sigmaKineticCmd.SetParameterName("sT", true);
    sigmaKineticCmd.SetRange("sT>=0.");                                
    sigmaKineticCmd.SetDefaultValue("50.");

    // sigma Radius command
    G4GenericMessenger::Command& sigmaRadiusCmd
      = fMessenger->DeclarePropertyWithUnit("sigmaRadius", "mm", fSigmaRadius, 
                                    "Sigma Radius of primaries.");
    sigmaRadiusCmd.SetParameterName("r", true);
    sigmaRadiusCmd.SetRange("r>=0.");                                
    sigmaRadiusCmd.SetDefaultValue("2.");

    // randomizePrimary command
    //G4GenericMessenger::Command& randomCmd
    //  = fMessenger->DeclareProperty("randomizePrimary", fRandomizePrimary);
    //G4String guidance
    //   = "Boolean flag for randomizing primary particle types.\n";   
    //guidance
    //   += "In case this flag is false, you can select the primary particle\n";
    //guidance += "  with /gun/particle command.";                               
    //randomCmd.SetGuidance(guidance);
    //randomCmd.SetParameterName("flg", true);
    //randomCmd.SetDefaultValue("true");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
