#ifndef PhysicsUtil_h
#define PhysicsUtil_h
#include <TVector3.h>
#include "TMath.h"
using namespace std;
/*
 * namespace is used for Physics Utilities...
 */
namespace PhysicsUtil {
bool isCorBQuark(int pdgId) {
	if (fabs(pdgId)==4 || fabs(pdgId)==5) {
		return true;
	} else
		return false;
}

float GetDeltaPhi(float v1, float v2) {
	// Computes the correctly normalized phi difference
	// v1, v2 = phi of object 1 and 2
	float diff = fabs(v2 - v1);
	float corr = 2 * acos(-1.) - diff;
	if (diff < acos(-1.)) {
		return diff;
	} else {
		return corr;
	}

}
float GetDeltaPhiPlusMinus(float v1, float v2) {
//	cout<<"================="<<endl;
//	cout<<"phi1:"<<v1<<endl;
//	cout<<"phi2:"<<v2<<endl;
	float v1Opposite=v1+TMath::Pi();
	if (v1Opposite>(TMath::Pi()))
		v1Opposite=v1Opposite-(2*TMath::Pi());
//	cout<<"phi1 opposite:"<<v1Opposite<<endl;
	if (v1>0) {
		if (v2>v1 || v2<v1Opposite) {
//			cout<<"v1>0++++++"<<endl;
			return +(GetDeltaPhi(v1, v2));
		} else {
//			cout<<"v1>0-------"<<endl;
			return -(GetDeltaPhi(v1, v2));
		}

	} else if (v1==0) {
		if (v2>v1) {
//			cout<<"v1=0----"<<endl;
			return -(GetDeltaPhi(v1, v2));
		} else {
//			cout<<"v1=0+++"<<endl;
			return +(GetDeltaPhi(v1, v2));
		}
	} else {
		if (v2>v1 && v2<v1Opposite) {
//			cout<<"++++++"<<endl;
			return +(GetDeltaPhi(v1, v2));
		} else {
//			cout<<"-------"<<endl;
			return -(GetDeltaPhi(v1, v2));
		}
	}

}
float GetAngle(TVector3 iJet1, TVector3 iJet2) {

	double px1 = iJet1.Px();
	double py1 = iJet1.Py();
	double pz1 = iJet1.Pz();
	double px2 = iJet2.Px();
	double py2 = iJet2.Py();
	double pz2 = iJet2.Pz();
	if (px1 == 0 && py1 == 0) {
		return 0;
	}
	if (px2 == 0 && py2 == 0) {
		return 0;
	}
	float ab = (px1 * px2 + py1 * py2 + pz1 * pz2);
	float abs1 = sqrt(px1 * px1 + py1 * py1 + pz1 * pz1);
	float abs2 = sqrt(px2 * px2 + py2 * py2 + pz2 * pz2);

	float alfa = acos(ab / (abs1 * abs2));

	//if (alfa < acos(-1.)){ return alfa;} else { return 2*acos(-1.) - alfa;}
	TVector3 v1(px1, py1, pz1);
	TVector3 v2(px2, py2, pz2);
	Double_t a = v1.Angle(v2);
	return (180 / TMath::Pi()) * alfa;
	//return a;

}
}

#endif
