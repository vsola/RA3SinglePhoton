####################################CONFIGURATION##################################
###################################################################################

###SAMPLE###
#Fall 10MC, 7TeV ======9
#Data, 7TeV ======10

sampleConf = 10


#####################################################################################
#################################################
import FWCore.ParameterSet.Config as cms

process = cms.Process("PhotonJetSelectionFromPat")
process.TFileService = cms.Service("TFileService", fileName = cms.string("histo.root") )

test=False
debug=True
import PhotonSusyAnalysis.SelectionAnalyzer.selectionanalyzer_multi_cfg as baseConfig
doSkimming=False
doAnalysis=True
noKinematicPresel=False
PUDistributionMC=cms.vdouble(0)
baseConfig.getProcessFor(sampleConf,process,test,doSkimming,doAnalysis,"",noKinematicPresel,PUDistributionMC,0)

process.source = cms.Source("PoolSource",
	    	fileNames = cms.untracked.vstring(

'/store/user/vsola/PhotonHad/photonJetSelection_B_V01NoJSON/9b8ea4fcca63d826ba9b43308235ddc8/photonJetSelection_9_1_9s4.root'
	)
		                   
	)
        
