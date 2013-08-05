#include <TImage.h>
#include <TError.h>
#include <vector>
#include <TFile.h>
#include <TROOT.h>
#include <TH1F.h>
#include <TGraphAsymmErrors.h>
#include <TObject.h>
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


TH1F * divideHistosForRatio(TH1F * sig, TH1F * bkg) {

  TH1F * cloneS = (TH1F *) sig->Clone( sig->GetTitle() );
  TH1F * cloneB = (TH1F *) bkg->Clone( bkg->GetTitle() );

  /*
  for( Int_t bin = 1; bin <= cloneB->GetNbinsX(); bin++ )
    cloneB->SetBinError( bin, 0. );    
  
  cloneS->Divide( cloneS, cloneB, 1, 1, "" );
  */

  for( Int_t bin = 1; bin <= cloneS->GetNbinsX(); bin++ ){

    Double_t sv = cloneS->GetBinContent(bin);
    Double_t se = cloneS->GetBinError(bin);

    Double_t bv = cloneB->GetBinContent(bin);

    Double_t rat = -1.;
    Double_t err =  0.;

    if( sv != 0. && bv != 0. ) {
      rat = sv / bv;
      // err = sqrt( sv / (bv*bv) );
      err = sqrt( se / (bv*bv) );
    }

    cloneS->SetBinContent( bin, rat );
    cloneS->SetBinError( bin, err );
  }

  return cloneS;
}


TH1F * getSystErrForRatio(TH1F * bkg) {

  TH1F * cloneB = (TH1F *) bkg->Clone( bkg->GetTitle() );

  for ( Int_t bin = 1; bin <= cloneB->GetNbinsX(); bin++ ) {
    Double_t relError = ( cloneB->GetBinError(bin) / cloneB->GetBinContent(bin) );

    cloneB->SetBinContent( bin, 1. );
    cloneB->SetBinError( bin, relError );
  }

  return cloneB;
}


void vs_PlotQCDcomp() {

  Bool_t saveC  = false;
  Bool_t diJets = true;
  Bool_t isMC   = false;

  TString vsSave;
  vsSave = "_T07w";

  TString jSave;
  if(diJets) jSave = "2j";
  else       jSave = "3j";

  TString sample;
  if(diJets) sample = "select_1ph_2jets";
  else       sample = "select_1ph_3jets";

  TString FOtag;
  if(isMC) FOtag = "_FO_CorrMC";
  //  else     FOtag = "_FO_Corr";
  else     FOtag = "_FO";

  TString sysu = "SYSTUP_";
  TString sysd = "SYSTDOWN_";

  TString outDir;
  outDir = "Plots_PhotonSusyAnalysis/QCDweights/";


  //  string inputFile1 = "/data/user/vsola/CMSSW_Releases/CMSSW_5_3_9/src/Plots_PhotonSusyAnalysis/Merged_QCD_PhotonJet_T07w_PAT/mergedHistos.root";
  //  string inputFile1 = "/data/user/vsola/CMSSW_Releases/CMSSW_5_3_9/src/Plots_PhotonSusyAnalysis/Merged_Data_V05w_PAT/mergedHistos.root";
  string inputFile1 = "/data/user/vsola/CMSSW_Releases/CMSSW_5_3_9/src/Plots_PhotonSusyAnalysis/PhotonHadReReco_22Jan2013_V05_PAT/mergedHistos.root";
  
  
  setMyTDRStyle();
  gROOT->SetStyle("mytdrStyle");
  
  //  gStyle->SetHistMinimumZero();
  //  gStyle->SetPaintTextFormat("4.2f");

  gStyle->SetHistLineWidth(2);
  gStyle->UseCurrentStyle();

  //  gStyle->SetPadTopMargin(1.0);
  //  gStyle->SetPadLeftMargin(3.2);
  //  gStyle->SetPadRightMargin(4.5);
  //  gStyle->SetPadBottomMargin(3.2);

  gROOT->ForceStyle(1);


  static const Int_t nHt  =  7;
  static const Int_t nPt  = 13;
  static const Int_t nMet = 16;
  static const Int_t nJet = 15;

  Double_t binPt[nPt+1]   = {0.,75.,90.,120.,160.,210.,260.,320.,400.,500.,650.,800.,1000.,1500.};
  Double_t binHt[nHt+1]   = {0.,400.,450.,550.,700.,900.,1200.,1500.};
  Double_t binMet[nMet+1] = {0.,10.,20.,30.,40.,50.,60.,70.,80.,90.,100.,120.,160.,200.,270.,350.,500.};
  Double_t binJet[nJet+1] = {0.,1.,2.,3.,4.,5.,6.,7.,8.,9.,10.,11.,12.,13.,14.,15};


  TLatex *as = new TLatex();
  as->SetNDC(true);
  as->SetTextColor(12);
  as->SetTextFont(43);
  as->SetTextSize(19);

  TLegend *legend = new TLegend(0.60, 0.70, 0.75, 0.85, "");
  legend->SetFillColor(10);
  legend->SetFillStyle(1001);
  legend->SetTextSize(0.04);
  legend->SetBorderSize(0);
  legend->SetShadowColor(0);

  std::string outLumi  = "CMS Work in Progress - QCD MC #sqrt{s} = 8 TeV - #geq 1 #gamma, #geq 2 j";

  TFile* f1 = TFile::Open( inputFile1.c_str() );

  //photon Pt
  TCanvas * cPt = new TCanvas("cPt","cPt");

  TH1F* hpt   = (TH1F*) f1->Get( sample+"/PreselCut_photonPt" );
  TH1F* hptFO = (TH1F*) f1->Get( sample+FOtag+"/PreselCut_photonPt" );

  TH1F *hptR = (TH1F*) hpt->Rebin(nPt,hpt->GetTitle(),binPt);
  if (hptR->GetSumw2N() == 0)
    hptR->Sumw2();

  TH1F *hptFOR = (TH1F*) hptFO->Rebin(nPt,hptFO->GetTitle(),binPt);
  if (hptFOR->GetSumw2N() == 0)
    hptFOR->Sumw2();

  TH1F* hptSU = (TH1F*) f1->Get( sample+FOtag+"/PreselCut_"+sysu+"photonPt" );
  TH1F* hptSD = (TH1F*) f1->Get( sample+FOtag+"/PreselCut_"+sysd+"photonPt" );

  TH1F *hptSUR = (TH1F*) hptSU->Rebin(nPt,hptSU->GetTitle(),binPt);
  if (hptSUR->GetSumw2N() == 0)
    hptSUR->Sumw2();

  TH1F *hptSDR = (TH1F*) hptSD->Rebin(nPt,hptSD->GetTitle(),binPt);
  if (hptSDR->GetSumw2N() == 0)
    hptSDR->Sumw2();

  if ( hptFOR != 0 ) {
    for (int b = 0; b < hptFOR->GetNbinsX(); b++) {

      Double_t mainHistoContent   = hptFOR->GetBinContent(b);
      Double_t systUpHistoContent = hptSUR->GetBinContent(b);
      Double_t systDnHistoContent = hptSDR->GetBinContent(b);
      Double_t systDiffUp = fabs( (double) systUpHistoContent - mainHistoContent );
      Double_t systDiffDn = fabs( (double) mainHistoContent - systDnHistoContent );

      // use average error for histogram
      Double_t systDiff = ( systDiffUp + systDiffDn ) / 2.;
      
      Double_t statErr   = hptFOR->GetBinError(b);
      Double_t combError = sqrt( systDiff * systDiff + statErr * statErr );
      hptFOR->SetBinError(b, combError);
    } //for
  }//if
    
  cPt->SetLogy(1);
  gPad->Update();
  cPt->Update();

  //  hptR->Scale(1,"width");
  //  hptR->SetMinimum(0.02);
  //  hptR->SetMaximum(1000); 
  hptR->GetXaxis()->SetTitle("1^{st} photon p_{T} [GeV]");
  hptR->GetYaxis()->SetTitle("Number of Events / GeV");

  if(isMC) hptR->SetMarkerSize(0);
  if(isMC) hptR->Draw("histE");
  else     hptR->Draw("E X0");


  hptFOR->SetMarkerSize(0);
  hptFOR->SetLineColor(2);
  hptFOR->SetFillColor(2);
  hptFOR->SetFillStyle(3004);
  hptFOR->Draw("same hist ][ E2");

  legend->Clear();
  if(isMC) legend->SetHeader("#gamma/QCD (Sim)");
  else     legend->SetHeader("#gamma/QCD (Data)");
  if(isMC) legend->AddEntry(hptR, "#gamma", "l");
  else     legend->AddEntry(hptR, "#gamma", "p");
  legend->AddEntry(hptFOR, "Pred (from #gamma_{jet})", "f");
  legend->Draw();

  as->DrawLatex(0.17, 0.93, outLumi.c_str() );
  cPt->Update();
  cPt->SetBottomMargin(0.2 + 0.8 * cPt->GetBottomMargin() - 0.2 * cPt->GetTopMargin());

  TPad *ratioPt = new TPad("BottomPad", "", 0, 0, 1, 1);
  ratioPt->SetTopMargin(0.8 - 0.8 * ratioPt->GetBottomMargin() + 0.2 * ratioPt->GetTopMargin());
  ratioPt->SetFillStyle(0);
  ratioPt->SetFrameFillColor(10);
  ratioPt->SetFrameBorderMode(0);
  ratioPt->Draw();

  ratioPt->cd();
  ratioPt->SetLogy(0);

  TH1F *hptRat = (TH1F*) divideHistosForRatio(hptR,hptFOR);
  hptRat->SetMinimum(0.);
  hptRat->SetMaximum(10.);
  hptRat->GetXaxis()->SetNdivisions(505);
  if(isMC) hptRat->GetYaxis()->SetTitle("Sim/Pred");
  else     hptRat->GetYaxis()->SetTitle("Data/Pred");
  hptRat->GetYaxis()->SetTitleSize(0.04);
  hptRat->GetYaxis()->SetLabelSize(0.03);
  hptRat->GetYaxis()->SetTitleOffset(1.3);
  hptRat->GetYaxis()->SetNdivisions(505);
  hptRat->SetMarkerStyle(20);
  hptRat->SetMarkerSize(1);
  hptRat->SetMarkerColor(1);
  hptRat->SetLineColor(1);
  hptRat->Draw("E X0");

  TH1F *hptFRat = (TH1F*) getSystErrForRatio(hptFOR);
  hptFRat->SetLineColor(2);
  hptFRat->SetFillColor(2);
  hptFRat->SetFillStyle(3004);
  hptFRat->Draw("same hist ][ E2");


  TLine * line = new TLine( hptRat->GetXaxis()->GetXmin(), 1., hptRat->GetXaxis()->GetXmax(), 1. );
  line->SetLineColor(1);
  line->SetLineWidth(0.5);
  line->SetLineStyle(1);
  line->Draw("same");

  hptR->GetXaxis()->SetLabelSize(0);
  hptR->GetXaxis()->SetTitle("");
  cPt->RedrawAxis();
  gPad->Update();
  cPt->Update();


  return;
}
