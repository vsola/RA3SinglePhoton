import FWCore.ParameterSet.Config as cms

selectedPhotonsWithRho = cms.EDProducer( 'PhotonRhoProducer',
                                         src          = cms.InputTag('selectedPatPhotons'),
                                         srcRho       = cms.InputTag("kt6PFJets", "rho"),
                                         srcRhoBarrel = cms.InputTag("kt6PFJetsBarrel", "rho")
                                       )
