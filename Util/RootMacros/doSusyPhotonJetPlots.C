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


void doSusyPhotonJetPlots() {
  
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
  //sqrt(0.0004^2+0.002²)
  double ewkFakeRate     = 0.015;
  double ewkFakeRateSyst = 0.001;


  // Analysis Options
  bool doEventYields   = false;
  bool doResultPlots   = true;
  bool doPileupWeights = false; 

  bool doBkgEstimatePerDataset          = false;
  bool doBkgEstimateCompBetweenDatasets = false;
  
  bool doMetCompPlots   = false;
  bool doTriggerStudies = false;


  vector<EventCounts> eventcountsPresel;
  vector<EventCounts> eventcounts;
  FitResultsQCDEst fitResData;
  FitResultsQCDEst fitResMC;

  
  /////////////////////////////////////////////////
  /////////////// DEFINE DATASETS /////////////////
  /////////////////////////////////////////////////
  
  vector < string > datasets;
  
  //  datasets.push_back("Plots_PhotonSusyAnalysis/Merged_Data_V24w_PAT/mergedHistos.root");

  datasets.push_back("Plots_PhotonSusyAnalysis/Merged_QCD_PhotonJet_T05rw_PAT/mergedHistos.root");
  //  datasets.push_back("Plots_PhotonSusyAnalysis/Merged_EWK_T05_PAT/mergedHistos.root");
  //  datasets.push_back("Plots_PhotonSusyAnalysis/WJetsToLNu_T05_PAT/mergedHistos.root");
  
  //  datasets.push_back("Plots_PhotonSusyAnalysis/TTBar_V05b_PAT/mergedHistos.root");
  //  datasets.push_back("Plots_PhotonSusyAnalysis/Merged_PhotonVJets_V05b_PAT/mergedHistos.root");
  
  //  datasets.push_back("Plots_PhotonSusyAnalysis/GGM_A_V20/histoGGMA.root");
  //  datasets.push_back("Plots_PhotonSusyAnalysis/GGM_B_V20/histoGGMB.root");

  //old files
  if (false) { 
    datasets.push_back("Plots_PhotonSusyAnalysis/Merged_Data_V20bc_PAT/mergedHistos.root");
    
    datasets.push_back("Plots_PhotonSusyAnalysis/Merged_QCD_PhotonJet_V20bv/mergedHistos.root");

    datasets.push_back("Plots_PhotonSusyAnalysis/TTBar_V20bt_PAT/mergedHistos.root");
    datasets.push_back("Plots_PhotonSusyAnalysis/WJets_V20bt_PAT/mergedHistos.root");
    datasets.push_back("Plots_PhotonSusyAnalysis/Merged_EWK_V20bt/mergedHistos.root");
    
    datasets.push_back("Plots_PhotonSusyAnalysis/Merged_EWKandQCD_V20bt/mergedHistos.root");
    
    datasets.push_back("Plots_PhotonSusyAnalysis/Merged_AllSM_V20bt/mergedHistos.root");
    datasets.push_back("Plots_PhotonSusyAnalysis/GGM_A_V20/histoGGMA.root");
    datasets.push_back("Plots_PhotonSusyAnalysis/GGM_B_V20/histoGGMB.root");
    datasets.push_back("Plots_PhotonSusyAnalysis/Merged_GGM_A_AllSM_V20bt/mergedHistos.root");
    datasets.push_back("Plots_PhotonSusyAnalysis/Merged_GGM_B_AllSM_V20bt/mergedHistos.root");
  }//false!!
  
  
  if (doMetCompPlots) {
    TFile * input = new TFile( ( dirname + "/" + "PhotonHadPromptReco_V11ag_PAT/mergedHistos.root" ).c_str(), "Read" );

    makeMetCompPlots(dirname, input);
  }//doMetCompPlots

  if (doTriggerStudies) {
    TFile * input = new TFile( ( dirname + "/" + "photonJetSelection_PhotonTrigger_V31_v5_SKIM/mergedHistos.root" ).c_str(), "Read" );

    makeTriggerEffPlots( dirname, input,
			 "select_All_HT_Nominator","ph50",
			 "select_All_HT_Denominator","ph70PFHT400",true,false);

    makeTriggerEffPlots( dirname, input,
			 "select_All_Photon_Nominator","ph50",
			 "select_All_Photon_Denominator","ph70PFHT400",false,true);
  }//doTriggerStudies

  //make plots for each dataset
  for (int d = 0; d < (int) datasets.size(); ++d) {

    if (doBkgEstimatePerDataset) {

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
      
      
      //QCD prediction
      PlotConfig * ph1_jet3 = new PlotConfig( lumiDataset, true, "#gamma", "",
					      "select_1ph_3jets", dataset, 1, 20, stackplots );
      
      PlotConfig * ph1_jet2 = new PlotConfig( lumiDataset, true, "#gamma", "",
					      "select_1ph_2jets", dataset, 1, 20, stackplots );
      
      PlotConfig * ph1_jet3_FO = new PlotConfig( lumiDataset, true, "#gamma_{jet}", "", 
						 "select_1ph_3jets_FO", dataset, kRed + 1, 4, stackplots );

      PlotConfig * ph1_jet3_FO_Corr = new PlotConfig( lumiDataset, true, "Pred. (from #gamma_{jet})", "", 
						      "select_1ph_3jets_FO_Corr", dataset, 2, 22, stackplots );

      PlotConfig * ph1_jet3_FO_CorrNoJet = new PlotConfig( lumiDataset, true, "Pred. (from #gamma_{jet})", "",
							   "select_1ph_3jets_FO_Corr2", dataset, 2, 22, stackplots );

      PlotConfig * ph1_jet3_FO_CorrMC = new PlotConfig( lumiDataset, true, "Pred. (from #gamma_{jet})", "",
							"select_1ph_3jets_FO_CorrMC", dataset, 2, 22, stackplots );

      PlotConfig * ph1_jet3_FO_CorrMCNoJet = new PlotConfig( lumiDataset, true, "Pred. (from #gamma_{jet})", "",
							     "select_1ph_3jets_FO_CorrMC2", dataset, 2, 22, stackplots );
      
      PlotConfig * ph1_jet2_FO = new PlotConfig( lumiDataset, true, "#gamma_{jet}", "", 
						 "select_1ph_2jets_FO", dataset, kRed + 1, 4, stackplots );

      PlotConfig * ph1_jet2_FO_Corr = new PlotConfig( lumiDataset, true, "Pred. (from #gamma_{jet})", "", 
						      "select_1ph_2jets_FO_Corr", dataset, 2, 22, stackplots );

      PlotConfig * ph1_jet2_FO_CorrMC = new PlotConfig( lumiDataset, true, "Pred. (from #gamma_{jet})", "",
      						"select_1ph_2jets_FO_CorrMC", dataset, 2, 22, stackplots );
      /*
      //EWK prediction - OLD
      PlotConfig * ph1_jet3_PixelSeed = new PlotConfig( lumiDataset, true, "#gamma_{e}", "", 
							"select_1ph_3jets_PixelSeed", dataset, 2, 20, stackplots );

      PlotConfig * ph1_jet3_PixelSeedCorr = new PlotConfig( lumiDataset, true, "Pred. (from #gamma_{e})", "",
							    "select_1ph_3jets_PixelSeedCorr", dataset, kRed + 1, 22, stackplots );

      //configs for Electron Veto applied
      PlotConfig * ph1_jet3_GenEleVeto = new PlotConfig( lumiDataset, true, "#gamma", "", 
							 "select_1ph_3jets_GenEleVeto", dataset, 1, 20, stackplots );

      PlotConfig * ph1_jet3_GenEleVetoPixelSeed = new PlotConfig( lumiDataset, true, "#gamma_{e}", "", 
								  "select_1ph_3jets_GenEleVetoPixelSeed", dataset, 2, 20, stackplots );

      PlotConfig * ph1_jet3_GenEleVetoPixelSeedCorr = new PlotConfig( lumiDataset, true, "Pred. (from #gamma_{e})", "",
								      "select_1ph_3jets_GenEleVetoPixelSeedCorr", dataset, kRed+ 1, 22, stackplots );
      
      //configs for Electron Veto Reverse applied (>=1 gen electron)
      PlotConfig * ph1_jet3_GenEleVetoRe = new PlotConfig( lumiDataset, true, "#gamma", "", 
							   "select_1ph_3jets_GenEleVetoRe", dataset, 1, 20, stackplots );

      PlotConfig * ph1_jet3_GenEleVetoRePixelSeed = new PlotConfig( lumiDataset, true, "#gamma_{e}", "",
								    "select_1ph_3jets_GenEleVetoRePixelSeed", dataset, 2, 20, stackplots );

      PlotConfig * ph1_jet3_GenEleVetoRePixelSeedCorr = new PlotConfig( lumiDataset, true, "Pred. (from #gamma_{e})", "",
									"select_1ph_3jets_GenEleVetoRePixelSeedCorr", dataset, kRed + 1, 22, stackplots );

      PlotConfig * ph1_jet3_GenEleVetoRePixelSeedMatchEle= new PlotConfig( lumiDataset, true, "#gamma_{e} (gen ele)", "",
									   "select_1ph_3jets_GenEleVetoRePixelSeedMatchEle", dataset, kRed + 1, 22, stackplots );

      PlotConfig * ph1_jet3_GenEleVetoRePixelSeedMatchJet= new PlotConfig( lumiDataset, true, "#gamma_{e} (gen jet)", "",
									   "select_1ph_3jets_GenEleVetoRePixelSeedMatchJet", dataset, kRed + 1, 22, stackplots );

      PlotConfig * ph1_jet3_GenEleVetoReMatchEle = new PlotConfig( lumiDataset, true, "#gamma (gen ele)", "",
								   "select_1ph_3jets_GenEleVetoReMatchEle", dataset, kRed + 1, 22, stackplots );

      PlotConfig * ph1_jet3_GenEleVetoReMatchJet = new PlotConfig( lumiDataset, true, "#gamma (gen jet)", "",
								   "select_1ph_3jets_GenEleVetoReMatchJet", dataset, kRed + 1, 22, stackplots );

      ///2jet EWK
      PlotConfig * ph1_jet2_PixelSeed = new PlotConfig( lumiDataset, true, "#gamma_{e}", "", 
							"select_1ph_2jets_PixelSeed", dataset, 2, 20, stackplots);

      PlotConfig * ph1_jet2_PixelSeedCorr = new PlotConfig( lumiDataset, true, "Pred. (from #gamma_{e})", "",
							    "select_1ph_2jets_PixelSeedCorr", dataset, kRed + 1, 22, stackplots );
      
      //configs for Electron Veto applied
      PlotConfig * ph1_jet2_GenEleVeto = new PlotConfig( lumiDataset, true, "#gamma", "", 
							"select_1ph_2jets_GenEleVeto", dataset, 1, 20, stackplots );

      PlotConfig * ph1_jet2_GenEleVetoPixelSeed = new PlotConfig( lumiDataset, true, "#gamma_{e}", "",
								 "select_1ph_2jets_GenEleVetoPixelSeed", dataset, 2, 20,stackplots );

      PlotConfig * ph1_jet2_GenEleVetoPixelSeedCorr = new PlotConfig( lumiDataset, true, "Pred. (from #gamma_{e})", "",
								      "select_1ph_2jets_GenEleVetoPixelSeedCorr", dataset, kRed + 1, 22, stackplots );
      //total prediction
      PlotConfig * ph1_jet3_ComplPred = new PlotConfig( lumiDataset, true, "Prediction (e #rightarrow #gamma+#gamma/QCD)", "", 
							"select_1ph_3jets_ComplPred", dataset, 9, 22, stackplots );

      PlotConfig * ph1_jet3_ComplPredMC = new PlotConfig( lumiDataset, true, "Prediction (e #rightarrow #gamma+#gamma/QCD)", "",
							  "select_1ph_3jets_ComplPredMC", dataset, 9, 20, stackplots );

      */      


      //EWK prediction
      //configs for Electron Veto Reverse applied (>=1 gen electron)
      //VS!!!
      PlotConfig * ph1_jet2_GenEleVetoRe = new PlotConfig( lumiDataset, true, "#gamma", "", 
							   "select_1ph_2jets_GenEleVetoRe", dataset, 1, 20, stackplots );

      PlotConfig * ph1_jet2_GenEleVetoRePixelSeed = new PlotConfig( lumiDataset, true, "#gamma_{e}", "",
								    "select_1ph_2jets_GenEleVetoRePixelSeed", dataset, 2, 20, stackplots );

      PlotConfig * ph1_jet2_GenEleVetoRePixelSeedCorr = new PlotConfig( lumiDataset, true, "Pred. (from #gamma_{e})", "",
									"select_1ph_2jets_GenEleVetoRePixelSeedCorr", dataset, kRed + 1, 22, stackplots );



      string additionalTextForCanvas = getLegendTitle(datasetDir);
      string sampleNameWithoutSpaces = removeSpaces( getSampleNameTech(datasetDir) );


      /* -- QCD Reweighting -- */
      //VS!!!
      vector<PlotConfig> configsJet1;
      configsJet1.push_back(*ph1_jet3);
      configsJet1.push_back(*ph1_jet3_FO_Corr);

      compareHistosSusyPhotonJetAnalysisFake( normToLumi, configsJet1, "PlotsFOComparison" + sampleNameWithoutSpaces, dirname,
					      additionalTextForCanvas, isData, isMC, true, 3 );

      vector<PlotConfig> configsJet1MC;
      configsJet1MC.push_back(*ph1_jet3);
      configsJet1MC.push_back(*ph1_jet3_FO_CorrMC);
      //configsJet1MC.push_back(*ph1_jet3GenPhoton);

      compareHistosSusyPhotonJetAnalysisFake( normToLumi, configsJet1MC, "PlotsFOComparisonMC" + sampleNameWithoutSpaces, dirname,
					      additionalTextForCanvas, isData, isMC, true, 3 );

      //additional noJet correction
      vector<PlotConfig> configsJet1Nojet;
      configsJet1Nojet.push_back(*ph1_jet3);
      //configsJet1.push_back(*ph1_jet3_FO);
      configsJet1Nojet.push_back(*ph1_jet3_FO_CorrNoJet);
      //configsJet1.push_back(*ph1_jet3GenPhoton);

      compareHistosSusyPhotonJetAnalysisFake( normToLumi, configsJet1Nojet, "PlotsFOComparisonCorr2" + sampleNameWithoutSpaces, dirname,
					      additionalTextForCanvas, isData, isMC, true, 3 );
      
      vector<PlotConfig> configsJet2;
      configsJet2.push_back(*ph1_jet3);
      //configsJet2.push_back(*ph1_jet3_Fake);
      //configsJet2.push_back(*ph1_jet3_Fake_Corr);
      configsJet2.push_back(*ph1_jet3_FO);

      compareHistosSusyPhotonJetAnalysisFake( normToLumi, configsJet2, "PlotsFOComparisonBeforeFit" + sampleNameWithoutSpaces,
					      dirname, additionalTextForCanvas, isData, isMC, false, 3, false );
      
      ///////////////////2Jet estimation///////////////////////////////////////
      vector<PlotConfig> configsJet1Dijet;
      configsJet1Dijet.push_back(*ph1_jet2);
      configsJet1Dijet.push_back(*ph1_jet2_FO_Corr);

      compareHistosSusyPhotonJetAnalysisFake( normToLumi, configsJet1Dijet, "PlotsFOComparisonDijet" + sampleNameWithoutSpaces, dirname,
					      additionalTextForCanvas, isData, isMC, true, 2 );
      
      vector<PlotConfig> configsJet1DijetMC;
      configsJet1DijetMC.push_back(*ph1_jet2);
      configsJet1DijetMC.push_back(*ph1_jet2_FO_CorrMC);

      compareHistosSusyPhotonJetAnalysisFake( normToLumi, configsJet1DijetMC, "PlotsFOComparisonDijetMC" + sampleNameWithoutSpaces, dirname,
					      additionalTextForCanvas, isData, isMC, true, 2 );
			
      vector<PlotConfig> configsJet2Dijet;
      configsJet2Dijet.push_back(*ph1_jet2);
      configsJet2Dijet.push_back(*ph1_jet2_FO);

      compareHistosSusyPhotonJetAnalysisFake( normToLumi, configsJet2Dijet, "PlotsFOComparisonBeforeFitDijet" + sampleNameWithoutSpaces, dirname,
					      additionalTextForCanvas, isData, isMC, false, 2, false );

      /* -- QCD Reweighting -- */ 
      //VS!!!


      /*
      vector<PlotConfig> configsJet5;
      configsJet5.push_back(*ph1_jet3);
      configsJet5.push_back(*ph1_jet3_PixelSeedCorr);
      configsJet5.push_back(*ph1_jet3_PixelSeed);

      compareHistosSusyPhotonJetAnalysisFake( normToLumi, configsJet5, "PlotsPixelSeedComparison" + sampleNameWithoutSpaces, dirname, 
					      additionalTextForCanvas, isData, isMC, false, 3 );

      vector<PlotConfig> configsJet5Dijet;
      configsJet5Dijet.push_back(*ph1_jet2);
      configsJet5Dijet.push_back(*ph1_jet2_PixelSeedCorr);
      configsJet5Dijet.push_back(*ph1_jet2_PixelSeed);

      compareHistosSusyPhotonJetAnalysisFake( normToLumi, configsJet5Dijet, "PlotsPixelSeedComparisonDijet" + sampleNameWithoutSpaces, dirname, 
					      additionalTextForCanvas, isData, isMC, false, 2 );
      */	

      if (isMC) {

	/*
	//VS!!!
	vector<PlotConfig> configsJet6MCGen2j;
	configsJet6MCGen2j.push_back(*ph1_jet2_GenEleVetoRe);
	configsJet6MCGen2j.push_back(*ph1_jet2_GenEleVetoRePixelSeedCorr);

	compareHistosSusyPhotonJetAnalysisFake( normToLumi, configsJet6MCGen2j, "PlotsPixelSeedComparisonDijetMCGenEleVetoRe" + sampleNameWithoutSpaces, dirname,
						additionalTextForCanvas, isData, isMC, true, 2 );
        //VS!!!
	*/

	/*
	vector<PlotConfig> configsJet6MCGen;
	configsJet6MCGen.push_back(*ph1_jet3_GenEleVetoRe);
	configsJet6MCGen.push_back(*ph1_jet3_GenEleVetoRePixelSeedCorr);

	compareHistosSusyPhotonJetAnalysisFake( normToLumi, configsJet6MCGen, "PlotsPixelSeedComparisonMCGenEleVetoRe" + sampleNameWithoutSpaces, dirname,
						additionalTextForCanvas, isData, isMC, true, 3 );

	vector<PlotConfig> configsJetMCGenEleEventMatchEle;
	configsJetMCGenEleEventMatchEle.push_back(*ph1_jet3_GenEleVetoRePixelSeedMatchEle);
	configsJetMCGenEleEventMatchEle.push_back(*ph1_jet3_GenEleVetoReMatchEle);

	vector < PlotConfig > configsJetMCGenEleJet;
	configsJetMCGenEleJet.push_back(*ph1_jet3_GenEleVetoRePixelSeed);
	configsJetMCGenEleJet.push_back(*ph1_jet3_GenEleVetoRePixelSeedMatchJet);

	vector < PlotConfig > configsJetMCGenEleEle;
	configsJetMCGenEleEle.push_back(*ph1_jet3_GenEleVetoRePixelSeed);
	configsJetMCGenEleEle.push_back(*ph1_jet3_GenEleVetoRePixelSeedMatchEle);
	*/
      }//isMC
      
    }//doBkgEstimatePerDataset
  }//for dataset.size()


  if (doBkgEstimateCompBetweenDatasets) {

    TFile * input1 = new TFile( ( dirname + "/" + "PlotsFOComparisonBeforeFitQCDandPhotonJet" + "_plot.root" ).c_str(), "Read" );
    TFile * input2 = new TFile( ( dirname + "/" + "PlotsFOComparisonBeforeFitAllSM"           + "_plot.root" ).c_str(), "Read" );

    compareHistosSusyPhotonJetAnalysisFakeBetweenDatasamples( input1, input2, "PlotsCompSMContamination", dirname, "#gamma/QCD",
							      "All SM", false, true, lumiData, 3 );
    
    //2jet 
    TFile * input1_2j = new TFile( (dirname + "/" + "PlotsFOComparisonBeforeFitDijetQCDandPhotonJet" + "_plot.root" ).c_str(), "Read" );
    TFile * input2_2j = new TFile( (dirname + "/" + "PlotsFOComparisonBeforeFitDijetAllSM"           + "_plot.root" ).c_str(), "Read" );

    compareHistosSusyPhotonJetAnalysisFakeBetweenDatasamples( input1_2j, input2_2j, "PlotsCompSMContaminationDijet", dirname, "#gamma/QCD",
							      "All SM", false, true, lumiData, 2 );
		
    TFile * input1AllSM      = new TFile( (dirname + "/" + "PlotsFOComparisonBeforeFitAllSM" + "_plot.root" ).c_str(), "Read" );
    TFile * input2SignalCont = new TFile( (dirname + "/" + "PlotsFOComparisonBeforeFitGGMBandAllSM" + "_plot.root" ).c_str(), "Read" );

    compareHistosSusyPhotonJetAnalysisFakeBetweenDatasamples( input1AllSM, input2SignalCont, "PlotsCompSignalBContamination", dirname,
							      "All SM", "All SM + GGM Signal", false, true, lumiData, 3 );

    TFile * input2SignalContA = new TFile( ( dirname + "/" + "PlotsFOComparisonBeforeFitGGMAandAllSM" + "_plot.root").c_str() , "Read" );
    
    compareHistosSusyPhotonJetAnalysisFakeBetweenDatasamples( input1AllSM, input2SignalContA, "PlotsCompSignalAContamination", dirname,
							      "All SM", "All SM + Signal", false, true, lumiData, 3 );

    TFile * input1AllSM_2j       = new TFile( (dirname + "/" + "PlotsFOComparisonBeforeFitDijetAllSM"        + "_plot.root" ).c_str(), "Read" );
    TFile * input2SignalContA_2j = new TFile( (dirname + "/" + "PlotsFOComparisonBeforeFitDijetGGMAandAllSM" + "_plot.root" ).c_str(), "Read" );

    compareHistosSusyPhotonJetAnalysisFakeBetweenDatasamples( input1AllSM_2j, input2SignalContA_2j, "PlotsCompSignalAContaminationDijet", dirname,
							      "All SM", "All SM + Signal", false, true, lumiData, 2 );

    TFile * input1NoJet = new TFile( (dirname + "/" + "PlotsFOComparisonBeforeFitDijetData" + "_plot.root" ).c_str(), "Read" );
    TFile * input2NoJet = new TFile( (dirname + "/" + "PlotsFOComparisonDijetData"          + "_plot.root" ).c_str(), "Read" );

    compareHistosSusyPhotonJetAnalysisFakeBetweenDatasamplesNoJet( input1NoJet, input2NoJet, "PlotsCompNoJets", dirname,
								   "Before Reweighting", "After Reweighting", false, true, lumiData, 2 );

  }//doBkgEstimateCompBetweenDatasets

  cout << "selections" << endl;

  vector < string > selections;
  selections.push_back("select_1ph_2jets");
  selections.push_back("select_1ph_2jets_1b");
  //  selections.push_back("select_1ph_3jets");

  //make plots for each selection
  /*
  int colorFSRTT   = kAzure + 3;
  int colorFSRWZ   = kAzure + 2;
  int colorEWK     = kAzure + 9;
  int colorQCD     = kAzure + 10;
  int colorSignal1 = kRed + 0;
  int colorSignal2 = kRed + 0;
  int colorSignal3 = kRed + 1;
  int colorSignal4 = kRed + 1;
  int colorSignal5 = kRed + 3;
  */
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

  for (int s = 0; s < (int) selections.size(); ++s) {

    string selection = selections[s];
    string selectionDir = selection;
    std::cout << "SELECTIONDIR:" << selectionDir << std::endl;

    vector < string > histoNames;

    //select different decay channels 1ph/2ph/noJets/nobJets etc with MET>10,ph>20,jet>30 on gen level

    bool stackplots = true;

    //MC backgrounds (estimated with data driven methods, only needed for MC only comparison)
    PlotConfig * qcdAndPhotonJet = new PlotConfig( lumiMC, true, getLegendTitle("QCD"), "QCDPJMC", selectionDir,
						   "Plots_PhotonSusyAnalysis/Merged_QCD_PhotonJet_V22w_PAT/mergedHistos.root",
						   4, 20, stackplots );

    PlotConfig * qcd             = new PlotConfig( lumiMC, true, getLegendTitle("QCD"), "QCDMC", selectionDir,
						   "Plots_PhotonSusyAnalysis/Merged_QCD_bins_V20bv/mergedHistos.root",
						   4, 20, stackplots );
   
    PlotConfig * phJet      = new PlotConfig( lumiMC, true, getLegendTitle("PhotonJet"), "PJMC", selectionDir,
						   "Plots_PhotonSusyAnalysis/GJets_V22w_PAT/mergedHistos.root",
						   3, 20, stackplots );

    PlotConfig * ttbar           = new PlotConfig( lumiMC, true, "t#bar{t} #gamma", "TTFSRMC", selectionDir,
						   "Plots_PhotonSusyAnalysis/TTBar_V05w_PAT/mergedHistos.root",
						   5, 20, stackplots );
    
    PlotConfig * wJets           = new PlotConfig( lumiMC, true, getLegendTitle("WJets"), "WJMC", selectionDir,
						   "Plots_PhotonSusyAnalysis/WJets_V22i_PAT/mergedHistos.root",
						   7, 20, stackplots );
      
    PlotConfig * ewkMConly       = new PlotConfig( lumiMC, true, getLegendTitle("ewk mc only"), "EWKMC", selectionDir + "_GenEleVetoRe",
						   "Plots_PhotonSusyAnalysis/Merged_EWK_V22i/mergedHistos.root",
						   7, 20, stackplots );
		

    //SM backgrounds (data driven)
    PlotConfig * qcdAndPhotonJetCorrData  = new PlotConfig( lumiData, true, "#gamma/QCD", "QCDPJData", selectionDir + "_FO_Corr",
							    //"j #rightarrow #gamma & #gamma-jet  (from data)",
							    "Plots_PhotonSusyAnalysis/Merged_Data_V05w_PAT/mergedHistos.root",
							    colorQCD, 20, stackplots );

    PlotConfig * qcdAndPhotonJetCorr2Data = new PlotConfig( lumiData, true, "#gamma/QCD", "QCDPJData", selectionDir + "_FO_Corr2",
							    //"j #rightarrow #gamma & #gamma-jet  (from data)",
							    "Plots_PhotonSusyAnalysis/Merged_Data_V22w_PAT/mergedHistos.root",
							    colorQCD, 20, stackplots );

    PlotConfig * ewkData                  = new PlotConfig( lumiData, true, "e #rightarrow #gamma", "EWKData", selectionDir + "_PixelSeedCorr",
							    "Plots_PhotonSusyAnalysis/Merged_Data_V05w_PAT/mergedHistos.root",
							    colorEWK, 20, stackplots );

    //SM backgrounds (MC driven - MC closure )
    PlotConfig * qcdAndPhotonJetCorrMC = new PlotConfig( lumiMC, true, "#gamma/QCD", "QCDPJMCD", selectionDir + "_FO_CorrMC",
							 //"j #rightarrow #gamma & #gamma-jet",
							 "Plots_PhotonSusyAnalysis/Merged_QCD_PhotonJet_V22w_PAT/mergedHistos.root",
							 3, 20, stackplots );
		
    PlotConfig * ewkMC                 = new PlotConfig( lumiMC, true, "e #rightarrow #gamma (MC driven)", "EWKMCD", selectionDir + "_GenEleVetoRePixelSeedCorr",
							 "Plots_PhotonSusyAnalysis/Merged_EWK_V22i_PAT/mergedHistos.root",
							 5, 20, stackplots );


    //SM backgrounds (MC)
    PlotConfig * ttbarGenPhoton = new PlotConfig( lumiMC, true, "t#bar{t} #gamma", "TTFSRMC", selectionDir + "_GenEleVeto",
						  "Plots_PhotonSusyAnalysis/TTBar_V22i_PAT/mergedHistos.root",
						  colorFSRTT, 20, stackplots );
    ttbarGenPhoton->MConlySyst  = uc_isrfsr;
    
    PlotConfig * zinv           = new PlotConfig( lumiMC, true, getLegendTitle("ZInv"), "ZINVMC", selectionDir,
						  "Plots_PhotonSusyAnalysis/ZInv_V17ft_PAT/mergedHistos.root", 
						  8, 20, stackplots);
    
    PlotConfig * photonVjet     = new PlotConfig( lumiMC, true, "W/Z #gamma", "PhotonVMC", selectionDir,
						  "Plots_PhotonSusyAnalysis/Merged_PhotonVJets_V05w_PAT/mergedHistos.root",
						  colorFSRWZ, 20, stackplots );

    PlotConfig * photonVjetGenPhoton = new PlotConfig( lumiMC, true, "W/Z #gamma ", "PhotonVMC", selectionDir + "_GenEleVeto",
						       "Plots_PhotonSusyAnalysis/Merged_PhotonVJets_V22i_PAT/mergedHistos.root",
						       colorFSRWZ, 20, stackplots );
    photonVjetGenPhoton->MConlySyst  = uc_isrfsr;

    //Signal points (MC)
    //    PlotConfig * signalGGMA = new PlotConfig( );
    PlotConfig * signalGGMB = new PlotConfig( );
    
    PlotConfig * signalGGMA = new PlotConfig( lumiMC, true, getLegendTitle("signalGGMA"), "", selectionDir,
					      "Plots_PhotonSusyAnalysis/GGM_A_V05w/histoGGMA.root", 
					      colorSignal1, 20, false );
    /*
    PlotConfig * signalGGMB = new PlotConfig( lumiMC, true, getLegendTitle("signalGGMB"), "", selectionDir,
					      "Plots_PhotonSusyAnalysis/GGM_B_V20/histoGGMB.root",
					      colorSignal5, 20, false );
    */

    //Data
    PlotConfig * data2011 = new PlotConfig( lumiData, false, getLegendTitle("Data"), "Data", selectionDir,
					    "Plots_PhotonSusyAnalysis/Merged_Data_V05w_PAT/mergedHistos.root",
					    1, 20, false );

    string additionalTextForCanvas = getLegendTitle(selectionDir);

    if (doResultPlots) {
      
      cout << "doResultsPlots" << endl;

      /*
      vector<PlotConfig> configsAllStacked;
      configsAllStacked.push_back(*data2011);
      configsAllStacked.push_back(*ttbar);
      configsAllStacked.push_back(*photonVjet);
      //configsAllStacked.push_back(*wJets);
      //configsAllStacked.push_back(*dyjettoll);
      //configsAllStacked.push_back(*zinv);
      //configsAllStacked.push_back(*qcd);
      //configsAllStacked.push_back(*phJet);

      // Signal MC
      //      configsAllStacked.push_back(*signalGGMA);
      //      configsAllStacked.push_back(*signalGGMB);

      compareHistosSusyPhotonJetAnalysis( histoNames, lumiData, true, true, configsAllStacked, "All_Stack_Data_" + selectionDir,
					  dirname, additionalTextForCanvas, true );
      */

      vector<PlotConfig> configsAllStackedCorr;
      configsAllStackedCorr.push_back(*data2011);
      configsAllStackedCorr.push_back(*ttbar);
      configsAllStackedCorr.push_back(*photonVjet);
      //      configsAllStackedCorr.push_back(*ttbarGenPhoton);
      //      configsAllStackedCorr.push_back(*photonVjetGenPhoton);
      //configsAllStackedCorr.push_back(*zinv);
      //configsAllStackedCorr.push_back(*ttbarGenPhoton);
      configsAllStackedCorr.push_back(*ewkData);
      configsAllStackedCorr.push_back(*qcdAndPhotonJetCorrData);
      configsAllStackedCorr.push_back(*signalGGMA);
      //      configsAllStackedCorr.push_back(*signalGGMB);

      compareHistosSusyPhotonJetAnalysis( histoNames, lumiData, true, true, configsAllStackedCorr, "All_Stack_CorrData_" + selectionDir, 
					  dirname, additionalTextForCanvas, true, false, false );

      /*
      vector<PlotConfig> configsAllStackedCorr2;
      configsAllStackedCorr2.push_back(*data2011);
      configsAllStackedCorr2.push_back(*ttbarGenPhoton);
      configsAllStackedCorr2.push_back(*photonVjetGenPhoton);
      //configsAllStackedCorr.push_back(*zinv);
      //configsAllStackedCorr.push_back(*ttbarGenPhoton);
      configsAllStackedCorr2.push_back(*ewkData);
      configsAllStackedCorr2.push_back(*qcdAndPhotonJetCorr2Data);
      configsAllStackedCorr2.push_back(*signalGGMA);
      configsAllStackedCorr2.push_back(*signalGGMB);

      compareHistosSusyPhotonJetAnalysis( histoNames, lumiData, true, true, configsAllStackedCorr2, "All_Stack_Corr2Data_" + selectionDir, 
					  dirname, additionalTextForCanvas, true, false, false );
      */

    }//doResultPlots

    //make plots checking relative EWK/Signal Contamination
    if (doBkgEstimateCompBetweenDatasets) {
      
      PlotConfig * AllSMMC_EWKContPred        = new PlotConfig( lumiMC, true, "Pred. (All SM)", "", selectionDir + "_FO_Corr",
								"Plots_PhotonSusyAnalysis/Merged_EWKandQCD_V20bt/mergedHistos.root",
								2, 20, false, 2, 3004 );

      PlotConfig * AllSMMC_EWKCont            = new PlotConfig( lumiMC, true, "#gamma (All SM)", "", selectionDir + "",
								"Plots_PhotonSusyAnalysis/Merged_EWKandQCD_V20bt/mergedHistos.root",
								1, 20, false );

      PlotConfig * EWKMC_EWKContPred          = new PlotConfig( lumiMC, true, "Pred. (t#bar{t}/W)", "", selectionDir + "_FO_Corr",
								"Plots_PhotonSusyAnalysis/Merged_EWK_V20bt/mergedHistos.root",
								4, 20, false, 4, 3005 );

      PlotConfig * AllSMPlusSigB_SigBContPred = new PlotConfig( lumiMC, true, "Pred. (All SM + Signal)", "", selectionDir + "_FO_Corr",
								"Plots_PhotonSusyAnalysis/Merged_GGM_A_AllSM_V20bt/mergedHistos.root",
								2, 20, false, 2, 3004 );

      PlotConfig * AllSMPlusSigB_SigBCont     = new PlotConfig( lumiMC, true, "#gamma (All SM + Signal)", "", selectionDir + "",
								"Plots_PhotonSusyAnalysis/Merged_GGM_A_AllSM_V20bt/mergedHistos.root",
								1, 20, false );
      
      PlotConfig * SigB_SigBContPred          = new PlotConfig( lumiMC, true, "Pred. (Signal)", "", selectionDir + "_FO_Corr",
								"Plots_PhotonSusyAnalysis/GGM_A_V20/histoGGMA.root", 
								4, 20, false, 4, 3005 );

      vector<PlotConfig> configsEWKContamination;
      configsEWKContamination.push_back(*AllSMMC_EWKCont);
      configsEWKContamination.push_back(*AllSMMC_EWKContPred);
      configsEWKContamination.push_back(*EWKMC_EWKContPred);
      
      vector<PlotConfig> configsSignalBContamination;
      configsSignalBContamination.push_back(*AllSMPlusSigB_SigBCont);
      configsSignalBContamination.push_back(*AllSMPlusSigB_SigBContPred);
      configsSignalBContamination.push_back(*SigB_SigBContPred);

      histoNames.clear();
      histoNames.push_back("PreselCut_metPt");
      histoNames.push_back("metPt");

      compareHistosSusyPhotonJetAnalysis( histoNames, lumiData, false, true, configsEWKContamination, "EWKContamination_"+ selectionDir, dirname, 
					  additionalTextForCanvas, false, false, false);
      
      compareHistosSusyPhotonJetAnalysis(histoNames, lumiData, false, true, configsSignalBContamination, "SignalContamination_"+ selectionDir, dirname, 
					 additionalTextForCanvas, false, false, false);
    }//doBkgEstimateCompBetweenDatasets


    //compare QCD/Photon+Jet MC shape
    if (doBkgEstimateCompBetweenDatasets) {

      PlotConfig * QCDMC       = new PlotConfig( lumiMC, true, "QCD", "", selectionDir + "_FO_Corr",
						 "Plots_PhotonSusyAnalysis/Merged_QCD_bins_V20bv/mergedHistos.root",
						 2, 20, false);

      PlotConfig * PHOTONJETMC = new PlotConfig( lumiMC, true, "Photon+Jet", "", selectionDir + "",
						 "Plots_PhotonSusyAnalysis/PhotonJet_V20bv_PAT/mergedHistos.root",
						 1, 20, false );

      vector<PlotConfig> configsQCDPhotonJetComp;
      configsQCDPhotonJetComp.push_back(*QCDMC);
      configsQCDPhotonJetComp.push_back(*PHOTONJETMC);
	
      histoNames.clear();
      histoNames.push_back("PreselCut_metPt");
      histoNames.push_back("PreselCut_mht");
      //histoNames.push_back("metPt");

      compareHistosSusyPhotonJetAnalysis( histoNames, lumiData, false, true, configsQCDPhotonJetComp, "QCD_PhotonJet_Comparison_"+ selectionDir, dirname, 
					  additionalTextForCanvas, false, true, false );
    }//doBkgEstimateCompBetweenDatasets


    if (doEventYields) {

      vector<PlotConfig> configsForEventCountBkgEst;
      configsForEventCountBkgEst.push_back(*ewkData);
      configsForEventCountBkgEst.push_back(*qcdAndPhotonJetCorrData);
      configsForEventCountBkgEst.push_back(*photonVjetGenPhoton);
      configsForEventCountBkgEst.push_back(*ttbarGenPhoton);

      vector<PlotConfig> configsForEventCountBkgEstCorr2;
      configsForEventCountBkgEstCorr2.push_back(*ewkData);
      configsForEventCountBkgEstCorr2.push_back(*qcdAndPhotonJetCorr2Data);
      configsForEventCountBkgEstCorr2.push_back(*photonVjetGenPhoton);
      configsForEventCountBkgEstCorr2.push_back(*ttbarGenPhoton);

      vector<PlotConfig> configsForEventCountBKGAllMCs;

      //EWK
      configsForEventCountBKGAllMCs.push_back(*wJets);
      configsForEventCountBKGAllMCs.push_back(*ttbar);
      //configsForEventCountBKGAllMCs.push_back(*dyjettoll);
      //configsForEventCountBKGAllMCs.push_back(*zinv);

      //Others
      //configsForEventCountBKGAllMCs.push_back(*wgtolnug);
      //configsForEventCountBKGAllMCs.push_back(*zgtollg);
      configsForEventCountBKGAllMCs.push_back(*photonVjet);

      //QCD
      configsForEventCountBKGAllMCs.push_back(*qcd);
      configsForEventCountBKGAllMCs.push_back(*phJet);

      vector<PlotConfig> configsForEventCountSignalMCs;

      //Signal
      PlotConfig * signalGGMABkgEst = new PlotConfig( lumiMC, true, "Bkg est", "", selectionDir + "_ComplPredMC",
						      "Plots_PhotonSusyAnalysis/GGM_A_V20/histoGGMA.root", 
						      2, 20, false );

      PlotConfig * signalGGMBBkgEst = new PlotConfig( lumiMC, true, "Bkg est", "", selectionDir + "_ComplPredMC",
						      "Plots_PhotonSusyAnalysis/GGM_B_V20/histoGGMB.root",
						      kPink - 6, 20, false );
			
      configsForEventCountSignalMCs.push_back(*signalGGMA);
      configsForEventCountSignalMCs.push_back(*signalGGMABkgEst);
      configsForEventCountSignalMCs.push_back(*signalGGMB);
      configsForEventCountSignalMCs.push_back(*signalGGMBBkgEst);
			
      //print limits for 200 GeV Cut
      string filename = "eventcounts200_"+selectionDir+".tex";
      double metCut   = 201;
      string prefix   = "";

      if( containsSubstr(selectionDir,"2j") )
	prefix="jTWO";
	
      calculateEventCounts( data2011, data2011, lumiData, lumiData,
			    configsForEventCountBkgEst,configsForEventCountBkgEstCorr2, qcdAndPhotonJetCorrData,
			    qcdAndPhotonJetCorrMC, qcdAndPhotonJet, ewkData, ewkMC,
			    ewkMConly, configsForEventCountSignalMCs,
			    configsForEventCountBKGAllMCs, filename, metCut, uc_FitMC,
			    uc_FitData, uc_FitExtrapol, ewkFakeRate, ewkFakeRateSyst,prefix );

      //print limits for 350 GeV Cut
      filename = "eventcounts350_"+selectionDir+".tex";
      metCut   = 351;
      calculateEventCounts( data2011, data2011, lumiData, lumiData,
			    configsForEventCountBkgEst,configsForEventCountBkgEstCorr2, qcdAndPhotonJetCorrData,
			    qcdAndPhotonJetCorrMC, qcdAndPhotonJet, ewkData, ewkMC,
			    ewkMConly, configsForEventCountSignalMCs,
			    configsForEventCountBKGAllMCs, filename, metCut, uc_FitMC,
			    uc_FitData, uc_FitExtrapol, ewkFakeRate, ewkFakeRateSyst,prefix);

      //print limits for 100 GeV Cut
      filename = "eventcounts100_"+selectionDir+".tex";
      metCut   = 101;
      calculateEventCounts( data2011, data2011, lumiData, lumiData,
			    configsForEventCountBkgEst, configsForEventCountBkgEstCorr2,qcdAndPhotonJetCorrData,
			    qcdAndPhotonJetCorrMC, qcdAndPhotonJet, ewkData, ewkMC,
			    ewkMConly, configsForEventCountSignalMCs,
			    configsForEventCountBKGAllMCs, filename, metCut, uc_FitMC,
			    uc_FitData, uc_FitExtrapol, ewkFakeRate, ewkFakeRateSyst,prefix);

    }//doEventYields

  }//for selection.size()


  if (doPileupWeights) {
    string selectAll = "select_All";
    bool stackplots  = true;

    PlotConfig * photonVjet = new PlotConfig( lumiMC, true, "#gamma+W/Z+Jet (Sim.)", "PhotonVMCAll", selectAll,
					      "Plots_PhotonSusyAnalysis/Merged_PhotonVJets_V03_PAT/mergedHistos.root",
					      11, 20, stackplots );

    PlotConfig * qcd        = new PlotConfig( lumiMC, true, getLegendTitle("QCD"), "QCDMC", selectAll,
					      "Plots_PhotonSusyAnalysis/Merged_QCD_PhotonJet_V22i/mergedHistos.root", 
					      4, 20, stackplots );

    PlotConfig * phJet      = new PlotConfig( lumiMC, true, getLegendTitle("PhotonJet"), "PJMC", selectAll,
					      "Plots_PhotonSusyAnalysis/PhotonJet_V20bv_PAT/mergedHistos.root",
					      3, 20, stackplots );

    PlotConfig * ttbar      = new PlotConfig( lumiMC, true, "t#bar{t}", "TTMC", selectAll,
					      "Plots_PhotonSusyAnalysis/TTBar_V03bv_PAT/mergedHistos.root",
					      5, 20, stackplots );
		
    PlotConfig * wJets      = new PlotConfig( lumiMC, true, getLegendTitle("WJets"), "WJMC", selectAll,
					      "Plots_PhotonSusyAnalysis/WJets_V20bt_PAT/mergedHistos.root",
					      7, 20, stackplots );
		
    PlotConfig * signalGGMA = new PlotConfig( lumiMC, true, getLegendTitle("signalGGMA"), "", selectAll,
					      "Plots_PhotonSusyAnalysis/GGM_A_V20/histoGGMA.root", 
					      2, 20, false);

    PlotConfig * signalGGMB = new PlotConfig( lumiMC, true, getLegendTitle("signalGGMB"), "", selectAll,
					      "Plots_PhotonSusyAnalysis/GGM_B_V20/histoGGMB.root", 
					      2, 20, false);

      
    vector<PlotConfig> configsAllStacked;

    configsAllStacked.push_back(*ttbar);
    configsAllStacked.push_back(*photonVjet);
    //configsAllStacked.push_back(*wJets);
    //configsAllStacked.push_back(*dyjettoll);
    //configsAllStacked.push_back(*zinv);

    //configsAllStacked.push_back(*qcd);
    //configsAllStacked.push_back(*phJet);

    configsAllStacked.push_back(*signalGGMA);
    configsAllStacked.push_back(*signalGGMB);
      
    vector < string > histoNames;

    compareHistosSusyPhotonJetAnalysis( histoNames, lumiData, true, true,
					configsAllStacked, "PUPlots_" + selectAll, dirname, "", true,
					false, false, true );

  }//doPileupWeights

}


