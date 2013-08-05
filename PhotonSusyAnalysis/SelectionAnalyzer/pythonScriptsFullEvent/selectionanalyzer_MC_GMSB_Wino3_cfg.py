####################################CONFIGURATION##################################
###################################################################################

###SAMPLE###
#Fall 10MC, 7TeV ======9
#Data, 7TeV ======10

sampleConf = 9


#####################################################################################
#################################################
import FWCore.ParameterSet.Config as cms

process = cms.Process("PhotonJetSelection")
process.TFileService = cms.Service("TFileService", fileName = cms.string("histoSkimGGMWino3.root") )

test=False
import PhotonSusyAnalysis.SelectionAnalyzer.selectionanalyzer_multi_cfg as baseConfig
doSkimming=True
doAnalysis=True
fileAppendix="GGM_Wino3"
noKinematicPresel=False
PUDistributionMC=cms.vdouble(0)
baseConfig.getProcessFor(sampleConf,process,test,doSkimming,doAnalysis,fileAppendix,noKinematicPresel,PUDistributionMC,0)


########Set path to local MC sets
process.source = cms.Source("PoolSource",
	    	fileNames = cms.untracked.vstring(
	    	
	    	'dcap:///pnfs/cms/WAX/11/store/user/lpcpjm/PrivateMC/FastSim/winolikegrid2/gen/fastsim_1600_800_375.root',
	
	
	)
		                   
	)

#Signal MC
process.weightProducer.Method=cms.string("Constant")
process.weightProducer.XS = cms.double(0.05499)
process.weightProducer.NumberEvts = cms.double(10000)
process.weightProducer.Lumi = cms.double(100.)
