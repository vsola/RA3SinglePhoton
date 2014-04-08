#ifndef SELECTIONANALYZER_H_
#define SELECTIONANALYZER_H_

// c++
#include <map>
#include <string>
#include <fstream>
#include <memory>

// root
#include "TROOT.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TString.h"

// cmssw
#include "PhysicsTools/UtilAlgos/interface/BasicAnalyzer.h"
#include "PhysicsTools/UtilAlgos/interface/EDAnalyzerWrapper.h"
#include "PhysicsTools/UtilAlgos/interface/EDFilterWrapper.h"

#include "PhysicsTools/SelectorUtils/interface/strbitset.h"
#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"

#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/PatCandidates/interface/Photon.h"


// user include files
#include "PhotonSusyAnalysis/SelectionAnalyzer/interface/PhotonJetSelector.h"

#include "Util/OwnUtil/interface/HistoDrawUtil.h"
#include "Util/OwnUtil/interface/PhysicsUtil.h"


class SelectionAnalyzer: public edm::BasicAnalyzer {

  public:
    /// default constructor
    SelectionAnalyzer(const edm::ParameterSet& cfg, TFileDirectory& fs);

    /// default destructor
    virtual ~SelectionAnalyzer() {
    };

    /// everything that needs to be done before the event loop
    void beginJob() ;

    /// everything that needs to be done after the event loop
    void endJob() ;

    /// everything that needs to be done during the event loop
    void analyze(const edm::EventBase& event);

    void initializeHistosSignalScan(TFileDirectory * fs, std::string prefix = "", std::string parPoint = "");
    void initializeHistos(TFileDirectory& fs, std::string prefix = "");

    void printBinnedMETAbove100STAT(PhotonJetSelector pjSelector, std::string prefix = "", std::string signalParPoint = "");
    void printBinnedMETAbove100(PhotonJetSelector pjSelector, std::string prefix = "", std::string signalParPoint = "");
    void printBinsMETAbove100(PhotonJetSelector pjSelector, std::string prefix = "", std::string signalParPoint = "");

    TH1F * rebinMETHistoForEventYields(TH1F * metHisto);
    void fillHistosSignalscan(const edm::EventBase& event, double weight, double weightNoPURescale, PhotonJetSelector pjSelector, std::string prefix = "", int squarkm = 0, int gluinom = 0, int neutrm = 0);
    void fillHistos(const edm::EventBase& event, double weight, double weightNoPURescale, PhotonJetSelector pjSelector, std::string prefix = "", int squarkm = 0, int gluinom = 0, int neutrm = 0);


  private:
    int loggingVerbosity_;
    bool plotOnlyEventsPassing_, drawPlots_, applyPUReweighting_, applyFakeRateCorrection_, punchthroughtest_, applyFakeRateCorrectionHisto_, applyFakeRateCorrectionHT_, applyEWKFakeRateCorrection_;
    double applyFakeRateCorrectionPar1_, applyFakeRateCorrectionPar2_, applyFakeRateCorrectionPar3_, applyFakeRateCorrectionPar4_, applyFakeRateCorrectionPar5_, applyFakeRateSystFit_, applyFakeRateSystSMCont_, applyFakeRateSystLowHighMet_, applyEWKFakeRatePar1_, applyEWKFakeRateParErr1_;
    std::vector<double> PUDistributionData_, PUDistributionMC_;
    std::string applyFakeRateCorrectionHistoName_,applyFakeRateCorrectionHistoName2j_, applyFakeRateCorrectionHistoNameHT_;
    /// PhotonJetSelector
    edm::ParameterSet selection_;
    PhotonJetSelector pjSelector_;
    PhotonJetSelector pjSelectorN1_;
    PhotonJetSelector pjSelectorPresel_;

    std::vector<std::string> cutsN1_;
    std::vector<std::string> cutsPresel_;
    /// histograms
    std::map<std::string, TH1*> hists_;
    std::map<std::string, TH2*> hists2D_;

    std::vector<std::string> signalScanPoints_;
    std::vector<std::string> highMetEvents_;
    std::vector<std::string> punchthroughEvents_;
    edm::LumiReWeighting LumiWeights_;
    TH1F * qcdCorrection_;
    TH1F * qcdCorrection2j_;
    TH2F * qcdCorrectionHT_;
    pat::strbitset pjSelectorReturnsN1_;
    pat::strbitset pjSelectorReturnsPresel_;
    pat::strbitset pjSelectorReturns_;
    double evtCounter_, evtCounter100_, evtCounter200_, evtCounter350_, evtCounterPresel_, evtCounterWeighted_, evtCounterWeightedError_, evtCounterPreselWeighted_, evtCounterPreselWeightedError_;
    TFileDirectory *  fs_;

    // test
    edm::InputTag srcRho_;

};


#endif /* SELECTIONANALYZER_H_ */
typedef edm::AnalyzerWrapper<SelectionAnalyzer> WrappedSelectionAnalyzer;
DEFINE_FWK_MODULE( WrappedSelectionAnalyzer);

typedef edm::FilterWrapper<PhotonJetSelector> WrappedPhotonJetFilter;
DEFINE_FWK_MODULE(WrappedPhotonJetFilter);
