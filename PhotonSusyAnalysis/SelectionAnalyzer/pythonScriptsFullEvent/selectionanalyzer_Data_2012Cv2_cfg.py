####################################CONFIGURATION##################################
###################################################################################

###SAMPLE###
sampleConf = 10
dataConf = 6


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
baseConfig.getProcessFor(sampleConf,process,test,doSkimming,doAnalysis,"",noKinematicPresel,PUDistributionMC,0,dataConf)


process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
    '/store/data/Run2012A/PhotonHad/AOD/PromptReco-v1/000/191/187/FA6C43DA-1587-E111-848D-001D09F292D1.root',
    '/store/data/Run2012A/PhotonHad/AOD/PromptReco-v1/000/190/592/C2CBBFFC-3682-E111-8795-001D09F252DA.root',
    )
)


