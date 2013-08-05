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
noKinematicPresel=True
PUDistributionMC=cms.vdouble(0)
baseConfig.getProcessFor(sampleConf,process,test,doSkimming,doAnalysis,"",noKinematicPresel,PUDistributionMC,0)


process.source = cms.Source("PoolSource",
	    	fileNames = cms.untracked.vstring(
	    	
		'/store/data/Run2011A/PhotonHad/AOD/PromptReco-v1/000/161/312/E0B76E4E-7959-E011-A03F-0030487C7E18.root',
        '/store/data/Run2011A/PhotonHad/AOD/PromptReco-v1/000/161/312/D827F860-F457-E011-9B6B-003048F117B6.root',
        '/store/data/Run2011A/PhotonHad/AOD/PromptReco-v1/000/161/312/D2AA8D68-0258-E011-8123-003048F024DE.root',
        '/store/data/Run2011A/PhotonHad/AOD/PromptReco-v1/000/161/311/86773789-D557-E011-96B5-001D09F26509.root',
        '/store/data/Run2011A/PhotonHad/AOD/PromptReco-v1/000/161/311/561BE34B-DF57-E011-A176-001D09F25438.root',
        '/store/data/Run2011A/PhotonHad/AOD/PromptReco-v1/000/161/311/1ACE709E-5A58-E011-B17A-0030487CD716.root',
        '/store/data/Run2011A/PhotonHad/AOD/PromptReco-v1/000/161/310/4E6D4C80-7859-E011-BC4E-003048F1110E.root',
        '/store/data/Run2011A/PhotonHad/AOD/PromptReco-v1/000/161/305/82A48CC2-1E57-E011-9D39-000423D987E0.root',
        '/store/data/Run2011A/PhotonHad/AOD/PromptReco-v1/000/161/303/6CB9AE9A-2057-E011-B421-003048F1C58C.root',
        '/store/data/Run2011A/PhotonHad/AOD/PromptReco-v1/000/161/301/10FDCF62-1D57-E011-8EFE-003048F1C832.root',
        '/store/data/Run2011A/PhotonHad/AOD/PromptReco-v1/000/161/233/80C322BC-6757-E011-ABE1-001D09F24498.root',
        '/store/data/Run2011A/PhotonHad/AOD/PromptReco-v1/000/161/224/9C7EE6B8-B756-E011-8CA2-001617C3B5D8.root',
        '/store/data/Run2011A/PhotonHad/AOD/PromptReco-v1/000/161/223/C6C3B1B5-095A-E011-A78B-003048F11CF0.root',
        '/store/data/Run2011A/PhotonHad/AOD/PromptReco-v1/000/161/222/FC97B770-0557-E011-B4BD-003048F118E0.root',
        '/store/data/Run2011A/PhotonHad/AOD/PromptReco-v1/000/161/217/82C1B000-0B5A-E011-9BB9-003048F1110E.root',
        '/store/data/Run2011A/PhotonHad/AOD/PromptReco-v1/000/161/217/607AF762-0A57-E011-B1B0-003048F1BF66.root',
        '/store/data/Run2011A/PhotonHad/AOD/PromptReco-v1/000/161/217/528DBD66-1857-E011-806C-003048CFB40C.root',
	    
	 	'/store/data/Run2010A/EG/AOD/Dec22ReReco_v1/0027/FE4C850F-2910-E011-B943-003048C692FE.root',
        '/store/data/Run2010A/EG/AOD/Dec22ReReco_v1/0027/FE167D38-2510-E011-ADDC-0030487E4EB9.root',
        '/store/data/Run2010A/EG/AOD/Dec22ReReco_v1/0027/FCF2FB6A-2110-E011-9204-003048C69408.root',
        '/store/data/Run2010A/EG/AOD/Dec22ReReco_v1/0027/FCEE1124-2910-E011-8E9E-0030487D5E53.root',
        '/store/data/Run2010A/EG/AOD/Dec22ReReco_v1/0027/FCC71DE5-2810-E011-B07D-0030487E4B8F.root',
        '/store/data/Run2010A/EG/AOD/Dec22ReReco_v1/0027/FCB21A39-2910-E011-99F0-003048C693BA.root',
        '/store/data/Run2010A/EG/AOD/Dec22ReReco_v1/0027/FC379B11-2310-E011-AF78-003048C693D0.root',
        '/store/data/Run2010A/EG/AOD/Dec22ReReco_v1/0027/FC336E0B-2810-E011-ABD0-0030487DA061.root',
        '/store/data/Run2010A/EG/AOD/Dec22ReReco_v1/0027/FC3066E8-2810-E011-B9C2-003048D43944.root',
	    	
	
	)
		                   
	)


