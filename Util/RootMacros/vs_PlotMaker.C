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
void vs_PlotMaker() {

  Bool_t saveC = false;

  TString vsSave;
  vsSave = "_V18Ab";
  TString lSave;
  lSave = " - V18Ab";

  TString outDir;
  outDir = "Plots_PhotonSusyAnalysis/pTweight/photonPt/";

  /*
  //  string inputFile1 = "/data/user/vsola/CMSSW_Releases/CMSSW_5_3_2_patch1/src/Plots_PhotonSusyAnalysis/Merged_Data_V03w_PAT/mergedHistos.root";
  string inputFile1 = "/data/user/vsola/CMSSW_Releases/CMSSW_5_3_5/src/Plots_PhotonSusyAnalysis/Merged_Data_V05bw_PAT/mergedHistos.root";
  string inputFile2 = "/data/user/vsola/CMSSW_Releases/CMSSW_5_3_5/src/Plots_PhotonSusyAnalysis/Merged_Data_V07b_PAT/mergedHistos.root";
  */
  
  //  string inputFile1 = "/data/user/vsola/CMSSW_Releases/CMSSW_5_3_2_patch1/src/Plots_PhotonSusyAnalysis/PhotonHadPromptReco_2012A_V03w_PAT/mergedHistos.root";
  string inputFile1 = "/data/user/vsola/CMSSW_Releases/CMSSW_5_3_5/src/Plots_PhotonSusyAnalysis/PhotonHadPromptReco_2012A_V14b_PAT/mergedHistos.root";
  string inputFile2 = "/data/user/vsola/CMSSW_Releases/CMSSW_5_3_5/src/Plots_PhotonSusyAnalysis/PhotonHadPromptReco_2012A_V18b_PAT/mergedHistos.root";
  //  string inputFile1 = "/data/user/vsola/CMSSW_Releases/CMSSW_5_3_5/src/Plots_PhotonSusyAnalysis/PhotonHadPromptReco_2012A_V09test1_PAT/mergedHistos.root";
  //  string inputFile2 = "/data/user/vsola/CMSSW_Releases/CMSSW_5_3_5/src/Plots_PhotonSusyAnalysis/PhotonHadPromptReco_2012A_V09test3_PAT/mergedHistos.root";
  
  

  setMyTDRStyle();
  gROOT->SetStyle("mytdrStyle");

  gStyle->SetHistLineWidth(2);
  gStyle->UseCurrentStyle();
  gROOT->ForceStyle(1);


  std::vector<double> binEdges;
  binEdges.clear();
  binEdges.push_back(0);
  binEdges.push_back(5);
  binEdges.push_back(75);
  binEdges.push_back(85);
  binEdges.push_back(95);
  binEdges.push_back(105);
  binEdges.push_back(115);
  binEdges.push_back(125);
  binEdges.push_back(140);
  binEdges.push_back(160);
  binEdges.push_back(190);
  binEdges.push_back(220);
  binEdges.push_back(260);
  binEdges.push_back(300);
  binEdges.push_back(400);
  binEdges.push_back(500);
  binEdges.push_back(650);
  binEdges.push_back(800);
  binEdges.push_back(1000);
  binEdges.push_back(1500);

  
  TLegend *legend = new TLegend(0.5, 0.71, 0.94, 0.87, "");
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
  std::string outLumi = "9.4 fb^{-1} #sqrt{s} = 8 TeV  #geq 1 #gamma, #geq 2 jets";
  //  std::string outLumi = "CMS Work in Progress - 9.4 fb^{-1} #sqrt{s} = 8 TeV  #geq 1 #gamma, #geq 2 jets";

  
  //  TFile * f1 = new TFile( "/data/user/vsola/CMSSW_Releases/CMSSW_5_3_2_patch1/src/Plots_PhotonSusyAnalysis/Merged_Data_V03w_PAT/mergedHistos.root", "Read" );

  TFile* f1 = TFile::Open( inputFile1.c_str() );
  TFile* f2 = TFile::Open( inputFile2.c_str() );


  //photon object
  TCanvas * cPh = new TCanvas("cPh","cPh");

  TH1F* hp1 = (TH1F*) f1->Get( "select_1ph_2jets/PreselCut_photonPt" );
  TH1F* hp2 = (TH1F*) f2->Get( "select_1ph_2jets/PreselCut_photonPt" );

  
  cPh->SetLogy(1);

  gPad->Update();
  cPh->Update();


  TH1F * hp1Rebin = (TH1F*) hp1->Rebin(binEdges.size() - 1, hp1->GetName(), &(binEdges.front()));
  TH1F * hp2Rebin = (TH1F*) hp2->Rebin(binEdges.size() - 1, hp2->GetName(), &(binEdges.front()));

  if (hp1Rebin->GetSumw2N() == 0)
    hp1Rebin->Sumw2();
  if (hp2Rebin->GetSumw2N() == 0)
    hp2Rebin->Sumw2();

  hp1Rebin->Scale(1,"width");
  hp1Rebin->SetMinimum(0.02);
  hp1Rebin->SetMaximum(5000);
  hp1Rebin->SetMarkerStyle(20);
  hp1Rebin->SetMarkerSize(1.1);
  hp1Rebin->SetMarkerColor(2);
  hp1Rebin->SetLineColor(2);
  hp1Rebin->Draw("E X0");

  hp1Rebin->GetXaxis()->SetRangeUser(50.,1500.);
  hp1Rebin->GetXaxis()->SetTitle("1st Photon p_{T} [GeV]");
  hp1Rebin->GetYaxis()->SetTitle("Number of Events / GeV");
  hp1Rebin->Draw("E X0");

  hp2Rebin->Scale(1,"width");
  hp2Rebin->GetXaxis()->SetRangeUser(50.,1500.);
  hp2Rebin->SetMarkerStyle(21);
  hp2Rebin->SetMarkerSize(0.9);
  hp2Rebin->SetMarkerColor(4);
  hp2Rebin->SetLineColor(4);
  hp2Rebin->Draw("E X0 same");

  cPh->Update();

  legend->SetHeader("Data"+lSave);
  legend->AddEntry(hp1Rebin,"#gamma - 532p1","p");
  legend->AddEntry(hp2Rebin,"#gamma - 535","p");
  //  legend->AddEntry(hp1Rebin,"#gamma - CMSSW_532p1","p");
  //  legend->AddEntry(hp2Rebin,"#gamma - CMSSW_535","p");

  legend->Draw();
  as->DrawLatex(0.45, 0.92, outLumi.c_str() );
  //  as->DrawLatex(0.16, 0.92, outLumi.c_str() );

  cPh->Update();

  cPh->SetBottomMargin(0.2 + 0.8 * cPh->GetBottomMargin() - 0.2 * cPh->GetTopMargin());
  //  cPh->Update();

  double bla1 = 0.2 + 0.8 * cPh->GetBottomMargin() - 0.2 * cPh->GetTopMargin();
  cout << bla1 << endl;

  TPad *ratioPad = new TPad("BottomPad", "", 0, 0, 1, 1);
  ratioPad->SetTopMargin(0.8 - 0.8 * ratioPad->GetBottomMargin() + 0.2 * ratioPad->GetTopMargin());
  ratioPad->SetFillStyle(0);
  ratioPad->SetFrameFillColor(10);
  ratioPad->SetFrameBorderMode(0);

  double bla2 = 0.8 - 0.8 * ratioPad->GetBottomMargin() + 0.2 * ratioPad->GetTopMargin();
  cout << bla2 << endl;

  ratioPad->Draw();
  ratioPad->cd();
  ratioPad->SetLogy(0);

  TH1F *hpRatio = (TH1F*)hp1Rebin->Clone("hpRatio");
  hpRatio->Divide(hp2Rebin,hp1Rebin,1,1);
  hpRatio->SetMinimum(0.5);
  hpRatio->SetMaximum(1.5);
  hpRatio->GetYaxis()->SetTitle("535/532p1");
  //  hpRatio->GetYaxis()->SetTitle("");
  hpRatio->GetYaxis()->SetTitleSize(0.03);
  hpRatio->GetYaxis()->SetLabelSize(0.03);
  hpRatio->GetYaxis()->SetNdivisions(503);
  //  hpRatio->GetXaxis()->SetNdivisions(505);
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

  if(saveC){
    cPh->SaveAs(outDir+"c_PhotonPtComp"+vsSave+".eps");
    cPh->SaveAs(outDir+"c_PhotonPtComp"+vsSave+".pdf");
  }


  //photon FO object
  TCanvas * cPhFO = new TCanvas("cPhFO","cPhFO");

  TH1F* hpFO1 = (TH1F*) f1->Get( "select_1ph_2jets_FO/PreselCut_photonPt" );
  TH1F* hpFO2 = (TH1F*) f2->Get( "select_1ph_2jets_FO/PreselCut_photonPt" );

  
  cPhFO->SetLogy(1);

  gPad->Update();
  cPhFO->Update();


  TH1F * hpFO1Rebin = (TH1F*) hpFO1->Rebin(binEdges.size() - 1, hpFO1->GetName(), &(binEdges.front()));
  TH1F * hpFO2Rebin = (TH1F*) hpFO2->Rebin(binEdges.size() - 1, hpFO2->GetName(), &(binEdges.front()));

  if (hpFO1Rebin->GetSumw2N() == 0)
    hpFO1Rebin->Sumw2();
  if (hp2Rebin->GetSumw2N() == 0)
    hpFO2Rebin->Sumw2();

  hpFO1Rebin->Scale(1,"width");
  hpFO1Rebin->SetMinimum(0.02);
  hpFO1Rebin->SetMaximum(5000);
  hpFO1Rebin->SetMarkerStyle(24);
  hpFO1Rebin->SetMarkerSize(1.1);
  hpFO1Rebin->SetMarkerColor(2);
  hpFO1Rebin->SetLineColor(2);
  hpFO1Rebin->Draw("E X0");

  hpFO1Rebin->GetXaxis()->SetRangeUser(50.,1500.);
  hpFO1Rebin->GetXaxis()->SetTitle("1st Photon p_{T} [GeV]");
  hpFO1Rebin->GetYaxis()->SetTitle("Number of Events / GeV");
  hpFO1Rebin->Draw("E X0");

  hpFO2Rebin->Scale(1,"width");
  hpFO2Rebin->GetXaxis()->SetRangeUser(50.,1500.);
  hpFO2Rebin->SetMarkerStyle(25);
  hpFO2Rebin->SetMarkerSize(0.9);
  hpFO2Rebin->SetMarkerColor(4);
  hpFO2Rebin->SetLineColor(4);
  hpFO2Rebin->Draw("E X0 same");

  cPhFO->Update();

  legend->Clear();
  legend->SetHeader("Data"+lSave);
  legend->AddEntry(hpFO1Rebin,"#gamma_{jet} Uncor - 532p1","p");
  legend->AddEntry(hpFO2Rebin,"#gamma_{jet} Uncor - 535","p");

  legend->Draw();
  as->DrawLatex(0.45, 0.92, outLumi.c_str() );
  //  as->DrawLatex(0.16, 0.92, outLumi.c_str() );

  cPhFO->Update();

  cPhFO->SetBottomMargin(0.2 + 0.8 * cPhFO->GetBottomMargin() - 0.2 * cPhFO->GetTopMargin());


  TPad *ratioPadFO = new TPad("BottomPadFO", "", 0, 0, 1, 1);
  ratioPadFO->SetTopMargin(0.8 - 0.8 * ratioPadFO->GetBottomMargin() + 0.2 * ratioPadFO->GetTopMargin());
  ratioPadFO->SetFillStyle(0);
  ratioPadFO->SetFrameFillColor(10);
  ratioPadFO->SetFrameBorderMode(0);

  ratioPadFO->Draw();
  ratioPadFO->cd();
  ratioPadFO->SetLogy(0);

  TH1F *hpRatioFO = (TH1F*)hpFO1Rebin->Clone("hpRatioFO");
  hpRatioFO->Divide(hpFO2Rebin,hpFO1Rebin,1,1);
  hpRatioFO->SetMinimum(0.5);
  hpRatioFO->SetMaximum(1.5);
  hpRatioFO->GetYaxis()->SetTitle("535/532p1");
  hpRatioFO->GetYaxis()->SetTitleSize(0.03);
  hpRatioFO->GetYaxis()->SetLabelSize(0.03);
  hpRatioFO->GetYaxis()->SetNdivisions(503);
  hpRatioFO->SetMarkerStyle(20);
  hpRatioFO->SetMarkerSize(1);
  hpRatioFO->SetMarkerColor(1);
  hpRatioFO->SetLineColor(1);
  hpRatioFO->Draw("E X0");

  line->Draw("same");

  hpFO1Rebin->GetXaxis()->SetLabelSize(0);
  hpFO1Rebin->GetXaxis()->SetTitle("");
  cPhFO->RedrawAxis();

  gPad->Update();
  cPhFO->Update();

  if(saveC){
    cPhFO->SaveAs(outDir+"c_PhotonPtFOComp"+vsSave+".eps");
    cPhFO->SaveAs(outDir+"c_PhotonPtFOComp"+vsSave+".pdf");
  }


  //photon FO Corr object
  TCanvas * cPhFOCor = new TCanvas("cPhFOCor","cPhFOCor");

  TH1F* hpFOCor1 = (TH1F*) f1->Get( "select_1ph_2jets_FO_Corr/PreselCut_photonPt" );
  TH1F* hpFOCor2 = (TH1F*) f2->Get( "select_1ph_2jets_FO_Corr/PreselCut_photonPt" );

  
  cPhFOCor->SetLogy(1);

  gPad->Update();
  cPhFOCor->Update();


  TH1F * hpFOCor1Rebin = (TH1F*) hpFOCor1->Rebin(binEdges.size() - 1, hpFOCor1->GetName(), &(binEdges.front()));
  TH1F * hpFOCor2Rebin = (TH1F*) hpFOCor2->Rebin(binEdges.size() - 1, hpFOCor2->GetName(), &(binEdges.front()));

  if (hpFOCor1Rebin->GetSumw2N() == 0)
    hpFOCor1Rebin->Sumw2();
  if (hp2Rebin->GetSumw2N() == 0)
    hpFOCor2Rebin->Sumw2();

  hpFOCor1Rebin->Scale(1,"width");
  hpFOCor1Rebin->SetMinimum(0.02);
  hpFOCor1Rebin->SetMaximum(5000);
  hpFOCor1Rebin->SetMarkerStyle(26);
  hpFOCor1Rebin->SetMarkerSize(1);
  hpFOCor1Rebin->SetMarkerColor(2);
  hpFOCor1Rebin->SetLineColor(2);
  hpFOCor1Rebin->Draw("E X0");

  hpFOCor1Rebin->GetXaxis()->SetRangeUser(50.,1500.);
  hpFOCor1Rebin->GetXaxis()->SetTitle("1st Photon p_{T} [GeV]");
  hpFOCor1Rebin->GetYaxis()->SetTitle("Number of Events / GeV");
  hpFOCor1Rebin->Draw("E X0");

  hpFOCor2Rebin->Scale(1,"width");
  hpFOCor2Rebin->GetXaxis()->SetRangeUser(50.,1500.);
  hpFOCor2Rebin->SetMarkerStyle(32);
  hpFOCor2Rebin->SetMarkerSize(1);
  hpFOCor2Rebin->SetMarkerColor(4);
  hpFOCor2Rebin->SetLineColor(4);
  hpFOCor2Rebin->Draw("E X0 same");

  cPhFOCor->Update();

  legend->Clear();
  legend->SetHeader("Data"+lSave);
  legend->AddEntry(hpFOCor1Rebin,"#gamma_{jet} Cor - 532p1","p");
  legend->AddEntry(hpFOCor2Rebin,"#gamma_{jet} Cor - 535","p");

  legend->Draw();
  as->DrawLatex(0.45, 0.92, outLumi.c_str() );
  //  as->DrawLatex(0.16, 0.92, outLumi.c_str() );

  cPhFOCor->Update();

  cPhFOCor->SetBottomMargin(0.2 + 0.8 * cPhFOCor->GetBottomMargin() - 0.2 * cPhFOCor->GetTopMargin());


  TPad *ratioPadFOCor = new TPad("BottomPadFOCor", "", 0, 0, 1, 1);
  ratioPadFOCor->SetTopMargin(0.8 - 0.8 * ratioPadFOCor->GetBottomMargin() + 0.2 * ratioPadFOCor->GetTopMargin());
  ratioPadFOCor->SetFillStyle(0);
  ratioPadFOCor->SetFrameFillColor(10);
  ratioPadFOCor->SetFrameBorderMode(0);

  ratioPadFOCor->Draw();
  ratioPadFOCor->cd();
  ratioPadFOCor->SetLogy(0);

  TH1F *hpRatioFOCor = (TH1F*)hpFOCor1Rebin->Clone("hpRatioFOCor");
  hpRatioFOCor->Divide(hpFOCor2Rebin,hpFOCor1Rebin,1,1);
  hpRatioFOCor->SetMinimum(0.5);
  hpRatioFOCor->SetMaximum(1.5);
  hpRatioFOCor->GetYaxis()->SetTitle("535/532p1");
  hpRatioFOCor->GetYaxis()->SetTitleSize(0.03);
  hpRatioFOCor->GetYaxis()->SetLabelSize(0.03);
  hpRatioFOCor->GetYaxis()->SetNdivisions(503);
  hpRatioFOCor->SetMarkerStyle(20);
  hpRatioFOCor->SetMarkerSize(1);
  hpRatioFOCor->SetMarkerColor(1);
  hpRatioFOCor->SetLineColor(1);
  hpRatioFOCor->Draw("E X0");

  line->Draw("same");

  hpFOCor1Rebin->GetXaxis()->SetLabelSize(0);
  hpFOCor1Rebin->GetXaxis()->SetTitle("");
  cPhFOCor->RedrawAxis();

  gPad->Update();
  cPhFOCor->Update();

  if(saveC){
    cPhFOCor->SaveAs(outDir+"c_PhotonPtFOCorComp"+vsSave+".eps");
    cPhFOCor->SaveAs(outDir+"c_PhotonPtFOCorComp"+vsSave+".pdf");
  }


  /*
  f1->Close();
  f2->Close();
  */

  return;
}
