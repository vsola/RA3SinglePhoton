#!/bin/bash

echo "mk targetdir"
targetdir="PhotonSusyPlots_V22i"

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
 ###############################################
 ###QCD background estimation
 ###############################################
 #####MC
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonBeforeFitQCDandPhotonJet/c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose.$filetype $targetdir/PreselBeforeCorrMC_PhotonPt.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonBeforeFitQCDandPhotonJet/c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RAT.$filetype $targetdir/PreselBeforeCorrMC_PhotonPtRAT.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonBeforeFitQCDandPhotonJet/c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RATRelErr.$filetype $targetdir/PreselBeforeCorrMC_PhotonPtRATRelErr.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonBeforeFitQCDandPhotonJet/c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RATEff.$filetype $targetdir/PreselBeforeCorrMC_PhotonPtRATEff.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonBeforeFitQCDandPhotonJet/c_ExtrapolationOfFitToWholeSpectrum.$filetype $targetdir/PreselBeforeCorrMC_CompExtrapolationWholeSpectrum.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonBeforeFitQCDandPhotonJet/c_ExtrapolationOfFitToWholeSpectrum_RATRelErr.$filetype $targetdir/PreselBeforeCorrMC_CompExtrapolationWholeSpectrumRelErr.$filetype
 
 cp Plots_PhotonSusyAnalysis/PlotsCompMetShapeComparison/c_PreselCut_metVsPhotonPt_Bin_From_65_CompTightLoose.$filetype $targetdir/MetShapeComp_QCD_PhotonJet_Bin1.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsCompMetShapeComparison/c_PreselCut_metVsPhotonPt_Bin_From_95_CompTightLoose.$filetype $targetdir/MetShapeComp_QCD_PhotonJet_Bin2.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsCompMetShapeComparison/c_PreselCut_metVsPhotonPt_Bin_From_115_CompTightLoose.$filetype $targetdir/MetShapeComp_QCD_PhotonJet_Bin3.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsCompMetShapeComparison/c_PreselCut_metVsPhotonPt_Bin_From_135_CompTightLoose.$filetype $targetdir/MetShapeComp_QCD_PhotonJet_Bin4.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsCompMetShapeComparison/c_PreselCut_metVsPhotonPt_Bin_From_205_CompTightLoose.$filetype $targetdir/MetShapeComp_QCD_PhotonJet_Bin5.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsCompMetShapeComparison/c_PreselCut_metVsPhotonPt_Bin_From_305_CompTightLoose.$filetype $targetdir/MetShapeComp_QCD_PhotonJet_Bin6.$filetype
 
 ###########SM/Signal contamination for Fit
 cp Plots_PhotonSusyAnalysis/PlotsCompSMContamination/c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RAT.$filetype $targetdir/ContaminationFit_SM_photonptRATWithFit.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsCompSMContamination/c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RAT_RATRelErr.$filetype $targetdir/ContaminationFitRelErr_SM_photonptRATWithFit.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsCompSignalBContamination/c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RAT.$filetype $targetdir/ContaminationFit_SignalB_photonptRATWithFit.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsCompSignalBContamination/c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RAT_RATRelErr.$filetype $targetdir/ContaminationFitRelErr_SignalB_photonptRATWithFit.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsCompSignalAContamination/c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RAT.$filetype $targetdir/ContaminationFit_SignalA_photonptRATWithFit.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsCompSignalAContamination/c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RAT_RATRelErr.$filetype $targetdir/ContaminationFitRelErr_SignalA_photonptRATWithFit.$filetype
 ###########Closure Test
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonQCDandPhotonJet/c_PreselCut_photonPt.$filetype $targetdir/PreselClosureMC_PhotonPt.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonQCDandPhotonJet/c_PreselCut_metPt.$filetype $targetdir/PreselClosureMC_Met.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonQCDandPhotonJet/c_PreselCut_ht.$filetype $targetdir/PreselClosureMC_ht.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonQCDandPhotonJet/c_PreselCut_mht.$filetype $targetdir/PreselClosureMC_mht.$filetype
 ###########SM/Signal contamination in Prediction
 cp Plots_PhotonSusyAnalysis/EWKContamination_select_1ph_3jets/c_PreselCut_metPt.$filetype $targetdir/PreselClosureMCEWKCont_Met.$filetype
 
 cp Plots_PhotonSusyAnalysis/SignalContamination_select_1ph_3jets/c_PreselCut_metPt.$filetype $targetdir/PreselClosureMCSMAndSignalCont_Met.$filetype
 #####Data
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonBeforeFitData2011/c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose.$filetype $targetdir/PreselBeforeCorrData_PhotonPt.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonBeforeFitData2011/c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RAT.$filetype $targetdir/PreselBeforeCorrData_PhotonPtRAT.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonBeforeFitData2011/c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RATRelErr.$filetype $targetdir/PreselBeforeCorrData_PhotonPtRATRelErr.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonBeforeFitData2011/c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RATEff.$filetype $targetdir/PreselBeforeCorrData_PhotonPtRATEff.$filetype
 ###########Results data
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonData2011/c_PreselCut_photonPt.$filetype $targetdir/PreselClosureData_PhotonPt.$filetype
 cp Plots_PhotonSusyAnalysis/PlotsFOComparisonData2011/c_PreselCut_metPt.$filetype $targetdir/PreselClosureData_Met.$filetype
 
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
 
 #####Data
 cp Plots_PhotonSusyAnalysis/PlotsPixelSeedComparisonData2011/c_PreselCut_metPt.$filetype $targetdir/PreselClosureData_EWK_Met.$filetype
 
 ###############################################
 ###Results
 ###############################################
 #####Datadriven
 dirname=$resdirDataDriven"_select_1ph_3jets"
 dirnameDCS=$resdirDataDrivenDCSonly"_select_1ph_3jets"
 dirnameMC=$resdirMConly"_select_1ph_3jets"
 cp Plots_PhotonSusyAnalysis/$dirname/c_PreselCut_metPt.$filetype $targetdir/PreselMet_3jet.$filetype
 cp Plots_PhotonSusyAnalysis/$dirname/c_metPt.$filetype $targetdir/Met_3jet.$filetype 
 cp Plots_PhotonSusyAnalysis/$dirname/c_metPt_INT.$filetype $targetdir/MetINT_3jet.$filetype 
 cp Plots_PhotonSusyAnalysis/$dirname/c_PreselCut_noJets.$filetype $targetdir/PreselNoJet_3jet.$filetype
 #####DCSonly
 cp Plots_PhotonSusyAnalysis/$dirnameDCS/c_PreselCut_metPt.$filetype $targetdir/DCSonly_PreselMet_3jet.$filetype
 cp Plots_PhotonSusyAnalysis/$dirnameDCS/c_metPt.$filetype $targetdir/DCSonly_Met_3jet.$filetype 
 cp Plots_PhotonSusyAnalysis/$dirnameDCS/c_metPt_INT.$filetype $targetdir/DCSonly_MetINT_3jet.$filetype 
 cp Plots_PhotonSusyAnalysis/$dirnameDCS/c_PreselCut_noJets.$filetype $targetdir/DCSonly_PreselNoJet_3jet.$filetype
 
 #####MConly
 cp Plots_PhotonSusyAnalysis/$dirnameMC/c_PreselCut_metPt.$filetype $targetdir/PreselMet_3jet_MConly.$filetype 
 cp Plots_PhotonSusyAnalysis/$dirnameMC/c_metPt.$filetype $targetdir/Met_3jet_MConly.$filetype 
 cp Plots_PhotonSusyAnalysis/$dirnameMC/c_metPt_INT.$filetype $targetdir/MetINT_3jet_MConly.$filetype 
 cp Plots_PhotonSusyAnalysis/$dirnameMC/c_PreselCut_noJets.$filetype $targetdir/PreselNoJets_MConly.$filetype 
 
cp eventcounts.tex  $targetdir/eventcounts.tex
done 


