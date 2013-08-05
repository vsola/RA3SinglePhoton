#ifndef PhysicsUtil_h
#define PhysicsUtil_h

#include <TVector3.h>
#include "TMath.h"
/*
 * namespace is used for Physics Utilities...
 */
namespace PhysicsUtil {
bool isCorBQuark(int pdgId);

float GetDeltaPhi(float v1, float v2);
float GetDeltaPhiPlusMinus(float v1, float v2);
float GetAngle(TVector3 iJet1, TVector3 iJet2);
}

#endif
