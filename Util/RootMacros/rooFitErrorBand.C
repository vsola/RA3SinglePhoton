#ifndef rootFileToPsandJpg_C_
#define rootFileToPsandJpg_C_
#ifndef __CINT__ 
#include <TKey.h>
#include <TImage.h>
#include <TError.h>
#include <TFile.h>
#include "Util/OwnUtil/src/HistoDrawUtil.h"

#endif

using namespace std;
void rooFitErrorBand() {

using namespace RooFit ;
RooRealVar c("c","c",0.0,0.4);
RooRealVar b("b","b",0.9,2.9);
RooRealVar a("a","a",1.9,2.4);
RooRealVar x("x","x",0.1,50);
RooGenericPdf gp("test","test","a+b*exp(-c*x)",RooArgSet(x,a,b,c));
RooDataSet* data = gp.generate(x,100) ;

}
;
#endif
