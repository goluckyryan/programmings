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
// $Id: B5PrimaryGeneratorAction.hh 76474 2013-11-11 10:36:34Z gcosmo $
//
/// \file B5PrimaryGeneratorAction.hh
/// \brief Definition of the B5PrimaryGeneratorAction class

#ifndef B5PrimaryGeneratorAction_h
#define B5PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4GenericMessenger;
class G4Event;
class G4ParticleDefinition;

/// Primary generator
///
/// A single particle is generated.
/// User can select 
/// - the initial momentum and angle
/// - the momentum and angle spreads
/// - random selection of a particle type from proton, kaon+, pi+, muon+, e+ 


class B5PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    B5PrimaryGeneratorAction();
    virtual ~B5PrimaryGeneratorAction();
    
    virtual void GeneratePrimaries(G4Event*);
    
    void SetKineticEnergy(G4double val) { fKineticEnergy = val; }
    G4double GetKineticEnergy() const { return fKineticEnergy; }

    void SetSigmaKineticEnergy(G4double val) { fSigmaKineticEnergy = val; }
    G4double GetSigmaKineticEnergy() const { return fSigmaKineticEnergy; }

    void SetSigmaRadius(G4double val) { fSigmaRadius = val; }
    G4double GetSigmaRadius() const { return fSigmaRadius; }

    void SetRandomize(G4bool val) { fRandomizePrimary = val; }
    G4bool GetRandomize() const { return fRandomizePrimary; }
    
private:
    void DefineCommands();

    G4ParticleGun* fParticleGun;
    G4GenericMessenger* fMessenger;
//    G4ParticleDefinition* fPositron;
//    G4ParticleDefinition* fMuon;
//    G4ParticleDefinition* fPion;
//    G4ParticleDefinition* fKaon;
    G4ParticleDefinition* fProton;
    G4double fKineticEnergy;
    G4double fSigmaKineticEnergy;
    G4double fSigmaRadius;
    G4bool fRandomizePrimary;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
