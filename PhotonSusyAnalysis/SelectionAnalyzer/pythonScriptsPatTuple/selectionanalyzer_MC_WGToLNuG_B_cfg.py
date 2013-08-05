####################################CONFIGURATION##################################
###################################################################################

###SAMPLE###
#MC   8TeV ======  9
#Data 8TeV ====== 10

sampleConf = 9

#####################################################################################
#####################################################################################

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
0.,
1.86771e-08,
7.20003e-08,
9.08322e-07,
1.44876e-05,
4.44401e-05,
0.000203518,
0.00147863,
0.00443121,
0.0095692,
0.016919,
0.0274966,
0.040819,
0.0519261,
0.0588805,
0.0638956,
0.0679402,
0.0695252,
0.0682525,
0.0651841,
0.0613764,
0.0575106,
0.0540394,
0.0510695,
0.0481074,
0.0442153,
0.0387861,
0.0319849,
0.0245317,
0.0173119,
0.0111302,
0.00649817,
0.00347492,
0.00173945,
0.000840656,
0.000404096,
0.000196403,
9.64925e-05,
4.75012e-05,
2.3246e-05,
1.12601e-05,
5.38145e-06,
2.52578e-06,
1.15678e-06,
5.13599e-07,
2.19971e-07,
9.06575e-08,
3.59534e-08,
1.3749e-08,
5.08789e-09,
1.32484e-05,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.
)

baseConfig.getProcessFor(sampleConf,process,test,doSkimming,doAnalysis,"",noKinematicPresel,PUDistributionMC,PUDistributionDataTrue)

process.weightProducer.Method = cms.string("Constant")
process.weightProducer.XS     = cms.double(0.2571)
process.weightProducer.NumberEvts = cms.double(471458)
process.weightProducer.Lumi   = cms.double(100.)


process.source = cms.Source("PoolSource",
	    	fileNames = cms.untracked.vstring(
	 '/store/results/susy/8TeV_WGToLNuG_FastSim_525_Summer12-v3/StoreResults-InTimePU_START52_V9-v3/8TeV_WGToLNuG_FastSim_525_Summer12-v3/USER/StoreResults-InTimePU_START52_V9-v3/0000/0009E749-37AB-E111-AFA5-D8D385AF8A16.root'	
         )
)

			
