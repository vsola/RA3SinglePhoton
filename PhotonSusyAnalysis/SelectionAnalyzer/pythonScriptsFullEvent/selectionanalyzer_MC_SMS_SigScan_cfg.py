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
process.TFileService = cms.Service("TFileService", fileName = cms.string("histo.root") )

test=False
import PhotonSusyAnalysis.SelectionAnalyzer.selectionanalyzer_multi_cfg as baseConfig
doSkimming=True
doAnalysis=True
fileAppendix=""
noKinematicPresel=False
PUDistributionMC=0
PUDistributionData=0
baseConfig.getProcessFor(sampleConf,process,test,doSkimming,doAnalysis,fileAppendix,noKinematicPresel,PUDistributionMC,PUDistributionData)


########Set path to local MC sets
process.source = cms.Source("PoolSource",
	    	fileNames = cms.untracked.vstring(
	  '/store/mc/Summer11/SMS-T1gg_Mgluino-400to2000_mNLSP-100-1975_7TeV-Pythia6Z/AODSIM/PU_START42_V11_FastSim-v2/0001/84649FB4-B7BF-E011-9AAA-00266CFAEBA0.root',
	 '/store/mc/Summer11/SMS-T1lg_Mgluino-400to2000_mLSP-100to1875_7TeV-Pythia6Z/AODSIM/PU_START42_V11_FastSim-v3/0002/00090213-C8CD-E011-9DE3-00266CF3336C.root',
       '/store/mc/Summer11/SMS-T1lg_Mgluino-400to2000_mLSP-100to1875_7TeV-Pythia6Z/AODSIM/PU_START42_V11_FastSim-v3/0002/002DD0A0-29CE-E011-AA01-0030487DA061.root',
       '/store/mc/Summer11/SMS-T1lg_Mgluino-400to2000_mLSP-100to1875_7TeV-Pythia6Z/AODSIM/PU_START42_V11_FastSim-v3/0002/002FDC70-C9CD-E011-9AA9-0025901D4C3C.root',
       '/store/mc/Summer11/SMS-T1lg_Mgluino-400to2000_mLSP-100to1875_7TeV-Pythia6Z/AODSIM/PU_START42_V11_FastSim-v3/0002/00480B5C-FACD-E011-B3CA-0030487F1BD5.root',
       '/store/mc/Summer11/SMS-T1lg_Mgluino-400to2000_mLSP-100to1875_7TeV-Pythia6Z/AODSIM/PU_START42_V11_FastSim-v3/0002/0060FD0B-C8CD-E011-8284-0025901D4C18.root',
       '/store/mc/Summer11/SMS-T1lg_Mgluino-400to2000_mLSP-100to1875_7TeV-Pythia6Z/AODSIM/PU_START42_V11_FastSim-v3/0002/007D73E3-0CCE-E011-9B45-002481E1512E.root',
       '/store/mc/Summer11/SMS-T1lg_Mgluino-400to2000_mLSP-100to1875_7TeV-Pythia6Z/AODSIM/PU_START42_V11_FastSim-v3/0002/00ABF83A-11CE-E011-BAC7-0025901D4AF0.root',
       '/store/mc/Summer11/SMS-T1lg_Mgluino-400to2000_mLSP-100to1875_7TeV-Pythia6Z/AODSIM/PU_START42_V11_FastSim-v3/0002/00CB9F0D-C8CD-E011-98A0-0025901D4C94.root',
       '/store/mc/Summer11/SMS-T1lg_Mgluino-400to2000_mLSP-100to1875_7TeV-Pythia6Z/AODSIM/PU_START42_V11_FastSim-v3/0002/0232E713-DFCD-E011-9261-003048F0E780.root',
       '/store/mc/Summer11/SMS-T1lg_Mgluino-400to2000_mLSP-100to1875_7TeV-Pythia6Z/AODSIM/PU_START42_V11_FastSim-v3/0002/0271C22E-C8CD-E011-BB56-0025901D4844.root',
       '/store/mc/Summer11/SMS-T1lg_Mgluino-400to2000_mLSP-100to1875_7TeV-Pythia6Z/AODSIM/PU_START42_V11_FastSim-v3/0002/0283009B-29CE-E011-A53D-003048D45FCE.root',
       '/store/mc/Summer11/SMS-T1lg_Mgluino-400to2000_mLSP-100to1875_7TeV-Pythia6Z/AODSIM/PU_START42_V11_FastSim-v3/0002/0299B270-BECD-E011-8025-0025901D4AFE.root',
       '/store/mc/Summer11/SMS-T1lg_Mgluino-400to2000_mLSP-100to1875_7TeV-Pythia6Z/AODSIM/PU_START42_V11_FastSim-v3/0002/02D2ACB4-F6CD-E011-BC45-003048D437BA.root',
       '/store/mc/Summer11/SMS-T1lg_Mgluino-400to2000_mLSP-100to1875_7TeV-Pythia6Z/AODSIM/PU_START42_V11_FastSim-v3/0002/02D5B79C-F6CD-E011-A06D-003048D43726.root',
       '/store/mc/Summer11/SMS-T1lg_Mgluino-400to2000_mLSP-100to1875_7TeV-Pythia6Z/AODSIM/PU_START42_V11_FastSim-v3/0002/02F25B67-33CE-E011-B406-003048CF6336.root',
       '/store/mc/Summer11/SMS-T1lg_Mgluino-400to2000_mLSP-100to1875_7TeV-Pythia6Z/AODSIM/PU_START42_V11_FastSim-v3/0002/02FD024C-10CE-E011-8EF0-0030487D5EA1.root',
       '/store/mc/Summer11/SMS-T1lg_Mgluino-400to2000_mLSP-100to1875_7TeV-Pythia6Z/AODSIM/PU_START42_V11_FastSim-v3/0002/0406925A-F4CD-E011-9975-00266CF3336C.root',
       '/store/mc/Summer11/SMS-T1lg_Mgluino-400to2000_mLSP-100to1875_7TeV-Pythia6Z/AODSIM/PU_START42_V11_FastSim-v3/0002/045AD042-BBCD-E011-B26C-003048F0E1EE.root',
       '/store/mc/Summer11/SMS-T1lg_Mgluino-400to2000_mLSP-100to1875_7TeV-Pythia6Z/AODSIM/PU_START42_V11_FastSim-v3/0002/04B3C5F4-DDCD-E011-AA8D-00266CF32FA0.root',

	
	),
	skipEvents=cms.untracked.uint32(0)
		    
		                   
	)

#Signal MC
process.weightProducer.Method=cms.string("")
process.weightProducer.XS = cms.double(1)
process.weightProducer.NumberEvts = cms.double(1)
process.weightProducer.Lumi = cms.double(1.)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )


process.schedule = cms.Schedule(process.selectionSequence,process.eRmAll)
