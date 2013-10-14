####################################CONFIGURATION##################################
###################################################################################

###SAMPLE###
sampleConf = 9


#####################################################################################
#################################################
import FWCore.ParameterSet.Config as cms

process              = cms.Process("PhotonJetSelection")
process.TFileService = cms.Service("TFileService", fileName = cms.string("histo.root") )

test = False
import PhotonSusyAnalysis.SelectionAnalyzer.selectionanalyzer_multi_cfg as baseConfig
doSkimming        = True
doAnalysis        = True
noKinematicPresel = False
PUDistributionMC  = cms.vdouble(0)
baseConfig.getProcessFor(sampleConf,process,test,doSkimming,doAnalysis,"",noKinematicPresel,PUDistributionMC,0)

#TTBar MC
process.weightProducer.Method     = cms.string("Constant")
process.weightProducer.XS         = cms.double(1.444)
process.weightProducer.NumberEvts = cms.double(1719954)
process.weightProducer.Lumi       = cms.double(100.)

process.source = cms.Source("PoolSource",
	    	fileNames = cms.untracked.vstring(
    '/store/mc/Summer12_DR53X/TTGJets_8TeV-madgraph/AODSIM/PU_S10_START53_V19-v1/10000/02D25ABD-18E4-E211-A70C-0025907FD2B6.root'
    )
)
