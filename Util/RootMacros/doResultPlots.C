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


void doResultPlot() {
  
  gROOT->ProcessLine(".L Util/RootMacros/compareHistosSusyPhotonJetAnalysis.C");
  gROOT->LoadMacro("Util/RootMacros/rootFileToPsandJpg.C");

  string dirname = "Plots_PhotonSusyAnalysis";

  cout << dirname << endl; 
  double lumiData              = 19800. ;
  double lumiDataBkgEstimation = 19800. ;
  double lumiMC                =   100. ;
  double uc_isrfsr             =     0.5; //isr/fsr uncertainty applied to plain MC contribution 0.5 = 50% 
	
  double uc_FitExtrapol =  5.;
  double uc_FitData     = 10.;
  double uc_FitMC       = 25.;

  double ewkFakeRate     = 0.015;
  double ewkFakeRateSyst = 0.001;

  cout << "colors" << endl;

  int colorFSRTT=kYellow;
  int colorFSRWZ=kOrange-2;
  int colorEWK=kTeal+5;
  int colorQCD=kCyan;
  int colorSignal1=kRed;
  int colorSignal2=kRed+0;
  int colorSignal3=kRed+1;
  int colorSignal4=kRed+1;
  int colorSignal5=kViolet;

  cout << "selections" << endl;
  string selectionDir = "select_1ph_2jets";
  std::cout << "SELECTIONDIR:" << selectionDir << std::endl;

  vector < string > histoNames;

  //select different decay channels 1ph/2ph/noJets/nobJets etc with MET>10,ph>20,jet>30 on gen level
  bool stackplots = true;

  //Data
  PlotConfig * data2012 = new PlotConfig( lumiData, false, getLegendTitle("Data"), "Data", selectionDir,
					  "Plots_PhotonSusyAnalysis/Merged_Data_V05w_PAT/mergedHistos.root",
					  1, 20, false );

  //SM backgrounds (data driven)
  PlotConfig * qcdAndPhotonJetData  = new PlotConfig( lumiData, true, "#gamma/QCD", "QCDPJData", selectionDir + "_FO_Corr",
						      "Plots_PhotonSusyAnalysis/Merged_Data_V05w_PAT/mergedHistos.root",
						      colorQCD, 20, stackplots );

  PlotConfig * ewkData              = new PlotConfig( lumiData, true, "e #rightarrow #gamma", "EWKData", selectionDir + "_PixelSeedCorr",
						      "Plots_PhotonSusyAnalysis/Merged_Data_V05w_PAT/mergedHistos.root",
						      colorEWK, 20, stackplots );

  
  //SM backgrounds (MC)
  PlotConfig * ttbar          = new PlotConfig( lumiMC, true, "t#bar{t} #gamma", "TTFSRMC", selectionDir,
						"Plots_PhotonSusyAnalysis/Merged_TTBar_V05w_PAT/mergedHistos.root",
						5, 20, stackplots );
    
  ttbar->MConlySyst = uc_isrfsr;
    
  PlotConfig * photonVjet     = new PlotConfig( lumiMC, true, "W/Z #gamma", "PhotonVMC", selectionDir,
						"Plots_PhotonSusyAnalysis/Merged_PhotonVJets_V05w_PAT/mergedHistos.root",
						colorFSRWZ, 20, stackplots );

  photonVjet->MConlySyst = uc_isrfsr;


  //Signal points (MC)
  PlotConfig * signalGGMA = new PlotConfig( lumiMC, true, getLegendTitle("signalGGMA"), "", selectionDir,
					    "Plots_PhotonSusyAnalysis/GGM_A_V05w/histoGGMA.root", 
					    colorSignal1, 20, false );

  string additionalTextForCanvas = getLegendTitle(selectionDir);

  cout << "doResultsPlots" << endl;

  vector<PlotConfig> configsAllStackedCorr;
  configsAllStackedCorr.push_back(*data2012);
  configsAllStackedCorr.push_back(*ewkData);
  configsAllStackedCorr.push_back(*qcdAndPhotonJetData);
  configsAllStackedCorr.push_back(*ttbar);
  configsAllStackedCorr.push_back(*photonVjet);
  configsAllStackedCorr.push_back(*signalGGMA);
  
  compareHistosSusyPhotonJetAnalysis( histoNames, lumiData, true, true, configsAllStackedCorr, 
				      "All_Stack_CorrData_" + selectionDir, 
				      dirname, additionalTextForCanvas, true, false, false );


  return;
}
