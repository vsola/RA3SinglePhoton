import FWCore.ParameterSet.Config as cms

#######################################################################
#######################################################################
######## Filters and Modules needed to process 8 TeV Data #############
#######################################################################
#######################################################################


######## Technical Trigger Bits  Data&MC ##############################
from HLTrigger.special.hltPhysicsDeclared_cfi import *
hltPhysicsDeclared.L1GtReadoutRecordTag = 'gtDigis'

######## Not in latest recipe (13.10.2010) ############################
from L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMaskTechTrigConfig_cff import *
from HLTrigger.HLTfilters.hltLevel1GTSeed_cfi import *

######## APPLY only on DATA! ##########################################
bptx = hltLevel1GTSeed.clone()
bptx.L1TechTriggerSeeding     = cms.bool(True)
bptx.L1SeedsLogicalExpression = cms.string('0')

######## PhysDeclared #################################################
physdeclared = cms.EDFilter("HLTHighLevel",
     TriggerResultsTag = cms.InputTag("TriggerResults","","HLT"),
     HLTPaths = cms.vstring('HLT_PhysicsDeclared'), # provide list of HLT paths (or patterns) you want
     eventSetupPathsKey = cms.string(''),           # not empty => use read paths from AlCaRecoTriggerBitsRcd via this key
     andOr = cms.bool(True),                        # how to deal with multiple triggers:
                                                    # True (OR) accept if ANY is true,
                                                    # False (AND) accept if ALL are true
     throw = cms.bool(True)                         # throw exception on unknown path names
 )

######## MinBias BSC###################################################
minBiasBSC_HLT = cms.EDFilter("HLTHighLevel",
     TriggerResultsTag = cms.InputTag("TriggerResults","","HLT"),
     HLTPaths = cms.vstring('HLT_L1Jet6U'),
     eventSetupPathsKey = cms.string(''), # not empty => use read paths from AlCaRecoTriggerBitsRcd via this key
     andOr = cms.bool(True),              # how to deal with multiple triggers
     throw = cms.bool(True)               # throw exception on unknown path names
 )

######## HLT JET15U ###################################################
jet15U_HLT = cms.EDFilter("HLTHighLevel",
     TriggerResultsTag = cms.InputTag("TriggerResults","","HLT"),
     HLTPaths = cms.vstring('HLT_Jet15U'), # provide list of HLT paths (or patterns) you want
     eventSetupPathsKey = cms.string(''),  # not empty => use read paths from AlCaRecoTriggerBitsRcd via this key
     andOr = cms.bool(True),               # how to deal with multiple triggers
     throw = cms.bool(True)                # throw exception on unknown path names
 )

######## HLT HT100U ###################################################
ht100U_HLT_data = cms.EDFilter("HLTHighLevel",
     TriggerResultsTag = cms.InputTag("TriggerResults","","HLT"),
     HLTPaths = cms.vstring('HLT_HT100U'), # provide list of HLT paths (or patterns) you want
     eventSetupPathsKey = cms.string(''),  # not empty => use read paths from AlCaRecoTriggerBitsRcd via this key
     andOr = cms.bool(True),               # how to deal with multiple triggers
     throw = cms.bool(True)                # throw exception on unknown path names
 )

ht100U_HLT_MC = cms.EDFilter("HLTHighLevel",
     TriggerResultsTag = cms.InputTag("TriggerResults","","REDIGI38X"),
     HLTPaths = cms.vstring('HLT_HT100U'), # provide list of HLT paths (or patterns) you want
     eventSetupPathsKey = cms.string(''),  # not empty => use read paths from AlCaRecoTriggerBitsRcd via this key
     andOr = cms.bool(True),               # how to deal with multiple triggers
     throw = cms.bool(True)                # throw exception on unknown path names
 )

######## HLT HT140U ###################################################
ht140U_HLT_data = cms.EDFilter("HLTHighLevel",
     TriggerResultsTag = cms.InputTag("TriggerResults","","HLT"),
     HLTPaths = cms.vstring('HLT_HT150U_v3','HLT_HT140U','HLT_HT100U'), # provide list of HLT paths (or patterns) you want
     eventSetupPathsKey = cms.string(''),  # not empty => use read paths from AlCaRecoTriggerBitsRcd via this key
     andOr = cms.bool(True),               # how to deal with multiple triggers
     throw = cms.bool(False)               # throw exception on unknown path names
 )

ht140U_HLT_MC = cms.EDFilter("HLTHighLevel",
     TriggerResultsTag = cms.InputTag("TriggerResults","","REDIGI38X"),
     HLTPaths = cms.vstring('HLT_HT140U'), # provide list of HLT paths (or patterns) you want
     eventSetupPathsKey = cms.string(''),  # not empty => use read paths from AlCaRecoTriggerBitsRcd via this key
     andOr = cms.bool(True),               # how to deal with multiple triggers
     throw = cms.bool(True)                # throw exception on unknown path names
 )

######## PhotonTriggerSelection for 2010 dataset ######################
photon2010_HLT_data = cms.EDFilter("HLTHighLevel",
     TriggerResultsTag = cms.InputTag("TriggerResults","","HLT"),
     HLTPaths = cms.vstring('HLT_Photon10_Cleaned_L1R','HLT_Photon10_L1R','HLT_Photon15_Cleaned_L1R',
                            'HLT_Photon20_Cleaned_L1R','HLT_Photon20_L1R','HLT_Photon30_Cleaned_L1R',
                            'HLT_Photon30_L1R_8E29','HLT_Photon30_L1R','HLT_Photon35_Isol_Cleaned_L1R_v1',
                            'HLT_Photon40_Isol_Cleaned_L1R_v1','HLT_Photon40_CaloId_Cleaned_L1R_v1'),
                                          # provide list of HLT paths (or patterns) you want
     eventSetupPathsKey = cms.string(''), # not empty => use read paths from AlCaRecoTriggerBitsRcd via this key
     andOr = cms.bool(True),              # how to deal with multiple triggers
     throw = cms.bool(False)              # throw exception on unknown path names
 )

######## PhotonHad Trigger Selection for 2011 dataset #################
photon2011_HLT_data = cms.EDFilter("HLTHighLevel",
     TriggerResultsTag = cms.InputTag("TriggerResults","","HLT"),
     HLTPaths = cms.vstring('HLT_Photon70_*_HT*_v*','HLT_Photon70_CaloIdL_HT400_v*','HLT_Photon70_CaloIdL_HT350_v*',
                            'HLT_Photon70_CaloIdL_HT300_v*','HLT_Photon70_CaloIdL_HT200_v*'),
     eventSetupPathsKey = cms.string(''),
     andOr = cms.bool(True),
     throw = cms.bool(False)
 )

photon2011_HLT_mc = cms.EDFilter("HLTHighLevel",
     TriggerResultsTag = cms.InputTag("TriggerResults","","REDIGI311X"),
     HLTPaths = cms.vstring('HLT_Photon70_CaloIdL_MHT30_v*'),
     eventSetupPathsKey = cms.string(''),
     andOr = cms.bool(True),
     throw = cms.bool(True) 
 )

######## PhotonHad Trigger Selection for 2012 dataset #################
photon2012_HLT_data = cms.EDFilter("HLTHighLevel",
     TriggerResultsTag = cms.InputTag("TriggerResults","","HLT"),
     HLTPaths = cms.vstring('HLT_Photon70_CaloIdXL_PFHT400_v*','HLT_Photon70_CaloIdXL_PFNoPUHT400_v*'),
     eventSetupPathsKey = cms.string(''),
     andOr = cms.bool(True),
     throw = cms.bool(False)
 )

photon2012_HLT_data_triggerEff_Photon60_FJHT300 = cms.EDFilter("HLTHighLevel",
     TriggerResultsTag = cms.InputTag("TriggerResults","","HLT"),
     HLTPaths = cms.vstring('HLT_Photon60_CaloIdL_FJHT300_v*'),
     eventSetupPathsKey = cms.string(''),
     andOr = cms.bool(True),
     throw = cms.bool(False)
 )

photon2012_HLT_data_triggerEff_Photon50 = cms.EDFilter("HLTHighLevel",
     TriggerResultsTag = cms.InputTag("TriggerResults","","HLT"),
     HLTPaths = cms.vstring('HLT_Photon50_CaloIdVL_v*'),
     eventSetupPathsKey = cms.string(''),
     andOr = cms.bool(True),
     throw = cms.bool(False)
 )

photon2012_HLT_data_triggerEff_Photon75 = cms.EDFilter("HLTHighLevel",
     TriggerResultsTag = cms.InputTag("TriggerResults","","HLT"),
     HLTPaths = cms.vstring('HLT_Photon75_CaloIdVL_v*'),
     eventSetupPathsKey = cms.string(''),
     andOr = cms.bool(True),
     throw = cms.bool(False)
 )

photon2012_HLT_data_triggerEff_Photon150 = cms.EDFilter("HLTHighLevel",
     TriggerResultsTag = cms.InputTag("TriggerResults","","HLT"),
     HLTPaths = cms.vstring('HLT_Photon150_v*'),
     eventSetupPathsKey = cms.string(''),
     andOr = cms.bool(True),
     throw = cms.bool(False)
 )

photon2012_HLT_data_triggerEff_PFHT650 = cms.EDFilter("HLTHighLevel",
     TriggerResultsTag = cms.InputTag("TriggerResults","","HLT"),
     HLTPaths = cms.vstring('HLT_PFHT650_v*','HLT_PFNoPUHT650_v*'),
     eventSetupPathsKey = cms.string(''),
     andOr = cms.bool(True),
     throw = cms.bool(False)
 )

photon2012_HLT_data_triggerEff_PFJet40 = cms.EDFilter("HLTHighLevel",
     TriggerResultsTag = cms.InputTag("TriggerResults","","HLT"),
     HLTPaths = cms.vstring('HLT_PFJet40_v*'),
     eventSetupPathsKey = cms.string(''),
     andOr = cms.bool(True),
     throw = cms.bool(False)
 )

photon2012_HLT_data_triggerEff_Mu40 = cms.EDFilter("HLTHighLevel",
     TriggerResultsTag = cms.InputTag("TriggerResults","","HLT"),
     HLTPaths = cms.vstring('HLT_Mu40_v*'),
     eventSetupPathsKey = cms.string(''),
     andOr = cms.bool(True),
     throw = cms.bool(False)
 )

photon2012_HLT_data_triggerEff_IsoMu24 = cms.EDFilter("HLTHighLevel",
     TriggerResultsTag = cms.InputTag("TriggerResults","","HLT"),
     HLTPaths = cms.vstring('HLT_IsoMu24_eta2p1_v*'),
     eventSetupPathsKey = cms.string(''),
     andOr = cms.bool(True),
     throw = cms.bool(False)
 )

photon2012_HLT_data_triggerEff_Ele27 = cms.EDFilter("HLTHighLevel",
     TriggerResultsTag = cms.InputTag("TriggerResults","","HLT"),
     HLTPaths = cms.vstring('HLT_Ele27_WP80_v*'),
     eventSetupPathsKey = cms.string(''),
     andOr = cms.bool(True),
     throw = cms.bool(False)
 )

######## Good vertex ################################################## 
from PhotonSusyAnalysis.GoodVertexNoProducer.goodvertexnoproducer_cfi import oneGoodVertexNoProducer
from PhotonSusyAnalysis.GoodVertexNoProducer.goodvertexfilter_cfi import oneGoodVertexFilter

######## Monster track events #########################################
noScraping= cms.EDFilter("FilterOutScraping",
    applyfilter = cms.untracked.bool(True),
    debugOn = cms.untracked.bool(False), ## Or 'True' to get some per-event info
    numtrack = cms.untracked.uint32(10),
    thresh = cms.untracked.double(0.25)
 )

######## The Good vertices collection needed by the tracking failure filter
goodVertices = cms.EDFilter(
  "VertexSelector",
  filter = cms.bool(False),
  src = cms.InputTag("offlinePrimaryVertices"),
  cut = cms.string("!isFake && ndof > 4 && abs(z) <= 24 && position.rho < 2")
)


#######################################################################
######## MET Filters ##################################################
from JetMETCorrections.Configuration.DefaultJEC_cff import *

######## The tracking failure filter ##################################
from RecoMET.METFilters.trackingFailureFilter_cfi import *
trackingFailureFilter.JetSource = cms.InputTag('ak5PFJetsL2L3Residual')
trackingFailureFilter.taggingMode = cms.bool(True)

######## The tracking POG filters #####################################
from RecoMET.METFilters.trackingPOGFilters_cff import *

######## BE Filter ####################################################
from RecoMET.METFilters.EcalDeadCellBoundaryEnergyFilter_cfi import *
EcalDeadCellBoundaryEnergyFilter.taggingMode = cms.bool(True)
EcalDeadCellBoundaryEnergyFilter.cutBoundEnergyDeadCellsEB=cms.untracked.double(10)
EcalDeadCellBoundaryEnergyFilter.cutBoundEnergyDeadCellsEE=cms.untracked.double(10)
EcalDeadCellBoundaryEnergyFilter.cutBoundEnergyGapEB=cms.untracked.double(100)
EcalDeadCellBoundaryEnergyFilter.cutBoundEnergyGapEE=cms.untracked.double(100)
EcalDeadCellBoundaryEnergyFilter.enableGap=cms.untracked.bool(False)
EcalDeadCellBoundaryEnergyFilter.limitDeadCellToChannelStatusEB = cms.vint32(12,14)
EcalDeadCellBoundaryEnergyFilter.limitDeadCellToChannelStatusEE = cms.vint32(12,14)

from RecoMET.METFilters.eeBadScFilter_cfi import *
eeBadScFilter.taggingMode=cms.bool(True)

######## Event Cleaning ###############################################
print("EventCleaning")

#######################################################################
######## Apply recommended noise cleaning per hand ####################
#######################################################################
######## MET CLEANING RECOMMENDATION STARTS HERE ######################
#######################################################################

# Instead of rejecting the event, add a flag indicating the HBHE noise 

from CommonTools.RecoAlgos.HBHENoiseFilter_cfi import *
HBHENoiseFilter.minIsolatedNoiseSumE = cms.double(999999.)
HBHENoiseFilter.minNumIsolatedNoiseChannels = cms.int32(999999)
HBHENoiseFilter.minIsolatedNoiseSumEt = cms.double(999999.)

from RecoMET.METAnalyzers.CSCHaloFilter_cfi import *

from RecoMET.METFilters.hcalLaserEventFilter_cfi import *
hcalLaserEventFilter.taggingMode = cms.bool(True)

# Reject events with anomalous ECAL laser corrections in 2012A+B 13Jul ReReco
from RecoMET.METFilters.ecalLaserCorrFilter_cfi import *

#######################################################################
######## MET CLEANING RECOMMENDATION ENDS HERE ########################
#######################################################################


#######################################################################
######## DEFINE TRIGGER SEQUENCES #####################################
#######################################################################

applyTechnicalPreselection = cms.Sequence(
    hltPhysicsDeclared*
    oneGoodVertexFilter*
    noScraping*
    oneGoodVertexNoProducer
 )

######## 2012 Data Trigger Selection ##################################
applyTechnicalPreselectionData2010 = cms.Sequence(
    hltPhysicsDeclared*
    oneGoodVertexFilter*
    noScraping*
    HBHENoiseFilter* #ok
    hcalLaserEventFilter*
    goodVertices*
    ak5PFJetsL2L3Residual*
    trackingFailureFilter* #ok
    trkPOGFilters*         #ok
    CSCTightHaloFilter*    #ok
    EcalDeadCellBoundaryEnergyFilter* 
    eeBadScFilter*       #ok
    ecalLaserCorrFilter* #ok
    oneGoodVertexNoProducer*
    photon2012_HLT_data
 )

######## 2012 Selection for Trigger Efficiency ########################
applyTechnicalPreselectionDataTriggerStudies = cms.Sequence(
    hltPhysicsDeclared*
    oneGoodVertexFilter*
    noScraping*
    HBHENoiseFilter*
    hcalLaserEventFilter*
    goodVertices*
    ak5PFJetsL2L3Residual*
    trackingFailureFilter*
    trkPOGFilters*
    CSCTightHaloFilter*
    EcalDeadCellBoundaryEnergyFilter*
    eeBadScFilter*
    ecalLaserCorrFilter*
    oneGoodVertexNoProducer*
#   photon2012_HLT_data_triggerEff_PFHT650
#   photon2012_HLT_data_triggerEff_Photon150
#   photon2012_HLT_data_triggerEff_Photon75
#   photon2012_HLT_data_triggerEff_PFJet40
    photon2012_HLT_data_triggerEff_Mu40
#   photon2012_HLT_data_triggerEff_IsoMu24
#   photon2012_HLT_data_triggerEff_Ele27
 )
    
applyTechnicalPreselectionMC = applyTechnicalPreselection

