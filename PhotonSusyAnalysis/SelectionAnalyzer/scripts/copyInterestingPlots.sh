#!/bin/bash

echo "mk targetdir"
targetdir="PhotonSusyPlots_V24ww"
resdirDataDriven="All_Stack_CorrData"
resdirDataDrivenDCSonly="All_Stack_DCSCorrData"
resdirMConly="All_Stack_Data"

mkdir $targetdir

filetypes=(pdf eps)
#eps 
for filetype in ${filetypes[@]}
 do
 ###############################################
 ###Trigger Efficiencies
 ###############################################
 cp Plots_PhotonSusyAnalysis/TriggerEfficiencies/TRIGGEREFF_select_All_PhotonHad300PhotonT_select_All_PhotonSingle75PhotonTPreselCut_hthltN90.$filetype $targetdir/triggerEffN90.$filetype
 cp Plots_PhotonSusyAnalysis/TriggerEfficiencies/TRIGGEREFF_select_All_PhotonHad300PhotonT_select_All_PhotonSingle75PhotonTPreselCut_hthltN90Hits.$filetype $targetdir/triggerEffN90Hits.$filetype
 cp Plots_PhotonSusyAnalysis/TriggerEfficiencies/TRIGGEREFF_select_All_PhotonHad350PhotonT_select_All_PhotonSingle75PhotonTPreselCut_hthltN90.$filetype $targetdir/triggerEffN90HT350.$filetype
 cp Plots_PhotonSusyAnalysis/TriggerEfficiencies/TRIGGEREFF_select_All_PhotonHad350PhotonT_select_All_PhotonSingle75PhotonTPreselCut_hthltN90Hits.$filetype $targetdir/triggerEffN90HitsHT350.$filetype
 cp Plots_PhotonSusyAnalysis/TriggerEfficiencies/TRIGGEREFF_select_All_PhotonHad400PhotonT_select_All_PhotonSingle75PhotonTPreselCut_hthltN90.$filetype $targetdir/triggerEffN90HT400.$filetype
 cp Plots_PhotonSusyAnalysis/TriggerEfficiencies/TRIGGEREFF_select_All_PhotonHad400PhotonT_select_All_PhotonSingle75PhotonTPreselCut_hthltN90Hits.$filetype $targetdir/triggerEffN90HitsHT400.$filetype
 
 ###############################################
 ###QCD background estimation
 ###############################################
 #####MC
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonBeforeFitQCDandPhotonJet/c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose.$filetype $targetdir/PreselBeforeCorrMC_PhotonPt.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonBeforeFitQCDandPhotonJet/c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RAT.$filetype $targetdir/PreselBeforeCorrMC_PhotonPtRAT.$filetype
 #cp Plots_PhotonSusyAnalysis/PlotsFOComparisonBeforeFitQCDandPhotonJet/c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RATRelErr.$filetype $targetdir/PreselBeforeCorrMC_PhotonPtRATRelErr.$filetype
 #cp Plots_PhotonSusyAnalysis/PlotsFOComparisonBeforeFitQCDandPhotonJet/c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RATEff.$filetype $targetdir/PreselBeforeCorrMC_PhotonPtRATEff.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonBeforeFitQCDandPhotonJet/c_ExtrapolationOfFitToWholeSpectrum.$filetype $targetdir/PreselBeforeCorrMC_CompExtrapolationWholeSpectrum.$filetype


 cp Plots_PhotonSusyAnalysis/PlotsCompMetShapeComparison/c_PreselCut_metVsPhotonPt_Bin_From_65_CompTightLoose.$filetype $targetdir/MetShapeComp_QCD_PhotonJet_Bin1.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsCompMetShapeComparison/c_PreselCut_metVsPhotonPt_Bin_From_95_CompTightLoose.$filetype $targetdir/MetShapeComp_QCD_PhotonJet_Bin2.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsCompMetShapeComparison/c_PreselCut_metVsPhotonPt_Bin_From_115_CompTightLoose.$filetype $targetdir/MetShapeComp_QCD_PhotonJet_Bin3.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsCompMetShapeComparison/c_PreselCut_metVsPhotonPt_Bin_From_135_CompTightLoose.$filetype $targetdir/MetShapeComp_QCD_PhotonJet_Bin4.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsCompMetShapeComparison/c_PreselCut_metVsPhotonPt_Bin_From_205_CompTightLoose.$filetype $targetdir/MetShapeComp_QCD_PhotonJet_Bin5.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsCompMetShapeComparison/c_PreselCut_metVsPhotonPt_Bin_From_305_CompTightLoose.$filetype $targetdir/MetShapeComp_QCD_PhotonJet_Bin6.$filetype
 #####MC 2jet
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonBeforeFitDijetQCDandPhotonJet/c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose.$filetype $targetdir/PreselBeforeCorrMC_PhotonPt_2j.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonBeforeFitDijetQCDandPhotonJet/c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RAT.$filetype $targetdir/PreselBeforeCorrMC_PhotonPtRAT_2j.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonBeforeFitDijetQCDandPhotonJet/c_DivideXPreselCut_noJetsVsPhotonPtLowMet_Bin_From_2_CompTightLoose_RAT.$filetype $targetdir/PreselBeforeCorrMC_PhotonPtDijetRAT_2j.$filetype
#cp Plots_PhotonSusyAnalysis/PlotsFOComparisonBeforeFitDijetQCDandPhotonJet/c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RATRelErr.$filetype $targetdir/PreselBeforeCorrMC_PhotonPtRATRelErr_2j.$filetype
 #cp Plots_PhotonSusyAnalysis/PlotsFOComparisonBeforeFitDijetQCDandPhotonJet/c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RATEff.$filetype $targetdir/PreselBeforeCorrMC_PhotonPtRATEff_2j.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonBeforeFitDijetQCDandPhotonJet/c_ExtrapolationOfFitToWholeSpectrum.$filetype $targetdir/PreselBeforeCorrMC_CompExtrapolationWholeSpectrum_2j.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonBeforeFitDijetQCDandPhotonJet/c_ExtrapolationOfFitToWholeSpectrumDijet.$filetype $targetdir/PreselBeforeCorrMC_CompExtrapolationWholeSpectrumDijet_2j.$filetype
 
 ###########SM/Signal contamination for Fit
 cp Plots_PhotonSusyAnalysis/PlotsCompSMContamination/c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RAT.$filetype $targetdir/ContaminationFit_SM_photonptRATWithFit.$filetype
#cp Plots_PhotonSusyAnalysis/PlotsCompSMContamination/c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RAT_RATRelErr.$filetype $targetdir/ContaminationFitRelErr_SM_photonptRATWithFit.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsCompSignalBContamination/c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RAT.$filetype $targetdir/ContaminationFit_SignalB_photonptRATWithFit.$filetype
#cp Plots_PhotonSusyAnalysis/PlotsCompSignalBContamination/c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RAT_RATRelErr.$filetype $targetdir/ContaminationFitRelErr_SignalB_photonptRATWithFit.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsCompSignalAContamination/c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RAT.$filetype $targetdir/ContaminationFit_SignalA_photonptRATWithFit.$filetype
#cp Plots_PhotonSusyAnalysis/PlotsCompSignalAContamination/c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RAT_RATRelErr.$filetype $targetdir/ContaminationFitRelErr_SignalA_photonptRATWithFit.$filetype
#2j
cp Plots_PhotonSusyAnalysis/PlotsCompSMContaminationDijet/c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RAT.$filetype $targetdir/ContaminationFit_SM_photonptRATWithFit_2j.$filetype 
cp Plots_PhotonSusyAnalysis/PlotsCompSignalAContaminationDijet/c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RAT.$filetype $targetdir/ContaminationFit_SignalA_photonptRATWithFit_2j.$filetype 
 ###########Closure Test
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonMCQCDandPhotonJet/c_PreselCut_photonPt.$filetype $targetdir/PreselClosureMC_PhotonPt.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonMCQCDandPhotonJet/c_PreselCut_metPt.$filetype $targetdir/PreselClosureMC_Met.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonMCQCDandPhotonJet/c_PreselCut_ht.$filetype $targetdir/PreselClosureMC_ht.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonMCQCDandPhotonJet/c_PreselCut_mht.$filetype $targetdir/PreselClosureMC_mht.$filetype
 #2jet
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonDijetMCQCDandPhotonJet/c_PreselCut_photonPt.$filetype $targetdir/PreselClosureMC_PhotonPt_2j.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonDijetMCQCDandPhotonJet/c_PreselCut_metPt.$filetype $targetdir/PreselClosureMC_Met_2j.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonDijetMCQCDandPhotonJet/c_PreselCut_ht.$filetype $targetdir/PreselClosureMC_ht_2j.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonDijetMCQCDandPhotonJet/c_PreselCut_mht.$filetype $targetdir/PreselClosureMC_mht_2j.$filetype
 
 ###########SM/Signal contamination in Prediction
 cp Plots_PhotonSusyAnalysis/EWKContamination_select_1ph_3jets/c_PreselCut_metPt.$filetype $targetdir/PreselClosureMCEWKCont_Met.$filetype
 
 cp Plots_PhotonSusyAnalysis/SignalContamination_select_1ph_3jets/c_PreselCut_metPt.$filetype $targetdir/PreselClosureMCSMAndSignalCont_Met.$filetype
 #####Data
cp Plots_PhotonSusyAnalysis/PlotsFOComparisonBeforeFitData/c_2D_select_1ph_3jets_PreselCut_metVsPhotonPt.$filetype $targetdir/PreselBeforeCorrData_MetVsPhotonPt.$filetype
cp Plots_PhotonSusyAnalysis/PlotsFOComparisonBeforeFitData/c_2D_select_1ph_3jets_FO_PreselCut_metVsPhotonPt.$filetype $targetdir/PreselBeforeCorrData_MetVsFakePhotonPt.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonBeforeFitData/c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose.$filetype $targetdir/PreselBeforeCorrData_PhotonPt.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonBeforeFitData/c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RAT.$filetype $targetdir/PreselBeforeCorrData_PhotonPtRAT.$filetype
#cp Plots_PhotonSusyAnalysis/PlotsFOComparisonBeforeFitData/c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RATRelErr.$filetype $targetdir/PreselBeforeCorrData_PhotonPtRATRelErr.$filetype
# cp Plots_PhotonSusyAnalysis/PlotsFOComparisonBeforeFitData/c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RATEff.$filetype $targetdir/PreselBeforeCorrData_PhotonPtRATEff.$filetype
cp Plots_PhotonSusyAnalysis/PlotsFOComparisonBeforeFitData/c_PreselCut_metPt.$filetype $targetdir/PreselBeforeCorrData_Met.$filetype 

 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonBeforeFitData/c_NoOfJetDependencyFit_NORM.$filetype $targetdir/PreselBeforeCorrData_NoJetDependency.$filetype
  cp Plots_PhotonSusyAnalysis/PlotsFOComparisonBeforeFitData/c_NoOfJetDependencyFit_NORM_RATRelErr.$filetype $targetdir/PreselBeforeCorrData_NoJetDependencyRelErr.$filetype

cp Plots_PhotonSusyAnalysis/PlotsFOComparisonBeforeFitDijetData/c_PreselCut_metPt.$filetype $targetdir/PreselBeforeCorrData_Met_2j.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonBeforeFitDijetData/c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose.$filetype $targetdir/PreselBeforeCorrData_PhotonPt_2j.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonBeforeFitDijetData/c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RAT.$filetype $targetdir/PreselBeforeCorrData_PhotonPtRAT_2j.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonBeforeFitDijetData/c_DivideXPreselCut_noJetsVsPhotonPtLowMet_Bin_From_2_CompTightLoose_RAT.$filetype $targetdir/PreselBeforeCorrData_PhotonPtDijetRAT_2j.$filetype
#cp Plots_PhotonSusyAnalysis/PlotsFOComparisonBeforeFitDijetData/c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RATRelErr.$filetype $targetdir/PreselBeforeCorrData_PhotonPtRATRelErr_2j.$filetype
# cp Plots_PhotonSusyAnalysis/PlotsFOComparisonBeforeFitDijetData/c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RATEff.$filetype $targetdir/PreselBeforeCorrData_PhotonPtRATEff_2j.$filetype
 
 #########No Jet Correction
 cp Plots_PhotonSusyAnalysis/All_Stack_Corr2Data_select_1ph_3jets/c_PreselCut_metPt.$filetype $targetdir/PreselAfterNoJetCorr_Met.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonCorr2Data/c_PreselCut_noJets.$filetype $targetdir/PreselAfterNoJetCorr_NoJet.$filetype

 ###########Results data
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonData/c_PreselCut_photonPt.$filetype $targetdir/PreselClosureData_PhotonPt.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonData/c_PreselCut_metPt.$filetype $targetdir/PreselClosureData_Met.$filetype
 
 #2jet
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonDijetData/c_PreselCut_photonPt.$filetype $targetdir/PreselClosureData_PhotonPt_2j.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonDijetData/c_PreselCut_metPt.$filetype $targetdir/PreselClosureData_Met_2j.$filetype
 
 ###############################################
 ###EWK background estimation
 ###############################################
 #####MC
 cp Plots_PhotonSusyAnalysis/PlotsPixelSeedComparisonTTBar/c_PreselCut_metPt.$filetype  $targetdir/PreselClosureMC_EWK_TTBAR_Met.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsPixelSeedComparisonMCGenEleVetoReTTBar/c_PreselCut_metPt.$filetype  $targetdir/PreselClosureMCGenEle_EWK_TTBAR_Met.$filetype
 
 cp Plots_PhotonSusyAnalysis/PlotsPixelSeedComparisonWJetsToLNu/c_PreselCut_metPt.$filetype  $targetdir/PreselClosureMC_EWK_WJetsToLNu_Met.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsPixelSeedComparisonMCGenEleVetoReWJetsToLNu/c_PreselCut_metPt.$filetype  $targetdir/PreselClosureMCGenEle_EWK_WJetsToLNu_Met.$filetype
 
 cp Plots_PhotonSusyAnalysis/PlotsPixelSeedComparisonEWK/c_PreselCut_metPt.$filetype  $targetdir/PreselClosureMC_EWK_Met.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsPixelSeedComparisonMCGenEleVetoReEWK/c_PreselCut_metPt.$filetype  $targetdir/PreselClosureMCGenEle_EWK_Met.$filetype
 
 #2jet
 cp Plots_PhotonSusyAnalysis/PlotsPixelSeedComparisonDijetTTBar/c_PreselCut_metPt.$filetype  $targetdir/PreselClosureMC_EWK_TTBAR_Met_2j.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsPixelSeedComparisonDijetMCGenEleVetoReTTBar/c_PreselCut_metPt.$filetype  $targetdir/PreselClosureMCGenEle_EWK_TTBAR_Met_2j.$filetype
 
 cp Plots_PhotonSusyAnalysis/PlotsPixelSeedComparisonDijetWJetsToLNu/c_PreselCut_metPt.$filetype  $targetdir/PreselClosureMC_EWK_WJetsToLNu_Met_2j.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsPixelSeedComparisonDijetMCGenEleVetoReWJetsToLNu/c_PreselCut_metPt.$filetype  $targetdir/PreselClosureMCGenEle_EWK_WJetsToLNu_Met_2j.$filetype
 
 cp Plots_PhotonSusyAnalysis/PlotsPixelSeedComparisonDijetEWK/c_PreselCut_metPt.$filetype  $targetdir/PreselClosureMC_EWK_Met_2j.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsPixelSeedComparisonDijetMCGenEleVetoReEWK/c_PreselCut_metPt.$filetype  $targetdir/PreselClosureMCGenEle_EWK_Met_2j.$filetype

 #####Data
 cp Plots_PhotonSusyAnalysis/PlotsPixelSeedComparisonData/c_PreselCut_metPt.$filetype $targetdir/PreselClosureData_EWK_Met.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsPixelSeedComparisonDijetData/c_PreselCut_metPt.$filetype $targetdir/PreselClosureData_EWK_Met_2j.$filetype
 
 ###############################################
 ###Results
 ###############################################
 #####Datadriven
 dirname=$resdirDataDriven"_select_1ph_3jets"
 dirname2j=$resdirDataDriven"_select_1ph_2jets"
 dirnameDCS=$resdirDataDrivenDCSonly"_select_1ph_3jets"
 dirnameMC=$resdirMConly"_select_1ph_3jets"
 
 cp Plots_PhotonSusyAnalysis/$dirname/c_PreselCut_metPt.$filetype $targetdir/PreselMet_3jet.$filetype
 cp Plots_PhotonSusyAnalysis/$dirname/c_PreselCut_metSumEt.$filetype $targetdir/PreselMetSumEt_3jet.$filetype
 cp Plots_PhotonSusyAnalysis/$dirname/c_metPt.$filetype $targetdir/Met_3jet.$filetype 
 cp Plots_PhotonSusyAnalysis/$dirname/c_PreselCut_metPt_INT.$filetype $targetdir/MetINT_3jet.$filetype
 cp Plots_PhotonSusyAnalysis/$dirname/c_PreselCut_metPt_SB.$filetype $targetdir/MetSB_3jet.$filetype 
 cp Plots_PhotonSusyAnalysis/$dirname/c_PreselCut_metPt_SdB2.$filetype $targetdir/MetSdB2_3jet.$filetype 
 cp Plots_PhotonSusyAnalysis/$dirname/c_PreselCut_noJets.$filetype $targetdir/PreselNoJet_3jet.$filetype
 cp Plots_PhotonSusyAnalysis/$dirname/c_PreselCut_photonEta.$filetype $targetdir/PreselPhotonEta_3jet.$filetype

 cp Plots_PhotonSusyAnalysis/$dirname/c_PreselCut_jetPt.$filetype $targetdir/PreselJetPt_3jet.$filetype
 cp Plots_PhotonSusyAnalysis/$dirname/c_PreselCut_htj.$filetype $targetdir/PreselHTJ_3jet.$filetype
 cp Plots_PhotonSusyAnalysis/$dirname/c_PreselCut_noPV.$filetype $targetdir/PreselNoPV_3jet.$filetype 
 
 cp Plots_PhotonSusyAnalysis/$dirname2j/c_PreselCut_metPt.$filetype $targetdir/PreselMet_2jet.$filetype
 cp Plots_PhotonSusyAnalysis/$dirname2j/c_metPt.$filetype $targetdir/Met_2jet.$filetype 
 cp Plots_PhotonSusyAnalysis/$dirname2j/c_PreselCut_metPt_INT.$filetype $targetdir/MetINT_2jet.$filetype
 cp Plots_PhotonSusyAnalysis/$dirname2j/c_PreselCut_metPt_SB.$filetype $targetdir/MetSB_2jet.$filetype 
 cp Plots_PhotonSusyAnalysis/$dirname2j/c_PreselCut_metPt_SdB2.$filetype $targetdir/MetSdB2_2jet.$filetype 
 cp Plots_PhotonSusyAnalysis/$dirname2j/c_PreselCut_noJets.$filetype $targetdir/PreselNoJet_2jet.$filetype
 cp Plots_PhotonSusyAnalysis/$dirname2j/c_PreselCut_photonEta.$filetype $targetdir/PreselPhotonEta_2jet.$filetype
 cp Plots_PhotonSusyAnalysis/$dirname2j/c_PreselCut_metSumEt.$filetype $targetdir/PreselMetSumEt_2jet.$filetype
 
  cp Plots_PhotonSusyAnalysis/$dirname2j/c_PreselCut_jetPt.$filetype $targetdir/PreselJetPt_2jet.$filetype
 cp Plots_PhotonSusyAnalysis/$dirname2j/c_PreselCut_htj.$filetype $targetdir/PreselHTJ_2jet.$filetype
 cp Plots_PhotonSusyAnalysis/$dirname2j/c_PreselCut_noPV.$filetype $targetdir/PreselNoPV_2jet.$filetype 
 
 #####DCSonly
 cp Plots_PhotonSusyAnalysis/$dirnameDCS/c_PreselCut_metPt.$filetype $targetdir/DCSonly_PreselMet_3jet.$filetype
 cp Plots_PhotonSusyAnalysis/$dirnameDCS/c_metPt.$filetype $targetdir/DCSonly_Met_3jet.$filetype 
 cp Plots_PhotonSusyAnalysis/$dirnameDCS/c_PreselCut_metPt_INT.$filetype $targetdir/DCSonly_MetINT_3jet.$filetype 
 cp Plots_PhotonSusyAnalysis/$dirnameDCS/c_PreselCut_noJets.$filetype $targetdir/DCSonly_PreselNoJet_3jet.$filetype
 
 #####MConly
 cp Plots_PhotonSusyAnalysis/$dirnameMC/c_PreselCut_metPt.$filetype $targetdir/PreselMet_3jet_MConly.$filetype 
 cp Plots_PhotonSusyAnalysis/$dirnameMC/c_metPt.$filetype $targetdir/Met_3jet_MConly.$filetype 
 cp Plots_PhotonSusyAnalysis/$dirnameMC/c_PreselCut_metPt_INT.$filetype $targetdir/MetINT_3jet_MConly.$filetype 
 cp Plots_PhotonSusyAnalysis/$dirnameMC/c_PreselCut_noJets.$filetype $targetdir/PreselNoJets_MConly.$filetype 
 
 ####Photon-Jet-Reweighting Plots
 mkdir $targetdir/PhotonJetReweightingComparisonLooseId
 mkdir $targetdir/PhotonReweightingComparisonLooseId
 mkdir $targetdir/PhotonJetReweightingComparison
 cp Plots_PhotonJetReweightingLooseId/$dirname2j/c_PreselCut_metPt.$filetype $targetdir/PhotonJetReweightingComparisonLooseId/.
 cp Plots_PhotonPtReweightingLooseId/$dirname2j/c_PreselCut_metPt.$filetype $targetdir/PhotonReweightingComparisonLooseId/.
 cp Plots_PhotonJetReweighting/$dirname2j/c_PreselCut_metPt.$filetype $targetdir/PhotonJetReweightingComparison/.
 
 
 #####all event counts
 cp eventcounts100_select_1ph_3jets.tex  $targetdir/eventcounts100.tex
 cp eventcounts200_select_1ph_3jets.tex  $targetdir/eventcounts200.tex
 cp eventcounts350_select_1ph_3jets.tex  $targetdir/eventcounts350.tex
 cp eventcounts200_select_1ph_3jets.tex  $targetdir/eventcounts.tex
 
 cp eventcounts100_select_1ph_2jets.tex  $targetdir/eventcounts100_2j.tex
 cp eventcounts200_select_1ph_2jets.tex  $targetdir/eventcounts200_2j.tex
 cp eventcounts350_select_1ph_2jets.tex  $targetdir/eventcounts350_2j.tex
 cp eventcounts200_select_1ph_2jets.tex  $targetdir/eventcounts_2j.tex

 
done 


