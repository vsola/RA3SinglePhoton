#include "PhotonSusyAnalysis/SelectionAnalyzer/interface/SelectionAnalyzer.h"
#include "TMath.h"

using namespace HistoDrawUtil;

SelectionAnalyzer :: SelectionAnalyzer(const edm::ParameterSet& cfg, TFileDirectory& fs):
        edm::BasicAnalyzer::BasicAnalyzer(cfg, fs),
        loggingVerbosity_ ( cfg.getParameter<int> ("loggingVerbosity") ),
        plotOnlyEventsPassing_(cfg.getParameter<bool> ("plotOnlyEventsPassing")),
        drawPlots_(cfg.getParameter<bool> ("drawPlots")),
        applyPUReweighting_(cfg.getParameter<bool> ("applyPUReweighting")),
        applyFakeRateCorrection_(cfg.getParameter<bool> ("applyFakeRateCorrection")),
        punchthroughtest_(cfg.getParameter<bool> ("punchthroughtest")),
        applyFakeRateCorrectionHisto_(cfg.getParameter<bool> ("applyFakeRateCorrectionHisto")),
        applyFakeRateCorrectionHT_(cfg.getParameter<bool> ("applyFakeRateCorrectionHT")),
        applyEWKFakeRateCorrection_(cfg.getParameter<bool> ("applyEWKFakeRateCorrection")),
        applyFakeRateCorrectionPar1_(cfg.getParameter<double> ("applyFakeRateCorrectionPar1")),
        applyFakeRateCorrectionPar2_(cfg.getParameter<double> ("applyFakeRateCorrectionPar2")),
        applyFakeRateCorrectionPar3_(cfg.getParameter<double> ("applyFakeRateCorrectionPar3")),
        applyFakeRateCorrectionPar4_(cfg.getParameter<double> ("applyFakeRateCorrectionPar4")),
        applyFakeRateCorrectionPar5_(cfg.getParameter<double> ("applyFakeRateCorrectionPar5")),
        applyFakeRateSystFit_(cfg.getParameter<double> ("applyFakeRateSystFit")),
        applyFakeRateSystSMCont_(cfg.getParameter<double> ("applyFakeRateSystSMCont")),
        applyFakeRateSystLowHighMet_(cfg.getParameter<double> ("applyFakeRateSystLowHighMet")),
        applyEWKFakeRatePar1_(cfg.getParameter<double> ("applyEWKFakeRatePar1")),
        applyEWKFakeRateParErr1_(cfg.getParameter<double> ("applyEWKFakeRateParErr1")),
        PUDistributionData_(cfg.getParameter<std::vector<double> > ("PUDistributionData")),
        PUDistributionMC_(cfg.getParameter<std::vector<double> > ("PUDistributionMC")),
        applyFakeRateCorrectionHistoName_(cfg.getParameter<std::string> ("applyFakeRateCorrectionHistoName")),
        applyFakeRateCorrectionHistoName2j_(cfg.getParameter<std::string> ("applyFakeRateCorrectionHistoName2j")),
        applyFakeRateCorrectionHistoNameHT_(cfg.getParameter<std::string> ("applyFakeRateCorrectionHistoNameHT")),
        selection_(cfg.getParameter<edm::ParameterSet> ("selection")),
        pjSelector_(selection_),
        pjSelectorN1_(selection_),
        pjSelectorPresel_(selection_) {

    //ini LumiWeights
    if (applyPUReweighting_) {
      if ( loggingVerbosity_ > 1 ) {
	std::cout << "PU MC:" << PUDistributionMC_.size() << std::endl;
	std::cout << "PU Data:" << PUDistributionData_.size() << std::endl;
      }
      std::vector<float> PUDistributionMCF(PUDistributionMC_.begin(), PUDistributionMC_.end());
      std::vector<float> PUDistributionDataF(PUDistributionData_.begin(), PUDistributionData_.end());
      LumiWeights_ = edm::LumiReWeighting(PUDistributionMCF, PUDistributionDataF);
    }
    fs_=&fs;

    //cout<<"ini Histos"<<endl;
    initializeHistos(fs);
    initializeHistos(fs, "SYSTUP_");
    initializeHistos(fs, "SYSTDOWN_");
    if (cfg.exists("cutsForPresel")) {
      cutsPresel_ = cfg.getParameter<std::vector<std::string> > ("cutsForPresel");
    }
    initializeHistos(fs, "PreselCut_");
    initializeHistos(fs, "PreselCut_SYSTUP_");
    initializeHistos(fs, "PreselCut_SYSTDOWN_");
    //set correct cuts for Presel Selector
    pjSelectorPresel_.setIgnoredCuts(pjSelectorPresel_.getAllCuts());
    for (int cutIt = 0; cutIt < (int) (cutsPresel_.size()); ++cutIt) {
      std::string cut = cutsPresel_.at(cutIt);

      pjSelectorPresel_.set(cut, true);
      //cout<<"turn on cut:"<<cut<<endl;

    }

    /*
    if (cfg.exists("cutsForN1")) {
        cutsN1_ = cfg.getParameter<std::vector<std::string> > ("cutsForN1");
        for (int cutIt = 0; cutIt < (int) (cutsN1_.size()); ++cutIt) {
            std::string cut = cutsN1_.at(cutIt);
            if ( loggingVerbosity_ > 1 )
                std::cout << "ini Histos" << "N_1_" << cut << "_" << std::endl;
            initializeHistos(fs, "N_1_" + cut + "_");
        }
    }
    */

    std::string fileName("PhotonSusyAnalysis/SelectionAnalyzer/data/" + applyFakeRateCorrectionHistoName_ + ".root");
     if ( loggingVerbosity_ > 1 ) {
        std::cout << "filename:" << applyFakeRateCorrectionHistoName_ << std::endl;
    }
    edm::FileInPath fip(fileName);

    TFile* f = TFile::Open(fip.fullPath().c_str());
    std::string canvasname = "cWdj";

    TCanvas * c = (TCanvas *) f->FindObjectAny(canvasname.c_str());
    std::string histoname = "hptW";
    if ( loggingVerbosity_ > 1 ){
        std::cout << "canvas:" << c << std::endl;
    }

    qcdCorrection_ = (TH1F *) c->FindObject(histoname.c_str());
    qcdCorrection_->SetDirectory(0);

    // read ==2jet correction histo
    std::string fileName2j("PhotonSusyAnalysis/SelectionAnalyzer/data/" + applyFakeRateCorrectionHistoName2j_ + ".root");
    if ( loggingVerbosity_ > 1 )
      std::cout << "filename2j:" << applyFakeRateCorrectionHistoName2j_ << std::endl;
    edm::FileInPath fip2j(fileName2j);

    TFile* f2j = TFile::Open(fip2j.fullPath().c_str());
    std::string canvasname2j = "cWdj";

    TCanvas * c2j = (TCanvas *) f2j->FindObjectAny(canvasname2j.c_str());
    if ( loggingVerbosity_ > 1 )
      std::cout << "canvas2j:" << c2j << std::endl;
    
    qcdCorrection2j_ = (TH1F *) c2j->FindObject(histoname.c_str());
    qcdCorrection2j_->SetDirectory(0);

    // read in HT histogram
    std::string fileNameHT("PhotonSusyAnalysis/SelectionAnalyzer/data/" + applyFakeRateCorrectionHistoNameHT_ + ".root");
    if ( loggingVerbosity_ > 1 )
        std::cout << "filename HT:" << applyFakeRateCorrectionHistoNameHT_ << std::endl;
    edm::FileInPath fipHT(fileNameHT);

    TFile* fHT = TFile::Open(fipHT.fullPath().c_str());
    canvasname = "cWdj";
    TCanvas * cHT = (TCanvas *) fHT->FindObjectAny(canvasname.c_str());
    if ( loggingVerbosity_ > 1 )
        std::cout << "canvas HT:" << cHT << std::endl;

    std::string histonameHT = "hpthtW";

    qcdCorrectionHT_ = (TH2F *) cHT->FindObject(histonameHT.c_str());
    qcdCorrectionHT_->SetDirectory(0);

    // debug
    if ( loggingVerbosity_ > 1 )
      std::cout << "constructor done:" << c << std::endl;

    // test
    // srcRho_ = cfg.getParameter<edm::InputTag> ("srcRho");


    f->Close();
    delete f;
    fHT->Close();
    delete fHT;

    return;
}


void SelectionAnalyzer :: beginJob() {
    evtCounter_ = 0;
    evtCounter100_ = 0;
    evtCounter200_ = 0;
    evtCounter350_ = 0;
    evtCounterPresel_ = 0;
    evtCounterWeighted_ = 0;
    evtCounterWeightedError_ = 0;
    evtCounterPreselWeighted_ = 0;
    evtCounterPreselWeightedError_ = 0;
    highMetEvents_.clear();
    signalScanPoints_.clear();
    punchthroughEvents_.clear();
}

// everything that needs to be done during the event loop
void SelectionAnalyzer :: analyze(const edm::EventBase& event) {

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

        double fakerateEventweight = pjSelectorPresel_.getFakeRateWeight( applyFakeRateCorrectionPar1_, applyFakeRateCorrectionPar2_, applyFakeRateCorrectionPar3_, applyFakeRateCorrectionPar4_, applyFakeRateCorrectionPar5_, applyFakeRateCorrectionHisto_, applyFakeRateCorrectionHT_, qcdCorrection_,qcdCorrection2j_, qcdCorrectionHT_ );

        double fakerateEventweightSYSTUP   = pjSelectorPresel_.getFakeRateWeightSYST( applyFakeRateCorrectionPar1_, applyFakeRateCorrectionPar2_, applyFakeRateCorrectionPar3_, applyFakeRateCorrectionPar4_, applyFakeRateCorrectionPar5_, 2, applyFakeRateCorrectionHisto_, applyFakeRateCorrectionHT_, qcdCorrection_,qcdCorrection2j_, qcdCorrectionHT_, applyFakeRateSystFit_, applyFakeRateSystLowHighMet_, applyFakeRateSystSMCont_ );

        double fakerateEventweightSYSTDOWN = pjSelectorPresel_.getFakeRateWeightSYST( applyFakeRateCorrectionPar1_, applyFakeRateCorrectionPar2_, applyFakeRateCorrectionPar3_, applyFakeRateCorrectionPar4_, applyFakeRateCorrectionPar5_, 1, applyFakeRateCorrectionHisto_, applyFakeRateCorrectionHT_, qcdCorrection_,qcdCorrection2j_, qcdCorrectionHT_, applyFakeRateSystFit_, applyFakeRateSystLowHighMet_, applyFakeRateSystSMCont_ );

        weightSYSTUP   = weight * fakerateEventweightSYSTUP;
        weightSYSTDOWN = weight * fakerateEventweightSYSTDOWN;
        weight         = weight * fakerateEventweight;
        weightNoPU     = weightNoPU * fakerateEventweight;

        //    std::cout << "photon pt:" << pjSelectorPresel_.correctedphotonpt() << std::endl;
        //    std::cout << "fake rate:" << fakerateEventweight                   << std::endl;
        //    std::cout << "============weight AFTER Fake rate:" << weight       << std::endl;

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

    /*
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
    */


    if (passesAllCutsExceptPresel) {
        evtCounterPresel_++;
        evtCounterPreselWeighted_            = evtCounterPreselWeighted_            + weight;
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

	/*
        if ( pjSelector_.isPhotonValid() && 
	     pjSelector_.isJetValid()    && 
	     pjSelector_.isJet2Valid()   && 
	     pjSelector_.isMetValid()    ){

            if ( pjSelector_.selectedPhotons().size() >= 1 &&
		 pjSelector_.selectedJets().size() == 2    &&
		 pjSelector_.met().pt() > 100.             &&
		 pjSelector_.getDeltaPhiMetPhoton1() > 0.5 &&
		 pjSelector_.getDeltaPhiMetPhoton1() < 2.5 &&
		 pjSelector_.getDeltaPhiJ1Photon() > 0.5   &&
		 pjSelector_.getDeltaPhiJ1Photon() < 0.5   &&
		 pjSelector_.getDeltaPhiMetJet1() > 0.5    &&
		 pjSelector_.getDeltaPhiMetJet1() < 2.5    &&
		 pjSelector_.getDeltaPhiMetJet2() > 0.5    &&
		 pjSelector_.getDeltaPhiMetJet2() < 2.5    &&
		 pjSelector_.getDeltaPhiJ1J2() > 0.5       &&
		 pjSelector_.getDeltaPhiJ1J2() < 2.5       ){

	      std::cout << "VS!!!"
			<< " - lumis: "          << event.eventAuxiliary().luminosityBlock()
			<< " , run: "            << event.eventAuxiliary().run()
			<< " , event#: "         << event.eventAuxiliary().event()
			<< "-> photon Pt: "      << pjSelector_.photon().pt()
			<< " , corr photon Pt: " << pjSelector_.correctedphotonpt()
			<< " , photon eta: "     << pjSelector_.photon().eta()
			<< " , # of jets: "      << pjSelector_.selectedJets().size()
			<< " , 1st jet Pt: "     << pjSelector_.jet().pt()
			<< " , 1st jet eta: "    << pjSelector_.jet().eta()
			<< " , 2nd jet Pt: "     << pjSelector_.jet2().pt()
			<< " , 2nd jet eta: "    << pjSelector_.jet2().eta()
			<< " , ht (HLT): "       << pjSelector_.htHLT()
			<< " , MET: "            << pjSelector_.met().pt()
			<< std::endl;

	    }
	}
	*/

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
	
	/*
        // Cross-check with Knut
        if ( pjSelector_.isPhotonValid() && 
	     pjSelector_.isJetValid()    && 
	     pjSelector_.isJet2Valid()   && 
	     pjSelector_.isMetValid()    ){

	  const pat::MET & met = pjSelector_.met();

	  //	  if( met.pt() < 100. ){
	    const pat::Photon & photon = pjSelector_.photon();


//	    edm::Handle<double> rhoH;
//	    event.getByLabel(srcRho_, rhoH);

//	      # runNumber : luminosityBlockNumber : eventNumber
//	      # met =
//	      # ht =
//	      # weight = (only for MC of course)
//	      # 1.photonPt =
//	      # 1.photonPtOfMatchedJet =
//	      # nJets =
//	      # 1.jetPt =
//	      # 1.jetEta =  

	    std::cout << "VS!!!"
		      << " # "                          << event.eventAuxiliary().run()
		      << " : "                          << event.eventAuxiliary().luminosityBlock()
		      << " : "                          << event.eventAuxiliary().event()
//		      << " # rho = "                    << *rhoH
		      << " # met = "                    << met.pt()
		      << " # ht = "                     << pjSelector_.htHLT()
		      << " # weight = "                 << weight
		      << " # 1.photonPt =  "            << pjSelector_.photon().pt()
		      << " # 1.photonPtOfMatchedJet = " << pjSelector_.correctedphotonpt()
		      << " # 1.photon chargedIsoCor =  "<< pjSelector_.photon().userFloat("chargedIsoCor")
		      << " # 1.photon photonIsoCor =  " << pjSelector_.photon().userFloat("photonIsoCor")
		      << " # 1.photon neutralIsoCor =  "<< pjSelector_.photon().userFloat("neutralIsoCor")
		      << " # nJets "                    << pjSelector_.selectedJets().size()
		      << " # 1.jetPt = "                << pjSelector_.jet().pt()
		      << " # 1.jetEta = "               << pjSelector_.jet().eta()
		      << " # 1.jetArea = "              << pjSelector_.jet().jetArea()
	      //<< " # 1.jet Uncorr = "           << pjSelector_.jet().correctedJet("Uncorrected")
	      //<< " # 1.jet L1Fast = "           << pjSelector_.jet().correctedJet("L1FastJet") //knut
	      //<< " # 1.jet L2Rel = "            << pjSelector_.jet().correctedJet("L2Relative")
	      //<< " # 1.jet L3Abs = "            << pjSelector_.jet().correctedJet("L3Absolute")
	      //<< " # 1.jet L2L3Res = "          << pjSelector_.jet().correctedJet("L2L3Residual")
		      << " # 2.jetPt = "                << pjSelector_.jet2().pt()
		      << " # 2.jetEta = "               << pjSelector_.jet2().eta()
		      << " # 2.jetArea = "              << pjSelector_.jet2().jetArea()
	      //<< " # 2.jet Uncorr = "           << pjSelector_.jet2().correctedJet("Uncorrected")
	      //<< " # 2.jet L1Fast = "           << pjSelector_.jet2().correctedJet("L1FastJet") //knut
	      //<< " # 2.jet L2Rel = "            << pjSelector_.jet2().correctedJet("L2Relative")
	      //<< " # 2.jet L3Abs = "            << pjSelector_.jet2().correctedJet("L3Absolute")
	      //<< " # 2.jet L2L3Res = "          << pjSelector_.jet2().correctedJet("L2L3Residual")
		      << std::endl
		      << std::endl;
	    //}
        }//end Knut checks	        
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

void SelectionAnalyzer :: endJob() {
    edm::LogError("SelectionAnalyzer");
    if ( loggingVerbosity_ > 1 ){
        std::cout << "Selected Events: " << evtCounter_ << std::endl;
        std::cout << "Selected Events Met100: " << evtCounter100_ << std::endl;
        std::cout << "Selected Events Met200: " << evtCounter200_ << std::endl;
        std::cout << "Selected Events Met350: " << evtCounter350_ << std::endl;
        std::cout << "Bins Met>100 (low edge): ";
    }
    printBinsMETAbove100(pjSelectorPresel_, "PreselCut_");
    if ( loggingVerbosity_ > 1 )
        std::cout << "Selected Events Met>100 (binned-Presel): ";
    printBinnedMETAbove100(pjSelectorPresel_, "PreselCut_");
    if ( loggingVerbosity_ > 1 )
        std::cout << "Selected Events Met>100 (binned-SYST UP/DOWN): ";
    printBinnedMETAbove100(pjSelectorPresel_, "PreselCut_SYSTUP_");
    if ( loggingVerbosity_ > 1 )
        std::cout << "Selected Events Met>100 (binned-STAT UP/DOWN): ";
    printBinnedMETAbove100STAT(pjSelectorPresel_, "PreselCut_");
    for (int i = 0; i < (int) signalScanPoints_.size(); ++i) {
        std::string app = signalScanPoints_[i];
        if ( loggingVerbosity_ > 1 ) {
            std::cout << "***SIGNALSCANPOINT_" << app << std::endl;
            std::cout << "Bins Met>100 (low edge): ";
        }
        printBinsMETAbove100(pjSelectorPresel_, "PreselCut_", app);
        if ( loggingVerbosity_ > 1 )
            std::cout << "Selected Events Met>100 (binned-Presel): ";
        printBinnedMETAbove100(pjSelectorPresel_, "PreselCut_", app);
        if ( loggingVerbosity_ > 1 )
            std::cout << "Selected Events Met>100 (binned-SYST UP/DOWN): ";
        printBinnedMETAbove100(pjSelectorPresel_, "PreselCut_SYSTUP_", app);
        if ( loggingVerbosity_ > 1 )
            std::cout << "Selected Events Met>100 (binned-STAT UP/DOWN): ";
        printBinnedMETAbove100STAT(pjSelectorPresel_, "PreselCut_", app);
        if ( loggingVerbosity_ > 1 )
            std::cout << "===ENDSIGNALSCANPOINT_" << app << std::endl;
    }

    pjSelector_.print(std::cout);
    if ( loggingVerbosity_ > 1 ) {
        std::cout << "Selected Events (Weighted): " << evtCounterWeighted_ << std::endl;
        std::cout << "Selected Events (Weighted Error Syst): " << evtCounterWeightedError_ - evtCounterWeighted_ << std::endl;
        std::cout << "Selected Events (Weighted Error Stat): " << sqrt(evtCounterWeighted_) << std::endl;
        std::cout << "Selected Events (Presel): " << evtCounterPresel_ << std::endl;
        std::cout << "Selected Events (Presel,Weighted): " << evtCounterPreselWeighted_ << std::endl;
        std::cout << "Selected Events (Presel,Weighted Error Syst): " << evtCounterPreselWeightedError_ - evtCounterPreselWeighted_ << std::endl;
        std::cout << "Selected Events (Presel,Weighted Error Stat): " << sqrt(evtCounterPreselWeighted_) << std::endl;
    }
    pjSelectorPresel_.print(std::cout);

    std::cout << "SELECTED HIGH MET EVENTS:" << std::endl;
    for (int i = 0; i < (int) highMetEvents_.size(); ++i) {
        std::cout << highMetEvents_[i] << std::endl;
    }
    if (punchthroughtest_) {
        ofstream outstream;

        outstream.open("punchthrough.txt");
        outstream << "\\documentclass{article} " << std::endl;
        outstream << "\\begin{document}  " << std::endl;
        outstream << "\\begin{tabular}{ | l | l | l | l | l | }  " << std::endl;
        outstream << "Event & No. of RPC-Hits & CaloJetPT & PfMET & CaloMET  \\\\ \\hline" << std::endl;
        for (int i = 0; i < (int) punchthroughEvents_.size(); ++i) {
            outstream << punchthroughEvents_[i] << std::endl;
        }
        outstream << "\\end{tabular} " << std::endl;
        outstream << "\\end{document} " << std::endl;
        outstream.close();
    }
}

void SelectionAnalyzer :: initializeHistosSignalScan(TFileDirectory * fs, std::string prefix, std::string parPoint) {
    if (drawPlots_ && parPoint != "") {
        hists_[(prefix + "metPt_" + parPoint).c_str()] = fs->make<TH1F> ((prefix + "metPt_" + parPoint).c_str(), "pt", 100, 0., 1000.);
        hists_[(prefix + "metPt_" + parPoint).c_str()]->Sumw2();
    }
}

void SelectionAnalyzer :: initializeHistos(TFileDirectory& fs, std::string prefix) {
    if (drawPlots_) {
        // initialize histos for basic object histograms
        hists_[(prefix + "photonPt").c_str()] = fs.make<TH1F> ((prefix + "photonPt").c_str(), "pt", 150, 5., 1505.);
        hists_[(prefix + "photonPt").c_str()]->Sumw2();
        hists_[(prefix + "photonTrigPt").c_str()] = fs.make<TH1F> ((prefix + "photonTrigPt").c_str(), "pt", 300, 5., 1505.);
        hists_[(prefix + "photonTrigPt").c_str()]->Sumw2();

        hists_[(prefix + "photonPtLowMet").c_str()] = fs.make<TH1F> ((prefix + "photonPtLowMet").c_str(), "pt", 150, 5., 1505.);
        hists_[(prefix + "photonPtLowMet").c_str()]->Sumw2();

        hists_[(prefix + "photonPtLowMet1").c_str()] = fs.make<TH1F> ((prefix + "photonPtLowMet1").c_str(), "pt", 150, 5., 1505.);
        hists_[(prefix + "photonPtLowMet1").c_str()]->Sumw2();

        hists_[(prefix + "photonPtLowMet2").c_str()] = fs.make<TH1F> ((prefix + "photonPtLowMet2").c_str(), "pt", 150, 5., 1505.);
        hists_[(prefix + "photonPtLowMet2").c_str()]->Sumw2();

        hists2D_[(prefix + "photonPtVsHthltLowMet").c_str()] = fs.make<TH2F> ((prefix + "photonPtVsHthltLowMet").c_str(), "photonPtVsHthltLowMet", 150, 5., 1505., 230, 200., 2500.);
        hists2D_[(prefix + "photonPtVsHthltLowMet").c_str()]->Sumw2();

        hists2D_[(prefix + "photonPtVsHthltLowMet1").c_str()] = fs.make<TH2F> ((prefix + "photonPtVsHthltLowMet1").c_str(), "photonPtVsHthltLowMet", 150, 5., 1505., 230, 200., 2500.);
        hists2D_[(prefix + "photonPtVsHthltLowMet1").c_str()]->Sumw2();

        hists2D_[(prefix + "photonPtVsHthltLowMet2").c_str()] = fs.make<TH2F> ((prefix + "photonPtVsHthltLowMet2").c_str(), "photonPtVsHthltLowMet", 150, 5., 1505., 230, 200., 2500.);
        hists2D_[(prefix + "photonPtVsHthltLowMet2").c_str()]->Sumw2();

        hists2D_[(prefix + "photonPtVsHthltLowMet2j").c_str()] = fs.make<TH2F> ((prefix + "photonPtVsHthltLowMet2j").c_str(), "photonPtVsHthltLowMet2j", 150, 5., 1505., 230, 200., 2500.);
        hists2D_[(prefix + "photonPtVsHthltLowMet2j").c_str()]->Sumw2();

        hists2D_[(prefix + "photonPtVsHtjLowMet").c_str()] = fs.make<TH2F> ((prefix + "photonPtVsHtjLowMet").c_str(), "photonPtVsHtjLowMet", 150, 5., 1505., 250, 0., 2500.);
        hists2D_[(prefix + "photonPtVsHtjLowMet").c_str()]->Sumw2();

        hists2D_[(prefix + "photonPtVsHtjLowMet1").c_str()] = fs.make<TH2F> ((prefix + "photonPtVsHtjLowMet1").c_str(), "photonPtVsHtjLowMet", 150, 5., 1505., 250, 0., 2500.);
        hists2D_[(prefix + "photonPtVsHtjLowMet1").c_str()]->Sumw2();

        hists2D_[(prefix + "photonPtVsHtjLowMet2").c_str()] = fs.make<TH2F> ((prefix + "photonPtVsHtjLowMet2").c_str(), "photonPtVsHtjLowMet", 150, 5., 1505., 250, 0., 2500.);
        hists2D_[(prefix + "photonPtVsHtjLowMet2").c_str()]->Sumw2();


	/* -- MC Photon Studies -- */
        hists_[(prefix + "photonPdgId").c_str()] = fs.make<TH1F> ((prefix + "photonPdgId").c_str(), "pdg id", 50, 0., 50.);
        hists_[(prefix + "photonPdgId").c_str()]->Sumw2();

        hists_[(prefix + "photonStatus").c_str()] = fs.make<TH1F> ((prefix + "photonStatus").c_str(), "status", 10, 0., 10.);
        hists_[(prefix + "photonStatus").c_str()]->Sumw2();

        hists_[(prefix + "photonPtGen").c_str()] = fs.make<TH1F> ((prefix + "photonPtGen").c_str(), "pt gen", 150, 5., 1505.);
        hists_[(prefix + "photonPtGen").c_str()]->Sumw2();

        hists_[(prefix + "photonIdGen").c_str()] = fs.make<TH1F> ((prefix + "photonIdGen").c_str(), "id gen", 50, 0., 50.);
        hists_[(prefix + "photonIdGen").c_str()]->Sumw2();

        hists2D_[(prefix + "photonPtGenVsRec").c_str()] = fs.make<TH2F> ((prefix + "photonPtGenVsRec").c_str(), "photonPtGenVsRec", 150, 5., 1505., 150, 5., 1505.);
        hists2D_[(prefix + "photonPtGenVsRec").c_str()]->Sumw2();

        hists2D_[(prefix + "photonPtCheck").c_str()] = fs.make<TH2F> ((prefix + "photonPtCheck").c_str(), "photonPtCheck", 150, 5., 1505., 150, 5., 1505.);
        hists2D_[(prefix + "photonPtCheck").c_str()]->Sumw2();
	/* -- MC Photon Studies -- */

        hists_[(prefix + "photonEt").c_str()] = fs.make<TH1F> ((prefix + "photonEt").c_str(), "et", 150, 5., 1505.);
        hists_[(prefix + "photonEt").c_str()]->Sumw2();

	//electron veto variables
	hists_[(prefix + "photonElectronSafe").c_str()] = fs.make<TH1F> ((prefix + "photonElectronSafe").c_str(), "photonElectronSafe", 2, 0., 2.);
	hists_[(prefix + "photonElectronSafe").c_str()]->Sumw2();
	hists_[(prefix + "photonPixelSeed").c_str()] = fs.make<TH1F> ((prefix + "photonPixelSeed").c_str(), "photonPixelSeed", 2, 0., 2.);
	hists_[(prefix + "photonPixelSeed").c_str()]->Sumw2();

        hists_[(prefix + "photonEta").c_str()] = fs.make<TH1F> ((prefix + "photonEta").c_str(), "eta", 50, -3., 3.);
        hists_[(prefix + "photonEta").c_str()]->Sumw2();
        hists_[(prefix + "photonPhi").c_str()] = fs.make<TH1F> ((prefix + "photonPhi").c_str(), "phi", 50, -5., 5.);
        hists_[(prefix + "photonPhi").c_str()]->Sumw2();
        hists_[(prefix + "photon2Pt").c_str()] = fs.make<TH1F> ((prefix + "photon2Pt").c_str(), "pt", 100, 5., 1005.);
        hists_[(prefix + "photon2Pt").c_str()]->Sumw2();
        hists_[(prefix + "photon2Eta").c_str()] = fs.make<TH1F> ((prefix + "photon2Eta").c_str(), "eta", 50, -3., 3.);
        hists_[(prefix + "photon2Eta").c_str()]->Sumw2();
        hists_[(prefix + "photon2Phi").c_str()] = fs.make<TH1F> ((prefix + "photon2Phi").c_str(), "phi", 50, -5., 5.);
        hists_[(prefix + "photon2Phi").c_str()]->Sumw2();
        hists_[(prefix + "hltphotonjetpt").c_str()] = fs.make<TH1F> ((prefix + "hltphotonjetpt").c_str(), "pt", 150, 5., 1505.);

        hists_[(prefix + "photonjetEmfInclE").c_str()] = fs.make<TH1F> ((prefix + "photonjetEmfInclE").c_str(), "emf", 20, 0., 1.);
        hists_[(prefix + "photonjetEmfInclE").c_str()]->Sumw2();
        hists_[(prefix + "photonjetEmf").c_str()] = fs.make<TH1F> ((prefix + "photonjetEmf").c_str(), "emf", 20, 0., 1.);
        hists_[(prefix + "photonjetEmf").c_str()]->Sumw2();
        hists_[(prefix + "photonjetResp").c_str()] = fs.make<TH1F> ((prefix + "photonjetResp").c_str(), "resp", 100, 0., 3.);
        hists_[(prefix + "photonjetResp").c_str()]->Sumw2();

        hists_[(prefix + "photonjetRespUncorr").c_str()] = fs.make<TH1F> ((prefix + "photonjetRespUncorr").c_str(), "resp", 100, 0., 3.);
        hists_[(prefix + "photonjetRespUncorr").c_str()]->Sumw2();

        hists_[(prefix + "photonjetRespL1").c_str()] = fs.make<TH1F> ((prefix + "photonjetRespL1").c_str(), "resp", 100, 0., 3.);
        hists_[(prefix + "photonjetRespL1").c_str()]->Sumw2();

        hists_[(prefix + "photonJetEtRel").c_str()] = fs.make<TH1F> ((prefix + "photonJetEtRel").c_str(), "etrel", 100, 0., 3.);
        hists_[(prefix + "photonJetEtRel").c_str()]->Sumw2();

        hists_[(prefix + "jetPt").c_str()] = fs.make<TH1F> ((prefix + "jetPt").c_str(), "pt", 100, 0., 1000.);
        hists_[(prefix + "jetPt").c_str()]->Sumw2();
        hists_[(prefix + "jetEta").c_str()] = fs.make<TH1F> ((prefix + "jetEta").c_str(), "eta", 50, -3., 3.);
        hists_[(prefix + "jetEta").c_str()]->Sumw2();
        hists_[(prefix + "jetPhi").c_str()] = fs.make<TH1F> ((prefix + "jetPhi").c_str(), "phi", 50, -5., 5.);
        hists_[(prefix + "jetPhi").c_str()]->Sumw2();
        hists_[(prefix + "jet2Pt").c_str()] = fs.make<TH1F> ((prefix + "jet2Pt").c_str(), "pt", 100, 0., 1000.);
        hists_[(prefix + "jet2Pt").c_str()]->Sumw2();
        hists_[(prefix + "jet2Eta").c_str()] = fs.make<TH1F> ((prefix + "jet2Eta").c_str(), "jet2Eta", 50, -3., 3.);
        hists_[(prefix + "jet2Eta").c_str()]->Sumw2();
        hists_[(prefix + "jet2Phi").c_str()] = fs.make<TH1F> ((prefix + "jet2Phi").c_str(), "phi", 50, -5., 5.);
        hists_[(prefix + "jet2Phi").c_str()]->Sumw2();
        hists_[(prefix + "jet3Pt").c_str()] = fs.make<TH1F> ((prefix + "jet3Pt").c_str(), "pt", 100, 0., 1000.);
        hists_[(prefix + "jet3Pt").c_str()]->Sumw2();
        hists_[(prefix + "jet3Eta").c_str()] = fs.make<TH1F> ((prefix + "jet3Eta").c_str(), "eta", 50, -3., 3.);
        hists_[(prefix + "jet3Eta").c_str()]->Sumw2();
        hists_[(prefix + "jet3Phi").c_str()] = fs.make<TH1F> ((prefix + "jet3Phi").c_str(), "phi", 50, -5., 5.);
        hists_[(prefix + "jet3Phi").c_str()]->Sumw2();
        hists_[(prefix + "jet4Pt").c_str()] = fs.make<TH1F> ((prefix + "jet4Pt").c_str(), "pt", 100, 0., 1000.);
        hists_[(prefix + "jet4Pt").c_str()]->Sumw2();
        hists_[(prefix + "jet4Eta").c_str()] = fs.make<TH1F> ((prefix + "jet4Eta").c_str(), "eta", 50, -3., 3.);
        hists_[(prefix + "jet4Eta").c_str()]->Sumw2();
        hists_[(prefix + "jet4Phi").c_str()] = fs.make<TH1F> ((prefix + "jet4Phi").c_str(), "phi", 50, -5., 5.);
        hists_[(prefix + "jet4Phi").c_str()]->Sumw2();
        hists_[(prefix + "bjetPt").c_str()] = fs.make<TH1F> ((prefix + "bjetPt").c_str(), "pt", 100, 0., 1000.);
        hists_[(prefix + "bjetPt").c_str()]->Sumw2();
        hists_[(prefix + "bjetEta").c_str()] = fs.make<TH1F> ((prefix + "bjetEta").c_str(), "eta", 50, -3., 3.);
        hists_[(prefix + "bjetEta").c_str()]->Sumw2();
        hists_[(prefix + "bjetPhi").c_str()] = fs.make<TH1F> ((prefix + "bjetPhi").c_str(), "phi", 50, -5., 5.);
        hists_[(prefix + "bjetPhi").c_str()]->Sumw2();
        hists_[(prefix + "bjet2Pt").c_str()] = fs.make<TH1F> ((prefix + "bjet2Pt").c_str(), "pt", 100, 0., 1000.);
        hists_[(prefix + "bjet2Pt").c_str()]->Sumw2();
        hists_[(prefix + "bjet2Eta").c_str()] = fs.make<TH1F> ((prefix + "bjet2Eta").c_str(), "eta", 50, -3., 3.);
        hists_[(prefix + "bjet2Eta").c_str()]->Sumw2();
        hists_[(prefix + "bjet2Phi").c_str()] = fs.make<TH1F> ((prefix + "bjet2Phi").c_str(), "phi", 50, -5., 5.);
        hists_[(prefix + "bjet2Phi").c_str()]->Sumw2();
        hists_[(prefix + "metPt").c_str()] = fs.make<TH1F> ((prefix + "metPt").c_str(), "pt", 100, 0., 1000.);
        hists_[(prefix + "metPt").c_str()]->Sumw2();

        hists_[(prefix + "metPtRaw").c_str()] = fs.make<TH1F> ((prefix + "metPtRaw").c_str(), "pt", 100, 0., 800.);
        hists_[(prefix + "metPtRaw").c_str()]->Sumw2();
        hists_[(prefix + "metPtT1").c_str()] = fs.make<TH1F> ((prefix + "metPtT1").c_str(), "pt", 100, 0., 1000.);
        hists_[(prefix + "metPtT1").c_str()]->Sumw2();
        hists_[(prefix + "metPtT2").c_str()] = fs.make<TH1F> ((prefix + "metPtT2").c_str(), "pt", 100, 0., 1000.);
        hists_[(prefix + "metPtT2").c_str()]->Sumw2();

        hists_[(prefix + "metPt2").c_str()] = fs.make<TH1F> ((prefix + "metPt2").c_str(), "pt", 100, 0., 1000.);
        hists_[(prefix + "metPt2").c_str()]->Sumw2();
        hists_[(prefix + "genMet").c_str()] = fs.make<TH1F> ((prefix + "genMet").c_str(), "pt", 100, 0., 1000.);
        hists_[(prefix + "genMet").c_str()]->Sumw2();
        hists_[(prefix + "metPhi").c_str()] = fs.make<TH1F> ((prefix + "metPhi").c_str(), "phi", 50, -5., 5.);
        hists_[(prefix + "metPhi").c_str()]->Sumw2();
        hists_[(prefix + "metSumEt").c_str()] = fs.make<TH1F> ((prefix + "metSumEt").c_str(), "sumet", 200, 0., 2000.);
        hists_[(prefix + "metSumEt").c_str()]->Sumw2();
        hists_[(prefix + "mt").c_str()] = fs.make<TH1F> ((prefix + "mt").c_str(), "mt", 150, -0., 1000.);
        hists_[(prefix + "mt").c_str()]->Sumw2();
        hists_[(prefix + "noJets").c_str()] = fs.make<TH1F> ((prefix + "noJets").c_str(), "noJets", 20, 0., 20.);
        hists_[(prefix + "noJets").c_str()]->Sumw2();
        hists_[(prefix + "noPhotons").c_str()] = fs.make<TH1F> ((prefix + "noPhotons").c_str(), "noPhotons", 20, 0., 20.);
        hists_[(prefix + "noPhotons").c_str()]->Sumw2();
        hists_[(prefix + "noPhotonsGenMatch").c_str()] = fs.make<TH1F> ((prefix + "noPhotonsGenMatc").c_str(), "noPhotonsGenMatch", 20, 0., 20.);
        hists_[(prefix + "noPhotonsGenMatch").c_str()]->Sumw2();
        hists_[(prefix + "noBJets").c_str()] = fs.make<TH1F> ((prefix + "noBJets").c_str(), "noBJets", 20, 0., 20.);
        hists_[(prefix + "noBJets").c_str()]->Sumw2();
        ///initialize histos for additional cut variables
        hists_[(prefix + "ht").c_str()] = fs.make<TH1F> ((prefix + "ht").c_str(), "ht", 250, 50., 2500.);
        hists_[(prefix + "ht").c_str()]->Sumw2();
        hists_[(prefix + "hthlt").c_str()] = fs.make<TH1F> ((prefix + "hthlt").c_str(), "hthlt", 230, 200., 2500.);
        hists_[(prefix + "hthlt").c_str()]->Sumw2();

        hists_[(prefix + "htj").c_str()] = fs.make<TH1F> ((prefix + "htj").c_str(), "htj", 150, -0., 1500.);
        hists_[(prefix + "htj").c_str()]->Sumw2();
        hists_[(prefix + "mht").c_str()] = fs.make<TH1F> ((prefix + "mht").c_str(), "mht", 100, -0., 800.);
        hists_[(prefix + "mht").c_str()]->Sumw2();
        hists_[(prefix + "mhtj").c_str()] = fs.make<TH1F> ((prefix + "mhtj").c_str(), "mhtj", 100, -0., 800.);
        hists_[(prefix + "mhtj").c_str()]->Sumw2();
        hists_[(prefix + "deltaPhiJ1J2").c_str()] = fs.make<TH1F> ((prefix + "deltaPhiJ1J2").c_str(), "deltaPhiJ1J2", 32, 0., 3.20);
        hists_[(prefix + "deltaPhiJ1J2").c_str()]->Sumw2();
        hists_[(prefix + "deltaPhiJ1Photon").c_str()] = fs.make<TH1F> ((prefix + "deltaPhiJ1Photon").c_str(), "deltaPhiJ1Photon", 32, 0., 3.20);
        hists_[(prefix + "deltaPhiJ1Photon").c_str()]->Sumw2();
        hists_[(prefix + "deltaRPhotonJet").c_str()] = fs.make<TH1F> ((prefix + "deltaRPhotonJet").c_str(), "deltaRPhotonJet", 32, 0., 3.20);
        hists_[(prefix + "deltaRPhotonJet").c_str()]->Sumw2();
        hists_[(prefix + "deltaPhiMetJet1").c_str()] = fs.make<TH1F> ((prefix + "deltaPhiMetJet1").c_str(), "deltaPhiMetJet1", 32, 0., 3.20);
        hists_[(prefix + "deltaPhiMetJet1").c_str()]->Sumw2();
        hists_[(prefix + "deltaPhiMetT1Photon").c_str()] = fs.make<TH1F> ((prefix + "deltaPhiMetT1Photon").c_str(), "deltaPhiMetT1Photon", 32, 0., 3.20);
        hists_[(prefix + "deltaPhiMetT1Photon").c_str()]->Sumw2();
        hists_[(prefix + "deltaPhiMetJet2").c_str()] = fs.make<TH1F> ((prefix + "deltaPhiMetJet2").c_str(), "deltaPhiMetJet2", 32, 0., 3.20);
        hists_[(prefix + "deltaPhiMetJet2").c_str()]->Sumw2();
        hists_[(prefix + "deltaPhiMetJet3").c_str()] = fs.make<TH1F> ((prefix + "deltaPhiMetJet3").c_str(), "deltaPhiMetJet3", 32, 0., 3.20);
        hists_[(prefix + "deltaPhiMetJet3").c_str()]->Sumw2();

        hists_[(prefix + "deltaPhiMetPhoton").c_str()] = fs.make<TH1F> ((prefix + "deltaPhiMetPhoton").c_str(), "deltaPhiMetPhoton", 32, 0., 3.20);
        hists_[(prefix + "deltaPhiMetPhoton").c_str()]->Sumw2();

        hists_[(prefix + "deltaRMetPhoton").c_str()] = fs.make<TH1F> ((prefix + "deltaRMetPhoton").c_str(), "deltaRMetPhoton", 32, 0., 3.20);
        hists_[(prefix + "deltaRMetPhoton").c_str()]->Sumw2();

        hists_[(prefix + "Mj12").c_str()] = fs.make<TH1F> ((prefix + "Mj12").c_str(), "Mj12", 150, 0., 1000.);
        hists_[(prefix + "Mj12").c_str()]->Sumw2();
        hists_[(prefix + "Mj23").c_str()] = fs.make<TH1F> ((prefix + "Mj23").c_str(), "Mj23", 150, 0., 1000.);
        hists_[(prefix + "Mj23").c_str()]->Sumw2();
        hists_[(prefix + "Mj13").c_str()] = fs.make<TH1F> ((prefix + "Mj13").c_str(), "Mj13", 150, 0., 1000.);
        hists_[(prefix + "Mj13").c_str()]->Sumw2();

        //initialize histos for photon id plots
        hists_[(prefix + "sigmaietaieta").c_str()] = fs.make<TH1F> ((prefix + "sigmaietaieta").c_str(), "sigmaietaieta", 50, 0., 0.016);
        hists_[(prefix + "sigmaietaieta").c_str()]->Sumw2();

        hists_[(prefix + "sigmaiphiiphi").c_str()] = fs.make<TH1F> ((prefix + "sigmaiphiiphi").c_str(), "sigmaiphiiphi", 50, 0., 0.016);
        hists_[(prefix + "sigmaiphiiphi").c_str()]->Sumw2();

        hists_[(prefix + "trackiso").c_str()] = fs.make<TH1F> ((prefix + "trackiso").c_str(), "trackiso", 50, 0., 50.);
        hists_[(prefix + "trackiso").c_str()]->Sumw2();
        hists_[(prefix + "ecaliso").c_str()] = fs.make<TH1F> ((prefix + "ecaliso").c_str(), "ecaliso", 50, 0., 50.);
        hists_[(prefix + "ecaliso").c_str()]->Sumw2();
        hists_[(prefix + "hcaliso").c_str()] = fs.make<TH1F> ((prefix + "hcaliso").c_str(), "hcaliso", 50, 0., 50.);
        hists_[(prefix + "hcaliso").c_str()]->Sumw2();

        hists_[(prefix + "trackiso03").c_str()] = fs.make<TH1F> ((prefix + "trackiso03").c_str(), "trackiso03", 50, 0., 50.);
        hists_[(prefix + "trackiso03").c_str()]->Sumw2();
        hists_[(prefix + "ecaliso03").c_str()] = fs.make<TH1F> ((prefix + "ecaliso03").c_str(), "ecaliso03", 50, 0., 50.);
        hists_[(prefix + "ecaliso03").c_str()]->Sumw2();
        hists_[(prefix + "hcaliso03").c_str()] = fs.make<TH1F> ((prefix + "hcaliso03").c_str(), "hcaliso03", 50, 0., 50.);
        hists_[(prefix + "hcaliso03").c_str()]->Sumw2();

        hists_[(prefix + "combiso").c_str()] = fs.make<TH1F> ((prefix + "combiso").c_str(), "combiso", 50, 0., 50.);
        hists_[(prefix + "combiso").c_str()]->Sumw2();

        hists_[(prefix + "chargedIso").c_str()] = fs.make<TH1F> ((prefix + "chargedIso").c_str(), "chargedIso", 50, 0., 50.);
        hists_[(prefix + "chargedIso").c_str()]->Sumw2();
        hists_[(prefix + "photonIso").c_str()] = fs.make<TH1F> ((prefix + "photonIso").c_str(), "photonIso", 50, 0., 50.);
        hists_[(prefix + "photonIso").c_str()]->Sumw2();
        hists_[(prefix + "neutralIso").c_str()] = fs.make<TH1F> ((prefix + "neutralIso").c_str(), "neutralIso", 50, 0., 50.);
        hists_[(prefix + "neutralIso").c_str()]->Sumw2();

        hists_[(prefix + "combisoTh").c_str()] = fs.make<TH1F> ((prefix + "combisoTh").c_str(), "combisoTh", 120, -30., 30.);
        hists_[(prefix + "combisoTh").c_str()]->Sumw2();
        hists_[(prefix + "combIsoCorTh").c_str()] = fs.make<TH1F> ((prefix + "combIsoCorTh").c_str(), "combIsoCorTh", 120, -30., 30.);
        hists_[(prefix + "combIsoCorTh").c_str()]->Sumw2();

        hists_[(prefix + "combisoThFO").c_str()] = fs.make<TH1F> ((prefix + "combisoThFO").c_str(), "combisoThFO", 120, -30., 30.);
        hists_[(prefix + "combisoThFO").c_str()]->Sumw2();
        hists_[(prefix + "combIsoCorThFO").c_str()] = fs.make<TH1F> ((prefix + "combIsoCorThFO").c_str(), "combIsoCorThFO", 120, -30., 30.);
        hists_[(prefix + "combIsoCorThFO").c_str()]->Sumw2();

        hists_[(prefix + "r9").c_str()] = fs.make<TH1F> ((prefix + "r9").c_str(), "r9", 100, 0., 2.);
        hists_[(prefix + "r9").c_str()]->Sumw2();

        hists_[(prefix + "hadronicOverEm").c_str()] = fs.make<TH1F> ((prefix + "hadronicOverEm").c_str(), "hadronicOverEm", 50, 0., 1);
        hists_[(prefix + "hadronicOverEm").c_str()]->Sumw2();

        hists_[(prefix + "hadTowOverEm").c_str()] = fs.make<TH1F> ((prefix + "hadTowOverEm").c_str(), "hadTowOverEm", 50, 0., 1);
        hists_[(prefix + "hadTowOverEm").c_str()]->Sumw2();

        hists_[(prefix + "pixelseed").c_str()] = fs.make<TH1F> ((prefix + "pixelseed").c_str(), "pixelseed", 100, 0., 100);
        hists_[(prefix + "pixelseed").c_str()]->Sumw2();

        ///initialize histos for additional histograms
        hists_[(prefix + "noPV").c_str()] = fs.make<TH1F> ((prefix + "noPV").c_str(), "noPV", 40, 0., 40.);
        hists_[(prefix + "noPV").c_str()]->Sumw2();

        hists_[(prefix + "noPVPU").c_str()] = fs.make<TH1F> ((prefix + "noPVPU").c_str(), "noPVPU", 40, 0., 40.);
        hists_[(prefix + "noPVPU").c_str()]->Sumw2();
        hists_[(prefix + "noPVPUWeighted").c_str()] = fs.make<TH1F> ((prefix + "noPVPUWeighted").c_str(), "noPVPUWeighted", 40, 0., 40.);
        hists_[(prefix + "noPVPUWeighted").c_str()]->Sumw2();

        hists_[(prefix + "vetoedJetsElectron").c_str()] = fs.make<TH1F> ((prefix + "vetoedJetsElectron").c_str(), "vetoedJetsElectron", 40, 0., 40.);
        hists_[(prefix + "vetoedJetsElectron").c_str()]->Sumw2();
        hists_[(prefix + "vetoedJetsElectronHLT").c_str()] = fs.make<TH1F> ((prefix + "vetoedJetsElectronHLT").c_str(), "vetoedJetsElectronHLT", 40, 0., 40.);
        hists_[(prefix + "vetoedJetsElectronHLT").c_str()]->Sumw2();
        hists_[(prefix + "vetoedJetsMuon").c_str()] = fs.make<TH1F> ((prefix + "vetoedJetsMuon").c_str(), "vetoedJetsMuon", 40, 0., 40.);
        hists_[(prefix + "vetoedJetsMuon").c_str()]->Sumw2();
        hists_[(prefix + "vetoedJetsMuonHLT").c_str()] = fs.make<TH1F> ((prefix + "vetoedJetsMuonHLT").c_str(), "vetoedJetsMuonHLT", 40, 0., 40.);
        hists_[(prefix + "vetoedJetsMuonHLT").c_str()]->Sumw2();

        ///MET Filter Histos
        hists_[(prefix + "HBHENoiseFilter").c_str()] = fs.make<TH1F> ((prefix + "HBHENoiseFilter").c_str(), "HBHENoiseFilter", 2, 0., 2.);
        hists_[(prefix + "HBHENoiseFilter").c_str()]->Sumw2();
        hists_[(prefix + "HcalLaserFilter").c_str()] = fs.make<TH1F> ((prefix + "HcalLaserFilter").c_str(), "HcalLaserFilter", 2, 0., 2.);
        hists_[(prefix + "HcalLaserFilter").c_str()]->Sumw2();
        hists_[(prefix + "EcaldDCTPFilter").c_str()] = fs.make<TH1F> ((prefix + "EcaldDCTPFilter").c_str(), "EcaldDCTPFilter", 2, 0., 2.);
        hists_[(prefix + "EcaldDCTPFilter").c_str()]->Sumw2();
        hists_[(prefix + "EcaldDCBEFilter").c_str()] = fs.make<TH1F> ((prefix + "EcaldDCBEFilter").c_str(), "EcaldDCBEFilter", 2, 0., 2.);
        hists_[(prefix + "EcaldDCBEFilter").c_str()]->Sumw2();
        hists_[(prefix + "trackingFailureFilter").c_str()] = fs.make<TH1F> ((prefix + "trackingFailureFilter").c_str(), "trackingFailureFilter", 2, 0., 2.);
        hists_[(prefix + "trackingFailureFilter").c_str()]->Sumw2();
        hists_[(prefix + "CSCHaloBeamFilter").c_str()] = fs.make<TH1F> ((prefix + "CSCHaloBeamFilter").c_str(), "CSCHaloBeamFilter", 2, 0., 2.);
        hists_[(prefix + "CSCHaloBeamFilter").c_str()]->Sumw2();
        hists_[(prefix + "eeBadScFilter").c_str()] = fs.make<TH1F> ((prefix + "eeBadScFilter").c_str(), "eeBadScFilter", 2, 0., 2.);
        hists_[(prefix + "eeBadScFilter").c_str()]->Sumw2();


        ///initialize 2D histograms
        hists2D_[(prefix + "mhtVsmet").c_str()] = fs.make<TH2F> ((prefix + "mhtVsmet").c_str(), "mhtVsmet", 100, -0., 1000., 100, -0., 1000.);
        hists2D_[(prefix + "mhtVsmet").c_str()]->Sumw2();
        hists2D_[(prefix + "mhtVsmet2").c_str()] = fs.make<TH2F> ((prefix + "mhtVsmet2").c_str(), "mhtVsmet2", 100, -0., 1000., 100, -0., 1000.);
        hists2D_[(prefix + "mhtVsmet2").c_str()]->Sumw2();
        hists2D_[(prefix + "metVsmet2").c_str()] = fs.make<TH2F> ((prefix + "metVsmet2").c_str(), "metVsmet2", 100, -0., 1000., 100, -0., 1000.);
        hists2D_[(prefix + "metVsmet2").c_str()]->Sumw2();

        hists2D_[(prefix + "metRawVsmetT1").c_str()] = fs.make<TH2F> ((prefix + "metRawVsmetT1").c_str(), "metRawVsmetT1", 100, -0., 1000., 100, -0., 1000.);
        hists2D_[(prefix + "metRawVsmetT1").c_str()]->Sumw2();
        hists2D_[(prefix + "metT1VsmetT2").c_str()] = fs.make<TH2F> ((prefix + "metT1VsmetT2").c_str(), "metT1VsmetT2", 100, -0., 1000., 100, -0., 1000.);
        hists2D_[(prefix + "metT1VsmetT2").c_str()]->Sumw2();

        hists2D_[(prefix + "noPVVsPhotonPt").c_str()] = fs.make<TH2F> ((prefix + "noPVVsPhotonPt").c_str(), "noPVVsPhotonPt", 25, -0., 25., 100, 5., 1005.);
        hists2D_[(prefix + "noPVVsPhotonPt").c_str()]->Sumw2();

        hists2D_[(prefix + "noJetsVsPhotonPt").c_str()] = fs.make<TH2F> ((prefix + "noJetsVsPhotonPt").c_str(), "noJetsVsPhotonPt", 15, 0., 15., 100, 5., 1005.);
        hists2D_[(prefix + "noJetsVsPhotonPt").c_str()]->Sumw2();

        hists2D_[(prefix + "noJetsVsPhotonPtLowMet").c_str()] = fs.make<TH2F> ((prefix + "noJetsVsPhotonPtLowMet").c_str(), "noJetsVsPhotonPt", 15, 0., 15., 100, 5., 1005.);
        hists2D_[(prefix + "noJetsVsPhotonPtLowMet").c_str()]->Sumw2();

        hists2D_[(prefix + "metVsPhotonPt").c_str()] = fs.make<TH2F> ((prefix + "metVsPhotonPt").c_str(), "metVsPhotonPt", 100, -0., 1000., 150, 5., 1505.);
        hists2D_[(prefix + "metVsPhotonPt").c_str()]->Sumw2();
        hists2D_[(prefix + "metVsnoJet").c_str()] = fs.make<TH2F> ((prefix + "metVsnoJet").c_str(), "metVsnoJet", 100, -0., 1000., 20, 0., 20.);
        hists2D_[(prefix + "metVsnoJet").c_str()]->Sumw2();
        hists2D_[(prefix + "metVsPhotonEt").c_str()] = fs.make<TH2F> ((prefix + "metVsPhotonEt").c_str(), "metVsPhotonEt", 100, -0., 1000., 100, 5., 1005.);

        hists2D_[(prefix + "metVsPhotonEt").c_str()]->Sumw2();

        hists2D_[(prefix + "metVsR9").c_str()] = fs.make<TH2F> ((prefix + "metVsR9").c_str(), "metVsR9", 100, -0., 1000., 200, -0., 10);

        hists2D_[(prefix + "metVsR9").c_str()]->Sumw2();

        hists2D_[(prefix + "metVsDeltaRMetPhoton").c_str()] = fs.make<TH2F> ((prefix + "metVsDeltaRMetPhoton").c_str(), "metVsDeltaRMetPhoton", 100, -0., 1000., 100, -0., 3.14);

        hists2D_[(prefix + "metVsDeltaRMetPhoton").c_str()]->Sumw2();

        hists2D_[(prefix + "metVsDeltaPhiMetPhoton").c_str()] = fs.make<TH2F> ((prefix + "metVsDeltaPhiMetPhoton").c_str(), "metVsDeltaRMetPhoton", 100, -0., 1000., 100, -0., 3.14);

        hists2D_[(prefix + "metVsDeltaPhiMetPhoton").c_str()]->Sumw2();

        hists2D_[(prefix + "mhtVsPhotonPt").c_str()] = fs.make<TH2F> ((prefix + "mhtVsPhotonPt").c_str(), "mhtVsPhotonPt", 100, -0., 1000., 150, 5., 1505.);
        hists2D_[(prefix + "mhtVsPhotonPt").c_str()]->Sumw2();
        hists2D_[(prefix + "metVsHT").c_str()] = fs.make<TH2F> ((prefix + "metVsHT").c_str(), "metVsHT", 100, -0., 1000., 150, -0., 1500.);
        hists2D_[(prefix + "metVsHT").c_str()]->Sumw2();
        hists2D_[(prefix + "mhtVsHT").c_str()] = fs.make<TH2F> ((prefix + "mhtVsHT").c_str(), "mhtVsHT", 100, -0., 1000., 150, -0., 1500.);
        hists2D_[(prefix + "mhtVsHT").c_str()]->Sumw2();

        hists2D_[(prefix + "deltaRPhotonJetVsEtrel").c_str()] = fs.make<TH2F> ((prefix + "deltaRPhotonJetVsEtrel").c_str(), "deltaRPhotonJetVsEtrel", 100, -0., 3.14, 100, -0., 3.);
        hists2D_[(prefix + "deltaRPhotonJetVsEtrel").c_str()]->Sumw2();
        hists2D_[(prefix + "deltaRPhotonJetVsEtrelUncorr").c_str()] = fs.make<TH2F> ((prefix + "deltaRPhotonJetVsEtrelUncorr").c_str(), "deltaRPhotonJetVsEtrelUncorr", 100, -0., 3.14, 100, -0., 3.);
        hists2D_[(prefix + "deltaRPhotonJetVsEtrelUncorr").c_str()]->Sumw2();
        hists2D_[(prefix + "deltaRPhotonJetVsEtrelGen").c_str()] = fs.make<TH2F> ((prefix + "deltaRPhotonJetVsEtrelGen").c_str(), "deltaRPhotonJetVsEtrelGen", 100, -0., 3.14, 100, -0., 3.);
        hists2D_[(prefix + "deltaRPhotonJetVsEtrelGen").c_str()]->Sumw2();

        hists2D_[(prefix + "combIsoVsPhotonPt").c_str()] = fs.make<TH2F> ((prefix + "combIsoVsPhotonPt").c_str(), "combIsoVsPhotonPt", 100, -0., 100., 150, 5., 1505.);
        hists2D_[(prefix + "combIsoVsPhotonPt").c_str()]->Sumw2();

        hists2D_[(prefix + "combIsoOldVsNew").c_str()] = fs.make<TH2F> ((prefix + "combIsoOldVsNew").c_str(), "combIsoOldVsNew", 120, -30., 30., 120, -30., 30.);
        hists2D_[(prefix + "combIsoOldVsNew").c_str()]->Sumw2();

        hists2D_[(prefix + "combIsoFOOldVsNew").c_str()] = fs.make<TH2F> ((prefix + "combIsoFOOldVsNew").c_str(), "combIsoFOOldVsNew", 120, -30., 30., 120, -30., 30.);
        hists2D_[(prefix + "combIsoFOOldVsNew").c_str()]->Sumw2();


	hists2D_[(prefix + "hadronicVshadTowOverEm").c_str()] = fs.make<TH2F> ((prefix + "hadronicVshadTowOverEm").c_str(), "hadronicVshadTowOverEm", 100, 0., 1., 100, 0., 1.);
	hists2D_[(prefix + "hadronicVshadTowOverEm").c_str()]->Sumw2();
 
	//Iso studies
        hists2D_[(prefix + "metVschargedIso").c_str()] = fs.make<TH2F> ((prefix + "metVschargedIso").c_str(), "metVschargedIso", 100, 0., 1000., 50, 0., 25.);
        hists2D_[(prefix + "metVschargedIso").c_str()]->Sumw2();
        hists2D_[(prefix + "ptVschargedIso").c_str()] = fs.make<TH2F> ((prefix + "ptVschargedIso").c_str(), "ptVschargedIso", 100, 0., 1000., 50, 0., 25.);
        hists2D_[(prefix + "ptVschargedIso").c_str()]->Sumw2();

        hists2D_[(prefix + "metVsneutralIso").c_str()] = fs.make<TH2F> ((prefix + "metVsneutralIso").c_str(), "metVsneutralIso", 100, 0., 1000., 50, 0., 25.);
        hists2D_[(prefix + "metVsneutralIso").c_str()]->Sumw2();
        hists2D_[(prefix + "ptVsneutralIso").c_str()] = fs.make<TH2F> ((prefix + "ptVsneutralIso").c_str(), "ptVsneutralIso", 100, 0., 1000., 50, 0., 25.);
        hists2D_[(prefix + "ptVsneutralIso").c_str()]->Sumw2();

        hists2D_[(prefix + "metVsphotonIso").c_str()] = fs.make<TH2F> ((prefix + "metVsphotonIso").c_str(), "metVsphotonIso", 100, 0., 1000., 50, 0., 25.);
        hists2D_[(prefix + "metVsphotonIso").c_str()]->Sumw2();
        hists2D_[(prefix + "ptVsphotonIso").c_str()] = fs.make<TH2F> ((prefix + "ptVsphotonIso").c_str(), "ptVsphotonIso", 100, 0., 1000., 50, 0., 25.);
        hists2D_[(prefix + "ptVsphotonIso").c_str()]->Sumw2();


	//Malte new ID
	hists2D_[(prefix + "metVssigmaietaieta").c_str()] = fs.make<TH2F> ((prefix + "metVssigmaietaieta").c_str(), "metVssigmaietaieta", 100, -0., 1000., 50, 0., 0.016);
	hists2D_[(prefix + "metVssigmaietaieta").c_str()]->Sumw2();
 
	hists2D_[(prefix + "metVssigmaiphiiphi").c_str()] = fs.make<TH2F> ((prefix + "metVssigmaiphiiphi").c_str(), "metVssigmaiphiiphi", 100, -0., 1000., 50, 0., 0.016);
	hists2D_[(prefix + "metVssigmaiphiiphi").c_str()]->Sumw2();
 
	hists2D_[(prefix + "metVshadronicOverEm").c_str()] = fs.make<TH2F> ((prefix + "metVshadronicOverEm").c_str(), "metVshadronicOverEm", 100, -0., 1000., 50, 0., 1);
	hists2D_[(prefix + "metVshadronicOverEm").c_str()]->Sumw2();
 
	hists2D_[(prefix + "metVshadTowOverEm").c_str()] = fs.make<TH2F> ((prefix + "metVshadTowOverEm").c_str(), "metVshadTowOverEm", 100, -0., 1000., 50, 0., 1);
	hists2D_[(prefix + "metVshadTowOverEm").c_str()]->Sumw2();

    }
}

void SelectionAnalyzer :: printBinnedMETAbove100STAT(PhotonJetSelector pjSelector, std::string prefix, std::string signalParPoint ) {
    // const pat::MET & met = pjSelector.met(); // unused variable
    std::string histoname = prefix + "metPt";
    if (signalParPoint != "") {
        histoname = histoname + "_" + signalParPoint;
    }
    TH1F * metHisto = (TH1F*) hists_[(histoname).c_str()]->Clone();
    if (metHisto->GetSumw2N() == 0)
        metHisto->Sumw2();
    TH1F * metHistoRebinned = SelectionAnalyzer :: rebinMETHistoForEventYields(metHisto);

    int firstbin = metHistoRebinned->FindBin(100);
    std::cout << "";
    for (int i = firstbin; i <= metHistoRebinned->GetNbinsX() + 1; i++) {
        //cout<<"bin low edge:"<<metHisto->GetBinLowEdge(i)<<endl;
        if (i != firstbin) {
            std::cout << ", ";
        }
        std::cout << metHistoRebinned->GetBinError(i);
    }
    std::cout << "" << std::endl;

}

void SelectionAnalyzer :: printBinnedMETAbove100(PhotonJetSelector pjSelector, std::string prefix, std::string signalParPoint) {
    // const pat::MET & met = pjSelector.met(); // unused variable
    std::string histoname = prefix + "metPt";
    if (signalParPoint != "") {
        histoname = histoname + "_" + signalParPoint;
    }
    TH1F * metHisto = (TH1F*) hists_[(histoname).c_str()]->Clone();
    if (metHisto->GetSumw2N() == 0)
        metHisto->Sumw2();
    TH1F * metHistoRebinned = SelectionAnalyzer :: rebinMETHistoForEventYields(metHisto);

    int firstbin = metHistoRebinned->FindBin(100);
    std::cout << "";
    for (int i = firstbin; i <= metHistoRebinned->GetNbinsX() + 1; i++) {
        //cout<<"bin low edge:"<<metHisto->GetBinLowEdge(i)<<endl;
        if (i != firstbin) {
            std::cout << ", ";
        }
        std::cout << metHistoRebinned->GetBinContent(i);
    }
    std::cout << "" << std::endl;

}

void SelectionAnalyzer :: printBinsMETAbove100(PhotonJetSelector pjSelector, std::string prefix, std::string signalParPoint) {
    // const pat::MET & met = pjSelector.met(); // unused variable
    std::string histoname = prefix + "metPt";
    if (signalParPoint != "") {
        histoname = histoname + "_" + signalParPoint;
    }
    TH1F * metHisto = (TH1F*) hists_[(histoname).c_str()]->Clone();
    TH1F * metHistoRebinned = rebinMETHistoForEventYields(metHisto);

    int firstbin = metHistoRebinned->FindBin(100);
    std::cout << "";
    for (int i = firstbin; i <= metHistoRebinned->GetNbinsX() + 1; i++) {
        //cout<<"bin low edge:"<<metHisto->GetBinLowEdge(i)<<endl;
        if (i != firstbin) {
            std::cout << ", ";
        }
        std::cout << metHistoRebinned->GetBinLowEdge(i);
    }
    std::cout << "" << std::endl;

}


TH1F * SelectionAnalyzer :: rebinMETHistoForEventYields(TH1F * metHisto) {

  std::vector<double> binEdges;
  double oldmaximum = metHisto->GetBinLowEdge(metHisto->GetNbinsX() + 1);

  binEdges.clear();
  binEdges.push_back(0);
  binEdges.push_back(10);
  binEdges.push_back(20);
  binEdges.push_back(30);
  binEdges.push_back(40);
  binEdges.push_back(50);
  binEdges.push_back(60);
  binEdges.push_back(70);
  binEdges.push_back(80);
  binEdges.push_back(90);
  binEdges.push_back(99);
  binEdges.push_back(120);
  binEdges.push_back(159);
  binEdges.push_back(199);
  binEdges.push_back(269);
  binEdges.push_back(349);
  binEdges.push_back(449);
  binEdges.push_back(oldmaximum);

  //binEdges.push_back(110);
  //binEdges.push_back(130);
  //binEdges.push_back(140);
  //binEdges.push_back(149);
  //binEdges.push_back(169);
  //binEdges.push_back(179);
  //binEdges.push_back(299);
  //binEdges.push_back(399);
  //binEdges.push_back(699);

  TH1F *hRebinned = (TH1F*) metHisto->Rebin(binEdges.size() - 1, metHisto->GetName(), &(binEdges.front()));

  return hRebinned;
}


void SelectionAnalyzer :: fillHistosSignalscan(const edm::EventBase& event, double weight, double weightNoPURescale, PhotonJetSelector pjSelector, std::string prefix, int squarkm, int gluinom, int neutrm) {

  if (drawPlots_ && (squarkm != 0 || gluinom != 0)) {
    if (pjSelector.isMetValid()) {

      const pat::MET & met = pjSelector.met();
      std::string app = pjSelector.getSignalScanPointName();
      //std::cout << "Fill met SIGNALSCAN!"<<app << std::endl;
      hists_[(prefix + "metPt_" + app).c_str()]->Fill(met.pt(), weight);
    }
  }

}


void SelectionAnalyzer :: fillHistos( const edm::EventBase& event, double weight, double weightNoPURescale, 
				      PhotonJetSelector pjSelector, std::string prefix, 
				      int squarkm, int gluinom, int neutrm ) {

  if (drawPlots_) {

    // reweighting studies
    if (pjSelector.isPhotonValid()) {
      if( pjSelector.met().pt() <= 100. ) {

	hists_[(prefix + "photonPtLowMet").c_str()]->Fill( pjSelector.correctedphotonpt(), weight );

	hists2D_[(prefix + "photonPtVsHthltLowMet").c_str()] ->Fill( pjSelector.correctedphotonpt(), pjSelector.htHLT(), weight );
	if( pjSelector.selectedJets().size() == 2 )
	  hists2D_[(prefix + "photonPtVsHthltLowMet2j").c_str()] ->Fill( pjSelector.correctedphotonpt(), pjSelector.htHLT(), weight );

	hists2D_[(prefix + "photonPtVsHtjLowMet").c_str()] ->Fill( pjSelector.correctedphotonpt(), pjSelector.htj(), weight );

	if( pjSelector.met().pt() <= 50. ) {
	  hists_[(prefix + "photonPtLowMet1").c_str()]->Fill( pjSelector.correctedphotonpt(), weight );
	  hists2D_[(prefix + "photonPtVsHthltLowMet1").c_str()] ->Fill( pjSelector.correctedphotonpt(), pjSelector.htHLT(), weight );
	  hists2D_[(prefix + "photonPtVsHtjLowMet1").c_str()] ->Fill( pjSelector.correctedphotonpt(), pjSelector.htj(), weight );
	} else {
	  hists_[(prefix + "photonPtLowMet2").c_str()]->Fill( pjSelector.correctedphotonpt(), weight );
	  hists2D_[(prefix + "photonPtVsHthltLowMet2").c_str()] ->Fill( pjSelector.correctedphotonpt(), pjSelector.htHLT(), weight );
	  hists2D_[(prefix + "photonPtVsHtjLowMet2").c_str()] ->Fill( pjSelector.correctedphotonpt(), pjSelector.htj(), weight );	  
	}

      }
    }


    if (pjSelector.isPhotonValid()) {
      const pat::Photon & photon = pjSelector.photon();
            
      hists_[(prefix + "photonPt").c_str()]->Fill(pjSelector.correctedphotonpt(), weight);
      hists_[(prefix + "photonTrigPt").c_str()]->Fill(pjSelector.photonptTRIG(), weight);

      /* -- MC Photon Studies -- */
      hists_[(prefix + "photonPdgId").c_str()]->Fill(photon.pdgId(), weight);

      hists_[(prefix + "photonStatus").c_str()]->Fill(photon.status(), weight);

      if (photon.genPhoton() != 0) {	      
	hists_[(prefix + "photonPtGen").c_str()]->Fill(photon.genPhoton()->pt(), weight);
	hists_[(prefix + "photonIdGen").c_str()]->Fill(photon.genPhoton()->pdgId(), weight);
	hists2D_[(prefix + "photonPtGenVsRec").c_str()]->Fill(photon.genPhoton()->pt(), pjSelector.correctedphotonpt(), weight);
      }

      hists2D_[(prefix + "photonPtCheck").c_str()]->Fill(photon.pt(), pjSelector.correctedphotonpt(), weight);
      /* -- MC Photon Studies -- */

      hists_[(prefix + "photonEt").c_str()]->Fill(photon.et(), weight);

      hists_[(prefix + "photonEta").c_str()]->Fill(photon.eta(), weight);
      hists_[(prefix + "photonPhi").c_str()]->Fill(photon.phi(), weight);

      float phPixelSeed = 0.;
      if( photon.hasPixelSeed() )
	phPixelSeed = 0.;
      else
	phPixelSeed = 1.;
      hists_[(prefix + "photonPixelSeed").c_str()]->Fill(phPixelSeed, weight);
      hists_[(prefix + "photonElectronSafe").c_str()]->Fill( (float) photon.userInt("isPromptElectronSafe"), weight);

      hists_[(prefix + "pixelseed").c_str()] ->Fill(photon.electronPixelSeeds().size(), weight);
      
      hists_[(prefix + "sigmaietaieta").c_str()]->Fill(photon.sigmaIetaIeta(), weight);
      hists_[(prefix + "sigmaiphiiphi").c_str()]->Fill(photon.userFloat("sigmaIphiIphi"), weight);

      hists_[(prefix + "hadronicOverEm").c_str()]->Fill(photon.hadronicOverEm(), weight);
      hists_[(prefix + "hadTowOverEm").c_str()]->Fill(photon.hadTowOverEm(), weight);

      hists2D_[(prefix + "hadronicVshadTowOverEm").c_str()]->Fill(photon.hadronicOverEm(), photon.hadTowOverEm(), weight);

      hists_[(prefix + "r9").c_str()] ->Fill(photon.r9(), weight);

      hists_[(prefix + "trackiso03").c_str()]->Fill(photon.trkSumPtSolidConeDR03(), weight);
      hists_[(prefix + "hcaliso03").c_str()] ->Fill(photon.hcalTowerSumEtConeDR03(), weight);
      hists_[(prefix + "ecaliso03").c_str()] ->Fill(photon.ecalRecHitSumEtConeDR03(), weight);

      hists_[(prefix + "trackiso").c_str()]->Fill(photon.trkSumPtSolidConeDR03()   - 0.011*photon.userFloat("rhoPU"), weight);
      hists_[(prefix + "hcaliso").c_str()] ->Fill(photon.hcalTowerSumEtConeDR03()  - 0.022*photon.userFloat("rhoPU"), weight);
      hists_[(prefix + "ecaliso").c_str()] ->Fill(photon.ecalRecHitSumEtConeDR03() - 0.081*photon.userFloat("rhoPU"), weight);

      double combiso = ( photon.ecalRecHitSumEtConeDR03() - 0.081 * photon.userFloat("rhoPU") ) 
	             + ( photon.hcalTowerSumEtConeDR03()  - 0.022 * photon.userFloat("rhoPU") ) 
	             + ( photon.trkSumPtSolidConeDR03()   - 0.011 * photon.userFloat("rhoPU") );
      hists_[(prefix + "combiso").c_str()]->Fill(combiso, weight);
      hists2D_[(prefix + "combIsoVsPhotonPt").c_str()]->Fill(combiso, photon.pt(), weight);

      hists_[(prefix + "chargedIso").c_str()]->Fill(photon.userFloat("chargedIsoCor"), weight);
      hists_[(prefix + "photonIso").c_str()] ->Fill(photon.userFloat("photonIsoCor"),  weight);
      hists_[(prefix + "neutralIso").c_str()]->Fill(photon.userFloat("neutralIsoCor"), weight);

      double combisoTh    = combiso - 6.;
      double combIsoCorTh = ( photon.userFloat("chargedIsoCor") -  2.6 ) +
	                    ( photon.userFloat("neutralIsoCor") - (3.5+0.04 *photon.pt()) ) +
	                    ( photon.userFloat("photonIsoCor")  - (1.3+0.005*photon.pt()) );

      double combisoThFO = combiso - TMath::Min(30.,0.3*photon.pt());
      double combIsoCorThFO = ( photon.userFloat("chargedIsoCor") - 15. ) +
	                      ( photon.userFloat("neutralIsoCor") - (3.5+0.04 *photon.pt()) ) +
	                      ( photon.userFloat("photonIsoCor")  - (1.3+0.005*photon.pt()) );

      hists_[(prefix + "combisoTh").c_str()]->Fill(combisoTh, weight);
      hists_[(prefix + "combIsoCorTh").c_str()]->Fill(combIsoCorTh, weight);
      hists2D_[(prefix + "combIsoOldVsNew").c_str()]->Fill(combisoTh, combIsoCorTh, weight);

      hists_[(prefix + "combisoThFO").c_str()]->Fill(combisoThFO, weight);
      hists_[(prefix + "combIsoCorThFO").c_str()]->Fill(combIsoCorThFO, weight);
      hists2D_[(prefix + "combIsoFOOldVsNew").c_str()]->Fill(combisoThFO, combIsoCorThFO, weight);
	    
      hists2D_[(prefix + "ptVschargedIso").c_str()]->Fill(pjSelector.correctedphotonpt(), photon.userFloat("chargedIsoCor"), weight);
      hists2D_[(prefix + "ptVsneutralIso").c_str()]->Fill(pjSelector.correctedphotonpt(), photon.userFloat("neutralIsoCor"), weight);
      hists2D_[(prefix + "ptVsphotonIso").c_str()]->Fill(pjSelector.correctedphotonpt(), photon.userFloat("photonIsoCor"), weight);
	    
      if(pjSelector.isMetValid()){
	const pat::MET & metP = pjSelector.met();
	      
	hists2D_[(prefix + "metVschargedIso").c_str()]->Fill(metP.pt(),photon.userFloat("chargedIsoCor"), weight);
	hists2D_[(prefix + "metVsneutralIso").c_str()]->Fill(metP.pt(),photon.userFloat("neutralIsoCor"), weight);
	hists2D_[(prefix + "metVsphotonIso").c_str()]->Fill(metP.pt(),photon.userFloat("photonIsoCor"), weight);
	      
	hists2D_[(prefix + "metVssigmaietaieta").c_str()]->Fill(metP.pt(),photon.sigmaIetaIeta(), weight);
	hists2D_[(prefix + "metVssigmaiphiiphi").c_str()]->Fill(metP.pt(),photon.userFloat("sigmaIphiIphi"), weight);
	hists2D_[(prefix + "metVshadronicOverEm").c_str()]->Fill(metP.pt(),photon.hadronicOverEm(), weight);
	hists2D_[(prefix + "metVshadTowOverEm").c_str()]->Fill(metP.pt(),photon.hadTowOverEm(), weight);
      } 
    }

    if (pjSelector.isPhoton2Valid()) {
      const pat::Photon & photon = pjSelector.photon2();
      hists_[(prefix + "photon2Pt").c_str()]->Fill(photon.pt(), weight);

      hists_[(prefix + "photon2Eta").c_str()]->Fill(photon.eta(), weight);

      hists_[(prefix + "photon2Phi").c_str()]->Fill(photon.phi(), weight);
    }

    if (pjSelector.isJetValid()) {
      const pat::Jet & jet = pjSelector.jet();
      hists_[(prefix + "jetPt").c_str()]->Fill(jet.pt(), weight);
      hists_[(prefix + "jetEta").c_str()]->Fill(jet.eta(), weight);
      hists_[(prefix + "jetPhi").c_str()]->Fill(jet.phi(), weight);

      /* for Simon
      for (std::vector<pat::Jet>::const_iterator jetsBegin = pjSelector.selectedJets().begin(), jetsEnd = pjSelector.selectedJets().end(), ijet = jetsBegin; ijet != jetsEnd; ++ijet) {        
	std::cout << "pt: " << ijet->pt() << std::endl;
      }
      */

    }

    if (pjSelector.isJet2Valid()) {
      const pat::Jet & jet = pjSelector.jet2();
      hists_[(prefix + "jet2Pt").c_str()]->Fill(jet.pt(), weight);
      hists_[(prefix + "jet2Eta").c_str()]->Fill(jet.eta(), weight);
      hists_[(prefix + "jet2Phi").c_str()]->Fill(jet.phi(), weight);
    }

    if (pjSelector.isJet3Valid()) {
      const pat::Jet & jet = pjSelector.jet3();
      hists_[(prefix + "jet3Pt").c_str()]->Fill(jet.pt(), weight);
      hists_[(prefix + "jet3Eta").c_str()]->Fill(jet.eta(), weight);
      hists_[(prefix + "jet3Phi").c_str()]->Fill(jet.phi(), weight);
    }

    if (pjSelector.isJet4Valid()) {
      const pat::Jet & jet = pjSelector.jet4();
      hists_[(prefix + "jet4Pt").c_str()]->Fill(jet.pt(), weight);
      hists_[(prefix + "jet4Eta").c_str()]->Fill(jet.eta(), weight);
      hists_[(prefix + "jet4Phi").c_str()]->Fill(jet.phi(), weight);
    }

    if (pjSelector.isbJetValid()) {
      const pat::Jet & jet = pjSelector.bjet();
      hists_[(prefix + "bjetPt").c_str()]->Fill(jet.pt(), weight);
      hists_[(prefix + "bjetEta").c_str()]->Fill(jet.eta(), weight);
      hists_[(prefix + "bjetPhi").c_str()]->Fill(jet.phi(), weight);
    }

    if (pjSelector.isbJet2Valid()) {
      const pat::Jet & jet = pjSelector.bjet2();
      hists_[(prefix + "bjet2Pt").c_str()]->Fill(jet.pt(), weight);
      hists_[(prefix + "bjet2Eta").c_str()]->Fill(jet.eta(), weight);
      hists_[(prefix + "bjet2Phi").c_str()]->Fill(jet.phi(), weight);
    }

    if (pjSelector.isMetValid()) {
      const pat::MET & met = pjSelector.met();
      const pat::MET & metRaw = pjSelector.metRaw();
      const pat::MET & metT1 = pjSelector.metT1();
      const pat::MET & metT2 = pjSelector.metT2();
      const pat::MET & met2 = pjSelector.met2();

      hists_[(prefix + "metPt").c_str()]->Fill(met.pt(), weight);

      if (squarkm != 0 || gluinom != 0) 
	fillHistosSignalscan(event, weight, weightNoPURescale, pjSelector, prefix, squarkm, gluinom, neutrm);
      
      hists_[(prefix + "metPtRaw").c_str()]->Fill(metRaw.pt(), weight);
      hists_[(prefix + "metPtT1").c_str()]->Fill(metT1.pt(), weight);
      hists_[(prefix + "metPtT2").c_str()]->Fill(metT2.pt(), weight);
      hists_[(prefix + "metPt2").c_str()]->Fill(met2.pt(), weight);

      if (met.genMET() != 0) 
	hists_[(prefix + "genMet").c_str()]->Fill(met.genMET()->pt(), weight);
       	  
      hists_[(prefix + "metPhi").c_str()]->Fill(met.phi(), weight);	  
      hists_[(prefix + "metSumEt").c_str()]->Fill(met.sumEt(), weight);	  
      hists_[(prefix + "mt").c_str()]->Fill(pjSelector.mt().pt(), weight);	  
    } // isMetValid()
    
    hists_[(prefix + "HBHENoiseFilter").c_str()] ->Fill(pjSelector.hbheNoise(), weight);
    hists_[(prefix + "HcalLaserFilter").c_str()] ->Fill(pjSelector.hcalLaserEvent(), weight);
    hists_[(prefix + "EcaldDCTPFilter").c_str()] ->Fill(pjSelector.ecalDeadCellTP(), weight);
    hists_[(prefix + "EcaldDCBEFilter").c_str()] ->Fill(pjSelector.ecalDeadCellBE(), weight);
    hists_[(prefix + "trackingFailureFilter").c_str()] ->Fill(pjSelector.trackingFailure(), weight);
    hists_[(prefix + "CSCHaloBeamFilter").c_str()] ->Fill(pjSelector.cscTightHalo(), weight);
    hists_[(prefix + "eeBadScFilter").c_str()] ->Fill(pjSelector.eeBadScFilter(), weight);

    hists_[(prefix + "noJets").c_str()]->Fill(pjSelector.selectedJets().size(), weight);
    hists_[(prefix + "noPhotons").c_str()]->Fill(pjSelector.selectedPhotons().size(), weight);
    hists_[(prefix + "noPhotonsGenMatch").c_str()]->Fill(pjSelector.selectedPhotonsWithGenMatch().size(), weight);
    hists_[(prefix + "noBJets").c_str()]->Fill(pjSelector.selectedBJets().size(), weight);

    if (pjSelector.isJetValid() || pjSelector.isPhotonValid()) {
      hists_[(prefix + "ht").c_str()]->Fill(pjSelector.ht(), weight);
      hists_[(prefix + "hthlt").c_str()]->Fill(pjSelector.htHLT(), weight);

      hists_[(prefix + "htj").c_str()]->Fill(pjSelector.htj(), weight);
      hists_[(prefix + "mht").c_str()]->Fill(pjSelector.mht().pt(), weight);
      hists_[(prefix + "mhtj").c_str()]->Fill(pjSelector.mhtj().pt(), weight);

      hists2D_[(prefix + "mhtVsmet").c_str()]->Fill(pjSelector.mht().pt(), pjSelector.met().pt(), weight);
      hists2D_[(prefix + "mhtVsmet2").c_str()]->Fill(pjSelector.mht().pt(), pjSelector.met2().pt(), weight);
      hists2D_[(prefix + "metVsmet2").c_str()]->Fill(pjSelector.met().pt(), pjSelector.met2().pt(), weight);
      hists2D_[(prefix + "metRawVsmetT1").c_str()]->Fill(pjSelector.metRaw().pt(), pjSelector.metT1().pt(), weight);
      hists2D_[(prefix + "metT1VsmetT2").c_str()]->Fill(pjSelector.metT1().pt(), pjSelector.metT2().pt(), weight);

      if (pjSelector.isPhotonValid()) {
	hists2D_[(prefix + "metVsPhotonPt").c_str()] ->Fill(pjSelector.met().pt(), pjSelector.correctedphotonpt(), weight);
	hists2D_[(prefix + "metVsnoJet").c_str()] ->Fill(pjSelector.met().pt(), pjSelector.selectedJets().size(), weight);

	hists2D_[(prefix + "noPVVsPhotonPt").c_str()] ->Fill(pjSelector.getNoPV(), pjSelector.correctedphotonpt(), weight);
	hists2D_[(prefix + "noJetsVsPhotonPt").c_str()] ->Fill(pjSelector.selectedJets().size(), pjSelector.correctedphotonpt(), weight);
		
	if (pjSelector.isMetValid()) {
	  if( pjSelector.met().pt() <= 100. ) {
	    hists2D_[(prefix + "noJetsVsPhotonPtLowMet").c_str()] ->Fill(pjSelector.selectedJets().size(), pjSelector.correctedphotonpt(), weight);
	  } // met().pt() <= 100.
	} // isMetValid()
	
	hists2D_[(prefix + "metVsPhotonEt").c_str()] ->Fill(pjSelector.met().pt(), pjSelector.photon().et(), weight);
	hists2D_[(prefix + "metVsDeltaRMetPhoton").c_str()] ->Fill(pjSelector.met().pt(), pjSelector.getDeltaRMetPhoton1(), weight);

	hists2D_[(prefix + "metVsDeltaPhiMetPhoton").c_str()] ->Fill(pjSelector.met().pt(), pjSelector.getDeltaPhiMetPhoton1(), weight);

	hists2D_[(prefix + "metVsR9").c_str()] ->Fill(pjSelector.met().pt(), pjSelector.photon().r9(), weight);
	hists2D_[(prefix + "mhtVsPhotonPt").c_str()] ->Fill(pjSelector.mht().pt(), pjSelector.correctedphotonpt(), weight);
      } // isPhotonValid()

      hists2D_[(prefix + "metVsHT").c_str()] ->Fill(pjSelector.met().pt(), pjSelector.ht(), weight);
      hists2D_[(prefix + "mhtVsHT").c_str()] ->Fill(pjSelector.mht().pt(), pjSelector.ht(), weight);
    } // isJetValid() || isPhotonValid()

    if (pjSelector.isJetValid()) {
      hists_[(prefix + "deltaPhiMetJet1").c_str()] ->Fill(pjSelector.getDeltaPhiMetJet1(), weight);
      if (pjSelector.isJetValid()) {

	if (pjSelector.isPhotonValid()) {
	  hists_[(prefix + "deltaPhiJ1Photon").c_str()] ->Fill(pjSelector.getDeltaPhiJ1Photon(), weight);
	  hists_[(prefix + "deltaRPhotonJet").c_str()] ->Fill(pjSelector.getMinDeltaRPhotonJet(), weight);
	  hists_[(prefix + "deltaPhiMetT1Photon").c_str()] ->Fill(pjSelector.getDeltaPhiMetT1Photon1(), weight);

	  hists_[(prefix + "deltaPhiMetPhoton").c_str()] ->Fill(pjSelector.getDeltaPhiMetPhoton1(), weight);
	  hists_[(prefix + "deltaRMetPhoton").c_str()] ->Fill(pjSelector.getDeltaRMetPhoton1(), weight);

	}

	if (pjSelector.isJet2Valid()) {
	  hists_[(prefix + "deltaPhiMetJet2").c_str()] ->Fill(pjSelector.getDeltaPhiMetJet2(), weight);
	  hists_[(prefix + "deltaPhiJ1J2").c_str()] ->Fill(pjSelector.getDeltaPhiJ1J2(), weight);
	  hists_[(prefix + "Mj12").c_str()] ->Fill(pjSelector.getMj12(), weight);
	}

	if (pjSelector.isJet3Valid()) {
	  hists_[(prefix + "deltaPhiMetJet3").c_str()] ->Fill(pjSelector.getDeltaPhiMetJet3(), weight);
	  hists_[(prefix + "Mj23").c_str()] ->Fill(pjSelector.getMj23(), weight);
	  hists_[(prefix + "Mj13").c_str()] ->Fill(pjSelector.getMj13(), weight);
	}
	
	hists_[(prefix + "noPV").c_str()]->Fill(pjSelector.getNoPV(), weight);
	hists_[(prefix + "noPVPU").c_str()]->Fill(pjSelector.getNoPVPU(), weightNoPURescale);
	hists_[(prefix + "noPVPUWeighted").c_str()]->Fill(pjSelector.getNoPVPU(), weight);
      } // isJetValid() 

      hists_[(prefix + "vetoedJetsElectron").c_str()]->Fill(pjSelector.vetoedElectronJets(), weight);
      hists_[(prefix + "vetoedJetsMuon").c_str()]->Fill(pjSelector.vetoedMuonJets(), weight);
      hists_[(prefix + "vetoedJetsElectronHLT").c_str()]->Fill(pjSelector.hltVetoedElectronJets(), weight);
      hists_[(prefix + "vetoedJetsMuonHLT").c_str()]->Fill(pjSelector.hltVetoedMuonJets(), weight);

      hists_[(prefix + "hltphotonjetpt").c_str()]->Fill(pjSelector.hltPhotonJetPt(), weight);

      if (pjSelector.getEtRelPhotonJets() != 0) 
	hists_[(prefix + "photonJetEtRel").c_str()]->Fill(pjSelector.getEtRelPhotonJets(), weight);
      
      std::vector<double> photonjetemfVec = pjSelector.getEMFPhotonJets();
      for (int v = 0; v < (int) photonjetemfVec.size(); ++v) {
	hists_[(prefix + "photonjetEmf").c_str()]->Fill(photonjetemfVec[v], weight);
      }
      std::vector<double> photonjetemfVecInclE = pjSelector.getEMFPhotonJetsInclEFrac();
      for (int v = 0; v < (int) photonjetemfVecInclE.size(); ++v) {
	hists_[(prefix + "photonjetEmfInclE").c_str()]->Fill(photonjetemfVecInclE[v], weight);
      }
      std::vector<double> photonjetrespVec = pjSelector.getResponsePhotonJets();
      for (int v = 0; v < (int) photonjetrespVec.size(); ++v) {
	hists_[(prefix + "photonjetResp").c_str()]->Fill(photonjetrespVec[v], weight);
      }
      std::vector<double> photonjetrespVecUncorr = pjSelector.getResponsePhotonJetsUncorr();
      for (int v = 0; v < (int) photonjetrespVecUncorr.size(); ++v) {
	hists_[(prefix + "photonjetRespUncorr").c_str()]->Fill(photonjetrespVecUncorr[v], weight);
      }
      std::vector<double> photonjetrespVecL1 = pjSelector.getResponsePhotonJetsL1();
      for (int v = 0; v < (int) photonjetrespVecL1.size(); ++v) {
	hists_[(prefix + "photonjetRespL1").c_str()]->Fill(photonjetrespVecL1[v], weight);
      }
      std::vector < std::pair<double, double> > etRelVec = pjSelector.getDeltaRVsEtrel();
      for (int v = 0; v < (int) etRelVec.size(); ++v) {
	hists2D_[(prefix + "deltaRPhotonJetVsEtrel").c_str()]->Fill(etRelVec[v].first, etRelVec[v].second, weight);
      }
      std::vector < std::pair<double, double> > etRelVecUncorr = pjSelector.getDeltaRVsEtrelUncorr();
      for (int v = 0; v < (int) etRelVecUncorr.size(); ++v) {
	hists2D_[(prefix + "deltaRPhotonJetVsEtrelUncorr").c_str()]->Fill(etRelVecUncorr[v].first, etRelVecUncorr[v].second, weight);
      }
      std::vector < std::pair<double, double> > etRelVecGen = pjSelector.getDeltaRVsEtrelGen();
      for (int v = 0; v < (int) etRelVecGen.size(); ++v) {
	hists2D_[(prefix + "deltaRPhotonJetVsEtrelGen").c_str()]->Fill(etRelVecGen[v].first, etRelVecGen[v].second, weight);
      }

    } // isJetValid()

  } // if(drawPlots_)

  return;
}
