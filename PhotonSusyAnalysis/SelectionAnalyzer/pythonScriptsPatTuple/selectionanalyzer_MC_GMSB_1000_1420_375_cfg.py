####################################CONFIGURATION##################################
###################################################################################

###SAMPLE###
sampleConf = 9


#####################################################################################

import FWCore.ParameterSet.Config as cms

process = cms.Process("PhotonJetSelection")
process.TFileService = cms.Service("TFileService", fileName = cms.string("histoSkimGGM_Bino_1000_1420.root") )

test=False

import PhotonSusyAnalysis.SelectionAnalyzer.selectionanalyzer_multi_cfg as baseConfig

doSkimming        = True
doAnalysis        = True
noKinematicPresel = False

fileAppendix      = "GGM_Bino_1000_1420"

PUDistributionMC  = cms.vdouble(0)


baseConfig.getProcessFor(sampleConf,process,test,doSkimming,doAnalysis,fileAppendix,noKinematicPresel,PUDistributionMC,0)


########Set path to local MC sets

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
    '/store/user/vsola/Spectra_gsq_B/fastsim_1000_1420_375.root'
    )
)

#Signal MC
process.weightProducer.Method     = cms.string("Constant")
process.weightProducer.XS         = cms.double(0.0439)
process.weightProducer.NumberEvts = cms.double(10000)
process.weightProducer.Lumi       = cms.double(100.)
