void makePlots(string dirname, bool isData, double lumi) {

	TFile * file = new TFile(
			("PTSelectionTreeMakerMergedResults/" + dirname).c_str(), "Update");

	compareHistosPTAnalysis(file, isData, lumi);
	file->Close();
}
void makeGraphics(string dirname) {
	gROOT->ProcessLine(".L Util/RootMacros/rootFileToPsandJpg.C");

	TFile * fileMCDef = new TFile(("PTSelectionTreeMakerMergedResults/"
			+ dirname).c_str(), "Open");
	rootFileToPsandJpg(fileMCDef, "");
	fileMCDef->Close();
	delete fileMCDef;

}
void doPTAnalysisPlots(bool makeOnlyEps = false) {
	//makePlots("Run2010AJetMet17SepRereco_2J100_V1DJ500_V1DJ500_NBE",true,11.0);
	if (!makeOnlyEps) {
		gROOT->ProcessLine(".L Util/RootMacros/compareHistosPTAnalysis.C");

		///###############################
		///Punchthrough studies
		///###############################
		//			makePlots("QCDDijetFlat7TeV_2J100_V6_V1DJ250_V1DJ250_NBE/tree_Summer10__BC19_PT33.root", false, 15);
		//				makePlots(
		//						"QCDDijetFlat7TeV_2J100_V6_V1DJ500_V2DJ500_NBE/tree_Summer10__BC19_PT33.root",
		//						false, 100);
		//				makePlots(
		//						"QCDDijetFlat7TeV_2J100_V6_V1DJ500_V2DJ500_NBE_Norm14.2/tree_Summer10__BC19_PT33.root",
		//						false, 14.2);
		//				makePlots(
		//						"QCDDijetFlat7TeV_2J100_V6_V1DJ250_V1DJ250_NBE/tree_Summer10__BC19_PT33.root",
		//						false, 100);
		//				makePlots(
		//						"QCDDijetFlat7TeV_2J100_V6_V1DJ250_V1DJ250_NBE_Norm14.2/tree_Summer10__BC19_PT33.root",
		//						false, 14.2);
		//

		/////make PT Tag Scan

//		makePlots(
//				"QCDDijetFlat7TeV_2J100_V9_V1DJ250_V1DJ250_NBE_Norm36/tree_Summer10__BC22_PT33.root",
//				false, 36);
//		makePlots(
//				"QCDDijetFlat7TeV_2J100_V9_V1DJ250_V1DJ250_NBE_Norm36/tree_Summer10__BC22_PT34.root",
//				false, 36);
//		makePlots(
//				"QCDDijetFlat7TeV_2J100_V9_V1DJ250_V1DJ250_NBE_Norm36/tree_Summer10__BC22_PT35.root",
//				false, 36);
//		makePlots(
//				"QCDDijetFlat7TeV_2J100_V9_V1DJ250_V1DJ250_NBE_Norm36/tree_Summer10__BC22_PT36.root",
//				false, 36);
//		makePlots(
//				"QCDDijetFlat7TeV_2J100_V9_V1DJ250_V1DJ250_NBE_Norm36/tree_Summer10__BC22_PT37.root",
//				false, 36);
//		makePlots(
//				"QCDDijetFlat7TeV_2J100_V9_V1DJ250_V1DJ250_NBE_Norm36/tree_Summer10__BC22_PT38.root",
//				false, 36);
//
//		makePlots(
//				"QCDDijetFlat7TeV_2J100_V9_V1DJ250_V1DJ250_NBE_Norm36/tree_Summer10__BC22_PT39.root",
//				false, 36);
//
//
//		///Data
//		makePlots(
//				"Run2010AJetMetNov4ReReco_2J100_V9_V1DJ250_V1DJ250_NBE/tree_Summer10__BC22_PT33.root",
//				true, 36);
//		makePlots(
//				"Run2010AJetMetNov4ReReco_2J100_V9_V1DJ250_V1DJ250_NBE/tree_Summer10__BC22_PT34.root",
//				true, 36);
//		makePlots(
//				"Run2010AJetMetNov4ReReco_2J100_V9_V1DJ250_V1DJ250_NBE/tree_Summer10__BC22_PT35.root",
//				true, 36);
//		makePlots(
//				"Run2010AJetMetNov4ReReco_2J100_V9_V1DJ250_V1DJ250_NBE/tree_Summer10__BC22_PT36.root",
//				true, 36);
//		makePlots(
//				"Run2010AJetMetNov4ReReco_2J100_V9_V1DJ250_V1DJ250_NBE/tree_Summer10__BC22_PT37.root",
//				true, 36);
//		makePlots(
//				"Run2010AJetMetNov4ReReco_2J100_V9_V1DJ250_V1DJ250_NBE/tree_Summer10__BC22_PT38.root",
//				true, 36);
//		makePlots(
//				"Run2010AJetMetNov4ReReco_2J100_V9_V1DJ250_V1DJ250_NBE/tree_Summer10__BC22_PT39.root",
//				true, 36);

		makePlots(
						"QCDDijetFlat7TeV_2J100_V9_V1DJ500_V1DJ500_NBE_Norm36/tree_Summer10__BC22_PT33.root",
						false, 36);
				makePlots(
						"QCDDijetFlat7TeV_2J100_V9_V1DJ500_V1DJ500_NBE_Norm36/tree_Summer10__BC22_PT34.root",
						false, 36);
				makePlots(
						"QCDDijetFlat7TeV_2J100_V9_V1DJ500_V1DJ500_NBE_Norm36/tree_Summer10__BC22_PT35.root",
						false, 36);
				makePlots(
						"QCDDijetFlat7TeV_2J100_V9_V1DJ500_V1DJ500_NBE_Norm36/tree_Summer10__BC22_PT36.root",
						false, 36);
				makePlots(
						"QCDDijetFlat7TeV_2J100_V9_V1DJ500_V1DJ500_NBE_Norm36/tree_Summer10__BC22_PT37.root",
						false, 36);
				makePlots(
						"QCDDijetFlat7TeV_2J100_V9_V1DJ500_V1DJ500_NBE_Norm36/tree_Summer10__BC22_PT38.root",
						false, 36);

				makePlots(
						"QCDDijetFlat7TeV_2J100_V9_V1DJ500_V1DJ500_NBE_Norm36/tree_Summer10__BC22_PT39.root",
						false, 36);


				///Data
				makePlots(
						"Run2010AJetMetNov4ReReco_2J100_V9_V1DJ250_V1DJ500_NBE/tree_Summer10__BC22_PT33.root",
						true, 36);
				makePlots(
						"Run2010AJetMetNov4ReReco_2J100_V9_V1DJ250_V1DJ500_NBE/tree_Summer10__BC22_PT34.root",
						true, 36);
				makePlots(
						"Run2010AJetMetNov4ReReco_2J100_V9_V1DJ250_V1DJ500_NBE/tree_Summer10__BC22_PT35.root",
						true, 36);
				makePlots(
						"Run2010AJetMetNov4ReReco_2J100_V9_V1DJ250_V1DJ500_NBE/tree_Summer10__BC22_PT36.root",
						true, 36);
				makePlots(
						"Run2010AJetMetNov4ReReco_2J100_V9_V1DJ250_V1DJ500_NBE/tree_Summer10__BC22_PT37.root",
						true, 36);
				makePlots(
						"Run2010AJetMetNov4ReReco_2J100_V9_V1DJ250_V1DJ500_NBE/tree_Summer10__BC22_PT38.root",
						true, 36);
				makePlots(
						"Run2010AJetMetNov4ReReco_2J100_V9_V1DJ250_V1DJ500_NBE/tree_Summer10__BC22_PT39.root",
						true, 36);
//		makePlots(
//				"Run2010AJetMetNov4ReReco_2J100_V9_V1DJ250_V1DJ250OnlyPT_NBE/tree_Summer10__BC19_PT33.root",
//				true, 36);
		//
		///BTag Efficiency DJ250 MC 36 pb
		//		makePlots(
		//				"QCDDijetFlat7TeV_2J100_V9_V1DJ250_V1DJ250_NBE_Norm36/tree_Summer10__BC17_PT33.root",
		//				false, 36);
		//		makePlots(
		//				"QCDDijetFlat7TeV_2J100_V9_V1DJ250_V1DJ250_NBE_Norm36/tree_Summer10__BC18_PT33.root",
		//				false, 36);
		//
		//		makePlots(
		//				"QCDDijetFlat7TeV_2J100_V9_V1DJ250_V1DJ250_NBE_Norm36/tree_Summer10__BC19_PT33.root",
		//				false, 36);
		//
		//		makePlots(
		//				"QCDDijetFlat7TeV_2J100_V9_V1DJ250_V1DJ250_NBE_Norm36/tree_Summer10__BC20_PT33.root",
		//				false, 36);
		//		makePlots(
		//				"QCDDijetFlat7TeV_2J100_V9_V1DJ250_V1DJ250_NBE_Norm36/tree_Summer10__BC21_PT33.root",
		//				false, 36);
		//		makePlots("QCDDijetFlat7TeV_2J100_V9_V1DJ250_V1DJ250_NBE_Norm36/tree_Summer10__BC22_PT33.root",
		//						false, 36);

		///###############################
		///DeadEcal Saturation Tests
		///###############################
		//		makePlots("QCDDijetFlat7TeV_DECAL_2J100_WoDeadECAL_SatNo_V1_V1GJ150_Norm100/tree_Summer10_DeadEcalSat__BC18_PT33.root", false, 100);
		//		makePlots("QCDDijetFlat7TeV_DECAL_2J100_WoDeadECAL_Sat0_V1_V1GJ150_Norm100/tree_Summer10_DeadEcalSat__BC18_PT33.root", false, 100);
		//		makePlots("QCDDijetFlat7TeV_DECAL_2J100_WoDeadECAL_Sat64_V1_V1GJ150_Norm100/tree_Summer10_DeadEcalSat__BC18_PT33.root", false, 100);
		//		makePlots("QCDDijetFlat7TeV_DECAL_2J100_WoDeadECAL_Sat128_V1_V1GJ150/tree_Summer10_DeadEcalSat__BC18_PT33.root", false, 100);
		//		makePlots("QCDDijetFlat7TeV_DECAL_2J100_WoDeadECAL_Sat256_V1_V1GJ150_Norm100/tree_Summer10_DeadEcalSat__BC18_PT33.root", false, 100);
		//		makePlots("QCDDijetFlat7TeV_DECAL_2J100_WoDeadECAL_Sat512_V1_V1GJ150_Norm100/tree_Summer10_DeadEcalSat__BC18_PT33.root", false, 100);
		//
		//		makePlots("QCDDijetFlat7TeV_DECAL_2J100_WoDeadECAL_SatNo_V1_V1GJ350_Norm100/tree_Summer10_DeadEcalSat__BC18_PT33.root", false, 100);
		//		makePlots("QCDDijetFlat7TeV_DECAL_2J100_WoDeadECAL_Sat0_V1_V1GJ350_Norm100/tree_Summer10_DeadEcalSat__BC18_PT33.root", false, 100);
		//		makePlots("QCDDijetFlat7TeV_DECAL_2J100_WoDeadECAL_Sat64_V1_V1GJ350_Norm100/tree_Summer10_DeadEcalSat__BC18_PT33.root", false, 100);
		//		makePlots("QCDDijetFlat7TeV_DECAL_2J100_WoDeadECAL_Sat128_V1_V1GJ350/tree_Summer10_DeadEcalSat__BC18_PT33.root", false, 100);
		//		makePlots("QCDDijetFlat7TeV_DECAL_2J100_WoDeadECAL_Sat256_V1_V1GJ350_Norm100/tree_Summer10_DeadEcalSat__BC18_PT33.root", false, 100);
		//		makePlots("QCDDijetFlat7TeV_DECAL_2J100_WoDeadECAL_Sat512_V1_V1GJ350_Norm100/tree_Summer10_DeadEcalSat__BC18_PT33.root", false, 100);
		//
		//
		//		makePlots("QCDDijetFlat7TeV_DECAL_2J100_WoDeadECAL_SatNo_V1_V1GJ700_Norm100/tree_Summer10_DeadEcalSat__BC18_PT33.root", false, 100);
		//		makePlots("QCDDijetFlat7TeV_DECAL_2J100_WoDeadECAL_Sat0_V1_V1GJ700_Norm100/tree_Summer10_DeadEcalSat__BC18_PT33.root", false, 100);
		//		makePlots("QCDDijetFlat7TeV_DECAL_2J100_WoDeadECAL_Sat64_V1_V1GJ700_Norm100/tree_Summer10_DeadEcalSat__BC18_PT33.root", false, 100);
		//		makePlots("QCDDijetFlat7TeV_DECAL_2J100_WoDeadECAL_Sat128_V1_V1GJ700/tree_Summer10_DeadEcalSat__BC18_PT33.root", false, 100);
		//		makePlots("QCDDijetFlat7TeV_DECAL_2J100_WoDeadECAL_Sat256_V1_V1GJ700_Norm100/tree_Summer10_DeadEcalSat__BC18_PT33.root", false, 100);
		//		makePlots("QCDDijetFlat7TeV_DECAL_2J100_WoDeadECAL_Sat512_V1_V1GJ700_Norm100/tree_Summer10_DeadEcalSat__BC18_PT33.root", false, 100);

		///###############################
		///DeadEcal without restirction to pthat, MEt tail 200
		///###############################

		//		makePlots(
		//				"QCDDijetFlat7TeV_DECAL_2J100_WoDeadECAL_V2_V1GJ150_V1GJ150/tree_Summer10__BC18_PT33.root",
		//				false, 100);
		//		makePlots(
		//				"QCDDijetFlat7TeV_DECAL_2J100_WoRecovery_V2_V1GJ150_V1GJ150/tree_Summer10__BC18_PT33.root",
		//				false, 100);
		//
		//		makePlots(
		//				"QCDDijetFlat7TeV_DECAL_2J100_WoRecovery_V2_V1GJ150_V1GJ150__NBE_NTP/tree_Summer10__BC18_PT33.root",
		//				false, 100);
		//		makePlots(
		//				"QCDDijetFlat7TeV_DECAL_2J100_WoRecovery_V2_V1GJ150_V1GJ150__BE/tree_Summer10__BC18_PT33.root",
		//				false, 100);
		//		makePlots(
		//				"QCDDijetFlat7TeV_DECAL_2J100_WoRecovery_V2_V1GJ150_V1GJ150__NBE/tree_Summer10__BC18_PT33.root",
		//				false, 100);
		//		makePlots(
		//				"QCDDijetFlat7TeV_DECAL_2J100_WoRecovery_V2_V1GJ150_V1GJ150__TP/tree_Summer10__BC18_PT33.root",
		//				false, 100);
		//		makePlots(
		//				"QCDDijetFlat7TeV_DECAL_2J100_WoRecovery_V2_V1GJ150_V1GJ150__NTP/tree_Summer10__BC18_PT33.root",
		//				false, 100);
		//		makePlots(
		//				"QCDDijetFlat7TeV_DECAL_2J100_WoRecovery_V2_V1GJ150_V1GJ150__DRMHT/tree_Summer10__BC18_PT33.root",
		//				false, 100);
		//		makePlots(
		//				"QCDDijetFlat7TeV_DECAL_2J100_WoRecovery_V2_V1GJ150_V1GJ150__NDRMHT/tree_Summer10__BC18_PT33.root",
		//				false, 100);

	}

}
