#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

class CalHit : public G4VHit {
private:
  G4int id;      
  G4double edep,tdep;

  public:
  CalHit();
  CalHit(G4int aid, G4double aedep, G4double atdep);
  virtual ~CalHit();

  // copy constructor & assignment operator
  CalHit(const CalHit& right);
  const CalHit& operator=(const CalHit& right);
  G4int operator==(const CalHit& right) const;
  
  // new/delete operators
  void* operator new(size_t);
  void operator delete(void* aHit);
  
  // set/get functions
  void SetID(G4int aid) { id = aid; }
  G4int GetID() const { return id; }

  void SetEdep(G4double aedep) { edep = aedep; }
  G4double GetEdep() const { return edep; }

  void SetTdep(G4double atdep) { tdep = atdep; }
  G4double GetTdep() const { return tdep; }

};

extern G4Allocator<CalHit> CalHitAllocator; 

inline void* CalHit::operator new(size_t)
{
  void* aHit= (void*)CalHitAllocator.MallocSingle();
  return aHit;
}

inline void CalHit::operator delete(void* aHit)
{
  CalHitAllocator.FreeSingle((CalHit*) aHit);
}

typedef G4THitsCollection<CalHit> CalHitsCollection;
