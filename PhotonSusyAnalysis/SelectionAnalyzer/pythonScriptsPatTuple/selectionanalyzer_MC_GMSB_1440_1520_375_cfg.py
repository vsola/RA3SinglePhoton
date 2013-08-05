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
process.TFileService = cms.Service("TFileService", fileName = cms.string("histo1440_1520.root") )

test=False
import PhotonSusyAnalysis.SelectionAnalyzer.selectionanalyzer_multi_cfg as baseConfig
doSkimming=False
doAnalysis=True
fileAppendix="1440_1520"
noKinematicPresel=False
PUDistributionMC=cms.vdouble(0.0688419,0.070276,0.071531,0.0656149,0.0693797,0.0722481,0.0692004,0.0690211,0.0708139,0.0681248,0.0657942,0.0650771,0.0537828,0.0381858,0.0310147,0.0202582,0.013625,0.00717103,0.00537827,0.00215131,0.00125493,0.000179276,0.000537827,0.000179276,0.000358552)
baseConfig.getProcessFor(sampleConf,process,test,doSkimming,doAnalysis,fileAppendix,noKinematicPresel,PUDistributionMC,0)


########Set path to local MC sets
process.source = cms.Source("PoolSource",
	    	fileNames = cms.untracked.vstring(
	    	
	    	'file:GMSBScan/photonJetSelection1440_1520.root'
	
	)
	
		                   
	)

#Signal MC
process.weightProducer.Method=cms.string("Constant")
process.weightProducer.XS = cms.double(1)
process.weightProducer.NumberEvts = cms.double(1)
process.weightProducer.Lumi = cms.double(1.)

process.GlobalTag.globaltag = 'START42_V12::All'
#'START42_V9::All'
