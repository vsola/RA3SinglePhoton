//photonPtVsHthltLowMet
//photonPtVsHthltLowMet2j

#include <TKey.h>
#include <TImage.h>
#include <TError.h>
#include <vector>
#include <TFile.h>
#include <TROOT.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TAxis.h>
#include <TLine.h>
#include <TGraphAsymmErrors.h>
#include <TObject.h>
#include <TExec.h>
#include <Util/OwnUtil/src/HistoDrawUtil.h>
#include <iostream>
#include <utility>
#include <cmath>
#include <cstdlib>
#include <TMath.h>
#include <TLegend.h>
#include <TLegendEntry.h>

using namespace HistoDrawUtil;
using namespace std;

void vs_PlotQCDweight2D() {

  Bool_t saveC  = false;
  Bool_t diJets = true;
  Bool_t dj     = false;

  Bool_t isData = true;

  TString vsSave;
  if(isData)
    vsSave = "_Data_V05";
  else
    vsSave = "_T07";

  TString jSave;
  if(diJets) jSave = "2j";
  else       jSave = "3j";

  TString jj;
  if(dj) jj = "2j";
  else   jj = "";

  TString sample;
  if(diJets) sample = "select_1ph_2jets";
  else       sample = "select_1ph_3jets";

  TString outDir;
  outDir = "Plots_PhotonSusyAnalysis/QCDweights/";


  //  string inputFile1 = "/data/user/vsola/CMSSW_Releases/CMSSW_5_3_9/src/Plots_PhotonSusyAnalysis/Merged_QCD_PhotonJet_T07_PAT/mergedHistos.root";
  string inputFile1 = "/data/user/vsola/CMSSW_Releases/CMSSW_5_3_9/src/Plots_PhotonSusyAnalysis/PhotonHadReReco_22Jan2013_V05_PAT/mergedHistos.root";
  
  
  setMyTDRStyle();
  gROOT->SetStyle("mytdrStyle");
  

  gStyle->SetHistMinimumZero();
  gStyle->SetPaintTextFormat("4.2f");

  gStyle->SetHistLineWidth(2);
  gStyle->UseCurrentStyle();

  //  gStyle->SetPadTopMargin(1.0);
  //  gStyle->SetPadLeftMargin(3.2);
  gStyle->SetPadRightMargin(4.5);
  //  gStyle->SetPadBottomMargin(3.2);

  gROOT->ForceStyle(1);

  Double_t binPt[13] = {0.,70.,80.,100.,140.,220.,300.,400.,500.,650.,800.,1000.,1500.};
  Double_t binHt[8]  = {0.,400.,450.,550.,700.,900.,1200.,1500.};

  TLatex *as = new TLatex();
  as->SetNDC(true);
  as->SetTextColor(12);
  as->SetTextFont(43);
  as->SetTextSize(28);

  std::string outLumi  = "CMS Work in Progress - QCD MC #sqrt{s} = 8 TeV - #geq 1 #gamma, #geq 2 j, #slash{E}_{T} < 100 GeV";
  std::string outLumi2 = "CMS Work in Progress - QCD MC #sqrt{s} = 8 TeV - #geq 1 #gamma, = 2 j, #slash{E}_{T} < 100 GeV";
  std::string outLumi3 = "CMS Work in Progress - QCD MC #sqrt{s} = 8 TeV - #geq 1 #gamma, #geq 3 j, #slash{E}_{T} < 100 GeV";

  std::string outLumij  = "CMS Work in Progress - QCD MC #sqrt{s} = 8 TeV - #geq 1 #gamma_{jet}, #geq 2 j, #slash{E}_{T} < 100 GeV";
  std::string outLumij2 = "CMS Work in Progress - QCD MC #sqrt{s} = 8 TeV - #geq 1 #gamma_{jet}, = 2 j, #slash{E}_{T} < 100 GeV";
  std::string outLumij3 = "CMS Work in Progress - QCD MC #sqrt{s} = 8 TeV - #geq 1 #gamma_{jet}, #geq 3 j, #slash{E}_{T} < 100 GeV";

  std::string outLumir  = "CMS Work in Progress - QCD MC #sqrt{s} = 8 TeV - #gamma_{jet}/#gamma , #geq 2 j, #slash{E}_{T} < 100 GeV";
  std::string outLumir2 = "CMS Work in Progress - QCD MC #sqrt{s} = 8 TeV - #gamma_{jet}/#gamma , = 2 j, #slash{E}_{T} < 100 GeV";
  std::string outLumir3 = "CMS Work in Progress - QCD MC #sqrt{s} = 8 TeV - #gamma_{jet}/#gamma , #geq 3 j, #slash{E}_{T} < 100 GeV";

  std::string outLumiw  = "CMS Work in Progress - QCD MC #sqrt{s} = 8 TeV - #gamma/#gamma_{jet} , #geq 2 j, #slash{E}_{T} < 100 GeV";
  std::string outLumiw2 = "CMS Work in Progress - QCD MC #sqrt{s} = 8 TeV - #gamma/#gamma_{jet} , = 2 j, #slash{E}_{T} < 100 GeV";
  std::string outLumiw3 = "CMS Work in Progress - QCD MC #sqrt{s} = 8 TeV - #gamma/#gamma_{jet} , #geq 3 j, #slash{E}_{T} < 100 GeV";

  TFile* f1 = TFile::Open( inputFile1.c_str() );

  // gamma
  TCanvas * cWaj = new TCanvas("cWaj","cWaj",1200,900);
  cWaj->Clear();

  cWaj->Update();
  cWaj->cd();
  gPad->Update();
  gPad->SetLogx(1);
  gPad->SetLogy(0);

  TH2F* hptht = (TH2F*) f1->Get( sample+"/PreselCut_photonPtVsHthltLowMet"+jj );
  
  TH2F *hpthtR = new TH2F("hpthtR",hptht->GetTitle(),12,binPt,7,binHt);
  if (hpthtR->GetSumw2N() == 0)
    hpthtR->Sumw2();
  

  TH2F* hpthtEL = (TH2F*) f1->Get( sample+"_PixelSeedCorr/PreselCut_photonPtVsHthltLowMet"+jj );
  
  TH2F *hpthtELR = new TH2F("hpthtELR",hpthtEL->GetTitle(),12,binPt,7,binHt);
  if (hpthtELR->GetSumw2N() == 0)
    hpthtELR->Sumw2();
  
  if(isData)
    hpthtR->Add(hpthtR,hpthtELR,1.,-1.);

  TAxis *xaxis = hptht->GetXaxis();
  TAxis *yaxis = hptht->GetYaxis();
  
  for ( Int_t j=1; j<=yaxis->GetNbins(); j++ ) {
    for ( Int_t i=1; i<=xaxis->GetNbins(); i++ ) {
      hpthtR->Fill(xaxis->GetBinCenter(i),yaxis->GetBinCenter(j),hptht->GetBinContent(i,j));
    }
  }
  /*
  for ( Int_t j=1; j<=7; j++ ) {
    for ( Int_t i=1; i<=11; i++ ) {
      cout << hpthtR->GetBinContent(i,j) << endl;
    }
  }
  */
  hpthtR->GetXaxis()->SetRangeUser(80.,1500.);
  hpthtR->GetYaxis()->SetRangeUser(450.,1500.);
  hpthtR->SetMinimum(0.);
  hpthtR->SetMaximum(200.);
  hpthtR->GetXaxis()->SetTitle("1^{st} Photon p_{T} [GeV]");
  hpthtR->GetYaxis()->SetTitle("H_{T} [GeV]");
  hpthtR->Draw("colz text");
  
  if(diJets){
    if (dj) as->DrawLatex(0.15, 0.93, outLumi2.c_str() );
    else    as->DrawLatex(0.15, 0.93, outLumi.c_str() );
  } else {
    as->DrawLatex(0.15, 0.93, outLumi3.c_str() );
  }

  cWaj->Update();

  if(saveC){
    cWaj->SaveAs(outDir+"c_ptht_"+jSave+jj+vsSave+".eps");
    cWaj->SaveAs(outDir+"c_ptht_"+jSave+jj+vsSave+".pdf");
  }

  // gamma_jet
  TCanvas * cWbj = new TCanvas("cWbj","cWbj",1200,900);
  cWbj->Clear();

  cWbj->Update();
  cWbj->cd();
  gPad->Update();
  gPad->SetLogx(1);
  gPad->SetLogy(0);

  TH2F* hpthtFO = (TH2F*) f1->Get( sample+"_FO/PreselCut_photonPtVsHthltLowMet"+jj );
  
  TH2F *hpthtFOR = new TH2F("hpthtFOR",hpthtFO->GetTitle(),12,binPt,7,binHt);
  if (hpthtFOR->GetSumw2N() == 0)
    hpthtFOR->Sumw2();
  
  TAxis *xaxisf = hpthtFO->GetXaxis();
  TAxis *yaxisf = hpthtFO->GetYaxis();
  
  for ( Int_t j=1; j<=yaxisf->GetNbins(); j++ ) {
    for ( Int_t i=1; i<=xaxisf->GetNbins(); i++ ) {
      hpthtFOR->Fill(xaxisf->GetBinCenter(i),yaxisf->GetBinCenter(j),hpthtFO->GetBinContent(i,j));
    }
  }
  
  hpthtFOR->GetXaxis()->SetRangeUser(80.,1500.);
  hpthtFOR->GetYaxis()->SetRangeUser(450.,1500.);
  hpthtFOR->SetMinimum(0.);
  hpthtFOR->SetMaximum(200.);
  hpthtFOR->GetXaxis()->SetTitle("1^{st} Photon p_{T} [GeV]");
  hpthtFOR->GetYaxis()->SetTitle("H_{T} [GeV]");
  hpthtFOR->Draw("colz text");
  
  if(diJets){
    if (dj) as->DrawLatex(0.15, 0.93, outLumij2.c_str() );
    else    as->DrawLatex(0.15, 0.93, outLumij.c_str() );
  } else {
    as->DrawLatex(0.15, 0.93, outLumij3.c_str() );
  }

  cWbj->Update();

  if(saveC){
    cWbj->SaveAs(outDir+"c_pthtFO_"+jSave+jj+vsSave+".eps");
    cWbj->SaveAs(outDir+"c_pthtFO_"+jSave+jj+vsSave+".pdf");
  }

  // ratio inv
  TCanvas * cWcj = new TCanvas("cWcj","cWcj",1200,900);
  cWcj->Clear();

  cWcj->Update();
  cWcj->cd();
  gPad->Update();
  gPad->SetLogx(1);
  gPad->SetLogy(0);

  TH2F *hpthtWinv = new TH2F("hpthtWinv","hpthtWinv",12,binPt,7,binHt);
  if (hpthtWinv->GetSumw2N() == 0)
    hpthtWinv->Sumw2();

  TAxis *xaxisw = hpthtWinv->GetXaxis();
  TAxis *yaxisw = hpthtWinv->GetYaxis();
  
  for ( Int_t j=1; j<=yaxisw->GetNbins(); j++ ) {
    for ( Int_t i=1; i<=xaxisw->GetNbins(); i++ ) {

      double valSig = hpthtFOR->GetBinContent(i,j);
      double valBkg = hpthtR->GetBinContent(i,j);

      double errSig = hpthtFOR->GetBinError(i,j);
      double errBkg = hpthtR->GetBinError(i,j);

      if (valSig != 0 && valBkg != 0) {
	double valDiv    = valSig / valBkg;

	double relErrSig = errSig / valSig;
	double relErrBkg = errBkg / valBkg;
	double relErrDiv = sqrt(pow(relErrSig, 2) + pow(relErrBkg, 2));
	double errDiv    = relErrDiv * valDiv;

	hpthtWinv->SetBinContent(i, j, valDiv);
	hpthtWinv->SetBinError(i, j, errDiv);
      } else {
	hpthtWinv->SetBinContent(i, j, 1.);
	hpthtWinv->SetBinError(i, j, 1.);
      }
    } 
  } 

  hpthtWinv->GetXaxis()->SetRangeUser(80.,1500.);
  hpthtWinv->GetYaxis()->SetRangeUser(450.,1500.);
  hpthtWinv->SetMinimum(0.);
  hpthtWinv->SetMaximum(3.);
  hpthtWinv->GetXaxis()->SetTitle("1^{st} Photon p_{T} [GeV]");
  hpthtWinv->GetYaxis()->SetTitle("H_{T} [GeV]");
  hpthtWinv->Draw("colz text");
  
  if(diJets){
    if (dj) as->DrawLatex(0.15, 0.93, outLumir2.c_str() );
    else    as->DrawLatex(0.15, 0.93, outLumir.c_str() );
  } else {
    as->DrawLatex(0.15, 0.93, outLumir3.c_str() );
  }

  cWcj->Update();

  if(saveC){
    cWcj->SaveAs(outDir+"c_pthtWinv_"+jSave+jj+vsSave+".eps");
    cWcj->SaveAs(outDir+"c_pthtWinv_"+jSave+jj+vsSave+".pdf");
  }

  // ratio -> weight
  TCanvas * cWdj = new TCanvas("cWdj","cWdj",1200,900);
  cWdj->Clear();

  cWdj->Update();
  cWdj->cd();
  gPad->Update();
  gPad->SetLogx(1);
  gPad->SetLogy(0);

  TH2F *hpthtW = new TH2F("hpthtW","hpthtW",12,binPt,7,binHt);
  if (hpthtW->GetSumw2N() == 0)
    hpthtW->Sumw2();

  TAxis *xaxisW = hpthtW->GetXaxis();
  TAxis *yaxisW = hpthtW->GetYaxis();
  
  for ( Int_t j=1; j<=yaxisW->GetNbins(); j++ ) {
    for ( Int_t i=1; i<=xaxisW->GetNbins(); i++ ) {
      
      double valSig = hpthtR->GetBinContent(i,j);
      double valBkg = hpthtFOR->GetBinContent(i,j);

      double errSig = hpthtR->GetBinError(i,j);
      double errBkg = hpthtFOR->GetBinError(i,j);

      if (valSig != 0 && valBkg != 0) {
	double valDiv    = valSig / valBkg;

	double relErrSig = errSig / valSig;
	double relErrBkg = errBkg / valBkg;
	double relErrDiv = sqrt(pow(relErrSig, 2) + pow(relErrBkg, 2));
	double errDiv    = relErrDiv * valDiv;

	hpthtW->SetBinContent(i, j, valDiv);
	hpthtW->SetBinError(i, j, errDiv);
      } else {
	hpthtW->SetBinContent(i, j, 1.);
	hpthtW->SetBinError(i, j, 1.);
	//	hpthtW->SetBinError(i, j, 1.14);
      }
    } 
  } 

  hpthtW->GetXaxis()->SetRangeUser(80.,1500.);
  hpthtW->GetYaxis()->SetRangeUser(450.,1500.);
  hpthtW->SetMinimum(0.);
  hpthtW->SetMaximum(10.);
  hpthtW->GetXaxis()->SetTitle("1^{st} Photon p_{T} [GeV]");
  hpthtW->GetYaxis()->SetTitle("H_{T} [GeV]");
  hpthtW->Draw("colz text");
  
  if(diJets){
    if (dj) as->DrawLatex(0.15, 0.93, outLumiw2.c_str() );
    else    as->DrawLatex(0.15, 0.93, outLumiw.c_str() );
  } else {
    as->DrawLatex(0.15, 0.93, outLumiw3.c_str() );
  }

  cWdj->Update();

  if(saveC){
    cWdj->SaveAs(outDir+"c_pthtW_"+jSave+jj+vsSave+".eps");
    cWdj->SaveAs(outDir+"c_pthtW_"+jSave+jj+vsSave+".pdf");
    cWdj->SaveAs(outDir+"c_pthtW_"+jSave+jj+vsSave+".root");
  }


  return;
}
