import FWCore.ParameterSet.Config as cms

selectionPlotMaker = cms.EDAnalyzer('WrappedSelectionAnalyzer',

	plotOnlyEventsPassing = cms.bool(True),
	punchthroughtest      = cms.bool(False),
	cutsForN1             = cms.vstring(),
	cutsForPresel         = cms.vstring(),
	drawPlots             = cms.bool(True),
	applyPUReweighting    = cms.bool(True),
                                    
	PUDistributionData    = cms.vdouble(0),
	PUDistributionMC      = cms.vdouble(0),
                                    
	loggingVerbosity      = cms.int32( 0 ),

	###Jet fakes photon (QCD/Photon+Jet)
	applyFakeRateCorrection        = cms.bool(False),
	applyFakeRateCorrectionPar1    = cms.double(0.0),
	applyFakeRateCorrectionPar2    = cms.double(0),
	applyFakeRateCorrectionPar3    = cms.double(0),
	applyFakeRateCorrectionPar4    = cms.double(0),
	applyFakeRateCorrectionPar5    = cms.double(0),
	applyFakeRateCorrectionSystInt = cms.double(0),
	applyFakeRateCorrectionHisto   = cms.bool(False),
	applyFakeRateCorrectionHT      = cms.bool(False),
	applyFakeRateCorrectionHistoName   = cms.string("QCDEst_3jet_Data"),
	applyFakeRateCorrectionHistoName2j = cms.string("QCDEst_2jet_Data"),
	applyFakeRateCorrectionHistoNameHT = cms.string("QCDEst_HT_Data"),
	applyFakeRateSystFit        = cms.double(0.20),
	applyFakeRateSystLowHighMet = cms.double(0.05),
	applyFakeRateSystSMCont     = cms.double(0.01),

	###Electron fakes photon (W+Jet, TTBar)
	applyEWKFakeRateCorrection = cms.bool(False),
	applyEWKFakeRatePar1       = cms.double(0.016),
	applyEWKFakeRateParErr1    = cms.double(0.01),

	selection   = cms.PSet(

		photonSrc    = cms.InputTag('selectedPatPhotons'),
                photonSrcHLT = cms.InputTag('selectedPatPhotons'),
                isPhotonFO   = cms.bool(False),
		jetSrc       = cms.InputTag('selectedPatJetsPFlow'),
		jetSrcHLT    = cms.InputTag('selectedPatJetsPFlow'),
		metSrc       = cms.InputTag('mylayer1METsRawPF',"","PhotonJetSelection"),
		metSrcRaw    = cms.InputTag('mylayer1METsRawPF',"",""),
		metSrcT1     = cms.InputTag('mylayer1METs1PF',"","PhotonJetSelection"),
		metSrcT2     = cms.InputTag('mylayer1METs2PF',"","PhotonJetSelection"),
		metSrc2      = cms.InputTag('mylayer1METs1',"","PhotonJetSelection"),
		electronSrc  = cms.InputTag('patElectrons'),
		muonSrc      = cms.InputTag('patMuons'),
		hcalLaserFilterSrc       = cms.InputTag('hcalLaserEventFilter','','PhotonJetSelection'),
		cscTightHaloFilterSrc    = cms.InputTag('CSCTightHaloFilter','','PhotonJetSelection'),
		ecalDeadCellBEFilterSrc  = cms.InputTag('EcalDeadCellBoundaryEnergyFilter','','PhotonJetSelection'),
		ecalDeadCellTPFilterSrc  = cms.InputTag('EcalDeadCellTriggerPrimitiveFilter','','PhotonJetSelection'),
		hbheNoiseFilterSrc       = cms.InputTag('HBHENoiseFilter','','PhotonJetSelection'),
		trackingFailureFilterSrc = cms.InputTag('trackingFailureFilter','','PhotonJetSelection'),
		eeBadScFilterSrc         = cms.InputTag('eeBadScFilter','PhotonJetSelection'),
		metMin           = cms.double(50),
		deltaPhiJ1Photon = cms.double(2.7),
		deltaPhiJ1J2     = cms.double(2.7),
		deltaRPhotonJet  = cms.double(0.5),
		deltaPhiMetJet1  = cms.double(0.5),
		deltaPhiMetJet2  = cms.double(0.0),
		deltaPhiMetJet3  = cms.double(0.1),

		###!!! evt with  MJ<cut passes
		Mj12  = cms.double(0),
		Mj23  = cms.double(0),
		Mj13  = cms.double(0),
		HT    = cms.double(200),
		HTJ   = cms.double(250),
		HTHLT = cms.double(500),
		#HTHLT = cms.double(450),

		####Trigger Cut!
		MHT       = cms.double(60),
		MHTJ      = cms.double(50),
		MT        = cms.double(0),
		jetPt     = cms.double(30),
		jet2Pt    = cms.double(30),
		jetEta    = cms.double(2.5),
		photonPt  = cms.double(80),
		photonEta = cms.double(1.4442),

		useGenForSelection     = cms.bool(False),
		requireGenForSelection = cms.bool(False),
		preferGenPhotons       = cms.bool(False),
		photonGenPdgId         = cms.double(22),
		photonGenPdgIdMother   = cms.double(0),
		genEleVeto             = cms.double(0),
		genPhotonVeto          = cms.double(0),
		debug                  = cms.bool(False),
		cutsToUse              = cms.vstring("MET"),
		#cutsToIgnore          = cms.vstring(),
		scanParameterisGluino  = cms.bool(True)
                
	) # selection
)

