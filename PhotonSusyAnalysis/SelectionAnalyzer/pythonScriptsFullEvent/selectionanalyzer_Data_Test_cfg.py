####################################CONFIGURATION##################################
###################################################################################

###SAMPLE###
sampleConf = 10
dataConf   = 8


#####################################################################################

import FWCore.ParameterSet.Config as cms

process = cms.Process("PhotonJetSelection")
process.TFileService = cms.Service("TFileService", fileName = cms.string("histo.root") )


test = False

import PhotonSusyAnalysis.SelectionAnalyzer.selectionanalyzer_multi_cfg as baseConfig

doSkimming        = True
doAnalysis        = False
noKinematicPresel = False
PUDistributionMC  = cms.vdouble(0)

baseConfig.getProcessFor(sampleConf,process,test,doSkimming,doAnalysis,"",noKinematicPresel,PUDistributionMC,0,dataConf)


process.source = cms.Source( "PoolSource",
                             fileNames = cms.untracked.vstring(
    '/store/data/Run2012A/PhotonHad/AOD/22Jan2013-v1/30000/D2964E14-DD81-E211-A02D-00215E2222E0.root'
    )
)


