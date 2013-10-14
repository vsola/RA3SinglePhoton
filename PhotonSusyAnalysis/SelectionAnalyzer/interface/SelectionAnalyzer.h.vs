/*
 * SelectionAnalyzer.h
 *
 *  Created on: Feb 8, 2011
 *      Author: gebbert
 */

#ifndef SELECTIONANALYZER_H_
#define SELECTIONANALYZER_H_

#include "PhotonSusyAnalysis/SelectionAnalyzer/interface/PhotonJetSelector.h"

#include "PhysicsTools/UtilAlgos/interface/BasicAnalyzer.h"
#include "PhysicsTools/UtilAlgos/interface/EDAnalyzerWrapper.h"
#include "PhysicsTools/UtilAlgos/interface/EDFilterWrapper.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "PhysicsTools/SelectorUtils/interface/strbitset.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"

#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"

#include <map>
#include <string>
#include <fstream>

class SelectionAnalyzer: public edm::BasicAnalyzer {

public:
	/// default constructor
	SelectionAnalyzer(const edm::ParameterSet& cfg, TFileDirectory& fs) :
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
		pjSelectorPresel_(selection_)
	{
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

		if (cfg.exists("cutsForN1")) {
			cutsN1_ = cfg.getParameter<std::vector<std::string> > ("cutsForN1");
			for (int cutIt = 0; cutIt < (int) (cutsN1_.size()); ++cutIt) {
				std::string cut = cutsN1_.at(cutIt);
				if ( loggingVerbosity_ > 1 )
					std::cout << "ini Histos" << "N_1_" << cut << "_" << std::endl;
				initializeHistos(fs, "N_1_" + cut + "_");
			}
		}

		std::string fileName("PhotonSusyAnalysis/SelectionAnalyzer/data/" + applyFakeRateCorrectionHistoName_ + ".root");
		 if ( loggingVerbosity_ > 1 ) {
			std::cout << "filename:" << applyFakeRateCorrectionHistoName_ << std::endl;
		}
		edm::FileInPath fip(fileName);

		TFile* f = TFile::Open(fip.fullPath().c_str());
		std::string canvasname = "c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RAT";

		//"c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RAT";
		//"c_PreselCut_photonPt_RAT";
		//"c_DivideXPreselCut_metVsPhotonPt_Bin_From_0_CompTightLoose_RAT";

		TCanvas * c = (TCanvas *) f->FindObjectAny(canvasname.c_str());
		std::string histoname = "blabla1clone2";
		if ( loggingVerbosity_ > 1 ){
			std::cout << "canvas:" << c << std::endl;
		}

		qcdCorrection_ = (TH1F *) c->FindObject(histoname.c_str());
		qcdCorrection_->SetDirectory(0);
		//read ==2jet correction histo
		std::string fileName2j("PhotonSusyAnalysis/SelectionAnalyzer/data/" + applyFakeRateCorrectionHistoName2j_ + ".root");
			if ( loggingVerbosity_ > 1 )
				std::cout << "filename2j:" << applyFakeRateCorrectionHistoName2j_ << std::endl;
			edm::FileInPath fip2j(fileName2j);

			TFile* f2j = TFile::Open(fip2j.fullPath().c_str());
			std::string canvasname2j = "c_DivideXPreselCut_noJetsVsPhotonPtLowMet_Bin_From_2_CompTightLoose_RAT";

			TCanvas * c2j = (TCanvas *) f2j->FindObjectAny(canvasname2j.c_str());
			if ( loggingVerbosity_ > 1 )
				std::cout << "canvas2j:" << c2j << std::endl;


			qcdCorrection2j_ = (TH1F *) c2j->FindObject(histoname.c_str());
			qcdCorrection2j_->SetDirectory(0);
		//read in HT histogram
		std::string fileNameHT("PhotonSusyAnalysis/SelectionAnalyzer/data/" + applyFakeRateCorrectionHistoNameHT_ + ".root");
		if ( loggingVerbosity_ > 1 )
			std::cout << "filename HT:" << applyFakeRateCorrectionHistoNameHT_ << std::endl;
		edm::FileInPath fipHT(fileNameHT);

		TFile* fHT = TFile::Open(fipHT.fullPath().c_str());
		canvasname = "c_DivideXPreselCut_metVsnoJet_Bin_From_0_CompTightLoose_RAT";
		TCanvas * cHT = (TCanvas *) fHT->FindObjectAny(canvasname.c_str());
		if ( loggingVerbosity_ > 1 )
			std::cout << "canvas HT:" << cHT << std::endl;

		qcdCorrectionHT_ = (TH1F *) cHT->FindObject(histoname.c_str());
		qcdCorrectionHT_->SetDirectory(0);
		//
		if ( loggingVerbosity_ > 1 )
			std::cout << "constructor done:" << c << std::endl;
		f->Close();
		delete f;
		fHT->Close();
		delete fHT;

	}
	/// default destructor
	virtual ~SelectionAnalyzer() {
	}
	;
	/// everything that needs to be done before the event loop
	void beginJob() {
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
	;
	/// everything that needs to be done after the event loop
	void endJob() {
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
	;
	void initializeHistosSignalScan(TFileDirectory * fs, std::string prefix = "", std::string parPoint = "") {
		if (drawPlots_ && parPoint != "") {
			hists_[(prefix + "metPt_" + parPoint).c_str()] = fs->make<TH1F> ((prefix + "metPt_" + parPoint).c_str(), "pt", 100, 0., 1000.);
			hists_[(prefix + "metPt_" + parPoint).c_str()]->Sumw2();
		}
	}
	void initializeHistos(TFileDirectory& fs, std::string prefix = "") {
		if (drawPlots_) {
			///initialize histos for basic object histograms
			hists_[(prefix + "photonPt").c_str()] = fs.make<TH1F> ((prefix + "photonPt").c_str(), "pt", 150, 5., 1505.);
			hists_[(prefix + "photonPt").c_str()]->Sumw2();
			hists_[(prefix + "photonTrigPt").c_str()] = fs.make<TH1F> ((prefix + "photonTrigPt").c_str(), "pt", 300, 5., 1505.);
			hists_[(prefix + "photonTrigPt").c_str()]->Sumw2();


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
			hists_[(prefix + "ht").c_str()] = fs.make<TH1F> ((prefix + "ht").c_str(), "ht", 150, 50., 1500.);
			hists_[(prefix + "ht").c_str()]->Sumw2();
			hists_[(prefix + "hthlt").c_str()] = fs.make<TH1F> ((prefix + "hthlt").c_str(), "hthlt", 150, 50., 1500.);
			hists_[(prefix + "hthlt").c_str()]->Sumw2();

			hists_[(prefix + "hthltN90").c_str()] = fs.make<TH1F> ((prefix + "hthltN90").c_str(), "hthltN90", 150, -0., 1500.);
			hists_[(prefix + "hthltN90").c_str()]->Sumw2();

			hists_[(prefix + "hthltN90Hits").c_str()] = fs.make<TH1F> ((prefix + "hthltN90Hits").c_str(), "hthltN90Hits", 150, -0., 1500.);
			hists_[(prefix + "hthltN90Hits").c_str()]->Sumw2();

			hists_[(prefix + "n90HLTPhotonJet").c_str()] = fs.make<TH1F> ((prefix + "n90HLTPhotonJet").c_str(), "n90HLTPhotonJet", 100, -0., 100.);
			hists_[(prefix + "n90HLTPhotonJet").c_str()]->Sumw2();
			hists_[(prefix + "n90hitsHLTPhotonJet").c_str()] = fs.make<TH1F> ((prefix + "n90hitsHLTPhotonJet").c_str(), "n90hitsHLTPhotonJet", 100, -0., 100.);
			hists_[(prefix + "n90hitsHLTPhotonJet").c_str()]->Sumw2();

			hists_[(prefix + "htj").c_str()] = fs.make<TH1F> ((prefix + "htj").c_str(), "htj", 150, -0., 1500.);
			hists_[(prefix + "htj").c_str()]->Sumw2();
			hists_[(prefix + "mht").c_str()] = fs.make<TH1F> ((prefix + "mht").c_str(), "mht", 100, -0., 800.);
			hists_[(prefix + "mht").c_str()]->Sumw2();
			hists_[(prefix + "mhtj").c_str()] = fs.make<TH1F> ((prefix + "mhtj").c_str(), "mhtj", 100, -0., 800.);
			hists_[(prefix + "mhtj").c_str()]->Sumw2();
			hists_[(prefix + "deltaPhiJ1J2").c_str()] = fs.make<TH1F> ((prefix + "deltaPhiJ1J2").c_str(), "deltaPhiJ1J2", 32, -0., 3.20);
			hists_[(prefix + "deltaPhiJ1J2").c_str()]->Sumw2();
			hists_[(prefix + "deltaPhiJ1Photon").c_str()] = fs.make<TH1F> ((prefix + "deltaPhiJ1Photon").c_str(), "deltaPhiJ1Photon", 32, -0., 3.20);
			hists_[(prefix + "deltaPhiJ1Photon").c_str()]->Sumw2();
			hists_[(prefix + "deltaRPhotonJet").c_str()] = fs.make<TH1F> ((prefix + "deltaRPhotonJet").c_str(), "deltaRPhotonJet", 32, -0., 3.20);
			hists_[(prefix + "deltaRPhotonJet").c_str()]->Sumw2();
			hists_[(prefix + "deltaPhiMetJet1").c_str()] = fs.make<TH1F> ((prefix + "deltaPhiMetJet1").c_str(), "deltaPhiMetJet1", 32, -0., 3.20);
			hists_[(prefix + "deltaPhiMetJet1").c_str()]->Sumw2();
			hists_[(prefix + "deltaPhiMetT1Photon").c_str()] = fs.make<TH1F> ((prefix + "deltaPhiMetT1Photon").c_str(), "deltaPhiMetT1Photon", 32, -0., 3.20);
			hists_[(prefix + "deltaPhiMetT1Photon").c_str()]->Sumw2();
			hists_[(prefix + "deltaPhiMetJet2").c_str()] = fs.make<TH1F> ((prefix + "deltaPhiMetJet2").c_str(), "deltaPhiMetJet2", 32, -0., 3.20);
			hists_[(prefix + "deltaPhiMetJet2").c_str()]->Sumw2();
			hists_[(prefix + "deltaPhiMetJet3").c_str()] = fs.make<TH1F> ((prefix + "deltaPhiMetJet3").c_str(), "deltaPhiMetJet3", 32, -0., 3.20);
			hists_[(prefix + "deltaPhiMetJet3").c_str()]->Sumw2();

			hists_[(prefix + "deltaPhiMetPhoton").c_str()] = fs.make<TH1F> ((prefix + "deltaPhiMetPhoton").c_str(), "deltaPhiMetPhoton", 32, -0., 3.20);
			hists_[(prefix + "deltaPhiMetPhoton").c_str()]->Sumw2();

			hists_[(prefix + "deltaRMetPhoton").c_str()] = fs.make<TH1F> ((prefix + "deltaRMetPhoton").c_str(), "deltaRMetPhoton", 32, -0., 3.20);
			hists_[(prefix + "deltaRMetPhoton").c_str()]->Sumw2();

			hists_[(prefix + "Mj12").c_str()] = fs.make<TH1F> ((prefix + "Mj12").c_str(), "Mj12", 150, -0., 1000.);
			hists_[(prefix + "Mj12").c_str()]->Sumw2();
			hists_[(prefix + "Mj23").c_str()] = fs.make<TH1F> ((prefix + "Mj23").c_str(), "Mj23", 150, -0., 1000.);
			hists_[(prefix + "Mj23").c_str()]->Sumw2();
			hists_[(prefix + "Mj13").c_str()] = fs.make<TH1F> ((prefix + "Mj13").c_str(), "Mj13", 150, -0., 1000.);
			hists_[(prefix + "Mj13").c_str()]->Sumw2();

			//initialize histos for photon id plots
			hists_[(prefix + "sigmaietaieta").c_str()] = fs.make<TH1F> ((prefix + "sigmaietaieta").c_str(), "sigmaietaieta", 50, -0., 0.016);
			hists_[(prefix + "sigmaietaieta").c_str()]->Sumw2();

			hists_[(prefix + "trackiso").c_str()] = fs.make<TH1F> ((prefix + "trackiso").c_str(), "trackiso", 100, -0., 100);
			hists_[(prefix + "trackiso").c_str()]->Sumw2();
			hists_[(prefix + "ecaliso").c_str()] = fs.make<TH1F> ((prefix + "ecaliso").c_str(), "ecaliso", 50, -0., 20);
			hists_[(prefix + "ecaliso").c_str()]->Sumw2();
			hists_[(prefix + "hcaliso").c_str()] = fs.make<TH1F> ((prefix + "hcaliso").c_str(), "hcaliso", 50, -0., 20);
			hists_[(prefix + "ecaliso03").c_str()] = fs.make<TH1F> ((prefix + "ecaliso03").c_str(), "ecaliso03", 50, -0., 20);
			hists_[(prefix + "ecaliso03").c_str()]->Sumw2();
			hists_[(prefix + "hcaliso03").c_str()] = fs.make<TH1F> ((prefix + "hcaliso03").c_str(), "hcaliso03", 50, -0., 20);
			hists_[(prefix + "hcaliso03").c_str()]->Sumw2();
			hists_[(prefix + "combiso").c_str()] = fs.make<TH1F> ((prefix + "combiso").c_str(), "combiso", 50, -0., 50);
			hists_[(prefix + "combiso").c_str()]->Sumw2();
			hists_[(prefix + "chargedIso").c_str()] = fs.make<TH1F> ((prefix + "chargedIso").c_str(), "chargedIso", 50, -0., 50);
			hists_[(prefix + "chargedIso").c_str()]->Sumw2();
			hists_[(prefix + "photonIso").c_str()] = fs.make<TH1F> ((prefix + "photonIso").c_str(), "photonIso", 50, -0., 50);
			hists_[(prefix + "photonIso").c_str()]->Sumw2();
			hists_[(prefix + "neutralIso").c_str()] = fs.make<TH1F> ((prefix + "neutralIso").c_str(), "neutralIso", 50, -0., 50);
			hists_[(prefix + "neutralIso").c_str()]->Sumw2();

			hists_[(prefix + "r9").c_str()] = fs.make<TH1F> ((prefix + "r9").c_str(), "r9", 200, -0., 10);
			hists_[(prefix + "r9").c_str()]->Sumw2();

			hists_[(prefix + "hadronicOverEm").c_str()] = fs.make<TH1F> ((prefix + "hadronicOverEm").c_str(), "hadronicOverEm", 50, -0., 1);
			hists_[(prefix + "hadronicOverEm").c_str()]->Sumw2();

			hists_[(prefix + "pixelseed").c_str()] = fs.make<TH1F> ((prefix + "pixelseed").c_str(), "pixelseed", 100, -0., 100);
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

			hists2D_[(prefix + "n90VsHTHLT").c_str()] = fs.make<TH2F> ((prefix + "n90VsHTHLT").c_str(), "n90VsHTHLT", 100, -0., 100, 150, -0., 1500.);
			hists2D_[(prefix + "n90VsHTHLT").c_str()]->Sumw2();

			hists2D_[(prefix + "n90VsJetPt").c_str()] = fs.make<TH2F> ((prefix + "n90VsJetPt").c_str(), "n90VsJetPt", 100, -0., 100, 100, -0., 1000.);
			hists2D_[(prefix + "n90VsJetPt").c_str()]->Sumw2();

			hists2D_[(prefix + "n90hitsVsn90HLTPhotonJet").c_str()] = fs.make<TH2F> ((prefix + "n90hitsVsn90HLTPhotonJet").c_str(), "n90hitsVsn90HLTPhotonJet", 100, -0., 100, 100, -0., 100.);
			hists2D_[(prefix + "n90hitsVsn90HLTPhotonJet").c_str()]->Sumw2();

			hists2D_[(prefix + "combIsoVsPhotonPt").c_str()] = fs.make<TH2F> ((prefix + "combIsoVsPhotonPt").c_str(), "combIsoVsPhotonPt", 100, -0., 100., 150, 5., 1505.);
			hists2D_[(prefix + "combIsoVsPhotonPt").c_str()]->Sumw2();

		}
	}
	void printBinnedMETAbove100STAT(PhotonJetSelector pjSelector, std::string prefix = "", std::string signalParPoint = "") {
		// const pat::MET & met = pjSelector.met(); // unused variable
		std::string histoname = prefix + "metPt";
		if (signalParPoint != "") {
			histoname = histoname + "_" + signalParPoint;
		}
		TH1F * metHisto = (TH1F*) hists_[(histoname).c_str()]->Clone();
		if (metHisto->GetSumw2N() == 0)
			metHisto->Sumw2();
		TH1F * metHistoRebinned = rebinMETHistoForEventYields(metHisto);

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
	void printBinnedMETAbove100(PhotonJetSelector pjSelector, std::string prefix = "", std::string signalParPoint = "") {
		// const pat::MET & met = pjSelector.met(); // unused variable
		std::string histoname = prefix + "metPt";
		if (signalParPoint != "") {
			histoname = histoname + "_" + signalParPoint;
		}
		TH1F * metHisto = (TH1F*) hists_[(histoname).c_str()]->Clone();
		if (metHisto->GetSumw2N() == 0)
			metHisto->Sumw2();
		TH1F * metHistoRebinned = rebinMETHistoForEventYields(metHisto);

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
	void printBinsMETAbove100(PhotonJetSelector pjSelector, std::string prefix = "", std::string signalParPoint = "") {
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
	TH1F * rebinMETHistoForEventYields(TH1F * metHisto) {
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
		//binEdges.push_back(110);
		binEdges.push_back(120);
		//binEdges.push_back(130);
		//binEdges.push_back(140);
		//binEdges.push_back(149);
		binEdges.push_back(159);
		//binEdges.push_back(169);
		//binEdges.push_back(179);
		binEdges.push_back(199);
		binEdges.push_back(269);
		//binEdges.push_back(299);
		binEdges.push_back(349);
		//binEdges.push_back(399);
		binEdges.push_back(449);
		//binEdges.push_back(699);
		binEdges.push_back(oldmaximum);

		TH1F *hRebinned = (TH1F*) metHisto->Rebin(binEdges.size() - 1, metHisto->GetName(), &(binEdges.front()));

		return hRebinned;
	}
	void fillHistosSignalscan(const edm::EventBase& event, double weight, double weightNoPURescale, PhotonJetSelector pjSelector, std::string prefix = "", int squarkm = 0, int gluinom = 0, int neutrm = 0) {

		if (drawPlots_ && (squarkm != 0 || gluinom != 0)) {
			if (pjSelector.isMetValid()) {

				const pat::MET & met = pjSelector.met();
				std::string app = pjSelector.getSignalScanPointName();
				//std::cout << "Fill met SIGNALSCAN!"<<app << std::endl;
				hists_[(prefix + "metPt_" + app).c_str()]->Fill(met.pt(), weight);
			}

		}

	}
	;
	void fillHistos(const edm::EventBase& event, double weight, double weightNoPURescale, PhotonJetSelector pjSelector, std::string prefix = "", int squarkm = 0, int gluinom = 0, int neutrm = 0) {
		if (drawPlots_) {
			//cout << "draw plots - " << prefix << std::endl;
			if (pjSelector.isPhotonValid()) {
				const pat::Photon & photon = pjSelector.photon();
				;
				//				std::cout << "fill photon pt plot  - " << pjSelector.correctedphotonpt() << std::endl;
				//				std::cout << "and weight  - " << weight << std::endl;
				hists_[(prefix + "photonPt").c_str()]->Fill(pjSelector.correctedphotonpt(), weight);
				hists_[(prefix + "photonTrigPt").c_str()]->Fill(pjSelector.photonptTRIG(), weight);
				
				hists_[(prefix + "photonEt").c_str()]->Fill(photon.et(), weight);

				//electron veto variables
				hists_[(prefix + "photonElectronSafe").c_str()]->Fill( (float) photon.userInt("isPromptElectronSafe"), weight);
				float phPixelSeed = 0.;
				if( photon.hasPixelSeed() )
				  phPixelSeed = 0.;
				else
				  phPixelSeed = 1.;
				hists_[(prefix + "photonPixelSeed").c_str()]->Fill(phPixelSeed, weight);


				hists_[(prefix + "photonEta").c_str()]->Fill(photon.eta(), weight);

				hists_[(prefix + "photonPhi").c_str()]->Fill(photon.phi(), weight);

				hists_[(prefix + "sigmaietaieta").c_str()]->Fill(photon.sigmaIetaIeta(), weight);

				hists_[(prefix + "trackiso").c_str()]->Fill(photon.trackIso(), weight);
				hists_[(prefix + "hcaliso").c_str()]->Fill(photon.hcalIso(), weight);
				hists_[(prefix + "hcaliso03").c_str()]->Fill(photon.hcalTowerSumEtConeDR03(), weight);
				hists_[(prefix + "hadronicOverEm").c_str()]->Fill(photon.hadronicOverEm(), weight);
				hists_[(prefix + "ecaliso").c_str()] ->Fill(photon.ecalIso(), weight);
				hists_[(prefix + "ecaliso03").c_str()] ->Fill(photon.ecalRecHitSumEtConeDR03(), weight);
				hists_[(prefix + "r9").c_str()] ->Fill(photon.r9(), weight);
				hists_[(prefix + "pixelseed").c_str()] ->Fill(photon.electronPixelSeeds().size(), weight);
				double combiso = (photon.ecalRecHitSumEtConeDR03() - 0.1474 * photon.userFloat("rhoPU")) + (photon.hcalTowerSumEtConeDR03() - 0.0467 * photon.userFloat("rhoPU")) + photon.trkSumPtSolidConeDR03();
				hists_[(prefix + "combiso").c_str()] ->Fill(combiso, weight);
				hists_[(prefix + "chargedIso").c_str()] ->Fill(photon.userFloat("chargedIso"), weight);
				hists_[(prefix + "photonIso").c_str()] ->Fill(photon.userFloat("photonIso"), weight);
				hists_[(prefix + "neutralIso").c_str()] ->Fill(photon.userFloat("neutralIso"), weight);
				hists2D_[(prefix + "combIsoVsPhotonPt").c_str()]->Fill(combiso, photon.pt(), weight);

			}
			//cout << "T1 - " << prefix << std::endl;

			if (pjSelector.isPhoton2Valid()) {
				const pat::Photon & photon = pjSelector.photon2();
				hists_[(prefix + "photon2Pt").c_str()]->Fill(photon.pt(), weight);

				hists_[(prefix + "photon2Eta").c_str()]->Fill(photon.eta(), weight);

				hists_[(prefix + "photon2Phi").c_str()]->Fill(photon.phi(), weight);

			}
			//std::cout << "Fill Jets!" << std::endl;

			if (pjSelector.isJetValid()) {
				//std::cout << "Fill Jets 1!" << std::endl;
				const pat::Jet & jet = pjSelector.jet();
				//std::cout << "Fill Jets 1a!" << std::endl;
				hists_[(prefix + "jetPt").c_str()]->Fill(jet.pt(), weight);

				hists_[(prefix + "jetEta").c_str()]->Fill(jet.eta(), weight);

				hists_[(prefix + "jetPhi").c_str()]->Fill(jet.phi(), weight);

				//std::cout << "Fill Jets 1b!" << std::endl;
			}
			if (pjSelector.isJet2Valid()) {
				//std::cout << "Fill Jets 2!" << std::endl;
				const pat::Jet & jet = pjSelector.jet2();
				hists_[(prefix + "jet2Pt").c_str()]->Fill(jet.pt(), weight);

				hists_[(prefix + "jet2Eta").c_str()]->Fill(jet.eta(), weight);

				hists_[(prefix + "jet2Phi").c_str()]->Fill(jet.phi(), weight);

				//std::cout << "Fill Jets 2b!" << std::endl;
			}
			if (pjSelector.isJet3Valid()) {
				//std::cout << "Fill Jets 3!" << std::endl;
				const pat::Jet & jet = pjSelector.jet3();
				hists_[(prefix + "jet3Pt").c_str()]->Fill(jet.pt(), weight);

				hists_[(prefix + "jet3Eta").c_str()]->Fill(jet.eta(), weight);

				hists_[(prefix + "jet3Phi").c_str()]->Fill(jet.phi(), weight);

				//std::cout << "Fill Jets 3b!" << std::endl;
			}
			if (pjSelector.isJet4Valid()) {
				//std::cout << "Fill Jets 4!" << std::endl;
				const pat::Jet & jet = pjSelector.jet4();
				hists_[(prefix + "jet4Pt").c_str()]->Fill(jet.pt(), weight);

				hists_[(prefix + "jet4Eta").c_str()]->Fill(jet.eta(), weight);

				hists_[(prefix + "jet4Phi").c_str()]->Fill(jet.phi(), weight);

				//std::cout << "Fill Jets 4b!" << std::endl;
			}

			if (pjSelector.isbJetValid()) {
				//std::cout << "Fill bJets 1!" << std::endl;
				const pat::Jet & jet = pjSelector.bjet();
				hists_[(prefix + "bjetPt").c_str()]->Fill(jet.pt(), weight);

				hists_[(prefix + "bjetEta").c_str()]->Fill(jet.eta(), weight);

				hists_[(prefix + "bjetPhi").c_str()]->Fill(jet.phi(), weight);

				//std::cout << "Fill bJets 1b!" << std::endl;
			}
			if (pjSelector.isbJet2Valid()) {
				//std::cout << "Fill bJets 2!" << std::endl;
				const pat::Jet & jet = pjSelector.bjet2();
				hists_[(prefix + "bjet2Pt").c_str()]->Fill(jet.pt(), weight);

				hists_[(prefix + "bjet2Eta").c_str()]->Fill(jet.eta(), weight);

				hists_[(prefix + "bjet2Phi").c_str()]->Fill(jet.phi(), weight);

				//std::cout << "Fill bJets 2b!" << std::endl;
			}

			if (pjSelector.isMetValid()) {
				//std::cout << "Fill met!" << std::endl;
				const pat::MET & met = pjSelector.met();
				const pat::MET & metRaw = pjSelector.metRaw();
				const pat::MET & metT1 = pjSelector.metT1();
				const pat::MET & metT2 = pjSelector.metT2();
				const pat::MET & met2 = pjSelector.met2();
				hists_[(prefix + "metPt").c_str()]->Fill(met.pt(), weight);
				if (squarkm != 0 || gluinom != 0) {
					fillHistosSignalscan(event, weight, weightNoPURescale, pjSelector, prefix, squarkm, gluinom, neutrm);
				}
				hists_[(prefix + "metPtRaw").c_str()]->Fill(metRaw.pt(), weight);
				//std::cout << "Fill T1 met!" << std::endl;
				hists_[(prefix + "metPtT1").c_str()]->Fill(metT1.pt(), weight);
				//std::cout << "Filled T1 met!" << std::endl;
				hists_[(prefix + "metPtT2").c_str()]->Fill(metT2.pt(), weight);
				hists_[(prefix + "metPt2").c_str()]->Fill(met2.pt(), weight);
				if (met.genMET() != 0) {
					hists_[(prefix + "genMet").c_str()]->Fill(met.genMET()->pt(), weight);
				}

				hists_[(prefix + "metPhi").c_str()]->Fill(met.phi(), weight);

				hists_[(prefix + "metSumEt").c_str()]->Fill(met.sumEt(), weight);

				hists_[(prefix + "mt").c_str()]->Fill(pjSelector.mt().pt(), weight);

				//std::cout << "Fill met b!" << std::endl;
			}

			hists_[(prefix + "HBHENoiseFilter").c_str()] ->Fill(pjSelector.hbheNoise(), weight);
			hists_[(prefix + "HcalLaserFilter").c_str()] ->Fill(pjSelector.hcalLaserEvent(), weight);
			hists_[(prefix + "EcaldDCTPFilter").c_str()] ->Fill(pjSelector.ecalDeadCellTP(), weight);
			hists_[(prefix + "EcaldDCBEFilter").c_str()] ->Fill(pjSelector.ecalDeadCellBE(), weight);
			hists_[(prefix + "trackingFailureFilter").c_str()] ->Fill(pjSelector.trackingFailure(), weight);
			hists_[(prefix + "CSCHaloBeamFilter").c_str()] ->Fill(pjSelector.cscTightHalo(), weight);
			hists_[(prefix + "eeBadScFilter").c_str()] ->Fill(pjSelector.eeBadScFilter(), weight);

			//std::cout << "Fill others!" << std::endl;
			hists_[(prefix + "noJets").c_str()]->Fill(pjSelector.selectedJets().size(), weight);

			hists_[(prefix + "noPhotons").c_str()]->Fill(pjSelector.selectedPhotons().size(), weight);

			hists_[(prefix + "noPhotonsGenMatch").c_str()]->Fill(pjSelector.selectedPhotonsWithGenMatch().size(), weight);

			hists_[(prefix + "noBJets").c_str()]->Fill(pjSelector.selectedBJets().size(), weight);
			//std::cout << "Fill others A!" << std::endl;
			if (pjSelector.isJetValid() || pjSelector.isPhotonValid()) {
				hists_[(prefix + "ht").c_str()]->Fill(pjSelector.ht(), weight);
				hists_[(prefix + "hthlt").c_str()]->Fill(pjSelector.htHLT(), weight);
				hists_[(prefix + "hthltN90").c_str()]->Fill(pjSelector.htHLTN90(), weight);
				hists_[(prefix + "hthltN90Hits").c_str()]->Fill(pjSelector.htHLTN90Hits(), weight);

				hists_[(prefix + "n90HLTPhotonJet").c_str()]->Fill(pjSelector.n90HLTPhotonJet(), weight);
				hists2D_[(prefix + "n90VsHTHLT").c_str()]->Fill(pjSelector.n90HLTPhotonJet(), pjSelector.htHLT(), weight);
				hists2D_[(prefix + "n90VsJetPt").c_str()]->Fill(pjSelector.n90HLTPhotonJet(), pjSelector.hltPhotonJetPt(), weight);
				if (pjSelector.hltPhotonJetId() != 0) {
					hists_[(prefix + "n90hitsHLTPhotonJet").c_str()]->Fill(pjSelector.hltPhotonJetId()->n90Hits, weight);
					hists2D_[(prefix + "n90hitsVsn90HLTPhotonJet").c_str()]->Fill(pjSelector.hltPhotonJetId()->n90Hits, pjSelector.n90HLTPhotonJet(), weight);
				}
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
					if(pjSelector.met().pt()<=100)
					hists2D_[(prefix + "noJetsVsPhotonPtLowMet").c_str()] ->Fill(pjSelector.selectedJets().size(), pjSelector.correctedphotonpt(), weight);


					hists2D_[(prefix + "metVsPhotonEt").c_str()] ->Fill(pjSelector.met().pt(), pjSelector.photon().et(), weight);
					hists2D_[(prefix + "metVsDeltaRMetPhoton").c_str()] ->Fill(pjSelector.met().pt(), pjSelector.getDeltaRMetPhoton1(), weight);

					hists2D_[(prefix + "metVsDeltaPhiMetPhoton").c_str()] ->Fill(pjSelector.met().pt(), pjSelector.getDeltaPhiMetPhoton1(), weight);

					hists2D_[(prefix + "metVsR9").c_str()] ->Fill(pjSelector.met().pt(), pjSelector.photon().r9(), weight);
					hists2D_[(prefix + "mhtVsPhotonPt").c_str()] ->Fill(pjSelector.mht().pt(), pjSelector.correctedphotonpt(), weight);
				}
				hists2D_[(prefix + "metVsHT").c_str()] ->Fill(pjSelector.met().pt(), pjSelector.ht(), weight);
				hists2D_[(prefix + "mhtVsHT").c_str()] ->Fill(pjSelector.mht().pt(), pjSelector.ht(), weight);
			}
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
					//std::cout << "Fill others C!" << std::endl;
					hists_[(prefix + "noPV").c_str()]->Fill(pjSelector.getNoPV(), weight);
					hists_[(prefix + "noPVPU").c_str()]->Fill(pjSelector.getNoPVPU(), weightNoPURescale);
					hists_[(prefix + "noPVPUWeighted").c_str()]->Fill(pjSelector.getNoPVPU(), weight);

				}

				hists_[(prefix + "vetoedJetsElectron").c_str()]->Fill(pjSelector.vetoedElectronJets(), weight);
				hists_[(prefix + "vetoedJetsMuon").c_str()]->Fill(pjSelector.vetoedMuonJets(), weight);
				hists_[(prefix + "vetoedJetsElectronHLT").c_str()]->Fill(pjSelector.hltVetoedElectronJets(), weight);
				hists_[(prefix + "vetoedJetsMuonHLT").c_str()]->Fill(pjSelector.hltVetoedMuonJets(), weight);

				hists_[(prefix + "hltphotonjetpt").c_str()]->Fill(pjSelector.hltPhotonJetPt(), weight);

				if (pjSelector.getEtRelPhotonJets() != 0) {
					hists_[(prefix + "photonJetEtRel").c_str()]->Fill(pjSelector.getEtRelPhotonJets(), weight);
				}
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
			}
		}
	}
	/// everything that needs to be done during the event loop
	void analyze(const edm::EventBase& event);

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
	TH1F * qcdCorrectionHT_;
	pat::strbitset pjSelectorReturnsN1_;
	pat::strbitset pjSelectorReturnsPresel_;
	pat::strbitset pjSelectorReturns_;
	double evtCounter_, evtCounter100_, evtCounter200_, evtCounter350_, evtCounterPresel_, evtCounterWeighted_, evtCounterWeightedError_, evtCounterPreselWeighted_, evtCounterPreselWeightedError_;
	TFileDirectory *  fs_;
};


#endif /* SELECTIONANALYZER_H_ */
typedef edm::AnalyzerWrapper<SelectionAnalyzer> WrappedSelectionAnalyzer;
DEFINE_FWK_MODULE( WrappedSelectionAnalyzer);

typedef edm::FilterWrapper<PhotonJetSelector> WrappedPhotonJetFilter;
DEFINE_FWK_MODULE(WrappedPhotonJetFilter);
