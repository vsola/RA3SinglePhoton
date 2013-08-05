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


void doBkgEstimatePerDataset() {
  
  gROOT->ProcessLine(".L Util/RootMacros/compareHistosSusyPhotonJetAnalysis.C");
  gROOT->LoadMacro("Util/RootMacros/rootFileToPsandJpg.C");

  string dirname = "Plots_PhotonSusyAnalysis";

  double lumiData              = 19800. ;
  double lumiDataBkgEstimation = 19800. ;
  double lumiMC                =   100. ;
  double uc_isrfsr             =     0.5; //isr/fsr uncertainty applied to plain MC contribution 0.5 = 50% 
	
  double uc_FitExtrapol =  5.;
  double uc_FitData     = 10.;
  double uc_FitMC       = 25.;

  double ewkFakeRate     = 0.015;
  double ewkFakeRateSyst = 0.001;


  vector < string > datasets;  
  datasets.push_back("Plots_PhotonSusyAnalysis/Merged_QCD_PhotonJet_T07w_PAT/mergedHistos.root");
  //  datasets.push_back("Plots_PhotonSusyAnalysis/QCD_HT250To500_T07_PAT/mergedHistos.root");

  for (int d = 0; d < (int) datasets.size(); ++d) {

    string dataset = datasets[d];
    int pos1 = dataset.find("/");
    int pos2 = dataset.find_last_of("/");

    string datasetDir = dataset.substr(pos1 + 1, pos2 - pos1 - 1);
    std::cout << "DATASETDIR:" << datasetDir << std::endl;

    //select different selections
    bool stackplots = false;
      
    bool isData = false;
    bool isMC   = true;
    double normToLumi  = lumiDataBkgEstimation;
    double lumiDataset = lumiMC;
      
    if (containsSubstr(dataset, "PhotonHad")||containsSubstr(dataset, "Data")) {
      isData = true;
      isMC   = false;
	
      normToLumi  = lumiDataBkgEstimation;
      lumiDataset = lumiData;
    }//isData
      
    /*
      //=======================================================
      ///merge subirs to make comparison plots for diff samples
      std::cout << "DATASET for merge:" << dataset << std::endl;

      TFile * merge1 = new TFile(dataset.c_str(), "UPDATE");
      vector < string > subdirs;
      subdirs.clear();
      subdirs.push_back("select_1ph_3jets_FO_Corr");
      subdirs.push_back("select_1ph_3jets_PixelSeedCorr");
      mergeSubdirs( merge1, subdirs, "select_1ph_3jets_ComplPred" );

      TFile * merge2 = new TFile(dataset.c_str(), "UPDATE");
      vector < string > subdirsMC;
      subdirsMC.clear();
      subdirsMC.push_back("select_1ph_3jets_FO_CorrMC");
      subdirsMC.push_back("select_1ph_3jets_PixelSeedCorrMC");
      mergeSubdirs( merge2, subdirsMC, "select_1ph_3jets_ComplPredMC" );
      //=======================================================
    */
      
    //QCD prediction
    PlotConfig * ph1_jet2 = new PlotConfig( lumiDataset, true, "#gamma", "",
					    "select_1ph_2jets", dataset, 1, 20, stackplots );
      
    PlotConfig * ph1_jet2_FO = new PlotConfig( lumiDataset, true, "#gamma_{jet}", "", 
					       "select_1ph_2jets_FO", dataset, kRed + 1, 4, stackplots );

    PlotConfig * ph1_jet2_FO_Corr = new PlotConfig( lumiDataset, true, "Pred. (from #gamma_{jet})", "", 
						    "select_1ph_2jets_FO_Corr", dataset, 2, 22, stackplots );

    PlotConfig * ph1_jet2_FO_CorrMC = new PlotConfig( lumiDataset, true, "Pred. (from #gamma_{jet})", "",
						      "select_1ph_2jets_FO_CorrMC", dataset, 2, 22, stackplots );

    string additionalTextForCanvas = getLegendTitle(datasetDir);
    string sampleNameWithoutSpaces = removeSpaces( getSampleNameTech(datasetDir) );

    /* -- QCD Reweighting -- */
    vector<PlotConfig> configsJet2Dijet;
    configsJet2Dijet.push_back(*ph1_jet2);
    configsJet2Dijet.push_back(*ph1_jet2_FO);
    compareHistosSusyPhotonJetAnalysisFake( normToLumi, configsJet2Dijet,
					    "PlotsFOComparisonBeforeFitDijet" + sampleNameWithoutSpaces, dirname,
					    additionalTextForCanvas, isData, isMC, false, 2, false );

    if ( isData ) {
    vector<PlotConfig> configsJet1Dijet;
    configsJet1Dijet.push_back(*ph1_jet2);
    configsJet1Dijet.push_back(*ph1_jet2_FO_Corr);
    compareHistosSusyPhotonJetAnalysisFake( normToLumi, configsJet1Dijet, 
					    "PlotsFOComparisonDijet" + sampleNameWithoutSpaces, dirname,
					    additionalTextForCanvas, isData, isMC, true, 2 );
    } else {
    vector<PlotConfig> configsJet1DijetMC;
    configsJet1DijetMC.push_back(*ph1_jet2);
    configsJet1DijetMC.push_back(*ph1_jet2_FO_CorrMC);

    compareHistosSusyPhotonJetAnalysisFake( normToLumi, configsJet1DijetMC, 
					    "PlotsFOComparisonDijetMC" + sampleNameWithoutSpaces, dirname,
					    additionalTextForCanvas, isData, isMC, true, 2 );

    cout << "MCCCCCC!!!" << endl;
    }	
    /* -- QCD Reweighting -- */ 


    /*
    //EWK prediction
    //configs for Electron Veto Reverse applied (>=1 gen electron)
    PlotConfig * ph1_jet2_GenEleVetoRe = new PlotConfig( lumiDataset, true, "#gamma", "", 
							 "select_1ph_2jets_GenEleVetoRe", dataset, 1, 20, stackplots );

    PlotConfig * ph1_jet2_GenEleVetoRePixelSeed = new PlotConfig( lumiDataset, true, "#gamma_{e}", "",
								  "select_1ph_2jets_GenEleVetoRePixelSeed", dataset, 2, 20, stackplots );

    PlotConfig * ph1_jet2_GenEleVetoRePixelSeedCorr = new PlotConfig( lumiDataset, true, "Pred. (from #gamma_{e})", "",
								      "select_1ph_2jets_GenEleVetoRePixelSeedCorr", dataset, kRed + 1, 22, stackplots );

    */

  }//for dataset.size()

  return;
}
