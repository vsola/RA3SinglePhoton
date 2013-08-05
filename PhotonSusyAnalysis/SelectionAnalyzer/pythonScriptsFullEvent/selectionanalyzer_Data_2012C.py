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
#    '/store/data/Run2012C/PhotonHad/AOD/PromptReco-v1/000/198/913/A031D5BA-78CE-E111-90B7-5404A63886B7.root'
    '/store/data/Run2012C/PhotonHad/AOD/PromptReco-v2/000/198/934/16E78B43-AECE-E111-B6DA-003048F1C420.root',
#    '/store/data/Run2012C/PhotonHad/AOD/PromptReco-v2/000/198/939/70DA3656-C1CE-E111-A349-001D09F2B30B.root',
    '/store/data/Run2012C/PhotonHad/AOD/PromptReco-v2/000/198/941/14D61065-6FCF-E111-A8C1-003048D37694.root'
    )
)


