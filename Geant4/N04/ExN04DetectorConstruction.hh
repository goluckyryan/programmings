#ifndef ExN04DetectorConstruction_h
#define ExN04DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4Material;
class G4Element;

class ExN04DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    ExN04DetectorConstruction();
    ~ExN04DetectorConstruction();

  public:
     G4VPhysicalVolume* Construct();

  private:
     void DefineMaterials();

#include "ExN04DetectorParameterDef.hh"

  G4Material* Air;
  G4Material* Ar;
  G4Material* Silicon;
  G4Material* Scinti;
  G4Material* Lead;

  G4Element* H;
  G4Element* C;
  G4Element* N;
  G4Element* O;
};

#endif
