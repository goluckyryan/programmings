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
/// \file electromagnetic/TestEm4/include/EventAction.hh
/// \brief Definition of the EventAction class
//
//
// $Id$
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class RunAction;
class EventActionMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class EventAction : public G4UserEventAction
{
  public:
    EventAction(RunAction*);
   ~EventAction();

  public:
    virtual void BeginOfEventAction(const G4Event*);
    virtual void   EndOfEventAction(const G4Event*);
    
    void addEdep(G4double Edep)     {fTotalEnergyDeposit += Edep;};      
    void addAdep(G4double Adep)     {fTotalActiveDeposit += Adep;};      
    void addPdep(G4double Pdep)     {fTotalPassivDeposit += Pdep;};      
    void addSdep(G4double Sdep)     {fTotalSiDeposit += Sdep;};      
    void addCdep(G4double Cdep)     {fTotalCsIDeposit += Cdep;};      
    void convTime(G4double TimeFast)     {fFastTiming  = TimeFast;};
    void convTime1(G4double TimeFast1)   {fFastTiming1 = TimeFast1;};
    void convTime2(G4double TimeFast2)   {fFastTiming2 = TimeFast2;};
    G4double GetEnergyDeposit()     {return fTotalEnergyDeposit;};    
    void SetDrawFlag(G4String val)  {fDrawFlag = val;};
    void SetPrintModulo(G4int val)  {fPrintModulo = val;};
        
  private:
    RunAction* fRun;            
    G4double fTotalEnergyDeposit;   // Energy deposited in Total material
    G4double fTotalActiveDeposit;   // Energy deposited in GS20
    G4double fTotalPassivDeposit;   // Energy deposited in GS10
    G4double fTotalSiDeposit;   // Energy deposited in Si
    G4double fTotalCsIDeposit;   // Energy deposited in CsI
    G4double fFastTiming;   // Fast Timing in LaBr
    G4double fFastTiming1;   // Fast Timing in CsI
    G4double fFastTiming2;   // Fast Timing in Plastic
    G4String fDrawFlag;             // control the drawing of event
    G4int                     fPrintModulo;          
    EventActionMessenger*     fEventMessenger;
    G4String        fDecayChain;    //new for Rdecay

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
