
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"

#include "ExN04DetectorConstruction.hh"
//#include "QGSP.hh"
#include "QBBC.hh"
#include "ExN04PrimaryGeneratorAction.hh"
#include "ExN04RunAction.hh"
#include "ExN04EventAction.hh"
#include "ExN04StackingAction.hh"
#include "ExN04TrackingAction.hh"
#include "ExN04SteppingAction.hh"
#include "ExN04SteppingVerbose.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

int main(int argc,char** argv)
{
  // User Verbose output class
  G4VSteppingVerbose* verbosity = new ExN04SteppingVerbose;
  G4VSteppingVerbose::SetInstance(verbosity);
  
  // Run manager
  G4RunManager* runManager = new G4RunManager;

  // User Initialization classes (mandatory)
  runManager->SetUserInitialization(new ExN04DetectorConstruction);
  //
  //G4VUserPhysicsList* physics = new QGSP;
  G4VUserPhysicsList* physics = new QBBC;
  runManager->SetUserInitialization(physics);

  runManager->Initialize();

  // User Action classes
  G4VUserPrimaryGeneratorAction* gen_action = new ExN04PrimaryGeneratorAction;
  runManager->SetUserAction(gen_action);
  //
  G4UserRunAction* run_action = new ExN04RunAction;
  runManager->SetUserAction(run_action);
  //
  G4UserEventAction* event_action = new ExN04EventAction;
  runManager->SetUserAction(event_action);
  //
  G4UserStackingAction* stacking_action = new ExN04StackingAction;
  runManager->SetUserAction(stacking_action);
  //
  G4UserTrackingAction* tracking_action = new ExN04TrackingAction;
  runManager->SetUserAction(tracking_action);
  //
  G4UserSteppingAction* stepping_action = new ExN04SteppingAction;
  runManager->SetUserAction(stepping_action);
  
  //get the pointer to the User Interface manager   
  G4UImanager* UI = G4UImanager::GetUIpointer();  

  if (argc!=1)   // batch mode  
    {
     G4String command = "/control/execute ";
     G4String fileName = argv[1];
     UI->ApplyCommand(command+fileName);
    }
    
  else           // interactive mode : define visualization and UI terminal
    { 
#ifdef G4VIS_USE
      G4VisManager* visManager = new G4VisExecutive;
      visManager->Initialize();
#endif    
     
      G4UIsession * session = 0;
#ifdef G4UI_USE_TCSH
      session = new G4UIterminal(new G4UItcsh);      
#else
      session = new G4UIterminal();
#endif

      UI->ApplyCommand("/control/execute vis.mac");     
      session->SessionStart();
      delete session;
     
#ifdef G4VIS_USE
      delete visManager;
#endif     
    }
    
  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  //                 owned and deleted by the run manager, so they should not
  //                 be deleted in the main() program !
  delete runManager;
  delete verbosity;

  return 0;
}
