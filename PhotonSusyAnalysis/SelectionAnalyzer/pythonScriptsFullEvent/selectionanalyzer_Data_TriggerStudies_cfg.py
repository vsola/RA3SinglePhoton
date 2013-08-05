####################################CONFIGURATION##################################
###################################################################################

###SAMPLE###
sampleConf = 10


#####################################################################################
#################################################
import FWCore.ParameterSet.Config as cms

process = cms.Process("PhotonJetSelection")
process.TFileService = cms.Service("TFileService", fileName = cms.string("histo.root") )


test=False
import PhotonSusyAnalysis.SelectionAnalyzer.selectionanalyzer_multi_cfg as baseConfig
doSkimming=False
doAnalysis=False
noKinematicPresel=False
PUDistributionMC=cms.vdouble(0)
baseConfig.getProcessFor(sampleConf,process,test,doSkimming,doAnalysis,"",noKinematicPresel,PUDistributionMC,0)


process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
    '/store/data/Run2012A/Photon/AOD/PromptReco-v1/000/190/456/08529E04-F980-E111-8F8B-0030486733B4.root',
    '/store/data/Run2012A/Photon/AOD/PromptReco-v1/000/190/450/3CC2524E-ED80-E111-BCFB-BCAEC518FF52.root',
    '/store/data/Run2012A/Photon/AOD/PromptReco-v1/000/190/456/34F8313E-FF80-E111-836F-5404A63886D2.root',
    '/store/data/Run2012A/Photon/AOD/PromptReco-v1/000/190/456/3E125AF6-FA80-E111-B9E7-002481E0CC00.root'
    )
)


