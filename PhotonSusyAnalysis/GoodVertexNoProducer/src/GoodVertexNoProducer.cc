// -*- C++ -*-
//
// Package:    GoodVertexNoProducer
// Class:      GoodVertexNoProducer
// 
/**\class GoodVertexNoProducer GoodVertexNoProducer.cc PhotonSusyAnalysis/GoodVertexNoProducer/src/GoodVertexNoProducer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Christian Autermann
//         Created:  Tue Nov 27 14:13:23 CET 2012
// $Id: GoodVertexNoProducer.cc,v 1.1 2012/11/27 13:35:13 auterman Exp $
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
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"


//
// class declaration
//

class GoodVertexNoProducer : public edm::EDProducer {
   public:
      explicit GoodVertexNoProducer(const edm::ParameterSet&);
      ~GoodVertexNoProducer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() ;
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      virtual void beginRun(edm::Run&, edm::EventSetup const&);
      virtual void endRun(edm::Run&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);

      // ----------member data ---------------------------
      edm::InputTag vertexSrc;        
      unsigned int minNDOF;
      double maxAbsZ;
      double maxd0;
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
GoodVertexNoProducer::GoodVertexNoProducer(const edm::ParameterSet& iConfig)
{
  vertexSrc = iConfig.getParameter<edm::InputTag>("vertexCollection");
  minNDOF = iConfig.getParameter<unsigned int>("minimumNDOF");
  maxAbsZ = iConfig.getParameter<double>("maxAbsZ");
  maxd0 = iConfig.getParameter<double>("maxd0");

  produces<int>("noGoodVertices");
}


GoodVertexNoProducer::~GoodVertexNoProducer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
GoodVertexNoProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
 int noGoodVertices=0;
 edm::Handle<reco::VertexCollection> pvHandle; 
 iEvent.getByLabel(vertexSrc,pvHandle);
 const reco::VertexCollection & vertices = *pvHandle.product();
 for(reco::VertexCollection::const_iterator it=vertices.begin() ; it!=vertices.end() ; ++it)
  {
      if(it->ndof() > minNDOF && 
         ( (maxAbsZ <=0 ) || fabs(it->z()) <= maxAbsZ ) &&
         ( (maxd0 <=0 ) || fabs(it->position().rho()) <= maxd0 )
         ) noGoodVertices++;
  }
 


       std::auto_ptr< int > pNoGoodVertices(new int);

        *pNoGoodVertices=noGoodVertices;

        iEvent.put(pNoGoodVertices, "noGoodVertices");
 
}

// ------------ method called once each job just before starting event loop  ------------
void 
GoodVertexNoProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
GoodVertexNoProducer::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void 
GoodVertexNoProducer::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
GoodVertexNoProducer::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
GoodVertexNoProducer::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
GoodVertexNoProducer::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
GoodVertexNoProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(GoodVertexNoProducer);
