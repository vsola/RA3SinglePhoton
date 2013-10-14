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


process.weightProducer.Method     = cms.string("Constant")
process.weightProducer.XS         = cms.double(107.5)
#process.weightProducer.NumberEvts = cms.double(9539562)
process.weightProducer.NumberEvts = cms.double(42391678)
process.weightProducer.Lumi       = cms.double(100.)

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
    '/store/mc/Summer12_DR53X/GJets_HT-400ToInf_8TeV-madgraph_v2/AODSIM/PU_S10_START53_V7A-v1/00000/002B2787-9B15-E211-A06F-0030486790B0.root',
    '/store/mc/Summer12_DR53X/GJets_HT-400ToInf_8TeV-madgraph_v2/AODSIM/PU_S10_START53_V7A-v1/00000/007419CB-A815-E211-9067-003048678FB2.root'
    )
)
