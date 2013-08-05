####################################CONFIGURATION##################################
###################################################################################

###SAMPLE###
#Data, 8TeV ======10

sampleConf = 10
dataConf   = 4

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
baseConfig.getProcessFor(sampleConf,process,test,doSkimming,doAnalysis,"",noKinematicPresel,PUDistributionMC,0,dataConf)


process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
                 '/store/data/Run2012C/PhotonHad/AOD/24Aug2012-v1/00000/F8804A6B-B3EE-E111-9D61-00215E21DBFA.root'
                )
               )


