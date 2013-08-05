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
process.weightProducer.XS     = cms.double(1.17)
process.weightProducer.NumberEvts = cms.double(1135698)
process.weightProducer.Lumi   = cms.double(100.)

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
    '/store/mc/Summer12_DR53X/WGToLNuG_PtG-50-130_8TeV-madgraph/AODSIM/PU_S10_START53_V7C-v1/20000/283E978D-438E-E211-8B78-00304866C398.root'
    )
)

			
