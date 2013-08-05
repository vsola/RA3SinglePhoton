import FWCore.ParameterSet.Config as cms

selectedPhotonsWithRhoAndIsos = cms.EDProducer('PFPhotonIsoProducer',

#   process.load("EGamma.EGammaAnalysisTools.photonIsoProducer_cfi")

    Photons      = cms.InputTag('selectedPhotonsWithRho'),
#   Electrons    = cms.InputTag('selectedPatElectrons'),

    IsoDepPhoton = cms.VInputTag( cms.InputTag('phPFIsoDepositChargedPFIso'),
                                  cms.InputTag('phPFIsoDepositGammaPFIso'),
                                  cms.InputTag('phPFIsoDepositNeutralPFIso') ),

    IsoValPhoton = cms.VInputTag( cms.InputTag('phPFIsoValueCharged03PFIdPFIso'),
                                  cms.InputTag('phPFIsoValueGamma03PFIdPFIso'),
                                  cms.InputTag('phPFIsoValueNeutral03PFIdPFIso') )

)
