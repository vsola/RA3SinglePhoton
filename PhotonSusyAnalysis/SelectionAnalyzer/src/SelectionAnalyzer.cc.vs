// -*- C++ -*-
//
// Package:    SelectionAnalyzer
// Class:      SelectionAnalyzer
//
/**\class SelectionAnalyzer SelectionAnalyzer.cc PhotonSusyAnalysis/SelectionAnalyzer/src/SelectionAnalyzer.cc

 Description: [one line class summary]

 Implementation:
 [Notes on implementation]
 */
//
// Original Author:  Ulla Gebbert,,,uni-hamburg
//         Created:  Tue Feb  8 10:13:40 CET 2011
// $Id: SelectionAnalyzer.cc,v 1.3 2012/12/10 08:26:01 kiesel Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/PatCandidates/interface/Photon.h"

#include "Util/OwnUtil/interface/HistoDrawUtil.h"
#include "Util/OwnUtil/interface/PhysicsUtil.h"
#include "PhotonSusyAnalysis/SelectionAnalyzer/interface/SelectionAnalyzer.h"

//
// class declaration
//
using namespace HistoDrawUtil;


// everything that needs to be done during the event loop
void SelectionAnalyzer::analyze(const edm::EventBase& event) {

  int lumis   = (int) event.eventAuxiliary().luminosityBlock();
  int run     = (int) event.eventAuxiliary().run();
  int eventno = (int) event.eventAuxiliary().event();

  using pat::Photon;
  using pat::Jet;
  using pat::MET;

  //load weight from event - if available
  double weight     = 1.0;
  double weightNoPU = 1.0;

  edm::InputTag weightTag("weightProducer", "weight", "PhotonJetSelection");
  edm::InputTag weightTagPat("weightProducer", "weight", "PhotonJetSelectionFromPat");
  edm::Handle<double> weight_;
  edm::Handle<double> weightPAT_;

  // get the objects from the event
  bool gotWeightPAT = event.getByLabel(weightTagPat, weightPAT_);

  if (!gotWeightPAT) {
    bool gotWeight = event.getByLabel(weightTag, weight_);

    if (gotWeight)
      weight = *weight_;
    else
      weight = 1;

  } else {
    weight = *weightPAT_;
  }

  //		std::cout << "WEIGHT Full Evt: " << *weight_    << std::endl;
  //		std::cout << "WEIGHT PAT: "      << *weightPAT_ << std::endl;
  //		std::cout << "WEIGHT Taken: "    <<  weight     << std::endl;

  //check if event passes selection
  pjSelectorReturns_ = pjSelector_.getBitTemplate();
  bool passSelection = pjSelector_(event, pjSelectorReturns_);
  weightNoPU = weight;

  if (applyPUReweighting_) {

    double puweight = LumiWeights_.weight(pjSelector_.getNoPVPU());
    weight = weight * puweight;

  }

  //prepare weights for syst variation
  double weightSYSTUP   = weight;
  double weightSYSTDOWN = weight;

  //check if event passes preselection
  pat::strbitset maskPresel      = pjSelectorPresel_.getBitTemplate();
  bool passesAllCutsExceptPresel = pjSelectorPresel_(event, maskPresel);

  if(punchthroughtest_){
    int rpcHits;
    rpcHits = 0;
    double JetPT;
    JetPT = 0;

    if(pjSelector_.isPunchthroughMuonBJet(rpcHits, JetPT))
      std::cout << "-------------------------Possible MuonBJet Punchthrough!!!---------------"
		<< run << " : " << lumis << " : " << eventno << std::endl;


    if(pjSelector_.isPunchthroughTrackCounting(rpcHits, JetPT))
      std::cout << "-------------------------Possible TrackCounting Punchthrough!!!---------------"
		<< run << " : " << lumis << " : " << eventno << std::endl;

    if((pjSelector_.isPunchthroughMuonBJet(rpcHits, JetPT)) || (pjSelector_.isPunchthroughTrackCounting(rpcHits, JetPT))){
      punchthroughEvents_.push_back(HistoDrawUtil::getStringFromInt(run) + ":" + HistoDrawUtil::getStringFromInt(lumis) + ":" + HistoDrawUtil::getStringFromInt(eventno) + " & " + HistoDrawUtil::getStringFromInt(rpcHits)+ " & " + HistoDrawUtil::getStringFromDouble(JetPT) + " & " + HistoDrawUtil::getStringFromDouble(pjSelector_.met().pt()) + " & " + HistoDrawUtil::getStringFromDouble(pjSelector_.met2().pt()) + "\\\\");
    }

  }//if punchthroughtest_

  // Apply FO Correction
  if (applyFakeRateCorrection_ && passesAllCutsExceptPresel) {

    //		std::cout << "============weight BEFORE Fake rate:" << weight << std::endl;
    //		std::cout << "Photon Found?:" << pjSelectorPresel_.isPhotonValid() << std::endl;

    double fakerateEventweight = pjSelectorPresel_.getFakeRateWeight( applyFakeRateCorrectionPar1_, applyFakeRateCorrectionPar2_, applyFakeRateCorrectionPar3_, applyFakeRateCorrectionPar4_, applyFakeRateCorrectionPar5_, applyFakeRateCorrectionHisto_, applyFakeRateCorrectionHT_, qcdCorrection_,qcdCorrection2j_, qcdCorrectionHT_ );

    double fakerateEventweightSYSTUP   = pjSelectorPresel_.getFakeRateWeightSYST( applyFakeRateCorrectionPar1_, applyFakeRateCorrectionPar2_, applyFakeRateCorrectionPar3_, applyFakeRateCorrectionPar4_, applyFakeRateCorrectionPar5_, 2, applyFakeRateCorrectionHisto_, applyFakeRateCorrectionHT_, qcdCorrection_,qcdCorrection2j_, qcdCorrectionHT_, applyFakeRateSystFit_, applyFakeRateSystLowHighMet_, applyFakeRateSystSMCont_ );

    double fakerateEventweightSYSTDOWN = pjSelectorPresel_.getFakeRateWeightSYST( applyFakeRateCorrectionPar1_, applyFakeRateCorrectionPar2_, applyFakeRateCorrectionPar3_, applyFakeRateCorrectionPar4_, applyFakeRateCorrectionPar5_, 1, applyFakeRateCorrectionHisto_, applyFakeRateCorrectionHT_, qcdCorrection_,qcdCorrection2j_, qcdCorrectionHT_, applyFakeRateSystFit_, applyFakeRateSystLowHighMet_, applyFakeRateSystSMCont_ );

    weightSYSTUP   = weight * fakerateEventweightSYSTUP;
    weightSYSTDOWN = weight * fakerateEventweightSYSTDOWN;
    weight         = weight * fakerateEventweight;
    weightNoPU     = weightNoPU * fakerateEventweight;

    //	std::cout << "photon pt:" << pjSelectorPresel_.correctedphotonpt() << std::endl;
    //	std::cout << "fake rate:" << fakerateEventweight                   << std::endl;
    //	std::cout << "============weight AFTER Fake rate:" << weight       << std::endl;

  }//if applyFakeRateCorrection && passesAllCutsExceptPresel

  // Apply EWK Correction
  if (applyEWKFakeRateCorrection_ && passesAllCutsExceptPresel) {
    //std::cout << "============weight BEFORE EWK rate:" << weight << std::endl;
    double weightEWK = applyEWKFakeRatePar1_;

    weight         = weight         *  weightEWK;
    weightNoPU     = weightNoPU     *  weightEWK;
    weightSYSTUP   = weightSYSTUP   * (weightEWK + applyEWKFakeRateParErr1_);
    weightSYSTDOWN = weightSYSTDOWN * (weightEWK - applyEWKFakeRateParErr1_);

    //std::cout << "============weight AFTER EWK rate:" << weight << std::endl;
  }//if applyEWKFakeRateCorrection && passesAllCutsExceptPresel


  //std::cout<<"==========passSelection  "<<passSelection<<std::endl;

  //fill N-1 plots
  for (int cutIt = 0; cutIt < (int) (cutsN1_.size()); ++cutIt) {
    std::string cut = cutsN1_.at(cutIt);

    //mask cuts for N-1 plots
    pat::strbitset mask = pjSelectorN1_.getBitTemplate();

    mask[cut] = true;

    bool passesAllCutsExceptCurrent = pjSelectorN1_(event, mask);
    if (passesAllCutsExceptCurrent)
      fillHistos(event, weight, weightNoPU, pjSelectorN1_, "N_1_" + cut + "_");

  }//for cutsN1


  if (passesAllCutsExceptPresel) {
    evtCounterPresel_++;
    evtCounterPreselWeighted_      = evtCounterPreselWeighted_      + weight;
    evtCounterPreselWeightedError_ = evtCounterPreselWeightedError_ + weightSYSTUP;

    //check if event is signal scan MC (official scan) and contains LHEE info
    if(pjSelector_.mgluino()!=0 || pjSelector_.msquark()!=0 ){

      //fill this parameter point in signalscan list
      std::string parPoint=pjSelector_.getSignalScanPointName();

      if(find(signalScanPoints_.begin(),signalScanPoints_.end(),parPoint)==signalScanPoints_.end()){
	// cout<<"NEW SIGNAL POINT!!!!!!!!!!!"<<parPoint<<endl;
	signalScanPoints_.push_back(parPoint);

	initializeHistosSignalScan(fs_, "PreselCut_", parPoint);
	initializeHistosSignalScan(fs_, "PreselCut_SYSTUP_", parPoint);
	initializeHistosSignalScan(fs_, "PreselCut_SYSTDOWN_", parPoint);
      }//if NEW signal point

    }//if signal scan MC

    fillHistos(event, weight, weightNoPU, pjSelectorPresel_, "PreselCut_",pjSelector_.msquark(),pjSelector_.mgluino(),pjSelector_.mnlsp());
    fillHistos(event, weightSYSTUP, weightNoPU, pjSelectorPresel_, "PreselCut_SYSTUP_",pjSelector_.msquark(),pjSelector_.mgluino(),pjSelector_.mnlsp());
    fillHistos(event, weightSYSTDOWN, weightNoPU, pjSelectorPresel_, "PreselCut_SYSTDOWN_",pjSelector_.msquark(),pjSelector_.mgluino(),pjSelector_.mnlsp());

    if (pjSelector_.met().pt() >= 100)
      evtCounter100_ += weight;

    if (pjSelector_.met().pt() >= 200)
      evtCounter200_ += weight;

    if (pjSelector_.met().pt() >= 350)
      evtCounter350_ += weight;


    // Check on high b-tag multiplicity
    /*
    if ( pjSelector_.isPhotonValid() && pjSelector_.isJet2Valid() ) {
      if ( pjSelector_.selectedBJets().size() >= 3 ){
	cout << "VS!!!"
	     << " - lumis: "       << event.eventAuxiliary().luminosityBlock()
	     << " , run: "         << event.eventAuxiliary().run()
	     << " , event#: "      << event.eventAuxiliary().event()
	     << "-> photon Pt: "   << pjSelector_.correctedphotonpt()
	     << " , MET: "         << pjSelector_.met().pt()
	     << " , # of jets: "   << pjSelector_.selectedJets().size()
	     << " , 1st jet Pt: "  << pjSelector_.jet().pt()
	     << " , 2nd jet Pt: "  << pjSelector_.jet2().pt()
	     << " , # of b jets: " << pjSelector_.selectedBJets().size()
	     << " , 1st bjet Pt: " << pjSelector_.bjet().pt()
	     << " , 2nd bjet Pt: " << pjSelector_.bjet2().pt()
	     << endl
	     << endl;
      }
    }//end b-tag checks
    */

  }//if passesAllaCutsExceptPresel


  //make plots based on selection
  if (passSelection || !plotOnlyEventsPassing_) {

    evtCounter_++;

    evtCounterWeighted_ = evtCounterWeighted_ + weight;
    evtCounterWeightedError_ = evtCounterWeightedError_ + weightSYSTUP;

    //add weighted entries for 200/350 cut, for signal scan weight is set to 1
    //and we need to get the rewighting stuff done and included in the acceptance


    //fill plots
    fillHistos(event, weightSYSTUP, weightNoPU, pjSelector_, "SYSTUP_");
    fillHistos(event, weightSYSTDOWN, weightNoPU, pjSelector_, "SYSTDOWN_");
    fillHistos(event, weight, weightNoPU, pjSelector_);

    ///cout Run/Event information of high MET Tails!
    if (pjSelector_.met().pt() > 300) {
      int lumis   = (int) event.eventAuxiliary().luminosityBlock();
      int run     = (int) event.eventAuxiliary().run();
      int eventno = (int) event.eventAuxiliary().event();
      highMetEvents_.push_back(HistoDrawUtil::getStringFromInt(run) + ":" + HistoDrawUtil::getStringFromInt(lumis) + ":" + HistoDrawUtil::getStringFromInt(eventno));
    }//if highMetEvents ( MET > 300 GeV )

  }//if passSelection


}

