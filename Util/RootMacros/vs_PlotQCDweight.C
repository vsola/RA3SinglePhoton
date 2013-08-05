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

void vs_PlotQCDweight() {

  Bool_t saveC  = true;
  Bool_t diJets = true;
  Bool_t dj     = false;

  TString vsSave;
  vsSave = "_V05w";

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
  string inputFile1 = "/data/user/vsola/CMSSW_Releases/CMSSW_5_3_9/src/Plots_PhotonSusyAnalysis/Merged_Data_V05w_PAT/mergedHistos.root";
  
  
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

  
  static const Int_t ptb = 18;
  Double_t binPt[ptb+1] = {0.,70.,80.,90.,100.,120.,140.,160.,190.,220.,260.,300.,350.,400.,500.,650.,800.,1000.,1500.};
  /*
  //4k
  static const Int_t ptb = 12;
  Double_t binPt[ptb+1] = {0.,70.,80.,100.,140.,220.,300.,400.,500.,650.,800.,1000.,1500.};
  */

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

  // gamma & gamma_jet
  TCanvas * cWaj = new TCanvas("cWaj","cWaj",1200,900);
  cWaj->Clear();

  cWaj->Update();
  cWaj->cd();
  gPad->Update();
  gPad->SetLogx(0);
  gPad->SetLogy(1);

  TH1F* hpt = (TH1F*) f1->Get( sample+"/PreselCut_photonPtLowMet"+jj );
  
  TH1F *hptR = (TH1F*) hpt->Rebin(ptb,hpt->GetTitle(),binPt);
  if (hptR->GetSumw2N() == 0)
    hptR->Sumw2();
  
  hptR->GetXaxis()->SetRangeUser(70.,1500.);
  //  hptR->GetXaxis()->SetRangeUser(0.,1500.); //4k
  hptR->SetMinimum(0.1);
  //  hptR->SetMinimum(0.01);
  //  hptR->SetMaximum(500.);
  hptR->GetXaxis()->SetTitle("1^{st} Photon p_{T} [GeV]");
  hptR->GetYaxis()->SetTitle("Events / GeV");
  hptR->SetMarkerSize(0);
  hptR->Draw("histE");

  TH1F* hptFO = (TH1F*) f1->Get( sample+"_FO/PreselCut_photonPtLowMet"+jj );

  TH1F *hptFOR = (TH1F*) hptFO->Rebin(ptb,hptFO->GetTitle(),binPt);
  if (hptFOR->GetSumw2N() == 0)
    hptFOR->Sumw2();

  hptFOR->GetXaxis()->SetRangeUser(70.,1500.);
  //  hptFOR->GetXaxis()->SetRangeUser(70.,1500.); //4k
  hptFOR->SetLineWidth(3);
  hptFOR->SetLineStyle(2);
  hptFOR->SetLineColor(2);
  hptFOR->SetMarkerSize(0);
  hptFOR->Draw("same histE");

  /*
  hptFOR->Draw("histE");
  hptR->Draw("same histE");
  hptFOR->Draw("same histE");
  */

  TLegend *legend = new TLegend(0.65, 0.70, 0.75, 0.85, "");
  legend->SetFillColor(10);
  legend->SetFillStyle(1001);
  legend->SetTextSize(0.04);
  legend->SetBorderSize(0);
  legend->SetShadowColor(0);
  legend->SetHeader("#gamma/QCD (Sim.)");
  legend->AddEntry(hptR,"#gamma","l");
  legend->AddEntry(hptFOR,"#gamma_{jet}","l");
  legend->Draw();

  if(diJets){
    if (dj) as->DrawLatex(0.15, 0.93, outLumi2.c_str() );
    else    as->DrawLatex(0.15, 0.93, outLumi.c_str() );
  } else {
    as->DrawLatex(0.15, 0.93, outLumi3.c_str() );
  }

  cWaj->Update();

  if(saveC){
    cWaj->SaveAs(outDir+"c_pt_"+jSave+jj+vsSave+".eps");
    cWaj->SaveAs(outDir+"c_pt_"+jSave+jj+vsSave+".pdf");
  }
  
  // ratio inv
  TCanvas * cWcj = new TCanvas("cWcj","cWcj",1200,900);
  cWcj->Clear();

  cWcj->Update();
  cWcj->cd();
  gPad->Update();
  gPad->SetLogx(0);
  gPad->SetLogy(0);

  TH1F *hptWinv = new TH1F("hptWinv","hptWinv",ptb,binPt);
  if (hptWinv->GetSumw2N() == 0)
    hptWinv->Sumw2();

  TAxis *xaxisw = hptWinv->GetXaxis();
  
  for ( Int_t i=1; i<=xaxisw->GetNbins(); i++ ) {

    double valSig = hptFOR->GetBinContent(i);
    double valBkg = hptR->GetBinContent(i);

    double errSig = hptFOR->GetBinError(i);
    double errBkg = hptR->GetBinError(i);

    if (valSig != 0 && valBkg != 0) {
      double valDiv    = valSig / valBkg;

      double relErrSig = errSig / valSig;
      double relErrBkg = errBkg / valBkg;
      double relErrDiv = sqrt(pow(relErrSig, 2) + pow(relErrBkg, 2));
      double errDiv    = relErrDiv * valDiv;

      hptWinv->SetBinContent(i, valDiv);
      hptWinv->SetBinError(i, errDiv);
    } else {
      hptWinv->SetBinContent(i, 1.);
      hptWinv->SetBinError(i, 1.);
    }
  }    

  hptWinv->GetXaxis()->SetRangeUser(70.,1500.);
  //  hptWinv->SetMinimum(0.);
  //  hptWinv->SetMaximum(3.);
  hptWinv->GetXaxis()->SetTitle("1^{st} Photon p_{T} [GeV]");
  hptWinv->GetYaxis()->SetTitle("w^{-1}");
  hptWinv->SetLineColor(2);
  hptWinv->SetMarkerColor(2);
  hptWinv->SetMarkerSize(0);
  hptWinv->Draw("hist E");
  
  legend->Clear();
  legend->SetHeader("#gamma/QCD (Sim.)");
  legend->AddEntry(hptWinv,"#gamma_{jet}/#gamma","l");
  legend->Draw();

  if(diJets){
    if (dj) as->DrawLatex(0.15, 0.93, outLumir2.c_str() );
    else    as->DrawLatex(0.15, 0.93, outLumir.c_str() );
  } else {
    as->DrawLatex(0.15, 0.93, outLumir3.c_str() );
  }

  cWcj->Update();

  if(saveC){
    cWcj->SaveAs(outDir+"c_ptWinv_"+jSave+jj+vsSave+".eps");
    cWcj->SaveAs(outDir+"c_ptWinv_"+jSave+jj+vsSave+".pdf");
  }
  
  // ratio -> weight
  TCanvas * cWdj = new TCanvas("cWdj","cWdj",1200,900);
  cWdj->Clear();

  cWdj->Update();
  cWdj->cd();
  gPad->Update();
  gPad->SetLogx(0);
  gPad->SetLogy(0);

  TH1F *hptW = new TH1F("hptW","hptW",ptb,binPt);
  if (hptW->GetSumw2N() == 0)
    hptW->Sumw2();

  TAxis *xaxisW = hptW->GetXaxis();
  
  for ( Int_t i=1; i<=xaxisW->GetNbins(); i++ ) {
      
    double valSig = hptR->GetBinContent(i);
    double valBkg = hptFOR->GetBinContent(i);

    double errSig = hptR->GetBinError(i);
    double errBkg = hptFOR->GetBinError(i);

    if (valSig != 0 && valBkg != 0) {
      double valDiv    = valSig / valBkg;

      double relErrSig = errSig / valSig;
      double relErrBkg = errBkg / valBkg;
      double relErrDiv = sqrt(pow(relErrSig, 2) + pow(relErrBkg, 2));
      double errDiv    = relErrDiv * valDiv;

      hptW->SetBinContent(i, valDiv);
      hptW->SetBinError(i, errDiv);
    } else {
      hptW->SetBinContent(i, 1.);
      hptW->SetBinError(i, 1.);
    }
  } 

  hptW->GetXaxis()->SetRangeUser(70.,1500.);
  //  hptW->SetMinimum(-0.5);
  //  hptW->SetMaximum(2.5);
  hptW->GetXaxis()->SetTitle("1^{st} Photon p_{T} [GeV]");
  hptW->GetYaxis()->SetTitle("weight");
  hptW->SetLineColor(2);
  hptW->SetMarkerColor(2);
  hptW->SetMarkerSize(0);
  hptW->Draw("hist E");
  
  legend->Clear();
  legend->SetHeader("#gamma/QCD (Sim.)");
  legend->AddEntry(hptW,"#gamma/#gamma_{jet}","l");
  legend->Draw();

  if(diJets){
    if (dj) as->DrawLatex(0.15, 0.93, outLumiw2.c_str() );
    else    as->DrawLatex(0.15, 0.93, outLumiw.c_str() );
  } else {
    as->DrawLatex(0.15, 0.93, outLumiw3.c_str() );
  }

  cWdj->Update();

  if(saveC){
    cWdj->SaveAs(outDir+"c_ptW_"+jSave+jj+vsSave+".eps");
    cWdj->SaveAs(outDir+"c_ptW_"+jSave+jj+vsSave+".pdf");
    cWdj->SaveAs(outDir+"c_ptW_"+jSave+jj+vsSave+".root");
  }
   

  return;
}
