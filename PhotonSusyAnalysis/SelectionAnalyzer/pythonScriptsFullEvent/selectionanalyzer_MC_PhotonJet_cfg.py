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
noKinematicPresel=False
PUDistributionMC=cms.vdouble(0)
baseConfig.getProcessFor(sampleConf,process,test,doSkimming,doAnalysis,"",noKinematicPresel,PUDistributionMC,0)

#PhotonJet
process.weightProducer.Method=cms.string("Constant")
process.weightProducer.XS = cms.double(107.5)
process.weightProducer.NumberEvts = cms.double(1611963)
process.weightProducer.Lumi = cms.double(100.)


process.source = cms.Source("PoolSource",
	    	fileNames = cms.untracked.vstring(
	    	
	    	'/store/mc/Summer12/GJets_HT-400ToInf_8TeV-madgraph/AODSIM/PU_S7_START52_V9-v1/0000/0027ABB1-6E93-E111-81F3-0026189438A9.root',
	    	'/store/mc/Summer12/GJets_HT-400ToInf_8TeV-madgraph/AODSIM/PU_S7_START52_V9-v1/0000/02F533A9-7393-E111-99C7-001A9281172A.root'
	
	)
		                   
	)