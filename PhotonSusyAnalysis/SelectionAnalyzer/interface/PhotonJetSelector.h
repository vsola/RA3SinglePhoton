#ifndef PHOTONJETSELECTOR_H_
#define PHOTONJETSELECTOR_H_

#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "PhysicsTools/SelectorUtils/interface/EventSelector.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "PhysicsTools/UtilAlgos/interface/EDFilterWrapper.h"

#include "PhysicsTools/SelectorUtils/interface/JetIDSelectionFunctor.h"
#include "PhysicsTools/SelectorUtils/interface/PFJetIDSelectionFunctor.h"

#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"

//#include "Util/OwnUtil/src/HistoDrawUtil.h"
//#include "Util/OwnUtil/src/PhysicsUtil.h"

#include "DataFormats/METReco/interface/MET.h"

#include <TF1.h>
#include <TH2F.h>
#include <Math/Point3D.h>
#include <boost/algorithm/string.hpp>

#include <vector>

/*
 \class PhotonJetSelector PhotonJet.h "PhysicsTools/FWLite/interface/PhotonJet.h"
 \brief Class of an EventSelector to apply a simple PhotonJet selection

 adapted to SinglePhoton analysis by Ulla Gebbert
 modified by Valentina Sola 16/08/2012
 
 modified by Christian Autermann 22.11.2012
*/
// $Id: PhotonJetSelector.h,v 1.2 2012/11/26 14:24:05 auterman Exp $

class TH1F;

class PhotonJetSelector: public EventSelector {

 public:
	// constructor
	PhotonJetSelector(const edm::ParameterSet & params);

	  // destructor
	  virtual ~PhotonJetSelector();

	  //define object collections
	  std::vector<pat::Jet> selectedJets() const;

	  std::vector<pat::Jet> selectedBJets() const;

	  std::vector<pat::Photon> selectedPhotons() const;

	  std::vector<pat::Photon> selectedPhotonsWithGenMatch() const;

	  // return photon
	  bool isPhotonValid();

	  double const photonptTRIG() const ;

	  double const correctedphotonpt() const;

	  const pat::Photon & photon() const;

	  bool isPhoton2Valid();

	  const pat::Photon & photon2() const;

	  // return jets
	  bool isJetValid();

	  const pat::Jet & jet() const;

	  bool isJet2Valid();

	  const pat::Jet & jet2() const;

	  bool isJet3Valid();

	  const pat::Jet & jet3() const;

	  bool isJet4Valid();

	  const pat::Jet & jet4() const ;

	  bool isbJetValid();

	  const pat::Jet & bjet() const ;

	  bool isbJet2Valid();
	  
	  const pat::Jet & bjet2() const;

	  // return MET
	  bool isMetValid();

	  const pat::MET & met() const;

	  const pat::MET & metRaw() const;

	  const pat::MET & metT1() const ;

	  const pat::MET & metT2() const;

	  const pat::MET & met2() const;

	  //return Filters
	  bool hcalLaserEvent();

	  bool ecalDeadCellBE();

	  bool ecalDeadCellTP();

	  bool trackingFailure();

	  bool hbheNoise();

	  bool eeBadScFilter();

	  bool cscTightHalo();

	  // return mass of SUSY particles
	  int mgluino();

	  int msquark();

	  int mnlsp();


	  const std::string getSignalScanPointName();


	  //HT
	  const double htj() const;


	  const std::string getPhotonJECLevel(pat::Jet jet) const;


	  //HT HLT
	  const double htHLT() const;


	  const double htHLTcalo() const;


	  const double htHLTN90() const;

	  const double htHLTN90Hits() const;


	  const reco::JetID * hltPhotonJetId() const;


	  const double n90HLTPhotonJet() const ;
	  

	  const double hltPhotonJetPt() const ;


	  const double hltPhotonJetPhi() const;
	

	  const double hltVetoedElectronJets() const;

	  const double hltVetoedMuonJets() const ;

	  const double vetoedElectronJets() const;

	  const double vetoedMuonJets() const ;
	  

	  const math::XYZTLorentzVector mhtj() const;


	  const double ht() const;

	  const math::XYZTLorentzVector mht() const;

	  const math::XYZTLorentzVector mt() const;

	  double getDeltaPhiJ1J2() ;
	  
	  double getDeltaPhiJ1Photon();
	  
	  std::vector<double> getEMFPhotonJets();
	
	  std::vector<double> getEMFPhotonJetsInclEFrac();
	
	  std::vector<double> getResponsePhotonJets();	  
	  std::vector<double> getResponsePhotonJetsUncorr();
	
	  std::vector<double> getResponsePhotonJetsL1();
	
	  double getEtRelPhotonJets();
	  
	  std::vector<std::pair<double, double> > getDeltaRVsEtrel();

	  std::vector<std::pair<double, double> > getDeltaRVsEtrelGen();

	  std::vector<std::pair<double, double> > getDeltaRVsEtrelUncorr();

	  double getMinDeltaRPhotonJet();
	
	  std::vector<double> getWeightAndErrorsPerBin(TH1F * h, double val);
	  std::vector<double> getWeightAndErrorsPerBin2D(TH2F * hh, double valPt, double valHt);

	  //systIncl: 0:normal 1:systDown 2:systUp
	  double getFakeRateWeightSYST(double p1, double p2, double p3, double p4, double p5, int systIncl, bool applyHistoCorrection, bool applyHTCorr, TH1F * corrHisto,TH1F * corrHisto2j, TH2F * corrHistoHT, double systFit, double systLowHighMet, double systSMCont) ;

	  double getFakeRateWeight(double p1, double p2, double p3, double p4, double p5, bool applyHistoCorrection, bool applyHTCorr, TH1F * corrHisto, TH1F * corrHisto2j, TH2F * corrHistoHT);
	  
	  int getNoPV();//# of good Vertices

	  int getNoPVPU();//# of good Vertices PU

	  double getMj12();//mass of j1+j2
	
	  double getMj13();//mass of j1+j3
	
	  double getMj23();//mass of j2+j3
	  
	  double getDeltaPhiMetPhoton1();
	
	  double getDeltaPhiMetT1Photon1();
	
	  double getDeltaRMetPhoton1();
	
	  double getDeltaPhiMetJet1() ;
	
	  bool isPunchthroughMuonBJet(int& rpcHits, double& JetPT) ;

	  bool isPunchthroughTrackCounting(int& k, double& JetPT);

	  double getDeltaPhiMetJet2();
	
	  double getDeltaPhiMetJet3();
	
	  using EventSelector::operator();

	  // here is where the selection occurs
	  virtual bool operator ()(const edm::EventBase & event, pat::strbitset & ret);


 protected:
	  void crosscleanSelectedPhotonsAndJets(bool applyPhotonIso);
	

	  bool isJetOverlappingPhoton(const pat::Jet jet, const pat::Photon photon);

	
	  bool isJetBetterPhoton(pat::Jet jet, pat::Photon photon);

	
	  std::vector<pat::Jet> getLeptonCleanedJets(std::vector<pat::Jet> jets, bool isHLTJet = false);


	  std::vector<pat::Jet> getHLTJets(edm::Handle<std::vector<pat::Jet> > jets);


	  std::vector<pat::Jet> getHLTJetsCalo(edm::Handle<std::vector<pat::Jet> > jets);
	

	  std::vector<pat::Jet> getHLTJetPhoton(std::vector<pat::Jet> jets, std::vector<pat::Photon> photons);


	  std::vector<pat::Jet> getCleanJetsJetID(std::vector<pat::Jet> jets);


	  void setScanGeneratorInfo(edm::Handle<LHEEventProduct> lhe);


	  std::vector<pat::Jet> getCleanJets(edm::Handle<std::vector<pat::Jet> > jets);


	  std::vector<pat::Jet> getGenJets(std::vector<pat::Jet> jets);


	  std::vector<pat::Jet> getCleanBJets(std::vector<pat::Jet> jets);
	  

	  std::vector<pat::Jet> getGenBJets(std::vector<pat::Jet> jets);

	  
	  bool hasMatchingElectron(std::vector<pat::Photon>::const_iterator iphoton, edm::Handle<reco::GenParticleCollection> genPartHandle, bool rejectPhotons);
	  

	  std::vector<pat::Photon> getHadrons(std::vector<pat::Photon> photons, edm::Handle<reco::GenParticleCollection> genPartHandle, bool revertSelection);


	  std::vector<pat::Photon> getGenElectrons(std::vector<pat::Photon> photons, edm::Handle<reco::GenParticleCollection> genPartHandle, bool rejectPhotons);


	  std::vector<pat::Photon> getGenPhotons(std::vector<pat::Photon> photons, edm::Handle<reco::GenParticleCollection> genPartHandle, bool rejectElectrons);


	  std::vector<pat::Photon> getCleanPhotons(edm::Handle<std::vector<pat::Photon> > photons);


	  //DEFINE OBJECT COLLECTIONS

	  /// photon input
	  edm::InputTag photonSrc_;

	  /// jet input
	  edm::InputTag jetSrc_;
	  edm::InputTag jetSrcHLT_;
	  edm::InputTag jetSrcHLTcalo_;

	  /// met input
	  edm::InputTag metSrc_;
	  edm::InputTag metSrcRaw_;
	  edm::InputTag metSrcT1_;
	  edm::InputTag metSrcT2_;
	  edm::InputTag metSrc2_;

	  //lepton Veto inputs
	  edm::InputTag electronSrc_;
	  edm::InputTag muonSrc_;

	  //MET Filter inputs
	  edm::InputTag hcalLaserFilterSrc_;
	  edm::InputTag cscTightHaloFilterSrc_;
	  edm::InputTag ecalDeadCellBEFilterSrc_;
	  edm::InputTag ecalDeadCellTPFilterSrc_;
	  edm::InputTag trackingFailureFilterSrc_;
	  edm::InputTag hbheNoiseFilterSrc_;
	  edm::InputTag eeBadScFilterSrc_;

	  /// photon
	  pat::Photon const *photon_;
	  pat::Photon const *photon2_;

	  /// MET
	  pat::MET const *met_;
	  pat::MET const *metRaw_;
	  pat::MET const *metT1_;
	  pat::MET const *metT2_;
	  pat::MET const *met2_;

	  ///jets
	  pat::Jet const *jet_;
	  pat::Jet const *jet2_;
	  pat::Jet const *jet3_;
	  pat::Jet const *jet4_;
	  pat::Jet const *bjet_;
	  pat::Jet const *bjet2_;

	  ///generator parameters	  
	  double msquark_, mgluino_, mnlsp_;
	  bool scanParameterisGluino_;
	  int noPV_, noPVPU_;

	  ///filters
	  bool hcalLaserFilter_, cscTightHaloFilter_, ecalDeadCellBEFilter_, ecalDeadCellTPFilter_, trackingFailureFilter_, hbheNoiseFilter_, eeBadScFilter_;
	  
	  ///selected objects
	  std::vector<pat::Jet> selectedBJets_;
	  std::vector<pat::Jet> selectedJets_;
	  std::vector<pat::Jet> selectedJetsHLT_;
	  std::vector<pat::Jet> selectedJetsHLTcalo_;
	  std::vector<pat::Jet> selectedJetPhotonsHLT_;
	  std::vector<pat::Jet> selectedJetElectronsHLT_;
	  std::vector<pat::Jet> selectedJetMuonsHLT_;
	  std::vector<pat::Photon> selectedPhotons_;
	  std::vector<std::pair<double, double> > deltaRVsEtrel_;
	  std::vector<std::pair<double, double> > deltaRVsEtrelUncorr_;
	  std::vector<std::pair<double, double> > deltaRVsEtrelGen_;
	  std::vector<pat::Jet> selectedPhotonJets_;
	  std::vector<pat::Jet> allPhotonJets_;
	  std::vector<pat::Jet> selectedElectronJets_;
	  std::vector<pat::Jet> selectedMuonJets_;

	  ///physical quantities
	  index_type jet0Index_;
	  index_type jet1Index_;
	  index_type jet2Index_;
	  index_type jet2InclIndex_;
	  index_type jet3Index_;
	  index_type jet4Index_;
	  index_type jet5Index_;
	  index_type bjet0Index_;
	  index_type bjet1Index_;
	  index_type bjet2Index_;
	  index_type photon1Index_;
	  index_type photon1plusIndex_;
	  index_type photon2Index_;
	  index_type metIndex_;
	  index_type deltaPhiJ1J2_;
	  index_type deltaPhiJ1Photon_;
	  index_type deltaRPhotonJet_;
	  index_type deltaPhiMetJet1_;
	  index_type deltaPhiMetJet2_;
	  index_type deltaPhiMetJet3_;
	  index_type Mj12_;
	  index_type Mj23_;
	  index_type Mj13_;
	  index_type HT_;
	  index_type HTHLT_;
	  index_type HTHLTcalo_;
	  index_type HTHLTN90_;
	  index_type HTJ_;
	  index_type MHT_;
	  index_type MHTJ_;
	  index_type MT_;
	  index_type jetPt_;
	  index_type jet2Pt_;
	  index_type jetEta_;
	  index_type photonPt_;
	  index_type photonGenPdgId_;
	  index_type photonGenPdgIdMother_;
	  index_type photonEta_;
	  index_type leptonVeto_;
	  index_type genEleVeto_;
	  index_type genPhotonVeto_;

	  ///boleans
	  bool useGenForSelection_, requireGenForSelection_, preferGenPhotons_;
	  bool isPhotonFO_;
	  bool debug_;

	  std::vector<std::string> allcuts;
	
 public:
	  //get functions
	  std::vector<std::string> getAllCuts() {
	    return allcuts;
	  }
	
	  index_type getBjet0Index() const {
	    return bjet0Index_;
	  }

	  index_type getBjet1Index() const {
	    return bjet1Index_;
	  }

	  index_type getBjet2Index() const {
	    return bjet2Index_;
	  }

	  index_type getJet0Index() const {
	    return jet0Index_;
	  }

	  index_type getJet1Index() const {
	    return jet1Index_;
	  }

	  index_type getJet2Index() const {
	    return jet2Index_;
	  }

	  index_type getJet2InclIndex() const {
	    return jet2InclIndex_;
	  }

	  index_type getJet3Index() const {
	    return jet3Index_;
	  }

	  index_type getJet4Index() const {
	    return jet4Index_;
	  }

	  index_type getJet5Index() const {
	    return jet5Index_;
	  }

	  index_type getMetIndex() const {
	    return metIndex_;
	  }

	  index_type getPhoton1Index() const {
	    return photon1Index_;
	  }

	  index_type getPhoton2Index() const {
	    return photon2Index_;
	  }


	  //cleaning function
	  void resetSelection();

	  //THE END!
};

#endif

