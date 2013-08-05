####################################CONFIGURATION##################################
###################################################################################

###SAMPLE###
# Data, 8TeV ====== 10

sampleConf = 10
dataConf   = 1


#####################################################################################

import FWCore.ParameterSet.Config as cms

process = cms.Process("PhotonJetSelectionFromPat")
process.TFileService = cms.Service("TFileService", fileName = cms.string("histo.root") )

test=False
import PhotonSusyAnalysis.SelectionAnalyzer.selectionanalyzer_multi_cfg as baseConfig
doSkimming=False
doAnalysis=True
noKinematicPresel=False
PUDistributionMC=cms.vdouble(0)
baseConfig.getProcessFor(sampleConf,process,test,doSkimming,doAnalysis,"",noKinematicPresel,PUDistributionMC,0,dataConf)

process.source = cms.Source( "PoolSource",
                             fileNames = cms.untracked.vstring(
    '/store/user/vsola/PhotonHad/photonJetSel_2012A_V07/13095b8363e254c8f42e8c440e197126/photonJetSelection_101_1_Xln.root'
    )
   )
        
