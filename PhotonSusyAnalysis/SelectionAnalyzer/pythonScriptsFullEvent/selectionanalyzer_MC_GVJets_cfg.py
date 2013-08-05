####################################CONFIGURATION##################################
###################################################################################

###SAMPLE###
sampleConf = 9


#####################################################################################
#################################################
import FWCore.ParameterSet.Config as cms

process              = cms.Process("PhotonJetSelection")
process.TFileService = cms.Service("TFileService", fileName = cms.string("histo.root") )

test = False
import PhotonSusyAnalysis.SelectionAnalyzer.selectionanalyzer_multi_cfg as baseConfig
doSkimming        = True
doAnalysis        = True
noKinematicPresel = False
PUDistributionMC  = cms.vdouble(0)
baseConfig.getProcessFor(sampleConf,process,test,doSkimming,doAnalysis,"",noKinematicPresel,PUDistributionMC,0)

#GVJets MC
process.weightProducer.Method     = cms.string("Constant")
process.weightProducer.XS         = cms.double(211.4)
process.weightProducer.NumberEvts = cms.double(14551998)
process.weightProducer.Lumi       = cms.double(100.)

process.source = cms.Source("PoolSource",
	    	fileNames = cms.untracked.vstring(
    '/store/mc/Summer12_DR53X/GVJets_Incl_8TeV-madgraph/AODSIM/PU_S10_START53_V7C-v1/00000/000950B2-D332-E211-B830-003048678B08.root',
    '/store/mc/Summer12_DR53X/GVJets_Incl_8TeV-madgraph/AODSIM/PU_S10_START53_V7C-v1/00000/008D378E-CD32-E211-AE85-00261894382D.root'
    )
)
        
