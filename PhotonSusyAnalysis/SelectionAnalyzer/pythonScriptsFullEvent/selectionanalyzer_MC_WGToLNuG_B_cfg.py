################################## CONFIGURATION ##################################
###################################################################################

### SAMPLE ###
sampleConf = 9


###################################################################################
###################################################################################
import FWCore.ParameterSet.Config as cms

process = cms.Process("PhotonJetSelection")
process.TFileService = cms.Service("TFileService", fileName = cms.string("histo.root") )

test = False

import PhotonSusyAnalysis.SelectionAnalyzer.selectionanalyzer_multi_cfg as baseConfig
doSkimming        = True
doAnalysis        = True
noKinematicPresel = False
PUDistributionMC  = cms.vdouble(0)
baseConfig.getProcessFor(sampleConf,process,test,doSkimming,doAnalysis,"",noKinematicPresel,PUDistributionMC,0)

process.weightProducer.Method = cms.string("Constant")
process.weightProducer.XS     = cms.double(0.2571)
process.weightProducer.NumberEvts = cms.double(471458)
process.weightProducer.Lumi   = cms.double(100.)

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
    '/store/mc/Summer12_DR53X/WGToLNuG_PtG-130_8TeV-madgraph-pythia6_tauola/AODSIM/PU_S10_START53_V7A-v1/00000/00A4302D-E624-E211-BD57-00215E21DAAA.root'
    )
)

			
