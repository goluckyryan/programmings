#ifndef TQGSP_h
#define TQGSP_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"
#include "CompileTimeConstraints.hh"

template<class T>
class TQGSP: public T
{
public:
  TQGSP(G4int ver = 1);
  virtual ~TQGSP();
  
public:
  // SetCuts() 
  virtual void SetCuts();
  
private:
  enum {ok = CompileTimeConstraints::IsA<T, G4VModularPhysicsList>::ok };

};
#include "QGSP.icc"
typedef TQGSP<G4VModularPhysicsList> QGSP;

// 2002 by J.P. Wellisch

#endif
