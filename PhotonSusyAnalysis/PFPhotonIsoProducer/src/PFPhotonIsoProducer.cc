// -*- C++ -*-
//
// Package:    PFPhotonIsoProducer
// Class:      PFPhotonIsoProducer
// 
/**\class PFPhotonIsoProducer PFPhotonIsoProducer.cc PhotonSusyAnalysis/PFPhotonIsoProducer/src/PFPhotonIsoProducer.cc

 Description: [one line class summary]

 Implementation:
 [Notes on implementation]
 */
//
// Original Author:  Malte Hoffmann,,,UniHamburg
//         Created:  Wed May  2 14:29:30 CEST 2012
// $Id: PFPhotonIsoProducer.cc,v 1.2 2012/12/10 08:26:00 kiesel Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include <FWCore/Framework/interface/ESHandle.h>

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"

#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"
#include "DataFormats/EgammaCandidates/interface/Conversion.h"

#include "DataFormats/EgammaReco/interface/SuperCluster.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"

#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"

#include "Geometry/CaloTopology/interface/CaloTopology.h"
//#include "Geometry/CaloEventSetup/interface/CaloTopologyRecord.h"
#include "Geometry/Records/interface/CaloTopologyRecord.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterTools.h"

#include "EGamma/EGammaAnalysisTools/src/PFIsolationEstimator.cc"

#include <TMath.h>

//
// class declaration
//
using namespace std;

class PFPhotonIsoProducer: public edm::EDProducer {
public:
	explicit PFPhotonIsoProducer(const edm::ParameterSet&);
	~PFPhotonIsoProducer();

	static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
	virtual void beginJob();
	virtual void produce(edm::Event&, const edm::EventSetup&);
	virtual void endJob();

	virtual void beginRun(edm::Run&, edm::EventSetup const&);
	virtual void endRun(edm::Run&, edm::EventSetup const&);
	virtual void beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
	virtual void endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);

	// ----------member data ---------------------------
	std::vector<edm::InputTag> inputTagIsoDepPhotons_;
	std::vector<edm::InputTag> inputTagIsoValPhotonsPFId_;
	edm::InputTag inputTagPhotons_;
	typedef std::vector<edm::Handle<edm::ValueMap<reco::IsoDeposit> > > IsoDepositMaps;
	typedef std::vector<edm::Handle<edm::ValueMap<double> > > IsoDepositVals;
};

//
// constants, enums and typedefs
//


//
// static data member definitions
//

//
// constructors and destructor
//

PFPhotonIsoProducer::PFPhotonIsoProducer(const edm::ParameterSet& iConfig) {

	//now do what ever other initialization is needed
	inputTagPhotons_ = iConfig.getParameter<edm::InputTag> ("Photons");
	inputTagIsoDepPhotons_ = iConfig.getParameter<std::vector<edm::InputTag> > ("IsoDepPhoton");
	inputTagIsoValPhotonsPFId_ = iConfig.getParameter<std::vector<edm::InputTag> > ("IsoValPhoton");
	produces<std::vector<pat::Photon> > ();

}

PFPhotonIsoProducer::~PFPhotonIsoProducer() {

	// do anything here that needs to be done at desctruction time
	// (e.g. close files, deallocate resources etc.)

}

//
// member functions
//

// ------------ method called to produce the data  ------------
void PFPhotonIsoProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
	using namespace edm;

	edm::Handle < pat::PhotonCollection > photonH;
	bool found = iEvent.getByLabel(inputTagPhotons_, photonH);
	if (!found) {
	  std::ostringstream err;
	  err << "Cannot get Photons: " << inputTagPhotons_ << std::endl;
	  edm::LogError("PFIsoReaderDemo") << err.str();
	  throw cms::Exception("MissingProduct", err.str());
	}

	// get the iso deposits. 3 (charged hadrons, photons, neutral hadrons)
	unsigned nTypes = 3;
	IsoDepositMaps photonIsoDep(nTypes);
	for (size_t j = 0; j < inputTagIsoDepPhotons_.size(); ++j) {
		iEvent.getByLabel(inputTagIsoDepPhotons_[j], photonIsoDep[j]);
	}
	IsoDepositVals photonIsoValPFId(nTypes);
	for (size_t j = 0; j < inputTagIsoValPhotonsPFId_.size(); ++j) {
		iEvent.getByLabel(inputTagIsoValPhotonsPFId_[j], photonIsoValPFId[j]);
	}

	// Photons
	const IsoDepositVals * photonIsoVals = &photonIsoValPFId;
	auto_ptr < vector<pat::Photon> > photonColl(new vector<pat::Photon> (*photonH));

	unsigned npho = photonH->size();


	// Tools for electron vetoing (Photon ID)
	// https://twiki.cern.ch/twiki/bin/view/CMS/ConversionTools
	edm::Handle < reco::BeamSpot > bsHandle;
	iEvent.getByLabel("offlineBeamSpot", bsHandle);
	const reco::BeamSpot &beamspot = *bsHandle.product();

	edm::Handle < reco::ConversionCollection > hConversions;
	iEvent.getByLabel("allConversions", hConversions);

	edm::Handle< reco::GsfElectronCollection > hElectrons;
	iEvent.getByLabel("gsfElectrons", hElectrons);
	//	iEvent.getByLabel(inputTagElectrons_, hElectrons);


	// To implement 'Alternate Code' for Iso variables
	PFIsolationEstimator isolator;
	isolator.initializePhotonIsolation(kTRUE);
	isolator.setConeSize(0.3);

	edm::Handle<reco::PFCandidateCollection> pfH;
	try {
	  iEvent.getByLabel("particleFlow",pfH);
	}
	catch(cms::Exception& e) {
	  edm::LogError("PFIsoReaderDemo") << "PFCandidate is not available!!!" << e.what();
	}
	
	edm::Handle<reco::VertexCollection> vtxH;
	try {
	  iEvent.getByLabel("offlinePrimaryVertices",vtxH);
	}
	catch(cms::Exception& e) {
	  edm::LogError("PFIsoReaderDemo") << "VertexCollection is not available!!!" << e.what();
	}


	// To get sigmaIphiIphi variable
	edm::Handle<EcalRecHitCollection> barrelRecHitsHandle;
	edm::ESHandle<CaloTopology> ctH;
	const CaloTopology* caloTopology = 0;

	try {
	  iEvent.getByLabel("reducedEcalRecHitsEB","",barrelRecHitsHandle);
	}
	catch(cms::Exception& e) {
	  edm::LogError("PFIsoReaderDemo") << "EcalRecHitCollection is not available!!! " << e.what();
	}
 
	try {
	  iSetup.get<CaloTopologyRecord>().get(ctH); 
	  caloTopology = ctH.product();
	}
	catch(cms::Exception& e) {
	  edm::LogError("PFIsoReaderDemo") << "CaloTopologyRecord is not available!!!" << e.what();
	  throw cms::Exception("MissingProduct", "CaloTopologyRecord is not available!!!");
	}


	// Tools for Photon ID
	double neutral = 0.;
	double charged = 0.;
	double photon  = 0.;

	double nhIso = 0.;
	double chIso = 0.;
	double phIso = 0.;

	double EAnh = 0.;
	double EAch = 0.;
	double EAph = 0.;

	double neutralIsoCor = 0.;
	double chargedIsoCor = 0.;
	double photonIsoCor  = 0.;

	int isPromptElectronSafe = 0;

	double sigmaIphiIphi = 1.;


	for (unsigned ipho = 0; ipho < npho; ++ipho) {
	  pat::PhotonRef myPhotonRef(photonH, ipho);
	  pat::Photon & phot = (*photonColl)[ipho];


	  // Deposit Iso Variables
	  neutral = (*(*photonIsoVals)[2])[myPhotonRef];
	  charged = (*(*photonIsoVals)[0])[myPhotonRef];
	  photon  = (*(*photonIsoVals)[1])[myPhotonRef];

	  phot.addUserFloat("neutralIsoDep", (float) neutral);
	  phot.addUserFloat("chargedIsoDep", (float) charged);
	  phot.addUserFloat("photonIsoDep", (float) photon);


	  // Alternate Code Iso Variables
	  // https://twiki.cern.ch/twiki/bin/view/CMS/EgammaPFBasedIsolation#Example_for_photons
	  reco::VertexRef primVtxRef(vtxH, 0);
	  //	  isolator.fGetIsolation(&phot,pfH.product(),primVtxRef,vtxH);
	  //	  isolator.fGetIsolation(phot.photonCore(),pfH.product(),primVtxRef,vtxH);

	  edm::Ptr<reco::Candidate> recoPhoRef = phot.originalObjectRef();
	  const reco::Photon *recoPhoton = dynamic_cast<const reco::Photon *>(recoPhoRef.get());

	  isolator.fGetIsolation(recoPhoton,pfH.product(),primVtxRef,vtxH);
 
	  nhIso = isolator.getIsolationNeutral();
	  chIso = isolator.getIsolationCharged();
	  phIso = isolator.getIsolationPhoton();
        
	  phot.addUserFloat( "neutralIsoAlt", (float) nhIso );
	  phot.addUserFloat( "chargedIsoAlt", (float) chIso );
	  phot.addUserFloat( "photonIsoAlt",  (float) phIso );
	  /*
	  cout << "VS!!! -> nhI = " << nhIso << " or " << neutral
	       <<        ", chI = " << chIso << " or " << charged
	       <<        ", phI = " << phIso << " or " << photon
	       << endl;
	  */
	  // only barrel is considered
	  // for reference -> https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedPhotonID2012
	  if     ( abs(phot.eta()) < 1.    ) EAnh = 0.030;
	  else if( abs(phot.eta()) < 1.479 ) EAnh = 0.057;
	  else                               EAnh = 0.;

	  if     ( abs(phot.eta()) < 1.    ) EAch = 0.012;
	  else if( abs(phot.eta()) < 1.479 ) EAch = 0.010;
	  else                               EAch = 0.;

	  if     ( abs(phot.eta()) < 1.    ) EAph = 0.148;
	  else if( abs(phot.eta()) < 1.479 ) EAph = 0.130;
	  else                               EAph = 0.;

	  phot.addUserFloat( "EAnh", (float) EAnh );
	  phot.addUserFloat( "EAch", (float) EAch );
	  phot.addUserFloat( "EAph", (float) EAph );


	  double rho = (double) phot.userFloat("rhoPU");


	  neutralIsoCor = max( nhIso - rho*EAnh, 0. );
	  chargedIsoCor = max( chIso - rho*EAch, 0. );
	  photonIsoCor  = max( phIso - rho*EAph, 0. );

	  phot.addUserFloat( "neutralIsoCor", (float) neutralIsoCor );
	  phot.addUserFloat( "chargedIsoCor", (float) chargedIsoCor );
	  phot.addUserFloat( "photonIsoCor",  (float) photonIsoCor  );


	  // for reference -> https://twiki.cern.ch/twiki/bin/view/CMS/ConversionTools
	  bool passelectronveto = !ConversionTools::hasMatchedPromptElectron(phot.photonCore()->superCluster(), hElectrons, 
									     hConversions, beamspot.position());
	  
	  if( passelectronveto )
	    isPromptElectronSafe = 1;
	  else
	    isPromptElectronSafe = 0;

	  phot.addUserInt( "isPromptElectronSafe",  isPromptElectronSafe );

	  if(phot.photonCore()->superCluster().isNonnull()) {
	    const reco::BasicCluster& seedClus = *(phot.photonCore()->superCluster()->seed());
	    std::vector<float> crysCov = EcalClusterTools::localCovariances(seedClus, barrelRecHitsHandle.product(), 
									    caloTopology);
	    sigmaIphiIphi = std::sqrt(crysCov[2]);
	  }

	  phot.addUserFloat( "sigmaIphiIphi", (float) sigmaIphiIphi );

	}

	iEvent.put(photonColl);
}

// ------------ method called once each job just before starting event loop  ------------
void PFPhotonIsoProducer::beginJob() {
}

// ------------ method called once each job just after ending the event loop
void PFPhotonIsoProducer::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void PFPhotonIsoProducer::beginRun(edm::Run&, edm::EventSetup const&) {
}

// ------------ method called when ending the processing of a run  ------------
void PFPhotonIsoProducer::endRun(edm::Run&, edm::EventSetup const&) {
}

// ------------ method called when starting to processes a luminosity block  ------------
void PFPhotonIsoProducer::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&) {
}

// ------------ method called when ending the processing of a luminosity block  ------------
void PFPhotonIsoProducer::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&) {
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void PFPhotonIsoProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
	//The following says we do not know what parameters are allowed so do no validation
	// Please change this to state exactly what you do use, even if it is no parameters
	edm::ParameterSetDescription desc;
	desc.setUnknown();
	descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE( PFPhotonIsoProducer);
