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
process.TFileService = cms.Service("TFileService", fileName = cms.string("CONDOR_OUTPUTFILENAME") )

test=False
import PhotonSusyAnalysis.SelectionAnalyzer.selectionanalyzer_multi_cfg as baseConfig
doSkimming=True
doAnalysis=True
fileAppendix="CONDOR_FILEAPP"
noKinematicPresel=False
PUDistributionMC=0
PUDistributionData=0
baseConfig.getProcessFor(sampleConf,process,test,doSkimming,doAnalysis,fileAppendix,noKinematicPresel,PUDistributionMC,PUDistributionData)


########Set path to local MC sets
process.source = cms.Source("PoolSource",
	    	fileNames = cms.untracked.vstring(
	    	
	'dcap:///pnfs/cms/WAX/11/store/user/lpcpjm/PrivateMC/FastSim/binolikegrid2/gen/fastsim_1440_1520_375.root',      
	
	),
	skipEvents=cms.untracked.uint32(CONDOR_SKIPEVENTS)
		    
		                   
	)

#Signal MC
process.weightProducer.Method=cms.string("Constant")
process.weightProducer.XS = cms.double(1)
process.weightProducer.NumberEvts = cms.double(1)
process.weightProducer.Lumi = cms.double(1.)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(CONDOR_MAXEVENTS) )


process.schedule = cms.Schedule(process.selectionSequence)
