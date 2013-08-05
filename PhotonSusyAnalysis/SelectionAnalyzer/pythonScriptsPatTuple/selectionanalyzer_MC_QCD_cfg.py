####################################CONFIGURATION##################################
###################################################################################

###SAMPLE###
#Fall 10MC, 7TeV ======9
#Data, 7TeV ======10

sampleConf = 9


#####################################################################################
#################################################
import FWCore.ParameterSet.Config as cms

process = cms.Process("PhotonJetSelectionFromPat")
process.TFileService = cms.Service("TFileService", fileName = cms.string("histo.root") )

test=False
import PhotonSusyAnalysis.SelectionAnalyzer.selectionanalyzer_multi_cfg as baseConfig
doSkimming=False
doAnalysis=True
noKinematicPresel=False
##41 bins
PUDistributionMC=cms.vdouble(
    2.344E-05,
    2.344E-05,
    2.344E-05,
    2.344E-05,
    4.687E-04,
    4.687E-04,
    7.032E-04,
    9.414E-04,
    1.234E-03,
    1.603E-03,
    2.464E-03,
    3.250E-03,
    5.021E-03,
    6.644E-03,
    8.502E-03,
    1.121E-02,
    1.518E-02,
    2.033E-02,
    2.608E-02,
    3.171E-02,
    3.667E-02,
    4.060E-02,
    4.338E-02,
    4.520E-02,
    4.641E-02,
    4.735E-02,
    4.816E-02,
    4.881E-02,
    4.917E-02,
    4.909E-02,
    4.842E-02,
    4.707E-02,
    4.501E-02,
    4.228E-02,
    3.896E-02,
    3.521E-02,
    3.118E-02,
    2.702E-02,
    2.287E-02,
    1.885E-02,
    1.508E-02,
    1.166E-02,
    8.673E-03,
    6.190E-03,
    4.222E-03,
    2.746E-03,
    1.698E-03,
    9.971E-04,
    5.549E-04,
    2.924E-04,
    1.457E-04,
    6.864E-05,
    3.054E-05,
    1.282E-05,
    5.081E-06,
    1.898E-06,
    6.688E-07,
    2.221E-07,
    6.947E-08,
    2.047E-08
)








PUDistributionDataTrue=cms.vdouble(
0,
2.11776e-06,
8.73346e-07,
8.35477e-06,
0.000683043,
0.00248088,
0.00016079,
0.000261379,
0.00243894,
0.00923758,
0.0197797,
0.0323905,
0.0478973,
0.0655906,
0.0811555,
0.0941737,
0.1045,
0.105639,
0.0944827,
0.0768165,
0.0595288,
0.0455745,
0.0351498,
0.0274396,
0.021701,
0.0173062,
0.0137764,
0.0108557,
0.00842968,
0.00643439,
0.00481868,
0.00353494,
0.00253712,
0.00178015,
0.00122048,
0.000817437,
0.000534764,
0.00034165,
0.000213121,
0.000129771,
7.71098e-05,
4.46973e-05,
2.52674e-05,
1.3926e-05,
7.48131e-06,
3.91686e-06,
1.99826e-06,
9.93308e-07,
4.8108e-07,
2.27012e-07,
1.04372e-07,
0,
0,
0,
0,
0,
0,
0,
0,
0
)
#cms.vdouble(
#0.0583369,0.0675177,0.0600385,0.0656528,0.062719,0.0682874,0.101699,0.0703519,0.0621599,0.0691656,0.0755862,0.0745666,0.0476641,0.0387674,0.0300911,0.0181066,0.0143125,0.0088776,0.00229146,0.00252451,0.00128297,0,0,0,0)
baseConfig.getProcessFor(sampleConf,process,test,doSkimming,doAnalysis,"",noKinematicPresel,PUDistributionMC,PUDistributionDataTrue)

#QCD
process.weightProducer.Method=cms.string("PtHat")
process.weightProducer.XS = cms.double(2.99815997E10)
process.weightProducer.NumberEvts = cms.double(1025622)
process.weightProducer.Lumi = cms.double(100.)



process.source = cms.Source("PoolSource",
	    	fileNames = cms.untracked.vstring(
	    	 
	    #	'file:photonJetSelection.root'
		'/store/user/gebbert/QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/photonJetSelection_V17/9eb0e622dba8674e0363aeef4926baa1/photonJetSelection_76_1_NaT.root',
	    '/store/user/gebbert/QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/photonJetSelection_V16/06869858c73d474ff891c1397072fd77/photonJetSelection_101_1_5vT.root',
'/store/user/gebbert/QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/photonJetSelection_V16/06869858c73d474ff891c1397072fd77/photonJetSelection_102_1_Fnu.root',
'/store/user/gebbert/QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/photonJetSelection_V16/06869858c73d474ff891c1397072fd77/photonJetSelection_103_1_XKo.root',
'/store/user/gebbert/QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/photonJetSelection_V16/06869858c73d474ff891c1397072fd77/photonJetSelection_104_1_sYD.root',
'/store/user/gebbert/QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/photonJetSelection_V16/06869858c73d474ff891c1397072fd77/photonJetSelection_105_1_YLC.root',
'/store/user/gebbert/QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/photonJetSelection_V16/06869858c73d474ff891c1397072fd77/photonJetSelection_106_1_bLV.root',
'/store/user/gebbert/QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/photonJetSelection_V16/06869858c73d474ff891c1397072fd77/photonJetSelection_107_1_S5U.root',
'/store/user/gebbert/QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/photonJetSelection_V16/06869858c73d474ff891c1397072fd77/photonJetSelection_108_1_OzH.root',
'/store/user/gebbert/QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/photonJetSelection_V16/06869858c73d474ff891c1397072fd77/photonJetSelection_109_1_fPr.root',
'/store/user/gebbert/QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/photonJetSelection_V16/06869858c73d474ff891c1397072fd77/photonJetSelection_10_1_p1f.root',
'/store/user/gebbert/QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/photonJetSelection_V16/06869858c73d474ff891c1397072fd77/photonJetSelection_110_1_tfx.root',
'/store/user/gebbert/QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/photonJetSelection_V16/06869858c73d474ff891c1397072fd77/photonJetSelection_111_1_WVr.root',
'/store/user/gebbert/QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/photonJetSelection_V16/06869858c73d474ff891c1397072fd77/photonJetSelection_112_1_dIA.root',
'/store/user/gebbert/QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/photonJetSelection_V16/06869858c73d474ff891c1397072fd77/photonJetSelection_113_1_wmN.root',
'/store/user/gebbert/QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/photonJetSelection_V16/06869858c73d474ff891c1397072fd77/photonJetSelection_114_1_YF9.root',
'/store/user/gebbert/QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/photonJetSelection_V16/06869858c73d474ff891c1397072fd77/photonJetSelection_115_1_adP.root',
'/store/user/gebbert/QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/photonJetSelection_V16/06869858c73d474ff891c1397072fd77/photonJetSelection_116_1_8Lu.root',
'/store/user/gebbert/QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/photonJetSelection_V16/06869858c73d474ff891c1397072fd77/photonJetSelection_117_1_qI1.root',
'/store/user/gebbert/QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/photonJetSelection_V16/06869858c73d474ff891c1397072fd77/photonJetSelection_118_1_hHV.root',
'/store/user/gebbert/QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/photonJetSelection_V16/06869858c73d474ff891c1397072fd77/photonJetSelection_119_1_FP5.root',
'/store/user/gebbert/QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/photonJetSelection_V16/06869858c73d474ff891c1397072fd77/photonJetSelection_11_1_ZNt.root',
'/store/user/gebbert/QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/photonJetSelection_V16/06869858c73d474ff891c1397072fd77/photonJetSelection_120_1_UqF.root',
'/store/user/gebbert/QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/photonJetSelection_V16/06869858c73d474ff891c1397072fd77/photonJetSelection_121_1_KBz.root',
'/store/user/gebbert/QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/photonJetSelection_V16/06869858c73d474ff891c1397072fd77/photonJetSelection_122_1_Iy6.root',
'/store/user/gebbert/QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/photonJetSelection_V16/06869858c73d474ff891c1397072fd77/photonJetSelection_123_1_8Mz.root',
'/store/user/gebbert/QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/photonJetSelection_V16/06869858c73d474ff891c1397072fd77/photonJetSelection_124_1_rtn.root',
'/store/user/gebbert/QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/photonJetSelection_V16/06869858c73d474ff891c1397072fd77/photonJetSelection_125_1_kjF.root',
'/store/user/gebbert/QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/photonJetSelection_V16/06869858c73d474ff891c1397072fd77/photonJetSelection_126_1_IAo.root',
'/store/user/gebbert/QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/photonJetSelection_V16/06869858c73d474ff891c1397072fd77/photonJetSelection_127_1_XjA.root',
'/store/user/gebbert/QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/photonJetSelection_V16/06869858c73d474ff891c1397072fd77/photonJetSelection_128_1_C22.root',
	    
	   
	
	)
		                   
	)

