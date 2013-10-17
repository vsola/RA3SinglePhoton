#include "PhotonSusyAnalysis/SelectionAnalyzer/interface/PhotonJetSelector.h"

#include "Util/OwnUtil/interface/HistoDrawUtil.h"
#include "Util/OwnUtil/interface/PhysicsUtil.h"

/*
 \class PhotonJetSelector PhotonJet.h "PhysicsTools/FWLite/interface/PhotonJet.h"
 \brief Class of an EventSelector to apply a simple PhotonJet selection

 adapted to SinglePhoton analysis by Ulla Gebbert

 modified by Valentina Sola 16/08/2012

 modified by Christian Autermann 22.11.2012
*/
// $Id: PhotonJetSelector.cc,v 1.5 2012/11/28 14:00:42 auterman Exp $

using namespace std;
using namespace HistoDrawUtil;

// constructor
PhotonJetSelector::PhotonJetSelector(const edm::ParameterSet & params) :
   photonSrc_(params.getParameter<edm::InputTag> ("photonSrc")), 
   photonSrcHLT_(params.getParameter<edm::InputTag> ("photonSrcHLT")), 
   jetSrc_(params.getParameter<edm::InputTag> ("jetSrc")), 
   jetSrcHLT_(params.getParameter<edm::InputTag> ("jetSrcHLT")), 
   metSrc_(params.getParameter<edm::InputTag> ("metSrc")),
   metSrcRaw_(params.getParameter<edm::InputTag> ("metSrcRaw")), 
   metSrcT1_(params.getParameter<edm::InputTag> ("metSrcT1")), 
   metSrcT2_(params.getParameter<edm::InputTag> ("metSrcT2")), 
   metSrc2_(params.getParameter<edm::InputTag> ("metSrc2")),
   electronSrc_(params.getParameter<edm::InputTag> ("electronSrc")), 
   muonSrc_(params.getParameter<edm::InputTag> ("muonSrc")), 
   hcalLaserFilterSrc_(params.getParameter<edm::InputTag> ("hcalLaserFilterSrc")), 
   cscTightHaloFilterSrc_(params.getParameter<edm::InputTag> ("cscTightHaloFilterSrc")),
   ecalDeadCellBEFilterSrc_(params.getParameter<edm::InputTag> ("ecalDeadCellBEFilterSrc")),
   ecalDeadCellTPFilterSrc_(params.getParameter<edm::InputTag> ("ecalDeadCellTPFilterSrc")),
   trackingFailureFilterSrc_(params.getParameter<edm::InputTag> ("trackingFailureFilterSrc")),
   hbheNoiseFilterSrc_(params.getParameter<edm::InputTag> ("hbheNoiseFilterSrc")),
   eeBadScFilterSrc_(params.getParameter<edm::InputTag> ("trackingFailureFilterSrc"))
{

  //clear objects
  bits_.clear();
  intCuts_.clear();
  doubleCuts_.clear();
  cutFlow_.clear();

  debug_ = params.getParameter<bool> ("debug");
  scanParameterisGluino_=params.getParameter<bool> ("scanParameterisGluino");

  //from selectionanalyzer_cfi.py
  double metMin = params.getParameter<double> ("metMin");
	      
  double deltaPhiJ1J2Max     = params.getParameter<double> ("deltaPhiJ1J2");
  double deltaPhiJ1PhotonMax = params.getParameter<double> ("deltaPhiJ1Photon");
  double deltaRPhotonJetMin  = params.getParameter<double> ("deltaRPhotonJet");
  double deltaPhiMetJet1Min  = params.getParameter<double> ("deltaPhiMetJet1");
  double deltaPhiMetJet2Min  = params.getParameter<double> ("deltaPhiMetJet2");
  double deltaPhiMetJet3Min  = params.getParameter<double> ("deltaPhiMetJet3");
  
  double Mj12Max = params.getParameter<double> ("Mj12");
  double Mj23Max = params.getParameter<double> ("Mj23");
  double Mj13Max = params.getParameter<double> ("Mj13");

  double HTMin    = params.getParameter<double> ("HT");
  double HTJMin   = params.getParameter<double> ("HTJ");
  double HTHLTMin = params.getParameter<double> ("HTHLT");
  double MHTMin   = params.getParameter<double> ("MHT");
  double MHTJMin  = params.getParameter<double> ("MHTJ");
  double MTMin    = params.getParameter<double> ("MT");

  double jetPtMin    = params.getParameter<double> ("jetPt");
  double jet2PtMin   = params.getParameter<double> ("jet2Pt");
  double photonPtMin = params.getParameter<double> ("photonPt");

  double photonGenPdgId       = params.getParameter<double> ("photonGenPdgId");
  double photonGenPdgIdMother = params.getParameter<double> ("photonGenPdgIdMother");
  double genEleVeto           = params.getParameter<double> ("genEleVeto");
  double genPhotonVeto        = params.getParameter<double> ("genPhotonVeto");

  double photonEtaMax = params.getParameter<double> ("photonEta");
  double jetEtaMax    = params.getParameter<double> ("jetEta");

  useGenForSelection_     = params.getParameter<bool> ("useGenForSelection");
  requireGenForSelection_ = params.getParameter<bool> ("requireGenForSelection");
  preferGenPhotons_       = params.getParameter<bool> ("preferGenPhotons");
  isPhotonFO_             = params.getParameter<bool> ("isPhotonFO");
  
  //define allcuts
  allcuts.clear();

  allcuts.push_back("photonEta");
  allcuts.push_back("jetEta");
  allcuts.push_back("deltaRPhotonJet");

  allcuts.push_back(">= 2 Photons");
  allcuts.push_back("= 1 Photons");
  allcuts.push_back(">= 1 Photons");
  allcuts.push_back("= 0 Jets");
  allcuts.push_back("= 1 Jets");
  allcuts.push_back("= 2 Jets");
  allcuts.push_back(">= 2 Jets");
  allcuts.push_back(">= 3 Jets");
  allcuts.push_back(">= 4 Jets");
  allcuts.push_back(">= 5 Jets");
  allcuts.push_back("= 0 bJets");
  allcuts.push_back(">= 1 bJets");
  allcuts.push_back(">= 2 bJets");

  allcuts.push_back("HT");
  allcuts.push_back("HTHLT");
  allcuts.push_back("MHT");

  allcuts.push_back("leptonVeto");
  
  allcuts.push_back("jetPt");
  allcuts.push_back("jet2Pt");
  allcuts.push_back("photonPt");
  allcuts.push_back("photonGenPdgId");
  allcuts.push_back("photonGenPdgIdMother");
  allcuts.push_back("genEleVeto");
  allcuts.push_back("genPhotonVeto");
  allcuts.push_back("deltaPhiJ1J2");
  allcuts.push_back("deltaPhiJ1Photon");

  allcuts.push_back("deltaPhiMetJet1");
  allcuts.push_back("deltaPhiMetJet2");
  allcuts.push_back("deltaPhiMetJet3");
  
  allcuts.push_back("Mj12");
  allcuts.push_back("Mj23");
  allcuts.push_back("Mj13");

  allcuts.push_back("HTJ");
  allcuts.push_back("MHTJ");
  allcuts.push_back("MT");
  allcuts.push_back("MET");

  //initialize cut for each entry of allcuts
  for (int cutIt = 0; cutIt < (int) (allcuts.size()); ++cutIt) {
    std::string cut = allcuts.at(cutIt);
    if (cut == "MET") {
      push_back(cut, metMin);
    } else if (cut == "deltaPhiJ1J2") {
      push_back(cut, deltaPhiJ1J2Max);
    } else if (cut == "deltaPhiJ1Photon") {
      push_back(cut, deltaPhiJ1PhotonMax);
    } else if (cut == "deltaRPhotonJet") {
      push_back(cut, deltaRPhotonJetMin);
    } else if (cut == "deltaPhiMetJet1") {
      push_back(cut, deltaPhiMetJet1Min);
    } else if (cut == "deltaPhiMetJet2") {
      push_back(cut, deltaPhiMetJet2Min);
    } else if (cut == "deltaPhiMetJet3") {
      push_back(cut, deltaPhiMetJet3Min);
    } else if (cut == "Mj12") {
      push_back(cut, Mj12Max);
    } else if (cut == "Mj23") {
      push_back(cut, Mj23Max);
    } else if (cut == "Mj13") {
      push_back(cut, Mj13Max);
    } else if (cut == "HT") {
      push_back(cut, HTMin);
    } else if (cut == "HTJ") {
      push_back(cut, HTJMin);
    } else if (cut == "HTHLT") {
      push_back(cut, HTHLTMin);
    } else if (cut == "MHT") {
      push_back(cut, MHTMin);
    } else if (cut == "MHTJ") {
      push_back(cut, MHTJMin);
    } else if (cut == "MT") {
      push_back(cut, MTMin);
    } else if (cut == "jetPt") {
      push_back(cut, jetPtMin);
    } else if (cut == "jet2Pt") {
      push_back(cut, jet2PtMin);
    } else if (cut == "photonPt") {
      push_back(cut, photonPtMin);
    } else if (cut == "photonEta") {
      push_back(cut, photonEtaMax);
    } else if (cut == "jetEta") {
      push_back(cut, jetEtaMax);
    } else if (cut == "photonGenPdgId") {
      push_back(cut, photonGenPdgId);
    } else if (cut == "photonGenPdgIdMother") {
      push_back(cut, photonGenPdgIdMother);
    } else if (cut == "genEleVeto") {
      push_back(cut, genEleVeto);
    } else if (cut == "genPhotonVeto") {
      push_back(cut, genPhotonVeto);
    }
    else {
      push_back(cut);
    }
    set(cut, false);
  }

  if (params.exists("cutsToUse")) {
    std::vector < std::string > cuts = params.getParameter<std::vector<std::string> > ("cutsToUse");
    for (int cutIt = 0; cutIt < (int) (cuts.size()); ++cutIt) {
      std::string cut = cuts.at(cutIt);
      set(cut, true);
    }
  }

  //define index_type objects
  //photon isolation
  jetEta_          = index_type(&bits_, std::string("jetEta"));
  photonEta_       = index_type(&bits_, std::string("photonEta"));
  deltaRPhotonJet_ = index_type(&bits_, std::string("deltaRPhotonJet"));
	      
  // # of photons
  photon1Index_     = index_type(&bits_, std::string("= 1 Photons"));
  photon1plusIndex_ = index_type(&bits_, std::string(">= 1 Photons"));
  photon2Index_     = index_type(&bits_, std::string(">= 2 Photons"));

  // # of jets & bJets
  jet0Index_     = index_type(&bits_, std::string("= 0 Jets"));
  jet1Index_     = index_type(&bits_, std::string("= 1 Jets"));
  jet2Index_     = index_type(&bits_, std::string("= 2 Jets"));
  jet2InclIndex_ = index_type(&bits_, std::string(">= 2 Jets"));
  jet3Index_     = index_type(&bits_, std::string(">= 3 Jets"));
  jet4Index_     = index_type(&bits_, std::string(">= 4 Jets"));
  jet5Index_     = index_type(&bits_, std::string(">= 5 Jets"));
  bjet0Index_    = index_type(&bits_, std::string("= 0 bJets"));
  bjet1Index_    = index_type(&bits_, std::string(">= 1 bJets"));
  bjet2Index_    = index_type(&bits_, std::string(">= 2 bJets"));

  //HT & MHT
  HT_        = index_type(&bits_, std::string("HT"));
  HTHLT_     = index_type(&bits_, std::string("HTHLT"));
  MHT_       = index_type(&bits_, std::string("MHT"));
		
  //leptonVeto
  leptonVeto_ = index_type(&bits_, std::string("leptonVeto"));

  //photon pt
  photonPt_ = index_type(&bits_, std::string("photonPt"));

  //photon gen match pdgid
  photonGenPdgId_ = index_type(&bits_, std::string("photonGenPdgId"));
  photonGenPdgIdMother_ = index_type(&bits_, std::string("photonGenPdgIdMother"));
  genEleVeto_ = index_type(&bits_, std::string("genEleVeto"));
  genPhotonVeto_ = index_type(&bits_, std::string("genPhotonVeto"));

  //jet pts
  jetPt_ = index_type(&bits_, std::string("jetPt"));
  jet2Pt_ = index_type(&bits_, std::string("jet2Pt"));

  //deltaPhi Cuts
  deltaPhiJ1J2_ = index_type(&bits_, std::string("deltaPhiJ1J2"));
  deltaPhiJ1Photon_ = index_type(&bits_, std::string("deltaPhiJ1Photon"));
  deltaPhiMetJet1_ = index_type(&bits_, std::string("deltaPhiMetJet1"));
  deltaPhiMetJet2_ = index_type(&bits_, std::string("deltaPhiMetJet2"));
  deltaPhiMetJet3_ = index_type(&bits_, std::string("deltaPhiMetJet3"));

  //Mj
  Mj12_ = index_type(&bits_, std::string("Mj12"));
  Mj23_ = index_type(&bits_, std::string("Mj23"));
  Mj13_ = index_type(&bits_, std::string("Mj13"));
  
  //met&co
  metIndex_ = index_type(&bits_, std::string("MET"));
  HTJ_ = index_type(&bits_, std::string("HTJ"));
  MHTJ_ = index_type(&bits_, std::string("MHTJ"));
  MT_ = index_type(&bits_, std::string("MT"));

  resetSelection();

  if (params.exists("cutsToIgnore")) {
    setIgnoredCuts(params.getParameter<std::vector<std::string> > ("cutsToIgnore"));
  }

  retInternal_ = getBitTemplate();
}


// destructor
PhotonJetSelector::~PhotonJetSelector() {
}


//define object collections
std::vector<pat::Jet> PhotonJetSelector::selectedJets() const {
  return selectedJets_;
}


std::vector<pat::Jet> PhotonJetSelector::selectedBJets() const {
  return selectedBJets_;
}


std::vector<pat::Photon> PhotonJetSelector::selectedPhotons() const {
  return selectedPhotons_;
}


std::vector<pat::Photon> PhotonJetSelector::selectedPhotonsWithGenMatch() const {
  std::vector<pat::Photon> ret;
  ret.clear();
  for (std::vector<pat::Photon>::const_iterator photonBegin = selectedPhotons_.begin(), photonEnd = selectedPhotons_.end(), iphoton = photonBegin; iphoton != photonEnd; ++iphoton) {

    if (iphoton->genPhoton() != 0) {	      
      if (abs(iphoton->genPhoton()->pdgId()) == cut(photonGenPdgId_, double())) {
        if (abs((iphoton->pt() - iphoton->genPhoton()->pt())) / iphoton->pt() <= 0.1) {
          if (reco::deltaR(*iphoton, *(iphoton->genPhoton())) <= 0.2) {
            ret.push_back(*iphoton);
          }//if deltaR
        }//if photon pt ratio
      }//if pdgId
    }//if genPhoton

  }//for Photon std::vector

  return ret;
}


// return photon
bool PhotonJetSelector::isPhotonValid() {
  return photon_ != 0;
}


double const PhotonJetSelector::photonptTRIG() const {
  if(photon_ != 0)
    return photon_->pt();
  else return 0;
}


double const PhotonJetSelector::correctedphotonpt() const {
  if (photon_->userFloat("ptMatchedJet") != 0) 
    return photon_->userFloat("ptMatchedJet");
  else 
    return photon_->pt();
}


const pat::Photon & PhotonJetSelector::photon() const {
  return *photon_;
}


bool PhotonJetSelector::isPhoton2Valid() {
  return photon2_ != 0;
}


const pat::Photon & PhotonJetSelector::photon2() const {
  return *photon2_;
}


// return jets
bool PhotonJetSelector::isJetValid() {
  return jet_ != 0;
}


const pat::Jet & PhotonJetSelector::jet() const {
  return *jet_;
}


bool PhotonJetSelector::isJet2Valid() {
  return jet2_ != 0;
}


const pat::Jet & PhotonJetSelector::jet2() const {
  return *jet2_;
}


bool PhotonJetSelector::isJet3Valid() {
  return jet3_ != 0;
}


const pat::Jet & PhotonJetSelector::jet3() const {
  return *jet3_;
}


bool PhotonJetSelector::isJet4Valid() {
  return jet4_ != 0;
}


const pat::Jet & PhotonJetSelector::jet4() const {
  return *jet4_;
}


bool PhotonJetSelector::isbJetValid() {
  return bjet_ != 0;
}


const pat::Jet & PhotonJetSelector::bjet() const {
  return *bjet_;
}


bool PhotonJetSelector::isbJet2Valid() {
  return bjet2_ != 0;
}


const pat::Jet & PhotonJetSelector::bjet2() const {
  return *bjet2_;
}


// return MET
bool PhotonJetSelector::isMetValid() {
  return met_ != 0;
}


const pat::MET & PhotonJetSelector::met() const {
  return *met_;
}


const pat::MET & PhotonJetSelector::metRaw() const {
  return *metRaw_;
}


const pat::MET & PhotonJetSelector::metT1() const {
  return *metT1_;
}


const pat::MET & PhotonJetSelector::metT2() const {
  return *metT2_;
}


const pat::MET & PhotonJetSelector::met2() const {
  return *met2_;
}


//return Filters
bool PhotonJetSelector::hcalLaserEvent(){
  return hcalLaserFilter_;
}


bool PhotonJetSelector::ecalDeadCellBE(){
  return ecalDeadCellBEFilter_;
}


bool PhotonJetSelector::ecalDeadCellTP(){
  return ecalDeadCellTPFilter_;
}


bool PhotonJetSelector::trackingFailure(){
  return trackingFailureFilter_;
}


bool PhotonJetSelector::hbheNoise(){
  return hbheNoiseFilter_;
}


bool PhotonJetSelector::eeBadScFilter(){
  return eeBadScFilter_;
}


bool PhotonJetSelector::cscTightHalo(){
  return cscTightHaloFilter_;
}


// return mass of SUSY particles
int PhotonJetSelector::mgluino() {
  return int(mgluino_);
}


int PhotonJetSelector::msquark() {
  return int(msquark_);
}


int PhotonJetSelector::mnlsp() {
  return int(mnlsp_);
}


const std::string PhotonJetSelector::getSignalScanPointName() {
  return removeSpaces( getStringFromInt(msquark()) + "_" 
        	     + getStringFromInt(mgluino()) + "_" 
        	     + getStringFromInt(mnlsp())   );
}


//
const std::string PhotonJetSelector::getPhotonJECLevel(pat::Jet jet) const {

  std::string jecleveltouse = "Uncorrected";
  jecleveltouse = jet.currentJECLevel();

  return jecleveltouse;
}


// HT for Presel
const double PhotonJetSelector::ht() const {
  double ht = 0;

  for (std::vector<pat::Jet>::const_iterator jetsBegin = selectedJets_.begin(), jetsEnd = selectedJets_.end(), ijet = jetsBegin; ijet != jetsEnd; ++ijet) {
    ht += ijet->pt();
  }
  
  for (std::vector<pat::Photon>::const_iterator photonBegin = selectedPhotons_.begin(), photonEnd = selectedPhotons_.end(), iphoton = photonBegin; iphoton != photonEnd; ++iphoton) {
    if (iphoton->userFloat("ptMatchedJet") != 0) {
      ht += iphoton->userFloat("ptMatchedJet");
    } else {
      ht += iphoton->pt();
    }
    break;
  }
  return ht;
}


// HT just from jets
const double PhotonJetSelector::htj() const {
  double ht = 0;
  for (std::vector<pat::Jet>::const_iterator jetsBegin = selectedJets_.begin(), jetsEnd = selectedJets_.end(), ijet = jetsBegin; ijet != jetsEnd; ++ijet) {
    ht += ijet->pt();
  }
  return ht;
}


// HT HLT
const double PhotonJetSelector::htHLT() const {
  double ht = 0;

  cout << "HTHLT" << endl;
  cout << "HTHLT - # of HLT jets = " << selectedJetsHLT_.size() << endl;
  for ( std::vector<pat::Jet>::const_iterator jetsBegin = selectedJetsHLT_.begin(), jetsEnd = selectedJetsHLT_.end(), 
	  ijet = jetsBegin; ijet != jetsEnd; ++ijet ) {
    ht += ijet->pt();
    cout << "HTHLT - selectedJetsHLT_ pT = " << ijet->pt() << endl;
  }//loop on selectedJetsHLT_

  cout << "HTHLT - Intermediate HT = " << ht << endl;

  cout << "HTHLT - # of photons =      " << selectedPhotons_.size() << endl;
  cout << "HTHLT - # of HLT photons =  " << selectedPhotonsHLT_.size() << endl;
  cout << "HTHLT - # of ALL HLT jets = " << selectedJetsHLTAll_.size() << endl;

  int np = 1;

  for ( std::vector<pat::Photon>::const_iterator photonBegin = selectedPhotonsHLT_.begin(), 
	  photonEnd = selectedPhotonsHLT_.end(), iphoton = photonBegin; iphoton != photonEnd; ++iphoton ) {

    double photonPt = iphoton->pt();

    cout << "HTHLT - photonPt = " << photonPt << " for photon # = " << np << endl;

    for ( std::vector<pat::Jet>::const_iterator jetsBegin = selectedJetsHLTAll_.begin(), 
	    jetsEnd = selectedJetsHLTAll_.end(), ijeta = jetsBegin; ijeta != jetsEnd; ++ijeta ) {

      const pat::Jet jet   = *ijeta;
      const pat::Photon ph = *iphoton;

      double deltaR_ = reco::deltaR(ph, jet);
 
      double ETRel = jet.pt() / photon.pt();
      if (jet.jecSetsAvailable() && jet.isPFJet()) 
	ETRel = jet.correctedJet( getPhotonJECLevel(jet) ).pt() / photon.pt();
  
      if ( deltaR_ < 0.3 && ETRel >= 0.95 )
	photonPt = ijeta->pt();      

    }// loop on selectedJetsHLTAll_
    cout << "HTHLT - photonPt = " << photonPt << " for photon # = " << np << endl;

    ht+= photonPt;

    np++;
  }// loop on selectedPhotonsHLT_

  cout << "HTHLT - Final HT = " << ht << endl;
  cout << "HTHLT" << endl;

  
  return ht;
}


//
const double PhotonJetSelector::hltPhotonJetPt() const {
  double pt = 0;
  if (photon_ != 0) {
    pt = photon_->pt();
  }
  return pt;
}


//
const double PhotonJetSelector::hltPhotonJetPhi() const {
  double phi = 0;
  if (photon_ != 0) {
    phi = photon_->phi();
  }
  return phi;
}
	

const double PhotonJetSelector::hltVetoedElectronJets() const {
  return selectedJetElectronsHLT_.size();
}

const double PhotonJetSelector::hltVetoedMuonJets() const {
  return selectedJetMuonsHLT_.size();
}

const double PhotonJetSelector::vetoedElectronJets() const {
  return selectedElectronJets_.size();
}

const double PhotonJetSelector::vetoedMuonJets() const {
  return selectedMuonJets_.size();
}
	  

const math::XYZTLorentzVector PhotonJetSelector::mhtj() const {
  math::XYZTLorentzVector v_ht = math::XYZTLorentzVector();
  for (std::vector<pat::Jet>::const_iterator jetsBegin = selectedJets_.begin(), jetsEnd = selectedJets_.end(), ijet = jetsBegin; ijet != jetsEnd; ++ijet) {
    v_ht += ijet->p4();
  }
  return v_ht;
}


const math::XYZTLorentzVector PhotonJetSelector::mht() const {
  math::XYZTLorentzVector v_ht = math::XYZTLorentzVector();
  for (std::vector<pat::Jet>::const_iterator jetsBegin = selectedJets_.begin(), jetsEnd = selectedJets_.end(), ijet = jetsBegin; ijet != jetsEnd; ++ijet) {
    v_ht += ijet->p4();
  }
  for (std::vector<pat::Photon>::const_iterator jetsBegin = selectedPhotons_.begin(), jetsEnd = selectedPhotons_.end(), ijet = jetsBegin; ijet != jetsEnd; ++ijet) {
    v_ht += ijet->p4();
  }
  return v_ht;
}


const math::XYZTLorentzVector PhotonJetSelector::mt() const {
  math::XYZTLorentzVector v_mt = math::XYZTLorentzVector();
  
  if ( met_ != 0 ) {
    v_mt = met_->p4();
  }
  if ( photon_ != 0 ) {
    v_mt += photon_->p4();
  }
  if ( photon2_ != 0 ) {
    v_mt += photon2_->p4();
  }
  for (std::vector<pat::Jet>::const_iterator jetsBegin = selectedJets_.begin(), jetsEnd = selectedJets_.end(), ijet = jetsBegin; ijet != jetsEnd; ++ijet) {
    v_mt += ijet->p4();
  }

  return v_mt;
}


double PhotonJetSelector::getDeltaPhiJ1J2() {
  if ( jet_ != 0 && jet2_ != 0 ) {
    return abs( PhysicsUtil::GetDeltaPhi(jet_->phi(), jet2_->phi()) );
  } else
    return 0.;
}
	  

double PhotonJetSelector::getDeltaPhiJ1Photon() {
  if ( jet_ != 0 && photon_ != 0 ) {
    return abs( PhysicsUtil::GetDeltaPhi(jet_->phi(), photon_->phi()) );
  } else
    return 0.;
}
	  

std::vector<double> PhotonJetSelector::getEMFPhotonJets() {
  std::vector<double> emfjets;
  for (std::vector<pat::Jet>::const_iterator jetsBegin = allPhotonJets_.begin(), jetsEnd = allPhotonJets_.end(), ijet = jetsBegin; ijet != jetsEnd; ++ijet) {
    double emf = 0;
    if ( ijet->isCaloJet() )
      emf = ijet->emEnergyFraction();
    else if ( ijet->isPFJet() )
      emf = ijet->photonEnergyFraction();
    emfjets.push_back(emf);
  }
  return emfjets;
}

	
std::vector<double> PhotonJetSelector::getEMFPhotonJetsInclEFrac() {
  std::vector<double> emfjets;
  for (std::vector<pat::Jet>::const_iterator jetsBegin = allPhotonJets_.begin(), jetsEnd = allPhotonJets_.end(), ijet = jetsBegin; ijet != jetsEnd; ++ijet) {
    double emf = 0;
    if (ijet->isCaloJet())
      emf = ijet->emEnergyFraction();
    else if (ijet->isPFJet())
      emf = ijet->photonEnergyFraction() + ijet->electronEnergyFraction();
    emfjets.push_back(emf);
  }
  return emfjets;
}

	
std::vector<double> PhotonJetSelector::getResponsePhotonJets() {
  std::vector<double> respjets;
  for (std::vector<pat::Jet>::const_iterator jetsBegin = allPhotonJets_.begin(), jetsEnd = allPhotonJets_.end(), ijet = jetsBegin; ijet != jetsEnd; ++ijet) {
    if (ijet->genJet() != 0) {
      respjets.push_back(ijet->pt() / ijet->genJet()->pt());
    }
  }
  return respjets;
}
	  

std::vector<double> PhotonJetSelector::getResponsePhotonJetsUncorr() {
  std::vector<double> respjets;
  for (std::vector<pat::Jet>::const_iterator jetsBegin = allPhotonJets_.begin(), jetsEnd = allPhotonJets_.end(), ijet = jetsBegin; ijet != jetsEnd; ++ijet) {
    if (ijet->genJet() != 0 && ijet->jecSetsAvailable()) {
      respjets.push_back(ijet->correctedJet("Uncorrected").pt() / ijet->genJet()->pt());
    }
  }
  return respjets;
}

	
std::vector<double> PhotonJetSelector::getResponsePhotonJetsL1() {
  std::vector<double> respjets;
  for (std::vector<pat::Jet>::const_iterator jetsBegin = allPhotonJets_.begin(), jetsEnd = allPhotonJets_.end(), ijet = jetsBegin; ijet != jetsEnd; ++ijet) {
    if (ijet->genJet() != 0 && ijet->jecSetsAvailable()) {
      respjets.push_back(ijet->correctedJet("L1FastJet").pt() / ijet->genJet()->pt());
    }
  }
  return respjets;
}

	
double PhotonJetSelector::getEtRelPhotonJets() {
  for (std::vector<pat::Jet>::const_iterator jetsBegin = allPhotonJets_.begin(), jetsEnd = allPhotonJets_.end(), ijet = jetsBegin; ijet != jetsEnd; ++ijet) {
    if (ijet->jecSetsAvailable() && photon_ != 0) {
      //      return (photon_->pt() / ijet->correctedJet("L1FastJet").pt());
      //      const pat::Jet jet = *ijet;
      return photon_->pt() / ijet->correctedJet( getPhotonJECLevel(*ijet) ).pt() ; //VS!!!
    }
  }
  return 0;
}
	  

std::vector<std::pair<double, double> > PhotonJetSelector::getDeltaRVsEtrel() {
  return deltaRVsEtrel_;
}


std::vector<std::pair<double, double> > PhotonJetSelector::getDeltaRVsEtrelGen() {
  return deltaRVsEtrelGen_;
}


std::vector<std::pair<double, double> > PhotonJetSelector::getDeltaRVsEtrelUncorr() {
  return deltaRVsEtrelUncorr_;
}


double PhotonJetSelector::getMinDeltaRPhotonJet() {
  double minDeltaR = -1.;
  
  for (std::vector<pat::Photon>::const_iterator photonBegin = selectedPhotons_.begin(), photonEnd = selectedPhotons_.end(), iphoton = photonBegin; iphoton != photonEnd; ++iphoton) {
    for (std::vector<pat::Jet>::const_iterator jetsBegin = selectedJets_.begin(), jetsEnd = selectedJets_.end(), ijet = jetsBegin; ijet != jetsEnd; ++ijet) {

      const pat::Jet jet = *ijet;
      const pat::Photon ph = *iphoton;
      double deltaR_ = reco::deltaR(ph, jet);

      if (minDeltaR < 0. || minDeltaR > deltaR_) {
	minDeltaR = deltaR_;
      }//assign minDeltaR

    }//for PAT Jets
  }//for PAT Photons

  return minDeltaR == -1. ? 0. : minDeltaR;
}
	

std::vector<double> PhotonJetSelector::getWeightAndErrorsPerBin(TH1F * h, double val) {

  double weight         = 1.;
  double weightSystUP   = 0.;
  double weightSystDown = 0.;

  if (h != 0) {
    int startBin = h->FindBin(val);
    
    if (h->GetBinContent(startBin) > 0) {
      weight         = h->GetBinContent(startBin);
      weightSystUP   = h->GetBinError(startBin);
      weightSystDown = h->GetBinError(startBin);
    }
  }

  std::vector<double> ret;
  ret.clear();
  ret.push_back(weight);
  ret.push_back(weightSystUP);
  ret.push_back(weightSystDown);

  return ret;
}


std::vector<double> PhotonJetSelector::getWeightAndErrorsPerBin2D(TH2F * hh, double valPt, double valHt) {

  double weight         = 1.;
  double weightSystUP   = 0.;
  double weightSystDown = 0.;

  if (hh != 0) {
    int startBin = hh->FindBin(valPt,valHt);
    
    if (hh->GetBinContent(startBin) > 0) {
      weight         = hh->GetBinContent(startBin);
      weightSystUP   = hh->GetBinError(startBin);
      weightSystDown = hh->GetBinError(startBin);
    }
  }

  std::vector<double> ret;
  ret.clear();
  ret.push_back(weight);
  ret.push_back(weightSystUP);
  ret.push_back(weightSystDown);

  return ret;
}


//systIncl: 0:normal 1:systDown 2:systUp
double PhotonJetSelector::getFakeRateWeightSYST( double p1, double p2, double p3, double p4, double p5, int systIncl, 
						 bool applyHistoCorrection, bool applyHTCorr, 
						 TH1F * corrHisto,TH1F * corrHisto2j, TH2F * corrHistoHT, 
						 double systFit, double systLowHighMet, double systSMCont ) {

  vector<double> weights;
  double weight = 1.;

  if ( applyHTCorr )
    applyHistoCorrection = false;

  if ( isPhotonValid() ) {

    double ht = htHLT();
    double photonpt = correctedphotonpt();
    double noJets   = selectedJets_.size();

    weight = getFakeRateWeight( p1, p2, p3, p4, p5, applyHistoCorrection, applyHTCorr, corrHisto, corrHisto2j, corrHistoHT );

    if ( systIncl == 2 || systIncl == 1 ) {
      double relSystFit        = systFit;
      double relSystLowHighMet = systLowHighMet;
      double relSystSMCont     = systSMCont;

      if ( applyHistoCorrection ) {
	
	if(noJets==2){
	  weights = getWeightAndErrorsPerBin( corrHisto2j, photonpt );
	}else{
	  weights = getWeightAndErrorsPerBin( corrHisto, photonpt );
	}

      } //if applyHistoCorrection


      if ( applyHTCorr ) {
	weights = getWeightAndErrorsPerBin2D( corrHistoHT, photonpt, ht );
      } //if applyHTCorr

      double relErr = weights.at(1) / weights.at(0);
      relSystFit = relErr;

      //apply a further 10% sys error for the case >=3 jets
      double systErr3jet       = weight * 0.1;
      double systErrFit        = weight * relSystFit;
      double systErrLowHighMet = weight * relSystLowHighMet;
      double systErrSMCont     = weight * relSystSMCont;

      double systError         = sqrt( pow(systErrFit, 2) 
				     + pow(systErrLowHighMet, 2) 
				     + pow(systErrSMCont, 2) );
      
      if ( noJets >= 3 && applyHistoCorrection ) {
	systError = sqrt( pow(systErr3jet, 2) ) 
	          + sqrt( pow(systErrFit, 2) 
		  + pow(systErrLowHighMet, 2) 
		  + pow(systErrSMCont, 2) );
      }
      

      if ( systIncl == 2 ) {
	weight = weight + systError;
      }

      if ( systIncl == 1 ) {
	weight = (weight - systError);
      }

    }//if systIncl
    
  }//if isPhotonValid

  return weight;
}


double PhotonJetSelector::getFakeRateWeight( double p1, double p2, double p3, double p4, double p5,
					     bool applyHistoCorrection, bool applyHTCorr, 
					     TH1F * corrHisto, TH1F * corrHisto2j, TH2F * corrHistoHT ) {

  vector<double> weightsPhoton;
  vector<double> weightsHT;
  double weight = 1.;

  if ( applyHTCorr )
    applyHistoCorrection = false;

  if ( isPhotonValid() ) {

    double ht = htHLT();
    double photonPt = correctedphotonpt();
    double nojets   = selectedJets_.size();

    if (applyHistoCorrection) {


      if ( nojets==2 ) {
	weightsPhoton = getWeightAndErrorsPerBin( corrHisto2j, photonPt );
      } else {
	weightsPhoton = getWeightAndErrorsPerBin( corrHisto, photonPt );
      }// # of jets

      weight = weight * weightsPhoton.at(0);
    } //if applyHistoCorrection

    if (applyHTCorr) {
      weightsHT = getWeightAndErrorsPerBin2D( corrHistoHT, photonPt, ht );
      weight    = weight * weightsHT.at(0);
    } //if applyHTCorr

  } //if isPhotonValid

  return weight;
}

	  
int PhotonJetSelector::getNoPV() {
  return noPV_;
}//# of good Vertices


int PhotonJetSelector::getNoPVPU() {
  return noPVPU_;
}//# of good Vertices PU


double PhotonJetSelector::getMj12() {
  if (isJetValid() && isJet2Valid()) {
    math::XYZTLorentzVector sum = jet_->p4() + jet2_->p4();
    return sum.M();
  } else
    return 0;
}//mass of j1+j2

	
double PhotonJetSelector::getMj13() {
  if (isJetValid() && isJet3Valid()) {
    math::XYZTLorentzVector sum = jet_->p4() + jet3_->p4();
    return sum.M();
  } else
    return 0;
}//mass of j1+j3
	

double PhotonJetSelector::getMj23() {
  if (isJet2Valid() && isJet3Valid()) {
    math::XYZTLorentzVector sum = jet2_->p4() + jet3_->p4();
    return sum.M();
  } else
    return 0;
}//mass of j2+j3
	  
	  double PhotonJetSelector::getDeltaPhiMetPhoton1() {
	    if (photon_ != 0 && isMetValid()) {
	      return abs(PhysicsUtil::GetDeltaPhi(met_->phi(), photon_->phi()));
	    } else
	      return 0.;
	  }
	
	  double PhotonJetSelector::getDeltaPhiMetT1Photon1() {
	    if (photon_ != 0 && isMetValid()) {
	      return abs(PhysicsUtil::GetDeltaPhi(metT1_->phi(), photon_->phi()));
	    } else
	      return 0.;
	  }
	
	  double PhotonJetSelector::getDeltaRMetPhoton1() {
	    if (photon_ != 0 && isMetValid()) {
	      return abs(reco::deltaR(*met_, *photon_));
	    } else
	      return 0.;
	  }
	
	  double PhotonJetSelector::getDeltaPhiMetJet1() {
	    if (jet_ != 0 && isMetValid()) {
	      return abs(PhysicsUtil::GetDeltaPhi(met_->phi(), jet_->phi()));
	    } else
	      return 0.;
	  }
	
	  bool PhotonJetSelector::isPunchthroughMuonBJet(int& rpcHits, double& JetPT) {
	    bool ret = false;
	    for (std::vector<pat::Jet>::const_iterator jetsBegin = selectedJetsHLT_.begin(), jetsEnd = selectedJetsHLT_.end(), ijet = jetsBegin; ijet != jetsEnd; ++ijet) {
	      if ((ijet->jetID().numberOfHitsRPC > 10) && (ijet->bDiscriminator("softMuonBJetTags") >= 0.15)) {
		std::cout << "B-TAG  " << ijet->bDiscriminator("softMuonBJetTags") << std::endl;
		std::cout << "Number of RPC Hits:    " << ijet->jetID().numberOfHitsRPC << std::endl;
		ret = true;
		rpcHits = (ijet->jetID().numberOfHitsRPC);
		JetPT = (ijet->pt());
	      }
	    }
	    return ret;
	  }

	  bool PhotonJetSelector::isPunchthroughTrackCounting(int& k, double& JetPT) {
	    bool ret = false;
	    for (std::vector<pat::Jet>::const_iterator jetsBegin = selectedJetsHLT_.begin(), jetsEnd = selectedJetsHLT_.end(), ijet = jetsBegin; ijet != jetsEnd; ++ijet) {
	      if ((ijet->jetID().numberOfHitsRPC > 10) && (ijet->bDiscriminator("trackCountingHighEffBJetTags") > 1.7)) {
		std::cout << "B-TAG  " << ijet->bDiscriminator("trackCountingHighEffBJetTags") << std::endl;
		std::cout << "Number of RPC Hits:    " << ijet->jetID().numberOfHitsRPC << std::endl;
		ret = true;
		k = (ijet->jetID().numberOfHitsRPC);
		JetPT = (ijet->pt());
	      }
	    }
	    return ret;
	  }

	  double PhotonJetSelector::getDeltaPhiMetJet2() {
	    if (jet2_ != 0 && isMetValid()) {
	      return abs(PhysicsUtil::GetDeltaPhi(met_->phi(), jet2_->phi()));
	    } else
	      return 0.;
	  }
	
	  double PhotonJetSelector::getDeltaPhiMetJet3() {
	    if (jet3_ != 0 && isMetValid()) {
	      return abs(PhysicsUtil::GetDeltaPhi(met_->phi(), jet3_->phi()));
	    } else
	      return 0.;
	  }

// here is where the selection occurs
bool PhotonJetSelector::operator ()(const edm::EventBase & event, pat::strbitset & ret) {

	    if (debug_) {
	      std::cout << "enter operator()" << std::endl;
	    }
	    resetSelection();
	    if (debug_) {
	      std::cout << "ret any()" << retInternal_.any() << std::endl;
	    }
	    if (debug_) {
	      std::cout << "reset selection done" << std::endl;
	    }

	    //Handle to generator information of scan
	    edm::Handle<LHEEventProduct> lhe;
	    edm::InputTag lheeSource_("source");
	    event.getByLabel(lheeSource_, lhe);
	    setScanGeneratorInfo(lhe);

	    // Handle to the photon collection
	    edm::Handle<std::vector<pat::Photon> > photons;
	    edm::Handle<std::vector<pat::Photon> > photonsHLT;

	    // Handle to the MET collection
	    edm::Handle < std::vector<pat::MET> > met;
	    edm::Handle < std::vector<pat::MET> > metRaw;
	    edm::Handle < std::vector<pat::MET> > metT1;
	    edm::Handle < std::vector<pat::MET> > metT2;
	    edm::Handle < std::vector<pat::MET> > met2;

	    //Handle to the jet collection
	    edm::Handle<std::vector<pat::Jet> > jets;
	    edm::Handle<std::vector<pat::Jet> > jetsHLT;
      
	    //Handles to leptons
	    edm::Handle<std::vector<pat::Muon> > muons;
	    edm::Handle<std::vector<pat::Electron> > electrons;

	    //Handle to MET Filters
	    edm::Handle < bool> hcalLaserFilter;
	    edm::Handle < bool> ecalDeadCellTPFilter;
	    edm::Handle < bool> ecalDeadCellBEFilter;
	    edm::Handle < bool> hbheNoiseFilter;
	    edm::Handle < bool> cscTightHaloFilter;
	    edm::Handle < bool> trackingFailureFilter;
	    edm::Handle < bool> eeBadScFilter;


	    // get the objects from the event
	    bool gotPhotons    = event.getByLabel(photonSrc_, photons);
	    bool gotPhotonsHLT = event.getByLabel(photonSrcHLT_, photonsHLT);

	    bool gotMET    = event.getByLabel(metSrc_, met);
	    bool gotMETRaw = event.getByLabel(metSrcRaw_, metRaw);
	    bool gotMETT1  = event.getByLabel(metSrcT1_, metT1);
	    bool gotMETT2  = event.getByLabel(metSrcT2_, metT2);
	    bool gotMET2   = event.getByLabel(metSrc2_, met2);

	    bool gotHcalLaser       = event.getByLabel(hcalLaserFilterSrc_,hcalLaserFilter);
	    bool gotecalDCTP        = event.getByLabel(ecalDeadCellTPFilterSrc_,ecalDeadCellTPFilter);
	    bool gotecalDCBE        = event.getByLabel(ecalDeadCellBEFilterSrc_,ecalDeadCellBEFilter);
	    bool gotHBHEnoise       = event.getByLabel(hbheNoiseFilterSrc_,hbheNoiseFilter);
	    bool gotCSCTightHalo    = event.getByLabel(cscTightHaloFilterSrc_,cscTightHaloFilter);
	    bool gotTrackingFailure = event.getByLabel(trackingFailureFilterSrc_,trackingFailureFilter);
	    bool goteeBadScFilter   = event.getByLabel(eeBadScFilterSrc_,eeBadScFilter);

	    if (gotMET) {
	      met_ = &met->at(0);
	    }
	    if (gotMET2) {
	      met2_ = &met2->at(0);
	    }
	    if (gotMETRaw) {
	      metRaw_ = &metRaw->at(0);
	    }
	    if (gotMETT1) {
	      metT1_ = &metT1->at(0);
	    }
	    if (gotMETT2) {
	      metT2_ = &metT2->at(0);
	    }

	    if (gotHcalLaser)
	      hcalLaserFilter_ = *hcalLaserFilter;
	    if (gotCSCTightHalo)
	      cscTightHaloFilter_ = *cscTightHaloFilter;
	    if (gotecalDCBE)
	      ecalDeadCellBEFilter_ = *ecalDeadCellBEFilter;
	    if (gotecalDCTP)
	      ecalDeadCellTPFilter_ = *ecalDeadCellTPFilter;
	    if (gotTrackingFailure)
	      trackingFailureFilter_ = *trackingFailureFilter;
	    if (gotHBHEnoise)
	      hbheNoiseFilter_ = *hbheNoiseFilter;
	    if (goteeBadScFilter)
	      eeBadScFilter_ = *eeBadScFilter;

	    bool gotJets      = event.getByLabel(jetSrc_, jets);
	    bool gotJetsHLT   = event.getByLabel(jetSrcHLT_, jetsHLT);
	    bool gotElectrons = event.getByLabel(electronSrc_, electrons);
	    bool gotMuons     = event.getByLabel(muonSrc_, muons);

	    edm::InputTag noGoodVerticesInputTag("oneGoodVertexNoProducer", "noGoodVertices", "");
	    edm::Handle<int> noGoodVertices;
	    event.getByLabel(noGoodVerticesInputTag, noGoodVertices);

	    if (noGoodVertices.isValid()) {		
	      noPV_ = *noGoodVertices;
	    }

	    //no of primary vertices as calculated with the pileup-Tools!
	    edm::InputTag PileupSrc_("addPileupInfo");
	    edm::Handle< std::vector<PileupSummaryInfo> > PupInfo;
	    event.getByLabel(PileupSrc_, PupInfo);

	    if (PupInfo.isValid()) {
	      int npv = -1;
	      std::vector<PileupSummaryInfo>::const_iterator PVI;

	      for (PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI) {
		int BX = PVI->getBunchCrossing();
		if (BX == 0) {
		  npv = PVI->getPU_NumInteractions();
		  continue;
		}
	      }

	      noPVPU_ = npv;	      
	    }//if PupInfo


	    ////////////////APPLY CUTS/////////////////////////////////////////////
	    if (debug_) {
	      std::cout << "apply cuts" << std::endl;
	    }

	    bool allCutsPassed = true;

	    //photon,jet eta & photon isolation
	    //preselect jets/photons and make crosscleaning

	    edm::InputTag genPartLabel("genParticles");
	    edm::Handle<reco::GenParticleCollection> genPartHandle;
	    event.getByLabel(genPartLabel, genPartHandle);

	    if (useGenForSelection_) {
	      selectedPhotons_ = getGenPhotons(getCleanPhotons(photons), genPartHandle, false);
	    } else if (requireGenForSelection_) {

	      //Handle to genparticle collection
	      bool genParticlesValid = genPartHandle.isValid();
	      if (genParticlesValid) {
		if (cut(photonGenPdgId_, double()) == 11) { // electron
		  selectedPhotons_ = getGenElectrons(getCleanPhotons(photons), genPartHandle, preferGenPhotons_);
		} else if (cut(photonGenPdgId_, double()) == 6) { // top quark
		  selectedPhotons_ = getHadrons(getCleanPhotons(photons), genPartHandle, false);
		} else if (cut(photonGenPdgId_, double()) == 5) { // bottom quark
		  selectedPhotons_ = getHadrons(getCleanPhotons(photons), genPartHandle, true);
		} else
		  selectedPhotons_ = getGenPhotons(getCleanPhotons(photons), genPartHandle, !preferGenPhotons_);
	      }
	    } else {
	      selectedPhotons_  = getCleanPhotons(photons); //PHOTONS (eta selected)
	    }
	    selectedPhotonsHLT_ = getCleanPhotons(photonsHLT); //HLT PHOTONS (eta selected)

	    if (useGenForSelection_) {
	      selectedJets_ = getGenJets(getCleanJets(jets));
	    } else {
	      selectedJets_ = getCleanJets(jets); //JETS
	    }

	    selectedJetsHLT_    = getHLTJets(jetsHLT);    //HLT JETS - w/o photons
	    selectedJetsHLTAll_ = getHLTJetsAll(jetsHLT); //HLT JETS


	    if (debug_) {
	      std::cout << "photon eta" << allCutsPassed << std::endl;
	    }

	    if (allCutsPassed) { //still true
	      if (debug_) {
		std::cout << "photon eta 1::" << std::endl;
		retInternal_.bits();
		std::cout << "photon eta 1::size" << retInternal_.bits().size() << std::endl;
		retInternal_.print(std::cout);
	      }

	      bool pass = !considerCut(photonEta_); // = ignoreCut(...) -> true if photonEta_ cut not applied

	      if (debug_) {
		std::cout << "photon eta 2" << allCutsPassed << std::endl;
	      }

	      if (!pass && selectedPhotons_.size() > 0) { //if pass is false -> considerCut is true
		if (debug_) {
		  std::cout << "pass photon eta 1?" << allCutsPassed << std::endl;
		}
		passCut(ret, photonEta_); 
		if (debug_) {
		  std::cout << "passed photon eta 1" << allCutsPassed << std::endl;
		}
		pass = true; // TRUE !!! lol
	      }

	      allCutsPassed = allCutsPassed && pass; //pass value
	    }

	    if (debug_) {
	      std::cout << "jeteta" << allCutsPassed << std::endl;
	    }

	    if (allCutsPassed) {
	      bool pass = !considerCut(jetEta_); 
	      if (!pass && selectedJets_.size() > 0) {
		passCut(ret, jetEta_);
		pass = true;
	      }

	      allCutsPassed = allCutsPassed && pass;
	    }
	    

	    //MET FILTERS
	    if (allCutsPassed) {
	      bool pass = true; //by Matle

	      if (gotHcalLaser && gotCSCTightHalo && gotecalDCTP && gotTrackingFailure && gotHBHEnoise && goteeBadScFilter) {
		pass = (eeBadScFilter_ && hcalLaserFilter_ && cscTightHaloFilter_  && ecalDeadCellTPFilter_ && trackingFailureFilter_ && hbheNoiseFilter_);
	      }
	      allCutsPassed = allCutsPassed && pass; //true if pass MET Filters
	    }//if allCutPassed

	    bool applyDeltaRCut = considerCut(deltaRPhotonJet_);

	    //CROSSCLEAN
	    selectedJets_ = getLeptonCleanedJets(selectedJets_);
	    crosscleanSelectedPhotonsAndJets(applyDeltaRCut);
	    selectedJets_ = getCleanJetsJetID(selectedJets_);
		
	    if (allCutsPassed) {
	      bool passdeltaRPhotonJet_ = !considerCut(deltaRPhotonJet_);

	      if (getMinDeltaRPhotonJet() > cut(deltaRPhotonJet_, double())) {
		passCut(ret, deltaRPhotonJet_);
		passdeltaRPhotonJet_ = true;
	      }
	      allCutsPassed = allCutsPassed && passdeltaRPhotonJet_;
	    }// deltaRPhotonJet > 0.5 ?!?


	    //noPhotons
	    bool passPhoton1     = !considerCut(photon1Index_);     // = 1 photon
	    bool passPhoton1plus = !considerCut(photon1plusIndex_); //>= 1 photon
	    bool passPhoton2     = !considerCut(photon2Index_);     // = 2 photons

	    if (allCutsPassed && gotPhotons) {
	      if (debug_) {
		edm::LogError("SelectionAnalyzer");
		std::cout << "===================photons: " << selectedPhotons_.size() << std::endl;
		for (std::vector<pat::Photon>::const_iterator photonBegin = selectedPhotons_.begin(), photonEnd = selectedPhotons_.end(), iphoton = photonBegin; iphoton != photonEnd; ++iphoton) {
		  //		  cout << "selected photon" << "pt: " << iphoton->pt() << " ET phot:" << iphoton->et() << " eta:" << iphoton->eta() << " phi:" << iphoton->phi() << endl;
		  cout << "selected photon" << "pt: " << iphoton->pt() << " ET phot:" << iphoton->pt() << " eta:" << iphoton->eta() << " phi:" << iphoton->phi() << endl;
		}
	      }

	      int ph = 0;
	      for (std::vector<pat::Photon>::const_iterator photonBegin = selectedPhotons_.begin(), photonEnd = selectedPhotons_.end(), iphoton = photonBegin; iphoton != photonEnd; ++iphoton, ++ph) {
		if (ph == 0) {
		  photon_ = &*iphoton;
		} else if (ph == 1) {
		  photon2_ = &*iphoton;
		} else {
		  break;
		}
	      }//very important -> takes the photon_ !!!

	      if (static_cast<int> (selectedPhotons_.size()) == 1) {
		passCut(ret, photon1Index_);
		passPhoton1 = true;
	      } // = 1 photon

	      if (static_cast<int> (selectedPhotons_.size()) >= 2) {
		passCut(ret, photon2Index_);
		passPhoton2 = true;
	      } //>= 2 photon

	      if (static_cast<int> (selectedPhotons_.size()) >= 1) {
		passCut(ret, photon1plusIndex_);
		passPhoton1plus = true;
	      } //>= 1 photon

	    }//if gotPhotons

	    allCutsPassed = allCutsPassed && passPhoton1 && passPhoton2 && passPhoton1plus;

	    if (debug_ && allCutsPassed) {
	      std::cout << "photons passed" << std::endl;
	    }

	    //# of jets & bJets
	    bool passJet0 = !considerCut(jet0Index_);
	    bool passJet1 = !considerCut(jet1Index_);
	    bool passJet2 = !considerCut(jet2Index_);
	    bool passJet2Incl = !considerCut(jet2InclIndex_);
	    bool passJet3 = !considerCut(jet3Index_);
	    bool passJet4 = !considerCut(jet4Index_);
	    bool passJet5 = !considerCut(jet5Index_);

	    if (allCutsPassed && gotJets) {

	      if (debug_) {
		std::cout << "!!!!!!!!!!!!!!jets: " << selectedJets_.size() << std::endl;
		for (std::vector<pat::Jet>::const_iterator jetsBegin = selectedJets_.begin(), jetsEnd = selectedJets_.end(), ijet = jetsBegin; ijet != jetsEnd; ++ijet) {
		  double emf = 0;
		  if (ijet->isCaloJet())
		    emf = ijet->emEnergyFraction();
		  else if (ijet->isPFJet())
		    emf = ijet->photonEnergyFraction();
		  cout << "selected jet" << "pt: " << ijet->pt() << " emf jet:" << emf << " eta:" << ijet->eta() << " phi:" << ijet->phi() << endl;
		}
	      }//if debug

	      int j = 0;
	      for (std::vector<pat::Jet>::const_iterator jetsBegin = selectedJets_.begin(), jetsEnd = selectedJets_.end(), ijet = jetsBegin; ijet != jetsEnd; ++ijet, ++j) {
		if (j == 0) {
		  jet_ = &*ijet;
		} else if (j == 1) {
		  jet2_ = &*ijet;
		} else if (j == 2) {
		  jet3_ = &*ijet;
		} else if (j == 3) {
		  jet4_ = &*ijet;
		} else {
		  break;
		}
	      }//very important -> takes the jet_ objects !!!

	      if ( selectedJets_.size() == 0) {
		passCut(ret, jet0Index_);
		passJet0 = true;
	      } // end if 0 jets
	      if ( selectedJets_.size() == 1) {
		passCut(ret, jet1Index_);
		passJet1 = true;
	      } // end if 1 jets
	      if ( selectedJets_.size() == 2) {
		passCut(ret, jet2Index_);
		passJet2 = true;
	      } // end if 2 jets
	      if ( selectedJets_.size() >= 2) {
		passCut(ret, jet2InclIndex_);
		passJet2Incl = true;
	      } // end if >=2 jets
	      if ( selectedJets_.size() >= 3) {
		passCut(ret, jet3Index_);
		passJet3 = true;
	      } // end if 3 jets
	      if ( selectedJets_.size() >= 4) {
		passCut(ret, jet4Index_);
		passJet4 = true;
	      } // end if 4 jets
	      if ( selectedJets_.size() > 4) {
		passCut(ret, jet5Index_);
		passJet5 = true;
	      } // end if 5 jets

	      allCutsPassed = allCutsPassed && passJet0 && passJet1 && passJet2 && passJet2Incl && passJet3 && passJet4 && passJet5; //@@changed: C.A.

	      if (allCutsPassed) {

		if (debug_) {
		  std::cout << "b jets" << std::endl;
		}

		//get b jet collection from jets
		if (useGenForSelection_)
		  selectedBJets_ = getGenBJets(getCleanBJets(selectedJets_));
		else
		  selectedBJets_ = getCleanBJets(selectedJets_);

		/* VS!!!
		  if (useGenForSelection_)
		  selectedBJets_ = getGenBJets(getCleanBJets(jets));
		  else
		  selectedBJets_ = getCleanBJets(jets);
		*/

		int bj = 0;
		for (std::vector<pat::Jet>::const_iterator jetsBegin = selectedBJets_.begin(), jetsEnd = selectedBJets_.end(), ijet = jetsBegin; ijet != jetsEnd; ++ijet, ++bj) {
		  if (bj == 0) {
		    bjet_ = &*ijet;
		  } else if (bj == 1) {
		    bjet2_ = &*ijet;
		  } else {
		    break;
		  }
		}//takes the first 2 bjets

		bool passBJet0 = !considerCut(bjet0Index_);
		bool passBJet1 = !considerCut(bjet1Index_);
		bool passBJet2 = !considerCut(bjet2Index_);

		if (static_cast<int> (selectedBJets_.size()) >= 2) {
		  passCut(ret, bjet2Index_);
		  passBJet2 = true;
		}
		if (static_cast<int> (selectedBJets_.size()) >= 1) {
		  passCut(ret, bjet1Index_);
		  passBJet1 = true;
		}
		if (static_cast<int> (selectedBJets_.size()) == 0) {
		  passCut(ret, bjet0Index_);
		  passBJet0 = true;
		}

		allCutsPassed = allCutsPassed && passBJet0 && passBJet1 && passBJet2;
	      }

	      if (debug_) {
		std::cout << "end of jet selection sequence" << std::endl;
	      }

	    }//if gotJets

	    if (debug_ && allCutsPassed) {
	      std::cout << "pass Jet&Photon" << allCutsPassed << std::endl;
	    }


	    //HT & MHT

	    if (debug_) {
	      std::cout << "HT" << allCutsPassed << std::endl;
	    }

	    if (allCutsPassed) {
	      bool passHt = !considerCut(HT_);
	      if (ht() > cut(HT_, double())) {
		passCut(ret, HT_);
		passHt = true;
	      }
	      allCutsPassed = allCutsPassed && passHt;
	    }


	    if (debug_) {
	      std::cout << "HTHLT" << allCutsPassed << std::endl;
	    }

	    // if (allCutsPassed && gotJetsHLT && gotPhotonsHLT) {
	    if (allCutsPassed) {
	      bool passHtHLT = !considerCut(HTHLT_);
	      if (htHLT() > cut(HTHLT_, double())) {
		passCut(ret, HTHLT_);
		passHtHLT = true;
	      }
	      allCutsPassed = allCutsPassed && passHtHLT;
	    }


	    if (debug_) {
	      std::cout << "MHT" << allCutsPassed << std::endl;
	    }

	    if (allCutsPassed) {
	      bool passHt = !considerCut(MHT_);
	      if (mht().pt() > cut(MHT_, double())) {
		passCut(ret, MHT_);
		passHt = true;
	      }
	      allCutsPassed = allCutsPassed && passHt;
	    }


	    //leptonVeto
	    if (debug_) {
	      std::cout << "leptonVeto" << allCutsPassed << std::endl;
	    }

	    if (allCutsPassed) {

	      bool pass = !considerCut(leptonVeto_);

	      if (gotElectrons && gotMuons && !pass) {
		if (debug_) {
		  std::cout << "electrons=" << electrons->size() << std::endl;
		  std::cout << "muons=" << muons->size() << std::endl;
		}

		if (!pass && photon_ != 0) {

		  //muon in the photon cone
		  bool photonOverlapsMuon = false;
		  for (std::vector<pat::Muon>::const_iterator muonBegin = muons->begin(), 
			 muonEnd = muons->end(), imuon = muonBegin; imuon != muonEnd; ++imuon) {
		    double deltaR_ = reco::deltaR(*imuon, *photon_);
		    if (deltaR_ < 0.1) {
		      photonOverlapsMuon = true;
		      break;
		    }
		  }

		  //electron in the photon cone
		  bool photonOverlapsElectron = false;
		  for (std::vector<pat::Electron>::const_iterator eleBegin = electrons->begin(), 
			 eleEnd = electrons->end(), iele = eleBegin; 
		       iele != eleEnd; ++iele) {
		    double deltaR_ = reco::deltaR(*iele, *photon_);
		    if (deltaR_ < 0.1) {
		      photonOverlapsElectron = true;
		      break;
		    }
		  }

		  if (photonOverlapsMuon || photonOverlapsElectron || (electrons->size() == 0 && muons->size() == 0)) {
		    passCut(ret, leptonVeto_);
		    pass = true;
		  }

		}
	      }
	      allCutsPassed = allCutsPassed && pass;
	    }//end lepton veto


	    //photon pt
	    if (debug_) {
	      std::cout << "photonpt" << allCutsPassed << std::endl;
	    }

	    if (allCutsPassed) {
	      bool pass = !considerCut(photonPt_);
	      if (photon_ != 0) {
		if (photon_->pt() > cut(photonPt_, double())) {
		  passCut(ret, photonPt_);
		  pass = true;
		}
	      }
	      allCutsPassed = allCutsPassed && pass;
	    }


	    //jet pts
	    if (debug_) {
	      std::cout << "jetpt" << allCutsPassed << std::endl;
	    }

	    if (allCutsPassed) {
	      bool pass = !considerCut(jetPt_);
	      if (jet_ != 0) {
		if (jet_->pt() > cut(jetPt_, double())) {
		  passCut(ret, jetPt_);
		  pass = true;
		}
	      }
	      allCutsPassed = allCutsPassed && pass;
	    }//jet_ pt

	    if (allCutsPassed) {
	      bool pass = !considerCut(jet2Pt_);
	      if (jet2_ != 0) {
		if (jet2_->pt() > cut(jet2Pt_, double())) {
		  passCut(ret, jet2Pt_);
		  pass = true;
		}
	      }
	      allCutsPassed = allCutsPassed && pass;
	    }//jet2_ pt


	    //deltaPhi Cuts
	    if (allCutsPassed) {
	      bool passdeltaPhiJJ = !considerCut(deltaPhiJ1J2_);
	      if (getDeltaPhiJ1J2() < cut(deltaPhiJ1J2_, double())) {
		passCut(ret, deltaPhiJ1J2_);
		passdeltaPhiJJ = true;
	      }
	      allCutsPassed = allCutsPassed && passdeltaPhiJJ;
	    }//deltaPhi j1 j2

	    if (allCutsPassed) {
	      bool passdeltaPhiJPhoton = !considerCut(deltaPhiJ1Photon_);
	      if (getDeltaPhiJ1Photon() < cut(deltaPhiJ1Photon_, double())) {
		passCut(ret, deltaPhiJ1Photon_);
		passdeltaPhiJPhoton = true;
	      }
	      allCutsPassed = allCutsPassed && passdeltaPhiJPhoton;
	    }//deltaPhi j1 photon

	    if (allCutsPassed) {
	      bool passdeltaPhiMetJet1 = !considerCut(deltaPhiMetJet1_);
	      if (getDeltaPhiMetJet1() > cut(deltaPhiMetJet1_, double())) {
		passCut(ret, deltaPhiMetJet1_);
		passdeltaPhiMetJet1 = true;
	      }
	      allCutsPassed = allCutsPassed && passdeltaPhiMetJet1;
	    }//deltaPhi met j1

	    if (allCutsPassed) {
	      bool passdeltaPhiMetJet2 = !considerCut(deltaPhiMetJet2_);
	      if (getDeltaPhiMetJet2() > cut(deltaPhiMetJet2_, double())) {
		passCut(ret, deltaPhiMetJet2_);
		passdeltaPhiMetJet2 = true;
	      }
	      allCutsPassed = allCutsPassed && passdeltaPhiMetJet2;
	    }//deltaPhi met j2

	    if (allCutsPassed) {
	      bool passdeltaPhiMetJet3 = !considerCut(deltaPhiMetJet3_);
	      if (getDeltaPhiMetJet3() > cut(deltaPhiMetJet3_, double())) {
		passCut(ret, deltaPhiMetJet3_);
		passdeltaPhiMetJet3 = true;
	      }
	      allCutsPassed = allCutsPassed && passdeltaPhiMetJet3;
	    }//deltaPhi met j3


	    //M jets
	    if (allCutsPassed) {
	      bool passMj12 = !considerCut(Mj12_);
	      if (getMj12() < cut(Mj12_, double())) {
		passCut(ret, Mj12_);
		passMj12 = true;
	      }
	      allCutsPassed = allCutsPassed && passMj12;
	    }//Mj12

	    if (allCutsPassed) {
	      bool passMj13 = !considerCut(Mj13_);
	      if (getMj13() < cut(Mj13_, double())) {
		passCut(ret, Mj13_);
		passMj13 = true;
	      }
	      allCutsPassed = allCutsPassed && passMj13;
	    }//Mj13

	    if (allCutsPassed) {
	      bool passMj23 = !considerCut(Mj23_);
	      if (getMj23() < cut(Mj23_, double())) {
		passCut(ret, Mj23_);
		passMj23 = true;
	      }
	      allCutsPassed = allCutsPassed && passMj23;
	    }//Mj23

	    if (debug_) {
	      std::cout << "Mjets selection sequence passed" << allCutsPassed << std::endl;
	    }


	    //met&co
	    bool passMET = !considerCut(metIndex_);
	    if (debug_) {
	      std::cout << "ignoreMet?" << passMET << std::endl;
	    }

	    if (gotMET) {

	      if (debug_) {
		std::cout << "MET"    << met_->pt() << std::endl;
		std::cout << "METRAW" << metRaw_->pt() << std::endl;
		std::cout << "METT1"  << metT1_->pt() << std::endl;
		std::cout << "METT2"  << metT2_->pt() << std::endl;
		std::cout << "MET2"   << met2_->pt() << std::endl;
	      }

	      if (useGenForSelection_) {
		if (met_->pt() > cut(metIndex_, double())) {
		  passCut(ret, "MET");
		  passMET = true;
		}
	      } else { //useGen
		if (met_->pt() > cut(metIndex_, double())) {
		  passCut(ret, "MET");
		  passMET = true;
		}		
	      }//MET cut

	    } else {
	      std::cout << "MET not found! " << metSrc_.label() << std::endl;
	    }//if gotMET

	    if (debug_ && passMET) {
	      std::cout << "passMET" << std::endl;
	    }

	    allCutsPassed = allCutsPassed && passMET;

	    if (allCutsPassed) {
	      bool passMt = !considerCut(MT_);
	      if (mt().pt() > cut(MT_, double())) {
		passCut(ret, MT_);
		passMt = true;
	      }
	      allCutsPassed = allCutsPassed && passMt;
	    }//MT cut

	    if (debug_) {
	      std::cout << "HTJ" << allCutsPassed << std::endl;
	    }

	    if (allCutsPassed) {
	      bool passHt = !considerCut(HTJ_);
	      if (htj() > cut(HTJ_, double())) {
		passCut(ret, HTJ_);
		passHt = true;
	      }
	      allCutsPassed = allCutsPassed && passHt;
	    }//HTJ cut

	    if (debug_) {
	      std::cout << "MHTJ" << mhtj().pt() << std::endl;
	    }

	    if (allCutsPassed) {
	      bool passHt = !considerCut(MHTJ_);
	      if (mhtj().pt() > cut(MHTJ_, double())) {
		passCut(ret, MHTJ_);
		passHt = true;
	      }
	      allCutsPassed = allCutsPassed && passHt;
	    }//MHTJ cut


	    //cut on generator level electron
	    if (allCutsPassed && cut(genEleVeto_, double()) != 0 && genPartHandle.isValid()) {
	      bool pass = !considerCut(genEleVeto_);

	      if (!pass) {
		bool hasGenElectron = false;

		for (reco::GenParticleCollection::const_iterator genPartIter = genPartHandle->begin(); 
		     genPartHandle->end() != genPartIter; ++genPartIter) {
		  const reco::GenParticle * genPart = &(*genPartIter);
		  if (genPart != 0) {
		    if (abs(genPartIter->pdgId()) == 11) {
		      if (genPartIter->status() == 3) {
			hasGenElectron = true;
			break;
		      }
		    }
		  }
		}//for loop

		if (hasGenElectron && cut(genEleVeto_, double()) == 1) {
		  passCut(ret, genEleVeto_);
		  pass = true;
		} else if (!hasGenElectron && cut(genEleVeto_, double()) == 2) {
		  passCut(ret, genEleVeto_);
		  pass = true;
		}

	      }// !pass

	      allCutsPassed = allCutsPassed && pass;
	    }//genEleVeto


	    if (allCutsPassed && cut(genPhotonVeto_, double()) != 0 && genPartHandle.isValid()) {
	      bool pass = !considerCut(genPhotonVeto_);

	      if (!pass) {
		bool hasGenPhoton = false;

		for (reco::GenParticleCollection::const_iterator genPartIter = genPartHandle->begin(); 
		     genPartHandle->end() != genPartIter; ++genPartIter) {
		  const reco::GenParticle * genPart = &(*genPartIter);
		  if (genPart != 0) {
		    if (abs(genPartIter->pdgId()) == 22) {
		      hasGenPhoton = true;
		      break;
		    }
		  }
		}//for loop

		if (hasGenPhoton && cut(genPhotonVeto_, double()) == 1) {
		  passCut(ret, genPhotonVeto_);
		  pass = true;
		} else if (!hasGenPhoton && cut(genPhotonVeto_, double()) == 2) {
		  passCut(ret, genPhotonVeto_);
		  pass = true;
		}
	      }// !pass

	      allCutsPassed = allCutsPassed && pass;
	    }//genPhotonVeto


	    //==============END of CUTTING===========================
	    if (debug_) {
	      std::cout << "end of selection" << std::endl;
	    }
	    /////////////////////////////////////////////////////////////

	    return (bool) (ret);
}


//// protected:  ////////////////////////////////////////////////////////

//
void PhotonJetSelector::crosscleanSelectedPhotonsAndJets(bool applyPhotonIso) {

  std::vector<pat::Jet> crosscleanedJets;
  std::vector<pat::Jet> crosscleanedPhotonJets;
  std::vector<pat::Jet> allPhotonJets;
  std::vector<pat::Photon> crosscleanedPhotons;

  for (std::vector<pat::Jet>::const_iterator jetsBegin = selectedJets_.begin(), jetsEnd = selectedJets_.end(), ijet = jetsBegin; ijet != jetsEnd; ++ijet) { //all jets

    bool jetOk       = true;
    bool jetPhotonOk = false;

    if (selectedPhotons_.size() > 0) {
      for (std::vector<pat::Photon>::const_iterator photonBegin = selectedPhotons_.begin(), photonEnd = selectedPhotons_.begin() + 1, iphoton = photonBegin; iphoton != photonEnd; ++iphoton) { //1st photon

	double deltaR_ = reco::deltaR(*ijet, *iphoton);

	//		  double ETRel = ijet->et() / iphoton->et();
	double ETRel = ijet->pt() / iphoton->pt(); //VS!!!

	jetOk       = !isJetOverlappingPhoton(*ijet, *iphoton);
	jetPhotonOk = isJetBetterPhoton(*ijet, *iphoton);


	//define deltaRVsEtrel values
	pair<double, double> currDeltaREtrel = pair<double, double> (deltaR_, ETRel);
	deltaRVsEtrel_.push_back(currDeltaREtrel);

	if (ijet->jecSetsAvailable()) {
	  double deltaRUncorr = reco::deltaR(ijet->correctedJet("Uncorrected"), *iphoton);
	  double ETRelUncorr = ijet->correctedJet("Uncorrected").pt() / iphoton->pt(); //VS!!!
	  pair<double, double> currDeltaREtrelUncorr = pair<double, double> (deltaRUncorr, ETRelUncorr);
	  deltaRVsEtrelUncorr_.push_back(currDeltaREtrelUncorr);
	}

	if (iphoton->genPhoton() != 0 && ijet->genJet() != 0) {
	  double deltaRGen = reco::deltaR(*(ijet->genJet()), *(iphoton->genPhoton()));
	  double ETRelGen = ijet->genJet()->pt() / iphoton->genPhoton()->pt(); //VS!!!
	  pair<double, double> currDeltaREtrelGen = pair<double, double> (deltaRGen, ETRelGen);
	  deltaRVsEtrelGen_.push_back(currDeltaREtrelGen);
	}


	//if isJetBetterPhoton
	if (jetPhotonOk) {
	  crosscleanedPhotonJets.push_back(*ijet);
	}
	//if isJetOverlappingPhoton
	if (!jetOk) {
	  allPhotonJets.push_back(*ijet);
	}
      }
    }

    //if NOT isJetOverlappingPhoton
    if (jetOk)
      crosscleanedJets.push_back(*ijet);    

  }

  selectedPhotonJets_ = crosscleanedPhotonJets; // deltaR <  0.3, Etrel >= 0.95
  allPhotonJets_      = allPhotonJets;          // deltaR <  0.3
  selectedJets_       = crosscleanedJets;       // deltaR >= 0.3

  if ( selectedPhotons_.size() > 0 ) {
    //bool firstPhoton = true;
	      
    for (std::vector<pat::Photon>::iterator photonBegin = selectedPhotons_.begin(), photonEnd = selectedPhotons_.end(), iphoton = photonBegin; iphoton != photonEnd; ++iphoton) { //all photons

      bool jetFound = false;
		
      for (std::vector<pat::Jet>::const_iterator jetsBegin = selectedPhotonJets_.begin(), jetsEnd = selectedPhotonJets_.end(), ijet = jetsBegin; ijet != jetsEnd; ++ijet) { //selected photon jets

	if ( isJetOverlappingPhoton(*ijet, *iphoton) ) { //deltaR < 0.3 (TRUE BY DEF INSIDE THIS LOOP!)

	  jetFound = true;
	  pat::Photon p = *iphoton;
	  pat::Jet uncorrJet = ijet->correctedJet("Uncorrected");
	  pat::Jet corrJetL1 = ijet->correctedJet("L1FastJet");
	  pat::Jet corrJet   = ijet->correctedJet( getPhotonJECLevel(*ijet) );

	  p.addUserFloat("ptMatchedJet", corrJet.pt()); //VS!!!

	  //START MET CORRECTION
	  double DeltaPx = 0.03 * uncorrJet.px();
	  double DeltaPy = 0.03 * uncorrJet.py();
	  double corrMetPx = met_->px() + DeltaPx;
	  double corrMetPy = met_->py() + DeltaPy;
	  reco::MET::LorentzVector correctedMET4vector(corrMetPx, corrMetPy, 0., 
								 sqrt(corrMetPx * corrMetPx + corrMetPy * corrMetPy));
	  std::vector<CorrMETData> corrections = met_->mEtCorr();

	  crosscleanedPhotons.push_back(p);
	  break;
	}//if deltaR < 0.3

      }//selected photon jet

      //no matching jet found? photon is fine and should be used!

      if (!jetFound) {
	//photon ok, not overlapping with 'better' jet, use photon
	pat::Photon p = *iphoton;
	p.addUserFloat("ptMatchedJet", (float) 0);

	crosscleanedPhotons.push_back(p);
      }//no photon-jet overlapping

    }//all photons
  }//if photons > 0

  selectedPhotons_ = crosscleanedPhotons;
}
	

//
bool PhotonJetSelector::isJetOverlappingPhoton(const pat::Jet jet, const pat::Photon photon) {
  //check overlap between jet and photon (deltaR<0.3)

  double deltaR_ = reco::deltaR(jet, photon);

  if ( deltaR_ < 0.3 ) 
    return true;
  else 
    return false;		
}

	
//
bool PhotonJetSelector::isJetBetterPhoton(pat::Jet jet, pat::Photon photon) {
  // check deltaR && Etrel between jet and photon
  // double ETRel = jet.et() / photon.et();
  double ETRel = jet.pt() / photon.pt(); //VS!!!

  if (jet.jecSetsAvailable() && jet.isPFJet()) {
    // ETRel = jet.correctedJet(getPhotonJECLevel(jet)).et() / photon.et();
    ETRel = jet.correctedJet( getPhotonJECLevel(jet) ).pt() / photon.pt(); //VS!!!
  }

  if (isJetOverlappingPhoton(jet, photon) && ETRel >= 0.95) 
    return true;
  else 
    return false;		
}

	
//
std::vector<pat::Jet> PhotonJetSelector::getLeptonCleanedJets(std::vector<pat::Jet> jets, bool isHLTJet) {
  //isHLTJet true in the getHLTJets() function only

  std::vector<pat::Jet> retjets;

  for (std::vector<pat::Jet>::const_iterator jetsBegin = jets.begin(), 
	 jetsEnd = jets.end(), ijet = jetsBegin; ijet != jetsEnd; ++ijet) {
    bool isJetPhotonLikeObject = false;

    if (selectedPhotons_.size() > 0) {
      for (std::vector<pat::Photon>::const_iterator photonBegin = selectedPhotons_.begin(), 
	     photonEnd = selectedPhotons_.begin() + 1, iphoton = photonBegin; iphoton != photonEnd; ++iphoton) {

	if (isJetOverlappingPhoton(*ijet, *iphoton)) //deltaR < 0.3
	  isJetPhotonLikeObject = true;
      }//photon loop
    }//if photon > 0

    bool rejectJet = false;
    if (!isJetPhotonLikeObject) { //NO jet-photon overlap

      if (ijet->hasOverlaps("muons") || ijet->hasOverlaps("electrons")) {
		  
	rejectJet = true;

	if (ijet->hasOverlaps("electrons")) { //overlap electron

	  if (isHLTJet)
	    selectedJetElectronsHLT_.push_back(*ijet);
	  else
	    selectedElectronJets_.push_back(*ijet);

	} else { //overlap muon

	  if (isHLTJet)
	    selectedJetMuonsHLT_.push_back(*ijet);
	  else
	    selectedMuonJets_.push_back(*ijet);

	}
      }
    }

    if (!rejectJet) //NO overlap with electrons and muons
      retjets.push_back(*ijet);
	      
  }//jets loop

  return retjets;
}


// Return HLT jets - photon cleaned
std::vector<pat::Jet> PhotonJetSelector::getHLTJets(edm::Handle<std::vector<pat::Jet> > jets) {
	    
  std::vector<pat::Jet> retjets;
  std::vector<pat::Jet> retjetsWoPhoton;

  if (!jets.isValid()) return retjets;

  //jet selection & cleaning	    
  for ( std::vector<pat::Jet>::const_iterator jetsBegin = jets->begin(), jetsEnd = jets->end(), ijet = jetsBegin; 
	ijet != jetsEnd; ++ijet ) {

    if ( ijet->pt() > 40  &&  abs( ijet->eta() ) < 3.0 )
      retjets.push_back(*ijet);

  }//for jetsHLT
   
  retjets = getCleanJetsJetID(retjets); // jetID cleaning


  for ( std::vector<pat::Jet>::const_iterator jetsBegin = retjets.begin(), 
	  jetsEnd = retjets.end(), ijet = jetsBegin; ijet != jetsEnd; ++ijet ) {

    if ( selectedPhotonsHLT_.size() > 0 ) {

      bool jetOverlapAPhoton = false;

      for ( std::vector<pat::Photon>::const_iterator photonBegin = selectedPhotonsHLT_.begin(), 
	      photonEnd = selectedPhotonsHLT_.end(), iphoton = photonBegin; iphoton != photonEnd; ++iphoton ) {

	if ( isJetBetterPhoton(*ijet, *iphoton) ){
	  jetOverlapAPhoton = true;	
	  break;
	}
	  
      }//for selectedPhotonsHLT_

      if( !jetOverlapAPhoton )
	retjetsWoPhoton.push_back(*ijet);

    } else {//if photons = 0
      retjetsWoPhoton.push_back(*ijet);
    }//if photonsHLT > 0
	      
  }//for jets

  return retjetsWoPhoton;
}


// Return ALL HLT jets
std::vector<pat::Jet> PhotonJetSelector::getHLTJetsAll(edm::Handle<std::vector<pat::Jet> > jets) {
	    
  std::vector<pat::Jet> retjets;

  if (!jets.isValid()) return retjets;

  //jet selection & cleaning	    
  for ( std::vector<pat::Jet>::const_iterator jetsBegin = jets->begin(), jetsEnd = jets->end(), ijet = jetsBegin; 
	ijet != jetsEnd; ++ijet ) {

    if ( ijet->pt() > 40  &&  abs( ijet->eta() ) < 3.0 )
      retjets.push_back(*ijet);

  }//for jetsHLT
   
  retjets = getCleanJetsJetID(retjets); // jetID cleaning

  return retjets;
}


// Clean jets using the CMSSW Jet Cleaner
std::vector<pat::Jet> PhotonJetSelector::getCleanJetsJetID(std::vector<pat::Jet> jets) {

  //create a PFJetIDSelectionFunctor object
  //look at CMSSW/PhysicsTools/SelectorUtils/interface/PFJetIDSelectionFunctor.h for details
  JetIDSelectionFunctor jetIDLoose(JetIDSelectionFunctor::PURE09, JetIDSelectionFunctor::LOOSE);
  PFJetIDSelectionFunctor pfjetIDLoose(PFJetIDSelectionFunctor::FIRSTDATA, PFJetIDSelectionFunctor::LOOSE);

  pat::strbitset ret   = jetIDLoose.getBitTemplate();
  pat::strbitset retPF = pfjetIDLoose.getBitTemplate();

  std::vector<pat::Jet> retjets;


  for (std::vector<pat::Jet>::const_iterator jetsBegin = jets.begin(), jetsEnd = jets.end(), 
	 ijet = jetsBegin; ijet != jetsEnd; ++ijet) {

    bool passJetID = false;

    if (ijet->isCaloJet() || ijet->isJPTJet())
      passJetID = jetIDLoose(*ijet, ret);
    else
      passJetID = pfjetIDLoose(*ijet, retPF);

    if (passJetID) 
      retjets.push_back(*ijet);

  }//for jets

  return retjets;
}


//
void PhotonJetSelector::setScanGeneratorInfo(edm::Handle<LHEEventProduct> lhe) {

  if (lhe.isValid()) {
    std::string comment = *(lhe->comments_begin());
    std::vector < std::string > commentSnippets;

    boost::split(commentSnippets, comment, boost::is_any_of("_"));

    double msqgl=0;
    if(commentSnippets.size()>=4){
      std::istringstream imsqgl(commentSnippets.at(2));
      imsqgl >> msqgl;
      std::istringstream imlsp(commentSnippets.at(3));
      imlsp >> mnlsp_;
    }
    else if(commentSnippets.size()>=4){
      std::istringstream imsqgl(commentSnippets.at(1));
      imsqgl >> msqgl;
      std::istringstream imlsp(commentSnippets.at(2));
      imlsp >> mnlsp_;
    }
    if (scanParameterisGluino_) {
      msquark_ = 10000;
      mgluino_ = msqgl;
    } else {
      mgluino_ = 10000;
      msquark_ = msqgl;
    }//if size >=4
  }//if valid lhe

}


std::vector<pat::Jet> PhotonJetSelector::getCleanJets(edm::Handle<std::vector<pat::Jet> > jets) {

	    std::vector<pat::Jet> retjets;

	    for (std::vector<pat::Jet>::const_iterator jetsBegin = jets->begin(), 
		   jetsEnd = jets->end(), ijet = jetsBegin; ijet != jetsEnd; ++ijet) {

	      bool passJetEta = false;

	      if ( abs(ijet->eta() ) < cut(jetEta_, double() ) ) //currently jetEta = 2.5 !!!
		passJetEta = true;
	   
	      if (passJetEta) 
		retjets.push_back(*ijet);
	    }//for jets

	    return retjets;
}


std::vector<pat::Jet> PhotonJetSelector::getGenJets(std::vector<pat::Jet> jets) { //TO BE DELETED ?!

	    std::vector<pat::Jet> ret;
	    for (std::vector<pat::Jet>::const_iterator jetsBegin = jets.begin(), 
		   jetsEnd = jets.end(), ijet = jetsBegin; ijet != jetsEnd; ++ijet) {

	      if (ijet->genJet() != 0) {
		if (ijet->genJet()->emEnergy() / ijet->genJet()->energy() < 0.9) {
		  ret.push_back(*ijet);
		}
	      }
	    }

	    return ret;
}


	  //VS!!! std::vector<pat::Jet> getCleanBJets(edm::Handle<std::vector<pat::Jet> > jets) {
std::vector<pat::Jet> PhotonJetSelector::getCleanBJets(std::vector<pat::Jet> jets) {
	    std::vector<pat::Jet> ret;

	    for (std::vector<pat::Jet>::const_iterator jetsBegin = jets.begin(), 
		   jetsEnd = jets.end(), ijet = jetsBegin; ijet != jetsEnd; ++ijet) {

	      //VS!!!
	      if ( ijet->bDiscriminator("combinedSecondaryVertexBJetTags") >= 0.679 ) {
		
		if (debug_) 
		  std::cout << "B-TAG  " << ijet->bDiscriminator("combinedSecondaryVertexBJetTags") << std::endl;

		ret.push_back(*ijet);
	      }
	    }
	  
	    return ret;
	  }
	  

std::vector<pat::Jet> PhotonJetSelector::getGenBJets(std::vector<pat::Jet> jets) { //TO BE DELETED ?!
	    std::vector<pat::Jet> ret;
	    for (std::vector<pat::Jet>::const_iterator jetsBegin = jets.begin(), 
		   jetsEnd = jets.end(), ijet = jetsBegin; ijet != jetsEnd; ++ijet) {
	      //	      if (abs(ijet->partonFlavour()) == 4 || abs(ijet->partonFlavour()) == 5) { // 4 is CHARM !!!
	      if ( abs(ijet->partonFlavour()) == 5 ) {
		ret.push_back(*ijet);
	      }
	    }
	    return ret;
}

	  
bool PhotonJetSelector::hasMatchingElectron(std::vector<pat::Photon>::const_iterator iphoton, edm::Handle<reco::GenParticleCollection> genPartHandle, bool rejectPhotons) {
	    //this function looks for a matching between the photon and 
	    //a generated electron as direct product of the interaction
	    //status = 3 -> "This includes the two incoming colliding 
	    //particles and partons produced in hard interaction." 
	    //[https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookGenParticleCandidate]

	    if (iphoton->genPhoton() == 0 || !rejectPhotons) {

	      for (reco::GenParticleCollection::const_iterator genPartIter = genPartHandle->begin(); 
		   genPartHandle->end() != genPartIter; ++genPartIter) {

		const reco::GenParticle * genPart = &(*genPartIter);

		if (genPart != 0) {
		  if (abs(genPartIter->pdgId()) == 11) {
		    if (genPartIter->status() == 3) {
		      if (abs((iphoton->pt() - genPartIter->pt())) / iphoton->pt() <= 0.3) {
			if (reco::deltaR(*iphoton, *genPartIter) <= 0.4) {
			  
			  return true;

			}//if deltaR <= 0.4
		      }//if ptRel <= 0.3
		    }//if status = 3
		  }//if pdgId = 11
		}//if genPart

	      }//for genPartIter
	    }//if iphoton (usually rejectPhotons = False)
		
	    return false;
}
	  

std::vector<pat::Photon> PhotonJetSelector::getHadrons(std::vector<pat::Photon> photons, edm::Handle<reco::GenParticleCollection> genPartHandle, bool revertSelection) {

	    std::vector<pat::Photon> ret;
	    ret.clear();

	    for (std::vector<pat::Photon>::const_iterator photonBegin = photons.begin(), 
		   photonEnd = photons.end(), iphoton = photonBegin; iphoton != photonEnd; ++iphoton) {
			
	      bool matchFound = false;
		
	      for (reco::GenParticleCollection::const_iterator genPartIter = genPartHandle->begin(); 
		   genPartHandle->end() != genPartIter; ++genPartIter) {

		const reco::GenParticle * genPart = &(*genPartIter);

		if (genPart != 0) {
		  if (abs(genPartIter->pdgId()) <= 6) {
		    if (genPartIter->status() == 3) {
		      if (abs((iphoton->pt() - genPartIter->pt())) / iphoton->pt() <= 0.3) {
			if (reco::deltaR(*iphoton, *genPartIter) <= 0.4) {

			  matchFound = true;
			  
			}//if deltaR <= 0.4
		      }//if ptRel <= 0.3
		    }//if status = 3
		  }//if pdfId <= 6 (d,u,s,c,b,t quarks)
		}//if genPart

	      }//loop genPartHandle

	      if (matchFound && !revertSelection) {
		ret.push_back(*iphoton);
	      } else if (revertSelection) {
		ret.push_back(*iphoton);
	      }

	    }//loop photons

	    return ret;
}


std::vector<pat::Photon> PhotonJetSelector::getGenElectrons(std::vector<pat::Photon> photons, edm::Handle<reco::GenParticleCollection> genPartHandle, bool rejectPhotons) {

	    std::vector<pat::Photon> ret;
	    ret.clear();
	    
	    for (std::vector<pat::Photon>::const_iterator photonBegin = photons.begin(), 
		   photonEnd = photons.end(), iphoton = photonBegin; iphoton != photonEnd; ++iphoton) {

	      if (hasMatchingElectron(iphoton, genPartHandle, rejectPhotons)) {

		ret.push_back(*iphoton);

	      }//if hasMatchingElectron
	    }//loop photons

	    return ret;
}


std::vector<pat::Photon> PhotonJetSelector::getGenPhotons(std::vector<pat::Photon> photons, edm::Handle<reco::GenParticleCollection> genPartHandle, bool rejectElectrons) {
		
	    std::vector<pat::Photon> ret;
	    ret.clear();
		
	    for (std::vector<pat::Photon>::const_iterator photonBegin = photons.begin(), 
		   photonEnd = photons.end(), iphoton = photonBegin; iphoton != photonEnd; ++iphoton) {
	      if (iphoton->genPhoton() != 0) {
		if (!hasMatchingElectron(iphoton, genPartHandle, false) || !rejectElectrons)
		  if (abs(iphoton->genPhoton()->pdgId()) == cut(photonGenPdgId_, double())) {
		    if (abs((iphoton->pt() - iphoton->genPhoton()->pt())) / iphoton->pt() <= 0.1) {
		      if (reco::deltaR(*iphoton, *(iphoton->genPhoton())) <= 0.2) {

			if (cut(photonGenPdgIdMother_, double()) == 0 || 
			    (abs(iphoton->genPhoton()->mother()->pdgId()) == cut(photonGenPdgIdMother_, double()))) {

			  ret.push_back(*iphoton);

			}//if deltaR <= 0.2
		      }//if ptRel <= 0.1
		    }//if pdgId = 22
		  }//if NOT electron
	      }//if genPhoton
	    }//for photons

	    return ret;
}


//
std::vector<pat::Photon> PhotonJetSelector::getCleanPhotons(edm::Handle<std::vector<pat::Photon> > photons) {
	    
  std::vector<pat::Photon> ret;

  for (std::vector<pat::Photon>::const_iterator photonBegin = photons->begin(), 
	 photonEnd = photons->end(), iphoton = photonBegin; iphoton != photonEnd; ++iphoton) {

    bool passPhotonEta = false;
	      
    if (abs(iphoton->eta()) < cut(photonEta_, double())) {
      passPhotonEta = true;
    }//if eta

    if (passPhotonEta)
      ret.push_back(*iphoton);

  }//loop photons

  return ret;
}


//cleaning function
void PhotonJetSelector::resetSelection() {
  photon_  = 0;
  photon2_ = 0;
  met_     = 0;
  jet_     = 0;
  jet2_    = 0;
  jet3_    = 0;
  jet4_    = 0;
  bjet_    = 0;
  bjet2_   = 0;
  noPV_    = 0;
  noPVPU_  = 0;

  selectedBJets_.clear();
  selectedJets_.clear();
  selectedJetsHLT_.clear();
  selectedPhotons_.clear();
  deltaRVsEtrel_.clear();
  deltaRVsEtrelGen_.clear();
  deltaRVsEtrelUncorr_.clear();
  selectedPhotonJets_.clear();
  allPhotonJets_.clear();

  selectedElectronJets_.clear();
  selectedMuonJets_.clear();
  selectedJetElectronsHLT_.clear();
  selectedJetMuonsHLT_.clear();
	    
  msquark_ = 0;
  mgluino_ = 0;
  mnlsp_ = 0;
}



//typedef edm::FilterWrapper<PhotonJetSelector> WrappedPhotonJetFilter;
//DEFINE_FWK_MODULE(WrappedPhotonJetFilter);
//DEFINE_FWK_MODULE(PhotonJetSelector);

//THE END!
