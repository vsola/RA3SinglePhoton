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

#TTBar MC
process.weightProducer.Method=cms.string("Constant")
process.weightProducer.XS = cms.double(136.3)
process.weightProducer.NumberEvts = cms.double(6736135)
process.weightProducer.Lumi = cms.double(100.)

process.source = cms.Source("PoolSource",
	    	fileNames = cms.untracked.vstring(
	'/store/mc/Summer12/TTJets_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S7_START52_V9-v1/0000/FE1EB375-B490-E111-8608-001A92810AA2.root',
	'/store/mc/Summer12/TTJets_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S7_START52_V9-v1/0000/FE13DD4B-A690-E111-BE35-003048FFD7BE.root'
 		
	)
		                   
	)
        
