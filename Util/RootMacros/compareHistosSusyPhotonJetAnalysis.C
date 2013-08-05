#ifndef compareHistosSusyPhotonJetAnalysis_C_
#define compareHistosSusyPhotonJetAnalysis_C_
#ifndef __CINT__

#include <TKey.h>
#include <TImage.h>
#include <TError.h>
#include <vector>
#include <TFile.h>
#include <TROOT.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TObject.h>
#include "Util/RootMacros/rootFileToPsandJpg.C"
#include <iostream>
#include <utility>
#include <TVirtualFitter.h>
#include "Util/OwnUtil/src/HistoDrawUtil.h"

#endif

#include "Util/OwnUtil/src/HistoDrawUtil.h"
std::string dummy;

#include <string>
std::string dummy2;
#include <iostream>
#include <algorithm>
#include <cctype>
#include <TLegend.h>
#include <TLegendEntry.h>

using namespace std;
using namespace HistoDrawUtil;


// return histo with the square of the error on the y axis
TH1F * getErr2(TH1F * h, string clonename) {

  std::vector<double> binEdges;
  for (int i = 1; i <= h->GetNbinsX() + 1; i++) {
    binEdges.push_back(h->GetBinLowEdge(i));
  }

  TH1F * hClone = new TH1F(clonename.c_str(), h->GetTitle(), h->GetNbinsX(), &(binEdges.front()));
  if (hClone->GetSumw2N() == 0)
    hClone->Sumw2();

  const int noBins = h->GetNbinsX();
  for (int i = 1; i < noBins + 1; i++) {
    hClone->Fill(h->GetBinCenter(i), h->GetBinError(i) * h->GetBinError(i));
  }

  return hClone;
}


// return histo with the square root of the bin content on the y axis
TH1F * getSqrt(TH1F * h, string clonename) {

  std::vector<double> binEdges;
  for (int i = 1; i <= h->GetNbinsX() + 1; i++) {
    binEdges.push_back(h->GetBinLowEdge(i));
  }

  TH1F * hClone = new TH1F(clonename.c_str(), h->GetTitle(), h->GetNbinsX(), &(binEdges.front()));
  if (hClone->GetSumw2N() == 0)
    hClone->Sumw2();

  const int noBins = h->GetNbinsX();
  for (int i = 1; i < noBins + 1; i++) {
    if (h->GetBinContent(i) != 0) 
      hClone->Fill(h->GetBinCenter(i), sqrt(h->GetBinContent(i)));
  }

  return hClone;
}


// set dimensions for bottom pad
TPad * createRatioBottomPad() {
  TPad *ratioPad = new TPad("BottomPad", "", 0, 0, 1, 1);
  ratioPad->SetTopMargin(0.8 - 0.8 * ratioPad->GetBottomMargin() + 0.2 * ratioPad->GetTopMargin());
  ratioPad->SetFillStyle(0);
  ratioPad->SetFrameFillColor(10);
  ratioPad->SetFrameBorderMode(0);
  return ratioPad;
}


// set names for the header
string getSampleNameTech(string curr) {
  string ret = "";

  if (containsSubstr(curr, "Merged_Data_V20bb_PAT"))
    ret = "DataPhotonPtRew";
  else if (containsSubstr(curr, "select_1ph_met10_0jets") || containsSubstr(curr, "select_1ph_met10_0jets"))
    ret = "#geq1 #gamma, =0 jets";
  else if (containsSubstr(curr, "select_2ph_met10_0jets") || containsSubstr(curr, "select_2ph_met_0jets"))
    ret = "#geq2 #gamma, =0 jets";
  else if (containsSubstr(curr, "select_1ph_met10_2jets") || containsSubstr(curr, "select_1ph_met_2jets"))
    ret = "#geq1 #gamma, #geq2 jets";
  else if (containsSubstr(curr, "select_2ph_met10_2jets") || containsSubstr(curr, "select_2ph_met_2jets"))
    ret = "#geq2 #gamma, #geq2 jets";
  else if (containsSubstr(curr, "select_1ph_met10_3jets") || containsSubstr(curr, "select_1ph_met_3jets"))
    ret = "#geq1 #gamma, #geq2 jets";
  else if (containsSubstr(curr, "select_1ph_3jets_Fake") || containsSubstr(curr, "select_2ph_met_3jets"))
    ret = "#geq2 #gamma, #geq3 jets";
  else if (containsSubstr(curr, "select_2ph_met10_3jets") || containsSubstr(curr, "select_2ph_met_3jets"))
    ret = "#geq2 #gamma, #geq3 jets";
  else if (containsSubstr(curr, "select_1ph_met10_2jets") || containsSubstr(curr, "select_1ph_met_2jets"))
    ret = "#geq1 #gamma, #geq2 b jets";
  else if (containsSubstr(curr, "select_2ph_met10_2jets") || containsSubstr(curr, "select_2ph_met_2jets"))
    ret = "#geq2 #gamma, #geq2 b jets";
  else if (containsSubstr(curr, "select_1ph_2jets") || containsSubstr(curr, "select_1ph_2jets"))
    ret = "#geq1 #gamma, #geq2 jets";
  else if (containsSubstr(curr, "select_1ph_2jets_1b") || containsSubstr(curr, "select_1ph_2jets_1b"))
    ret = "#geq1 #gamma, #geq2 jets, #geq1 b";
  else if (containsSubstr(curr, "select_1ph_3jets") || containsSubstr(curr, "select_1ph_3jets"))
    ret = "#geq1 #gamma, #geq3 jets";
  else if (containsSubstr(curr, "select_2ph_2jets") || containsSubstr(curr, "select_2ph_2jets"))
    ret = "2 #gamma,=2 jets";
  else if (containsSubstr(curr, "select_2ph_3jets") || containsSubstr(curr, "select_2ph_3jets"))
    ret = "2 #gamma, #geq3 jets";
  else if (containsSubstr(curr, "PhotonVJets"))
    ret = "W/Z+#gamma";
  else if (containsSubstr(curr, "Merged_EWKandQCD"))
    ret = "EWKandQCD ";
  else if (containsSubstr(curr, "Merged_EWK"))
    ret = "EWK";
  else if (containsSubstr(curr, "Merged_GGM_A_AllSM"))
    ret = "GGM B and All SM ";
  else if (containsSubstr(curr, "Merged_GGM_B_AllSM"))
    ret = "GGM A and All SM ";
  else if (containsSubstr(curr, "GMSB_B"))
    ret = "GGM B";
  else if (containsSubstr(curr, "GMSB_A"))
    ret = "GGM A";
  else if (containsSubstr(curr, "GMSB_C"))
    ret = "GGM C";
  else if (containsSubstr(curr, "GMSB_E"))
    ret = "GGM E";
  else if (containsSubstr(curr, "AllSM"))
    ret = "All SM";
  else if (containsSubstr(curr, "Merged_QCD_PhotonJet"))
    ret = "QCD and Photon Jet";
  else if (containsSubstr(curr, "PhotonJet"))
    ret = "PhotonJet";
  else if (containsSubstr(curr, "TTBar"))
    ret = "TTBar";
  else if (containsSubstr(curr, "WGToLNuG"))
    ret = "WGToLNuG";
  else if (containsSubstr(curr, "ZGToLLG"))
    ret = "ZGToLLG";

  else if (containsSubstr(curr, "WJets"))
    ret = "WJetsToLNu";
  else if (containsSubstr(curr, "DYJet"))
    ret = "DYJetsToLL";
  else if (containsSubstr(curr, "QCD"))
    ret = "QCD";

  else if (containsSubstr(curr, "SignalA"))
    ret = "$m_{#tilde{s}}=820,m_{#tilde{g}}$=800,m_{#tilde{#chi}^0_1}$=200)";
  else if (containsSubstr(curr, "GMSB1"))
    ret = "(750/700/225)";
  else if (containsSubstr(curr, "GMSB2"))
    ret = "(450/400/125)";
  else if (containsSubstr(curr, "GMSB3"))
    ret = "750/1000/375";
  else if (containsSubstr(curr, "GMSB4"))
    ret = "(450/1400/225)";
  else if (containsSubstr(curr, "GMSB5"))
    ret = "750/1000/375";
  else if (containsSubstr(curr, "Data"))
    ret = "Data";
  else if (containsSubstr(curr, "gm1b"))
    ret = "GM1b";
  else if (containsSubstr(curr, "ZInv"))
    ret = "ZInv";
  else if (containsSubstr(curr, "PhotonHad") || containsSubstr(curr, "Merged_Data"))
    ret = "Data";

  return ret;
}


// set name of the objects
string getPhotonTypeFromTitle(string curr) {
  string ret = "#gamma";
  if (containsSubstr(curr, "FO"))
    ret = "#gamma_{jet}";
  if (containsSubstr(curr, "PixelSeed"))
    ret = "#gamma_{e}";
  return ret;
}


// set legend names
string getLegendTitle(string curr) {
  string ret = "";

  if (containsSubstr(curr, "select_1ph_met10_0jets") || containsSubstr(curr, "select_1ph_met10_0jets"))
    ret = "#geq1 #gamma, =0 jets";
  else if (containsSubstr(curr, "select_2ph_met10_0jets") || containsSubstr(curr, "select_2ph_met_0jets"))
    ret = "#geq2 #gamma, =0 jets";
  else if (containsSubstr(curr, "select_1ph_met10_2jets") || containsSubstr(curr, "select_1ph_met_2jets"))
    ret = "#geq1 #gamma, #geq2 jets";
  else if (containsSubstr(curr, "select_2ph_met10_2jets") || containsSubstr(curr, "select_2ph_met_2jets"))
    ret = "#geq2 #gamma, #geq2 jets";
  else if (containsSubstr(curr, "select_1ph_met10_3jets") || containsSubstr(curr, "select_1ph_met_3jets"))
    ret = "#geq1 #gamma, #geq2 jets";
  else if (containsSubstr(curr, "select_1ph_3jets_Fake") || containsSubstr(curr, "select_2ph_met_3jets"))
    ret = "#geq2 #gamma, #geq3 jets";
  else if (containsSubstr(curr, "select_2ph_met10_3jets") || containsSubstr(curr, "select_2ph_met_3jets"))
    ret = "#geq2 #gamma, #geq3 jets";
  else if (containsSubstr(curr, "select_1ph_met10_2jets") || containsSubstr(curr, "select_1ph_met_2jets"))
    ret = "#geq1 #gamma, #geq2 b jets";
  else if (containsSubstr(curr, "select_2ph_met10_2jets") || containsSubstr(curr, "select_2ph_met_2jets"))
    ret = "#geq2 #gamma, #geq2 b jets";
  else if (containsSubstr(curr, "select_1ph_2jets") || containsSubstr(curr, "select_1ph_2jets"))
    ret = "#geq1 #gamma, #geq2 jets";
  else if (containsSubstr(curr, "select_1ph_2jets_1b") || containsSubstr(curr, "select_1ph_2jets_1b"))
    ret = "#geq1 #gamma, #geq2 jets, #geq1 b";
  else if (containsSubstr(curr, "select_1ph_3jets") || containsSubstr(curr, "select_1ph_3jets"))
    ret = "#geq1 #gamma, #geq3 jets";
  else if (containsSubstr(curr, "select_2ph_2jets") || containsSubstr(curr, "select_2ph_2jets"))
    ret = "2 #gamma, #geq2 jets";
  else if (containsSubstr(curr, "select_2ph_3jets") || containsSubstr(curr, "select_2ph_3jets"))
    ret = "2 #gamma, #geq3 jets";
  else if (containsSubstr(curr, "PhotonVJets"))
    ret = "W/Z+#gamma";
  else if (containsSubstr(curr, "Merged_EWKandQCD"))
    ret = "t#bar{t}/W and #gamma/QCD ";
  else if (containsSubstr(curr, "Merged_EWK"))
    ret = "t#bar{t}/W (Sim.)  ";
  else if (containsSubstr(curr, "Merged_GMSB_B_AllSM"))
    ret = "GGM B and All SM ";
  else if (containsSubstr(curr, "Merged_GMSB_A_AllSM"))
    ret = "GGM A and All SM ";
  else if (containsSubstr(curr, "GMSB_B"))
    ret = "GGM B";
  else if (containsSubstr(curr, "GMSB_A"))
    ret = "GGM A";
  else if (containsSubstr(curr, "GMSB_C"))
    ret = "GGM C";
  else if (containsSubstr(curr, "GMSB_E"))
    ret = "GGM E";
  else if (containsSubstr(curr, "AllSM"))
    ret = "All SM";
  else if (containsSubstr(curr, "Merged_QCD_PhotonJet"))
    ret = "#gamma/QCD (Sim.)";
  else if (containsSubstr(curr, "PhotonJet"))
    ret = "PhotonJet";
  else if (containsSubstr(curr, "TTBar"))
    ret = "t#bar{t} #gamma";
  else if (containsSubstr(curr, "WGToLNuG"))
    ret = "WGToLNuG";
  else if (containsSubstr(curr, "ZGToLLG"))
    ret = "ZGToLLG";
  
  else if (containsSubstr(curr, "WJets"))
    ret = "WJetsToLNu";
  else if (containsSubstr(curr, "DYJet"))
    ret = "DYJetsToLL";
  else if (containsSubstr(curr, "QCD"))
    ret = "QCD";

  else if (containsSubstr(curr, "SignalA"))
    ret = "$m_{#tilde{s}}=820,m_{#tilde{g}}$=800,m_{#tilde{#chi}^0_1}$=200)";
  else if (containsSubstr(curr, "GGMA"))
    ret = "1420/1000/375"; //VS!!!
  //    ret = "1200/1120/375"; //VS!!!
  else if (containsSubstr(curr, "GGMB"))
    ret = "1040/960/375"; //VS!!!
  else if (containsSubstr(curr, "GMSB1"))
    ret = "(750/700/225)";
  else if (containsSubstr(curr, "GMSB2"))
    ret = "(450/400/125)";
  else if (containsSubstr(curr, "GMSB3"))
    ret = "750/1000/375";
  else if (containsSubstr(curr, "GMSB4"))
    ret = "(450/1400/225)";
  else if (containsSubstr(curr, "GMSB5"))
    ret = "750/1000/375";
  else if (containsSubstr(curr, "GMSBWino1"))
    ret = "800/1840/375";
  else if (containsSubstr(curr, "GMSBWino2"))
    ret = "1040/960/375";
  else if (containsSubstr(curr, "GMSBWino3"))
    ret = "1600/800/375";
  else if (containsSubstr(curr, "GMSBBino1"))
    ret = "1040/1840/375";
  else if (containsSubstr(curr, "GMSBBino2"))
    ret = "1200/1120/375";
  else if (containsSubstr(curr, "GMSBBino3"))
    ret = "1840/960/375";
  else if (containsSubstr(curr, "PhotonHad") || containsSubstr(curr, "Merged_Data") || containsSubstr(curr, "Data"))
    ret = "Data";
  else if (containsSubstr(curr, "gm1b"))
    ret = "GM1b";
  else if (containsSubstr(curr, "ZInv"))
    ret = "ZInv";
  
  return ret;
}


// set titles for x axis
string getAxisTitle(string currhname) {
  string ret = "";

  if (containsSubstr(currhname, "N_1")) {
    currhname = replaceAllBeforeLastOccurenceOf(currhname, "_");
    ret = "N-1  ";
  }

  for (int j = 0; j < (int) currhname.length(); ++j) {
    currhname[j] = tolower(currhname[j]);
  }

  if (containsSubstr(currhname, "PreselCut_hthltN90Hits"))
    ret += "H_{T} [GeV] (CaloJets, pt>40,eta<3.0,N90Hits>1) ";
  else if (containsSubstr(currhname, "PreselCut_hthltN90"))
    ret += "H_{T} [GeV] (CaloJets, pt>40,eta<3.0,N90>1)";
  else if (containsSubstr(currhname, "PreselCut_hthlt"))
    ret += "H_{T} [GeV] (CaloJets, pt>40,eta<3.0,no JetID)";
  
  if (containsSubstr(currhname, "photonphi"))
    ret += "1st photon #varphi";
  else if (containsSubstr(currhname, "photoneta"))
    ret += "1st photon #eta";
  else if (containsSubstr(currhname, "photonpt"))
    ret += "1st photon p_{T} [GeV]";
  else if (containsSubstr(currhname, "photonTrig"))
    ret += "1st photon p_{T} [GeV]";

  else if (containsSubstr(currhname, "photon2phi"))
    ret += "2nd photon #varphi";
  else if (containsSubstr(currhname, "photon2eta"))
    ret += "2nd photon #eta";
  else if (containsSubstr(currhname, "photon2pt"))
    ret += "2nd photon p_{T} [GeV]";
  
  else if (containsSubstr(currhname, "jetphi"))
    ret += "1st jet #varphi";
  else if (containsSubstr(currhname, "jeteta"))
    ret += "1st jet #eta";
  else if (containsSubstr(currhname, "jetpt"))
    ret += "1st jet p_{T} [GeV]";

  else if (containsSubstr(currhname, "jet2phi"))
    ret += "2nd jet #varphi";
  else if (containsSubstr(currhname, "jet2eta"))
    ret += "2nd jet #eta";
  else if (containsSubstr(currhname, "jet2pt"))
    ret += "2nd jet p_{T} [GeV]";

  else if (containsSubstr(currhname, "jet3phi"))
    ret += "3rd jet #varphi";
  else if (containsSubstr(currhname, "jet3eta"))
    ret += "3rd jet #eta";
  else if (containsSubstr(currhname, "jet3pt"))
    ret += "3rd jet p_{T} [GeV]";

  else if (containsSubstr(currhname, "jet4phi"))
    ret += "4th jet #varphi";
  else if (containsSubstr(currhname, "jet4eta"))
    ret += "4th jet #eta";
  else if (containsSubstr(currhname, "jet4Pt"))
    ret += "4th jet p_{T} [GeV]";

  else if (containsSubstr(currhname, "bjetphi"))
    ret += "1st b jet #varphi";
  else if (containsSubstr(currhname, "bjeteta"))
    ret += "1st b jet #eta";
  else if (containsSubstr(currhname, "bjetpt"))
    ret += "1st b jet p_{T} [GeV]";
  else if (containsSubstr(currhname, "bjet2phi"))
    ret += "2nd b jet #varphi";
  else if (containsSubstr(currhname, "bjet2eta"))
    ret += "2nd b jet #eta";
  else if (containsSubstr(currhname, "bjet2pt"))
    ret += "2nd b jet p_{T} [GeV]";
  
  else if (containsSubstr(currhname, "deltarmetphoton"))
    ret += "#Delta R_{MET,#gamma}";
  else if (containsSubstr(currhname, "deltaphimetphoton"))
    ret += "#Delta #phi_{MET,#gamma}";
  else if (containsSubstr(currhname, "r9"))
    ret += "r9";
  else if (containsSubstr(currhname, "nojet"))
    ret += "Number of Jets";
  else if (containsSubstr(currhname, "nopv"))
    ret += "Number of primary vertices";
  else if (containsSubstr(currhname, "metpt"))
    ret += "#slash{E}_{T} [GeV]";
  else if (containsSubstr(currhname, "metphi"))
    ret += "#slash{E}_{T} #varphi";
  else if (containsSubstr(currhname, "metsumet"))
    ret += "#Sigma #slash{E}_{T} [GeV]";
  else if (containsSubstr(currhname, "met2"))
    ret += "Calo #slash{E}_{T} [GeV]";
  else if (containsSubstr(currhname, "met"))
    ret += "PF #slash{E}_{T} [GeV]";
  else if (containsSubstr(currhname, "mt"))
    ret += "M_{T} [GeV]";
  else if (containsSubstr(currhname, "mht"))
    ret += "#slash{H}_{T} [GeV]";
  else if (containsSubstr(currhname, "ht"))
    ret += "H_{T} [GeV]";
  else if (containsSubstr(currhname, "mj12"))
    ret += "M_{j1,j2}";
  else if (containsSubstr(currhname, "Mmj13"))
    ret += "M_{j1,j3}";
  else if (containsSubstr(currhname, "mj23"))
    ret += "M_{j2,j3}";

  else if (containsSubstr(currhname, "nophotons"))
    ret += "Number of Photons";
  else if (containsSubstr(currhname, "nobJets"))
    ret += "Number of b Jets";

  else if (containsSubstr(currhname, "deltaphij1j2"))
    ret += "#Delta #phi (j1,j2)";
  else if (containsSubstr(currhname, "deltaphimetjet1"))
    ret += "#Delta #phi (met,j1)";
  else if (containsSubstr(currhname, "deltaphimetjet2"))
    ret += "#Delta #phi (met,j2)";
  else if (containsSubstr(currhname, "deltaphimetjet3"))
    ret += "#Delta #phi (met,j3)";
  else if (containsSubstr(currhname, "deltaphij1photon"))
    ret += "#Delta #phi (#gamma,j1)";

  return ret;
}


// merge subdirectories
void mergeSubdirs(TFile * file, vector<string> subdirs, string newdir) {

  file->rmdir(newdir.c_str());
  file->mkdir(newdir.c_str());

  for (int sub = 0; sub < (int) subdirs.size(); ++sub) {
    file->cd(subdirs.at(sub).c_str());
    TKey * key;
    TIter nextkey(gDirectory->GetListOfKeys());

    while ((key = (TKey*) nextkey())) {
      TObject *obj = key->ReadObj();

      if (obj->IsA()->InheritsFrom("TH1")) {
	string objname = obj->GetName();

	if (sub == 0) {
	  file->cd();
	  file->cd(newdir.c_str());

	  TH1 *h1Clone = (TH1*) ((TH1*) obj)->Clone();
	  file->cd();

	} else {
	  file->cd();
	  file->cd(newdir.c_str());
	  string firsthname = newdir + "/" + obj->GetName();

	  TH1 *histoInTarget = (TH1 *) gDirectory->FindObjectAny(obj->GetName());

	  if (histoInTarget != 0) {
	    TH1 *h2 = (TH1*) obj;
	    histoInTarget->Add(h2);
	  }
	  
	  if (sub == (int) subdirs.size() - 1) 
	    histoInTarget->Write();
	  
	} // if sub
      } // if obj
    } // while key
  } // for sub

  file->WriteKeys();
  file->Close();

  return;
}


// Set to 0 the errors of the input histo
void setErrorsToZero(TH1F * h) {
  const int noBins = h->GetNbinsX();
  for (int i = 1; i <= noBins; i++) {    
    h->SetBinError(i, 0);
  }
  return;
}


// histo->Scale(1,"width");
void DivideHistoByBinWidth(TH1F * histo){
  if (histo->GetSumw2N() == 0)
    histo->Sumw2();

  histo->Scale(1,"width");

  return;
}


// set edges for the rebinning
std::vector<double> getBinEdgesRebin(TH1F * histo) {

  int lowestBinWithEntries = 0;
  
  for (int i = 1; i <= histo->GetNbinsX() + 1; i++) {
    if (histo->GetBinContent(i) > 0) {
      lowestBinWithEntries = i;
      break;
    }
  }

  double stepsizeFactor = 1.1;
  if (containsSubstr(histo->GetName(), "photon") || containsSubstr(histo->GetName(), "Photon")) {
    stepsizeFactor = 1.0;
  }

  std::vector<double> binEdges;

  binEdges.clear();
  if (!containsSubstr(histo->GetName(), "no") && !containsSubstr(histo->GetName(), "Number of") && !containsSubstr(histo->GetName(), "eta") && !containsSubstr(histo->GetName(), "phi")) {
    bool firstbin = false;
    bool secondbin = false;
    double oldBinWidth = histo->GetBinWidth(1);
    double oldmaximum = histo->GetBinLowEdge(histo->GetNbinsX() + 1);
    double currBinWidth = oldBinWidth;

    double currBinLowEdge = histo->GetBinLowEdge(1);

    for (int i = 1; i <= histo->GetNbinsX() + 1; i++) {

      if (containsSubstr(histo->GetName(), "photon") || containsSubstr(histo->GetName(), "Photon")) {
	if (currBinLowEdge >= 125) {
	  if (!firstbin) {
	    firstbin = true;
	    stepsizeFactor = 1.3;
	    currBinWidth = 1.2 * currBinWidth;
	  } else
	    currBinWidth = currBinWidth * stepsizeFactor;
	}
      } else if (containsSubstr(histo->GetName(), "htj")) {
	if (currBinLowEdge >= 50) {
	  if (!firstbin) {
	    firstbin = true;
	    currBinWidth = 6 * currBinWidth;
	    stepsizeFactor = 1.0;
	  }
	  currBinWidth = currBinWidth * stepsizeFactor;
	}
      } else if (containsSubstr(histo->GetName(), "ht")) {
	if (currBinLowEdge >= 200) {
	  if (!firstbin) {
	    firstbin = true;
	    currBinWidth = 4 * currBinWidth;
	    stepsizeFactor = 1.2;
	  }
	  currBinWidth = currBinWidth * stepsizeFactor;
	}
      } else if (containsSubstr(histo->GetName(), "SumEt")) {
	if (currBinLowEdge >= 300) {
	  if (!firstbin) {
	    firstbin = true;
	    currBinWidth = 6 * currBinWidth;
	    stepsizeFactor = 1;
	  }
	  currBinWidth = currBinWidth * stepsizeFactor;
	}
      }
      else {
	currBinWidth = currBinWidth * stepsizeFactor;
      }

      currBinLowEdge = currBinLowEdge + currBinWidth;
      if (currBinLowEdge + (currBinWidth * stepsizeFactor) >= oldmaximum) {
	binEdges.push_back(oldmaximum);
	break;
      }
      binEdges.push_back(currBinLowEdge);
    }

    if (containsSubstr(histo->GetName(), "noJets") && !containsSubstr(histo->GetName(), "Vs")){ //VS!!!
      binEdges.clear();      
      binEdges.push_back(0.);
      binEdges.push_back(1.);
      binEdges.push_back(2.);
      binEdges.push_back(3.);
      binEdges.push_back(4.);
      binEdges.push_back(5.);
      binEdges.push_back(6.);
      binEdges.push_back(7.);
      binEdges.push_back(8.);
      binEdges.push_back(9.);
      binEdges.push_back(10.);
      binEdges.push_back(11.);
      binEdges.push_back(12.);
      binEdges.push_back(13.);
      binEdges.push_back(14.);
      binEdges.push_back(15.);
    }

    if (containsSubstr(histo->GetName(), "photonPt") && !containsSubstr(histo->GetName(), "Vs")){ //VS!!!
      binEdges.clear();
      
      binEdges.push_back(0.);
      binEdges.push_back(15.);
      binEdges.push_back(25.);
      binEdges.push_back(35.);
      binEdges.push_back(45.);
      binEdges.push_back(55.);
      binEdges.push_back(65.);
      binEdges.push_back(75.);
      binEdges.push_back(85.);
      binEdges.push_back(95.);
      binEdges.push_back(105.);
      binEdges.push_back(115.);
      binEdges.push_back(125.);
      binEdges.push_back(137.);
      binEdges.push_back(152.6);
      binEdges.push_back(172.88);
      binEdges.push_back(199.244);
      binEdges.push_back(233.517);
      binEdges.push_back(278.072);
      binEdges.push_back(335.994);
      binEdges.push_back(411.292);
      binEdges.push_back(509.18);
      binEdges.push_back(636.434);
      binEdges.push_back(801.864);
      binEdges.push_back(1016.92);
      binEdges.push_back(1505.);
      /*
      binEdges.push_back(0.);
      binEdges.push_back(15.);
      binEdges.push_back(25.);
      binEdges.push_back(35.);
      binEdges.push_back(45.);
      binEdges.push_back(55.);
      binEdges.push_back(65.);
      binEdges.push_back(75.);
      binEdges.push_back(80.);
      binEdges.push_back(85.);
      binEdges.push_back(90.);
      binEdges.push_back(95.);
      binEdges.push_back(100.);
      binEdges.push_back(105.);
      binEdges.push_back(110.);
      binEdges.push_back(115.);
      binEdges.push_back(120.);
      binEdges.push_back(125.);
      binEdges.push_back(130.);
      binEdges.push_back(140.);
      binEdges.push_back(150.);
      binEdges.push_back(160.);
      binEdges.push_back(170.);
      binEdges.push_back(185.);
      binEdges.push_back(200.);
      binEdges.push_back(215.);
      binEdges.push_back(230.);
      binEdges.push_back(255.);
      binEdges.push_back(280.);
      binEdges.push_back(305.);
      binEdges.push_back(335.);
      binEdges.push_back(370.);
      binEdges.push_back(410.);
      binEdges.push_back(460.);
      binEdges.push_back(510.);
      binEdges.push_back(570.);
      binEdges.push_back(635.);
      binEdges.push_back(715.);
      binEdges.push_back(800.);
      binEdges.push_back(900.);
      binEdges.push_back(1010.);
      binEdges.push_back(1250.);
      binEdges.push_back(1505.);
      */
    }

    if (containsSubstr(histo->GetName(), "met") && !containsSubstr(histo->GetName(), "hoton") && !containsSubstr(histo->GetName(), "noJet") && !containsSubstr(histo->GetName(), "SumEt")) {
      //cout << "MET gets new binning..." << endl;
      binEdges.clear();
      binEdges.push_back(0);
      binEdges.push_back(10);
      binEdges.push_back(20);
      binEdges.push_back(30);
      binEdges.push_back(40);
      binEdges.push_back(50);
      binEdges.push_back(60);
      binEdges.push_back(70);
      binEdges.push_back(80);
      binEdges.push_back(90);
      binEdges.push_back(99);
      binEdges.push_back(120);
      binEdges.push_back(159);
      binEdges.push_back(199);
      binEdges.push_back(269);
      binEdges.push_back(349);
      binEdges.push_back(499);
    }

  } else {

    for (int i = 1; i <= histo->GetNbinsX() + 1; i++) {			  
      binEdges.push_back(histo->GetBinLowEdge(i));
    }

  }

  return binEdges;
}


// convert a graph into an histo 
TH1F * getHistoFromGraph(TGraphAsymmErrors * effSig) {
  const int noBins = effSig->GetN();

  TH1F * hDiv = new TH1F(effSig->GetName(), effSig->GetTitle(), effSig->GetXaxis()->GetNbins(), effSig->GetXaxis()->GetXmin(), effSig->GetXaxis()->GetXmax());
  if (hDiv->GetSumw2N() == 0)
    hDiv->Sumw2();

  for (int i = 0; i < noBins; i++) {
    int binContainingPoint = effSig->GetXaxis()->FindBin(effSig->GetX()[i]);
    hDiv->SetBinContent(binContainingPoint, effSig->GetY()[i] + (hDiv->GetBinContent(binContainingPoint)));
    hDiv->SetBinError(binContainingPoint, effSig->GetEYhigh()[i] + (hDiv->GetBinError(binContainingPoint)));
  }

  return hDiv;
}


// return the red error bans for ratio plots
// (relative errors of the background sample)
TH1F * getSystErrForRatio(TH1F * bkg) {
  string newname = bkg->GetName();
  newname = newname + "cloneforSystRat";
  TH1F * bkgClone = (TH1F *) bkg->Clone(newname.c_str());

  for (int i = 1; i <= bkgClone->GetNbinsX(); i++) {
    double relError = (bkgClone->GetBinError(i) / bkgClone->GetBinContent(i));
    bkgClone->SetBinContent(i, 1);
    bkgClone->SetBinError(i, relError);
  }

  return bkgClone;
}


// makes the ratio plots
TH1F * divideHistosForRatio(TH1F * sig, TH1F * bkg) {
  string newname = bkg->GetName();
  newname = newname + "clonefordiv";

  TH1F * bkgClone = (TH1F *) bkg->Clone(newname.c_str());

  // The error bars of the ratio plots should not contain the errors of the
  // background, therefore they are set to 0
  /*
  for( unsigned int bin = 0; bin <= bkgClone->GetNbinsX()+1; bin++)
    bkgClone->SetBinError( bin, 0 ); //Knut?!?
  */
  setErrorsToZero(bkgClone);

  sig->Divide(sig, bkgClone, 1, 1, "");

  return sig;
}


TH1F * divideHistos(TH1F * sig, TH1F * bkg) {
  // sig->Divide(bkg);
  // return sig;

  string newdivname = sig->GetName();
  newdivname = newdivname + "clone2";
  const int noBins = sig->GetNbinsX();

  std::vector<double> binEdges;
  for (int i = 1; i <= noBins + 1; i++) 
    binEdges.push_back(sig->GetBinLowEdge(i));
  
  TH1F * hdiv = new TH1F(newdivname.c_str(), sig->GetTitle(), sig->GetNbinsX(), &(binEdges.front()));
  if (hdiv->GetSumw2N() == 0)
    hdiv->Sumw2();
  hdiv->SetDirectory(0);
	
  // hdiv->Divide(sig,bkg);
  for (int i = 0; i <= noBins; i++) {

    double errSig = sig->GetBinError(i);//sqrt(sig->GetBinContent(i));
    double errBkg = bkg->GetBinError(i);//sqrt(bkg->GetBinContent(i));
    double valSig = sig->GetBinContent(i);
    double valBkg = bkg->GetBinContent(i);

    if (valSig != 0 && valBkg != 0) {
      double relErrSig = errSig / valSig;
      double relErrBkg = errBkg / valBkg;
      double valDiv    = valSig / valBkg;
      double relErrDiv = sqrt(pow(relErrSig, 2) + pow(relErrBkg, 2));
      double errDiv    = relErrDiv * valDiv;

      hdiv->SetBinError(i, errDiv);
      hdiv->SetBinContent(i, valDiv);
    } else {

      //To modify according to Knut results?!
      if (valSig == 0 && valBkg != 0) { 
	hdiv->SetBinError(i, errBkg);
	hdiv->SetBinContent(i, 0);
      } else {
	hdiv->SetBinError(i, 0);
	hdiv->SetBinContent(i, 0);
      }

    } // if vals
  } // for noBins

  return hdiv;
}


// evaluate efficiency graphs with stat + syst errors
TGraphAsymmErrors * getEffDivideHisto(TGraphAsymmErrors * effSig, TGraphAsymmErrors * effBkg) {
  
  const int noBins = effSig->GetN();

  Double_t *ylowe  = effSig->GetEYlow();
  Double_t *yupe   = effSig->GetEYhigh();
  Double_t *y      = effSig->GetY();

  Double_t *yloweB = effBkg->GetEYlow();
  Double_t *yupeB  = effBkg->GetEYhigh();
  Double_t *yB     = effBkg->GetY();

  TGraphAsymmErrors * effSigCloneForNewGraph = (TGraphAsymmErrors *) effSig->Clone("a");

  Double_t *yloweF = effSigCloneForNewGraph->GetEYlow();
  Double_t *yupeF  = effSigCloneForNewGraph->GetEYhigh();
  Double_t *yF     = effSigCloneForNewGraph->GetY();

  Double_t *xloweF = effSigCloneForNewGraph->GetEXlow();
  Double_t *xupeF  = effSigCloneForNewGraph->GetEXhigh();
  Double_t *xF     = effSigCloneForNewGraph->GetX();

  vector<int> pointstodelete;
  pointstodelete.clear();

  for (int i = 0; i < noBins; i++) {

    if ( y[i] == 0 ) {

      yF[i]     = 0;
      yloweF[i] = ylowe[i];
      yupeF[i]  = yupe[i];
      pointstodelete.push_back(i);

    } else if (yB[i] == 0) {

      yF[i]     = 0;
      yloweF[i] = yloweB[i];
      yupeF[i]  = yupeB[i];
      pointstodelete.push_back(i);

    } else {

      yF[i] = y[i] / yB[i];

      double relErr1Up = yupe[i] / y[i];
      double relErr2Up = yupeB[i] / yB[i];
      double relErrUp  = ( relErr1Up + relErr2Up ) * yF[i];
      yupeF[i]         = relErrUp;

      double relErr1Down = ylowe[i] / y[i];
      double relErr2Down = yloweB[i] / yB[i];
      double relErrDown  = ( relErr1Down + relErr2Down ) * yF[i];
      double maxUp       = ( y[i] + yupe[i]  ) / ( yB[i] - yloweB[i] );
      double maxDown     = ( y[i] - ylowe[i] ) / ( yB[i] + yupeB[i]  );
      yloweF[i]          = relErrDown;

      yupeF[i]  = maxUp - yF[i];
      yloweF[i] = yF[i] - maxDown;
      
    } // if
  } // for noBins

  TGraphAsymmErrors * ret = new TGraphAsymmErrors(noBins, xF, yF, xloweF, xupeF, yloweF, yupeF);
  return ret;
}


// return an histo with h integral in the first bin (!)
// and the corresponding error (sum of squares)
TH1F * getIntegratedHisto(TH1F * h) {
  double maxValue = 0;
  TH1F * intH = (TH1F *) h->Clone();

  for (int b = h->GetNbinsX(); b >= 0; b--) {
    double err         = 0;
    double ValueToFill = h->IntegralAndError(b, h->GetNbinsX(), err, "");
    // Return integral of bin contents in range [binx1,binx2] and its error
    // By default the integral is computed as the sum of bin contents in the range.
    // if option "width" is specified, the integral is the sum of
    // the bin contents multiplied by the bin width in x.
    // The error is computed using error propagation from the bin errors assumming that
    // all the bins are uncorrelated.

    if (ValueToFill > maxValue)
      maxValue = ValueToFill;

    intH->SetBinContent(b, ValueToFill);
    intH->SetBinError(b, err);
  } // for noBins

  return intH;
}


// save MC histos without PU reweighting
void createNoPVWeightsHisto(vector<PlotConfig> configs, TFile * output) {
  double lumi = 0;
  string currhname = "PreselCut_noPVPU";

  for (int conf = 0; conf < (int) configs.size(); ++conf) {

    if ((configs.at(conf)).isMC) {
      TFile *input = new TFile((configs.at(conf).filename).c_str(), "read");
      input->cd((configs.at(conf).dirName).c_str());

      TH1F * histoMC = (TH1F *) gDirectory->FindObjectAny(currhname.c_str());

      if (histoMC == 0) {
	cout << "noVertices Histo in MC NOT found!" << endl;
      } else if (histoMC != 0) {
	string canvasname = "noVerticesFrac" + configs.at(conf).filename;
	TCanvas * c = new TCanvas(canvasname.c_str(), canvasname.c_str());

	TLegend *legend = new TLegend(0.659, 0.586, 0.923, 0.919, "");
	legend->SetTextSize(0.04);

	legend->SetFillColor(0);

	histoMC->SetLineColor(2);
	histoMC->GetXaxis()->SetTitle("#primary Vertices");
	histoMC->GetYaxis()->SetTitle("fraction of events");

	if (histoMC->GetSumw2N() == 0)
	  histoMC->Sumw2();
	//histoMC->Scale(1 / histoMC->Integral());

	cout << "@@@@@@@@@@@@@@@@@@@@@ no PV fraction in MC:" << configs.at(conf).filename << endl;
	cout << "{ ";
	for (int bin = 1; bin <= histoMC->GetNbinsX() + 1; bin++) {
	  cout << histoMC->GetBinContent(bin) << ", ";
	}
	cout << " }" << endl;

	histoMC->Draw("");
	legend->AddEntry(histoMC, "Sim.", "l");
	legend->Draw("same");
	drawCmsPrel(lumi, "", false, 0, false);
	output->WriteTObject(c, 0, "overwrite");

      }
      input->Close();
      delete input;
    }
  }
}


void makeSignalToBackgroundPlots(TList * signal, TH1F * background, string addLabelInHisto, double normToLumi, bool isData, bool isMC, string outputdir, TFile* output) {

	string currhname = background->GetName();
	//cout << "NEUES SB HISTO:" << currhname << endl;
	string canvasname = "c_" + currhname + "_SB";

	TCanvas * canv = new TCanvas(canvasname.c_str(), canvasname.c_str());

	canv->SetLogy(0);
	gPad->SetLogy(0);
	gPad->Update();
	canv->Update();
	TLegend *legend = new TLegend(0.56, 0.69, 0.83, 0.80, "");
	legend->SetTextSize(0.04);
	legend->SetFillColor(10);
	legend->SetFillStyle(1001);

	string xAxisTitle = "" + getAxisTitle(currhname);
	//cout << "XAXIS:" << xAxisTitle << endl;
	TH1F * bkg = (TH1F *) getIntegratedHisto(background);
	bkg->GetXaxis()->SetLabelSize(0.05);
	bkg->GetXaxis()->SetTitleSize(0.05);
	bkg->GetXaxis()->SetTitle(xAxisTitle.c_str());
	string newytitle = bkg->GetYaxis()->GetTitle();
	bkg->GetYaxis()->SetRangeUser(0, 2);
	newytitle = "S/#sqrt{S+B}";

	bkg->GetYaxis()->SetTitle(newytitle.c_str());
	int noH = 0;
	TH1F * legdummy = new TH1F("legdummy", "legdummy", 5, 0, 100);

	legdummy->SetFillColor(0);
	legdummy->SetLineColor(0);
	//	legend->SetHeader("GGM m_{#tilde{q}}/m_{#tilde{g}}/m_{#tilde{#chi}^{0}_{1}} [GeV]");

	TIter keyH(signal);
	while (TObject * obj = (TObject *) keyH()) {
		TH1F * sig = ((TH1F *) getIntegratedHisto(((TH1F*) obj)));
		sig->GetYaxis()->SetTitle(newytitle.c_str());
		sig->GetYaxis()->SetRangeUser(0, 15);
		sig->GetXaxis()->SetTitleSize(0.05);
		sig->GetXaxis()->SetLabelSize(0.05);
		sig->GetXaxis()->SetTitle(xAxisTitle.c_str());
		TH1F * sPlusB = (TH1F *) bkg->Clone();
		if (sPlusB->GetSumw2N() == 0)
			sPlusB->Sumw2();
		sPlusB->Add((TH1F *) sig->Clone());

		if (sig->GetSumw2N() == 0)
			sig->Sumw2();
		sig->Divide((TH1F *) getSqrt(sPlusB, "sqrtsb"));

		if (noH == 0) {
			sig->Draw("hist");
		} else {
			sig->Draw("same hist");
		}
		legend->AddEntry(sig, sig->GetTitle(), "l");
		noH++;

	}

	//legend->SetHeader(addLabelInHisto.c_str());
	legend->Draw("same");
	//HistoDrawUtil::cmsPrel(normToLumi, 1, isData, isMC);
	drawCmsPrel(normToLumi, "", false, 0, false, addLabelInHisto);
	canv->Update();
	gPad->Update();
	//cout << "save:" << outputdir << endl;
	canv->SaveAs((outputdir + "_SB" + ".pdf").c_str());
	canv->Print((outputdir + "_SB" + ".eps").c_str());
	output->WriteTObject(canv, 0, "overwrite");
	delete legdummy;
}
void makeSignalToBackgroundErrPlots(TList * signal, TH1F * background, string addLabelInHisto, double normToLumi, bool isData, bool isMC, string outputdir, TFile* output) {

	string currhname = background->GetName();
	//cout << "NEUES SB HISTO:" << currhname << endl;
	string canvasname = "c_" + currhname + "_SdB2";

	TCanvas * canv = new TCanvas(canvasname.c_str(), canvasname.c_str());

	canv->SetLogy(0);
	gPad->SetLogy(0);
	gPad->Update();
	canv->Update();
	TLegend *legend = new TLegend(0.56, 0.69, 0.83, 0.80, "");
	legend->SetTextSize(0.04);
	legend->SetFillColor(10);
	legend->SetFillStyle(1001);

	string xAxisTitle = "" + getAxisTitle(currhname);
	//cout << "XAXIS:" << xAxisTitle << endl;
	TH1F * bkg = (TH1F *) getIntegratedHisto(background);
	bkg->GetXaxis()->SetLabelSize(0.05);
	bkg->GetXaxis()->SetTitleSize(0.05);
	bkg->GetXaxis()->SetTitle(xAxisTitle.c_str());
	string newytitle = bkg->GetYaxis()->GetTitle();
	bkg->GetYaxis()->SetRangeUser(0, 2);
	newytitle = "S/#sqrt{S+#sigma_{B}^{2}}";

	bkg->GetYaxis()->SetTitle(newytitle.c_str());
	int noH = 0;
	TH1F * legdummy = new TH1F("legdummy", "legdummy", 5, 0, 100);

	legdummy->SetFillColor(0);
	legdummy->SetLineColor(0);
	//	legend->SetHeader("GGM m_{#tilde{q}}/m_{#tilde{g}}/m_{#tilde{#chi}^{0}_{1}} [GeV]");

	TIter keyH(signal);
	while (TObject * obj = (TObject *) keyH()) {
		TH1F * sig = ((TH1F *) getIntegratedHisto(((TH1F*) obj)));
		sig->GetYaxis()->SetTitle(newytitle.c_str());

		sig->GetXaxis()->SetTitleSize(0.05);
		sig->GetXaxis()->SetLabelSize(0.05);
		sig->GetXaxis()->SetTitle(xAxisTitle.c_str());
		//		cout << "Add signal BEFORE:" << sig->GetBinLowEdge(1) << endl;
		//		cout << "Add signal BEFORE:" << sig->GetBinLowEdge(sig->GetNbinsX())
		//				<< endl;
		//		cout << "To bkg BEFORE :" << bkg->GetBinLowEdge(1) << endl;
		//		cout << "To bkg  BEFORE:" << bkg->GetBinLowEdge(bkg->GetNbinsX())
		//				<< endl;
		TH1F * dB2 = (TH1F *) getErr2(bkg, "db2Clone");
		if (dB2->GetSumw2N() == 0)
			dB2->Sumw2();
		///
		//		cout << "Add signal:" << sig->GetBinLowEdge(1) << endl;
		//		cout << "Add signal:" << sig->GetBinLowEdge(sig->GetNbinsX()) << endl;
		//		cout << "To bkg :" << dB2->GetBinLowEdge(1) << endl;
		//		cout << "To bkg :" << dB2->GetBinLowEdge(dB2->GetNbinsX()) << endl;
		dB2->Add((TH1F *) sig->Clone("cl"));

		TH1F * SqrtsPlusdB2 = (TH1F *) getSqrt(dB2, "SqrtsPlusdB2");
		if (sig->GetSumw2N() == 0)
			sig->Sumw2();

		sig->Divide(SqrtsPlusdB2);

		sig->GetYaxis()->SetRangeUser(0, 15);
		sig->GetXaxis()->SetRangeUser(0, 1000);

		if (noH == 0) {
			sig->Draw("hist");
		} else {
			sig->Draw("same hist");
		}
		legend->AddEntry(sig, sig->GetTitle(), "l");
		noH++;

	}

	//legend->SetHeader(addLabelInHisto.c_str());
	legend->Draw("same");
	//HistoDrawUtil::cmsPrel(normToLumi, 1, isData, isMC);
	drawCmsPrel(normToLumi, "", false, 0, false, addLabelInHisto);
	canv->Update();
	gPad->Update();
	//cout << "save:" << outputdir << endl;
	canv->SaveAs((outputdir + "_SdB2" + ".pdf").c_str());
	canv->Print((outputdir + "_SdB2" + ".eps").c_str());
	output->WriteTObject(canv, 0, "overwrite");
	delete legdummy;
}
void makeSignalToBackgroundBErrPlots(TList * signal, TH1F * background, string addLabelInHisto, double normToLumi, bool isData, bool isMC, string outputdir, TFile* output) {

	string currhname = background->GetName();
	//cout << "NEUES SB HISTO:" << currhname << endl;
	string canvasname = "c_" + currhname + "_BdB2";

	TCanvas * canv = new TCanvas(canvasname.c_str(), canvasname.c_str());

	canv->SetLogy(0);
	gPad->SetLogy(0);
	gPad->Update();
	canv->Update();
	TLegend *legend = new TLegend(0.56, 0.69, 0.83, 0.80, "");
	legend->SetTextSize(0.04);
	legend->SetFillColor(10);
	legend->SetFillStyle(1001);

	string xAxisTitle = "" + getAxisTitle(currhname);
	//cout << "XAXIS:" << xAxisTitle << endl;
	TH1F * bkg = (TH1F *) getIntegratedHisto(background);
	bkg->GetXaxis()->SetLabelSize(0.05);
	bkg->GetXaxis()->SetTitleSize(0.05);
	bkg->GetXaxis()->SetTitle(xAxisTitle.c_str());
	string newytitle = bkg->GetYaxis()->GetTitle();
	bkg->GetYaxis()->SetRangeUser(0, 2);
	newytitle = "S/sqrt(B+dB^2)";

	bkg->GetYaxis()->SetTitle(newytitle.c_str());
	int noH = 0;
	TH1F * legdummy = new TH1F("legdummy", "legdummy", 5, 0, 100);

	legdummy->SetFillColor(0);
	legdummy->SetLineColor(0);
	//	legend->SetHeader("GGM m_{#tilde{q}}/m_{#tilde{g}}/m_{#tilde{#chi}^{0}_{1}} [GeV]");

	TIter keyH(signal);
	while (TObject * obj = (TObject *) keyH()) {
		TH1F * sig = ((TH1F *) getIntegratedHisto(((TH1F*) obj)));
		sig->GetYaxis()->SetTitle(newytitle.c_str());

		sig->GetXaxis()->SetTitleSize(0.05);
		sig->GetXaxis()->SetLabelSize(0.05);
		sig->GetXaxis()->SetTitle(xAxisTitle.c_str());
		TH1F * dB2 = (TH1F *) getErr2(bkg, "db2Clone");
		if (dB2->GetSumw2N() == 0)
			dB2->Sumw2();
		dB2->Add((TH1F *) bkg->Clone("cl"));

		TH1F * SqrtsPlusdB2 = (TH1F *) getSqrt(dB2, "SqrtsPlusdB2");
		if (sig->GetSumw2N() == 0)
			sig->Sumw2();

		sig->Divide(SqrtsPlusdB2);

		sig->GetYaxis()->SetRangeUser(0, 15);
		sig->GetXaxis()->SetRangeUser(0, 1000);

		if (noH == 0) {
			sig->Draw("hist");
		} else {
			sig->Draw("same hist");
		}
		legend->AddEntry(sig, sig->GetTitle(), "l");
		noH++;

	}

	//legend->SetHeader(addLabelInHisto.c_str());
	legend->Draw("same");
	//HistoDrawUtil::cmsPrel(normToLumi, 1, isData, isMC);
	drawCmsPrel(normToLumi, "", false, 0, false, addLabelInHisto);
	canv->Update();
	gPad->Update();
	//cout << "save:" << outputdir << endl;
	canv->SaveAs((outputdir + "_SdB2" + ".pdf").c_str());
	canv->Print((outputdir + "_SdB2" + ".eps").c_str());
	output->WriteTObject(canv, 0, "overwrite");
	delete legdummy;
}


//
void makePlotsInBinsOfPerDatasample( string histoname, string addLabelInLegend, vector<double> binRanges, 
				     string outputdir, TFile* output, bool norm, string sampleName, 
				     double normToLumi, bool isData, bool isMC ) {

  string canvasname = "c_" + histoname + sampleName + "_projX";

  if (norm)
    canvasname = canvasname + "_NORM";

  TCanvas * canv = new TCanvas(canvasname.c_str(), canvasname.c_str());
  canv->SetLogy(0);
  gPad->SetLogy(0);
  gPad->Update();
  canv->Update();

  TLegend *legend = new TLegend(0.59, 0.71, 0.84, 0.87, "");
  legend->SetTextSize(0.04);
  legend->SetFillColor(10);
  legend->SetFillStyle(1001);
  legend->SetHeader(addLabelInLegend.c_str());

  string currhnameXOnly = replaceAllAfterFirstOccurenceOf(histoname, "Vs");

  string yaxistitle = "Number of Events / GeV";
  string xaxistitle = getAxisTitle(currhnameXOnly);

  double maxYValue = 0;
  double minYValue = 500;
  TH2F * histo2D = (TH2F *) gDirectory->FindObjectAny(histoname.c_str());

  if (histo2D->GetEntries() != 0) {
    TH1D * projX = histo2D->ProjectionX();

    if (projX->GetSumw2N() == 0)
      projX->Sumw2();
    if (norm && projX->Integral() != 0)
      projX->Scale(1 / projX->Integral());

    projX->GetXaxis()->SetTitle(xaxistitle.c_str());
    projX->GetYaxis()->SetTitle(yaxistitle.c_str());

    maxYValue = projX->GetBinContent(projX->GetMaximumBin());
  //minYValue = projX->GetBinContent(projX->GetMinimumBin());

    projX->SetName("first");
    projX->Draw();

    for (int b = 0; b < (int) binRanges.size(); ++b) {
      int lowerbinValue = binRanges[b];
      int higherbinValue = 0;

      if (b + 1 < (int) binRanges.size())
	higherbinValue = binRanges[b + 1];

      int higherbin = -1;
      
      if (higherbinValue != 0)
	higherbin = histo2D->GetYaxis()->FindBin(higherbinValue);

      int lowerbin = histo2D->GetYaxis()->FindBin(lowerbinValue);
      lowerbin += 1;

      int lowEdgeValue = static_cast<int> (histo2D->GetYaxis()->GetBinLowEdge(lowerbin));
      int upEdgeValue  = static_cast<int> (histo2D->GetYaxis()->GetBinUpEdge(higherbin));

      TH1D * proj = histo2D->ProjectionX("", lowerbin, higherbin);

      if (proj->GetSumw2N() == 0)
	proj->Sumw2();

      if (norm && proj->Integral() != 0)
	proj->Scale(1 / proj->Integral());

      if (proj->GetBinContent(proj->GetMaximumBin()) > maxYValue)
	maxYValue = 1.2 * proj->GetBinContent(proj->GetMaximumBin());

      if (proj->GetBinContent(proj->GetMinimumBin()) < minYValue && proj->GetBinContent(proj->GetMinimumBin()) > 0)
	minYValue = 0.5 * proj->GetBinContent(proj->GetMinimumBin());

      proj->GetYaxis()->SetRangeUser(0.1, maxYValue);

      proj->SetDirectory(0);
      proj->SetLineColor(b + 2);
      proj->SetMarkerColor(b + 2);
      proj->SetMarkerStyle(24 + b);

      string lowLegendLabel = getStringFromInt(lowEdgeValue);
      string upLegendLabel = getStringFromInt(upEdgeValue);
      string legendLabel = lowLegendLabel + " - " + upLegendLabel;

      if (higherbin == -1) 
	legendLabel = ">" + lowLegendLabel;

      legend->AddEntry(proj, legendLabel.c_str(), "p");
      proj->SetName(legendLabel.c_str());
      proj->DrawClone("same p");
    }

    legend->Draw("same");
    //cmsPrel(normToLumi, 1, isData, isMC);
    drawCmsPrel(normToLumi, "", false, 0, false);
    canv->Update();
    gPad->Update();
    string canvName = canv->GetName();

    outputdir = outputdir + canvName;
    canv->SaveAs((outputdir + ".pdf").c_str());
    canv->SaveAs((outputdir + ".eps").c_str());
    output->WriteTObject(canv, 0, "overwrite");
    delete canv;
  }

  return;
}


// add syst uncertainties to the histo bin errors
TH1F * readFileAndSetSystErrorsAccordingToSYSTHistos(string currhname, double lumiScaleFactor, double addMConlySyst) {

  //VS!!!
  if( currhname.compare("hthltCalo") == 0 ) 
    return 0;
  else if( currhname.compare("PreselCut_hthltCalo") == 0 ) 
    return 0;
  else if( currhname.compare("PreselCut_SYSTUP_hthltCalo") == 0 ) 
    return 0;
  else if( currhname.compare("PreselCut_SYSTDOWN_hthltCalo") == 0 ) 
    return 0;


  TH1F * hOrig = (TH1F *) gDirectory->FindObjectAny(currhname.c_str());
  TH1F * h     = (TH1F *) hOrig->Clone("");

  if (h != 0) {
    if (h->GetSumw2N() == 0)
      h->Sumw2();

    string currhnameSYSTUP   = currhname;
    string currhnameSYSTDOWN = currhname;

    if (containsSubstr(currhname, "PreselCut_")) {
      currhnameSYSTUP   = replaceSubstr(currhname, "PreselCut_", "PreselCut_SYSTUP_");
      currhnameSYSTDOWN = replaceSubstr(currhname, "PreselCut_", "PreselCut_SYSTDOWN_");
    } else {
      currhnameSYSTUP   = "SYSTUP_" + currhname;
      currhnameSYSTDOWN = "SYSTDOWN_" + currhname;
    }

    TH1F * hSYSTUPOrig = (TH1F *) gDirectory->FindObjectAny(currhnameSYSTUP.c_str());
    TH1F * hSYSTUP     = (TH1F *) hSYSTUPOrig->Clone("");
    if (hSYSTUP->GetSumw2N() == 0)
      hSYSTUP->Sumw2();

    TH1F * hSYSTDOWNOrig = (TH1F *) gDirectory->FindObjectAny(currhnameSYSTDOWN.c_str());
    TH1F * hSYSTDOWN     = (TH1F *) hSYSTDOWNOrig->Clone("");
    if (hSYSTDOWN->GetSumw2N() == 0)
      hSYSTDOWN->Sumw2();
    
    // Scale to lumi first to get stat errors right
    h->Scale(lumiScaleFactor);
    if (hSYSTUP != 0)
      hSYSTUP->Scale(lumiScaleFactor);
    if (hSYSTDOWN != 0)
      hSYSTDOWN->Scale(lumiScaleFactor);

    // Rebin histos
    TH1F *hRebinned;
    TH1F *hRebinnedSYSTUP;
    TH1F *hRebinnedSYSTDOWN;

    if(!containsSubstr(h->GetName(),"Filter") ) {
      std::vector<double> binEdges = getBinEdgesRebin(h);

      if( (binEdges.size()) > 1){
	hRebinned         = (TH1F*) h->Rebin(binEdges.size() - 1, h->GetName(), &(binEdges.front()));
	// DivideHistoByBinWidth(hRebinned);
	hRebinned->Scale(1,"width");

	hRebinnedSYSTUP   = (TH1F*) hSYSTUP->Rebin(binEdges.size() - 1, hSYSTUP->GetName(), &(binEdges.front()));
	hRebinnedSYSTUP->Scale(1,"width");

	hRebinnedSYSTDOWN = (TH1F*) hSYSTDOWN->Rebin(binEdges.size() - 1, hSYSTDOWN->GetName(), &(binEdges.front()));
	hRebinnedSYSTDOWN->Scale(1,"width");
      } else {
	hRebinned         = 0;
	hRebinnedSYSTUP   = 0;
	hRebinnedSYSTDOWN = 0;
      }

    } else {
      hRebinned = (TH1F*) h;
    } // if Filter

    // combine with syst error
    if ( hRebinned != 0 && hRebinnedSYSTUP != 0 && hRebinnedSYSTDOWN != 0 && 
	 !containsSubstr(h->GetName(),"Filter") ) {

      for (int b = 0; b < hRebinned->GetNbinsX(); b++) {
	double mainHistoContent   = hRebinned->GetBinContent(b);
	double systUpHistoContent = hRebinnedSYSTUP->GetBinContent(b);
	double systDnHistoContent = hRebinnedSYSTDOWN->GetBinContent(b);
	double systDiffUp         = fabs( (double) systUpHistoContent - mainHistoContent );
	double systDiffDown       = fabs( (double) mainHistoContent - systDnHistoContent );
	
	double systDiff = 0.;

 	if ( systDiffUp != 0. ) 
	  systDiff = ( systDiffUp + systDiffDown ) / 2.;
	
	// if sample is declared as MC only add 100% systematic error
	// ---> lower ISR/FSR uncerts to 50%
	// ---> systDiff is really 0 for ISR/FSR ?!
	if ( addMConlySyst!=0 && systDiff == 0 ) 
	  systDiff = mainHistoContent*addMConlySyst;
	
	double statErr = hRebinned->GetBinError(b);
	
	double combError = sqrt(systDiff * systDiff + statErr * statErr);
	hRebinned->SetBinError(b, combError);

      } // for noBins
    } // if histos != 0

    return hRebinned;
  } // if h != 0

  return 0;
}


// Set syst errors for 2D histos as | h - hSYSTUP |
// and sums in quadrature with stat error
TH2F * readFileAndSetSystErrorsAccordingToSYSTHistos2D(string currhname, double lumiScaleFactor, double addMConlySyst) {

  TH2F * h = (TH2F *) gDirectory->FindObjectAny(currhname.c_str());

  if (h != 0) {

    if (h->GetSumw2N() == 0)
      h->Sumw2();
    string currhnameSYSTUP   = currhname;
    string currhnameSYSTDOWN = currhname;

    if (containsSubstr(currhname, "PreselCut_")) {
      currhnameSYSTUP   = replaceSubstr(currhname, "PreselCut_", "PreselCut_SYSTUP_");
      currhnameSYSTDOWN = replaceSubstr(currhname, "PreselCut_", "PreselCut_SYSTDOWN_");
    } else {
      currhnameSYSTUP   = "SYSTUP_" + currhname;
      currhnameSYSTDOWN = "SYSTDOWN_" + currhname;
    }

    TH2F * hSYSTUP = (TH2F *) gDirectory->FindObjectAny(currhnameSYSTUP.c_str());
    if (hSYSTUP->GetSumw2N() == 0)
      hSYSTUP->Sumw2();

    TH2F * hSYSTDOWN = (TH2F *) gDirectory->FindObjectAny(currhnameSYSTDOWN.c_str());
    if (hSYSTDOWN->GetSumw2N() == 0)
      hSYSTDOWN->Sumw2();

    // Scale to lumi first to get stat errors right
    h->Scale(lumiScaleFactor);
    if (hSYSTUP != 0)
      hSYSTUP->Scale(lumiScaleFactor);
    if (hSYSTDOWN != 0)
      hSYSTDOWN->Scale(lumiScaleFactor);

    // Now combine with syst error
    if (hSYSTUP != 0) {
      for (int b = 1; b <= h->GetNbinsX(); b++) {
	for (int c = 1; c <= h->GetNbinsY(); c++) {
	  double mainHistoContent   = h->GetBinContent(b, c);
	  double systUpHistoContent = hSYSTUP->GetBinContent(b, c);
	  double systDiff           = fabs( (double) systUpHistoContent - mainHistoContent );

	  // if sample is declared as mc only add 100% systematic error
	  // --->lower ISR/FSR uncerts to 50%
	  if (addMConlySyst!=0 && systDiff == 0) {
	    systDiff = mainHistoContent* addMConlySyst;
	  }

	  double statErr   = h->GetBinError(b, c);
	  double combError = sqrt(systDiff * systDiff + statErr * statErr);
	  h->SetBinError(b, c, combError);

	} // for y bins
      } // for x bins
    } //if hSYSTUP != 0
  } // if h != 0

  return h;
}


// Calculate error for Fake/Tight Efficiency
TH1F * makeRatioPlots(TList * signal, TH1F * background, string addLabelInHisto, string datasetLabel, double norm, double lumi, bool isData, bool isMC, string outputdir, TFile* output, bool calcEffAndFitCorr = false, int noJets = 3, string jetLabel = "") {

  string currhname = background->GetName();

  string canvasname = "c_" + currhname + "_RAT";
  if (norm) 
    canvasname = canvasname + "_NORM";

  
  TCanvas * canv = new TCanvas(canvasname.c_str(), canvasname.c_str());

  canv->SetLogy(0);
  gPad->SetLogy(0);
  gPad->Update();
  canv->Update();
  TLegend *legend = new TLegend(0.59, 0.71, 0.84, 0.87, "");
  legend->SetTextSize(0.04);
  legend->SetFillColor(10);
  legend->SetFillStyle(1001);
  legend->SetHeader(datasetLabel.c_str());
  string currhnameXOnly = replaceAllBeforeFirstOccurenceOf(currhname, "Vs");
  string xAxisTitle = getAxisTitle(currhnameXOnly);

  //  string newytitle = "w^{-1}";
  string newytitle = "weight";
  int count = 0;
  TIter keyH(signal);

  bool isFakeSelection = false;
  bool isFOSelection = false;

  TH1F * resRat = 0;

  while (TObject * obj = (TObject *) keyH()) {
    /* VS!!!
    TH1F * sig = (TH1F *) obj->Clone("bla");
    if (sig->GetSumw2N() == 0)
      sig->Sumw2();
    
    TH1F * bkg = (TH1F *) background->Clone("blabla");
    if (bkg->GetSumw2N() == 0)
      bkg->Sumw2();
    */
    TH1F * bkg = (TH1F *) obj->Clone("bla");
    if ( bkg->GetSumw2N() == 0 )
      bkg->Sumw2();
    
    TH1F * sig = (TH1F *) background->Clone("blabla"); // tight ID is passed in the 'background' position
    if ( sig->GetSumw2N() == 0 )
      sig->Sumw2();

    TH1F * effRat = divideHistos((TH1F *) sig->Clone("blabla1"), (TH1F *) bkg->Clone("blabla2"));

    effRat->GetYaxis()->SetTitle(newytitle.c_str());
    //    effRat->GetYaxis()->SetRangeUser(-0.5, 2.5); //VS!!!
    effRat->GetXaxis()->SetTitleSize(0.05);
    effRat->GetXaxis()->SetLabelSize(0.05);
    effRat->SetLineColor(((TH1F*) obj)->GetLineColor());
    effRat->SetMarkerColor(((TH1F*) obj)->GetLineColor());
    effRat->GetXaxis()->SetTitle(xAxisTitle.c_str());
    effRat->GetXaxis()->SetRangeUser(75, 1500);

    canv->cd();

    if (count == 0) {
      if (isMC) {
	effRat->SetMarkerSize(0);
	effRat->Draw("hist E");
      } else {
	effRat->Draw("X0");
      }
    } else {
      if (isMC) {
	effRat->SetLineStyle(2);
	effRat->SetLineWidth(3);
	effRat->SetMarkerSize(0);
	effRat->Draw("same hist E");
      } else {
	effRat->Draw("same X0");
      }
    }
    
    canv->cd();

    count++;
    if ( containsSubstr(obj->GetTitle(), "Fake")) 
      isFakeSelection = true;
    
    if ( containsSubstr(obj->GetTitle(), "FO") 
      || containsSubstr(obj->GetTitle(), "#gamma_{e}") 
      || containsSubstr(obj->GetTitle(), "#gamma_{jet}") ) 
      isFOSelection = true;
        
    //    string legendentry = "#gamma_{jet}/#gamma";
    string legendentry = "#gamma/#gamma_{jet}";
    
    legend->AddEntry(effRat, legendentry.c_str(), "l");
    
  }

  legend->SetHeader(datasetLabel.c_str());
  legend->Draw("same");
  //cmsPrel(lumi, 1, isData, isMC);
  drawCmsPrel(lumi, addLabelInHisto, false, noJets, false, jetLabel);

  canv->Update();
  gPad->Update();

  canv->SaveAs( (outputdir + "_RAT" + ".pdf").c_str() );
  canv->SaveAs( (outputdir + "_RAT" + ".eps").c_str() );
  canv->SaveAs( (outputdir + "_RAT" + ".root").c_str() );

  output->WriteTObject(canv, 0, "overwrite");

  delete canv;

  if (!calcEffAndFitCorr) {
    delete resRat;
    resRat = 0;
  }

  return resRat;
}


//
void makePlotsComparingFitResultsInDiffBins(string canvasname, TList * fittedRatHistsInBins, TFile* output, string outputdir, bool isData, bool isMC, double normToLumi) {
	int noBins = fittedRatHistsInBins->GetSize();
	if (noBins != 2) {
		cout << "ERROR - makePlotsComparingFitResultsInDiffBins is only implemented for exactly 2 input histos - but no of histos is:" << noBins << endl;
		return;
	}
	TCanvas * canv = new TCanvas(canvasname.c_str(), canvasname.c_str());
	canv->SetLogy(0);
	gPad->SetLogy(0);
	gPad->Update();
	canv->Update();
	TLegend *legend = new TLegend(0.479, 0.738, 0.920, 0.928, "");
	legend->SetFillColor(10);
	legend->SetFillStyle(1001);
	legend->SetTextSize(0.04);
	TH1F * fitRes1 = 0;
	TH1F * fitRes2 = 0;
	TIter keyH(fittedRatHistsInBins);
	int count = 0;
	while (TObject * obj = (TObject *) keyH()) {
		TH1F * fitRes = (TH1F *) obj;
		fitRes->SetLineColor(count + 1);
		fitRes->SetLineStyle(1);
		fitRes->SetMarkerColor(count + 1);
		fitRes->SetMarkerSize(0.9);
		if (count == 0)
			fitRes1 = (TH1F *) fitRes->Clone();
		if (count == 1)
			fitRes2 = (TH1F *) fitRes->Clone();
		legend->AddEntry(fitRes, fitRes->GetTitle(), "lp");
		count++;
	}

	canv->Update();
	gPad->Update();
	double maxYValue = fitRes1->GetBinContent(fitRes1->GetMaximumBin());
	if (fitRes2->GetBinContent(fitRes2->GetMaximumBin()) > maxYValue)
		maxYValue = fitRes2->GetBinContent(fitRes2->GetMaximumBin());
	fitRes1->GetYaxis()->SetRangeUser(0, maxYValue * 1.7);
	fitRes1->Draw("EP");
	fitRes2->Draw("sameEP");

	fitRes1->SetMarkerStyle(20);

	fitRes2->SetLineColor(2);
	fitRes2->SetMarkerColor(2);
	fitRes2->SetMarkerStyle(25);
	if (isMC) {
		//fitRes1->SetMarkerSize(0);
		//fitRes2->SetMarkerSize(0);
		//fitRes2->SetLineWidth(3);
		//fitRes2->SetLineStyle(2);
		fitRes2->DrawClone("EX0P");
		fitRes2->DrawClone("EX0Psame");
	} else {

		fitRes1->DrawClone("EX0P");
		fitRes2->DrawClone("sameEX0P");
	}

	canv->Update();
	gPad->Update();

	TH1F * relErrors = (TH1F*) fitRes1->Clone();
	if (relErrors->GetSumw2N() == 0)
		relErrors->Sumw2();
	relErrors->SetDirectory(0);
	relErrors->Add((TH1F *) fitRes2->Clone(), -1);

	relErrors->Divide(relErrors, (TH1F *) fitRes1->Clone(), 1, 1, "B");

	//	TGraphAsymmErrors * relErrBay = new TGraphAsymmErrors();
	//	relErrBay->BayesDivide(relErrors, fitRes1, "");
	//relErrors->Draw("same");
	legend->Draw("same");
	canv->Update();
	gPad->Update();
	string locoutputdir = outputdir + canvasname;
	//cout << "save:" << locoutputdir << endl;
	//canv->SaveAs((locoutputdir + "_COMPBINS" + ".pdf").c_str());
	canv->Print((locoutputdir + "_COMPBINS" + ".eps").c_str());
	output->WriteTObject(canv, 0, "overwrite");
	delete canv;
	//Draw rel fit res error in own Canvas
	if (relErrors != 0) {
		string canvasnameRelErr = canvasname + "RelErr";
		TCanvas * canvRelErr = new TCanvas(canvasnameRelErr.c_str(), canvasnameRelErr.c_str());
		relErrors->GetYaxis()->SetTitle("rel. Error ");
		relErrors->GetYaxis()->SetRangeUser(-0.1, 0.1);
		setErrorsToZero(relErrors);
		if (isMC) {
			relErrors->SetMarkerSize(1);
			relErrors->Draw("EX0P");
		} else {
			relErrors->SetMarkerSize(1);
			relErrors->Draw("EX0P");
		}

		canvRelErr->Update();
		//canvRelErr->SaveAs((outputdir + "_RATRelErr" + ".pdf").c_str());
		canvRelErr->Print((outputdir + "_RATRelErr" + ".eps").c_str());
		output->WriteTObject(canvRelErr, 0, "overwrite");
		delete canvRelErr;
		delete fitRes1;
		delete fitRes2;
		delete relErrors;
	}

}


//
void makePlotsInBinsOf( string histoname, string addLabelInLegend, string datasetLabel, 
			vector<double> binRanges, string outputdir, TFile* output, bool norm, 
			vector<PlotConfig> configs, double normToLumi, bool isData, bool isMC, 
			bool divideXNotYAxisInBins = false, bool calcEffAndMakeFit = false, 
			int noJets = 3, TList * trash = 0) {

  // read subdir for tight selection to get bin ranges
  TFile *input = new TFile((configs.at(0).filename).c_str(), "read");
  input->cd((configs.at(0).dirName).c_str());
  TH2F * histo2D = (TH2F *) readFileAndSetSystErrorsAccordingToSYSTHistos2D( histoname, normToLumi / configs.at(0).lumi, configs.at(0).MConlySyst );

  if(histo2D!=0){

    vector<int> lowerBinEdges;
    vector<int> upperBinEdges;
    vector<int> lowerBinEdgesLabel;
    vector<int> upperBinEdgesLabel;
    string jetlabel = "";

    if (divideXNotYAxisInBins)
      histo2D->GetXaxis()->GetNbins();

    for (int b = 0; b < (int) binRanges.size(); b++) {
      int lowerbinValue = binRanges[b];
      int higherbinValue = 0;

      if (b + 1 < (int) binRanges.size())
	higherbinValue = binRanges[b + 1];
      int higherbin = -1;

      if (higherbinValue != 0) {
	higherbin = histo2D->GetYaxis()->FindBin(higherbinValue);
	if (divideXNotYAxisInBins)
	  higherbin = histo2D->GetXaxis()->FindBin(higherbinValue);
      }

      int lowerbin = histo2D->GetYaxis()->FindBin(lowerbinValue);
      if (divideXNotYAxisInBins)
	lowerbin = histo2D->GetXaxis()->FindBin(lowerbinValue);

      if (b != 0)
	lowerbin += 1;

      int lowEdgeValue = 0;
      if (divideXNotYAxisInBins) {
	lowEdgeValue = static_cast<int> (histo2D->GetXaxis()->GetBinLowEdge(lowerbin));
      } else
	lowEdgeValue = static_cast<int> (histo2D->GetYaxis()->GetBinLowEdge(lowerbin));

      int upEdgeValue = 0;
      if (divideXNotYAxisInBins) {
	upEdgeValue = static_cast<int> (histo2D->GetXaxis()->GetBinUpEdge(higherbin));
      } else
	upEdgeValue = static_cast<int> (histo2D->GetYaxis()->GetBinUpEdge(higherbin));

      lowerBinEdges.push_back(lowerbin);
      upperBinEdges.push_back(higherbin);
      lowerBinEdgesLabel.push_back(lowEdgeValue);
      upperBinEdgesLabel.push_back(upEdgeValue);
      
    } // for binRange


    // loop over subdirs
    TList * fittedRatHistsInBins = new TList();

    for (int bin = 0; bin < (int) lowerBinEdges.size(); ++bin) {
      int lowerbin = lowerBinEdges[bin];
      int upperbin = (int) upperBinEdges[bin];
      int lowerbinValue = lowerBinEdgesLabel[bin];
      int upperbinValue = upperBinEdgesLabel[bin];

      string canvasname = "";
      canvasname = "c_" + histoname + "_Bin_From_";

      if (divideXNotYAxisInBins)
	canvasname = "c_DivideX" + histoname + "_Bin_From_";

      string canvasnameapp = getStringFromInt(lowerbinValue);
      canvasname = canvasname + canvasnameapp;
      canvasname = canvasname + "_CompTightLoose";
      canvasname = removeSpaces(canvasname);

      if (norm)
	canvasname = canvasname + "_NORM";

      TList * histosFake = new TList();
      TH1F * histoTight = 0;
      TCanvas * canv = new TCanvas(canvasname.c_str(), canvasname.c_str());
      canv->SetLogy(1);
      canv->Update();

      TLegend *legend = new TLegend(0.59, 0.65, 0.87, 0.86, "");
      legend->SetFillColor(10);
      legend->SetFillStyle(1001);
      legend->SetTextSize(0.045);
      legend->SetHeader(datasetLabel.c_str());
	
      string labelHeaderThisBin = addLabelInLegend;
      string lowbinLabel        = getStringFromInt(lowerbinValue);
      string upbinLabel         = getStringFromInt(upperbinValue);

      if ((int) upperbin == -1) {
	labelHeaderThisBin = addLabelInLegend + ">" + lowbinLabel + "GeV";
      }
      if ((int) lowerbinValue == 0) {
	labelHeaderThisBin = addLabelInLegend + "<" + upbinLabel + "GeV";
      }
      if (containsSubstr(addLabelInLegend, "MET")) {
	labelHeaderThisBin=replaceSubstr(labelHeaderThisBin, "MET", "#slash{E}_{T}");
      } else if (containsSubstr(addLabelInLegend, "#Jets")) {
	labelHeaderThisBin = "";
	jetlabel = "#geq1#gamma," + lowbinLabel + " jets";
      }

      if (containsSubstr(addLabelInLegend, "#JetsLowMet")) {
	labelHeaderThisBin = "#slash{E}_{T}< 100 GeV";
      }

      TH1F * legdummy = new TH1F("legdummy", "legdummy", 5, 0, 100);
      legdummy->SetFillColor(0);
      legdummy->SetLineColor(0);
	
      canv->Update();

      string currhnameXOnly = replaceAllBeforeFirstOccurenceOf(histoname, "_");
      currhnameXOnly = replaceAllAfterFirstOccurenceOf(currhnameXOnly, "Vs");

      string yaxistitle = "Number of Events / GeV";
      if (norm)
	yaxistitle = "Norm. " + yaxistitle;

      string xaxistitle = getAxisTitle(currhnameXOnly);

      if (divideXNotYAxisInBins) {
	string currhnameYOnly = replaceAllBeforeLastOccurenceOf(histoname, "Vs");
	xaxistitle = getAxisTitle(currhnameYOnly);
      }

      double maxYValue = 0;
      double minYValue = 500;

      for (int conf = 0; conf < (int) configs.size(); ++conf) {

	TFile *inputL = new TFile((configs.at(conf).filename).c_str(), "read");
	inputL->cd((configs.at(conf).dirName).c_str());

	TH2F * histo2Dconf = (TH2F *) readFileAndSetSystErrorsAccordingToSYSTHistos2D(histoname, normToLumi / configs.at(conf).lumi, configs.at(conf).MConlySyst);
	histo2Dconf->SetDirectory(0);

	//draw projection for current bin
	if (histo2Dconf != 0) {
	  TH1D * proj = 0;
	  if (divideXNotYAxisInBins) {
	    proj = histo2Dconf->ProjectionY("", lowerbin, upperbin);
	  } else {
	    proj = histo2Dconf->ProjectionX("", lowerbin, upperbin);
	  }
	  proj->SetDirectory(0);
	  if (proj->GetSumw2N() == 0)
	    proj->Sumw2();

	  string legendLabel = configs.at(conf).sampleName;

	  TH1F *projCloneToDrawTemp = (TH1F*) proj->Clone("cl");

	  //apply variable rebinning
	  projCloneToDrawTemp->SetName(xaxistitle.c_str());
	  std::vector<double> binEdges = getBinEdgesRebin(projCloneToDrawTemp);
	  TH1F *projCloneToDraw = (TH1F*) projCloneToDrawTemp->Rebin(binEdges.size() - 1, projCloneToDrawTemp->GetName(), &(binEdges.front()));
	  DivideHistoByBinWidth(projCloneToDraw);
	  projCloneToDraw->SetName(legendLabel.c_str());
	  projCloneToDraw->SetDirectory(0);
	  projCloneToDraw->SetTitle(legendLabel.c_str());
	  projCloneToDraw->SetLineColor((configs.at(conf).linecolor));
	  projCloneToDraw->SetMarkerColor((configs.at(conf).linecolor));
	  projCloneToDraw->SetMarkerStyle(24 + conf);
	  projCloneToDraw->GetYaxis()->SetTitle(yaxistitle.c_str());
	  projCloneToDraw->GetXaxis()->SetTitle(xaxistitle.c_str());
	  if (norm && projCloneToDraw->Integral() != 0)
	    projCloneToDraw->Scale(1 / projCloneToDraw->Integral());

	  if (projCloneToDraw->GetBinContent(projCloneToDraw->GetMaximumBin()) > maxYValue) {
	    maxYValue = projCloneToDraw->GetBinContent(projCloneToDraw->GetMaximumBin());
	  }

	  if (projCloneToDraw->GetBinContent(projCloneToDraw->GetMinimumBin()) < minYValue && projCloneToDraw->GetBinContent(proj->GetMinimumBin()) > 0) {
	    minYValue = projCloneToDraw->GetBinContent(projCloneToDraw->GetMinimumBin());
	  }

	  if (!norm) {
	    projCloneToDraw->GetYaxis()->SetRangeUser(0.1, 300 * maxYValue);
	  } else
	    projCloneToDraw->GetYaxis()->SetRangeUser(0, 1.2 * maxYValue);

	  if (conf == 0) {
	    if (isMC) {
	      projCloneToDraw->SetMarkerSize(0);
	      projCloneToDraw->Draw("histE");
	      legend->AddEntry(projCloneToDraw, legendLabel.c_str(), "l");
	    } else {
	      projCloneToDraw->Draw("EX0");
	      legend->AddEntry(projCloneToDraw, legendLabel.c_str(), "p");
	    }
	    
	    canv->Update();
	    histoTight = (TH1F *) projCloneToDraw->Clone();
	    histoTight->SetDirectory(0);
	  } else {

	    if (isMC) {
	      projCloneToDraw->SetMarkerSize(0);
	      projCloneToDraw->SetLineStyle(2);
	      projCloneToDraw->SetLineWidth(3);
	      projCloneToDraw->Draw("samehistE");
	      legend->AddEntry(projCloneToDraw, legendLabel.c_str(), "l");
	    } else {
	      projCloneToDraw->Draw("sameEX0");
	      legend->AddEntry(projCloneToDraw, legendLabel.c_str(), "p");
	    }
	    
	    TH1F * fake = (TH1F *) projCloneToDraw->Clone();
	    fake->SetDirectory(0);
	    histosFake->Add(fake);
	    
	  } // if conf ==0 	  
	  delete proj;
	} // if histo2Dconf != 0	
	inputL->Close();
      } // for configs

      legend->Draw("same");
      //cmsPrel(normToLumi, 1, isData, isMC);
      drawCmsPrel(normToLumi, labelHeaderThisBin, false, noJets, false, jetlabel);
      canv->Update();

      string canvName = canvasname;
      string locoutputdir = outputdir + canvName;
      canv->SaveAs((locoutputdir + ".pdf").c_str());
      canv->SaveAs((locoutputdir + ".eps").c_str());
      delete legdummy;
      output->WriteTObject(canv, 0, "overwrite");
      delete canv;
      canv = 0;
      delete legend;
      legend = 0;

      if (!norm) {
	string canvasnameWoC_ = replaceAllBeforeFirstOccurenceOf(canvasname, "c_");
	histoTight->SetName(canvasnameWoC_.c_str());
	TH1F * fitRatPlotInCurrBin = makeRatioPlots( histosFake, histoTight, labelHeaderThisBin, datasetLabel,
						     norm, normToLumi, isData, isMC, locoutputdir, output, 
						     calcEffAndMakeFit, noJets, jetlabel );
	/*
	TH1F * fitRatPlotInCurrBin = makeRatioPlots( histoTight, histosFake, labelHeaderThisBin, datasetLabel, 
						     norm, normToLumi, isData, isMC, locoutputdir, output, 
						     calcEffAndMakeFit, noJets, jetlabel );
	*/
	if (fitRatPlotInCurrBin != 0) {
	  fitRatPlotInCurrBin->SetTitle(labelHeaderThisBin.c_str());
	  fittedRatHistsInBins->Add(fitRatPlotInCurrBin);	  
	} // if fitRatPlotInCurrBin
      } // if !norm

    } // for lowerBinEdges

    input->Close();
    delete input;

    for (int conf = 0; conf < (int) configs.size(); ++conf) {
      TFile *inputconf = new TFile((configs.at(conf).filename).c_str(), "read");
      inputconf->cd((configs.at(conf).dirName).c_str());

      string sampleaddLabelInLegend = (configs.at(conf).sampleName) + ": " + addLabelInLegend;
      string sampleNameString = configs.at(conf).dirName;
      makePlotsInBinsOfPerDatasample(histoname, sampleaddLabelInLegend, binRanges, outputdir, output, norm, sampleNameString, normToLumi, isData, isMC);

      inputconf->Close();
      delete inputconf;
    } // for configs

  } // if histo2D != 0

  return;
}


//
void makeRatioPlotLastTwoHistos(TList * signal, string addLabelInHisto, double normToLumi, bool isData, bool isMC, string outputdir, TFile* output, int noJets = 0) {
	if (signal->GetSize() >= 2) {

		string currhname = ((TH1F *) signal->At(signal->GetSize() - 1))->GetTitle();
		string canvasname = addLabelInHisto + "_RAT";

		TCanvas * canv = new TCanvas(canvasname.c_str(), canvasname.c_str());

		canv->SetLogy(0);
		gPad->SetLogy(0);
		gPad->Update();
		canv->Update();

		string xAxisTitle = getAxisTitle(currhname);
		//cout << "XAXIS:" << xAxisTitle << endl;
		double maxYValue = 0;
		TH1F * nominator = (TH1F *) (signal->At(signal->GetSize() - 1))->Clone();
		TH1F * denominator = (TH1F *) (signal->At(signal->GetSize() - 2))->Clone();
		TH1F * rat = nominator;
		string yaxistitle = "";//nominator->GetYaxis()->GetTitle();
		yaxistitle = yaxistitle + "" + nominator->GetTitle() + "/";
		yaxistitle = yaxistitle + "" + denominator->GetTitle() + "";
		rat->GetYaxis()->SetTitle(yaxistitle.c_str());
		rat->Divide(nominator, denominator, 1, 1, "");
		rat->Draw("");
		drawCmsPrel(normToLumi, "", false, noJets, false);
		//cmsPrel(normToLumi, 1, isData, isMC);

		canv->Update();
		gPad->Update();
		//cout << "save:" << outputdir << endl;
		canv->SaveAs((outputdir + "_RAT" + ".pdf").c_str());
		canv->Print((outputdir + "_RAT" + ".eps").c_str());
		canv->SaveAs((outputdir + "_RAT.root").c_str());
		output->WriteTObject(canv, 0, "overwrite");
		delete canv;

	}
}
;
void makeIntegralPlots(TList * signal, TList * data, TH1F * background, string addLabelInHisto, double normToLumi, bool isData, bool isMC, string outputdir, TFile* output) {

	string currhname = background->GetName();
	//cout << "NEUES INTEGRAL HISTO:" << currhname << endl;
	string canvasname = "c_" + currhname + "_INT";

	TCanvas * canv = new TCanvas(canvasname.c_str(), canvasname.c_str());

	canv->SetLogy(0);
	gPad->SetLogy(0);
	gPad->Update();
	canv->Update();
	TLegend *legend = new TLegend(0.47, 0.55, 0.82, 0.82, "");

	legend->SetFillColor(10);
	legend->SetFillStyle(1001);
	legend->SetTextSize(0.04);

	string xAxisTitle = getAxisTitle(currhname);
	//cout << "XAXIS:" << xAxisTitle << endl;
	double maxYValue = 0;
	TH1F * bkg = (TH1F *) getIntegratedHisto(background);
	bkg->GetXaxis()->SetLabelSize(0.05);
	bkg->GetXaxis()->SetTitleSize(0.05);
	bkg->GetXaxis()->SetTitle(xAxisTitle.c_str());
	string newytitle = bkg->GetYaxis()->GetTitle();
	string newxtitle = bkg->GetXaxis()->GetTitle();
	newytitle = "#scale[0.5]{#int} " + newytitle;
	newxtitle = "Cut on " + newxtitle;
	maxYValue = bkg->GetBinContent(bkg->GetMaximumBin());
	;
	bkg->GetYaxis()->SetTitle(newytitle.c_str());
	bkg->GetXaxis()->SetTitle(newxtitle.c_str());
	bkg->SetFillColor(17);
	bkg->SetLineColor(17);
	bkg->Draw("histE");
	TIter keyHData(data);
	while (TObject * obj = (TObject *) keyHData()) {
		TH1F * dat = ((TH1F *) getIntegratedHisto(((TH1F*) obj)));
		dat->GetYaxis()->SetTitle(newytitle.c_str());
		dat->GetXaxis()->SetTitleSize(0.05);
		dat->GetXaxis()->SetLabelSize(0.05);
		dat->GetXaxis()->SetTitle(xAxisTitle.c_str());
		dat->Draw("sameEX0");
		legend->AddEntry(dat, dat->GetTitle(), "p");
		if (dat->GetMaximumStored() > maxYValue)
			maxYValue = dat->GetBinContent(dat->GetMaximumBin());
		;
	}

	legend->AddEntry(bkg, "Background", "f");
	TH1F * legdummy = new TH1F("legdummy", "legdummy", 5, 0, 100);

	legdummy->SetFillColor(0);
	legdummy->SetLineColor(0);
	//	legend->AddEntry(legdummy, "GGM m_{#tilde{q}}/m_{#tilde{g}}/m_{#tilde{#chi}^{0}_{1}} [GeV]", "l");

	TIter keyH(signal);
	while (TObject * obj = (TObject *) keyH()) {
		TH1F * sig = ((TH1F *) getIntegratedHisto(((TH1F*) obj)));
		sig->GetYaxis()->SetTitle(newytitle.c_str());
		sig->GetXaxis()->SetTitleSize(0.05);
		sig->GetXaxis()->SetLabelSize(0.05);
		sig->GetXaxis()->SetTitle(xAxisTitle.c_str());
		sig->SetMarkerSize(0);
		sig->Draw("same histE");
		legend->AddEntry(sig, sig->GetTitle(), "l");
		if (sig->GetMaximumStored() > maxYValue)
			maxYValue = sig->GetBinContent(sig->GetMaximumBin());
		;
	}
	//	if (bkg != 0) {
	//		bkg->GetYaxis()->SetRangeUser(bkg->GetYaxis()->GetXmin(), 300
	//				* maxYValue);
	//	}
	//	canv->RedrawAxis();

	canv->Update();
	gPad->Update();
	bkg->GetYaxis()->SetRangeUser(0.2, maxYValue * 5);
	//gPad->SetLeftMargin(0.25);
	canv->SetLogy(1);
	gPad->SetLogy(1);
	//legend->SetHeader(addLabelInHisto.c_str());
	legend->Draw("same");
	//cmsPrel(normToLumi, 1, isData, isMC);
	drawCmsPrel(normToLumi, "", false, 0, false, addLabelInHisto);
	canv->Update();
	gPad->Update();
	//cout << "save:" << outputdir << endl;
	canv->SaveAs((outputdir + "_INT" + ".pdf").c_str());
	canv->Print((outputdir + "_INT" + ".eps").c_str());
	output->WriteTObject(canv, 0, "overwrite");

}


// make superimposed plots for fake rate comparison
// adding ratio plots at the bottom
void makeFakeRateComparisonPlots( bool norm, vector<string> histoNames, vector<PlotConfig> configs, 
				  string resultFolderName, string resultDir, TFile * output, string addLabelInHisto, 
				  bool isData, bool isMC, double normToLumi, bool drawRatioPad, 
				  int noJets, bool isPrediction = true, bool calcEffAndMakeFit = true ) {

  //make canvas for each histo
  for (int c = 0; c < (int) histoNames.size(); ++c) {
    TList * trash = new TList();
    string currhname = histoNames[c];

    string canvasname = "c_" + currhname;
    if (norm)
      canvasname = canvasname + "_NORM";
    
    TCanvas * canv = new TCanvas(canvasname.c_str(), canvasname.c_str());
    trash->Add(canv);
    if (!norm)
      canv->SetLogy(1);

    gPad->Update();
    canv->Update();

    TLegend *legend = new TLegend(0.59, 0.71, 0.84, 0.87, "");
    trash->Add(legend);
    legend->SetFillColor(10);
    legend->SetFillStyle(1001);
    legend->SetTextSize(0.04);
    legend->SetHeader(addLabelInHisto.c_str());

    //loop over all configs and draw histos in canvas
    string xaxistitle = getAxisTitle(currhname);
    double highestYValue = 0;

    TList * looseIdList = new TList();

    TH1F * tightIdHisto    = 0;
    TH1F * sumOfLooseHisto = 0;

    for (int conf = 0; conf < (int) configs.size(); ++conf) {
      TFile *input = new TFile((configs.at(conf).filename).c_str(), "read");

      input->cd((configs.at(conf).dirName).c_str());

      TH1F * h = (TH1F *) readFileAndSetSystErrorsAccordingToSYSTHistos(currhname, normToLumi / configs.at(conf).lumi, configs.at(conf).MConlySyst);

      if (h != 0) {
	canv->cd();
	canv->Update();
	gPad->Update();
	TH1F * hClone = (TH1F *) h->Clone();

	hClone->SetDirectory(0);

	canv->Update();
	gPad->Update();

	//axis labels
	double binwidth = hClone->GetXaxis()->GetBinWidth(1);

	bool isGeV = containsSubstr(xaxistitle, "[GeV]");
	string binwidthstr = HistoDrawUtil::getStringFromDouble(binwidth, 1);

	if (containsSubstr(binwidthstr, ".0")) 
	  binwidthstr = HistoDrawUtil::getStringFromInt(binwidth);

	string yaxistitle = "Number of Events / GeV";
	
	if (norm) {
	  yaxistitle = "Norm. " + yaxistitle;
	  if (hClone->GetSumw2N() == 0)
	    hClone->Sumw2();
	  hClone->Scale(1 / hClone->Integral());
	}

	hClone->GetYaxis()->SetTitle(yaxistitle.c_str());
	hClone->GetXaxis()->SetTitle(xaxistitle.c_str());
	hClone->SetLineColor(configs.at(conf).linecolor);
	hClone->SetMarkerColor(configs.at(conf).linecolor);

	if (hClone->GetBinContent(hClone->GetMaximumBin()) > highestYValue)
	  highestYValue = hClone->GetBinContent(hClone->GetMaximumBin());

	//VS!!!
	if (!norm) {
	  hClone->GetYaxis()->SetRangeUser(0.05, 4 * highestYValue);
	  //	  hClone->GetYaxis()->SetRangeUser(0.05, 2 * highestYValue);

	  if (hClone->GetBinContent(hClone->GetMinimumBin()) < 0.1 && hClone->GetBinContent(hClone->GetMinimumBin()) > 0)
	    hClone->GetYaxis()->SetRangeUser(0.0005, 4 * highestYValue);
	  //	    hClone->GetYaxis()->SetRangeUser(0.0005, 2 * highestYValue);

	} else {
	  hClone->GetYaxis()->SetRangeUser(0, 2 * highestYValue);
	}
	

	canv->Update();
	gPad->Update();

	hClone->SetTitle((configs.at(conf).sampleName).c_str());

	if (hClone != 0) {
	  if (conf == 0) {

	    if (isMC) {
	      hClone->SetMarkerSize(0);
	      hClone->Draw("histE");
	      legend->AddEntry(hClone, (configs.at(conf).sampleName).c_str(), "l");
	    } else {
	      hClone->Draw("E X0");
	      legend->AddEntry(hClone, (configs.at(conf).sampleName).c_str(), "p");
	    }

	    tightIdHisto = hClone;

	  } else {

	    if (conf == 1 && isPrediction) {
	      if (isMC) {
		hClone->SetFillColor(hClone->GetLineColor());
		hClone->SetFillStyle(3004);
		hClone->SetMarkerSize(0);
		hClone->Draw("same hist ][ E2");
		legend->AddEntry(hClone, (configs.at(conf).sampleName).c_str(), "f");
	      } else {
		hClone->SetFillColor(hClone->GetLineColor());
		hClone->SetFillStyle(3004);
		hClone->SetMarkerSize(0);
		hClone->Draw("same hist ][ E2");
		legend->AddEntry(hClone, (configs.at(conf).sampleName).c_str(), "f");
	      }

	    } else {
	      if (isMC) {
		hClone->SetLineWidth(3);
		hClone->SetLineStyle(2);
		hClone->SetMarkerSize(0);
		hClone->Draw("same histE");
		legend->AddEntry(hClone, (configs.at(conf).sampleName).c_str(), "l");
	      } else {
		hClone->SetMarkerStyle(configs.at(conf).markerstyle);
		hClone->Draw("same E X0");
		legend->AddEntry(hClone, (configs.at(conf).sampleName).c_str(), "p");
	      }
	    }

	    looseIdList->Add(hClone);
	    if (sumOfLooseHisto != 0) {
	      sumOfLooseHisto->Add((TH1F *) hClone->Clone());
	      if (sumOfLooseHisto->GetSumw2N() == 0)
		sumOfLooseHisto->Sumw2();
	    }

	    else {
	      sumOfLooseHisto = (TH1F *) hClone->Clone();
	      sumOfLooseHisto->SetTitle("SUM Fakes");
	      sumOfLooseHisto->SetDirectory(0);
	    }
	  }

	  canv->Update();
	  gPad->Update();
	} // if hClone != 0
      } // if h != 0
      input->Close();
    } // for conf


    if (drawRatioPad && looseIdList->GetSize() != 0) {
      tightIdHisto->GetXaxis()->SetLabelSize(0);
      tightIdHisto->GetXaxis()->SetTitleSize(0);
      TIter keyLooseId(looseIdList);

      while (TObject * obj = (TObject *) keyLooseId()) {
	((TH1F*) obj)->GetXaxis()->SetLabelSize(0);
	((TH1F*) obj)->GetXaxis()->SetTitleSize(0);
      }

      canv->SetBottomMargin(0.2 + 0.8 * canv->GetBottomMargin() - 0.2 * canv->GetTopMargin());

      TPad *bRatioBottomPad = createRatioBottomPad();
      bRatioBottomPad->Draw();
      bRatioBottomPad->cd();
      //      gPad->SetLogy(1);
      gPad->SetLogy(0);
      TH1 * ax = (TH1*) ((TH1F*) tightIdHisto)->Clone("mycloneax");
      //      ax->SetMinimum(0.2);
      //      ax->SetMaximum(4.0);
      ax->SetMinimum(0.); //VS!!!
      ax->SetMaximum(2.);
      ax->GetYaxis()->SetNdivisions(505);
      ax->GetXaxis()->SetNdivisions(505);

      if (!isData) 
	ax->GetYaxis()->SetTitle("Sim./Pred.");
      else 
	ax->GetYaxis()->SetTitle("Data/Pred.");
      
      ax->GetYaxis()->SetLabelSize(0.03);
      ax->GetYaxis()->SetTitleSize(0.05);
      ax->GetYaxis()->SetLabelColor(1);
      //      ax->GetYaxis()->SetTitleOffset(0.05);
      ax->GetYaxis()->SetTitleOffset(1.3);

      ax->GetXaxis()->SetTitleSize(0.05);
      ax->GetXaxis()->SetLabelSize(0.05);
      ax->GetXaxis()->SetTicks("+");
      ax->GetXaxis()->SetTitle(xaxistitle.c_str());

      ax->Draw("axis");
      canv->Update();
      gPad->Update();
      bRatioBottomPad->cd();

      TH1F* ratio     = 0;
      TH1F* ratioSyst = 0;

      ratio = (TH1F*) ((TH1F*) tightIdHisto)->Clone("myclone");

      TH1F * looseHistoForRatio = (TH1F *) looseIdList->First();

      ratio->SetMarkerSize(1);
      if (ratio->GetSumw2N() == 0)
	ratio->Sumw2();
	
      //ratio->Divide(ratio, looseHistoForRatio, 1, 1, "");	
      ratio     = divideHistosForRatio(ratio, looseHistoForRatio);
      ratioSyst = getSystErrForRatio(looseHistoForRatio);

      ratio->Draw("p0e1x0,same");
      ratioSyst->Draw("same hist ][ E2");

      /*
      TLatex axlabel;
      axlabel.SetNDC(false);
      axlabel.SetTextFont(43);
      axlabel.SetTextSize(23);
      axlabel.SetTextColor(1);
      std::string out = "1";
      axlabel.DrawLatex(-20, 0.8, out.c_str());
      out = "3";
      axlabel.DrawLatex(-20, 2.8, out.c_str());
      out = "0.3";
      axlabel.DrawLatex(-38, 0.2, out.c_str());
      */
      canv->Update();
      gPad->Update();
      bRatioBottomPad->cd();
      TLine * line = new TLine(ratio->GetXaxis()->GetXmin(), 1, ratio->GetXaxis()->GetXmax(), 1);
      line->SetLineColor(1);
      line->SetLineWidth(1);
      line->Draw("same");
      canv->RedrawAxis();

      canv->Update();
      gPad->Update();

      canv->Update();
      gPad->Update();
    }

    legend->Draw("same");
    //cmsPrel(normToLumi, 1, isData, isMC);
    drawCmsPrel(normToLumi, "", false, noJets, false);

    canv->Update();
    gPad->Update();

    string outputdir = resultDir + "/" + resultFolderName + "/" + canv->GetName();
    //canv->SaveAs((outputdir + ".gif").c_str());
    canv->SaveAs((outputdir + ".pdf").c_str());
    canv->SaveAs((outputdir + ".eps").c_str());
    output->WriteTObject(canv, 0, "overwrite");
    //looseIdList->Add(sumOfLooseHisto);

    if (!norm)
      makeRatioPlots(looseIdList, tightIdHisto, addLabelInHisto, addLabelInHisto, norm, normToLumi, isData, isMC, outputdir, output, false, noJets);

    TIter nextTrash(trash);
    while (TObject * obj = (TObject *) nextTrash()) {
      //cout << "delete:" << obj->GetName() << endl;
      if (obj != 0)
	delete obj;
      obj = 0;
    }
  }

}


//
void makeTriggerEffPlots(string resultDir, TFile * input, string dirNominator,string nomTitle, string dirDenominator,string denomTitle,bool photonleg,bool htleg) {
	string outputdir = resultDir + "/" + "TriggerEfficiencies";
	system(("mkdir " + outputdir).c_str());
	TFile * output = new TFile((outputdir + "_plot.root").c_str(), "Update");
	setMyTDRStyle();
	gROOT->SetStyle("mytdrStyle");

	gStyle->SetPadGridX(1);
	gStyle->SetPadGridY(1);

	vector < string > histonames;
	if (htleg)
	 histonames.push_back("hthlt");
	if (photonleg)
	 histonames.push_back("photonTrigPt");

	for (int i = 0; i < (int) histonames.size(); ++i) {
		string histoname  = histonames.at(i);
		//		string histoname1 = histonames1.at(i);
		string canvasname = "TRIGGEREFF_" + nomTitle + "_" + denomTitle + "_" + histoname;
		TCanvas * canv = new TCanvas(canvasname.c_str(), canvasname.c_str());
		input->cd(dirDenominator.c_str());
		TH1F * histoDenominator = (TH1F*) gDirectory->FindObjectAny(histoname.c_str());
		input->cd(dirNominator.c_str());
		TH1F * histoNominator = (TH1F*) gDirectory->FindObjectAny(histoname.c_str());

		TGraphAsymmErrors * eff;
		eff = new TGraphAsymmErrors(histoNominator, histoDenominator);		

		eff->GetYaxis()->SetTitle("Efficiency");
		eff->GetXaxis()->SetTitle(getAxisTitle(histoname).c_str());
		if (photonleg) eff->GetXaxis()->SetTitle("Photon p_{T} [GeV]");
		//		if (photonleg)eff->GetXaxis()->SetRangeUser(70, 180);
		//		if (htleg)eff->GetXaxis()->SetRangeUser(350, 600);
		if (photonleg) eff->GetXaxis()->SetRangeUser(50, 500);
		if (htleg)     eff->GetXaxis()->SetRangeUser(300, 1000);

		eff->SetLineWidth(2);
		eff->SetMarkerStyle(20);
		eff->SetMarkerSize(0.6);
		eff->SetMarkerColor( eff->GetLineColor() );

		eff->SetMinimum(0.);
//		eff->SetMaximum(1.2);
		eff->SetMaximum(1.25);
		eff->Draw("AEP");

		if (photonleg) eff->Fit("pol0","","",80,500);
		//		if (photonleg) eff->Fit("pol0","","",200,500);

		TLine ll;
		ll.SetLineColor(2);
		ll.SetLineWidth(1);
		ll.SetLineStyle(7);
		if (photonleg) ll.DrawLine(80.,0.,80.,1.25);
		if (htleg) ll.DrawLine(450.,0.,450.,1.25);

		TLatex l;
		l.SetTextAlign(12);
		l.SetTextSize(0.04);
		l.SetTextFont(42);
		l.SetNDC();

		l.DrawLatex(0.16, 0.93, "#int#it{L}dt = 19.8 fb^{-1}  #sqrt{s} = 8 GeV - 22Jan2013 ReReco");
		//		l.DrawLatex(0.16, 0.93, "#int#it{L}dt = 12.7 fb^{-1}  #sqrt{s} = 8 GeV - 22Jan2013 ReReco");
		//		l.DrawLatex(0.20, 0.93, "#int#it{L}dt = 11.2 fb^{-1}  #sqrt{s} = 8 GeV  2012");
		//              l.DrawLatex(0.20, 0.93, "#int#it{L}dt = 6.8 fb^{-1}  #sqrt{s} = 8 GeV  2012Cv2");
		//		l.DrawLatex(0.20, 0.93, "#int#it{L}dt = 4.04 fb^{-1}  #sqrt{s} = 8 GeV");
		//		l.DrawLatex(0.20, 0.93, "HLT_PFHT350  #sqrt{s} = 8 GeV");
		//		l.DrawLatex(0.28, 0.84, "HLT_PFHT650");
		//		l.DrawLatex(0.39, 0.84, "HLT_PFNoPUHT650");
		//		l.DrawLatex(0.28, 0.84, "HLT_PFHT650, HLT_PFNoPUHT650");
		l.DrawLatex(0.28, 0.84, "HLT_Photon75");
		//		l.DrawLatex(0.28, 0.84, "HLT_Photon150");
		//		l.DrawLatex(0.28, 0.84, "HLT_Ele27_WP80");
		//		l.DrawLatex(0.26, 0.84, "HLT_Photon75_CaloIdVL");
		//
		//		if(photonleg) l.DrawLatex(0.26, 0.79, "H_{T} > 450 GeV");
		//		if(htleg) l.DrawLatex(0.26, 0.79, "1st Photon p_{T} > 85 GeV");
		/*
		if(photonleg) l.DrawLatex(0.28, 0.79, "H_{T} > 750 GeV");
		if(htleg) l.DrawLatex(0.28, 0.79, "1st Photon p_{T} > 160 GeV");
		*/
		if(photonleg) l.DrawLatex(0.28, 0.79, "H_{T} > 450 GeV");
		if(htleg) l.DrawLatex(0.28, 0.79, "1st Photon p_{T} > 85 GeV");
		//		if(htleg) l.DrawLatex(0.28, 0.79, "1st Photon p_{T} > 80 GeV");
		//		if(htleg) l.DrawLatex(0.28, 0.79, "1st Electron p_{T} > 80 GeV");
		//		if(photonleg) l.DrawLatex(0.20, 0.95, "Events with H_{T} > 450 GeV");
		//		if(htleg) l.DrawLatex(0.20, 0.95, "Events with Photon p_{T} > 80 GeV");
		//		if(htleg) l.DrawLatex(0.20, 0.95, "Events with Photon p_{T} > 85 GeV");
		//
		//cout << "save:" << outputdir + "/" + canvasname << endl;
		canv->SaveAs((outputdir + "/" + canvasname + ".pdf").c_str());
		canv->Print((outputdir + "/" + canvasname + ".eps").c_str());
		canv->Print((outputdir + "/" + canvasname + ".png").c_str());

		output->WriteTObject(canv, 0, "overwrite");


		TCanvas * cc = new TCanvas( ( canvasname + "_test" ).c_str() , 
					    ( canvasname + "_test" ).c_str() ) ;
		cc->cd();
		//		histoDenominator->SetOptStats(0);
		//		histoDenominator->GetYaxis()->SetTitle("Events");

		if (photonleg) histoDenominator->GetXaxis()->SetTitle("Photon p_{T} [GeV]");
		if (photonleg) histoDenominator->GetXaxis()->SetRangeUser(50, 500);
		if (htleg) histoDenominator->GetXaxis()->SetTitle("H_{T} [GeV]");
		if (htleg) histoDenominator->GetXaxis()->SetRangeUser(300, 1000);
		histoDenominator->SetLineColor(2);
		histoDenominator->Draw();
		histoNominator->SetLineColor(4);
		histoNominator->Draw("same");
		if (photonleg) l.DrawLatex(0.20, 0.95, "Events with H_{T} > 750 GeV");		
		//		if (htleg) l.DrawLatex(0.20, 0.95, "Events with Photon p_{T} > 85 GeV");	
		if (htleg) l.DrawLatex(0.20, 0.95, "Events with Photon p_{T} > 160 GeV");	


		cc->SaveAs((outputdir + "/" + canvasname + "_test.pdf").c_str());
		cc->SaveAs((outputdir + "/" + canvasname + "_test.eps").c_str());
		output->WriteTObject(cc, 0, "overwrite");

		cc->SetLogy();
		//		histoDenominator->Draw();
		//		histoNominator->Draw("same");
		cc->SaveAs((outputdir + "/" + canvasname + "_test_log.pdf").c_str());
		cc->SaveAs((outputdir + "/" + canvasname + "_test_log.eps").c_str());


		Bool_t test = false;

		if( htleg && test ){
		TCanvas * cc2 = new TCanvas( ( canvasname + "_calo" ).c_str() , 
					     ( canvasname + "_calo" ).c_str() ) ;
		cc2->cd();
		cc2->Divide(2,2);

		input->cd(dirDenominator.c_str());
		TH1F * histoDenominator1 = (TH1F*) gDirectory->FindObjectAny("hthltCalo");
		TH2F * histoDenominator2 = (TH2F*) gDirectory->FindObjectAny("HTHLTvsHTHLTcalo");
		input->cd(dirNominator.c_str());
		TH1F * histoNominator1 = (TH1F*) gDirectory->FindObjectAny("hthltCalo");
		TH2F * histoNominator2 = (TH2F*) gDirectory->FindObjectAny("HTHLTvsHTHLTcalo");

		cc2->cd(1);
		histoNominator->GetXaxis()->SetTitle("H_{T} [GeV]");
		histoNominator->GetXaxis()->SetRangeUser(200, 1500);
		histoNominator->SetLineColor(2);
		histoNominator->Draw();
		histoNominator1->SetLineColor(4);
		histoNominator1->Draw("same");

		cc2->cd(2);
		histoDenominator->GetXaxis()->SetTitle("H_{T} [GeV]");
		histoDenominator->GetXaxis()->SetRangeUser(200, 1500);
		histoDenominator->SetLineColor(2);
		histoDenominator->Draw();
		histoDenominator1->SetLineColor(4);
		histoDenominator1->Draw("same");

		cc2->cd(3);
		histoNominator2->Draw("colz");

		cc2->cd(4);
		histoDenominator2->Draw("colz");


		cc2->SaveAs((outputdir + "/" + canvasname + "_calo.pdf").c_str());
		cc2->SaveAs((outputdir + "/" + canvasname + "_calo.eps").c_str());
		output->WriteTObject(cc2, 0, "overwrite");
		}


	}

}
;

void makeMetCompPlots(string resultDir, TFile * input) {
	string outputdir = resultDir + "/" + "MetComparisons";
	system(("mkdir " + outputdir).c_str());
	TFile * output = new TFile((outputdir + "_plot.root").c_str(), "Recreate");
	setMyTDRStyle();
	gROOT->SetStyle("mytdrStyle");

	vector < string > histonames;
	histonames.push_back("PreselCut_metRawPt");
	histonames.push_back("PreselCut_metT1Pt");
	histonames.push_back("PreselCut_metT2Pt");
	input->cd("select_All");
	string canvasname = "METCOMP";

	TCanvas * canv = new TCanvas(canvasname.c_str(), canvasname.c_str());

	canv->SetLogy(1);
	gPad->SetLogy(1);
	TH1F * histo = (TH1F*) gDirectory->FindObjectAny("PreselCut_metPtRaw");
	TH1F * histoT1 = (TH1F*) gDirectory->FindObjectAny("PreselCut_metPtT1");
	TH1F * histoT2 = (TH1F*) gDirectory->FindObjectAny("PreselCut_metPtT2");
	histo->GetXaxis()->SetRangeUser(0, 600);
	histo->GetXaxis()->SetTitle("MET[GeV]");
	//	histo->GetYaxis()->SetTitle("Number of Events / GeV"); 
	histo->GetYaxis()->SetTitle("Number of Events / Bin"); //VS!!!
	histo->Rebin(4);
	histoT1->Rebin(4);
	histoT2->Rebin(4);
	histo->SetMarkerStyle(20);
	histoT1->SetMarkerStyle(25);
	histoT2->SetMarkerStyle(22);
	histo->SetMarkerColor(1);
	histoT1->SetMarkerColor(4);
	histoT2->SetMarkerColor(2);
	histo->Draw();
	histoT1->SetLineColor(4);
	histoT1->Draw("same");
	histoT2->SetLineColor(2);
	histoT2->Draw("same");

	TLegend *legend = new TLegend(0.59, 0.71, 0.84, 0.87, "");
	legend->SetTextSize(0.04);
	legend->SetFillColor(10);
	legend->SetFillStyle(1001);
	legend->AddEntry(histo, "Raw", "lp");
	legend->AddEntry(histoT1, "Type-I", "lp");
	legend->AddEntry(histoT2, "Type-II", "lp");
	legend->Draw("same");

	//cout << "save:" << outputdir + "/" + canvasname << endl;
	canv->SaveAs((outputdir + "/" + canvasname + ".pdf").c_str());
	canv->Print((outputdir + "/" + canvasname + ".eps").c_str());
	output->WriteTObject(canv, 0, "overwrite");

}
;
void compareHistosSusyPhotonJetAnalysisMetShapeBetweenDatasamples(TFile * input1, TFile * input2, string resultFolderName, string resultDir, string leg1, string leg2, bool isData, bool isMC, double normToLumi, int noJets) {
	system(("mkdir " + resultDir).c_str());
	system(("mkdir " + resultDir + "/" + resultFolderName).c_str());
	setMyTDRStyle();
	gROOT->SetStyle("mytdrStyle");

	gStyle->SetHistLineWidth(2);
	gStyle->UseCurrentStyle();
	gROOT->ForceStyle(1);

	TFile * output = new TFile((resultDir + "/" + resultFolderName + "_plot.root").c_str(), "Recreate");
	vector < string > canvasnames;
	canvasnames.push_back("c_PreselCut_metVsPhotonPt_Bin_From_65_CompTightLoose");
	canvasnames.push_back("c_PreselCut_metVsPhotonPt_Bin_From_95_CompTightLoose");
	canvasnames.push_back("c_PreselCut_metVsPhotonPt_Bin_From_115_CompTightLoose");
	canvasnames.push_back("c_PreselCut_metVsPhotonPt_Bin_From_135_CompTightLoose");
	canvasnames.push_back("c_PreselCut_metVsPhotonPt_Bin_From_155_CompTightLoose");
	canvasnames.push_back("c_PreselCut_metVsPhotonPt_Bin_From_205_CompTightLoose");
	canvasnames.push_back("c_PreselCut_metVsPhotonPt_Bin_From_305_CompTightLoose");
	TList * ratioHistos = new TList();

	for (int c = 0; c < canvasnames.size(); c++) {
		string canvasname = canvasnames.at(c);
		string histoname = "Photon";

		TCanvas * canv1 = (TCanvas *) input1->FindObjectAny(canvasname.c_str());
		//cout << "canv1:" << canv1 << endl;
		TH1F * hist1 = (TH1F *) canv1->FindObject(histoname.c_str());
		//cout << "hist1:" << hist1 << endl;
		hist1->SetDirectory(0);
		hist1->GetXaxis()->SetRangeUser(0, 1500);
		TCanvas * canv2 = (TCanvas *) input2->FindObjectAny(canvasname.c_str());
		//cout << "canv2:" << canv2 << endl;
		TH1F * hist2 = (TH1F *) canv2->FindObject(histoname.c_str());
		//cout << "hist2:" << hist2 << endl;
		hist2->SetDirectory(0);
		hist2->GetXaxis()->SetRangeUser(0, 1500);
		hist1->Scale(1 / hist1->Integral());
		hist2->Scale(1 / hist2->Integral());

		double maxYValue = hist1->GetBinContent(hist1->GetMaximumBin());
		if (hist2->GetBinContent(hist2->GetMaximumBin()) > maxYValue)
			maxYValue = hist2->GetBinContent(hist2->GetMaximumBin());
		hist1->GetYaxis()->SetRangeUser(0.0001, 1500);

		output->ReOpen("Update");
		TCanvas * canv = new TCanvas(canvasname.c_str(), canvasname.c_str());
		;
		canv->SetLogy(1);
		gPad->SetLogy(1);

		gPad->Update();
		canv->Update();
		hist1->SetMarkerStyle(20);

		hist2->SetLineColor(2);
		hist2->SetMarkerColor(2);
		hist2->SetMarkerStyle(25);
		if (isMC) {
			hist1->SetMarkerSize(0);
			hist2->SetMarkerSize(0);
			//		hist2->SetLineWidth(3);
			//		hist2->SetLineStyle(2);
			hist1->DrawClone("histE");
			hist2->DrawClone("histEsame");
		} else {

			hist1->DrawClone("EX0P");
			hist2->DrawClone("sameEX0P");
		}
		//cmsPrel(normToLumi, 1, isData, isMC);
		drawCmsPrel(normToLumi, "", false, noJets, false);
		gPad->Update();
		canv->Update();

		TLegend *legend = new TLegend(0.59, 0.71, 0.84, 0.87, "");
		legend->SetTextSize(0.04);
		legend->SetFillColor(10);
		legend->SetFillStyle(1001);
		legend->AddEntry(hist1, leg1.c_str(), "lp");
		legend->AddEntry(hist2, leg2.c_str(), "lp");
		legend->Draw("same");
		string outputdir = resultDir + "/" + resultFolderName + "/" + canvasname;
		//cout << "save:" << outputdir << endl;
		canv->SaveAs((outputdir + "" + ".pdf").c_str());
		canv->Print((outputdir + "" + ".eps").c_str());
		output->WriteTObject(canv, 0, "overwrite");

		//create ratio histo
		TH1F * rat = (TH1F *) hist1->Clone();

		rat->Divide((TH1F *) hist2->Clone());
		rat->SetDirectory(0);
		ratioHistos->Add(rat);
		//delete canv;
	}
	string canvasname = "ShapeComparison_RAT";
	TCanvas * canvRat = new TCanvas(canvasname.c_str(), canvasname.c_str());

	TIter key(ratioHistos);
	int count = 0;
	while (TKey* keyHisto = (TKey*) key()) {

		string hname = keyHisto->GetName();
		//cout << "Draw!" << endl;
		if (count == 0)
			((TH1F *) keyHisto)->Draw("");
		else
			((TH1F *) keyHisto)->Draw("same");
		gPad->Update();
		canvRat->Update();
		count++;
	}
	string outputdir = resultDir + "/" + resultFolderName + "/" + canvasname;
	//cout << "save:" << outputdir << endl;
	canvRat->SaveAs((outputdir + "" + ".pdf").c_str());
	canvRat->Print((outputdir + "" + ".eps").c_str());
	output->WriteTObject(canvRat, 0, "overwrite");

	input1->Close();
	input2->Close();

}


// signal contamination plots
void compareHistosSusyPhotonJetAnalysisFakeBetweenDatasamples(TFile * input1, TFile * input2, string resultFolderName, string resultDir, string leg1, string leg2, bool isData, bool isMC, double normToLumi, int noJets) {

  system(("mkdir " + resultDir).c_str());
  system(("mkdir " + resultDir + "/" + resultFolderName).c_str());
  setMyTDRStyle();
  gROOT->SetStyle("mytdrStyle");

  gStyle->SetHistLineWidth(2);
  gStyle->UseCurrentStyle();
  gROOT->ForceStyle(1);

  TFile * output = new TFile((resultDir + "/" + resultFolderName + "_plot.root").c_str(), "Recreate");
  
  string canvasname = "c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RAT";
  string histoname = "blabla1clone2";

  TCanvas * canv1 = (TCanvas *) input1->FindObjectAny(canvasname.c_str());
  cout << "canv1:" << canv1 << endl;
  TH1F * hist1 = (TH1F *) canv1->FindObject(histoname.c_str());
  cout << "hist1:" << hist1 << endl;
  hist1->SetDirectory(0);
  hist1->GetXaxis()->SetRangeUser(75, 1500);
  TCanvas * canv2 = (TCanvas *) input2->FindObjectAny(canvasname.c_str());
  cout << "canv2:" << canv2 << " from input:" << input2->GetName() << endl;
  TH1F * hist2 = (TH1F *) canv2->FindObject(histoname.c_str());
  cout << "hist2:" << hist2 << endl;
  hist2->SetDirectory(0);
  hist2->GetXaxis()->SetRangeUser(75, 1500);

  double maxYValue = hist1->GetBinContent(hist1->GetMaximumBin());
  if (hist2->GetBinContent(hist2->GetMaximumBin()) > maxYValue)
    maxYValue = hist2->GetBinContent(hist2->GetMaximumBin());
  hist1->GetYaxis()->SetRangeUser(0.1, maxYValue * 1.2);

  TCanvas * canv = new TCanvas(canvasname.c_str(), canvasname.c_str());
	
  gPad->Update();
  canv->Update();
  hist1->SetMarkerStyle(20);
  
  hist2->SetLineColor(2);
  hist2->SetMarkerColor(2);
  hist2->SetMarkerStyle(25);
  hist2->SetLineColor(2);
  hist2->SetMarkerColor(2);
  hist2->SetMarkerStyle(25);
  string xaxistitle = hist1->GetXaxis()->GetTitle();
  hist1->GetXaxis()->SetTitle("");
  hist2->GetXaxis()->SetTitle("");
  hist1->GetXaxis()->SetNdivisions(505);
  hist2->GetXaxis()->SetNdivisions(505);
  hist1->GetXaxis()->SetLabelSize(0);
  hist2->GetXaxis()->SetLabelSize(0);
  hist2->GetXaxis()->SetNdivisions(505);
  if (isMC) {
    hist1->DrawClone("EX0P");
    hist2->DrawClone("EX0Psame");
  } else {
    hist1->DrawClone("EX0P");
    hist2->DrawClone("sameEX0P");
  }
  canv->SetBottomMargin(0.2 + 0.8 * canv->GetBottomMargin() - 0.2 * canv->GetTopMargin());
  TPad *bRatioBottomPad = createRatioBottomPad();
  bRatioBottomPad->Draw();
  bRatioBottomPad->cd();
  TH1 * ax = (TH1*) ((TH1F*) hist1)->Clone("mycloneax");
  ax->SetMinimum(0.9);
  ax->SetMaximum(1.1);
  ax->GetYaxis()->SetNdivisions(505);
  ax->GetXaxis()->SetNdivisions(505);

  ax->GetYaxis()->SetLabelSize(0.03);
  ax->GetYaxis()->SetTitle("Ratio");
  ax->GetYaxis()->SetTitleSize(0.05);
  ax->GetYaxis()->SetTitleOffset(0.05);
  ax->GetXaxis()->SetTitleSize(0.05);
  ax->GetYaxis()->SetTitleOffset(1.3);
  ax->GetXaxis()->SetLabelSize(0.05);
  ax->GetXaxis()->SetTicks("+");
  ax->GetXaxis()->SetTitle(xaxistitle.c_str());
  
  ax->Draw("axis");
  canv->Update();
  gPad->Update();
  bRatioBottomPad->cd();
  TH1* ratio = 0;

  ratio = (TH1F*) ((TH1F*) hist1)->Clone("myclone");
  TH1F * looseHistoForRatio = (TH1F *) hist2;
  ratio->SetMarkerSize(1);
  if (ratio->GetSumw2N() == 0)
    ratio->Sumw2();
  //VS!!!	ratio->Divide(ratio, looseHistoForRatio, 1, 1, "B");
  ratio->Divide(ratio, looseHistoForRatio, 1, 1);
  ratio->GetYaxis()->SetRangeUser(0.8, 1.2);
  ratio->GetYaxis()->SetTitle("Ratio");
  
  ratio->GetXaxis()->SetTitle(xaxistitle.c_str());
  ratio->GetXaxis()->SetTitleSize(0.05);
  ratio->GetXaxis()->SetLabelSize(0.05);
  ratio->GetXaxis()->SetTitleOffset(1.25);
  ratio->Draw("p0e1x0,same");
  canv->Update();
  gPad->Update();
  bRatioBottomPad->cd();
  TLine * line = new TLine(75, 1, hist1->GetXaxis()->GetXmax(), 1);
  line->SetLineColor(1);
  line->SetLineWidth(1);
  line->Draw("same");
  canv->RedrawAxis();
  canv->Update();
  gPad->Update();
  //cmsPrel(normToLumi, 1, isData, isMC);
  drawCmsPrel(normToLumi, "", false, noJets, false);
  gPad->Update();
  canv->Update();

  TH1F * relErrors = (TH1F *) hist1->Clone();
  if (relErrors->GetSumw2N() == 0)
    relErrors->Sumw2();
  relErrors->SetDirectory(0);
  relErrors->Add((TH1F *) hist2->Clone(), -1);
  relErrors->Divide(relErrors, (TH1F *) hist1->Clone(), 1, 1, "B");
  //relErrors->Draw("same");
  TLegend *legend = new TLegend(0.59, 0.71, 0.84, 0.87, "");
  legend->SetTextSize(0.04);
  legend->SetFillColor(10);
  legend->SetFillStyle(1001);
  legend->AddEntry(hist1, leg1.c_str(), "lp");
  legend->AddEntry(hist2, leg2.c_str(), "lp");
  legend->Draw("same");
  string outputdir = resultDir + "/" + resultFolderName + "/" + canvasname;
  cout << "save:" << outputdir << endl;
  canv->SaveAs((outputdir + "" + ".pdf").c_str());
  canv->Print((outputdir + "" + ".eps").c_str());
  output->WriteTObject(canv, 0, "overwrite");

  //Draw rel fit res error in own Canvas
  if (relErrors != 0) {
    string canvasnameRelErr = canvasname + "RelErr";
    TCanvas * canvRelErr = new TCanvas(canvasnameRelErr.c_str(), canvasnameRelErr.c_str());
    relErrors->GetYaxis()->SetTitle("rel. Error ");
    relErrors->GetYaxis()->SetRangeUser(-0.2, 0.2);
    setErrorsToZero(relErrors);
    if (isMC) {
      relErrors->SetMarkerSize(1);
      relErrors->Draw("EX0P");
    } else {
      relErrors->SetMarkerSize(1);
      relErrors->Draw("EX0P");
    }
    //cmsPrel(normToLumi, 1, isData, isMC);
    drawCmsPrel(normToLumi, "", false, noJets, false);
    canvRelErr->Update();
    canvRelErr->SaveAs((outputdir + "_RATRelErr" + ".pdf").c_str());
    canvRelErr->Print((outputdir + "_RATRelErr" + ".eps").c_str());
    output->WriteTObject(canvRelErr, 0, "overwrite");
  }
}


//
void compareHistosSusyPhotonJetAnalysisFakeBetweenDatasamplesNoJet(TFile * input1, TFile * input2, string resultFolderName, string resultDir, string leg1, string leg2, bool isData, bool isMC, double normToLumi, int noJets) {
	system(("mkdir " + resultDir).c_str());
	system(("mkdir " + resultDir + "/" + resultFolderName).c_str());
	setMyTDRStyle();
	gROOT->SetStyle("mytdrStyle");

	gStyle->SetHistLineWidth(2);
	gStyle->UseCurrentStyle();
	gROOT->ForceStyle(1);

	TFile * output = new TFile((resultDir + "/" + resultFolderName + "_plot.root").c_str(), "Recreate");

	string canvasname = "c_PreselCut_noJets_RAT";
	string histoname = "blabla1clone2";

	TCanvas * canv1 = (TCanvas *) input1->FindObjectAny(canvasname.c_str());
	cout << "canv1:" << canv1 << endl;
	TH1F * hist1 = (TH1F *) canv1->FindObject(histoname.c_str());
	cout << "hist1:" << hist1 << endl;

	hist1->Scale(1 / hist1->Integral());
	hist1->SetDirectory(0);
	hist1->GetXaxis()->SetRangeUser(0, 10);
	TCanvas * canv2 = (TCanvas *) input2->FindObjectAny(canvasname.c_str());
	cout << "canv2:" << canv2 << " from input:" << input2->GetName() << endl;
	TH1F * hist2 = (TH1F *) canv2->FindObject(histoname.c_str());
	cout << "hist2:" << hist2 << endl;
	hist2->SetDirectory(0);
	hist2->GetXaxis()->SetRangeUser(0, 10);
	hist2->Scale(1 / hist2->Integral());
	double maxYValue = hist1->GetBinContent(hist1->GetMaximumBin());
	if (hist2->GetBinContent(hist2->GetMaximumBin()) > maxYValue)
		maxYValue = hist2->GetBinContent(hist2->GetMaximumBin());
	hist1->GetYaxis()->SetRangeUser(0.1, maxYValue * 3);

	TCanvas * canv = new TCanvas(canvasname.c_str(), canvasname.c_str());
	;
	gPad->Update();
	canv->Update();
	hist1->SetMarkerStyle(20);

	hist2->SetLineColor(2);
	hist2->SetMarkerColor(2);
	hist2->SetMarkerStyle(25);
	hist2->SetLineColor(2);
	hist2->SetMarkerColor(2);
	hist2->SetMarkerStyle(25);
	string xaxistitle = hist1->GetXaxis()->GetTitle();
	hist1->GetXaxis()->SetTitle("");
	hist2->GetXaxis()->SetTitle("");
	hist1->GetXaxis()->SetNdivisions(505);
	hist2->GetXaxis()->SetNdivisions(505);
	hist1->GetXaxis()->SetLabelSize(0);
	hist2->GetXaxis()->SetLabelSize(0);
	hist2->GetXaxis()->SetNdivisions(505);
	if (isMC) {
		//		hist1->SetMarkerSize(0);
		//		hist2->SetMarkerSize(0);
		//		hist2->SetLineWidth(3);
		//		hist2->SetLineStyle(2);
		hist1->DrawClone("EX0P");
		hist2->DrawClone("EX0Psame");
	} else {

		hist1->DrawClone("EX0P");
		hist2->DrawClone("sameEX0P");
	}
	canv->SetBottomMargin(0.2 + 0.8 * canv->GetBottomMargin() - 0.2 * canv->GetTopMargin());
	TPad *bRatioBottomPad = createRatioBottomPad();
	bRatioBottomPad->Draw();
	bRatioBottomPad->cd();
	TH1 * ax = (TH1*) ((TH1F*) hist1)->Clone("mycloneax");
	ax->SetMinimum(0.9);
	ax->SetMaximum(1.1);
	ax->GetYaxis()->SetNdivisions(505);
	ax->GetXaxis()->SetNdivisions(505);

	ax->GetYaxis()->SetLabelSize(0.03);
	ax->GetYaxis()->SetTitle("Ratio");
	ax->GetYaxis()->SetTitleSize(0.05);
	ax->GetYaxis()->SetTitleOffset(0.05);
	ax->GetXaxis()->SetTitleSize(0.05);
	ax->GetYaxis()->SetTitleOffset(1.3);
	ax->GetXaxis()->SetLabelSize(0.05);
	ax->GetXaxis()->SetTicks("+");
	ax->GetXaxis()->SetTitle(xaxistitle.c_str());

	ax->Draw("axis");
	canv->Update();
	gPad->Update();
	bRatioBottomPad->cd();
	TH1* ratio = 0;

	ratio = (TH1F*) ((TH1F*) hist1)->Clone("myclone");
	TH1F * looseHistoForRatio = (TH1F *) hist2;
	ratio->SetMarkerSize(1);
	if (ratio->GetSumw2N() == 0)
		ratio->Sumw2();
	ratio->Divide(ratio, looseHistoForRatio, 1, 1, "B");
	ratio->GetYaxis()->SetRangeUser(0.8, 1.2);
	ratio->GetYaxis()->SetTitle("Ratio");

	ratio->GetXaxis()->SetTitle(xaxistitle.c_str());
	ratio->GetXaxis()->SetTitleSize(0.05);
	ratio->GetXaxis()->SetLabelSize(0.05);
	ratio->GetXaxis()->SetTitleOffset(1.25);
	ratio->Draw("p0e1x0,same");
	canv->Update();
	gPad->Update();
	bRatioBottomPad->cd();
	TLine * line = new TLine(75, 1, hist1->GetXaxis()->GetXmax(), 1);
	line->SetLineColor(1);
	line->SetLineWidth(1);
	line->Draw("same");
	canv->RedrawAxis();
	canv->Update();
	gPad->Update();
	//cmsPrel(normToLumi, 1, isData, isMC);
	drawCmsPrel(normToLumi, "", false, noJets, false);
	gPad->Update();
	canv->Update();

	TH1F * relErrors = (TH1F *) hist1->Clone();
	if (relErrors->GetSumw2N() == 0)
		relErrors->Sumw2();
	relErrors->SetDirectory(0);
	relErrors->Add((TH1F *) hist2->Clone(), -1);
	relErrors->Divide(relErrors, (TH1F *) hist1->Clone(), 1, 1, "B");
	//relErrors->Draw("same");
	TLegend *legend = new TLegend(0.59, 0.71, 0.84, 0.87, "");
	legend->SetTextSize(0.04);
	legend->SetFillColor(10);
	legend->SetFillStyle(1001);
	legend->AddEntry(hist1, leg1.c_str(), "lp");
	legend->AddEntry(hist2, leg2.c_str(), "lp");
	legend->Draw("same");
	string outputdir = resultDir + "/" + resultFolderName + "/" + canvasname;
	cout << "save:" << outputdir << endl;
	canv->SaveAs((outputdir + "" + ".pdf").c_str());
	canv->Print((outputdir + "" + ".eps").c_str());
	output->WriteTObject(canv, 0, "overwrite");

	//Draw rel fit res error in own Canvas
	if (relErrors != 0) {
		string canvasnameRelErr = canvasname + "RelErr";
		TCanvas * canvRelErr = new TCanvas(canvasnameRelErr.c_str(), canvasnameRelErr.c_str());
		relErrors->GetYaxis()->SetTitle("rel. Error ");
		relErrors->GetYaxis()->SetRangeUser(-0.2, 0.2);
		setErrorsToZero(relErrors);
		if (isMC) {
			relErrors->SetMarkerSize(1);
			relErrors->Draw("EX0P");
		} else {
			relErrors->SetMarkerSize(1);
			relErrors->Draw("EX0P");
		}
		//cmsPrel(normToLumi, 1, isData, isMC);
		drawCmsPrel(normToLumi, "", false, noJets, false);
		canvRelErr->Update();
		canvRelErr->SaveAs((outputdir + "_RATRelErr" + ".pdf").c_str());
		canvRelErr->Print((outputdir + "_RATRelErr" + ".eps").c_str());
		output->WriteTObject(canvRelErr, 0, "overwrite");
	}

}


//
void compareHistosSusyPhotonJetAnalysisFakeBetweenNoPV(TFile * input1, string resultFolderName, string resultDir, string leg1, string leg2, bool isData, bool isMC, double normToLumi, int noJets) {

	string canvasname1 = "c_PreselCut_photonPt_RAT";

	vector < string > canvNames;

	string canvasname1a = "c_DivideXPreselCut_noPVVsPhotonPt_Bin_From_1_CompTightLoose_RAT";
	string canvasname1b = "c_DivideXPreselCut_noPVVsPhotonPt_Bin_From_3_CompTightLoose_RAT";
	string canvasname2  = "c_DivideXPreselCut_noPVVsPhotonPt_Bin_From_6_CompTightLoose_RAT";
	string canvasname3  = "c_DivideXPreselCut_noPVVsPhotonPt_Bin_From_9_CompTightLoose_RAT";
	string canvasname4  = "c_DivideXPreselCut_noPVVsPhotonPt_Bin_From_11_CompTightLoose_RAT";
	canvNames.push_back(canvasname1a);
	canvNames.push_back(canvasname1b);
	canvNames.push_back(canvasname2);
	canvNames.push_back(canvasname3);
	canvNames.push_back(canvasname4);

	string histoname = "blabla1clone2";
	TList * relErrorList = new TList();

	TCanvas * canv1 = (TCanvas *) input1->FindObjectAny(canvasname1.c_str());
	TH1F * hist1    = (TH1F *) canv1->FindObject(histoname.c_str());

	if (hist1 != 0) {
		hist1->SetDirectory(0);
		hist1->GetXaxis()->SetRangeUser(75, 1005);
		hist1->GetYaxis()->SetRangeUser(0, 3);
		hist1->SetMarkerStyle(20);
		hist1->SetLineColor(1);

		string newcanvasname = "c_PileUpDependencyFit";
		TCanvas * canv = new TCanvas(newcanvasname.c_str(), newcanvasname.c_str());
		;
		TLegend *legend = new TLegend(0.3, 0.71, 0.84, 0.87, "");
		legend->SetTextSize(0.04);
		legend->SetFillColor(10);
		legend->SetFillStyle(1001);
		gPad->Update();
		canv->Update();
		if (isMC) {

			hist1->DrawClone("EX0P");
		} else {

			hist1->DrawClone("EX0P");
		}
		legend->AddEntry(hist1, leg1.c_str(), "lp");

		for (int ca = 0; ca < canvNames.size(); ca++) {

			string canvName = canvNames.at(ca);
			TCanvas * canv2 = (TCanvas *) input1->FindObjectAny(canvName.c_str());

			//cout << "canv2:" << canv2 << endl;
			TH1F * hist2 = (TH1F *) canv2->FindObject(histoname.c_str());

			//cout << "fit2:" << fit2 << endl;
			if (hist2 != 0) {
				hist2->SetDirectory(0);

				hist2->GetXaxis()->SetRangeUser(75, 1005);
				hist2->GetYaxis()->SetRangeUser(0, 3);

				hist2->SetLineColor(ca + 2);
				hist2->SetMarkerColor(ca + 2);
				hist2->SetMarkerStyle(25 + ca);
				canv->Update();
				if (isMC) {

					hist2->DrawClone("EX0Psame");
				} else {

					hist2->DrawClone("sameEX0P");
				}
				if (ca == 0)
					leg2 = "=1 PV";
				if (ca == 1)
					leg2 = "=3 PV";
				if (ca == 2)
					leg2 = "=6 PV";
				if (ca == 3)
					leg2 = "=9 PV";
				if (ca == 4)
					leg2 = "=11 PV";
				legend->AddEntry(hist2, leg2.c_str(), "lp");
				//delete canv2;
				//add rell error histo to list
				TH1F * relErrors = (TH1F *) hist1->Clone("bla");
				std::vector<double> binEdges;

				for (int i = 1; i <= hist2->GetNbinsX() + 1; i++) {

					binEdges.push_back(hist2->GetBinLowEdge(i));

				}
				//cout << "binEdges:" << binEdges.size()<< endl;
				relErrors = (TH1F*) relErrors->Rebin(binEdges.size() - 1, relErrors->GetName(), &(binEdges.front()));
				//cout << "bins nach rebin:" << relErrors->GetNbinsX()<< endl;
				if (relErrors->GetSumw2N() == 0)
					relErrors->Sumw2();
				relErrors->SetDirectory(0);
				relErrors->GetXaxis()->SetRangeUser(75, 1005);

				relErrors->Add((TH1F *) hist2->Clone("blabla"), -1);
				TH1F * h1cloneForDiv = (TH1F*) relErrors->Clone();
				h1cloneForDiv->GetXaxis()->SetRangeUser(75, 1005);
				relErrors->Divide(relErrors, h1cloneForDiv, 1, 1, "B");
				relErrors->SetDirectory(0);
				relErrorList->Add(relErrors);
				relErrors->SetLineColor(hist2->GetLineColor());
				relErrors->SetMarkerColor(hist2->GetMarkerColor());
				relErrors->SetMarkerStyle(hist2->GetMarkerStyle());
			}
			//cout << "end of loop:" << endl;
		}
		//cout << "loop done:" << endl;
		legend->Draw("same");
		gPad->Update();
		canv->Update();

		//cout << "save:" << endl;
		string outputdir = resultDir + "/" + resultFolderName + "/" + newcanvasname;
		//cout << "save:" << outputdir << endl;
		canv->SaveAs((outputdir + "" + ".pdf").c_str());
		canv->Print((outputdir + "" + ".eps").c_str());
		input1->WriteTObject(canv, 0, "overwrite");
		delete canv;
		//Draw rel fit res error in own Canvas
		if (relErrorList->GetSize() != 0) {
			string canvasnameRelErr = newcanvasname + "RelErr";
			TCanvas * canvRelErr = new TCanvas(canvasnameRelErr.c_str(), canvasnameRelErr.c_str());
			//cmsPrel(normToLumi, 1, isData, isMC);
			drawCmsPrel(normToLumi, "", false, noJets, false);
			TIter key(relErrorList);
			int count = 0;
			while (TKey* keyHisto = (TKey*) key()) {
				TH1F * relErrors = (TH1F *) keyHisto;
				relErrors->SetDirectory(0);
				relErrors->GetYaxis()->SetTitle("rel. Error ");
				relErrors->GetYaxis()->SetRangeUser(-1, 1);
				if (count == 0) {
					if (isMC) {
						relErrors->SetMarkerSize(1);
						relErrors->Draw("EX0P 0");
					} else {
						relErrors->SetMarkerSize(1);
						relErrors->Draw("EX0P 0");
					}
				} else {
					if (isMC) {
						relErrors->SetMarkerSize(1);
						relErrors->Draw("EX0Psame 0");
					} else {
						relErrors->SetMarkerSize(1);
						relErrors->Draw("EX0Psame 0");
					}
				}

				//setErrorsToZero(relErrors);

				canvRelErr->Update();

				gPad->Update();
				canvRelErr->Update();
				count++;
			}

			canvRelErr->SaveAs((outputdir + "_RATRelErr" + ".pdf").c_str());
			canvRelErr->Print((outputdir + "_RATRelErr" + ".eps").c_str());
			input1->WriteTObject(canvRelErr, 0, "overwrite");
			delete canvRelErr;
		}

	} else {
		cout << "ERROR - histo not found:" << histoname << endl;
	}

}


//
void compareHistosSusyPhotonJetAnalysisFakeBetweenNoJets(TFile * input1, string resultFolderName, string resultDir, string leg1, string leg2, bool isData, bool isMC, double normToLumi, int noJets, bool norm) {

  string canvasname1 = "c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RAT";

  vector < string > canvNames;

  string canvasname2 = "c_DivideXPreselCut_noJetsVsPhotonPt_Bin_From_2_CompTightLoose_RAT";
  string canvasname3 = "c_DivideXPreselCut_noJetsVsPhotonPt_Bin_From_3_CompTightLoose_RAT";
  string canvasname4 = "c_DivideXPreselCut_noJetsVsPhotonPt_Bin_From_4_CompTightLoose_RAT";
  string canvasname5 = "c_DivideXPreselCut_noJetsVsPhotonPt_Bin_From_5_CompTightLoose_RAT";
  string canvasname6 = "c_DivideXPreselCut_noJetsVsPhotonPt_Bin_From_6_CompTightLoose_RAT";

  canvNames.push_back(canvasname2);
  canvNames.push_back(canvasname3);
  canvNames.push_back(canvasname4);
  canvNames.push_back(canvasname5);
  canvNames.push_back(canvasname6);

  string histoname = "blabla1clone2";
  TList * relErrorList = new TList();

  TCanvas * canv1 = (TCanvas *) input1->FindObjectAny(canvasname1.c_str());
  cout << "canv1:" << canv1 << endl;
  TH1F * hist1 = (TH1F *) canv1->FindObject(histoname.c_str());
  cout << "hist1:" << hist1 << endl;

  if (hist1 != 0) {
    hist1->SetDirectory(0);
    hist1->GetXaxis()->SetRangeUser(75, 1005);
    hist1->GetYaxis()->SetRangeUser(0, 3);
    hist1->GetYaxis()->SetNdivisions(505);
    hist1->SetMarkerStyle(20);
    hist1->SetLineColor(1);

    string newcanvasname = "c_NoOfJetDependencyFit";
    if (norm) 
      newcanvasname = newcanvasname + "_NORM";
    
    TCanvas * canv = new TCanvas(newcanvasname.c_str(), newcanvasname.c_str());
		
    TLegend *legend = new TLegend(0.67, 0.69, 0.94, 0.89, "");
    legend->SetTextSize(0.04);
    legend->SetFillColor(10);
    legend->SetFillStyle(1001);
    gPad->Update();
    canv->Update();
    string yaxistitle = (hist1->GetYaxis()->GetTitle());

    if (norm) {
      yaxistitle = "Norm. " + yaxistitle;
      hist1->Scale(1 / hist1->Integral());
      hist1->GetYaxis()->SetRangeUser(0, 0.2);
      hist1->GetYaxis()->SetTitle(yaxistitle.c_str());
      hist1->GetYaxis()->SetTitleOffset(1.1*hist1->GetYaxis()->GetTitleOffset());
    }
    if (isMC) {      
      hist1->DrawClone("EX0P");
    } else {
      hist1->DrawClone("EX0P");
    }

    legend->AddEntry(hist1, leg1.c_str(), "lp");

    for (int ca = 0; ca < canvNames.size(); ca++) {

      string canvName = canvNames.at(ca);
      TCanvas * canv2 = (TCanvas *) input1->FindObjectAny(canvName.c_str());

      cout << "canv2:" << canv2 << endl;
      if (canv2 != 0) {
	TH1F * hist2 = (TH1F *) canv2->FindObject(histoname.c_str());
	
	if (hist2 != 0) {
	  if (norm) {
	    hist2->Scale(1 / hist2->Integral());
	    hist2->GetYaxis()->SetTitle(yaxistitle.c_str());
	  }
	  hist2->SetDirectory(0);
	  hist2->GetYaxis()->SetNdivisions(505);
	  hist2->GetYaxis()->SetTitleOffset(1.1*hist2->GetYaxis()->GetTitleOffset());

	  hist2->GetXaxis()->SetRangeUser(75, 1005);
	  hist2->GetYaxis()->SetRangeUser(0, 3);

	  hist2->SetLineColor(ca + 2);
	  hist2->SetMarkerColor(ca + 2);
	  hist2->SetMarkerStyle(25 + ca);
	  if (ca + 2 >= 5) {
	    hist2->SetLineColor(kOrange);
	    hist2->SetMarkerColor(kOrange);
	  }

	  canv->Update();
	  if (isMC) {	    
	    hist2->DrawClone("EX0Psame");
	  } else {
	    hist2->DrawClone("sameEX0P");
	  }

	  if (ca == 0)
	    leg2 = "2 jets";
	  if (ca == 1)
	    leg2 = "3 jets";
	  if (ca == 2)
	    leg2 = "4 jets";
	  if (ca == 3)
	    leg2 = "5 jets";
	  if (ca == 4)
	    leg2 = "6 jets";
	  if (ca == canvNames.size() - 2) {
	    leg2 = ">=" + leg2;	    
	  } else {
	    leg2 = "=" + leg2;
	  }
	  legend->AddEntry(hist2, leg2.c_str(), "lp");

	  //delete canv2;
	  //add rell error histo to list
	  TH1F * relErrors = (TH1F *) hist1->Clone("bla");
	  std::vector<double> binEdges;
	  
	  for (int i = 1; i <= hist2->GetNbinsX() + 1; i++) {	    
	    binEdges.push_back(hist2->GetBinLowEdge(i));
	  }

	  cout << "binEdges:" << binEdges.size() << endl;
	  relErrors = (TH1F*) relErrors->Rebin(binEdges.size() - 1, relErrors->GetName(), &(binEdges.front()));
	  cout << "bins nach rebin:" << relErrors->GetNbinsX() << endl;
	  if (relErrors->GetSumw2N() == 0)
	    relErrors->Sumw2();
	  relErrors->SetDirectory(0);
	  relErrors->GetXaxis()->SetRangeUser(75, 1005);
	  TH1F * h1cloneForDiv = (TH1F*) hist2->Clone("blub");
	  cout << "hist2 entries:" << hist2->GetBinContent(hist2->GetMaximumBin()) << endl;
	  if (hist2->GetBinContent(hist2->GetMaximumBin()) > 0) {
	    h1cloneForDiv->GetXaxis()->SetRangeUser(75, 1005);

	    h1cloneForDiv->Add((TH1F *) relErrors->Clone("blabla"), -1);
	    relErrors->Divide(h1cloneForDiv, relErrors, 1, 1, "B");
	    relErrors->SetDirectory(0);
	    relErrors->SetTitle(("" + leg2).c_str());
	    relErrorList->Add(relErrors);
	    relErrors->SetLineColor(hist2->GetLineColor());
	    relErrors->SetMarkerColor(hist2->GetMarkerColor());
	    relErrors->SetMarkerStyle(hist2->GetMarkerStyle());
	  }
	}
      } // if canv2 != 0
    } // for canvNames

    legend->Draw("same");
    gPad->Update();
    canv->Update();

    string outputdir = resultDir + "/" + resultFolderName + "/" + newcanvasname;
    canv->SaveAs((outputdir + "" + ".pdf").c_str());
    canv->SaveAs((outputdir + "" + ".eps").c_str());
    input1->WriteTObject(canv, 0, "overwrite");
    delete canv;

    //Draw rel fit res error in own Canvas
    if (relErrorList->GetSize() != 0) {
      string canvasnameRelErr = newcanvasname + "RelErr";
      TCanvas * canvRelErr = new TCanvas(canvasnameRelErr.c_str(), canvasnameRelErr.c_str());
      TLegend *legend = new TLegend(0.67, 0.69, 0.94, 0.89, "");
      legend->SetTextSize(0.04);
      legend->SetFillColor(10);
      legend->SetFillStyle(1001);
      //cmsPrel(normToLumi, 1, isData, isMC);
      drawCmsPrel(normToLumi, "", false, noJets, false);
      TIter key(relErrorList);
      int count = 0;

      while (TKey* keyHisto = (TKey*) key()) {
	TH1F * relErrors = (TH1F *) keyHisto;
	relErrors->SetDirectory(0);
	relErrors->GetYaxis()->SetTitle("rel. Error ");
	relErrors->GetYaxis()->SetRangeUser(-0.5, 0.5);
	if (count == 0) {
	  if (isMC) {
	    relErrors->SetMarkerSize(1);
	    relErrors->Draw("");
	  } else {
	    relErrors->SetMarkerSize(1);
	    relErrors->Draw("");
	  }
	} else {
	  if (isMC) {
	    relErrors->SetMarkerSize(1);
	    relErrors->Draw("same");
	  } else {
	    relErrors->SetMarkerSize(1);
	    relErrors->Draw("same");
	  }
	}
	
	legend->AddEntry(relErrors);
	//setErrorsToZero(relErrors);
	
	canvRelErr->Update();

	gPad->Update();
	canvRelErr->Update();
	count++;
      }
      legend->Draw("same");
      canvRelErr->SaveAs((outputdir + "_RATRelErr" + ".pdf").c_str());
      canvRelErr->Print((outputdir + "_RATRelErr" + ".eps").c_str());
      input1->WriteTObject(canvRelErr, 0, "overwrite");
      delete canvRelErr;
    }

  } else {
    cout << "ERROR - histo not found:" << histoname << endl;
  }

  return;
}


//
void compareHistosSusyPhotonJetAnalysisFakeBetweenLowMetAndWholeSpectrum(TFile * input1, string resultFolderName, string resultDir, string leg1, string leg2, bool isData, bool isMC, double normToLumi, int noJets, string addLabelInHisto) {

  string canvasname = "c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RAT";
  string canvasnameWholeSpect = "c_PreselCut_photonPt_RAT";

  string histoname = "blabla1clone2";

  TCanvas * canv1 = (TCanvas *) input1->FindObjectAny(canvasname.c_str());
  TH1F * hist1 = (TH1F *) canv1->FindObject(histoname.c_str());

  if (hist1 != 0) {
    hist1->SetDirectory(0);
    hist1->GetXaxis()->SetRangeUser(75, 1500);
    TCanvas * canv2 = (TCanvas *) input1->FindObjectAny(canvasnameWholeSpect.c_str());

    TH1F * hist2 = (TH1F *) canv2->FindObject(histoname.c_str());
    hist2->SetDirectory(0);
    hist2->GetXaxis()->SetRangeUser(75, 1500);

    double maxYValue = hist1->GetBinContent(hist1->GetMaximumBin());
    if (hist2->GetBinContent(hist2->GetMaximumBin()) > maxYValue)
      maxYValue = hist2->GetBinContent(hist2->GetMaximumBin());
    hist1->GetYaxis()->SetRangeUser(0.01, maxYValue * 1.2);

    string newcanvasname = "c_ExtrapolationOfFitToWholeSpectrum";
    TCanvas * canv = new TCanvas(newcanvasname.c_str(), newcanvasname.c_str());
		
    gPad->Update();
    canv->Update();
    hist1->SetMarkerStyle(20);

    hist2->SetLineColor(2);
    hist2->SetMarkerColor(2);
    hist2->SetMarkerStyle(25);
    string xaxistitle = hist1->GetXaxis()->GetTitle();
    hist1->GetXaxis()->SetTitle("");
    hist2->GetXaxis()->SetTitle("");
    hist1->GetXaxis()->SetNdivisions(505);
    hist2->GetXaxis()->SetNdivisions(505);
    hist1->GetXaxis()->SetLabelSize(0);
    hist2->GetXaxis()->SetLabelSize(0);
    hist2->GetYaxis()->SetNdivisions(505);
    hist1->GetYaxis()->SetNdivisions(505);

    hist1->DrawClone("EX0P");
    hist2->DrawClone("EX0Psame");

    canv->SetBottomMargin(0.2 + 0.8 * canv->GetBottomMargin() - 0.2 * canv->GetTopMargin());
    TPad *bRatioBottomPad = createRatioBottomPad();
    bRatioBottomPad->Draw();
    bRatioBottomPad->cd();

    TH1 * ax = (TH1*) ((TH1F*) hist1)->Clone("mycloneax");
    ax->SetMinimum(0.9);
    ax->SetMaximum(1.1);
    ax->GetYaxis()->SetNdivisions(505);
    ax->GetXaxis()->SetNdivisions(505);

    ax->GetYaxis()->SetLabelSize(0.03);
    ax->GetYaxis()->SetTitle("Ratio");
    ax->GetYaxis()->SetTitleSize(0.05);
    ax->GetYaxis()->SetTitleOffset(0.05);
    ax->GetXaxis()->SetTitleSize(0.05);
    ax->GetYaxis()->SetTitleOffset(1.3);
    ax->GetXaxis()->SetLabelSize(0.05);
    ax->GetXaxis()->SetTicks("+");
    ax->GetXaxis()->SetTitle(xaxistitle.c_str());

    ax->Draw("axis");
    canv->Update();
    gPad->Update();
    bRatioBottomPad->cd();
    TH1* ratio = 0;

    ratio = (TH1F*) ((TH1F*) hist1)->Clone("myclone");
    TH1F * looseHistoForRatio = (TH1F *) hist2;
    ratio->SetMarkerSize(1);
    if (ratio->GetSumw2N() == 0)
      ratio->Sumw2();

    ratio->Divide(ratio, looseHistoForRatio, 1, 1, "B");

    ratio->GetYaxis()->SetRangeUser(0.8, 1.2);
    ratio->GetYaxis()->SetTitle("Ratio");

    ratio->GetXaxis()->SetTitle(xaxistitle.c_str());
    ratio->GetXaxis()->SetTitleSize(0.05);
    ratio->GetXaxis()->SetLabelSize(0.05);
    ratio->GetXaxis()->SetTitleOffset(1.25);

    ratio->Draw("p0e1x0,same");

    canv->Update();
    gPad->Update();

    bRatioBottomPad->cd();
    TLine * line = new TLine(75, 1, ax->GetXaxis()->GetXmax(), 1);
    line->SetLineColor(1);
    line->SetLineWidth(1);
    line->Draw("same");
    canv->RedrawAxis();
    canv->Update();
    gPad->Update();

    gPad->Update();
    canv->Update();

    TH1F * relErrors = (TH1F *) hist1->Clone("bla");
    if (relErrors->GetSumw2N() == 0)
      relErrors->Sumw2();

    relErrors->SetDirectory(0);
    relErrors->Add((TH1F *) hist2->Clone("blabla"), -1);
    relErrors->Divide(relErrors, (TH1F *) hist1->Clone(), 1, 1, "B");
    relErrors->SetDirectory(0);
    //relErrors->Draw("same");

    gPad->Update();
    canv->Update();

    TLegend *legend = new TLegend(0.35, 0.65, 0.8, 0.85);
    legend->SetTextSize(0.04);
    legend->SetFillColor(10);
    legend->SetFillStyle(1001);
    legend->SetHeader(addLabelInHisto.c_str());
    legend->AddEntry(hist1, leg1.c_str(), "lp");
    legend->AddEntry(hist2, leg2.c_str(), "lp");
    legend->Draw("same");

    drawCmsPrel(normToLumi, "", false, noJets, false);

    string outputdir = resultDir + "/" + resultFolderName + "/" + newcanvasname;
    canv->SaveAs((outputdir + "" + ".pdf").c_str());
    canv->SaveAs((outputdir + "" + ".eps").c_str());

    input1->WriteTObject(canv, 0, "overwrite");

    delete canv;
	
    // Draw rel fit res error in own Canvas
    if (relErrors != 0) {
      string canvasnameRelErr = newcanvasname + "RelErr";
      TCanvas * canvRelErr = new TCanvas(canvasnameRelErr.c_str(), canvasnameRelErr.c_str());
      //cmsPrel(normToLumi, 1, isData, isMC);

      relErrors->GetYaxis()->SetTitle("rel. Error ");
      relErrors->GetYaxis()->SetRangeUser(-0.1, 0.1);
      setErrorsToZero(relErrors);
      if (isMC) {
	relErrors->SetMarkerSize(1);
	relErrors->Draw("EX0P");
      } else {
	relErrors->SetMarkerSize(1);
	relErrors->Draw("EX0P");
      }

      TLegend *legendrel = new TLegend(0.50, 0.71, 0.80, 0.87, "");
      legendrel->SetTextSize(0.04);
      legendrel->SetFillColor(10);
      legendrel->SetFillStyle(1001);
      string datasetname = "";
      legendrel->SetHeader(addLabelInHisto.c_str());
      legendrel->Draw("same");
      canvRelErr->Update();
      drawCmsPrel(normToLumi, "", false, noJets, false);
      canvRelErr->SaveAs((outputdir + "_RATRelErr" + ".pdf").c_str());
      canvRelErr->Print((outputdir + "_RATRelErr" + ".eps").c_str());
      input1->WriteTObject(canvRelErr, 0, "overwrite");
      delete canvRelErr;
    }

  } else {
    cout << "ERROR - histo not found:" << histoname << endl;
  }

  return;
}


//
void compareHistosSusyPhotonJetAnalysisFakeBetweenLowMetAndWholeSpectrumDiJet(TFile * input1, string resultFolderName, string resultDir, string leg1, string leg2, bool isData, bool isMC, double normToLumi, int noJets, string addLabelInHisto) {

	string canvasname = "c_DivideXPreselCut_noJetsVsPhotonPtLowMet_Bin_From_2_CompTightLoose_RAT";
	string canvasnameWholeSpect = "c_DivideXPreselCut_noJetsVsPhotonPt_Bin_From_2_CompTightLoose_RAT";

	string histoname = "blabla1clone2";
	
	TCanvas * canv1 = (TCanvas *) input1->FindObjectAny(canvasname.c_str());
	//cout << "canv1:" << canv1 << endl;
	TH1F * hist1 = (TH1F *) canv1->FindObject(histoname.c_str());
	//cout << "hist1:" << hist1 << endl;
	if (hist1 != 0) {
		hist1->SetDirectory(0);
		hist1->GetXaxis()->SetRangeUser(75, 1500);

		TCanvas * canv2 = (TCanvas *) input1->FindObjectAny(canvasnameWholeSpect.c_str());
		//cout << "canv2:" << canv2 << endl;
		TH1F * hist2 = (TH1F *) canv2->FindObject(histoname.c_str());
		//cout << "hist2:" << hist2 << endl;
		hist2->SetDirectory(0);
		hist2->GetXaxis()->SetRangeUser(75, 1500);

		double maxYValue = hist1->GetBinContent(hist1->GetMaximumBin());
		if (hist2->GetBinContent(hist2->GetMaximumBin()) > maxYValue)
			maxYValue = hist2->GetBinContent(hist2->GetMaximumBin());
		hist1->GetYaxis()->SetRangeUser(0.05, maxYValue * 1.2);
		string newcanvasname = "c_ExtrapolationOfFitToWholeSpectrumDijet";
		TCanvas * canv = new TCanvas(newcanvasname.c_str(), newcanvasname.c_str());
		;
		gPad->Update();
		canv->Update();
		hist1->SetMarkerStyle(20);

		hist2->SetLineColor(2);
		hist2->SetMarkerColor(2);
		hist2->SetMarkerStyle(25);
		string xaxistitle = hist1->GetXaxis()->GetTitle();
		hist1->GetXaxis()->SetTitle("");
		hist2->GetXaxis()->SetTitle("");
		hist1->GetXaxis()->SetNdivisions(505);
		hist2->GetXaxis()->SetNdivisions(505);
		hist1->GetXaxis()->SetLabelSize(0);
		hist2->GetXaxis()->SetLabelSize(0);
		hist2->GetYaxis()->SetNdivisions(505);
		hist1->GetYaxis()->SetNdivisions(505);
		if (isMC) {
			//			hist1->SetMarkerSize(0);
			//			hist2->SetMarkerSize(0);
			//			hist2->SetLineWidth(3);
			//			hist2->SetLineStyle(2);
			hist1->DrawClone("EX0P");
			hist2->DrawClone("EX0Psame");
		} else {

			hist1->DrawClone("EX0P");
			hist2->DrawClone("sameEX0P");
		}
		canv->SetBottomMargin(0.2 + 0.8 * canv->GetBottomMargin() - 0.2 * canv->GetTopMargin());
		TPad *bRatioBottomPad = createRatioBottomPad();
		bRatioBottomPad->Draw();
		bRatioBottomPad->cd();
		TH1 * ax = (TH1*) ((TH1F*) hist1)->Clone("mycloneax");
		ax->SetMinimum(0.9);
		ax->SetMaximum(1.1);
		ax->GetYaxis()->SetNdivisions(505);
		ax->GetXaxis()->SetNdivisions(505);

		ax->GetYaxis()->SetLabelSize(0.03);
		ax->GetYaxis()->SetTitle("Ratio");
		ax->GetYaxis()->SetTitleSize(0.05);
		ax->GetYaxis()->SetTitleOffset(0.05);
		ax->GetXaxis()->SetTitleSize(0.05);
		ax->GetYaxis()->SetTitleOffset(1.3);
		ax->GetXaxis()->SetLabelSize(0.05);
		ax->GetXaxis()->SetTicks("+");
		ax->GetXaxis()->SetTitle(xaxistitle.c_str());

		ax->Draw("axis");
		canv->Update();
		gPad->Update();
		bRatioBottomPad->cd();
		TH1* ratio = 0;

		ratio = (TH1F*) ((TH1F*) hist1)->Clone("myclone");
		TH1F * looseHistoForRatio = (TH1F *) hist2;
		ratio->SetMarkerSize(1);
		if (ratio->GetSumw2N() == 0)
			ratio->Sumw2();
		ratio->Divide(ratio, looseHistoForRatio, 1, 1, "B");
		ratio->GetYaxis()->SetRangeUser(0.8, 1.2);
		ratio->GetYaxis()->SetTitle("Ratio");

		ratio->GetXaxis()->SetTitle(xaxistitle.c_str());
		ratio->GetXaxis()->SetTitleSize(0.05);
		ratio->GetXaxis()->SetLabelSize(0.05);
		ratio->GetXaxis()->SetTitleOffset(1.25);
		ratio->Draw("p0e1x0,same");
		canv->Update();
		gPad->Update();
		bRatioBottomPad->cd();
		TLine * line = new TLine(75, 1, ax->GetXaxis()->GetXmax(), 1);
		line->SetLineColor(1);
		line->SetLineWidth(1);
		line->Draw("same");
		canv->RedrawAxis();
		canv->Update();
		gPad->Update();

		gPad->Update();
		canv->Update();

		TH1F * relErrors = (TH1F *) hist1->Clone("bla");
		if (relErrors->GetSumw2N() == 0)
			relErrors->Sumw2();
		relErrors->SetDirectory(0);
		relErrors->Add((TH1F *) hist2->Clone("blabla"), -1);
		relErrors->Divide(relErrors, (TH1F *) hist1->Clone(), 1, 1, "B");
		relErrors->SetDirectory(0);
		//relErrors->Draw("same");

		gPad->Update();
		canv->Update();
		TLegend *legend = new TLegend(0.35, 0.65, 0.8, 0.85);
		legend->SetTextSize(0.04);
		legend->SetFillColor(10);
		legend->SetFillStyle(1001);
		legend->SetHeader(addLabelInHisto.c_str());
		legend->AddEntry(hist1, leg1.c_str(), "lp");
		legend->AddEntry(hist2, leg2.c_str(), "lp");
		legend->Draw("same");
		//cmsPrel(normToLumi, 1, isData, isMC);
		string jetlabel = "#geq1#gamma, 2 jets";
		drawCmsPrel(normToLumi, "", false, noJets, false, jetlabel);
		string outputdir = resultDir + "/" + resultFolderName + "/" + newcanvasname;
		//cout << "save:" << outputdir << endl;
		canv->SaveAs((outputdir + "" + ".pdf").c_str());
		canv->Print((outputdir + "" + ".eps").c_str());
		input1->WriteTObject(canv, 0, "overwrite");
		delete canv;
		//Draw rel fit res error in own Canvas

		if (relErrors != 0) {
			string canvasnameRelErr = newcanvasname + "RelErr";
			TCanvas * canvRelErr = new TCanvas(canvasnameRelErr.c_str(), canvasnameRelErr.c_str());
			//cmsPrel(normToLumi, 1, isData, isMC);

			relErrors->GetYaxis()->SetTitle("rel. Error ");
			relErrors->GetYaxis()->SetRangeUser(-0.1, 0.1);
			setErrorsToZero(relErrors);
			if (isMC) {
				relErrors->SetMarkerSize(1);
				relErrors->Draw("EX0P");
			} else {
				relErrors->SetMarkerSize(1);
				relErrors->Draw("EX0P");
			}
			TLegend *legendrel = new TLegend(0.50, 0.71, 0.80, 0.87, "");
			legendrel->SetTextSize(0.04);
			legendrel->SetFillColor(10);
			legendrel->SetFillStyle(1001);
			string datasetname = "";
			legendrel->SetHeader(addLabelInHisto.c_str());
			legendrel->Draw("same");
			canvRelErr->Update();
			drawCmsPrel(normToLumi, "", false, noJets, false, jetlabel);
			canvRelErr->SaveAs((outputdir + "_RATRelErr" + ".pdf").c_str());
			canvRelErr->Print((outputdir + "_RATRelErr" + ".eps").c_str());
			input1->WriteTObject(canvRelErr, 0, "overwrite");
			delete canvRelErr;
		}
	} else {
		cout << "ERROR - histo not found:" << histoname << endl;
	}

}


//
void compareHistosSusyPhotonJetAnalysisFakeBetweenLowMetAndLargeMetSpectrum(TFile * input1, string resultFolderName, string resultDir, string leg1, string leg2, bool isData, bool isMC, double normToLumi, int noJets, string addLabelInHisto) {

  string canvasname           = "c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RAT";
  string canvasnameWholeSpect = "c_DivideXPreselCut_metVsPhotonPt_Bin_From_100_CompTightLoose_RAT";

  string histoname = "blabla1clone2";

  TCanvas * canv1 = (TCanvas *) input1->FindObjectAny(canvasname.c_str());
  TH1F * hist1    = (TH1F *) canv1->FindObject(histoname.c_str());

  if (hist1 != 0) {
    hist1->SetDirectory(0);
    hist1->GetXaxis()->SetRangeUser(75, 1500);

    TCanvas * canv2 = (TCanvas *) input1->FindObjectAny(canvasnameWholeSpect.c_str());
    TH1F * hist2 = (TH1F *) canv2->FindObject(histoname.c_str());

    hist2->SetDirectory(0);
    hist2->GetXaxis()->SetRangeUser(75, 1500);

    double maxYValue = hist1->GetBinContent(hist1->GetMaximumBin());
    if (hist2->GetBinContent(hist2->GetMaximumBin()) > maxYValue)
      maxYValue = hist2->GetBinContent(hist2->GetMaximumBin());
    hist1->GetYaxis()->SetRangeUser(0, maxYValue * 1.2);

    string newcanvasname = "c_ExtrapolationOfFitToLargeMet";
    TCanvas * canv = new TCanvas(newcanvasname.c_str(), newcanvasname.c_str());
		
    gPad->Update();
    canv->Update();
    hist1->SetMarkerStyle(20);

    hist2->SetLineColor(2);
    hist2->SetMarkerColor(2);
    hist2->SetMarkerStyle(25);

    string xaxistitle = hist1->GetXaxis()->GetTitle();
    hist1->GetXaxis()->SetTitle("");
    hist2->GetXaxis()->SetTitle("");
    hist1->GetXaxis()->SetNdivisions(505);
    hist2->GetXaxis()->SetNdivisions(505);
    hist1->GetXaxis()->SetLabelSize(0);
    hist2->GetXaxis()->SetLabelSize(0);
    hist2->GetXaxis()->SetNdivisions(505);

    hist1->DrawClone("EX0P");
    hist2->DrawClone("EX0Psame");

    canv->SetBottomMargin(0.2 + 0.8 * canv->GetBottomMargin() - 0.2 * canv->GetTopMargin());
    TPad *bRatioBottomPad = createRatioBottomPad();
    bRatioBottomPad->Draw();
    bRatioBottomPad->cd();

    TH1 * ax = (TH1*) ((TH1F*) hist1)->Clone("mycloneax");
    ax->SetMinimum(0.9);
    ax->SetMaximum(1.1);
    ax->GetYaxis()->SetNdivisions(505);
    ax->GetXaxis()->SetNdivisions(505);

    ax->GetYaxis()->SetLabelSize(0.03);
    ax->GetYaxis()->SetTitle("Ratio");
    ax->GetYaxis()->SetTitleSize(0.05);
    ax->GetYaxis()->SetTitleOffset(0.05);
    ax->GetXaxis()->SetTitleSize(0.05);
    ax->GetYaxis()->SetTitleOffset(1.3);
    ax->GetXaxis()->SetLabelSize(0.05);
    ax->GetXaxis()->SetTicks("+");
    ax->GetXaxis()->SetTitle(xaxistitle.c_str());

    ax->Draw("axis");
    
    canv->Update();
    gPad->Update();
    bRatioBottomPad->cd();

    TH1* ratio = 0;
    ratio = (TH1F*) ((TH1F*) hist1)->Clone("myclone");
    TH1F * looseHistoForRatio = (TH1F *) hist2;
    ratio->SetMarkerSize(1);
    if (ratio->GetSumw2N() == 0)
      ratio->Sumw2();
    ratio->Divide(ratio, looseHistoForRatio, 1, 1, "B");
    ratio->GetYaxis()->SetRangeUser(0.8, 1.2);
    ratio->GetYaxis()->SetTitle("Ratio");

    ratio->GetXaxis()->SetTitle(xaxistitle.c_str());
    ratio->GetXaxis()->SetTitleSize(0.05);
    ratio->GetXaxis()->SetLabelSize(0.05);
    ratio->GetXaxis()->SetTitleOffset(1.25);
    ratio->Draw("p0e1x0,same");
    canv->Update();
    gPad->Update();
    bRatioBottomPad->cd();

    TLine * line = new TLine(hist1->GetXaxis()->GetXmin(), 1, hist1->GetXaxis()->GetXmax(), 1);
    line->SetLineColor(1);
    line->SetLineWidth(1);
    line->Draw("same");

    canv->RedrawAxis();
    canv->Update();
    gPad->Update();
    gPad->Update();
    canv->Update();

    TH1F * relErrors = (TH1F *) hist1->Clone("bla");
    if (relErrors->GetSumw2N() == 0)
      relErrors->Sumw2();

    relErrors->SetDirectory(0);
    relErrors->Add((TH1F *) hist2->Clone("blabla"), -1);
    relErrors->Divide(relErrors, (TH1F *) hist1->Clone(), 1, 1, "");
    relErrors->SetDirectory(0);
    
    gPad->Update();
    canv->Update();

    TLegend *legend = new TLegend(0.4, 0.7, 0.4, 0.9, "");
    legend->SetX1NDC(0.4);
    legend->SetX2NDC(0.9);
    legend->SetTextSize(0.04);
    legend->SetFillColor(10);
    legend->SetFillStyle(1001);
    legend->AddEntry(hist1, leg1.c_str(), "lp");
    legend->AddEntry(hist2, leg2.c_str(), "lp");
    legend->Draw("same");
    //cmsPrel(normToLumi, 1, isData, isMC);
    drawCmsPrel(normToLumi, "", false, noJets, false);

    string outputdir = resultDir + "/" + resultFolderName + "/" + newcanvasname;

    canv->SaveAs( (outputdir + "" + ".pdf").c_str() );
    canv->SaveAs( (outputdir + "" + ".eps").c_str() );
    input1->WriteTObject(canv, 0, "overwrite");
    delete canv;
	
    // Draw rel fit res error in own canvas
    if (relErrors != 0) {
      string canvasnameRelErr = newcanvasname + "RelErr";
      TCanvas * canvRelErr = new TCanvas(canvasnameRelErr.c_str(), canvasnameRelErr.c_str());
      //cmsPrel(normToLumi, 1, isData, isMC);
      drawCmsPrel(normToLumi, "", false, noJets, false);
      relErrors->GetYaxis()->SetTitle("rel. Error ");
      relErrors->GetYaxis()->SetRangeUser(-0.1, 0.1);
      setErrorsToZero(relErrors);

      relErrors->SetMarkerSize(1);
      relErrors->Draw("EX0P");

      TLegend *legendrel = new TLegend(0.50, 0.71, 0.80, 0.87, "");
      legendrel->SetTextSize(0.04);
      legendrel->SetFillColor(10);
      legendrel->SetFillStyle(1001);
      string datasetname = "";
      legendrel->SetHeader(addLabelInHisto.c_str());
      legendrel->Draw("same");
      canvRelErr->Update();
      canvRelErr->SaveAs((outputdir + "_RATRelErr" + ".pdf").c_str());
      canvRelErr->SaveAs((outputdir + "_RATRelErr" + ".eps").c_str());
      input1->WriteTObject(canvRelErr, 0, "overwrite");
      delete canvRelErr;
    }

  } else {
    cout << "ERROR - histo not found:" << histoname << endl;
  }

  return;
}


//
void compareHistosSusyPhotonJetAnalysisFake( double normToLumi, vector<PlotConfig> configs, 
					     string resultFolderName, string resultDir, string addLabelInHisto, 
					     bool isData, bool isMC, bool drawRatioPad, 
					     int noJets, bool isPrediction = true ) {

  system(("mkdir " + resultDir).c_str());
  system(("mkdir " + resultDir + "/" + resultFolderName).c_str());

  setMyTDRStyle();
  gROOT->SetStyle("mytdrStyle");
  cout << "FAKE COMP:" << addLabelInHisto << endl;

  gStyle->SetHistLineWidth(2);
  gStyle->UseCurrentStyle();
  gROOT->ForceStyle(1);
  vector < string > histoNames;

  histoNames.push_back("photonPt");
  histoNames.push_back("metPt");
  histoNames.push_back("ht");
  histoNames.push_back("hthlt");
  histoNames.push_back("noJets");
  histoNames.push_back("noPV");
  histoNames.push_back("noPVPUWeighted");
  histoNames.push_back("PreselCut_metPtRaw");
  histoNames.push_back("PreselCut_ht");
  histoNames.push_back("PreselCut_metPt");
  histoNames.push_back("PreselCut_metPtT1");
  histoNames.push_back("PreselCut_metPt2");
  histoNames.push_back("PreselCut_photonPt");
  histoNames.push_back("PreselCut_photonEta");
  histoNames.push_back("PreselCut_noJets");
  histoNames.push_back("PreselCut_noPV");
  histoNames.push_back("PreselCut_noPVPUWeighted");
  histoNames.push_back("PreselCut_mht");
  histoNames.push_back("PreselCut_mhtj");
  histoNames.push_back("PreselCut_hthlt");
  histoNames.push_back("PreselCut_hthltN90Hits");
  histoNames.push_back("PreselCut_jetPt");
  histoNames.push_back("PreselCut_HBHENoiseFilter");
  histoNames.push_back("PreselCut_EcaldDCTPFilter");
  histoNames.push_back("PreselCut_EcaldDCBEFilter");
  histoNames.push_back("PreselCut_trackingFailureFilter");
  histoNames.push_back("PreselCut_CSCHaloBeamFilter");
  histoNames.push_back("PreselCut_HcalLaserFilter");
  histoNames.push_back("HBHENoiseFilter");
  histoNames.push_back("EcaldDCTPFilter");
  histoNames.push_back("EcaldDCBEFilter");
  histoNames.push_back("trackingFailureFilter");
  histoNames.push_back("CSCHaloBeamFilter");
  histoNames.push_back("HcalLaserFilter");

  TList * trash = new TList();
  TFile * output = new TFile((resultDir + "/" + resultFolderName + "_plot.root").c_str(), "Recreate");
  bool norm = true;

  // norm always false !!!
  norm = false;

  makeFakeRateComparisonPlots( norm, histoNames, configs, resultFolderName, resultDir, 
			       output, addLabelInHisto, isData, isMC, normToLumi, drawRatioPad, 
			       noJets, isPrediction, false);

  //draw Mht/Met in dependence of Ht/PhotonPt
  string outputdir = resultDir + "/" + resultFolderName + "/";

  vector<double> metPtBins = vector<double> ();
  metPtBins.clear();
  metPtBins.push_back(0);
  metPtBins.push_back(99);

  vector<double> noPVBins = vector<double> ();
  noPVBins.clear();
  noPVBins.push_back(1);
  noPVBins.push_back(2);
  noPVBins.push_back(3);
  noPVBins.push_back(4);
  noPVBins.push_back(5);
  noPVBins.push_back(6);
  noPVBins.push_back(7);
  noPVBins.push_back(8);
  noPVBins.push_back(9);
  noPVBins.push_back(10);
  noPVBins.push_back(15);

  vector<double> noJetBins = vector<double> ();
  noJetBins.clear();
  noJetBins.push_back(1.9);
  noJetBins.push_back(2.9);
  noJetBins.push_back(3.9);
  noJetBins.push_back(4.9);

  vector<double> noJetBinsDijet = vector<double> ();
  noJetBinsDijet.clear();
  noJetBinsDijet.push_back(0.9);
  noJetBinsDijet.push_back(1.9);
  noJetBinsDijet.push_back(2.9);

  vector<double> photonPtBins = vector<double> ();
  photonPtBins.clear();
  photonPtBins.push_back(70);
  photonPtBins.push_back(90);
  photonPtBins.push_back(110);
  photonPtBins.push_back(130);
  photonPtBins.push_back(150);
  photonPtBins.push_back(200);
  photonPtBins.push_back(300);
  photonPtBins.push_back(400);

  vector<double> htBins = vector<double> ();
  htBins.clear();
  htBins.push_back(200);
  htBins.push_back(250);
  htBins.push_back(300);
  htBins.push_back(350);
  htBins.push_back(500);


  makePlotsInBinsOf( "PreselCut_metVsPhotonPt", "Photon Pt", 
		     addLabelInHisto, photonPtBins, outputdir, output, 
		     norm, configs, normToLumi, isData, isMC, false, false, noJets, trash );


  //!!Switch x/Y
  makePlotsInBinsOf( "PreselCut_metVsPhotonPt", "MET", 
		     addLabelInHisto, metPtBins, outputdir, output, 
		     norm, configs, normToLumi, isData, isMC, true, true, noJets );

  makePlotsInBinsOf( "PreselCut_metVsnoJet", "MET", 
		     addLabelInHisto, metPtBins, outputdir, output, 
		     norm, configs, normToLumi, isData, isMC, true, true, noJets );

  makePlotsInBinsOf( "PreselCut_noPVVsPhotonPt", "#PV", 
		     addLabelInHisto, noPVBins, outputdir, output, 
		     norm, configs, normToLumi, isData, isMC, true, true, noJets );


  if (noJets == 2)
    noJetBins = noJetBinsDijet;

  makePlotsInBinsOf( "PreselCut_noJetsVsPhotonPt", "#Jets", 
		     addLabelInHisto, noJetBins, outputdir, output, 
		     norm, configs, normToLumi, isData, isMC, true, true, noJets );

  makePlotsInBinsOf( "PreselCut_noJetsVsPhotonPtLowMet", "#JetsLowMet", 
		     addLabelInHisto, noJetBins, outputdir, output, 
		     norm, configs, normToLumi, isData, isMC, true, true, noJets );

  //make comparison betweenLowMetAndWholeSpectrum
  compareHistosSusyPhotonJetAnalysisFakeBetweenLowMetAndWholeSpectrum( output, resultFolderName, resultDir, 
								       "control region (#slash{E}_{T}< 100 GeV)", "all events", 
								       isData, isMC, normToLumi, noJets, addLabelInHisto );

  compareHistosSusyPhotonJetAnalysisFakeBetweenLowMetAndLargeMetSpectrum( output, resultFolderName, resultDir, 
									  "control region(#slash{E}_{T}< 100 GeV)", "signal region(#slash{E}_{T}> 100 GeV)", 
									  isData, isMC, normToLumi, noJets, addLabelInHisto );

  compareHistosSusyPhotonJetAnalysisFakeBetweenNoPV( output, resultFolderName, resultDir, 
						     "All", ">1PV", isData, isMC, normToLumi, noJets );

  string noOfJets = getStringFromInt(noJets);
  compareHistosSusyPhotonJetAnalysisFakeBetweenNoJets( output, resultFolderName, resultDir, 
						       (">=" + noOfJets + " jets").c_str(), ">1Jet", 
						       isData, isMC, normToLumi, noJets, true );

  compareHistosSusyPhotonJetAnalysisFakeBetweenNoJets( output, resultFolderName, resultDir, 
						       (">=" + noOfJets + " jets").c_str(), ">1Jet", 
						       isData, isMC, normToLumi, noJets, false );

  if (noJets == 2)
    compareHistosSusyPhotonJetAnalysisFakeBetweenLowMetAndWholeSpectrumDiJet( output, resultFolderName, resultDir, 
									      "control region (#slash{E}_{T}< 100 GeV)", "all events", 
									      isData, isMC, normToLumi, noJets, addLabelInHisto );

  // delete trash
  TIter nextTrash(trash);
  while (TObject * obj = (TObject *) nextTrash()) {
    if (obj != 0)
      delete obj;
    obj = 0;
  }

  // close outputfile
  output->Close();
  delete output;

}


//
EventCounts getEventCountsForSample(PlotConfig config, string currhname, double normToLumi, double metCut) {

  EventCounts retEvtCounts;
  double lumiScaleFactor = normToLumi / (config.lumi);
  if (!config.isMC) {
    lumiScaleFactor = 1;
  }

  TFile *input = new TFile((config.filename).c_str(), "read");
  input->cd((config.dirName).c_str());
  TDirectory *subdir = gDirectory;
  cout << "CURRENT SUBDIR:" << subdir->GetName() << endl;

  TH1F * hOrig = (TH1F *) gDirectory->FindObjectAny(currhname.c_str());
  if (hOrig->GetSumw2N() == 0)
    hOrig->Sumw2();
  TH1F * h = (TH1F *) hOrig->Clone("");

  if (h != 0) {
    if (h->GetSumw2N() == 0)
      h->Sumw2();

    string currhnameSYSTUP = currhname;
    string currhnameSYSTDOWN = currhname;

    if (containsSubstr(currhname, "PreselCut_")) {
      currhnameSYSTUP = replaceSubstr(currhname, "PreselCut_", "PreselCut_SYSTUP_");
      currhnameSYSTDOWN = replaceSubstr(currhname, "PreselCut_", "PreselCut_SYSTDOWN_");
    } else {
      currhnameSYSTUP = "SYSTUP_" + currhname;
      currhnameSYSTDOWN = "SYSTDOWN_" + currhname;
    }

    TH1F * hSYSTUPOrig = (TH1F *) gDirectory->FindObjectAny(currhnameSYSTUP.c_str());
    TH1F * hSYSTUP = (TH1F *) hSYSTUPOrig->Clone("");
    if (hSYSTUP->GetSumw2N() == 0)
      hSYSTUP->Sumw2();

    TH1F * hSYSTDOWNOrig = (TH1F *) gDirectory->FindObjectAny(currhnameSYSTDOWN.c_str());
    TH1F * hSYSTDOWN = (TH1F *) hSYSTDOWNOrig->Clone("");
    if (hSYSTDOWN->GetSumw2N() == 0)
      hSYSTDOWN->Sumw2();
    // Scale to lumi first to get stat errors right
    h->Scale(lumiScaleFactor);

    if (hSYSTUP != 0)
      hSYSTUP->Scale(lumiScaleFactor);
    if (hSYSTDOWN != 0)
      hSYSTDOWN->Scale(lumiScaleFactor);

    TH1F * hSystErr   = (TH1F *) h->Clone("systerr");
    TH1F * hSystErrDn = (TH1F *) h->Clone("systerrDn");
    TH1F * hStatErr   = (TH1F *) h->Clone("staterr");
    TH1F * hCombErr   = (TH1F *) h->Clone("comberr");
    TH1F * hCombErrDn = (TH1F *) h->Clone("comberrDn");

    double systErrCompl      = 0;
    double systErrComplDown  = 0;
    double statErrComplQuadr = 0;
    double combErrComplQuadr = 0;
    double noEvts = 0.;

    //find first bin which contains MET Value
    int startBin = h->FindBin(metCut);
    cout << " - bin lowedge: " << h->GetBinLowEdge(startBin) << endl;
    cout << " - Met cut: " << metCut << endl;

    for (int b = startBin; b < h->GetNbinsX(); b++) {
      double mainHistoContent = h->GetBinContent(b);
      noEvts += mainHistoContent;

      double systUpHistoContent = hSYSTUP->GetBinContent(b);
      double systDnHistoContent = hSYSTDOWN->GetBinContent(b);
      double systDiff   = fabs((double) systUpHistoContent - mainHistoContent);
      double systDiffDn = fabs((double) mainHistoContent - systDnHistoContent);

      systErrCompl     = systErrCompl + systDiff;
      systErrComplDown = systErrComplDown + systDiffDn;

      double statErr = h->GetBinError(b);
      statErrComplQuadr = statErrComplQuadr + (statErr * statErr);

      double combError   = sqrt(systDiff * systDiff + statErr * statErr);
      double combErrorDn = sqrt(systDiffDn * systDiffDn + statErr * statErr);

      hSystErr->SetBinError(b, systDiff);
      hSystErrDn->SetBinError(b, systDiffDn);
      hStatErr->SetBinError(b, statErr);
      hCombErr->SetBinError(b, combError);
      hCombErrDn->SetBinError(b, combErrorDn);
    }

    retEvtCounts.latexname   = config.latexname;
    retEvtCounts.samplename  = config.sampleName;
    retEvtCounts.noEvts      = noEvts;
    retEvtCounts.systErrUp   = systErrCompl;
    retEvtCounts.systErrDown = systErrComplDown;
    retEvtCounts.statErr     = sqrt(statErrComplQuadr);
    retEvtCounts.combErr     = sqrt(retEvtCounts.statErr * retEvtCounts.statErr + retEvtCounts.systErrUp * retEvtCounts.systErrUp);
    retEvtCounts.noOverflows = h->GetBinContent(h->GetNbinsX() + 1);
    retEvtCounts.isMC        = config.isMC;

    if (retEvtCounts.isMC && retEvtCounts.systErrUp == 0 && config.MConlySyst) {
      retEvtCounts.systErrUp = noEvts;
      retEvtCounts.systErrDown = noEvts;
    }
  }

  return retEvtCounts;
}


//
void compareHistosSusyPhotonJetAnalysis(vector<string> histoNames, double normToLumi, 
					bool isData, bool isMC, vector<PlotConfig> configs, 
					string resultFolderName, string resultDir, string addLabelInHisto = "", 
					bool stacked = false, bool norm = false, bool makeN1Plots = false, bool doPU = false,
					int noOfJets = 3) {
  if (norm && stacked) {
    cout << "ERROR - normalize and draw stacked histos is not implemented yet!" << endl;    
  }
  if (norm) {
    resultFolderName = "Norm_" + resultFolderName;
  }
  if (configs.size() == 0) {
    cout << "ERROR - no configs given--->nothing to plot...." << endl;
    
  }
  system(("mkdir " + resultDir).c_str());
  system(("mkdir " + resultDir + "/" + resultFolderName).c_str());

  setMyTDRStyle();
  gROOT->SetStyle("mytdrStyle");
  gStyle->SetHistLineWidth(2);
  gStyle->UseCurrentStyle();
  gROOT->ForceStyle(1);
  gStyle->SetTextSize(0.04);

  //start processing
  TList * trash = new TList();

  //read first config and make list of histograms
  vector < string > histoNames2D;

  if (histoNames.size() == 0) {
    TFile *input1 = new TFile((configs.at(0).filename).c_str(), "read");
    input1->cd((configs.at(0).dirName).c_str());
    TDirectory *subdir = gDirectory;
    //cout << "CURRENT SUBDIR:" << subdir->GetName() << endl;
    TList* listofkeys = (TList*) (subdir->GetListOfKeys());
    TIter key(listofkeys);
    while (TKey* keyHisto = (TKey*) key()) {
      string hname = keyHisto->GetName();
      if (containsSubstr(keyHisto->GetClassName(), "TH1")) {
	histoNames.push_back(hname);
	//cout << "add histo name:" << keyHisto->GetClassName() << endl;
      } else if (containsSubstr(keyHisto->GetClassName(), "TH2")) {
	histoNames2D.push_back(hname);
	//cout << "add histo name:" << keyHisto->GetClassName() << endl;
      }
    }
    input1->Close();
    delete input1;
  }

  TFile * output = new TFile((resultDir + "/" + resultFolderName + "_plot.root").c_str(), "Recreate");
  //make PUWeightPlots for data & 1MC sample (only if data is given at all)
  if (doPU) {
    createNoPVWeightsHisto(configs, output);
  }

  //make canvas for each histo
  if (!doPU) {
    for (int c = 0; c < (int) histoNames.size(); ++c) {
      string currhname = histoNames[c];

      if ((!containsSubstr(currhname, "N_1") || makeN1Plots) && (!containsSubstr(currhname, "SYST"))
	  && (!containsSubstr(currhname, "photonTrig"))
	  && (!containsSubstr(currhname, "chargedIso"))
	  && (!containsSubstr(currhname, "photonIso"))
	  && (!containsSubstr(currhname, "neutralIso"))
	  && (!containsSubstr(currhname, "Filter"))
	  && (!containsSubstr(currhname, "LowMet")) //VS!!!
	  && (!containsSubstr(currhname, "Gen")) //VS!!!
	  ) {

	string canvasname = "c_" + currhname;
	TCanvas * canv = new TCanvas(canvasname.c_str(), canvasname.c_str());
	trash->Add(canv);
	canv->SetLogy(1);
	gPad->SetLogy(1);
	gPad->Update();
	canv->Update();

	//	TLegend *legend = new TLegend(0.42, 0.615, 0.920, 0.928, "");
	//	TLegend *legendClo = new TLegend(0.35, 0.58, 0.84, 0.88, "");
	TLegend *legend       = new TLegend(0.42, 0.65, 0.920, 0.928, ""); //VS!!!
	TLegend *legendClo    = new TLegend(0.35, 0.75, 0.84, 0.88, ""); //VS!!!
	TList * legendentries = new TList();

	trash->Add(legend);
	legend->SetFillColor(10);
	legend->SetFillStyle(1001);
	legendClo->SetFillColor(10);
	legendClo->SetFillStyle(1001);

	//loop over all configs and draw histos in canvas
	THStack * stack = new THStack("stack", "stack");
	TH1F * allstacked = 0;
	
	TList* histosToDrawInAdditionToStack = new TList();
	histosToDrawInAdditionToStack->Clear();
	TList* histosDataToDrawInAdditionToStack = new TList();
	histosDataToDrawInAdditionToStack->Clear();
	TH1F * legdummy = new TH1F("legdummy", "legdummy", 5, 0, 100);
	
	legdummy->SetFillColor(0);
	legdummy->SetLineColor(0);
	double highestYValue = 0.;
	double lowestYValue = 500.;
	TH1F * firstHisto = 0;

	string xaxistitle = getAxisTitle(currhname);
	for (int conf = 0; conf < (int) configs.size(); ++conf) {	
	  TFile *input = new TFile((configs.at(conf).filename).c_str(), "read");
	  input->cd((configs.at(conf).dirName).c_str());
	  double lumiScaleFactor = normToLumi / (double) (configs.at(conf).lumi);
	  if (!configs.at(conf).isMC) {
	    lumiScaleFactor = 1;
	  }
	  TH1F * h = readFileAndSetSystErrorsAccordingToSYSTHistos(currhname, lumiScaleFactor, configs.at(conf).MConlySyst);
	  if (h != 0) {
	    if (h->GetEntries() != 0) {
	      canv->cd();
	      canv->Update();
	      gPad->Update();
	      TH1F * hClone = (TH1F *) h->Clone();
	      hClone->GetXaxis()->SetNdivisions(505);
	      hClone->SetDirectory(0);
	      
	      canv->Update();
	      gPad->Update();
	      if (hClone != 0) {
		if (hClone->GetEntries() != 0) {
		  
		  hClone->SetLineColor(configs.at(conf).linecolor);
		  if (hClone->GetSumw2N() == 0)
		    hClone->Sumw2();
			
		  if (hClone->GetBinContent(hClone->GetMaximumBin()) > highestYValue) {
		    highestYValue = 1.2 * hClone->GetBinContent(hClone->GetMaximumBin());
		    if (!norm) {
		      highestYValue = 100 * hClone->GetBinContent(hClone->GetMaximumBin());
		    }
		  }
		  if (hClone->GetBinContent(hClone->GetMinimumBin()) < lowestYValue) {
		    lowestYValue = 0.5 * hClone->GetBinContent(hClone->GetMinimumBin());
		    
		  }

		  canv->Update();
		  gPad->Update();
		  if (configs.at(conf).isPutOnStack && stacked) {
		    hClone->SetFillColor(configs.at(conf).linecolor);
		  }
			
		  double binwidth = hClone->GetXaxis()->GetBinWidth(1);
			
		  bool isGeV = containsSubstr(xaxistitle, "[GeV]");
		  string binwidthstr = HistoDrawUtil::getStringFromDouble(binwidth, 1);
		  if (containsSubstr(binwidthstr, ".0")) {
		    binwidthstr = HistoDrawUtil::getStringFromInt(binwidth);
		  }
		  //		  string yaxistitle = "Number of Events / GeV";
		  string yaxistitle = "Number of Events / Bin"; //VS!!!

		  if (norm) {
		    yaxistitle = "Norm. " + yaxistitle;
		  }

		  hClone->GetYaxis()->SetTitle(yaxistitle.c_str());
		  if (!isData && isMC) {
		    hClone->GetXaxis()->SetTitle(xaxistitle.c_str());
		  } else {
		    hClone->GetXaxis()->SetLabelSize(0);
		  }
		  hClone->SetTitle((configs.at(conf).sampleName).c_str());
		  if (configs.at(conf).isPutOnStack && stacked) {
		    stack->Add((TH1F*) hClone);
			  
		    if (allstacked == 0)
		      allstacked = (TH1F*) hClone->Clone();
		    else
		      allstacked->Add((TH1F*) hClone->Clone());
		    allstacked->SetDirectory(0);
		    
		  } else if (conf == 0) {
		    if (!configs.at(conf).isMC) {
		      hClone->SetTitle((configs.at(conf).sampleName).c_str());
		      histosDataToDrawInAdditionToStack->Add(hClone);
			    
		    } else
		      histosToDrawInAdditionToStack->Add(hClone);

		    if (!stacked) {
		      if (norm && hClone->Integral() != 0) {
			if (hClone->GetSumw2N() == 0)
			  hClone->Sumw2();
			hClone->Scale(1 / hClone->Integral());
			
		      }

		      //cout<<"DRAW"<<endl;
			    
		      string drawoption = "hist E";
		      if (isData && isMC) {
			drawoption = drawoption + "";
		      }
		      if (!configs.at(conf).isMC) {
			drawoption = "E X0";
		      } else if (configs.at(conf).fillstyle != 0) {
			hClone->SetMarkerSize(0);
			hClone->SetFillColor(configs.at(conf).fillcolor);
			hClone->SetFillStyle(configs.at(conf).fillstyle);
			drawoption = "E2";
		      } else {
			hClone->SetMarkerSize(0);
		      }
			    
		      hClone->Draw(drawoption.c_str());
		      firstHisto = hClone;
		      firstHisto->SetDirectory(0);
		    }
			  
		  } else {
		    
		    if (!configs.at(conf).isMC) {
		      histosDataToDrawInAdditionToStack->Add(hClone);
		    } else {
			    
		      histosToDrawInAdditionToStack->Add(hClone);
			    
		    }
		    if (!stacked) {
		      if (norm && hClone->Integral() != 0) {
			if (hClone->GetSumw2N() == 0)
			  hClone->Sumw2();
			hClone->Scale(1 / hClone->Integral());
			
		      }
		      //cout<<"DRAW same"<<endl;
			    
			    
		      string drawoption = "same hist E";
		      if (isData && isMC) {
			drawoption = drawoption + "";
		      }
		      if (!configs.at(conf).isMC) {
			drawoption = "same E X0";
		      } else if (configs.at(conf).fillstyle != 0) {
			hClone->SetMarkerSize(0);
			hClone->SetFillColor(configs.at(conf).fillcolor);
			hClone->SetFillStyle(configs.at(conf).fillstyle);
			drawoption = "same E2";
		      } else {
			hClone->SetMarkerSize(0);
		      }
			    
		      hClone->Draw(drawoption.c_str());
		    }
		  }
		  if (!configs.at(conf).isMC) {
		    legendClo->AddEntry(hClone, hClone->GetTitle(), "p");
			  
		  } else {
		    if (configs.at(conf).isPutOnStack || configs.at(conf).fillstyle != 0) {
		      TLegendEntry * entry = legend->AddEntry(hClone, hClone->GetTitle(), "f");
		      legendentries->Add((TObject *) entry);
		      
		    } else {
		      TLegendEntry * entry = legend->AddEntry(hClone, hClone->GetTitle(), "l");
		      legendentries->Add((TObject *) entry);
		    }
		  }
		}
	      }
	    } else {
	      cout << "WARNING --------------histo empty!" << currhname << endl;
	    }
	  } else {
	    cout << "WARNING --------------histo NOT found!" << currhname << endl;
	  }
	  canv->cd();
	  canv->Update();
	  gPad->Update();
	  //close current input

	  input->Close();
	  delete input;
	  input = 0;
	}

	if (firstHisto != 0) {
	  canv->Update();
	  gPad->Update();
	  if(lowestYValue==0){lowestYValue=0.1;}
	  lowestYValue=0.1;
	  firstHisto->GetYaxis()->SetRangeUser(lowestYValue, highestYValue);
	  canv->Update();
	  gPad->Update();
	}

	//cout << "process stacked histograms..." << endl;
	TList * histosToDrawInAdditionToStackPlusBkg = new TList();
	if (stacked && allstacked != 0) {
		
	  canv->cd();
	  canv->Update();
	  gPad->Update();
	  if (allstacked->GetBinContent(allstacked->GetMaximumBin()) > highestYValue)
	    highestYValue = 100 * allstacked->GetBinContent(allstacked->GetMaximumBin());
		
	  stack->SetMaximum(10*highestYValue);
	  
	  stack->SetMaximum(10 * highestYValue);
	  if (allstacked->GetMaximumBin() > 2) {
	    stack->SetMaximum(1000 * highestYValue);
	  }
	   //VS!!! -> redo
	  stack->SetMinimum(0.1);
	  if (allstacked->GetBinContent(allstacked->GetMinimumBin()) < 0.1 && allstacked->GetBinContent(allstacked->GetMinimumBin()) > 0) {
	    stack->SetMinimum(0.5*allstacked->GetBinContent(allstacked->GetMinimumBin()));
	  }
		
	  stack->Draw("");
	  TList* stacklist = stack->GetHists();
	  TIter keySt(stacklist);
	  TH1 * hst = 0;
		
	  while ((hst = (TH1 *) keySt())) {
	    hst->SetMinimum(0.1);
	    hst->SetMaximum(highestYValue);
		  
	    stack->GetHistogram()->GetXaxis()->SetTitle(hst->GetXaxis()->GetTitle());
	    stack->GetHistogram()->GetYaxis()->SetTitle(hst->GetYaxis()->GetTitle());
	  }

	  if (isData && isMC) {
	    stack->GetHistogram()->GetXaxis()->SetLabelSize(0);
	    stack->GetHistogram()->GetXaxis()->SetTitle("");
	  }
		
	  stack->Draw("hist");
		
	  //allstacked->Draw("same");
		
	  TIter keyH(histosToDrawInAdditionToStack);
	  while (TObject * obj = (TObject *) keyH()) {
	    ((TH1F *) obj)->GetYaxis()->SetRangeUser(0.1, highestYValue);
		  
	    if (isData && isMC) {
	      ((TH1F *) obj)->Draw("same hist");
	    } else
	      ((TH1F *) obj)->Draw("same hist");
	    //Add allstacked=background to signal mc for integral plots
	    TH1F * objToDraw = ((TH1F*) obj->Clone());
	    objToDraw->Add((TH1F*) allstacked->Clone());
	    string newtitle = objToDraw->GetTitle();
	    newtitle = "Bkg + " + newtitle;
	    objToDraw->SetTitle(newtitle.c_str());
	    histosToDrawInAdditionToStackPlusBkg->Add(objToDraw);
		  
	  }
		
	  TIter keyHDat(histosDataToDrawInAdditionToStack);
	  while (TObject * obj = (TObject *) keyHDat()) {
	    ((TH1F*) obj)->GetYaxis()->SetRangeUser(0.1, highestYValue);
		  
	    if (isData && isMC) {
	      ((TH1F*) obj)->Draw("same E X0");
	    } else
	      ((TH1F*) obj)->Draw("same E X0");
	    if (allstacked != 0) {
	      if (allstacked->GetEntries() > 0) {
		allstacked->SetLineColor(0);
		allstacked->SetFillColor(1);
		allstacked->SetMarkerSize(0);
		allstacked->SetFillStyle(3005);
		allstacked->Draw("sameE2");
		TLegendEntry * entry = legend->AddEntry(allstacked, "Total SM bkg", "f");
		legendentries->Add((TObject *) entry);
		canv->SetBottomMargin(0.2 + 0.8 * canv->GetBottomMargin() - 0.2 * canv->GetTopMargin());
		      
		TPad *bRatioBottomPad = createRatioBottomPad();
		bRatioBottomPad->Draw();
		bRatioBottomPad->cd();
		//		gPad->SetLogy(0); //VS!!! -> redo
		gPad->SetLogy(1);
		TH1 * ax = (TH1*) ((TH1F*) obj)->Clone();
		/*
		ax->SetMinimum(0.5); //VS!!! -> redo
		ax->SetMaximum(1.5);
		*/
		ax->SetMinimum(0.2);
		ax->SetMaximum(4);
		ax->GetYaxis()->SetNdivisions(505);
		//		ax->GetYaxis()->SetNdivisions(503);
		ax->GetYaxis()->SetTitle("Data/Bkg");
		ax->GetYaxis()->SetTitleSize(0.04);
		ax->GetYaxis()->SetLabelSize(0.03);
		ax->GetYaxis()->SetLabelColor(1);
		ax->GetYaxis()->SetTitleOffset(1.25);
		ax->GetXaxis()->SetLabelSize(0.05);
		ax->GetXaxis()->SetNdivisions(505);
		ax->GetXaxis()->SetTicks("+");
		ax->GetXaxis()->SetTitle(xaxistitle.c_str());

		ax->Draw("axis");
		TH1F* ratio = 0;
		TH1F* ratioSyst = 0;
		      
		ratio = (TH1F*) ((TH1F*) obj)->Clone();
		if (ratio->GetSumw2N() == 0)
		  ratio->Sumw2();
		ratio = divideHistosForRatio(ratio, allstacked);
		ratioSyst = getSystErrForRatio(allstacked);
		ratio->Draw("p0e1x0,same");
		ratioSyst->Draw("sameE2");

		TLine * line = new TLine(ratio->GetXaxis()->GetXmin(), 1, ratio->GetXaxis()->GetXmax(), 1);
		line->SetLineColor(1);
		line->SetLineWidth(1);
		line->Draw("same");

		/*
		TLatex axlabel;
		axlabel.SetNDC(false);
		axlabel.SetTextFont(43);
		axlabel.SetTextSize(23);
		axlabel.SetTextColor(1);
		std::string out = "1";
		axlabel.DrawLatex(-20, 0.8, out.c_str());
		out = "3";
		axlabel.DrawLatex(-20, 2.8, out.c_str());
		out = "0.5"; //VS!!!
		out = "0.3";
		axlabel.DrawLatex(-38, 0.2, out.c_str());
		*/ //VS!!!

		canv->Update();
		gPad->Update();
	      }
	    }
	  }
	}

	//cout << "draw legend...MC entries..." << endl;
	TIter nextLeg(legendentries, kIterBackward);
	while (TObject * obj = (TObject *) nextLeg()) {
	  TLegendEntry * entry = (TLegendEntry *) obj;

	  if (containsSubstr(entry->GetOption(), "f")) {
	    legendClo->AddEntry(entry->GetObject(), entry->GetLabel(), entry->GetOption());
	    //cout << "iter legend bkwd..." << entry->GetLabel() << endl;
	  }
	}
	//cout<<  "draw legend...Signal MC entries..." << endl;

	if (legendentries->GetSize() > 3) {
	  //VS!!!
	  //	  legendClo->AddEntry(legdummy, " ", "l");
	  //	  legendClo->AddEntry(legdummy, " ", "l");
	  //legendClo->AddEntry(legdummy, "GGM m_{#tilde{q}}/m_{#tilde{g}}/m_{#tilde{#chi}^{0}_{1}} [GeV]", "l");
	  //	  legendClo->AddEntry(legdummy, " ", "l");

	  legendClo->SetNColumns(2);
	}
	
	TIter nextLegF(legendentries, kIterForward);
	while (TObject * obj = (TObject *) nextLegF()) {

	  TLegendEntry * entry = (TLegendEntry *) obj;
	  if (containsSubstr(entry->GetOption(), "l")) {
	    legendClo->AddEntry(entry->GetObject(), entry->GetLabel(), entry->GetOption());
	  }
	}
	canv->Update();
	gPad->Update();

	legendClo->SetTextSize(0.04);
	legendClo->Draw("same");
	bool drawCMSPrel=false;
	cout<<"canv name:"<<canv->GetName()<<endl;
	cout<<"legendentries:"<<legendentries->GetSize()<<endl;	
	if (legendentries->GetSize() > 3 ) {
	  cout<<"legendentries!!1:"<<noOfJets<<endl;	
	  if(HistoDrawUtil::containsSubstr(addLabelInHisto,"2")){
	    if(HistoDrawUtil::containsSubstr(canv->GetName(),"c_PreselCut_metPt")){
	      drawCMSPrel=true;
	      cout<<"canv name!!!!!!!!!:"<<canv->GetName()<<endl;
	    }
	  }
	}

	if (addLabelInHisto == "") {
	  drawCmsPrel(normToLumi, "", false, noOfJets, false, addLabelInHisto,true,drawCMSPrel);
	} else
	  drawCmsPrel(normToLumi, "", false, 0, false, addLabelInHisto,true,drawCMSPrel);
	      
	canv->Update();
	gPad->Update();

	//cout << "save plot..." << endl;
	string outputdir = resultDir + "/" + resultFolderName + "/" + canv->GetName();
	//canv->SaveAs((outputdir + ".gif").c_str());
	canv->SaveAs((outputdir + ".pdf").c_str());
	canv->Print( (outputdir + ".eps").c_str());
	output->WriteTObject(canv, 0, "overwrite");

	//save canvas to file
	//make ratio histo (last two histos)
	if (!stacked) {
	  //add ratio histo of last two histograms
	  makeRatioPlotLastTwoHistos(histosToDrawInAdditionToStack, canv->GetName(), normToLumi, isData, isMC, outputdir, output);
	}
	//make INT & S/B plots
	if ((containsSubstr(currhname, "mht") || containsSubstr(currhname, "metPt")) && stacked) {
	  makeIntegralPlots(histosToDrawInAdditionToStackPlusBkg, histosDataToDrawInAdditionToStack, allstacked, addLabelInHisto, normToLumi, isData, isMC, outputdir, output);
	  makeSignalToBackgroundPlots(histosToDrawInAdditionToStack, allstacked, addLabelInHisto, normToLumi, isData, isMC, outputdir, output);
	  makeSignalToBackgroundErrPlots(histosToDrawInAdditionToStack, allstacked, addLabelInHisto, normToLumi, isData, isMC, outputdir, output);
	}

	//clear stuff
	histosToDrawInAdditionToStack->Clear();
	histosDataToDrawInAdditionToStack->Clear();
	delete legdummy;
      }
      //cout << "end histo processing..." << endl;
    }
  }

  //cout << "delete trash:" << endl;
  TIter nextTrash(trash);
  while (TObject * obj = (TObject *) nextTrash()) {
    if (obj != 0)
      delete obj;
    obj = 0;
  }

  //close outputfile
  //cout << "close output" << output->GetName() << endl;
  output->Close();
  delete output;

};


void calculateEventCounts(PlotConfig * data2011, PlotConfig * data2011DCS, double lumiData, double lumiDataDCS, vector<PlotConfig> configsForEventCountBkgEst, vector<PlotConfig> configsForEventCountBkgEstCorr2, PlotConfig * qcdAndPhotonJetCorrData, PlotConfig * qcdAndPhotonJetCorrMC,
  PlotConfig * qcdAndPhotonJet, PlotConfig * ewkData, PlotConfig * ewkMC, PlotConfig * ewkMConly, vector<PlotConfig> configsForEventCountSignalMCs, vector<PlotConfig> configsForEventCountBKGAllMCs, string filename, double metCut, double uc_FitMC, double uc_FitData, double uc_FitExtrapol,
  double ewkFakeRate, double ewkFakeRateSyst, string jetSelApp = "") {
	//=====START EVENT COUNT CALCULATION=================================
	//===================================================================
	//DATA
	string distName = "PreselCut_metPt";

	EventCounts evtCtsdata = getEventCountsForSample(*data2011, "PreselCut_metPt", lumiData, metCut);
	//DATA DCS
	EventCounts evtCtsdataDCS = getEventCountsForSample(*data2011DCS, "PreselCut_metPt", lumiDataDCS, metCut);
	//BKG ESTIMATION
	vector<EventCounts> evtCountsBkgEst;
	EventCounts bkgEstTot;
	bkgEstTot.samplename = "Total Bkg Prediction";
	bkgEstTot.latexname = "SMBkgTot";
	for (int conf = 0; conf < (int) configsForEventCountBkgEst.size(); ++conf) {

		EventCounts evtCountFullSel = getEventCountsForSample(configsForEventCountBkgEst.at(conf), "PreselCut_metPt", lumiData, metCut);
		evtCountsBkgEst.push_back(evtCountFullSel);

		bkgEstTot.noEvts += evtCountFullSel.noEvts;
		bkgEstTot.systErrUp += evtCountFullSel.systErrUp;
		bkgEstTot.systErrDown += evtCountFullSel.systErrDown;
		bkgEstTot.statErr += (evtCountFullSel.statErr * evtCountFullSel.statErr);

	}
	double totBkgEst = bkgEstTot.noEvts;
	bkgEstTot.statErr = sqrt(bkgEstTot.statErr);
	bkgEstTot.combErr = sqrt(bkgEstTot.statErr * bkgEstTot.statErr + bkgEstTot.systErrUp * bkgEstTot.systErrUp);
	//BKG ESTIMATION CORR2
	vector<EventCounts> evtCountsBkgEstCorr2;
	EventCounts bkgEstTotCorr2;
	bkgEstTotCorr2.samplename = "Total Bkg Prediction (Corr 2)";
	bkgEstTotCorr2.latexname = "SMBkgTotCorr2";
	for (int conf = 0; conf < (int) configsForEventCountBkgEstCorr2.size(); ++conf) {

		EventCounts evtCountFullSelCorr2 = getEventCountsForSample(configsForEventCountBkgEstCorr2.at(conf), "PreselCut_metPt", lumiData, metCut);
		evtCountsBkgEst.push_back(evtCountFullSelCorr2);

		bkgEstTotCorr2.noEvts += evtCountFullSelCorr2.noEvts;
		bkgEstTotCorr2.systErrUp += evtCountFullSelCorr2.systErrUp;
		bkgEstTotCorr2.systErrDown += evtCountFullSelCorr2.systErrDown;
		bkgEstTotCorr2.statErr += (evtCountFullSelCorr2.statErr * evtCountFullSelCorr2.statErr);

	}
	double totBkgEstCorr2 = bkgEstTotCorr2.noEvts;
	bkgEstTotCorr2.statErr = sqrt(bkgEstTotCorr2.statErr);
	bkgEstTotCorr2.combErr = sqrt(bkgEstTotCorr2.statErr * bkgEstTotCorr2.statErr + bkgEstTotCorr2.systErrUp * bkgEstTotCorr2.systErrUp);

	//each bkg est
	//QCD
	EventCounts qcdBkgFromData = getEventCountsForSample(*qcdAndPhotonJetCorrData, "PreselCut_metPt", lumiData, metCut);

	EventCounts qcdBkgFromMC = getEventCountsForSample(*qcdAndPhotonJetCorrMC, "PreselCut_metPt", lumiData, metCut);

	EventCounts qcdBkgOnlyFromMC = getEventCountsForSample(*qcdAndPhotonJet, "PreselCut_metPt", lumiData, metCut);

	//EWK
	EventCounts ewkBkgFromData = getEventCountsForSample(*ewkData, "PreselCut_metPt", lumiData, metCut);

	EventCounts ewkBkgFromMC = getEventCountsForSample(*ewkMC, "PreselCut_metPt", lumiData, metCut);

	EventCounts ewkBkgOnlyFromMC = getEventCountsForSample(*ewkMConly, "PreselCut_metPt", lumiData, metCut);

	//BKG ESTIMATION DCS
	vector<EventCounts> evtCountsBkgEstDCS;
	EventCounts bkgEstTotDCS;
	bkgEstTotDCS.samplename = "Total Bkg Prediction (DCSonly)";
	for (int conf = 0; conf < (int) configsForEventCountBkgEst.size(); ++conf) {

		EventCounts evtCountFullSel = getEventCountsForSample(configsForEventCountBkgEst.at(conf), "PreselCut_metPt", lumiDataDCS, metCut);
		evtCountsBkgEstDCS.push_back(evtCountFullSel);

		bkgEstTotDCS.noEvts += evtCountFullSel.noEvts;
		bkgEstTotDCS.systErrUp += evtCountFullSel.systErrUp;
		bkgEstTotDCS.systErrDown += evtCountFullSel.systErrDown;
		bkgEstTotDCS.statErr += (evtCountFullSel.statErr * evtCountFullSel.statErr);

	}
	bkgEstTotDCS.statErr = sqrt(bkgEstTotDCS.statErr);
	//SIGNAL EXPECTATION
	vector<EventCounts> evtCountsSignalMCs;
	for (int conf = 0; conf < (int) configsForEventCountSignalMCs.size(); ++conf) {

		EventCounts evtCountFullSel = getEventCountsForSample(configsForEventCountSignalMCs.at(conf), "PreselCut_metPt", lumiData, metCut);
		evtCountsSignalMCs.push_back(evtCountFullSel);
	}

	//MC INFO
	vector<EventCounts> evtCountsBkgAllMCs;
	for (int conf = 0; conf < (int) configsForEventCountBKGAllMCs.size(); ++conf) {

		EventCounts evtCountFullSel = getEventCountsForSample(configsForEventCountBKGAllMCs.at(conf), "PreselCut_metPt", lumiData, metCut);
		evtCountsBkgAllMCs.push_back(evtCountFullSel);
	}
	EventCounts qcdTemp = getEventCountsForSample(*qcdAndPhotonJetCorrData, "PreselCut_metPt", lumiData, metCut);
	////////////////PRINT INFO
	cout << "===============Lumi:" << lumiData << " 1/pb" << endl;
	evtCtsdata.printCounts();
	bkgEstTot.printCounts();
	cout << "Bkg contains:" << endl;
	for (int ct = 0; ct < (int) evtCountsBkgEst.size(); ++ct) {
		evtCountsBkgEst.at(ct).printCounts();
	}
	cout << "!!!!!!!Bkg Corr2:" << endl;
	bkgEstTotCorr2.printCounts();
	cout << "===============Lumi:" << lumiDataDCS << " 1/pb (DCS only)" << endl;
	evtCtsdataDCS.printCounts();
	bkgEstTotDCS.printCounts();
	cout << "Bkg contains:" << endl;
	for (int ct = 0; ct < (int) evtCountsBkgEstDCS.size(); ++ct) {
		evtCountsBkgEstDCS.at(ct).printCounts();
	}
	cout << "==============QCD Background Closure Test" << endl;
	//QCD Bkg only
	qcdBkgFromData.printCounts();
	qcdBkgFromMC.printCounts();
	qcdBkgOnlyFromMC.printCounts();
	cout << "==============EWK Background Closure Test" << endl;
	//EWK Bkg only
	ewkBkgFromData.printCounts();
	ewkBkgFromMC.printCounts();
	ewkBkgOnlyFromMC.printCounts();
	cout << "===============Signal:" << lumiData << " 1/pb " << endl;

	for (int ct = 0; ct < (int) evtCountsSignalMCs.size(); ++ct) {
		double perc = 0;
		double percAll = 0;

		if (containsSubstr(evtCountsSignalMCs.at(ct).samplename, "Bkg est") && ct > 0) {
			double noEvtsBkgEst = evtCountsSignalMCs.at(ct).noEvts;
			double noEvtsSig = evtCountsSignalMCs.at(ct - 1).noEvts;
			perc = 100 * (noEvtsBkgEst / noEvtsSig);
			percAll = 100 * (noEvtsBkgEst / (noEvtsBkgEst + totBkgEst));

		}

		evtCountsSignalMCs.at(ct).printCounts();
		if (perc != 0) {
			cout << "Signal Contamination (bkgd pred signal/signal):" << perc << "%" << endl;
		}
		if (percAll != 0) {
			cout << "Signal Contamination (bkgd pred (signal)/bkgd pred (signal+bkg)):" << percAll << "%" << endl;
		}
	}

	cout << "===============event counts for AN:" << lumiData << " 1/pb " << endl;
	//string filename = "eventcounts.tex";
	system(("rm " + filename).c_str());
	//lumi information
	string lumiStr = "";
	lumiStr = lumiStr + "echo " + "'\\'" + "def" + "'\\'" + "lumiData" + "{" + (string) getStringFromDouble(lumiData / 1000, 2) + "} >> " + filename + ";";
	system((lumiStr).c_str());

	string uncertFit = "";
	uncertFit = uncertFit + "echo " + "'\\'" + "def" + "'\\'" + "UNCERTFITMC" + "{" + (string) getStringFromInt(uc_FitMC) + "} >> " + filename + ";";
	system((uncertFit).c_str());

	string uncertFitData = "";
	uncertFitData = uncertFitData + "echo " + "'\\'" + "def" + "'\\'" + "UNCERTFIT" + "{" + (string) getStringFromInt(uc_FitData) + "} >> " + filename + ";";
	system((uncertFitData).c_str());

	string uncertFitExtrapol = "";
	uncertFitExtrapol = uncertFitExtrapol + "echo " + "'\\'" + "def" + "'\\'" + "UNCERTEXTRAPOL" + "{" + (string) getStringFromInt(uc_FitExtrapol) + "} >> " + filename + ";";
	system((uncertFitExtrapol).c_str());

	string ewkFakeRateStr = "";
	ewkFakeRateStr = ewkFakeRateStr + "echo " + "'\\'" + "def" + "'\\'" + "EWKFAKERATE" + "{" + (string) getStringFromDouble(ewkFakeRate, 3) + "} >> " + filename + ";";
	system((ewkFakeRateStr).c_str());

	string ewkFakeRateSystStr = "";
	ewkFakeRateSystStr = ewkFakeRateSystStr + "echo " + "'\\'" + "def" + "'\\'" + "EWKFAKERATESYST" + "{" + (string) getStringFromDouble(ewkFakeRateSyst, 4) + "} >> " + filename + ";";
	system((ewkFakeRateSystStr).c_str());

	//
	for (int ct = 0; ct < (int) evtCountsBkgAllMCs.size(); ++ct) {
		evtCountsBkgAllMCs.at(ct).printCountsLatex(filename);

	}

	double percFit = uc_FitData / (uc_FitExtrapol + uc_FitData);

	double qcdRelUncertExtrapol = 100 * ((1 - percFit) * qcdTemp.systErrUp) / bkgEstTot.noEvts;
	double qcdRelUncertFit = 100 * ((percFit) * qcdTemp.systErrUp) / bkgEstTot.noEvts;
	for (int ct = 0; ct < (int) evtCountsBkgEst.size(); ++ct) {
		EventCounts currC = evtCountsBkgEst.at(ct);
		currC.printCountsLatex(filename);
		currC.printRelSystCountsLatex(bkgEstTot.noEvts, filename);

	}
	evtCtsdata.printCountsLatex(filename);
	bkgEstTot.printCountsLatex(filename);
	string qcdRelUncertFitStr = "";
	qcdRelUncertFitStr = qcdRelUncertFitStr + "echo " + "'\\'" + "def" + "'\\'" + jetSelApp + "QCDRELUNCERTFIT" + "{" + (string) getStringFromDouble(qcdRelUncertFit, 1) + "} >> " + filename + ";";
	system((qcdRelUncertFitStr).c_str());

	string qcdRelUncertExtrapolStr = "";
	qcdRelUncertExtrapolStr = qcdRelUncertExtrapolStr + "echo " + "'\\'" + "def" + "'\\'" + jetSelApp + "QCDRELUNCERTEXTRAPOL" + "{" + (string) getStringFromDouble(qcdRelUncertExtrapol, 1) + "} >> " + filename + ";";
	system((qcdRelUncertExtrapolStr).c_str());

	//QCD Bkg only
	qcdBkgFromData.printCountsLatex(filename);
	qcdBkgFromMC.printCountsLatex(filename);
	qcdBkgOnlyFromMC.printCountsLatex(filename);
	//EWK Bkg only
	ewkBkgFromData.printCountsLatex(filename);
	ewkBkgFromMC.printCountsLatex(filename);
	ewkBkgOnlyFromMC.printCountsLatex(filename);

}

#endif
