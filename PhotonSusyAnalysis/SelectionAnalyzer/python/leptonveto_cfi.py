import FWCore.ParameterSet.Config as cms
muonSelector = cms.EDFilter(
  "GoodMuonSelector",
  MuonSource   = cms.InputTag('patMuons'),
  VertexSource = cms.InputTag("offlinePrimaryVertices"),
  MinMuPt      = cms.double(10),
  MaxMuEta     = cms.double(2.6),
  MaxMuD0      = cms.double(0.02),
  MaxMuDz      = cms.double(1),
  MaxMuRelIso  = cms.double(0.20),
  MinMuNumHit  = cms.double(11),
  DoMuonVeto           = cms.bool(False),
  DoMuonID             = cms.bool(True),
  DoMuonVtxAssociation = cms.bool(True),
  DoMuonIsolation      = cms.bool(True)
)

from PhysicsTools.PatAlgos.selectionLayer1.muonCountFilter_cfi import *

# muons selectors

patMuonsID = muonSelector.clone()
patMuonsID.MaxMuRelIso = 0.15
patMuonsID.DoMuonIsolation = False

patMuonsIDIso = muonSelector.clone()
patMuonsIDIso.MaxMuRelIso = 0.15

patMuonsPFID = muonSelector.clone()
patMuonsPFID.MuonSource = cms.InputTag("patMuonsPFlow")
patMuonsPFID.MaxMuRelIso = 0.20
patMuonsPFID.DoMuonIsolation = False

patMuonsPFIDIso = muonSelector.clone()
patMuonsPFIDIso.MuonSource = cms.InputTag("patMuonsPFlow")
patMuonsPFIDIso.MaxMuRelIso = 0.20

# muon filters

countMuonsID = countPatMuons.clone()
countMuonsID.src = cms.InputTag('patMuonsID')
countMuonsID.minNumber = cms.uint32(1)

countMuonsIDIso = countPatMuons.clone()
countMuonsIDIso.src = cms.InputTag('patMuonsIDIso')
countMuonsIDIso.minNumber = cms.uint32(1)

countPFMuonsID = countPatMuons.clone()
countPFMuonsID.src = cms.InputTag('patMuonsPFID')
countPFMuonsID.minNumber = cms.uint32(1)

countPFMuonsIDIso = countPatMuons.clone()
countPFMuonsIDIso.src = cms.InputTag('patMuonsPFIDIso')
countPFMuonsIDIso.minNumber = cms.uint32(1)

# muon sequences

ra2Muons = cms.Sequence(
  patMuonsID *
  patMuonsIDIso
)
ra2PFMuons = cms.Sequence(
  patMuonsPFID *
  patMuonsPFIDIso
)
ra2MuonVeto = cms.Sequence(
  ~countMuonsIDIso
)
ra2PFMuonVeto = cms.Sequence(
  ~countPFMuonsIDIso
)

electronSelector = cms.EDFilter(
  "GoodElectronSelector",
  ElectronSource = cms.InputTag('patElectrons'),
  VertexSource   = cms.InputTag("offlinePrimaryVertices"),
  MinElePt       = cms.double(10),
  MaxEleEta      = cms.double(2.6),
  MaxEleD0       = cms.double(0.02),
  MaxEleDz       = cms.double(1),
  MaxEleRelIso   = cms.double(0.20),
  DoElectronVeto           = cms.bool(False),
  DoElectronID             = cms.bool(True),
  DoElectronVtxAssociation = cms.bool(True),
  DoElectronIsolation      = cms.bool(True)
)

from PhysicsTools.PatAlgos.selectionLayer1.electronCountFilter_cfi import *

# electrons selectors

patElectronsID = electronSelector.clone()
patElectronsID.MaxEleRelIso = 0.15
patElectronsID.DoElectronIsolation = False

patElectronsIDIso = electronSelector.clone()
patElectronsIDIso.MaxEleRelIso = 0.15

patElectronsPFID = electronSelector.clone()
patElectronsPFID.ElectronSource = cms.InputTag("patElectronsPFlow")
patElectronsPFID.MaxEleRelIso = 0.20
patElectronsPFID.DoElectronIsolation = False

patElectronsPFIDIso = electronSelector.clone()
patElectronsPFIDIso.ElectronSource = cms.InputTag("patElectronsPFlow")
patElectronsPFIDIso.MaxEleRelIso = 0.20

countElectronsID = countPatElectrons.clone()
countElectronsID.src = cms.InputTag('patElectronsID')
countElectronsID.minNumber = cms.uint32(1)

countElectronsIDIso = countPatElectrons.clone()
countElectronsIDIso.src = cms.InputTag('patElectronsIDIso')
countElectronsIDIso.minNumber = cms.uint32(1)

countPFElectronsID = countPatElectrons.clone()
countPFElectronsID.src = cms.InputTag('patElectronsPFID')
countPFElectronsID.minNumber = cms.uint32(1)

countPFElectronsIDIso = countPatElectrons.clone()
countPFElectronsIDIso.src = cms.InputTag('patElectronsPFIDIso')
countPFElectronsIDIso.minNumber = cms.uint32(1)

ra2Electrons = cms.Sequence(
  patElectronsID *
  patElectronsIDIso
)
ra2PFElectrons = cms.Sequence(
  patElectronsPFID *
  patElectronsPFIDIso
)
ra2ElectronVeto = cms.Sequence(
  ~countElectronsIDIso
)
ra2PFElectronVeto = cms.Sequence(
  ~countPFElectronsIDIso
)

leptonVeto= cms.Sequence(
 #ra2Electrons*ra2Muons*
 ra2PFElectrons*ra2PFMuons
 #*~countElectronsIDIso*~countMuonsIDIso
)
