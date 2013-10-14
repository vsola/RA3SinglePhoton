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
doAnalysis        = False
noKinematicPresel = False
PUDistributionMC  = cms.vdouble(0)
baseConfig.getProcessFor(sampleConf,process,test,doSkimming,doAnalysis,"",noKinematicPresel,PUDistributionMC,0)

#QCD
#process.weightProducer.Method=cms.string("PtHat")
process.weightProducer.Method     = cms.string("Constant")
process.weightProducer.XS         = cms.double(204)
process.weightProducer.NumberEvts = cms.double(13843863)
process.weightProducer.Lumi       = cms.double(100.)

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(        
    '/store/mc/Summer12_DR53X/QCD_HT-1000ToInf_TuneZ2star_8TeV-madgraph-pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/140514DC-F60C-E211-9458-008CFA00206C.root',
    '/store/mc/Summer12_DR53X/QCD_HT-1000ToInf_TuneZ2star_8TeV-madgraph-pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/1416CBEB-4A0E-E211-B79B-0024E87699B3.root'
    )
)
