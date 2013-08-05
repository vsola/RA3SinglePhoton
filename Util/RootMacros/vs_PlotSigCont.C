#include <TKey.h>
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

void vs_PlotSigCont() {

  Bool_t saveC = true;

  TString vsSave;
  vsSave = "_Bino_1000_1420_v3";
  TString lSave;
  lSave = "";

  TString outDir;
  outDir = "Plots_PhotonSusyAnalysis/Signal/";
  
  string inputFile1 = "/data/user/vsola/CMSSW_Releases/CMSSW_5_3_9/src/Plots_PhotonSusyAnalysis/Merged_QCD_PhotonJet_T07w_PAT/mergedHistos.root";
  string inputFile2 = "/data/user/vsola/CMSSW_Releases/CMSSW_5_3_9/src/Plots_PhotonSusyAnalysis/Signal/histoSkimGGM_Bino_1000_1420.root";


  setMyTDRStyle();
  gROOT->SetStyle("mytdrStyle");

  gStyle->SetHistLineWidth(2);
  gStyle->UseCurrentStyle();
  gROOT->ForceStyle(1);


  std::vector<double> binEdges;
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
  binEdges.push_back(499);

  TLegend *legend = new TLegend(0.35, 0.65, 0.94, 0.87, "");
  legend->SetFillColor(10);
  legend->SetFillStyle(1001);
  legend->SetTextSize(0.04);
  legend->SetBorderSize(0);
  legend->SetShadowColor(0);


  TLatex *as = new TLatex();
  as->SetNDC(true);
  as->SetTextColor(12);
  as->SetTextFont(43);
  as->SetTextSize(20);
  //  std::string outLumi = "9.4 fb^{-1} #sqrt{s} = 8 TeV  #geq 1 #gamma, #geq 2 jets";
  std::string outLumi = "CMS Work in Progress - MC  #sqrt{s} = 8 TeV  #geq 1 #gamma, #geq 2 jets";


  TFile* f1 = TFile::Open( inputFile1.c_str() );
  TFile* f2 = TFile::Open( inputFile2.c_str() );


  //photon object
  TCanvas * cPh = new TCanvas("cPh","cPh");

  TH1F* hp1 = (TH1F*) f1->Get( "select_1ph_2jets/PreselCut_metPt" );
  TH1F* hp2 = (TH1F*) f2->Get( "select_1ph_2jets/PreselCut_metPt" );

  TH1F * hp1Rebin = (TH1F*) hp1->Rebin(binEdges.size() - 1, hp1->GetName(), &(binEdges.front()));
  TH1F * hp2Rebin = (TH1F*) hp2->Rebin(binEdges.size() - 1, hp2->GetName(), &(binEdges.front()));

  if (hp1Rebin->GetSumw2N() == 0)
    hp1Rebin->Sumw2();
  if (hp2Rebin->GetSumw2N() == 0)
    hp2Rebin->Sumw2();

  //  hp1Rebin->Add(hp2Rebin);
  hp2Rebin->Add(hp1Rebin);


  TH1F* hp1F = (TH1F*) f1->Get( "select_1ph_2jets_FO_CorrMC/PreselCut_metPt" );
  TH1F* hp2F = (TH1F*) f2->Get( "select_1ph_2jets_FO_CorrMC/PreselCut_metPt" );

  TH1F * hp1FRebin = (TH1F*) hp1F->Rebin(binEdges.size() - 1, hp1F->GetName(), &(binEdges.front()));
  TH1F * hp2FRebin = (TH1F*) hp2F->Rebin(binEdges.size() - 1, hp2F->GetName(), &(binEdges.front()));

  if (hp1FRebin->GetSumw2N() == 0)
    hp1FRebin->Sumw2();
  if (hp2FRebin->GetSumw2N() == 0)
    hp2FRebin->Sumw2();

  hp1FRebin->Add(hp2FRebin);


  cPh->SetLogy(1);

  gPad->Update();
  cPh->Update();

  //  hp1Rebin->Scale(1,"width");
  hp1Rebin->SetMinimum(0.001);
  hp1Rebin->SetMaximum(5000);
  //  hp1Rebin->GetXaxis()->SetRangeUser(0.,500.);
  
  hp1Rebin->SetMarkerSize(0);
  hp1Rebin->SetMarkerColor(1);
  hp1Rebin->SetLineColor(1);
  hp1Rebin->GetXaxis()->SetTitle("#slash{E}_{T} [GeV]");
  hp1Rebin->GetYaxis()->SetTitle("Number of Events / GeV");
  hp1Rebin->Draw("hist E");

  hp2Rebin->SetMarkerSize(0);
  hp2Rebin->SetMarkerColor(4);
  hp2Rebin->SetLineColor(4);
  hp2Rebin->Draw("same hist E");

  hp1FRebin->SetFillColor(2);
  hp1FRebin->SetLineColor(2);
  hp1FRebin->SetFillStyle(3005);
  hp1FRebin->SetMarkerSize(0);
  hp1FRebin->Draw("same hist ][ E2");
		
  hp2FRebin->SetFillColor(4);
  hp2FRebin->SetLineColor(4);
  hp2FRebin->SetFillStyle(3004);
  hp2FRebin->SetMarkerSize(0);
  hp2FRebin->Draw("same hist ][ E2");
		
  cPh->Update();

  legend->SetHeader("#gamma/QCD (Sim.)"+lSave);
  //  legend->AddEntry(hp1Rebin,"#gamma (#gamma/QCD + Signal)","l");
  legend->AddEntry(hp2Rebin,"#gamma (#gamma/QCD + Signal)","l");
  legend->AddEntry(hp1Rebin,"#gamma (#gamma/QCD)","l");
  legend->AddEntry(hp1FRebin,"Pred. (#gamma/QCD + Signal)","f");
  legend->AddEntry(hp2FRebin,"Pred. (Signal)","f");
  //  legend->AddEntry(hp2Rebin,"#gamma (Signal)","l");
  //  legend->AddEntry(hp1FRebin,"Pred. (#gamma/QCD)","f");

  legend->Draw();
  as->DrawLatex(0.18, 0.92, outLumi.c_str() );

  cPh->Update();
  /*
  cPh->SetBottomMargin(0.2 + 0.8 * cPh->GetBottomMargin() - 0.2 * cPh->GetTopMargin());


  TPad *ratioPad = new TPad("BottomPad", "", 0, 0, 1, 1);
  ratioPad->SetTopMargin(0.8 - 0.8 * ratioPad->GetBottomMargin() + 0.2 * ratioPad->GetTopMargin());
  ratioPad->SetFillStyle(0);
  ratioPad->SetFrameFillColor(10);
  ratioPad->SetFrameBorderMode(0);

  ratioPad->Draw();
  ratioPad->cd();
  ratioPad->SetLogy(0);

  TH1F *hpRatio = (TH1F*)hp1Rebin->Clone("hpRatio");
  hpRatio->Divide(hp2Rebin,hp1Rebin,1,1);
  hpRatio->SetMinimum(0.);
  hpRatio->SetMaximum(2.);
  hpRatio->GetXaxis()->SetNdivisions(505);
  hpRatio->GetYaxis()->SetTitle("oldIso/newIso");
  //  hpRatio->GetYaxis()->SetTitle("");
  hpRatio->GetYaxis()->SetTitleSize(0.03);
  hpRatio->GetYaxis()->SetLabelSize(0.03);
  hpRatio->GetYaxis()->SetNdivisions(503);
  hpRatio->SetMarkerStyle(20);
  hpRatio->SetMarkerSize(1);
  hpRatio->SetMarkerColor(1);
  hpRatio->SetLineColor(1);
  hpRatio->Draw("E X0");

  TLine * line = new TLine(hpRatio->GetXaxis()->GetXmin(), 1, hpRatio->GetXaxis()->GetXmax(), 1);
  line->SetLineColor(1);
  line->SetLineWidth(0.5);
  line->SetLineStyle(2);
  line->Draw("same");

  hp1Rebin->GetXaxis()->SetLabelSize(0);
  hp1Rebin->GetXaxis()->SetTitle("");
  cPh->RedrawAxis();

  gPad->Update();
  cPh->Update();
  */

  if(saveC){
    cPh->SaveAs(outDir+"c_SigContQCD"+vsSave+".eps");
    cPh->SaveAs(outDir+"c_SigContQCD"+vsSave+".pdf");
  }


  return;
}
