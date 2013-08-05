####################################CONFIGURATION##################################
###################################################################################

###SAMPLE###
#Data, 8TeV ======10

sampleConf = 10
dataConf = 2

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
                 '/store/data/Run2012A/PhotonHad/AOD/13Jul2012-v1/00000/0086FBB4-85CE-E111-BEBB-E41F131817F8.root',
                 '/store/data/Run2012B/PhotonHad/AOD/13Jul2012-v1/00000/00615A62-8DD0-E111-91A6-00215E2222D4.root'
                )
               )


