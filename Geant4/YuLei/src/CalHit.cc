// ====================================================================
//   CalHit.cc
//
// ====================================================================
#include "CalHit.hh"

// allocator
G4Allocator<CalHit> CalHitAllocator;

////////////////////
CalHit::CalHit()
  : id(-1), edep(0.)
////////////////////
{
}

/////////////////////////////////////////
CalHit::CalHit(G4int aid, G4double aedep, G4double atdep)
  : id(aid), edep(aedep), tdep(atdep)
/////////////////////////////////////////
{
}

/////////////////
CalHit::~CalHit()
/////////////////
{
}


