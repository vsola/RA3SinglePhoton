// -*- C++ -*-
//
// Package:    PhotonRhoProducer
// Class:      PhotonRhoProducer
// 
/**\class PhotonRhoProducer PhotonRhoProducer.cc PhotonSusyAnalysis/PhotonRhoProducer/src/PhotonRhoProducer.cc

 Description: [one line class summary]

 Implementation:
 [Notes on implementation]
 */
//
// Original Author:  Ulla Gebbert,,,uni-hamburg
//         Created:  Wed Jul  6 15:38:17 CEST 2011
// $Id: PhotonRhoProducer.cc,v 1.2 2012/12/10 08:26:01 kiesel Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"


#include "DataFormats/PatCandidates/interface/Photon.h"
//
// class declaration
//
using namespace std;
using namespace edm;
class PhotonRhoProducer: public edm::EDProducer {
public:
	explicit PhotonRhoProducer(const edm::ParameterSet&);
	~PhotonRhoProducer();

	static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
	virtual void beginJob();
	virtual void produce(edm::Event&, const edm::EventSetup&);
	virtual void endJob();

	virtual void beginRun(edm::Run&, edm::EventSetup const&);
	virtual void endRun(edm::Run&, edm::EventSetup const&);
	virtual void beginLuminosityBlock(edm::LuminosityBlock&,
			edm::EventSetup const&);
	virtual void endLuminosityBlock(edm::LuminosityBlock&,
			edm::EventSetup const&);
	edm::InputTag src_;
	edm::InputTag srcRho_;
        edm::InputTag srcRhoBarrel_;
	// ----------member data ---------------------------
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
PhotonRhoProducer::PhotonRhoProducer(const edm::ParameterSet& cfg) {
	src_    = cfg.getParameter<edm::InputTag> ("src");
	srcRho_ = cfg.getParameter<edm::InputTag> ("srcRho");
	srcRhoBarrel_ = cfg.getParameter<edm::InputTag> ("srcRhoBarrel");
	produces<std::vector<pat::Photon> > ();

}

PhotonRhoProducer::~PhotonRhoProducer() {

	// do anything here that needs to be done at desctruction time
	// (e.g. close files, deallocate resources etc.)

}

//
// member functions
//

// ------------ method called to produce the data  ------------
void PhotonRhoProducer::produce(edm::Event& evt, const edm::EventSetup& iSetup) {
	using namespace edm;

	Handle<vector<pat::Photon> > photons;
	evt.getByLabel(src_, photons);

	Handle<double> rhoPU;
	evt.getByLabel(srcRho_, rhoPU);
        Handle<double> rhoPUBarrel;
        evt.getByLabel(srcRhoBarrel_, rhoPUBarrel);

	auto_ptr < vector<pat::Photon> > photonColl(new vector<pat::Photon> (*photons));

	for (unsigned int i = 0; i < photonColl->size(); ++i) {
		pat::Photon & p = (*photonColl)[i];

		p.addUserFloat("rhoPU", (float) *rhoPU);

		if(rhoPUBarrel.isValid())
			p.addUserFloat("rhoPUBarrel", (float) *rhoPUBarrel);

	}

	evt.put(photonColl);

}

// ------------ method called once each job just before starting event loop  ------------
void PhotonRhoProducer::beginJob() {
}

// ------------ method called once each job just after ending the event loop  ------------
void PhotonRhoProducer::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void PhotonRhoProducer::beginRun(edm::Run&, edm::EventSetup const&) {
}

// ------------ method called when ending the processing of a run  ------------
void PhotonRhoProducer::endRun(edm::Run&, edm::EventSetup const&) {
}

// ------------ method called when starting to processes a luminosity block  ------------
void PhotonRhoProducer::beginLuminosityBlock(edm::LuminosityBlock&,
		edm::EventSetup const&) {
}

// ------------ method called when ending the processing of a luminosity block  ------------
void PhotonRhoProducer::endLuminosityBlock(edm::LuminosityBlock&,
		edm::EventSetup const&) {
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void PhotonRhoProducer::fillDescriptions(
		edm::ConfigurationDescriptions& descriptions) {
	//The following says we do not know what parameters are allowed so do no validation
	// Please change this to state exactly what you do use, even if it is no parameters
	edm::ParameterSetDescription desc;
	desc.setUnknown();
	descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(PhotonRhoProducer)
;
