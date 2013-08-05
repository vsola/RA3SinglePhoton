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


void vs_PlotComp() {

  Bool_t log   = false;
  Bool_t saveC = true;

  Double_t minRat = 0.5;
  Double_t maxRat = 1.5;
  
  Double_t minRat2 = 0.5;
  Double_t maxRat2 = 1.5;
  
  /*
  TString vsSave;
  vsSave = "_ph_R_V05";
  TString lSave;
  lSave = " - #gamma";
  TString sample;
  sample = "select_1ph_2jets";
  */
  /*
  TString vsSave;
  vsSave = "_phFO_R_V05";
  TString lSave;
  lSave = " - #gamma_{jet}";
  TString sample;
  sample = "select_1ph_2jets_FO";
  */
  
  TString vsSave;
  vsSave = "_phEWK_R_V05";
  TString lSave;
  lSave = " - #gamma_{e}";
  TString sample;
  sample = "select_1ph_2jets_PixelSeed";
  

  TString outDir;
  outDir = "Plots_PhotonSusyAnalysis/studies/";

  string inputFile1 = "/data/user/vsola/CMSSW_Releases/CMSSW_5_3_9/src/Plots_PhotonSusyAnalysis/PhotonHadReReco_22Jan2013A_V05_PAT/mergedHistos.root";
  string inputFile2 = "/data/user/vsola/CMSSW_Releases/CMSSW_5_3_5/src/Plots_PhotonSusyAnalysis/PhotonHadPromptReco_2012A_V24_PAT/mergedHistos.root";
  
 
  setMyTDRStyle();
  gROOT->SetStyle("mytdrStyle");

  gStyle->SetTitleColor(1);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetHistLineWidth(2);
  gStyle->UseCurrentStyle();
  gROOT->ForceStyle(1);


  std::vector<double> binPt;
  binPt.clear();
  binPt.push_back(0);
  binPt.push_back(70);
  binPt.push_back(90);
  binPt.push_back(140);
  binPt.push_back(220);
  binPt.push_back(300);
  binPt.push_back(400);
  binPt.push_back(500);
  binPt.push_back(650);
  binPt.push_back(800);
  binPt.push_back(1000);
  binPt.push_back(1500);

  std::vector<double> binMET;
  binMET.clear();
  binMET.push_back(0);
  binMET.push_back(10);
  binMET.push_back(20);
  binMET.push_back(30);
  binMET.push_back(40);
  binMET.push_back(50);
  binMET.push_back(60);
  binMET.push_back(70);
  binMET.push_back(80);
  binMET.push_back(90);
  binMET.push_back(99);
  binMET.push_back(120);
  binMET.push_back(159);
  binMET.push_back(199);
  binMET.push_back(269);
  binMET.push_back(349);
  binMET.push_back(499);

  std::vector<double> binJet;
  binJet.clear();
  binJet.push_back(0);
  binJet.push_back(30);
  binJet.push_back(60);
  binJet.push_back(90);
  binJet.push_back(120);
  binJet.push_back(160);
  binJet.push_back(200);
  binJet.push_back(260);
  binJet.push_back(350);
  binJet.push_back(450);
  binJet.push_back(600);
  binJet.push_back(750);
  binJet.push_back(950);


  TLegend *legend = new TLegend(0.55, 0.69, 0.93, 0.85, "");
  legend->SetFillColor(10);
  legend->SetFillStyle(1001);
  legend->SetTextSize(0.03);
  legend->SetBorderSize(0);
  legend->SetShadowColor(0);


  TFile* f1 = TFile::Open( inputFile1.c_str() );
  TFile* f2 = TFile::Open( inputFile2.c_str() );


  TCanvas * cPh = new TCanvas("cPh","cPh");


  //photon pt
  TH1F* hp1 = (TH1F*) f1->Get( sample+"/PreselCut_photonPt" );
  TH1F* hp2 = (TH1F*) f2->Get( sample+"/PreselCut_photonPt" );

  
  cPh->SetLogy(0);
  if(log) cPh->SetLogy(1);

  gPad->Update();
  cPh->Update();


  TH1F * hp1r = (TH1F*) hp1->Rebin(binPt.size() - 1, hp1->GetName(), &(binPt.front()));
  TH1F * hp2r = (TH1F*) hp2->Rebin(binPt.size() - 1, hp2->GetName(), &(binPt.front()));

  if (hp1r->GetSumw2N() == 0)
    hp1r->Sumw2();
  if (hp2r->GetSumw2N() == 0)
    hp2r->Sumw2();

  hp1r->Scale(1./hp1->GetEntries());
  hp1r->SetTitle("Leading Photon p_{T}");
  hp1r->GetXaxis()->SetTitle("1st Photon p_{T} [GeV]");
  hp1r->GetYaxis()->SetTitle("Events");
  hp1r->SetMarkerStyle(21);
  hp1r->SetMarkerSize(0.8);
  hp1r->SetMarkerColor(2);
  hp1r->SetLineColor(2);
  hp1r->Draw();

  hp2r->Scale(1./hp2->GetEntries());
  hp2r->SetMarkerStyle(20);
  hp2r->SetMarkerSize(0.9);
  hp2r->SetMarkerColor(4);
  hp2r->SetLineColor(4);
  hp2r->Draw("E0 X0 same");

  cPh->Update();

  legend->SetHeader("Data 2012 A"+lSave);
  legend->AddEntry(hp1r,"ReReco 22Jan2013","lp");
  legend->AddEntry(hp2r,"PromptReco","p");

  legend->Draw();

  cPh->Update();

  cPh->SetBottomMargin(0.2 + 0.8 * cPh->GetBottomMargin() - 0.2 * cPh->GetTopMargin());

  TPad *ratioPadP = new TPad("BottomPadP", "", 0, 0, 1, 1);
  ratioPadP->SetTopMargin(0.8 - 0.8 * ratioPadP->GetBottomMargin() + 0.2 * ratioPadP->GetTopMargin());
  ratioPadP->SetFillStyle(0);
  ratioPadP->SetFrameFillColor(10);
  ratioPadP->SetFrameBorderMode(0);

  ratioPadP->Draw();
  ratioPadP->cd();
  ratioPadP->SetLogy(0);

  TH1F *hpR = (TH1F*)hp1r->Clone("hpR");
  hpR->Divide(hp1r,hp2r,1.,1.);
  hpR->SetMinimum(minRat);
  hpR->SetMaximum(maxRat);
  hpR->GetYaxis()->SetTitle("ReReco/PromptReco");
  //  hpR->GetYaxis()->SetTitle("");
  hpR->GetYaxis()->SetTitleSize(0.03);
  hpR->GetYaxis()->SetLabelSize(0.03);
  hpR->GetYaxis()->SetNdivisions(503);
  //  hpR->GetXaxis()->SetNdivisions(505);
  hpR->SetMarkerStyle(20);
  hpR->SetMarkerSize(1);
  hpR->SetMarkerColor(1);
  hpR->SetLineColor(1);
  hpR->Draw("E X0");

  TLine * linep = new TLine(hpR->GetXaxis()->GetXmin(), 1., hpR->GetXaxis()->GetXmax(), 1.);
  linep->SetLineColor(2);
  linep->SetLineWidth(0.5);
  linep->SetLineStyle(2);
  linep->Draw("same");

  hp1r->GetXaxis()->SetLabelSize(0);
  hp1r->GetXaxis()->SetTitle("");
  cPh->RedrawAxis();

  gPad->Update();
  cPh->Update();
 
  if(saveC){
    cPh->SaveAs(outDir+"c_phPt"+vsSave+".eps");
    cPh->SaveAs(outDir+"c_phPt"+vsSave+".pdf");
  }

  
  //photon eta
  TH1F* he1 = (TH1F*) f1->Get( sample+"/PreselCut_photonEta" );
  TH1F* he2 = (TH1F*) f2->Get( sample+"/PreselCut_photonEta" );
  
  cPh->SetLogy(0);

  gPad->Update();
  cPh->Update();

  he1->Scale(1./he1->GetEntries());
  he1->GetXaxis()->SetTitle("1st Photon #eta");
  he1->GetYaxis()->SetTitle("Events");
  he1->GetXaxis()->SetRangeUser(-1.55,1.55);
  he1->SetMarkerStyle(21);
  he1->SetMarkerSize(0.8);
  he1->SetMarkerColor(2);
  he1->SetLineColor(2);
  he1->Draw();

  he2->Scale(1./he2->GetEntries());
  he2->GetXaxis()->SetRangeUser(-1.55,1.55);
  he2->SetMarkerStyle(20);
  he2->SetMarkerSize(0.9);
  he2->SetMarkerColor(4);
  he2->SetLineColor(4);
  he2->Draw("E0 X0 same");

  cPh->Update();
 
  TPad *ratioPadE = new TPad("BottomPadE", "", 0, 0, 1, 1);
  ratioPadE->SetTopMargin(0.8 - 0.8 * ratioPadE->GetBottomMargin() + 0.2 * ratioPadE->GetTopMargin());
  ratioPadE->SetFillStyle(0);
  ratioPadE->SetFrameFillColor(10);
  ratioPadE->SetFrameBorderMode(0);

  ratioPadE->Draw();
  ratioPadE->cd();
  ratioPadE->SetLogy(0);

  TH1F *heR = (TH1F*)he1->Clone("heR");
  heR->Divide(he1,he2,1.,1.);
  heR->SetMinimum(minRat);
  heR->SetMaximum(maxRat);
  heR->GetYaxis()->SetTitle("ReReco/PromptReco");
  heR->GetYaxis()->SetTitleSize(0.03);
  heR->GetYaxis()->SetLabelSize(0.03);
  heR->GetYaxis()->SetNdivisions(503);
  heR->SetMarkerStyle(20);
  heR->SetMarkerSize(1);
  heR->SetMarkerColor(1);
  heR->SetLineColor(1);
  heR->Draw("E X0");

  TLine * linee = new TLine(-1.55, 1., 1.55, 1.);
  linee->SetLineColor(2);
  linee->SetLineWidth(0.5);
  linee->SetLineStyle(2);
  linee->Draw("same");

  he1->GetXaxis()->SetLabelSize(0);
  he1->GetXaxis()->SetTitle("");
  cPh->RedrawAxis();

  gPad->Update();
  cPh->Update();
 
  if(saveC){
    cPh->SaveAs(outDir+"c_phEta"+vsSave+".eps");
    cPh->SaveAs(outDir+"c_phEta"+vsSave+".pdf");
  }

  
  //photon phi
  TH1F* hph1 = (TH1F*) f1->Get( sample+"/PreselCut_photonPhi" );
  TH1F* hph2 = (TH1F*) f2->Get( sample+"/PreselCut_photonPhi" );
  
  cPh->SetLogy(0);

  gPad->Update();
  cPh->Update();

  hph1->Scale(1./hph1->GetEntries());
  hph1->GetXaxis()->SetTitle("1st Photon #phi");
  hph1->GetYaxis()->SetTitle("Events");
  hph1->GetXaxis()->SetRangeUser(-3.15,3.15);
  hph1->SetMarkerStyle(21);
  hph1->SetMarkerSize(0.8);
  hph1->SetMarkerColor(2);
  hph1->SetLineColor(2);
  hph1->Draw();

  hph2->Scale(1./hph2->GetEntries());
  hph2->GetXaxis()->SetRangeUser(-3.15,3.15);
  hph2->SetMarkerStyle(20);
  hph2->SetMarkerSize(0.9);
  hph2->SetMarkerColor(4);
  hph2->SetLineColor(4);
  hph2->Draw("E0 X0 same");

  cPh->Update();
 
  TPad *ratioPadPh = new TPad("BottomPadPh", "", 0, 0, 1, 1);
  ratioPadPh->SetTopMargin(0.8 - 0.8 * ratioPadPh->GetBottomMargin() + 0.2 * ratioPadPh->GetTopMargin());
  ratioPadPh->SetFillStyle(0);
  ratioPadPh->SetFrameFillColor(10);
  ratioPadPh->SetFrameBorderMode(0);

  ratioPadPh->Draw();
  ratioPadPh->cd();
  ratioPadPh->SetLogy(0);

  TH1F *hphR = (TH1F*)hph1->Clone("hphR");
  if (hphR->GetSumw2N() == 0)
    hphR->Sumw2();
  hphR->Divide(hph1,hph2,1.,1.);
  hphR->SetMinimum(minRat);
  hphR->SetMaximum(maxRat);
  hphR->GetYaxis()->SetTitle("ReReco/PromptReco");
  hphR->GetYaxis()->SetTitleSize(0.03);
  hphR->GetYaxis()->SetLabelSize(0.03);
  hphR->GetYaxis()->SetNdivisions(503);
  hphR->SetMarkerStyle(20);
  hphR->SetMarkerSize(1);
  hphR->SetMarkerColor(1);
  hphR->SetLineColor(1);
  hphR->Draw("E X0");

  TLine * lineph = new TLine(-3.15, 1., 3.15, 1.);
  lineph->SetLineColor(2);
  lineph->SetLineWidth(0.5);
  lineph->SetLineStyle(2);
  lineph->Draw("same");

  hph1->GetXaxis()->SetLabelSize(0);
  hph1->GetXaxis()->SetTitle("");
  cPh->RedrawAxis();

  gPad->Update();
  cPh->Update();
 
  if(saveC){
    cPh->SaveAs(outDir+"c_phPhi"+vsSave+".eps");
    cPh->SaveAs(outDir+"c_phPhi"+vsSave+".pdf");
  }
  
  
  //MET
  TH1F* hm1 = (TH1F*) f1->Get( sample+"/PreselCut_metPt" );
  TH1F* hm2 = (TH1F*) f2->Get( sample+"/PreselCut_metPt" );

  
  cPh->SetLogy(0);
  if(log) cPh->SetLogy(1);

  gPad->Update();
  cPh->Update();


  TH1F * hm1r = (TH1F*) hm1->Rebin(binMET.size() - 1, hm1->GetName(), &(binMET.front()));
  TH1F * hm2r = (TH1F*) hm2->Rebin(binMET.size() - 1, hm2->GetName(), &(binMET.front()));

  if (hm1r->GetSumw2N() == 0)
    hm1r->Sumw2();
  if (hm2r->GetSumw2N() == 0)
    hm2r->Sumw2();

  hm1r->Scale(1./hm1->GetEntries());
  hm1r->GetXaxis()->SetTitle("#slash{E}_{T} [GeV]");
  hm1r->GetYaxis()->SetTitle("Events");
  hm1r->SetMarkerStyle(21);
  hm1r->SetMarkerSize(0.8);
  hm1r->SetMarkerColor(2);
  hm1r->SetLineColor(2);
  hm1r->Draw();

  hm2r->Scale(1./hm2->GetEntries());
  hm2r->SetMarkerStyle(20);
  hm2r->SetMarkerSize(0.9);
  hm2r->SetMarkerColor(4);
  hm2r->SetLineColor(4);
  hm2r->Draw("E0 X0 same");

  cPh->Update();

  legend->Draw();

  cPh->Update();
 
  TPad *ratioPadM = new TPad("BottomPadM", "", 0, 0, 1, 1);
  ratioPadM->SetTopMargin(0.8 - 0.8 * ratioPadM->GetBottomMargin() + 0.2 * ratioPadM->GetTopMargin());
  ratioPadM->SetFillStyle(0);
  ratioPadM->SetFrameFillColor(10);
  ratioPadM->SetFrameBorderMode(0);

  ratioPadM->Draw();
  ratioPadM->cd();
  ratioPadM->SetLogy(0);

  TH1F *hmR = (TH1F*)hm1r->Clone("hmR");
  hmR->Divide(hm1r,hm2r,1.,1.);
  hmR->SetMinimum(minRat2);
  hmR->SetMaximum(maxRat2);
  hmR->GetYaxis()->SetTitle("ReReco/PromptReco");
  hmR->GetYaxis()->SetTitleSize(0.03);
  hmR->GetYaxis()->SetLabelSize(0.03);
  hmR->GetYaxis()->SetNdivisions(503);
  hmR->SetMarkerStyle(20);
  hmR->SetMarkerSize(1);
  hmR->SetMarkerColor(1);
  hmR->SetLineColor(1);
  hmR->Draw("E X0");

  TLine * linem = new TLine(hmR->GetXaxis()->GetXmin(), 1., hmR->GetXaxis()->GetXmax(), 1.);
  linem->SetLineColor(2);
  linem->SetLineWidth(0.5);
  linem->SetLineStyle(2);
  linem->Draw("same");

  hm1r->GetXaxis()->SetLabelSize(0);
  hm1r->GetXaxis()->SetTitle("");
  cPh->RedrawAxis();

  gPad->Update();
  cPh->Update();
 
  if(saveC){
    cPh->SaveAs(outDir+"c_MET"+vsSave+".eps");
    cPh->SaveAs(outDir+"c_MET"+vsSave+".pdf");
  }

  
  //1st jet pt
  TH1F* hj1 = (TH1F*) f1->Get( sample+"/PreselCut_jetPt" );
  TH1F* hj2 = (TH1F*) f2->Get( sample+"/PreselCut_jetPt" );
  
  cPh->SetLogy(0);
  if(log) cPh->SetLogy(1);

  gPad->Update();
  cPh->Update();
  
  TH1F * hj1r = (TH1F*) hj1->Rebin(binJet.size() - 1, hj1->GetName(), &(binJet.front()));
  TH1F * hj2r = (TH1F*) hj2->Rebin(binJet.size() - 1, hj2->GetName(), &(binJet.front()));

  if (hj1r->GetSumw2N() == 0)
    hj1r->Sumw2();
  if (hj2r->GetSumw2N() == 0)
    hj2r->Sumw2();
  
  hj1r->Scale(1./hj1->GetEntries());
  hj1r->GetXaxis()->SetTitle("1st Jet p_{T} [GeV]");
  hj1r->GetYaxis()->SetTitle("Events");
  hj1r->SetMarkerStyle(21);
  hj1r->SetMarkerSize(0.8);
  hj1r->SetMarkerColor(2);
  hj1r->SetLineColor(2);
  hj1r->Draw();

  hj2r->Scale(1./hj2->GetEntries());
  hj2r->SetMarkerStyle(20);
  hj2r->SetMarkerSize(0.9);
  hj2r->SetMarkerColor(4);
  hj2r->SetLineColor(4);
  hj2r->Draw("E0 X0 same");

  cPh->Update();

  //  legend->Draw();

  cPh->Update();
 
  TPad *ratioPadJ1 = new TPad("BottomPadJ1", "", 0, 0, 1, 1);
  ratioPadJ1->SetTopMargin(0.8 - 0.8 * ratioPadJ1->GetBottomMargin() + 0.2 * ratioPadJ1->GetTopMargin());
  ratioPadJ1->SetFillStyle(0);
  ratioPadJ1->SetFrameFillColor(10);
  ratioPadJ1->SetFrameBorderMode(0);

  ratioPadJ1->Draw();
  ratioPadJ1->cd();
  ratioPadJ1->SetLogy(0);

  TH1F *hjR = (TH1F*)hj1r->Clone("hjR");
  hjR->Divide(hj1r,hj2r,1.,1.);
  hjR->SetMinimum(minRat);
  hjR->SetMaximum(maxRat);
  hjR->GetYaxis()->SetTitle("ReReco/PromptReco");
  hjR->GetYaxis()->SetTitleSize(0.03);
  hjR->GetYaxis()->SetLabelSize(0.03);
  hjR->GetYaxis()->SetNdivisions(503);
  hjR->SetMarkerStyle(20);
  hjR->SetMarkerSize(1);
  hjR->SetMarkerColor(1);
  hjR->SetLineColor(1);
  hjR->Draw("E X0");

  TLine * linej = new TLine(hjR->GetXaxis()->GetXmin(), 1., hjR->GetXaxis()->GetXmax(), 1.);
  linej->SetLineColor(2);
  linej->SetLineWidth(0.5);
  linej->SetLineStyle(2);
  linej->Draw("same");

  hj1r->GetXaxis()->SetLabelSize(0);
  hj1r->GetXaxis()->SetTitle("");
  cPh->RedrawAxis();

  gPad->Update();
  cPh->Update();
 
  if(saveC){
    cPh->SaveAs(outDir+"c_jetPt"+vsSave+".eps");
    cPh->SaveAs(outDir+"c_jetPt"+vsSave+".pdf");
  }


  //2nd jet pt
  TH1F* hjj1 = (TH1F*) f1->Get( sample+"/PreselCut_jet2Pt" );
  TH1F* hjj2 = (TH1F*) f2->Get( sample+"/PreselCut_jet2Pt" );
  
  cPh->SetLogy(0);
  if(log) cPh->SetLogy(1);

  gPad->Update();
  cPh->Update();
  
  TH1F * hjj1r = (TH1F*) hjj1->Rebin(binJet.size() - 1, hjj1->GetName(), &(binJet.front()));
  TH1F * hjj2r = (TH1F*) hjj2->Rebin(binJet.size() - 1, hjj2->GetName(), &(binJet.front()));

  if (hjj1r->GetSumw2N() == 0)
    hjj1r->Sumw2();
  if (hjj2r->GetSumw2N() == 0)
    hjj2r->Sumw2();
  
  hjj1r->Scale(1./hjj1->GetEntries());
  hjj1r->GetXaxis()->SetTitle("2nd Jet p_{T} [GeV]");
  hjj1r->GetYaxis()->SetTitle("Events");
  hjj1r->SetMarkerStyle(21);
  hjj1r->SetMarkerSize(0.8);
  hjj1r->SetMarkerColor(2);
  hjj1r->SetLineColor(2);
  hjj1r->Draw();

  hjj2r->Scale(1./hjj2->GetEntries());
  hjj2r->SetMarkerStyle(20);
  hjj2r->SetMarkerSize(0.9);
  hjj2r->SetMarkerColor(4);
  hjj2r->SetLineColor(4);
  hjj2r->Draw("E0 X0 same");

  cPh->Update();

  //  legend->Draw();

  cPh->Update();
 
  TPad *ratioPadJ2 = new TPad("BottomPadJ2", "", 0, 0, 1, 1);
  ratioPadJ2->SetTopMargin(0.8 - 0.8 * ratioPadJ2->GetBottomMargin() + 0.2 * ratioPadJ2->GetTopMargin());
  ratioPadJ2->SetFillStyle(0);
  ratioPadJ2->SetFrameFillColor(10);
  ratioPadJ2->SetFrameBorderMode(0);

  ratioPadJ2->Draw();
  ratioPadJ2->cd();
  ratioPadJ2->SetLogy(0);

  TH1F *hjjR = (TH1F*)hjj1r->Clone("hjjR");
  hjjR->Divide(hjj1r,hjj2r,1.,1.);
  hjjR->SetMinimum(minRat);
  hjjR->SetMaximum(maxRat);
  hjjR->GetYaxis()->SetTitle("ReReco/PromptReco");
  hjjR->GetYaxis()->SetTitleSize(0.03);
  hjjR->GetYaxis()->SetLabelSize(0.03);
  hjjR->GetYaxis()->SetNdivisions(503);
  hjjR->SetMarkerStyle(20);
  hjjR->SetMarkerSize(1);
  hjjR->SetMarkerColor(1);
  hjjR->SetLineColor(1);
  hjjR->Draw("E X0");

  linej->Draw("same");

  hjj1r->GetXaxis()->SetLabelSize(0);
  hjj1r->GetXaxis()->SetTitle("");
  cPh->RedrawAxis();

  gPad->Update();
  cPh->Update();
 
  if(saveC){
    cPh->SaveAs(outDir+"c_jet2Pt"+vsSave+".eps");
    cPh->SaveAs(outDir+"c_jet2Pt"+vsSave+".pdf");
  }

  

  return;
}
