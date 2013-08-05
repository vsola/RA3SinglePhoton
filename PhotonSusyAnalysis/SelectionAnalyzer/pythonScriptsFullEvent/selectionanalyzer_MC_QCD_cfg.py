####################################CONFIGURATION##################################
###################################################################################

###SAMPLE###
#Fall 10MC, 7TeV ======9
#Data, 7TeV ======10

sampleConf = 9


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

#QCD
process.weightProducer.Method=cms.string("PtHat")
process.weightProducer.XS = cms.double(2.99815997E10)
process.weightProducer.NumberEvts = cms.double(1025622)
process.weightProducer.Lumi = cms.double(100.)

process.source = cms.Source("PoolSource",
            fileNames = cms.untracked.vstring(
            
            '/store/mc/Summer12/QCD_Pt-15to3000_TuneZ2star_Flat_8TeV_pythia6/AODSIM/PU_S7_START52_V9-v5/0000/F8A0ECCC-E098-E111-9407-0030487F1A49.root',
            '/store/mc/Summer12/QCD_Pt-15to3000_TuneZ2star_Flat_8TeV_pythia6/AODSIM/PU_S7_START52_V9-v5/0000/FCE8334B-C098-E111-A8D4-0025904B12FE.root'
            )
    
    )