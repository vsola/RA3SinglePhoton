import FWCore.ParameterSet.Config as cms

from JetMETCorrections.Type1MET.MetType1Corrections_cff import *
##from JetMETCorrections.Configuration.L2L3Corrections_Summer09_cff import *
from JetMETCorrections.Configuration.DefaultJEC_cff import *
from JetMETCorrections.Type1MET.pfMETCorrections_cff import *
from JetMETCorrections.Type1MET.caloMETCorrections_cff import *


#############Correctors for charged Pf jets#################################
myak5PFL1FastjetChs = ak5PFL1Fastjet.clone(algorithm = 'AK5PFchs',srcRho = cms.InputTag('kt6PFJetsPFlow','rho'))

myak5PFL1FastChsL2L3Residual = cms.ESProducer('JetCorrectionESChain',
      correctors = cms.vstring('myak5PFL1FastjetChs','ak5PFL2Relative','ak5PFL3Absolute','ak5PFResidual')
      )
myak5PFL1FastChsL2L3 = cms.ESProducer('JetCorrectionESChain',
      correctors = cms.vstring('myak5PFL1FastjetChs','ak5PFL2Relative','ak5PFL3Absolute')
      )
      

myCorrak5PFL1FastChs = cms.ESProducer('JetCorrectionESChain',
      correctors = cms.vstring('myak5PFL1FastjetChs')
      )
 
      

#################################################################################
from PhysicsTools.PatAlgos.producersLayer1.metProducer_cff import *
patMETs.addGenMET=False
mylayer1METsRawPF = patMETs.clone()
mylayer1METsRawPF.addGenMET=False
mylayer1METsRawPF.addMuonCorrections = cms.bool(False)
mylayer1METsRawPF.metSource = cms.InputTag("pfMet","","")

mylayer1METs1PF = patMETs.clone()
mylayer1METs1PF.addMuonCorrections = cms.bool(False)
mylayer1METs1PF.metSource = cms.InputTag("pfType1CorrectedMet","","")

mylayer1METs2PF = patMETs.clone()
mylayer1METs2PF.addMuonCorrections = cms.bool(False)
mylayer1METs2PF.metSource = cms.InputTag("pfType1p2CorrectedMet","","")

mylayer1METsRaw = patMETs.clone()
mylayer1METsRaw.addGenMET=False
mylayer1METsRaw.addMuonCorrections = cms.bool(False)
mylayer1METsRaw.metSource = cms.InputTag("met","","")

mylayer1METs1 = patMETs.clone()
mylayer1METs1.addMuonCorrections = cms.bool(False)
mylayer1METs1.metSource = cms.InputTag("caloType1CorrectedMet","","")

mylayer1METs2 = patMETs.clone()
mylayer1METs2.addMuonCorrections = cms.bool(False)
mylayer1METs2.metSource = cms.InputTag("caloType1p2CorrectedMet","","")

pfJetMETcorr.src = cms.InputTag('pfJetsPFlow') 
pfJetMETcorr.skipMuons=False
caloJetMETcorr.srcMET=cms.InputTag('met') 
caloType1CorrectedMet.src=cms.InputTag('met') 
caloType1p2CorrectedMet.src=cms.InputTag('met') 
pfCandMETcorr.src = cms.InputTag('pfNoJetPFlow')    
#Use type-0 correction?
pfType1p2CorrectedMet.applyType0Corrections=True
pfType1CorrectedMet.applyType0Corrections=True

myproducePFMETCorrections = cms.Sequence(
  
   #pfCandsNotInJet*
   pfJetMETcorr
   * pfCandMETcorr
   * pfType1CorrectedMet
   * pfType1p2CorrectedMet
)
myproduceCaloMETCorrections = cms.Sequence(
    caloJetMETcorr
   * muonCaloMETcorr
   * caloType1CorrectedMet
   * caloType1p2CorrectedMet
)

makemyLayer1METsPF = cms.Sequence(
	myproducePFMETCorrections*
	mylayer1METs1PF*
	mylayer1METs2PF
)

makemyLayer1METs = cms.Sequence(
	produceCaloMETCorrections*
	mylayer1METs1*
	mylayer1METs2
	)
