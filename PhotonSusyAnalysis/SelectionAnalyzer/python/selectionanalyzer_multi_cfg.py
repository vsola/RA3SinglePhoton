import FWCore.ParameterSet.Config as cms

def getProcessFor(sampleConf,process,test,doSkimming,doAnalysis,fileAppendix,noKinematicPresel,PUDistributionMC,PUDistributionData,dataConf=0):

 	"""configure nearly all settings need for the job 
 	@type process: cms process
 	@param process: the actual running cmssw process
 	@type isData: boolean
 	@param isData: True, if its real data, false for MC
 	@type test: boolean
 	@param test: decreases number of events and increases sequence
 	"""

	#####################################################################################
	###### CONFIGURATION ################################################################

	isData = False
	if sampleConf == 10: 
		isData = True
	isMC = True
	if isData == True:  
		isMC = False

	dump = False
#	dump = True
	PunchThroughTester = False 
	printTreeViewer    = False
        
	quickScanForQCDEstOnly = False
#	quickScanForQCDEstOnly = True
        	
	doFastJEC = True                                 
	
	isTest = False
	if test is True:
	 isTest = True
	
	doPUCorr = True
	if PUDistributionMC != 0:
	 if len(PUDistributionMC) == 1 :
	  doPUCorr = False
	print 'doPUCorr? ',doPUCorr

	doTriggerEffStudy = False
	if doSkimming is False and doAnalysis is False:
	 doTriggerEffStudy = True
	
	# If no Skimming is done run over all events not only the ones containing at least 1 photon, 2 jets, etc.
	# if doSkimming is False:
	#	noKinematicPresel = True
	
	skimName      = "photonJetSelection.root"
	skimNameHisto = "photonJetSelectionHistoTree.root"
	if doSkimming is False:
	 skimName     = "photonJetSelectionSKIM.root"
	if fileAppendix != "":
	 skimName="photonJetSelection"
	 skimName+=fileAppendix
	 skimName+= ".root"
	 
	#####################################################################################
	#####################################################################################

	if sampleConf == 9:
		print "!!!Sample:Summer12 MC 8Tev!!!"
	if sampleConf == 10:
		print "!!!Sample:Data 2012 8Tev!!!"
	
	#####################################################################################
	#####################################################################################

	import FWCore.ParameterSet.Config as cms

	# Message logger
	process.load("FWCore.MessageLogger.MessageLogger_cfi")
	process.MessageLogger.cerr.FwkReport  = cms.untracked.PSet(
		reportEvery = cms.untracked.int32(2000),
		limit       = cms.untracked.int32(10000000)
	       )

	#####################################################################################
	###### OutputModule #################################################################

	process.out = cms.OutputModule("PoolOutputModule",
		fileName = cms.untracked.string(skimName),
		outputCommands = cms.untracked.vstring(
		'drop *'
		 )
	        )


	#####################################################################################
	###### Event Processed ##############################################################
		
    	process.maxEvents         = cms.untracked.PSet( input = cms.untracked.int32(-1) )
#    	process.maxEvents         = cms.untracked.PSet( input = cms.untracked.int32(1000) )

	if isTest is True:
		process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(3000) )

	if dump is True: #FALSE
		process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(2) )


	#####################################################################################
	###### Import of standard configurations ############################################

	print "load standard configuration"
	process.load('Configuration/StandardSequences/Services_cff')
	process.load('FWCore/MessageService/MessageLogger_cfi')
 	process.load('Configuration/Geometry/GeometryIdeal_cff') #VS!!!
	process.load('Configuration/StandardSequences/MagneticField_AutoFromDBCurrent_cff')
	process.load('Configuration/StandardSequences/Reconstruction_cff')
	process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
	process.load('Configuration/EventContent/EventContent_cff')

	print "load PAT Sequences"
	process.load("PhysicsTools.PatAlgos.patSequences_cff")

	# Remove default MET corrections - added later with proper configuration!
	getattr(process, "patDefaultSequence").remove(process.patMETCorrections)
	process.patMETs.metSource = cms.InputTag("met")

	
	if sampleConf == 9:  
#		process.GlobalTag.globaltag = 'START53_V7E::All'
#		process.GlobalTag.globaltag = 'START53_V7G::All'
		process.GlobalTag.globaltag = 'START53_V27::All'  # CMSSW >= 538
	if sampleConf == 10:  
#		process.GlobalTag.globaltag = cms.string('GR_P_V42_AN3::All')
		process.GlobalTag.globaltag = cms.string('FT_53_V21_AN5::All')  # 22Jan2013 (2012ABCD)
		# Different global tags for 2012 data 
		# What about  GR_R_53_V16     >=533X 	To be used for data reprocessing  ?!
		if dataConf == 1:
			process.GlobalTag.globaltag = cms.string('GR_P_V39_AN3::All')  # 2012A and 2012B (52X) prompt reco data 
		if dataConf == 2:
			process.GlobalTag.globaltag = cms.string('FT_53_V6_AN3::All')  # Jul13, 2012 CMSSW_5_3_2_patch4
		if dataConf == 3:
			process.GlobalTag.globaltag = cms.string('FT_53_V6C_AN3::All') # Aug06, 2012 CMSSW_5_3_3_patch1
		if dataConf == 4:
			process.GlobalTag.globaltag = cms.string('FT_53_V10_AN3::All') # Aug24, 2012 CMSSW_5_3_2_patch4
		if dataConf == 5:
			process.GlobalTag.globaltag = cms.string('GR_P_V40_AN3::All')  # 2012C v1 prompt reco data (53X,<533)
		if dataConf == 6:
			process.GlobalTag.globaltag = cms.string('GR_P_V41_AN3::All')  # 2012C v2 prompt reco data
		if dataConf == 7:
			process.GlobalTag.globaltag = cms.string('GR_P_V42_AN3::All')  # 2012D prompt reco data
		if dataConf == 8:
			process.GlobalTag.globaltag = cms.string('FT_53_V21_AN5::All')  # 22Jan2013 (2012ABCD)
			

	#####################################################################################
	###### PAT ##########################################################################
	# Define pat jet collections, apply standard correction, preselect genjets

	print "load PAT tools"
	# from PhysicsTools.PatAlgos.tools.coreTools import *
	process.patJetPartonAssociation.coneSizeToAssociate = 0.5


	#####################################################################################
	###### PF2PAT #######################################################################

	print "add PF2PAT"
	postfix = "PFlow"
	
	jetCorrLabelStrPF=('AK5PF', ['L1Offset','L2Relative', 'L3Absolute'])

	if doFastJEC is True:
		jetCorrLabelStrPF=('AK5PFchs', ['L1FastJet','L2Relative', 'L3Absolute'])

	if isData is True:
		jetCorrLabelStrPF=('AK5PF', ['L1Offset','L2Relative', 'L3Absolute'])
		if doFastJEC is True:
			jetCorrLabelStrPF=('AK5PFchs', ['L1FastJet','L2Relative', 'L3Absolute','L2L3Residual'])
	
	print("JetCorrLabel for PF2PAT jets:",jetCorrLabelStrPF)

	# Avoid precleaning of electrons & muons, use pfNoPU instead of pfNoEle as jet clustering input
	process.load('CommonTools/ParticleFlow/pfJets_cff')
	process.pfJets.src="pfNoPileUp" 
	
	# Call PF2PAT
	from PhysicsTools.PatAlgos.tools.pfTools import usePF2PAT
	
	usePF2PAT( process,
		   runPF2PAT = True,
 		   jetAlgo   = 'AK5',
 		   runOnMC   = isMC,
 		   postfix   = postfix,
 		   jetCorrections = jetCorrLabelStrPF,
 		   pvCollection   = cms.InputTag('offlinePrimaryVertices'),
 		   typeIMetCorrections = False
		 ) 
	process.pfPileUpPFlow.checkClosestZVertex = False

	# Use all pfJets as input - disable tau top projection
	getattr(process,"pfNoTau"+postfix).enable=False
	getattr(process,"pfNoJet"+postfix).bottomCollection="pfNoPileUpPFlow"	
	
	# Apply fast JEC
	process.patseq = cms.Sequence(   
		                       getattr(process,"patPF2PATSequence"+postfix)
				     )
	
	if doFastJEC is True:
		from PhysicsTools.SelectorUtils.pvSelector_cfi import pvSelector

		process.goodOfflinePrimaryVertices = cms.EDFilter(
			"PrimaryVertexObjectFilter",
			filterParams = pvSelector.clone( minNdof = cms.double(4.0), maxZ = cms.double(24.0) ),
			src = cms.InputTag('offlinePrimaryVertices')
		       )
	 
		process.pfPileUpPFlow.Enable   = True
		process.pfPileUpPFlow.Vertices = 'goodOfflinePrimaryVertices'

		process.pfJetsPFlow.doAreaFastjet = True
		process.pfJetsPFlow.doRhoFastjet  = False
	 
		process.pfJets.doAreaFastjet = True
		process.pfJets.doRhoFastjet  = False
	     
		process.patJetCorrFactorsPFlow.rho = cms.InputTag("kt6PFJetsPFlow", "rho")
		process.pfPileUpPFlow.checkClosestZVertex = cms.bool(False)
	
		from RecoJets.JetProducers.kt4PFJets_cfi import kt4PFJets
		process.kt6PFJetsPFlow = kt4PFJets.clone(
			rParam = cms.double(0.6),
			src = cms.InputTag('pfNoElectron'+postfix),
			doAreaFastjet = cms.bool(True),
			doRhoFastjet = cms.bool(True),
			Rho_EtaMax = cms.double(2.5)
		       )
	
		getattr( process, "patPF2PATSequence"+postfix ).replace(
			 getattr(process,"pfNoElectron"+postfix),
			 getattr(process,"pfNoElectron"+postfix)*
			 process.kt6PFJetsPFlow
		       )


	getattr(process, "patElectrons"+postfix ).embedGenMatch = isMC
	getattr(process, "patMuons"+postfix ).embedGenMatch     = isMC

	if isData==True:
		from PhysicsTools.PatAlgos.tools.coreTools import removeMCMatching
		removeMCMatching(process,['All'])


	# load the PU JetID sequence
	process.load("CMGTools.External.pujetidsequence_cff")

        process.puJetId.jets  = cms.InputTag("myjetselection")
	process.puJetMva.jets = cms.InputTag("myjetselection")

        process.puJetIdChs.jets  = cms.InputTag("myjetselection")
	process.puJetMvaChs.jets = cms.InputTag("myjetselection")

	print "end PF2PAT configuration"


	#####################################################################################
	###### MET Corrections ##############################################################

	print "add MET collections"
	process.load("PhotonSusyAnalysis.SelectionAnalyzer.muonmet_cfi")
	
	if isData==True:
		process.mylayer1METs1.addGenMET   = False
		process.mylayer1METs2.addGenMET   = False
		process.mylayer1METs1PF.addGenMET = False
		process.mylayer1METs2PF.addGenMET = False
	

	#####################################################################################
	###### JEC ##########################################################################
		
	if doFastJEC is True:
		process.pfJetMETcorr.src             = "pfJetsPFlow"
		process.pfJetMETcorr.jetCorrLabel    = "ak5PFL1FastL2L3"
		process.pfJetMETcorr.offsetCorrLabel = ""
	 
	# Use residual jet corrections for data
	if isData == True:
		print " add JEC Residual for data!"
		if doFastJEC is False:
			process.caloJetMETcorr.jetCorrLabel  = "ak5CaloL2L3Residual"
			process.pfJetMETcorr.jetCorrLabel    = "ak5PFL2L3Residual"
			process.pfJetMETcorr.offsetCorrLabel = ""
	 
		if doFastJEC is True:
			process.caloJetMETcorr.jetCorrLabel  = "ak5CaloL2L3Residual"
			process.pfJetMETcorr.jetCorrLabel    = "ak5PFL1FastL2L3Residual"
			process.pfJetMETcorr.offsetCorrLabel = ""
	  
		print "end add JEC "
	

	#####################################################################################
	###### MC Matching ##################################################################

	print "add MC Matching"

	process.load("PhysicsTools.PatAlgos.mcMatchLayer0.jetMatch_cfi")
	from PhysicsTools.PatAlgos.tools.jetTools import switchJetCollection

	process.patJetGenJetMatch.resolveByMatchQuality      = True
	process.patJetGenJetMatchPFlow.resolveByMatchQuality = True
	process.patJetGenJetMatch.matched                    = cms.InputTag('ak5GenJets')
	process.patJetGenJetMatchPFlow.matched               = cms.InputTag('ak5GenJets')
	process.patJetGenJetMatchPFlow.maxDeltaR             = 0.3
	process.patJetGenJetMatchPFlow.maxDPtRel             = 0.3	

	# Match photon!
	process.load("PhysicsTools.PatAlgos.mcMatchLayer0.photonMatch_cfi")
	print "match photons"
	process.photonMatch.mcPdgId = cms.vint32(22)
	print "match photons done"

	
	#####################################################################################
	###### Jet Collections PAT ##########################################################
	
	print "add PAT Jet Collections"  
	
	# if isData: apply residual JEC
        # First step: only AK5
	
	jetCorrLabelStr=('AK5Calo', ['L1Offset','L2Relative', 'L3Absolute'])

	if doFastJEC is True:
		jetCorrLabelStr=('AK5Calo', ['L1FastJet','L2Relative', 'L3Absolute'])
	 
	# Use residual jet corrections for data
	if isData == True:
		print "apply residual corrections"
		jetCorrLabelStr=('AK5Calo', ['L1Offset','L2Relative', 'L3Absolute','L2L3Residual'])
		if doFastJEC is True:
			jetCorrLabelStr=('AK5Calo', ['L1FastJet','L2Relative', 'L3Absolute','L2L3Residual'])
                 	
 	print "switch PAT Calo Jet Collection"     
	switchJetCollection( process, 
		             cms.InputTag('ak5CaloJets'),   
		             doJTA            = True,            
		             doBTagging       = True,            
		             jetCorrLabel     = jetCorrLabelStr,  
		             doType1MET       = False,            
		             genJetCollection = cms.InputTag('ak5GenJets'),
		             jetIdLabel	      = "ak5",
		             doJetID          = True
		           ) 
		            

	# Embed CaloTowers and PF Candidates
	process.patJets.embedCaloTowers      = True
	process.patJetsPFlow.embedCaloTowers = True

	
	#####################################################################################
	###### Photon Rho & Iso #############################################################

	if doFastJEC is True:
	 process.kt6PFJets = kt4PFJets.clone(
		                              src = cms.InputTag('particleFlow'),
					      rParam = cms.double(0.6),
					      doRhoFastjet = cms.bool(True),
					      Rho_EtaMax = cms.double(2.5)
					    )
	 
	 process.kt6PFJetsBarrel            = process.kt6PFJets.clone()
	 process.kt6PFJetsBarrel.Rho_EtaMax = cms.double(1.4442)
	 
	 process.patDefaultSequence.replace(
		                             process.patJetCorrFactors,
					     process.kt6PFJetsBarrel*process.patJetCorrFactors
					   )
	  
        # Photon PFIsolation
	from CommonTools.ParticleFlow.Tools.pfIsolation import setupPFElectronIso, setupPFPhotonIso
	process.phoIsoSequence = setupPFPhotonIso(process, 'selectedPhotonsWithRho')

        # Electron PFIsolation
	# from CommonTools.ParticleFlow.Tools.pfIsolation import setupPFElectronIso, setupPFMuonIso
	# process.eleIsoSequence = setupPFElectronIso(process, 'gsfElectrons')
	# process.pfeleiso       = cms.Sequence(process.pfParticleSelectionSequence + process.eleIsoSequence)


	# Photon - Electron Conversion Variables
	process.patConversions = cms.EDProducer( "PATConversionProducer",
						 # input collection
						 electronSource = cms.InputTag("selectedPatElectrons")  
					       )

	
	
	
	#####################################################################################
	####### TECHNICAL PRESELECTION ######################################################
	process.load("PhotonSusyAnalysis.SelectionAnalyzer.technicalpreselection_cff")

	####### WeightProducer ##############################################################
	# Load WeightProducer (from RA2 analysis)
	process.load("RA2.WeightProducer.weightproducer_cfi")
	
	####### ADD RHO TO PHOTON COLLECTION, NEEDED FOR PILEUP STUDIES #####################
	process.load("PhotonSusyAnalysis.PhotonRhoProducer.photonrhoproducer_cfi")

	####### ADD PFIsolation TO PHOTON COLLECTION ########################################
	process.load("PhotonSusyAnalysis.PFPhotonIsoProducer.pfphotonisoproducer_cfi")
	
	####### ECAL Dead Cell Filter #######################################################
	process.load('RecoMET.METFilters.EcalDeadCellTriggerPrimitiveFilter_cfi')
	process.EcalDeadCellTriggerPrimitiveFilter.taggingMode = cms.bool(True)


	#####################################################################################
	###### ANALYSIS SELECTION ###########################################################
	process.myjetselection  = process.selectedPatJets.clone(
		src = 'selectedPatJetsPFlow',
		cut = 'pt()>30'
		)

	# photonKinematicCuts = 'pt()>80 && isEB()' 
	
	# Define photon id (tight, fake, electron, etc.)
 	# With rho&03Cone
	
	# New Photon ID - Dec2012
	# https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedPhotonID2012
	
	# Photon
	cutForPhotonIdTight = '!hasPixelSeed() && r9()<1.0 && sigmaIetaIeta()>0.001 && userFloat("sigmaIphiIphi")>0.001 && sigmaIetaIeta()<0.012 && hadTowOverEm()<0.05 && userFloat("chargedIsoCor")<2.6 && userFloat("neutralIsoCor")<(3.5+0.04*pt()) && userFloat("photonIsoCor")<(1.3+0.005*pt())'

	# Photon_ele
	cutForPhotonIdTightNoPixelSeedVeto = 'hasPixelSeed() && r9()<1.0 && sigmaIetaIeta()>0.001 && userFloat("sigmaIphiIphi")>0.001 && sigmaIetaIeta()<0.012 && hadTowOverEm()<0.05 && userFloat("chargedIsoCor")<2.6 && userFloat("neutralIsoCor")<(3.5+0.04*pt()) && userFloat("photonIsoCor")<(1.3+0.005*pt())'
	
	# Photon_jet
	cutForFODenominator = '!hasPixelSeed() && r9()<1.0 && sigmaIetaIeta()>0.001 && userFloat("sigmaIphiIphi")>0.001 && sigmaIetaIeta()<0.012 && hadTowOverEm()<0.05 && userFloat("chargedIsoCor")>0.26 && userFloat("chargedIsoCor")<26.0 && userFloat("neutralIsoCor")>(0.35+0.004*pt()) && userFloat("neutralIsoCor")<(35.0+0.4*pt()) && userFloat("photonIsoCor")>(0.13+0.0005*pt()) && userFloat("photonIsoCor")<(13.0+0.05*pt()) && ( userFloat("chargedIsoCor")>2.6) || userFloat("neutralIsoCor")>(3.5+0.04*pt()) || userFloat("photonIsoCor")>(1.3+0.005*pt())'

	# Photon_hlt
	cutForPhotonIdHLT = cutForPhotonIdTight 
	# cutForPhotonIdHLT = cutForFODenominator+"||"+ cutForPhotonIdTight 
	# cutForPhotonIdHLT = '!hasPixelSeed() && r9()<1.0 && sigmaIetaIeta()>0.001 && userFloat("sigmaIphiIphi")>0.001 && sigmaIetaIeta()<0.012 && hadTowOverEm()<0.05 && userFloat("chargedIsoCor")<26.0 && userFloat("neutralIsoCor")<(35.0+0.4*pt()) && userFloat("photonIsoCor")<(13.0+0.05*pt())'


	# Only used in myphotonselectionLoose
	cutForPhotonIdTrigger = 'hadTowOverEm()<0.1 && isEB() && sigmaIetaIeta()<0.02'
	

	# Define corresponding photon selectors
	process.myphotonselection  = process.selectedPatPhotons.clone(
		src = 'selectedPhotonsWithRhoAndIsos',
		cut = 'isEB() && '+cutForPhotonIdTight
		# cut = photonKinematicCuts+' && '+cutForPhotonIdTight
	       )
	                                     
	process.myphotonselectionTRIGGEREFF  = process.selectedPatPhotons.clone(
		src = 'selectedPhotonsWithRhoAndIsos',
		cut = 'isEB() && '+cutForPhotonIdTight #VS!!! Trigger
	       )
	
	process.myphotonselectionPixelSeed  = process.selectedPatPhotons.clone(
		src = 'selectedPhotonsWithRhoAndIsos',
		cut = 'isEB() && '+cutForPhotonIdTightNoPixelSeedVeto
	       )
	
	process.myphotonselectionTRIGGEREFFPS  = process.selectedPatPhotons.clone(
		src = 'selectedPhotonsWithRhoAndIsos',
		cut = 'isEB() && '+cutForPhotonIdTightNoPixelSeedVeto
	       )
	
	process.myphotonselectionFO  = process.selectedPatPhotons.clone(
		src = 'selectedPhotonsWithRhoAndIsos',
		cut = 'isEB() && '+cutForFODenominator
	       )	                                     
	
	process.myphotonselectionTRIGGEREFFFO  = process.selectedPatPhotons.clone(
		src = 'selectedPhotonsWithRhoAndIsos',
		cut = 'isEB() && '+cutForFODenominator
	       )
	
	process.myphotonselectionLoose  = process.selectedPatPhotons.clone(
		src = 'selectedPhotonsWithRhoAndIsos',
		cut = 'pt()>60 && '+cutForPhotonIdTrigger
	       )

	process.myphotonselectionHLT  = process.selectedPatPhotons.clone(
		src = 'selectedPhotonsWithRhoAndIsos',
		cut = 'isEB() && '+cutForPhotonIdHLT
	       )

	# Cross cleaning electrons,muons, photons & jet
	process.cleanPatJetsIsolatedLeptonsPF = process.cleanPatJets.clone() 
#	process.cleanPatJetsIsolatedLeptonsPF = process.selectedPatJets.clone() #VS!!!
	process.cleanPatJetsIsolatedLeptonsPF.src           = 'myjetselection'
	process.cleanPatJetsIsolatedLeptonsPF.preselection  = cms.string('pt()>30')
	process.cleanPatJetsIsolatedLeptonsPF.checkOverlaps = cms.PSet(
		muons     = cms.PSet(
 		 src       = cms.InputTag("patMuonsPFlow"),
		 algorithm = cms.string("byDeltaR"),
		 preselection        = cms.string("abs(eta()) < 2.6  && pt() >15 && isPFMuon() && (isGlobalMuon() || isTrackerMuon())"),  # don't preselect the muons
		 deltaR              = cms.double(0.3),
		 checkRecoComponents = cms.bool(False), # don't check if they share some AOD object ref
		 pairCut             = cms.string(""),
		 requireNoOverlaps   = cms.bool(False), # overlaps don't cause the jet to be discared
	        ),
		electrons = cms.PSet(
		#src       = cms.InputTag("gsfElectrons"),
		 src       = cms.InputTag("patElectronsPFlow"),
		 algorithm = cms.string("byDeltaR"),
		 preselection        = cms.string("( pt()>15 && abs(eta())<1.479 && ((chargedHadronIso()+photonIso()+neutralHadronIso()) / pt())<0.15  && deltaEtaSuperClusterTrackAtVtx()<0.007 && deltaPhiSuperClusterTrackAtVtx()<0.8 && hadronicOverEm()<0.15 && sigmaIetaIeta()<0.01 ) || ( pt()>20 && abs(eta())>1.479 && abs(eta())<2.5 && ((chargedHadronIso()+photonIso()+neutralHadronIso()) / pt())<0.15  && deltaEtaSuperClusterTrackAtVtx()<0.01 && deltaPhiSuperClusterTrackAtVtx()<0.7 && sigmaIetaIeta()<0.03 )"),  # don't preselect the electrons
		 deltaR              = cms.double(0.3),
		 checkRecoComponents = cms.bool(False), # don't check if they share some AOD object ref
		 pairCut             = cms.string(""),
		 requireNoOverlaps   = cms.bool(False), # overlaps don't cause the jet to be discared
	        )
	)
	process.cleanPatJetsIsolatedLeptonsPF.finalCut = cms.string('')

	process.cleanPatJetsIsolatedLeptonsCalo     = process.cleanPatJetsIsolatedLeptonsPF.clone()
	process.cleanPatJetsIsolatedLeptonsCalo.src = 'selectedPatJets'
	
	

	#####################################################################################
	####### Select All ##################################################################
	#####################################################################################

	process.load("PhotonSusyAnalysis.SelectionAnalyzer.selectionanalyzer_cfi")

	process.selectionPlotMaker.selection.photonSrc    = ('myphotonselection')
	process.selectionPlotMaker.selection.photonSrcHLT = ('myphotonselectionHLT')
	process.selectionPlotMaker.selection.jetSrc       = ('cleanPatJetsIsolatedLeptonsPF')
	# process.selectionPlotMaker.selection.jetSrcHLT    = ('selectedPatJetsPFlow')
	process.selectionPlotMaker.selection.jetSrcHLT    = ('myjetselection')
	process.selectionPlotMaker.selection.metMin       = 100 
	process.selectionPlotMaker.punchthroughtest       = PunchThroughTester # = False
	process.selectionPlotMaker.selection.useGenForSelection = False


	if PUDistributionMC != 0:
		process.selectionPlotMaker.PUDistributionMC   = PUDistributionMC
	if PUDistributionData != 0:
		process.selectionPlotMaker.PUDistributionData = PUDistributionData
	process.selectionPlotMaker.applyPUReweighting  = doPUCorr

	if isData == True :
	 process.selectionPlotMaker.applyPUReweighting = False

	
	process.select_All=process.selectionPlotMaker.clone();
	process.select_All.selection.cutsToUse = cms.vstring("HT")
	process.select_All.cutsForN1           = cms.vstring()
	process.select_All.cutsForPresel       = cms.vstring("HT")
	process.select_All.selection.photonSrc = ('myphotonselectionLoose')
	process.select_All.selection.jetSrc    = ('myjetselection')
	
	
	# Trigger Studies (HLT)
	process.select_All_HT_Nominator                       = process.select_All.clone()
	process.select_All_HT_Nominator.selection.photonSrc   = ('myphotonselectionTRIGGEREFF')
	process.select_All_HT_Nominator.selection.cutsToUse   = cms.vstring("HTHLT",">= 1 Photons","photonPtCor","MET")
	process.select_All_HT_Nominator.cutsForPresel         = cms.vstring("HTHLT",">= 1 Photons","photonPtCor")
	process.select_All_HT_Nominator.selection.photonPtCor = 40
	process.select_All_HT_Nominator.selection.HTHLT       = 750
		
	process.select_All_HT_Denominator                     = process.select_All_HT_Nominator.clone()

	
	process.select_All_Photon_Nominator                       = process.select_All.clone()
	process.select_All_Photon_Nominator.selection.photonSrc   = ('myphotonselectionTRIGGEREFF')
	process.select_All_Photon_Nominator.selection.cutsToUse   = cms.vstring("HTHLT",">= 1 Photons","photonPtCor","MET")
	process.select_All_Photon_Nominator.cutsForPresel         = cms.vstring("HTHLT",">= 1 Photons","photonPtCor")
	process.select_All_Photon_Nominator.selection.photonPtCor = 200
	process.select_All_Photon_Nominator.selection.HTHLT       = 300
	
	process.select_All_Photon_Denominator                     = process.select_All_Photon_Nominator.clone()


	process.select_All_HT_Nominator_PS                       = process.select_All.clone()
	process.select_All_HT_Nominator_PS.selection.photonSrc   = ('myphotonselectionTRIGGEREFFPS')
	process.select_All_HT_Nominator_PS.selection.cutsToUse   = cms.vstring("HTHLT",">= 1 Photons","photonPtCor","MET")
	process.select_All_HT_Nominator_PS.cutsForPresel         = cms.vstring("HTHLT",">= 1 Photons","photonPtCor")
	process.select_All_HT_Nominator_PS.selection.photonPtCor = 40
	process.select_All_HT_Nominator_PS.selection.HTHLT       = 750

	process.select_All_HT_Denominator_PS                     = process.select_All_HT_Nominator_PS.clone()


	process.select_All_Photon_Nominator_PS                       = process.select_All.clone()
	process.select_All_Photon_Nominator_PS.selection.photonSrc   = ('myphotonselectionTRIGGEREFFPS')
	process.select_All_Photon_Nominator_PS.selection.cutsToUse   = cms.vstring("HTHLT",">= 1 Photons","photonPtCor","MET")
	process.select_All_Photon_Nominator_PS.cutsForPresel         = cms.vstring("HTHLT",">= 1 Photons","photonPtCor")
	process.select_All_Photon_Nominator_PS.selection.photonPtCor = 200
	process.select_All_Photon_Nominator_PS.selection.HTHLT       = 300

	process.select_All_Photon_Denominator_PS                     = process.select_All_Photon_Nominator_PS.clone()


	process.select_All_HT_Nominator_FO                            = process.select_All.clone()
	process.select_All_HT_Nominator_FO.selection.photonSrc        = ('myphotonselectionTRIGGEREFFFO')
#	process.select_All_HT_Nominator_FO.selection.cutsToUse        = cms.vstring("HTHLT",">= 1 Photons","photonPtCor","photonJetMatch","MET")
#	process.select_All_HT_Nominator_FO.cutsForPresel              = cms.vstring("HTHLT",">= 1 Photons","photonPtCor","photonJetMatch")
	process.select_All_HT_Nominator_FO.selection.cutsToUse        = cms.vstring("HTHLT",">= 1 Photons","photonPtCor","photonJetMatch","photonTightMatch","MET")
	process.select_All_HT_Nominator_FO.cutsForPresel              = cms.vstring("HTHLT",">= 1 Photons","photonPtCor","photonJetMatch","photonTightMatch")
	process.select_All_HT_Nominator_FO.selection.photonPtCor      = 40
	process.select_All_HT_Nominator_FO.selection.HTHLT            = 750
	process.select_All_HT_Nominator_FO.selection.photonJetMatch   = 1
	process.select_All_HT_Nominator_FO.selection.photonTightMatch = 1
	
	process.select_All_HT_Denominator_FO                          = process.select_All_HT_Nominator_FO.clone()


	process.select_All_Photon_Nominator_FO                            = process.select_All.clone()
	process.select_All_Photon_Nominator_FO.selection.photonSrc        = ('myphotonselectionTRIGGEREFFFO')
#	process.select_All_Photon_Nominator_FO.selection.cutsToUse        = cms.vstring("HTHLT",">= 1 Photons","photonPtCor","photonJetMatch","MET")
#	process.select_All_Photon_Nominator_FO.cutsForPresel              = cms.vstring("HTHLT",">= 1 Photons","photonPtCor","photonJetMatch")
	process.select_All_Photon_Nominator_FO.selection.cutsToUse        = cms.vstring("HTHLT",">= 1 Photons","photonPtCor","photonJetMatch","photonTightMatch","MET")
	process.select_All_Photon_Nominator_FO.cutsForPresel              = cms.vstring("HTHLT",">= 1 Photons","photonPtCor","photonJetMatch","photonTightMatch")
	process.select_All_Photon_Nominator_FO.selection.photonPtCor      = 200
	process.select_All_Photon_Nominator_FO.selection.HTHLT            = 300
	process.select_All_Photon_Nominator_FO.selection.photonJetMatch   = 1
	process.select_All_Photon_Nominator_FO.selection.photonTightMatch = 1

	process.select_All_Photon_Denominator_FO                          = process.select_All_Photon_Nominator_FO.clone()

	
	################################################################################################
	# ==1 Photon, >=2jets
	################################################################################################
	
	process.select_1ph_2jets = process.selectionPlotMaker.clone();
	process.select_1ph_2jets.selection.cutsToUse = cms.vstring(">= 2 Jets",">= 1 Photons","HTHLT",
								   "photonEta","jetPt","jetEta","MET",
								   "photonPtCor")
	process.select_1ph_2jets.cutsForN1           = cms.vstring("MET","photonEta")
	process.select_1ph_2jets.cutsForPresel       = cms.vstring(">= 2 Jets",">= 1 Photons","HTHLT",
								   "photonEta","jetPt","jetEta",
								   "photonPtCor")
	process.select_1ph_2jets.selection.requireGenForSelection = False
	

	# ==1 Photon, =2jets +++++BKG++++ Fake electron/noPixelSeedVetoPhoton
	process.select_1ph_2jets_PixelSeed                     = process.select_1ph_2jets.clone();
	process.select_1ph_2jets_PixelSeed.selection.photonSrc = ('myphotonselectionPixelSeed')
	
	# ==1 Photon, =2jets +++++BKG++++ Fake electron/noPixelSeedVetoPhoton FakeRateApplied!
	process.select_1ph_2jets_PixelSeedCorr                            = process.select_1ph_2jets.clone();
	process.select_1ph_2jets_PixelSeedCorr.selection.photonSrc        = ('myphotonselectionPixelSeed')
	process.select_1ph_2jets_PixelSeedCorr.applyEWKFakeRateCorrection = True
	if isData is True:
		process.select_1ph_2jets_PixelSeedCorr.applyEWKFakeRatePar1       = 0.0157 # DATA #
		process.select_1ph_2jets_PixelSeedCorr.applyEWKFakeRateParErr1    = 0.0080
	else:
		process.select_1ph_2jets_PixelSeedCorr.applyEWKFakeRatePar1       = 0.0084 #  MC  #
		process.select_1ph_2jets_PixelSeedCorr.applyEWKFakeRateParErr1    = 0.0009
	
	####### Gen Electron Veto applied
	# ==1 Photon, =2jets +++++BKG++++ Fake electron/noPixelSeedVetoPhoton 
	process.select_1ph_2jets_GenEleVeto                      = process.select_1ph_2jets.clone();
	process.select_1ph_2jets_GenEleVeto.selection.cutsToUse  = cms.vstring(">= 2 Jets",">= 1 Photons","HTHLT",
									       "photonEta","jetPt","jetEta","MET",
									       "genEleVeto","photonPtCor")
	process.select_1ph_2jets_GenEleVeto.cutsForPresel        = cms.vstring(">= 2 Jets",">= 1 Photons","HTHLT",
									       "photonEta","jetPt","jetEta",
									       "genEleVeto","photonPtCor")
	process.select_1ph_2jets_GenEleVeto.selection.genEleVeto = 2 # NO electron gen
	
	# ==1 Photon, =2jets +++++BKG++++ Fake electron/noPixelSeedVetoPhoton
	process.select_1ph_2jets_GenEleVetoPixelSeed                      = process.select_1ph_2jets_GenEleVeto.clone();
	process.select_1ph_2jets_GenEleVetoPixelSeed.selection.photonSrc  = ('myphotonselectionPixelSeed')
	process.select_1ph_2jets_GenEleVetoPixelSeed.selection.genEleVeto = 2
	
	# ==1 Photon, =2jets +++++BKG++++ Fake electron/noPixelSeedVetoPhoton FakeRateApplied!
	process.select_1ph_2jets_GenEleVetoPixelSeedCorr                            = process.select_1ph_2jets_GenEleVeto.clone();
	process.select_1ph_2jets_GenEleVetoPixelSeedCorr.selection.photonSrc        = ('myphotonselectionPixelSeed')
	process.select_1ph_2jets_GenEleVetoPixelSeedCorr.applyEWKFakeRateCorrection = True
#	process.select_1ph_2jets_GenEleVetoPixelSeedCorr.applyEWKFakeRatePar1       = 0.0157 # DATA #
#	process.select_1ph_2jets_GenEleVetoPixelSeedCorr.applyEWKFakeRateParErr1    = 0.0080
	process.select_1ph_2jets_GenEleVetoPixelSeedCorr.applyEWKFakeRatePar1       = 0.0084 #  MC  #
	process.select_1ph_2jets_GenEleVetoPixelSeedCorr.applyEWKFakeRateParErr1    = 0.0009
	process.select_1ph_2jets_GenEleVetoPixelSeedCorr.selection.genEleVeto       = 2 # NO electron gen
	
	####### Gen Electron Veto applied REVERSE
	# ==1 Photon, =2jets +++++BKG++++ Fake electron/noPixelSeedVetoPhoton 
	process.select_1ph_2jets_GenEleVetoRe                      = process.select_1ph_2jets_GenEleVeto.clone();
	process.select_1ph_2jets_GenEleVetoRe.selection.photonSrc  = ('myphotonselection')
	process.select_1ph_2jets_GenEleVetoRe.selection.cutsToUse  = cms.vstring("genEleVeto",">= 2 Jets",">= 1 Photons",
										 "HTHLT","photonEta","jetPt","jetEta",
										 "MET","photonPtCor")
	process.select_1ph_2jets_GenEleVetoRe.selection.genEleVeto = 1 # electron gen
	
	# ==1 Photon, =2jets +++++BKG++++ Fake electron/noPixelSeedVetoPhoton
	process.select_1ph_2jets_GenEleVetoRePixelSeed                      = process.select_1ph_2jets_GenEleVeto.clone();
	process.select_1ph_2jets_GenEleVetoRePixelSeed.selection.photonSrc  = ('myphotonselectionPixelSeed')
	process.select_1ph_2jets_GenEleVetoRePixelSeed.selection.genEleVeto = 1 # electron gen
	
	# ==1 Photon, =2jets +++++BKG++++ Fake electron/noPixelSeedVetoPhoton FakeRateApplied!
	process.select_1ph_2jets_GenEleVetoRePixelSeedCorr                            = process.select_1ph_2jets_GenEleVeto.clone();
	process.select_1ph_2jets_GenEleVetoRePixelSeedCorr.selection.photonSrc        = ('myphotonselectionPixelSeed')
	process.select_1ph_2jets_GenEleVetoRePixelSeedCorr.applyEWKFakeRateCorrection = True
#	process.select_1ph_2jets_GenEleVetoRePixelSeedCorr.applyEWKFakeRatePar1       = 0.0157 # DATA #
#	process.select_1ph_2jets_GenEleVetoRePixelSeedCorr.applyEWKFakeRateParErr1    = 0.0080
	process.select_1ph_2jets_GenEleVetoRePixelSeedCorr.applyEWKFakeRatePar1       = 0.0084 #  MC  #
	process.select_1ph_2jets_GenEleVetoRePixelSeedCorr.applyEWKFakeRateParErr1    = 0.0009
	process.select_1ph_2jets_GenEleVetoRePixelSeedCorr.selection.genEleVeto       = 1 # electron gen
	

	# ==1 Photon, =2jets +++++BKG++++ FO
	process.select_1ph_2jets_FO                            = process.select_1ph_2jets.clone();
	process.select_1ph_2jets_FO.selection.photonSrc        = ('myphotonselectionFO')
	process.select_1ph_2jets_FO.selection.cutsToUse        = cms.vstring(">= 2 Jets",">= 1 Photons","HTHLT",
									     "photonEta","jetPt","jetEta","MET",
									     "photonPtCor","photonJetMatch","photonTightMatch")
	process.select_1ph_2jets_FO.cutsForPresel              = cms.vstring(">= 2 Jets",">= 1 Photons","HTHLT",
									     "photonEta","jetPt","jetEta",
									     "photonPtCor","photonJetMatch","photonTightMatch")
	process.select_1ph_2jets_FO.selection.photonJetMatch   = 1
	process.select_1ph_2jets_FO.selection.photonTightMatch = 1
	process.select_1ph_2jets_FO.selection.isPhotonFO       = True

	# ==1 Photon, =2jets +++++BKG++++ FO Corr+++ Estimate after application of FakeRate
	######################################################
	####### !!!!!!!!!!!!! HERE 2Jet !!!!!!!!!!!!! ########
	######################################################
	process.select_1ph_2jets_FO_Corr                                    = process.select_1ph_2jets.clone();
	process.select_1ph_2jets_FO_Corr.selection.cutsToUse                = cms.vstring(">= 2 Jets",">= 1 Photons","HTHLT",
											  "photonEta","jetPt","jetEta","MET",
											  "photonPtCor","photonJetMatch","photonTightMatch")
	process.select_1ph_2jets_FO_Corr.cutsForPresel                     = cms.vstring(">= 2 Jets",">= 1 Photons","HTHLT",
											 "photonEta","jetPt","jetEta",
											 "photonPtCor","photonJetMatch","photonTightMatch")
	process.select_1ph_2jets_FO_Corr.selection.isPhotonFO               = True
	process.select_1ph_2jets_FO_Corr.selection.photonSrc                = ('myphotonselectionFO')
	process.select_1ph_2jets_FO_Corr.selection.photonJetMatch           = 1
	process.select_1ph_2jets_FO_Corr.selection.photonTightMatch         = 1
	process.select_1ph_2jets_FO_Corr.applyFakeRateSystFit               = 0.10
	process.select_1ph_2jets_FO_Corr.applyFakeRateSystLowHighMet        = 0.05
	process.select_1ph_2jets_FO_Corr.applyFakeRateSystSMCont            = 0.00
	process.select_1ph_2jets_FO_Corr.applyFakeRateCorrection            = True
	process.select_1ph_2jets_FO_Corr.applyFakeRateCorrectionHT          = True	
	process.select_1ph_2jets_FO_Corr.applyFakeRateCorrectionHistoNameHT = "QCDEst_HT_Data"
	
	process.select_1ph_2jets_FO_CorrMC                                    = process.select_1ph_2jets_FO_Corr.clone();
	process.select_1ph_2jets_FO_CorrMC.applyFakeRateSystFit               = 0.20
	process.select_1ph_2jets_FO_CorrMC.applyFakeRateSystLowHighMet        = 0.05
	process.select_1ph_2jets_FO_CorrMC.applyFakeRateSystSMCont            = 0.00
	process.select_1ph_2jets_FO_CorrMC.applyFakeRateCorrectionHT          = True	
	process.select_1ph_2jets_FO_CorrMC.applyFakeRateCorrectionHistoNameHT = "QCDEst_HT_MC"


	################################################################################################
	# ==1 Photon, >=3jets
	################################################################################################
	process.select_1ph_3jets                      = process.selectionPlotMaker.clone();
	process.select_1ph_3jets.selection.cutsToUse  = cms.vstring(">= 3 Jets",">= 1 Photons","HTHLT",
								   "photonEta","jetPt","jetEta","MET",
								    "photonPtCor")
	process.select_1ph_3jets.cutsForN1            = cms.vstring("MET")
	process.select_1ph_3jets.cutsForPresel        = cms.vstring(">= 3 Jets",">= 1 Photons","HTHLT",
								   "photonEta","jetPt","jetEta",
								    "photonPtCor")
	process.select_1ph_3jets.selection.requireGenForSelection = False
	process.select_1ph_3jets.selection.genEleVeto = 0 # NO cut applied
	
	# ==1 Photon, >=3jets +++++BKG++++ Fake electron/noPixelSeedVetoPhoton
	process.select_1ph_3jets_PixelSeed                     = process.select_1ph_3jets.clone();
	process.select_1ph_3jets_PixelSeed.selection.photonSrc = ('myphotonselectionPixelSeed')
	
	# ==1 Photon, >=3jets +++++BKG++++ Fake electron/noPixelSeedVetoPhoton FakeRateApplied!
	process.select_1ph_3jets_PixelSeedCorr                            = process.select_1ph_3jets.clone();
	process.select_1ph_3jets_PixelSeedCorr.selection.photonSrc        = ('myphotonselectionPixelSeed')
	process.select_1ph_3jets_PixelSeedCorr.applyEWKFakeRateCorrection = True
	if isData is True:
		process.select_1ph_3jets_PixelSeedCorr.applyEWKFakeRatePar1       = 0.0157 # DATA #
		process.select_1ph_3jets_PixelSeedCorr.applyEWKFakeRateParErr1    = 0.0080
	else:
		process.select_1ph_3jets_PixelSeedCorr.applyEWKFakeRatePar1       = 0.0084 #  MC  #
		process.select_1ph_3jets_PixelSeedCorr.applyEWKFakeRateParErr1    = 0.0009
	
	####### Gen Electron Veto applied
	# ==1 Photon, >=3jets +++++BKG++++ Fake electron/noPixelSeedVetoPhoton 
	process.select_1ph_3jets_GenEleVeto                      = process.select_1ph_3jets.clone();
	process.select_1ph_3jets_GenEleVeto.selection.cutsToUse  = cms.vstring(">= 3 Jets",">= 1 Photons","HTHLT",
									       "photonEta","jetPt","jetEta","MET",
									       "genEleVeto","photonPtCor")
	process.select_1ph_3jets_GenEleVeto.cutsForPresel        = cms.vstring(">= 3 Jets",">= 1 Photons","HTHLT",
									       "photonEta","jetPt","jetEta",
									       "genEleVeto","photonPtCor")
	process.select_1ph_3jets_GenEleVeto.selection.genEleVeto = 2 # NO electron gen
	
	# ==1 Photon, >=3jets +++++BKG++++ Fake electron/noPixelSeedVetoPhoton
	process.select_1ph_3jets_GenEleVetoPixelSeed                      = process.select_1ph_3jets_GenEleVeto.clone();
	process.select_1ph_3jets_GenEleVetoPixelSeed.selection.photonSrc  = ('myphotonselectionPixelSeed')
	process.select_1ph_3jets_GenEleVetoPixelSeed.selection.genEleVeto = 2 # NO electron gen
	
	# ==1 Photon, >=3jets +++++BKG++++ Fake electron/noPixelSeedVetoPhoton FakeRateApplied!
	process.select_1ph_3jets_GenEleVetoPixelSeedCorr=process.select_1ph_3jets_GenEleVeto.clone();
	process.select_1ph_3jets_GenEleVetoPixelSeedCorr.selection.photonSrc=('myphotonselectionPixelSeed')
	process.select_1ph_3jets_GenEleVetoPixelSeedCorr.applyEWKFakeRateCorrection = True
#	process.select_1ph_3jets_GenEleVetoPixelSeedCorr.applyEWKFakeRatePar1       = 0.0157 # DATA #
#	process.select_1ph_3jets_GenEleVetoPixelSeedCorr.applyEWKFakeRateParErr1    = 0.0080
	process.select_1ph_3jets_GenEleVetoPixelSeedCorr.applyEWKFakeRatePar1       = 0.0084 #  MC  #
	process.select_1ph_3jets_GenEleVetoPixelSeedCorr.applyEWKFakeRateParErr1    = 0.0009
	process.select_1ph_3jets_GenEleVetoPixelSeedCorr.selection.genEleVeto       = 2 # NO electron gen
	
	####### Gen Electron Veto applied REVERSE
	# ==1 Photon, >=3jets +++++BKG++++ Fake electron/noPixelSeedVetoPhoton 
	process.select_1ph_3jets_GenEleVetoRe                                  = process.select_1ph_3jets_GenEleVeto.clone();
	process.select_1ph_3jets_GenEleVetoRe.selection.photonSrc              = ('myphotonselection')
	process.select_1ph_3jets_GenEleVetoRe.selection.cutsToUse              = cms.vstring("genEleVeto",">= 3 Jets",">= 1 Photons","HTHLT",
											     "photonEta","jetPt","jetEta","MET",
											     "photonPtCor")
	process.select_1ph_3jets_GenEleVetoRe.selection.genEleVeto             = 1  # electron gen
	process.select_1ph_3jets_GenEleVetoRe.selection.requireGenForSelection = False
	process.select_1ph_3jets_GenEleVetoRe.selection.photonGenPdgId         = 11 # electron
	
	# ==1 Photon, >=3jets +++++BKG++++ Fake electron/noPixelSeedVetoPhoton
	process.select_1ph_3jets_GenEleVetoRePixelSeed                                  = process.select_1ph_3jets_GenEleVeto.clone();
	process.select_1ph_3jets_GenEleVetoRePixelSeed.selection.photonSrc              = ('myphotonselectionPixelSeed')
	process.select_1ph_3jets_GenEleVetoRePixelSeed.selection.genEleVeto             = 1 # electron gen
	process.select_1ph_3jets_GenEleVetoRePixelSeed.selection.requireGenForSelection = False
	process.select_1ph_3jets_GenEleVetoRePixelSeed.selection.photonGenPdgId         = 11 # electron
	
	# ==1 Photon, >=3jets +++++BKG++++ Fake electron/noPixelSeedVetoPhoton 
	process.select_1ph_3jets_GenEleVetoReMatchEle                                  = process.select_1ph_3jets_GenEleVeto.clone();
	process.select_1ph_3jets_GenEleVetoReMatchEle.selection.photonSrc              = ('myphotonselection')
	process.select_1ph_3jets_GenEleVetoReMatchEle.selection.cutsToUse              = cms.vstring("genEleVeto",">= 3 Jets",">= 1 Photons","HTHLT",
												     "photonEta","jetPt","jetEta","MET",
												     "photonPtCor")
	process.select_1ph_3jets_GenEleVetoReMatchEle.selection.genEleVeto             = 1
	process.select_1ph_3jets_GenEleVetoReMatchEle.selection.requireGenForSelection = True # !!!
	process.select_1ph_3jets_GenEleVetoReMatchEle.selection.photonGenPdgId         = 11
	
	# ==1 Photon, >=3jets +++++BKG++++ Fake electron/noPixelSeedVetoPhoton
	process.select_1ph_3jets_GenEleVetoRePixelSeedMatchEle                                  = process.select_1ph_3jets_GenEleVeto.clone();
	process.select_1ph_3jets_GenEleVetoRePixelSeedMatchEle.selection.photonSrc              = ('myphotonselectionPixelSeed')
	process.select_1ph_3jets_GenEleVetoRePixelSeedMatchEle.selection.genEleVeto             = 1
	process.select_1ph_3jets_GenEleVetoRePixelSeedMatchEle.selection.requireGenForSelection = True # !!!
	process.select_1ph_3jets_GenEleVetoRePixelSeedMatchEle.selection.photonGenPdgId         = 11
	
	# ==1 Photon, >=3jets +++++BKG++++ Fake electron/noPixelSeedVetoPhoton 
	process.select_1ph_3jets_GenEleVetoReMatchJet                                  = process.select_1ph_3jets_GenEleVeto.clone();
	process.select_1ph_3jets_GenEleVetoReMatchJet.selection.photonSrc              = ('myphotonselection')
	process.select_1ph_3jets_GenEleVetoReMatchJet.selection.cutsToUse              = cms.vstring("genEleVeto",">= 3 Jets",">= 1 Photons","HTHLT",
												     "photonEta","jetPt","jetEta","MET",
												     "photonPtCor")
	process.select_1ph_3jets_GenEleVetoReMatchJet.selection.genEleVeto             = 1
	process.select_1ph_3jets_GenEleVetoReMatchJet.selection.requireGenForSelection = True # !!!
	process.select_1ph_3jets_GenEleVetoReMatchJet.selection.photonGenPdgId         = 6 # top quark
	
	# ==1 Photon, >=3jets +++++BKG++++ Fake electron/noPixelSeedVetoPhoton
	process.select_1ph_3jets_GenEleVetoRePixelSeedMatchJet                                  = process.select_1ph_3jets_GenEleVeto.clone();
	process.select_1ph_3jets_GenEleVetoRePixelSeedMatchJet.selection.photonSrc              = ('myphotonselectionPixelSeed')
	process.select_1ph_3jets_GenEleVetoRePixelSeedMatchJet.selection.genEleVeto             = 1
	process.select_1ph_3jets_GenEleVetoRePixelSeedMatchJet.selection.requireGenForSelection = True # !!!
	process.select_1ph_3jets_GenEleVetoRePixelSeedMatchJet.selection.photonGenPdgId         = 6 # top quark
	
	# ==1 Photon, >=3jets +++++BKG++++ Fake electron/noPixelSeedVetoPhoton 
	process.select_1ph_3jets_GenEleVetoReMatchNoJet                                  = process.select_1ph_3jets_GenEleVeto.clone();
	process.select_1ph_3jets_GenEleVetoReMatchNoJet.selection.photonSrc              = ('myphotonselection')
	process.select_1ph_3jets_GenEleVetoReMatchNoJet.selection.cutsToUse              = cms.vstring("genEleVeto",">= 3 Jets",">= 1 Photons","HTHLT",
												       "photonEta","jetPt","jetEta","MET",
												       "photonPtCor")
	process.select_1ph_3jets_GenEleVetoReMatchNoJet.selection.genEleVeto             = 1
	process.select_1ph_3jets_GenEleVetoReMatchNoJet.selection.requireGenForSelection = True # !!!
	process.select_1ph_3jets_GenEleVetoReMatchNoJet.selection.photonGenPdgId         = 5 # b quark
	
	# ==1 Photon, >=3jets +++++BKG++++ Fake electron/noPixelSeedVetoPhoton
	process.select_1ph_3jets_GenEleVetoRePixelSeedMatchNoJet                                  = process.select_1ph_3jets_GenEleVeto.clone();
	process.select_1ph_3jets_GenEleVetoRePixelSeedMatchNoJet.selection.photonSrc              = ('myphotonselectionPixelSeed')
	process.select_1ph_3jets_GenEleVetoRePixelSeedMatchNoJet.selection.genEleVeto             = 1
	process.select_1ph_3jets_GenEleVetoRePixelSeedMatchNoJet.selection.requireGenForSelection = True # !!!
	process.select_1ph_3jets_GenEleVetoRePixelSeedMatchNoJet.selection.photonGenPdgId         = 5 # b quark
	
	# ==1 Photon, >=3jets +++++BKG++++ Fake electron/noPixelSeedVetoPhoton FakeRateApplied!
	process.select_1ph_3jets_GenEleVetoRePixelSeedCorr                                  = process.select_1ph_3jets_GenEleVeto.clone();
	process.select_1ph_3jets_GenEleVetoRePixelSeedCorr.selection.photonSrc              = ('myphotonselectionPixelSeed')
	process.select_1ph_3jets_GenEleVetoRePixelSeedCorr.applyEWKFakeRateCorrection       = True
	process.select_1ph_3jets_GenEleVetoRePixelSeedCorr.applyEWKFakeRatePar1             = 0.0084 #  MC  #
	process.select_1ph_3jets_GenEleVetoRePixelSeedCorr.applyEWKFakeRateParErr1          = 0.0009
	process.select_1ph_3jets_GenEleVetoRePixelSeedCorr.selection.genEleVeto             = 1
	process.select_1ph_3jets_GenEleVetoRePixelSeedCorr.selection.requireGenForSelection = False
	process.select_1ph_3jets_GenEleVetoRePixelSeedCorr.selection.photonGenPdgId         = 11
	
	
	# ==1 Photon, >=3jets +++++BKG++++ FO
	process.select_1ph_3jets_FO                            = process.select_1ph_3jets.clone();
	process.select_1ph_3jets_FO.selection.photonSrc        = ('myphotonselectionFO')
	process.select_1ph_3jets_FO.selection.cutsToUse        = cms.vstring(">= 3 Jets",">= 1 Photons","HTHLT",
									     "photonEta","jetPt","jetEta","MET",
									     "photonPtCor","photonJetMatch","photonTightMatch")
	process.select_1ph_3jets_FO.cutsForPresel              = cms.vstring(">= 3 Jets",">= 1 Photons","HTHLT",
									     "photonEta","jetPt","jetEta",
									     "photonPtCor","photonJetMatch","photonTightMatch")
	process.select_1ph_3jets_FO.selection.photonJetMatch   = 1
	process.select_1ph_3jets_FO.selection.photonTightMatch = 1
	process.select_1ph_3jets_FO.selection.isPhotonFO       = True

	# ==1 Photon, >=3jets +++++BKG++++ FO Corr+++ Estimate after application of FakeRate
	######################################################
	####### !!!!!!!!!!!!! HERE 3Jet !!!!!!!!!!!!! ########
	######################################################
	process.select_1ph_3jets_FO_Corr                                      = process.select_1ph_3jets_FO.clone();
	process.select_1ph_3jets_FO_Corr.applyFakeRateSystFit                 = 0.10
	process.select_1ph_3jets_FO_Corr.applyFakeRateSystLowHighMet          = 0.05
	process.select_1ph_3jets_FO_Corr.applyFakeRateSystSMCont              = 0.00
	process.select_1ph_3jets_FO_Corr.selection.photonSrc                  = ('myphotonselectionFO')
	process.select_1ph_3jets_FO_Corr.applyFakeRateCorrection              = True
	process.select_1ph_3jets_FO_Corr.applyFakeRateCorrectionHT            = True
	process.select_1ph_3jets_FO_Corr.applyFakeRateCorrectionHistoNameHT = "QCDEst_HT_Data"
	
	process.select_1ph_3jets_FO_CorrMC                                    = process.select_1ph_3jets_FO_Corr.clone();
	process.select_1ph_3jets_FO_CorrMC.applyFakeRateSystFit               = 0.25
	process.select_1ph_3jets_FO_CorrMC.applyFakeRateSystLowHighMet        = 0.05
	process.select_1ph_3jets_FO_CorrMC.applyFakeRateSystSMCont            = 0.00
	process.select_1ph_3jets_FO_CorrMC.applyFakeRateCorrectionHT          = True	
	process.select_1ph_3jets_FO_CorrMC.applyFakeRateCorrectionHistoNameHT = "QCDEst_HT_MC"


	
	################################################################################################
	# ==1 Photon, >=2jets, Btagging
	################################################################################################
	process.select_1ph_2jets_1b                     = process.selectionPlotMaker.clone();
	process.select_1ph_2jets_1b.selection.cutsToUse = cms.vstring(">= 2 Jets",">= 1 Photons","HTHLT",
								      "photonEta","jetPt","jetEta","MET",
								      ">= 1 bJets","photonPtCor")
	process.select_1ph_2jets_1b.cutsForN1           = cms.vstring("MET","photonEta")
	process.select_1ph_2jets_1b.cutsForPresel       = cms.vstring(">= 2 Jets",">= 1 Photons","HTHLT",
								      "photonEta","jetPt","jetEta",
								      ">= 1 bJets","photonPtCor")
	process.select_1ph_2jets_1b.selection.requireGenForSelection = False
	
	# ==1 Photon, =2jets +++++BKG++++ Fake electron/noPixelSeedVetoPhoton
	process.select_1ph_2jets_1b_PixelSeed                     = process.select_1ph_2jets_1b.clone();
	process.select_1ph_2jets_1b_PixelSeed.selection.photonSrc = ('myphotonselectionPixelSeed')
	
	# ==1 Photon, >=2jets +++++BKG++++ Fake electron/noPixelSeedVetoPhoton FakeRateApplied!
	process.select_1ph_2jets_1b_PixelSeedCorr                            = process.select_1ph_2jets_1b.clone();
	process.select_1ph_2jets_1b_PixelSeedCorr.selection.photonSrc        = ('myphotonselectionPixelSeed')
	process.select_1ph_2jets_1b_PixelSeedCorr.applyEWKFakeRateCorrection = True
	if isData is True:
		process.select_1ph_2jets_1b_PixelSeedCorr.applyEWKFakeRatePar1       = 0.0157 # DATA #
		process.select_1ph_2jets_1b_PixelSeedCorr.applyEWKFakeRateParErr1    = 0.0080
	else:
		process.select_1ph_2jets_1b_PixelSeedCorr.applyEWKFakeRatePar1       = 0.0084 #  MC  #
		process.select_1ph_2jets_1b_PixelSeedCorr.applyEWKFakeRateParErr1    = 0.0009
	
	# ==1 Photon, =2jets +++++BKG++++ FO Corr+++ Estimate after application of FakeRate
	process.select_1ph_2jets_1b_FO_Corr                                    = process.select_1ph_2jets_1b.clone();
	process.select_1ph_2jets_1b_FO_Corr.selection.cutsToUse                     = cms.vstring(">= 2 Jets",">= 1 Photons","HTHLT",">= 1 bJets",
												  "photonEta","jetPt","jetEta","MET",
												  "photonPtCor","photonJetMatch","photonTightMatch")
	process.select_1ph_2jets_1b_FO_Corr.cutsForPresel                           = cms.vstring(">= 2 Jets",">= 1 Photons","HTHLT",">= 1 bJets",
												  "photonEta","jetPt","jetEta",
												  "photonPtCor","photonJetMatch","photonTightMatch")
	process.select_1ph_2jets_1b_FO_Corr.selection.isPhotonFO               = True
	process.select_1ph_2jets_1b_FO_Corr.selection.photonJetMatch           = 1
	process.select_1ph_2jets_1b_FO_Corr.selection.photonTightMatch         = 1
	process.select_1ph_2jets_1b_FO_Corr.applyFakeRateSystFit               = 0.10
	process.select_1ph_2jets_1b_FO_Corr.applyFakeRateSystLowHighMet        = 0.05
	process.select_1ph_2jets_1b_FO_Corr.applyFakeRateSystSMCont            = 0.00
	process.select_1ph_2jets_1b_FO_Corr.selection.photonSrc                = ('myphotonselectionFO')
	process.select_1ph_2jets_1b_FO_Corr.applyFakeRateCorrection            = True
       	process.select_1ph_2jets_1b_FO_Corr.applyFakeRateCorrectionHT          = True	
	process.select_1ph_2jets_1b_FO_Corr.applyFakeRateCorrectionHistoNameHT = "QCDEst_HT_Data"


	process.select_1ph_2jets_1b_FO_CorrMC                                    = process.select_1ph_2jets_1b_FO_Corr.clone();
	process.select_1ph_2jets_1b_FO_CorrMC.applyFakeRateSystFit               = 0.20
	process.select_1ph_2jets_1b_FO_CorrMC.applyFakeRateSystLowHighMet        = 0.05
	process.select_1ph_2jets_1b_FO_CorrMC.applyFakeRateSystSMCont            = 0.00
       	process.select_1ph_2jets_1b_FO_CorrMC.applyFakeRateCorrectionHT          = True	
	process.select_1ph_2jets_1b_FO_CorrMC.applyFakeRateCorrectionHistoNameHT = "QCDEst_HT_MC"


	#####################################################################################
	###### FILTER #######################################################################
                                    
	# Jet count filter
	from PhysicsTools.PatAlgos.selectionLayer1.jetCountFilter_cfi import countPatJets
	process.myjetselectionFilter = countPatJets.clone(
		src = 'myjetselection',
		minNumber = 2
	       )
	
	# Photon count filter
	from PhysicsTools.PatAlgos.selectionLayer1.photonCountFilter_cfi import countPatPhotons
	process.myphotonselectionFilter = countPatPhotons.clone(
		src = 'myphotonselectionLoose',
		minNumber = 1
	       )
	
	# HT filter		
	filtercutsPreselHT      = process.select_All.selection.clone()
	process.filter_PreselHT = cms.EDFilter( 'WrappedPhotonJetFilter',
						filtercutsPreselHT
					      )

	
	#####################################################################################
	###### Paths & Sequences ############################################################

	print("=========Pfjetsource:",process.pfJetsPFlow.src)
	print("=========process.kt6PFJets.src:",process.kt6PFJets.src)
	print("=========process.kt6PFJetsPFlow.src:",process.kt6PFJetsPFlow.src)
	
	print("=========process.kt6PFJets.Rho_EtaMax:",process.kt6PFJets.Rho_EtaMax)
	print("=========process.kt6PFJetsPFlow.Rho_EtaMax:",process.kt6PFJetsPFlow.Rho_EtaMax)
	
	print("=========patJetCorrFactorsPFlow.rho:",process.patJetCorrFactorsPFlow.rho)
	print("=========process.patJetCorrFactorsPFlow.payload:",process.patJetCorrFactorsPFlow.payload)
	
	###### Dump ###########################################################
        # Dumps all products stored in an event to the screen
	process.dump = cms.EDAnalyzer('EventContentAnalyzer')
	process.p    = cms.Path(process.dump)
	
	###### OutputModule ###################################################
	process.out = cms.OutputModule("PoolOutputModule",
				       fileName = cms.untracked.string(skimName),
				       SelectEvents = cms.untracked.PSet( SelectEvents = cms.vstring('selectionSequence') ),
				       outputCommands = cms.untracked.vstring(
		'drop *',
		'keep *_muons_*_*',
		'keep *_muonMETValueMapProducer_*_*',
		'keep *_generator_*_*',
		'keep patPhotons_*_*_*',
		'keep *Photon_*_*_*',
		'keep *PhotonCores_*_*_*',
		'keep patElectrons_*_*_*',
		'keep bool_*_*_*',
		'keep *_selectedPhotonsWithRhoAndIsos*_*_*',
		'keep *_patConversions*_*_*',
		'keep patMuons_*_*_*',
		'keep patMet_*_*_*',
		'keep *_genParticles_*_*',
		'keep *_ak5CaloJets_*_*',
		'keep *CaloJets_*_*_*',
		'keep *PFJets_*_*_*',
		'keep *_ak5GenJets*_*_*',
		'keep *_*PFJets_*_*',
		'keep *_pfJetsPFlow*_*_*',
		'keep *_particleFlow_*_*',
		'keep *_met_*_*',
		'keep *_pfMet_*_*',
		'keep *_tcMet_*_*',
		'keep patJets_*_*_*',
		'keep *_selectedPatJets*_*_*',
		'keep *_corMetType*_*_*',
		'keep *_mylayer1METs*_*_*',
		'keep *_HBHENoiseFilterResultProducer_*_*',
		'keep *_TriggerResults_*_HLT',
		'keep *_TriggerResults_*_REDIGI*',
		'keep *_offlinePrimaryVertices_*_*',
		'keep *_oneGoodVertexNoProducer_*_*',
		'keep *_offlinePrimaryVertices_*_*',
		'keep *_weightProducer_*_*',
		'keep *_pfNoJetPFlow_*_*',
		'keep *_*addPileupInfo*_*_*',
		'keep double_*_rho_*',
		'keep *_goodOfflinePrimaryVertices*_*_*',
		'keep *_reducedEcalRecHitsEB*_*_*',
		'keep *_reducedEcalRecHitsEE*_*_*', 
		'keep *_pfchsMETcorr*_*_*', 
		'keep *_*generalTracks*_*_*',
		'keep *_puJetId*_*_*', # input variables
		'keep *_puJetMva*_*_*' # final MVAs and working point flags
		)
	)

	process.outPat = cms.OutputModule( "PoolOutputModule",
					   fileName = cms.untracked.string(skimName),
					   SelectEvents = cms.untracked.PSet( SelectEvents = cms.vstring('selectionSequence') ),
					   outputCommands = cms.untracked.vstring('drop *')
					 )
	
	process.outAll = cms.OutputModule( "PoolOutputModule",
					   fileName = cms.untracked.string(skimName),
					   outputCommands = cms.untracked.vstring( 'keep *' )
					 )
	
	process.rmAll = cms.OutputModule( "PoolOutputModule",
					  fileName = cms.untracked.string(skimName),
					  outputCommands = cms.untracked.vstring( 'drop *' )
					)

	
	process.e      = cms.EndPath(process.out)
	process.ePat   = cms.EndPath(process.outPat)
	process.eAll   = cms.EndPath(process.outAll)
	process.eRmAll = cms.EndPath(process.rmAll)
	

	###### DrawerModule ###################################################
	process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
	
	process.printTree = cms.EDAnalyzer( "ParticleTreeDrawer",
					    src           = cms.InputTag("genParticles"),
					    printP4       = cms.untracked.bool(False),
					    printPtEtaPhi = cms.untracked.bool(True),
					    printVertex   = cms.untracked.bool(False),
					    printStatus   = cms.untracked.bool(True),
					    printIndex    = cms.untracked.bool(False),
					    status        = cms.untracked.vint32(1,3)
					  )

	process.printTreeList = cms.EDAnalyzer( "ParticleListDrawer",
						maxEventsToPrint = cms.untracked.int32(0),
						printVertex      = cms.untracked.bool(False),
						src              = cms.InputTag("genParticles")
					      )
    
	
	###### Execution Path #################################################
	# Configure process options
	process.options = cms.untracked.PSet(
		wantSummary = cms.untracked.bool(True),
		SkipEvent = cms.untracked.vstring('ProductNotFound')
	       ) 

	print("execution path")


	if doSkimming is True or doTriggerEffStudy is True:
		if  sampleConf == 10 : #DATA
			if doTriggerEffStudy == True:
				process.selectionSequence = cms.Path(process.oneGoodVertexFilter*process.applyTechnicalPreselectionDataTriggerStudies)
			else:
				process.selectionSequence = cms.Path(process.oneGoodVertexFilter*process.applyTechnicalPreselectionData2010)
		else: #MC
			process.selectionSequence = cms.Path(process.oneGoodVertexFilter*process.applyTechnicalPreselectionMC)
		# Analysis on AOD
		process.selectionSequence *= (process.goodOfflinePrimaryVertices*process.patDefaultSequence+process.patseq)

		process.selectionSequence *=  process.selectedPhotonsWithRho	
	
		process.selectionSequence *= process.pfParticleSelectionSequence+process.phoIsoSequence
		process.selectionSequence *= process.selectedPhotonsWithRhoAndIsos
		process.selectionSequence *= process.patConversions
		process.selectionSequence *= process.kt6PFJetsBarrel*process.pfchsMETcorr

	else: #Analysis on PATTuples
		process.selectionSequence = cms.Path(process.oneGoodVertexFilter)
	
	if isMC == True :
		process.selectionSequence *= process.weightProducer


	# Object Selection
	process.selectionSequence *= process.myjetselection*process.myphotonselection*process.myphotonselectionPixelSeed*process.myphotonselectionFO*process.myphotonselectionLoose*process.myphotonselectionHLT
        # Object Cleaning
	process.selectionSequence *= process.cleanPatJetsIsolatedLeptonsCalo*process.cleanPatJetsIsolatedLeptonsPF
	# MET Selection
	process.selectionSequence *= process.makemyLayer1METs*process.makemyLayer1METsPF*process.mylayer1METsRawPF*process.mylayer1METsRaw

	if sampleConf == 10 : #DATA
		process.selectionSequence *= process.EcalDeadCellTriggerPrimitiveFilter
				
	# run the PU JetID sequence
	if doFastJEC is True:
		process.selectionSequence *= process.puJetIdSqeuenceChs
		# process.selectionSequence *= process.puJetIdChs*process.puJetMvaChs
	else:
		process.selectionSequence *= process.puJetIdSqeuence
		# process.selectionSequence *= process.puJetId*process.puJetMva


	if noKinematicPresel == False:
		process.selectionSequence *= process.myjetselectionFilter*process.myphotonselectionFilter*process.filter_PreselHT


	process.selectionSequence *= process.selectionPlotMaker
	process.selectionSequence *= process.select_All


	
	if doAnalysis is True:
		if isTest is True:
			process.selectionSequence *= process.myjetselectionFilter*process.myphotonselectionFilter*process.filter_PreselHT*process.selectionPlotMaker

		else:
		    
			if quickScanForQCDEstOnly is False: #Always
			    
				# process.selectionSequence *= process.select_1ph_3jets_PixelSeed*process.select_1ph_3jets_PixelSeedCorr
				process.selectionSequence *= process.select_1ph_2jets_PixelSeed*process.select_1ph_2jets_PixelSeedCorr
				# process.selectionSequence *= process.select_1ph_3jets_GenEleVetoPixelSeedCorr*process.select_1ph_3jets_GenEleVetoPixelSeed*process.select_1ph_3jets_GenEleVeto
				# process.selectionSequence *= process.select_1ph_3jets_GenEleVetoRePixelSeedCorr*process.select_1ph_3jets_GenEleVetoRePixelSeed*process.select_1ph_3jets_GenEleVetoRe
				process.selectionSequence *= process.select_1ph_2jets_GenEleVetoPixelSeedCorr*process.select_1ph_2jets_GenEleVetoPixelSeed*process.select_1ph_2jets_GenEleVeto
				process.selectionSequence *= process.select_1ph_2jets_GenEleVetoRePixelSeedCorr*process.select_1ph_2jets_GenEleVetoRePixelSeed*process.select_1ph_2jets_GenEleVetoRe
				process.selectionSequence *= process.select_1ph_2jets_1b_PixelSeed*process.select_1ph_2jets_1b_PixelSeedCorr

			# process.selectionSequence *= process.select_1ph_3jets
			process.selectionSequence *= process.select_1ph_2jets
			process.selectionSequence *= process.select_1ph_2jets_1b
			
			# process.selectionSequence *= process.select_1ph_3jets_FO
			process.selectionSequence *= process.select_1ph_2jets_FO
		    
			# process.selectionSequence *= process.select_1ph_3jets_FO_Corr
			# process.selectionSequence *= process.select_1ph_3jets_FO_CorrMC

                        if isData is True:
				process.selectionSequence *= process.select_1ph_2jets_FO_Corr
			else:
				process.selectionSequence *= process.select_1ph_2jets_FO_CorrMC

			process.selectionSequence *= process.select_1ph_2jets_1b_FO_Corr
						

	if doTriggerEffStudy is True:
		process.selectionSequence *= process.myphotonselectionTRIGGEREFF
		process.selectionSequence *= process.myphotonselectionTRIGGEREFFPS
		process.selectionSequence *= process.myphotonselectionTRIGGEREFFFO
		
		process.selectionSequence *= (process.select_All_HT_Denominator+process.select_All_Photon_Denominator+process.select_All_HT_Denominator_PS+process.select_All_Photon_Denominator_PS+process.select_All_HT_Denominator_FO+process.select_All_Photon_Denominator_FO)
		process.selectionSequence *= process.photon2012_HLT_data*(process.select_All_HT_Nominator+process.select_All_Photon_Nominator+process.select_All_HT_Nominator_PS+process.select_All_Photon_Nominator_PS+process.select_All_HT_Nominator_FO+process.select_All_Photon_Nominator_FO)
		
		
	
	print(process.selectionSequence)
	
	print("GenJetMatching:")
	print(process.patJetGenJetMatch.src)
	print(process.patJetGenJetMatchPFlow.src)
	print(process.patJetGenJetMatch.matched)
	print(process.patJetGenJetMatchPFlow.matched)
	
	print(process.patJetGenJetMatch.maxDPtRel)
	
	print(process.photonMatch.src)
	print(process.photonMatch.mcPdgId)
    
	if doSkimming is False:
		print("---Analysis only---")
		process.schedule = cms.Schedule(process.selectionSequence,process.ePat)
	else:
		print("---write SKIM---!")
		process.schedule = cms.Schedule(process.selectionSequence,process.e)
	
	if dump is True: #FALSE
		process.schedule = cms.Schedule(process.selectionSequence,process.p,process.eAll)

        open('dumpConfig.py','w').write(process.dumpPython())
