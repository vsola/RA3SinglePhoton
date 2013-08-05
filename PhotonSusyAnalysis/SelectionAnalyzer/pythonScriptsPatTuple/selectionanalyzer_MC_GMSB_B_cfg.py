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
process.TFileService = cms.Service("TFileService", fileName = cms.string("histoGMSBB.root") )

test=False
import PhotonSusyAnalysis.SelectionAnalyzer.selectionanalyzer_multi_cfg as baseConfig
doSkimming=False
doAnalysis=True
fileAppendix="GMSBB"
noKinematicPresel=False
PUDistributionMC=0
baseConfig.getProcessFor(sampleConf,process,test,doSkimming,doAnalysis,fileAppendix,noKinematicPresel,PUDistributionMC,0)
########Set path to local MC sets
process.source = cms.Source("PoolSource",
	    	fileNames = cms.untracked.vstring(
	    	
	'file:GGMSamplePoints/photonJetSelectionGGMB.root'
	
	)
		                   
	)

#Signal MC
process.weightProducer.Method=cms.string("")
process.weightProducer.XS = cms.double(0.0068)
process.weightProducer.NumberEvts = cms.double(8415)
process.weightProducer.Lumi = cms.double(100.)

process.GlobalTag.globaltag = 'START42_V12::All'