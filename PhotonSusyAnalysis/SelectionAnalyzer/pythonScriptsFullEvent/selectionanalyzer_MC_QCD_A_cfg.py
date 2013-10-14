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
process.weightProducer.XS         = cms.double(276000)
process.weightProducer.NumberEvts = cms.double(27062078)
process.weightProducer.Lumi       = cms.double(100.)

process.source = cms.Source("PoolSource",
            fileNames = cms.untracked.vstring(
    '/store/mc/Summer12_DR53X/QCD_HT-250To500_TuneZ2star_8TeV-madgraph-pythia6/AODSIM/PU_S10_START53_V7A-v1/00002/FE50FBD0-8615-E211-A638-00266CFAE748.root',
    '/store/mc/Summer12_DR53X/QCD_HT-250To500_TuneZ2star_8TeV-madgraph-pythia6/AODSIM/PU_S10_START53_V7A-v1/00002/FE08341E-5315-E211-82B8-008CFA002BB0.root',
    '/store/mc/Summer12_DR53X/QCD_HT-250To500_TuneZ2star_8TeV-madgraph-pythia6/AODSIM/PU_S10_START53_V7A-v1/00002/FCC26B88-9415-E211-A461-848F69FD2484.root',
    '/store/mc/Summer12_DR53X/QCD_HT-250To500_TuneZ2star_8TeV-madgraph-pythia6/AODSIM/PU_S10_START53_V7A-v1/00002/FCB6A707-2215-E211-917E-00266CF9B184.root'
   )
)
