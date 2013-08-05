#if !defined(_CINT_) || defined(_MAKECINT_)

#include <TROOT.h>
#include <TMath.h>
#include <TFile.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TH1.h>
#include <TH1D.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TAxis.h>
#include <TPave.h>
#include <TLegend.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <Riostream.h>
#include <fstream>

#include <iomanip>
#include <time.h>
#include <stdio.h>

#include <TKey.h>
#include <TImage.h>
#include <TError.h>
#include <TObject.h>

#include <vector>
#include <utility>
/*
#include <TVirtualFitter.h>
#include "Util/RootMacros/rootFileToPsandJpg.C"
#include "Util/OwnUtil/src/HistoDrawUtil.h"
*/
#endif

using namespace std;


bool containsSubstr(string phrase, string sought) {

  int pos = phrase.find(sought); 
  if ((int) pos != (int) string::npos)
    return true;
  else
    return false;
}


void getBinEdgesRebin() {


  TH1F *photonPt = new TH1F("photonPt","pt",150,5.,1505.);
  TH1F *histo = photonPt;


  int lowestBinWithEntries = 0;

  for (int i = 1; i <= histo->GetNbinsX() + 1; i++) {
    if (histo->GetBinContent(i) > 0) {
      lowestBinWithEntries = i;
      break;
    }
  }


  double stepsizeFactor = 1.1;
  if (containsSubstr(histo->GetName(), "photon") || containsSubstr(histo->GetName(), "Photon")) 
    stepsizeFactor = 1.0;
  
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
	    stepsizeFactor = 1.3;//1.3;
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
      } else {
	currBinWidth = currBinWidth * stepsizeFactor;
      }

      currBinLowEdge = currBinLowEdge + currBinWidth;
      if (currBinLowEdge + (currBinWidth * stepsizeFactor) >= oldmaximum) {
	binEdges.push_back(oldmaximum);
	break;
      }

      binEdges.push_back(currBinLowEdge);
    }

    if (containsSubstr(histo->GetName(), "met") && !containsSubstr(histo->GetName(), "hoton") && !containsSubstr(histo->GetName(), "noJet") && !containsSubstr(histo->GetName(), "SumEt"))
      {
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
    if (false && containsSubstr(histo->GetName(), "Number of Jets")) {
      binEdges.clear();
      binEdges.push_back(0);
      binEdges.push_back(1);
      binEdges.push_back(2);
      binEdges.push_back(3);
      binEdges.push_back(4);
      binEdges.push_back(5);
      //binEdges.push_back(7);
      binEdges.push_back(9);
      //binEdges.push_back(13);
      //binEdges.push_back(16);
      binEdges.push_back(20);
      /*
      //cout << "No of Jets gets new binning..." << endl;
      binEdges.clear();
      binEdges.push_back(0);
      binEdges.push_back(1);
      binEdges.push_back(2);
      binEdges.push_back(3);
      binEdges.push_back(4);
      binEdges.push_back(5);
      binEdges.push_back(6);
      binEdges.push_back(7);
      binEdges.push_back(8);
      binEdges.push_back(9);
      binEdges.push_back(10);
      //binEdges.push_back(13);
      //binEdges.push_back(16);
      //			binEdges.push_back(20);
      */

    } else {
      for (int i = 1; i <= histo->GetNbinsX() + 1; i++) {	
	binEdges.push_back(histo->GetBinLowEdge(i));
      }
    }
  }


  for (int bin = 0; bin < (int) binEdges.size(); bin++) {
    cout << binEdges.at(bin) << endl;
  }


	return;
}
