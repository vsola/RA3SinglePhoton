#include <TKey.h>
#include <TImage.h>
#include <TError.h>
#include <vector>
#include <TFile.h>
#include <TROOT.h>
#include <TH1F.h>
#include <TGraphAsymmErrors.h>
#include <TObject.h>
#include <Util/OwnUtil/src/HistoDrawUtil.h>
#include <Util/RootMacros/rootFileToPsandJpg.C>
#include <Util/RootMacros/compareHistosSusyPhotonJetAnalysis.C>
#include <iostream>
#include <utility>
#include <cmath>
#include <cstdlib>
#include <TMath.h>
#include <TLegend.h>
#include <TLegendEntry.h>

using namespace HistoDrawUtil;
using namespace std;
void doTriggerPlots() {

  gROOT->ProcessLine(".L Util/RootMacros/compareHistosSusyPhotonJetAnalysis.C");
  gROOT->LoadMacro("Util/RootMacros/rootFileToPsandJpg.C");
  string dirname = "Plots_PhotonSusyAnalysis";
 
  TFile * input = new TFile( (dirname + "/PhotonTrigger_Run2012_22Jan13_V04/mergedHistos.root").c_str(),
			     "Read" );
  
  makeTriggerEffPlots(dirname, input,
		      "select_All_HT_Nominator","ph50",
		      "select_All_HT_Denominator","ph70PFHT400",true,false);
  
  makeTriggerEffPlots(dirname, input,
		      "select_All_Photon_Nominator","ph50",
		      "select_All_Photon_Denominator","ph70PFHT400",false,true);
  


  return;
}
