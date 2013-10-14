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
doAnalysis        = False
noKinematicPresel = False
PUDistributionMC  = cms.vdouble(0)
baseConfig.getProcessFor(sampleConf,process,test,doSkimming,doAnalysis,"",noKinematicPresel,PUDistributionMC,0)

#QCD
#process.weightProducer.Method=cms.string("PtHat")
process.weightProducer.Method     = cms.string("Constant")
process.weightProducer.XS         = cms.double(8426)
process.weightProducer.NumberEvts = cms.double(30599292)
process.weightProducer.Lumi       = cms.double(100.)

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(        
    '/store/mc/Summer12_DR53X/QCD_HT-500To1000_TuneZ2star_8TeV-madgraph-pythia6/AODSIM/PU_S10_START53_V7A-v1/00003/FEFAC8C6-9F25-E211-99A9-00A0D1EE8D7C.root',
    '/store/mc/Summer12_DR53X/QCD_HT-500To1000_TuneZ2star_8TeV-madgraph-pythia6/AODSIM/PU_S10_START53_V7A-v1/00003/FE11BCA1-2826-E211-A803-0024E8768CF3.root'
    )
)
