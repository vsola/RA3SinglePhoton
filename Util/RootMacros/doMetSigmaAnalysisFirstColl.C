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
#include <Util/RootMacros/compareHistosMetSigmaAnalysis.C>
#include <iostream>
#include <utility>
#include <cmath>
#include <cstdlib>
#include <TMath.h>

void makePlots(string dirname, string dirnameMC, bool files, string jetCutPt,
		bool isZee, bool isPhotonJet, double lumi, bool doPF, bool doCalo, bool doTypeI=true) {

	if (!files) {
		//gROOT->Reset();

		TFile * file = new TFile(("MetSigmaMergedResults_PlotsForThesis/" + dirname
				+ "/metSigmaResult.root").c_str(), "Open");
		TFile * fileMC = 0;

		if (dirname == dirnameMC) {
			fileMC = file;
		} else if (dirnameMC != "") {
			fileMC = new TFile(("MetSigmaMergedResults_PlotsForThesis/" + dirnameMC
					+ "/metSigmaResult.root").c_str(), "Open");
		}
		string zee = "";
		if (isZee)
			zee = "Zee";
		if (isPhotonJet)
			zee = "PhotonJet";

		/////////////implementation:
		///void compareHistosMetSigmaAnalysis(TFile * file, TFile * fileMC,
		///		string sampleName = "", bool qcd = false, bool doUCenergyPlots = true,
		///		bool plotTypeRaw = true, bool plotTypeI = true, bool plotTypeII = true,
		///		bool plotTypeIILocal = true, bool plotTypePF = false, bool plotTypePFI =
		///		false, bool plotTypePFII = false, bool plotTypePFIIL = false,
		//		bool plotTypeTC = false, string jetCutPt = "10")

		//////		//raw,typeI,typeIIL,PF,TC
		//		compareHistosMetSigmaAnalysis(file, fileMC, zee, false, true, true,
		//			true,false, true, true, false,false, false, true, jetCutPt);
		////
		//		//raw,typeI
		//		compareHistosMetSigmaAnalysis(file, fileMC, zee, false, true, true,
		//				true, false, false, false,false, false, false,false, jetCutPt);
		//		//raw,typeIIL
		//		compareHistosMetSigmaAnalysis(file, fileMC, zee, false, true, true,
		//				false,false, true, false, false,false, false, false, jetCutPt);
		////		//		//
		if (doCalo) {
			//raw,typeI,typeIIL
			compareHistosMetSigmaAnalysis(file, fileMC, zee, false, true, true,
					doTypeI, false, true, false, false, false, false, false,
					jetCutPt, lumi);
		}
		//
		////		//raw,typeI,typeIIL,PF,PFI,PFIIL,TC
		//		compareHistosMetSigmaAnalysis(file, fileMC, zee, false, true, true,
		//				true, false, true, true,true, false,true, true, jetCutPt);
		//		//typeIIL,PF,PFI,PFIIL
		//		compareHistosMetSigmaAnalysis(file, fileMC, zee, false, true, false,
		//				false, false, true, true, true, false, true, false, jetCutPt);

		if (doPF) {
			//PF,PFI,PFIIL
			compareHistosMetSigmaAnalysis(file, fileMC, zee, false, true,
					false, false, false, false, true, doTypeI, false, true, false,
					jetCutPt, lumi);
			//						//PFIIL,PFII
			//						compareHistosMetSigmaAnalysis(file, fileMC, zee, false, true,
			//								false, false, false, false, true, true, true, true, false,
			//								jetCutPt, lumi);
		}
		//		//PF,PFI
		//		compareHistosMetSigmaAnalysis(file, fileMC, zee, false, true, false,
		//				false, false, false, true, true, false, false, false, jetCutPt);
		//typeIIL,PF,PFI
		//compareHistosMetSigmaAnalysis(file, fileMC, zee, false, true, false,
		//		false, false, true, true, true, false, false, false, jetCutPt);
		//
		////		//raw,typeI,typeII,typeIIL
		////		compareHistosMetSigmaAnalysis(file, fileMC, zee, false, true, true,
		////			true, true,false, false, true,false,false,false, jetCutPt);
		//
		//		//typeIIL
		//		compareHistosMetSigmaAnalysis(file, fileMC, zee, false, true, false,
		//				false,false, true, false, false,false, false, false, jetCutPt);
		//		//typeI
		//		compareHistosMetSigmaAnalysis(file, fileMC, zee, false, true, false,
		//				true,false, false, false, false,false, false, false, jetCutPt);
		//		//raw
		//		compareHistosMetSigmaAnalysis(file, fileMC, zee, false, true, true,
		//				false,false, false, false, false,false, false, false, jetCutPt);
		//
		////		//typeIIL and typeII
		//		compareHistosMetSigmaAnalysis(file, fileMC, zee, false, true, false,
		//				false, true, true, false, false, false, false, false, jetCutPt);
		//////
		//		//PF
		//		compareHistosMetSigmaAnalysis(file, fileMC, zee, false, true, false,
		//				false,false, false, true, false,false, false, false, jetCutPt);
		//
		//		//TC
		//		compareHistosMetSigmaAnalysis(file, fileMC, zee, false, true, false,
		//				false,false, false, false, false,false, false, true, jetCutPt);

		//gROOT->Reset();
		//cout<<"close"<<endl;
		file->Close();
		//cout<<"delete"<<endl;
		delete file;
		if (dirname != dirnameMC) {
			fileMC->Close();
			delete fileMC;
		}
	} else {

		//		TFile
		//				* filePs =
		//						new TFile(("MetSigmaMergedResults/"+dirname+"/metSigmaResult_MetComp_Raw_TypeI.root").c_str(),"Open");
		//		rootFileToPsandJpg(filePs, "");
		//		filePs->Close();
		//		delete filePs;
		//		//
		//		TFile
		//				* filePsRawTypeIIL =
		//						new TFile(("MetSigmaMergedResults/"+dirname+"/metSigmaResult_MetComp_Raw_TypeIIL.root").c_str(),"Open");
		//		rootFileToPsandJpg(filePsRawTypeIIL, "");
		//		filePsRawTypeIIL->Close();
		//		delete filePsRawTypeIIL;
		////////////
		if (doCalo) {
			TFile
					* filePsII =
							new TFile(
									("MetSigmaMergedResults_PlotsForThesis/" + dirname
											+ "/metSigmaResult_MetComp_Raw_TypeI_TypeIIL.root").c_str(),
									"Open");
			rootFileToPsandJpg(filePsII, "");
			filePsII->Close();
			delete filePsII;
			TFile
								* filePsI =
										new TFile(
												("MetSigmaMergedResults_PlotsForThesis/" + dirname
														+ "/metSigmaResult_MetComp_Raw_TypeIIL.root").c_str(),
												"Open");
						rootFileToPsandJpg(filePsI, "");
						filePsI->Close();
						delete filePsI;
		}
		if (doPF) {
			TFile * filePsIIPF = new TFile(("MetSigmaMergedResults_PlotsForThesis/" + dirname
					+ "/metSigmaResult_MetComp_PF_PFI_PFIIL.root").c_str(),
					"Open");
			rootFileToPsandJpg(filePsIIPF, "");
			filePsIIPF->Close();
			delete filePsIIPF;
			TFile * filePsIPF = new TFile(("MetSigmaMergedResults_PlotsForThesis/" + dirname
								+ "/metSigmaResult_MetComp_PF_PFIIL.root").c_str(),
								"Open");
						rootFileToPsandJpg(filePsIPF, "");
						filePsIPF->Close();
						delete filePsIPF;
			//						TFile
			//								* filePsIIPFL =
			//										new TFile(
			//												("MetSigmaMergedResults/" + dirname
			//														+ "/metSigmaResult_MetComp_PF_PFI_PFII_PFIIL.root").c_str(),
			//												"Open");
			//						rootFileToPsandJpg(filePsIIPFL, "");
			//						filePsIIPFL->Close();
			//						delete filePsIIPFL;
		}

		////
		//		TFile
		//				* filePsIIPFTC =
		//						new TFile(("MetSigmaMergedResults/"+dirname+"/metSigmaResult_MetComp_Raw_TypeI_TypeIIL_PF_TC.root").c_str(),"Open");
		//		rootFileToPsandJpg(filePsIIPFTC, "");
		//		filePsIIPFTC->Close();
		//		delete filePsIIPFTC;
		//		TFile * filePsIIPFI = new TFile(("MetSigmaMergedResults/" + dirname
		//				+ "/metSigmaResult_MetComp_TypeIIL_PF_PFI.root").c_str(),
		//				"Open");
		//		rootFileToPsandJpg(filePsIIPFI, "");
		//		filePsIIPFI->Close();
		//		delete filePsIIPFI;
		//		TFile
		//				* filePsIIPFIAndII =
		//						new TFile(
		//								("MetSigmaMergedResults/" + dirname
		//										+ "/metSigmaResult_MetComp_TypeIIL_PF_PFI_PFIIL.root").c_str(),
		//								"Open");
		//		rootFileToPsandJpg(filePsIIPFIAndII, "");
		//		filePsIIPFIAndII->Close();
		//		delete filePsIIPFIAndII;
		//
		//		TFile
		//				* filePsOnlyPF =
		//						new TFile(("MetSigmaMergedResults/"+dirname+"/metSigmaResult_MetComp_PF.root").c_str(),"Open");
		//		rootFileToPsandJpg(filePsOnlyPF, "");
		//		filePsOnlyPF->Close();
		//		delete filePsOnlyPF;
		//
		//		TFile
		//				* filePsOnlyTC =
		//						new TFile(("MetSigmaMergedResults/"+dirname+"/metSigmaResult_MetComp_TC.root").c_str(),"Open");
		//		rootFileToPsandJpg(filePsOnlyTC, "");
		//		filePsOnlyTC->Close();
		//		delete filePsOnlyTC;
		//
		//		TFile
		//				* filePsOnlyRaw =
		//						new TFile(("MetSigmaMergedResults/"+dirname+"/metSigmaResult_MetComp_Raw.root").c_str(),"Open");
		//		rootFileToPsandJpg(filePsOnlyRaw, "");
		//		filePsOnlyRaw->Close();
		//		delete filePsOnlyRaw;
		//
		//		TFile
		//				* filePsOnlyI_noRaw =
		//						new TFile(("MetSigmaMergedResults/"+dirname+"/metSigmaResult_MetComp_TypeI.root").c_str(),"Open");
		//		rootFileToPsandJpg(filePsOnlyI_noRaw, "");
		//		filePsOnlyI_noRaw->Close();
		//		delete filePsOnlyI_noRaw;
		//
		//		TFile
		//				* filePsOnlyII_noRaw =
		//						new TFile(("MetSigmaMergedResults/"+dirname+"/metSigmaResult_MetComp_TypeIIL.root").c_str(),"Open");
		//		rootFileToPsandJpg(filePsOnlyII_noRaw, "");
		//		filePsOnlyII_noRaw->Close();
		//		delete filePsOnlyII_noRaw;

	}

}
void doMetSigmaAnalysisFirstColl(bool files = false) {




//	//latest MinBias Plots as used for AN 10-131
		makePlots("RerecoJune9th_MBGOODCOLL_V100625B_V1",
							"MinBiasPythia8MC_V100621_V1", files, "25", false, false, 0.0012,
							false, true);



//////	//ZEE
//	//DATA VS MC==============Pf10!
//	makePlots("ZEE_Run2010AEGNov4Rereco_V4_V2InclPF10",
//			"Fall10DYEE_Pf10GeV_V4_V2InclPF10", files, "10", true, false, 36,
//			true, false);
//
//	makePlots("ZEE_Run2010AEGNov4Rereco_V4_V2Incl",
//			"Fall10DYEE_Pf6GeV_V4_V2Incl", files, "20", true, false, 36, false,
//			true);
//
//	//Incl PU
//	makePlots("ZEE_Run2010AEGNov4Rereco_V4_V2InclPF10InclPU",
//			"Fall10DYEE_Pf10GeVInclPU_V4_V2InclPF10InclPU", files, "10", true,
//			false, 36, true, false);
//	makePlots("ZEE_Run2010AEGNov4Rereco_V4_V2ExclPF10InclPU",
//			"Fall10DYEE_Pf10GeVInclPU_V4_V2ExclPF10InclPU", files, "10", true,
//			false, 36, true, false,false);
//
//////
//////	//Incl PU
//	makePlots("ZEE_Run2010AEGNov4Rereco_V4_V2ExclInclPU",
//			"Fall10DYEE_Pf6GeVInclPU_V4_V2ExclInclPU", files, "20", true,
//			false, 36, false, true,false);
//	makePlots("ZEE_Run2010AEGNov4Rereco_V4_V2InclInclPU",
//			"Fall10DYEE_Pf6GeVInclPU_V4_V2InclInclPU", files, "20", true,
//			false, 36, false, true);
////
////
//	//uge,2 Feb, temp
////	//MC only==============Calo!
//	makePlots("Fall10DYEE_Pf6GeV_V4_V2Excl", "Fall10DYEE_Pf6GeV_V4_V2Excl",
//			files, "20", true, false, 36, false, true,false);
//////
//	makePlots("Fall10DYEE_Pf6GeV_V4_V2Incl", "Fall10DYEE_Pf6GeV_V4_V2Incl",
//			files, "20", true, false, 36, false, true);
//
//	//MC only==============Pf10!
//	makePlots("Fall10DYEE_Pf10GeV_V4_V2ExclPF10",
//			"Fall10DYEE_Pf10GeV_V4_V2ExclPF10", files, "10", true, false, 36,
//			true, false,false);
//	makePlots("Fall10DYEE_Pf10GeV_V4_V2InclPF10",
//			"Fall10DYEE_Pf10GeV_V4_V2InclPF10", files, "10", true, false, 36,
//			true, false);
////	//MC only==============Pf6!
////	makePlots("Fall10DYEE_Pf6GeV_V4_V2ExclPF6",
////			"Fall10DYEE_Pf6GeV_V4_V2ExclPF6", files, "6", true, false, 36,
////			true, false);
////	makePlots("Fall10DYEE_Pf6GeV_V4_V2InclPF6",
////			"Fall10DYEE_Pf6GeV_V4_V2InclPF6", files, "6", true, false, 36,
////			true, false);
////////
////////	///Dijet DATA VS MC
////
//	makePlots("DJ_Run2010AJetMetNov4ReReco_V4_V2",
//			"Fall10QCDDijetFlat7TeV_V4_V2", files, "40", false, false, 0.02,
//			false, true);
//	makePlots("DJ_Run2010AJetMetNov4ReReco_V4_V2PF",
//			"Fall10QCDDijetFlat7TeV_V4_V2PF", files, "40", false, false, 0.02,
//			true, false);



}

