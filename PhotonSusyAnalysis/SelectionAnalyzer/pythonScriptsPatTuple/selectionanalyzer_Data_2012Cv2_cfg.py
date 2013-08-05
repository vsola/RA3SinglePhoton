####################################CONFIGURATION##################################
###################################################################################

###SAMPLE###
# Data, 8TeV ======10

sampleConf = 10
dataConf   = 6


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
    '/store/user/vsola/PhotonHad/photonJetSelection_Cv2_V02NoJSON//e72d55eb677450000f944cdd0d28aeed/photonJetSelection_99_1_UWu.root'
    )
   )
        
