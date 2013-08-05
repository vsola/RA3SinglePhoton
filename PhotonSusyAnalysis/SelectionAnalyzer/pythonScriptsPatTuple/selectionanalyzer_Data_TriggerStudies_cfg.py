####################################CONFIGURATION##################################
###################################################################################

###SAMPLE###
#Fall 10MC, 7TeV ======9
#Data, 7TeV ======10

sampleConf = 10


#####################################################################################
#################################################
import FWCore.ParameterSet.Config as cms

process = cms.Process("PhotonJetSelectionFromPat")
process.TFileService = cms.Service("TFileService", fileName = cms.string("histo.root',") )

test=False
import PhotonSusyAnalysis.SelectionAnalyzer.selectionanalyzer_multi_cfg as baseConfig
doSkimming=False
doAnalysis=False
noKinematicPresel=False
PUDistributionMC=cms.vdouble(0)
baseConfig.getProcessFor(sampleConf,process,test,doSkimming,doAnalysis,"",noKinematicPresel,PUDistributionMC,0)

process.source = cms.Source("PoolSource",
	    	fileNames = cms.untracked.vstring(
											#'file:photonJetSelection.root','
											
											'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_10_1_1FT.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_11_1_5D7.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_11_1_8mQ.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_12_1_1sj.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_12_1_JKx.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_13_1_TYM.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_13_1_uWk.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_14_1_BIb.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_15_1_smZ.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_16_1_CLW.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_16_1_XvS.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_17_1_Tfi.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_17_1_xVQ.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_18_1_3Jz.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_18_1_hmI.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_19_1_cgS.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_19_1_yXo.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_1_1_5hP.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_20_1_Xic.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_20_1_vSq.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_21_1_0FW.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_21_1_4NG.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_22_1_l70.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_22_1_nqA.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_23_1_LPH.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_24_1_Q7f.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_24_1_irg.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_25_1_Zlm.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_26_1_tnu.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_27_1_aq3.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_27_1_mda.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_28_1_Wrl.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_28_1_xJb.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_29_1_V6e.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_29_1_dAG.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_2_1_APV.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_2_1_Um0.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_30_1_ADC.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_30_1_ruu.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_31_1_5yq.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_31_1_X2w.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_32_1_Fgh.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_32_1_a6i.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_33_1_wi6.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_33_1_xWy.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_34_1_uSA.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_34_1_umE.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_35_1_8le.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_35_1_YJH.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_36_1_MmB.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_36_1_tiA.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_37_1_4Et.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_37_1_7wc.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_38_1_Hyv.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_39_1_Pf9.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_3_1_4Q7.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_3_1_YVf.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_40_1_mRU.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_40_1_toE.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_41_1_Ady.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_42_1_q7H.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_43_1_wIj.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_44_1_MhY.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_45_1_3e7.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_45_1_BbK.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_46_1_5UQ.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_46_1_64c.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_47_1_IS6.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_48_1_fkF.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_49_1_5Zx.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_4_1_E4o.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_4_1_l4w.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_50_1_xOC.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_51_1_G4r.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_51_1_yYy.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_52_1_2Lk.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_52_1_V1r.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_53_1_2Yt.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_54_1_S3l.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_55_1_7Yz.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_55_1_BCN.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_56_1_s0n.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_56_1_v0a.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_57_1_7eJ.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_57_1_q6S.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_58_1_Ugo.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_58_1_r4M.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_59_1_MGF.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_5_1_8lC.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_5_1_lbN.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_60_1_Gbt.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_61_1_WEA.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_62_1_RO4.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_63_1_ha0.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_64_1_aHa.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_65_1_6sb.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_66_1_8gi.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_67_1_LSX.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_68_1_Udj.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_69_1_Jxy.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_6_1_HQY.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_6_1_wsM.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_70_1_tfl.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_71_1_8QE.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_72_1_ZHQ.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_72_1_oQV.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_73_1_YIi.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_73_1_gjC.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_74_1_4RL.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_74_1_bmO.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_7_1_A5Z.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_8_1_Tha.root',
'/store/user/gebbert/PhotonHad/photonJetSelection_PhotonHadTrigger_V31_v1/cc8aca7f0b10ddc2bee1e329daf3f4d6/photonJetSelection_9_1_f1u.root',

	)
		                   
	)
        
