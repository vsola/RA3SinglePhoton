####################################CONFIGURATION##################################
###################################################################################

###SAMPLE###
#Fall 10MC, 7TeV ======9
#Data, 7TeV ======10

sampleConf = 10


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
baseConfig.getProcessFor(sampleConf,process,test,doSkimming,doAnalysis,"",noKinematicPresel,PUDistributionMC,0)


process.source = cms.Source("PoolSource",
	    	fileNames = cms.untracked.vstring(
	    	'/store/user/gebbert/PhotonSusyAnalysisPickedEvents/PickEvents_Dec8_PhotonHad_PromptReco_B/pickevents_1_1_Lnz.root',
			'/store/user/gebbert/PhotonSusyAnalysisPickedEvents/PickEvents_Dec8_PhotonHad_PromptReco_v4/pickevents_1_1_Hwq.root',
			'/store/user/gebbert/PhotonSusyAnalysisPickedEvents/PickEvents_Dec8_PhotonHad_PromptReco_v6/pickevents_1_1_pxB.root',
			'/store/user/gebbert/PhotonSusyAnalysisPickedEvents/PickEvents_Dec8_PhotonHad_RerecoAug/pickevents_1_1_zCK.root',

	 
	   	
	
	)
		                   
	)


