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
#PUDistributionMC=0
#cms.vdouble(0.0632552,0.0733345,0.0649666,0.0716465,0.0703166,0.0704317,0.0742516,0.0755711,0.0636501,0.0754431,0.0649156,0.0630281,0.0521733,0.0356385,0.0301922,0.0200847,0.0160874,0.00907482,0.00218225,0.00261043,0.00114548,0,0,0,0)
baseConfig.getProcessFor(sampleConf,process,test,doSkimming,doAnalysis,"",noKinematicPresel,PUDistributionMC,PUDistributionDataTrue)

#PhotonJet
process.weightProducer.Method=cms.string("Constant")
process.weightProducer.XS = cms.double(107.5)
process.weightProducer.NumberEvts = cms.double(1611963)
process.weightProducer.Lumi = cms.double(100.)


process.source = cms.Source("PoolSource",
	    	fileNames = cms.untracked.vstring(
            '/store/user/mhoffman/GJets_HT-400ToInf_8TeV-madgraph/photonJetSelection_PhotonJet_V39NoJSON/f9ea5cdce6f181773d7e1c80f1cd4040/photonJetSelection_12_1_m17.root',
            '/store/user/mhoffman/GJets_HT-400ToInf_8TeV-madgraph/photonJetSelection_PhotonJet_V39NoJSON/f9ea5cdce6f181773d7e1c80f1cd4040/photonJetSelection_13_1_42K.root'
	     
	    
	)
		                   
	)
