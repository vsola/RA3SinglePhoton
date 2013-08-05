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
void vs_PlotMet() {

  Bool_t saveC = true;

  TString vsSave;
  vsSave = "_T03";
  TString lSave;
  lSave = "";

  TString outDir;
  outDir = "Plots_PhotonSusyAnalysis/plotIso/";

  
  string inputFile = "/data/user/vsola/CMSSW_Releases/CMSSW_5_3_5/src/Plots_PhotonSusyAnalysis/Merged_QCD_PhotonJet_T03_PAT/mergedHistos.root";
  //  string inputFile1 = "/data/user/vsola/CMSSW_Releases/CMSSW_5_3_5/src/Plots_PhotonSusyAnalysis/Merged_QCD_PhotonJet_T02w_PAT/mergedHistos.root";
  //  string inputFile2 = "/data/user/vsola/CMSSW_Releases/CMSSW_5_3_5/src/Plots_PhotonSusyAnalysis/Merged_QCD_PhotonJet_MH01_06_PAT/mergedHistos.root";


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
  //  std::string outLumi = "9.4 fb^{-1} #sqrt{s} = 8 TeV  #geq 1 #gamma, #geq 2 jets";
  std::string outLumi = "CMS Work in Progress - MC  #sqrt{s} = 8 TeV  #geq 1 #gamma, #geq 2 jets";



  TFile* ff = TFile::Open( inputFile.c_str() );


  //photon object
  TCanvas * cPh = new TCanvas("cPh","cPh");

  TH1F* hp1 = (TH1F*) ff->Get( "select_1ph_2jets/PreselCut_metPt" );
  TH1F* hp2 = (TH1F*) ff->Get( "select_1ph_2jetsISO/PreselCut_metPt" );


  cPh->SetLogy(1);

  gPad->Update();
  cPh->Update();


  TH1F * hp1Rebin = (TH1F*) hp1->Rebin(binEdges.size() - 1, hp1->GetName(), &(binEdges.front()));
  TH1F * hp2Rebin = (TH1F*) hp2->Rebin(binEdges.size() - 1, hp2->GetName(), &(binEdges.front()));

  if (hp1Rebin->GetSumw2N() == 0)
    hp1Rebin->Sumw2();
  if (hp2Rebin->GetSumw2N() == 0)
    hp2Rebin->Sumw2();

  
  //  hp1Rebin->Scale(1,"width");
  hp1Rebin->SetMinimum(0.005);
  hp1Rebin->SetMaximum(5000);
  
  hp1Rebin->SetMarkerStyle(20);
  hp1Rebin->SetMarkerSize(1.1);
  hp1Rebin->SetMarkerColor(2);
  hp1Rebin->SetLineColor(2);
  hp1Rebin->Draw("E X0");

  //  hp1Rebin->GetXaxis()->SetRangeUser(0.,500.);
  hp1Rebin->GetXaxis()->SetTitle("#slash{E}_{T} [GeV]");
  hp1Rebin->GetYaxis()->SetTitle("Number of Events / GeV");
  hp1Rebin->Draw("E X0");

  //  hp2Rebin->Scale(1,"width");
  //  hp2Rebin->GetXaxis()->SetRangeUser(0.,500.);
  hp2Rebin->SetMarkerStyle(21);
  hp2Rebin->SetMarkerSize(0.9);
  hp2Rebin->SetMarkerColor(4);
  hp2Rebin->SetLineColor(4);
  hp2Rebin->Draw("E X0 same");

  cPh->Update();

  legend->SetHeader("#gamma/QCD (Sim.)"+lSave);
  legend->AddEntry(hp1Rebin,"#gamma - oldIso","p");
  legend->AddEntry(hp2Rebin,"#gamma - newIso","p");

  legend->Draw();
  as->DrawLatex(0.18, 0.92, outLumi.c_str() );

  cPh->Update();

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

  if(saveC){
    cPh->SaveAs(outDir+"c_METcomp"+vsSave+".eps");
    cPh->SaveAs(outDir+"c_METcomp"+vsSave+".pdf");
  }


  //photon FO object
  TCanvas * cPhf = new TCanvas("cPhf","cPhf");

  TH1F* hp1f = (TH1F*) ff->Get( "select_1ph_2jets_FO/PreselCut_metPt" );
  TH1F* hp2f = (TH1F*) ff->Get( "select_1ph_2jets_FOISO/PreselCut_metPt" );


  cPhf->SetLogy(1);

  gPad->Update();
  cPhf->Update();


  TH1F * hp1fRebin = (TH1F*) hp1f->Rebin(binEdges.size() - 1, hp1f->GetName(), &(binEdges.front()));
  TH1F * hp2fRebin = (TH1F*) hp2f->Rebin(binEdges.size() - 1, hp2f->GetName(), &(binEdges.front()));

  if (hp1fRebin->GetSumw2N() == 0)
    hp1fRebin->Sumw2();
  if (hp2fRebin->GetSumw2N() == 0)
    hp2fRebin->Sumw2();

  //  hp1fRebin->Scale(1,"width");
  hp1fRebin->SetMinimum(0.005);
  hp1fRebin->SetMaximum(5000);
  hp1fRebin->SetMarkerStyle(20);
  hp1fRebin->SetMarkerSize(1.1);
  hp1fRebin->SetMarkerColor(2);
  hp1fRebin->SetLineColor(2);

  //  hp1fRebin->GetXaxis()->SetRangeUser(0.,500.);
  hp1fRebin->GetXaxis()->SetTitle("#slash{E}_{T} [GeV]");
  hp1fRebin->GetYaxis()->SetTitle("Number of Events / GeV");
  hp1fRebin->Draw("E X0");

  //  hp2fRebin->Scale(1,"width");
  //  hp2fRebin->GetXaxis()->SetRangeUser(0.,500.);
  hp2fRebin->SetMarkerStyle(21);
  hp2fRebin->SetMarkerSize(0.9);
  hp2fRebin->SetMarkerColor(4);
  hp2fRebin->SetLineColor(4);
  hp2fRebin->Draw("E X0 same");

  cPhf->Update();

  legend->Clear();
  legend->SetHeader("#gamma/QCD (Sim.)"+lSave);
  legend->AddEntry(hp1fRebin,"#gamma_{jet} - oldIso","p");
  legend->AddEntry(hp2fRebin,"#gamma_{jet} - newIso","p");

  legend->Draw();
  as->DrawLatex(0.18, 0.92, outLumi.c_str() );

  cPhf->Update();

  cPhf->SetBottomMargin(0.2 + 0.8 * cPhf->GetBottomMargin() - 0.2 * cPhf->GetTopMargin());


  TPad *ratioPadf = new TPad("BottomPadf", "", 0, 0, 1, 1);
  ratioPadf->SetTopMargin(0.8 - 0.8 * ratioPadf->GetBottomMargin() + 0.2 * ratioPadf->GetTopMargin());
  ratioPadf->SetFillStyle(0);
  ratioPadf->SetFrameFillColor(10);
  ratioPadf->SetFrameBorderMode(0);

  ratioPadf->Draw();
  ratioPadf->cd();
  ratioPadf->SetLogy(0);

  TH1F *hpRatiof = (TH1F*)hp1fRebin->Clone("hpRatiof");
  hpRatiof->Divide(hp2fRebin,hp1fRebin,1,1);
  hpRatiof->SetMinimum(0.);
  hpRatiof->SetMaximum(2.);
  hpRatiof->GetXaxis()->SetNdivisions(505);
  hpRatiof->GetYaxis()->SetTitle("oldIso/newIso");
  //  hpRatiof->GetYaxis()->SetTitle("");
  hpRatiof->GetYaxis()->SetTitleSize(0.03);
  hpRatiof->GetYaxis()->SetLabelSize(0.03);
  hpRatiof->GetYaxis()->SetNdivisions(503);
  hpRatiof->SetMarkerStyle(20);
  hpRatiof->SetMarkerSize(1);
  hpRatiof->SetMarkerColor(1);
  hpRatiof->SetLineColor(1);
  hpRatiof->Draw("E X0");

  line->Draw("same");

  hp1fRebin->GetXaxis()->SetLabelSize(0);
  hp1fRebin->GetXaxis()->SetTitle("");
  cPhf->RedrawAxis();

  gPad->Update();
  cPhf->Update();

  if(saveC){
    cPhf->SaveAs(outDir+"c_METcomp_FO"+vsSave+".eps");
    cPhf->SaveAs(outDir+"c_METcomp_FO"+vsSave+".pdf");
  }


  //photon FO CorrMC object
  TCanvas * cPhfc = new TCanvas("cPhfc","cPhfc");

  TH1F* hp1fc = (TH1F*) ff->Get( "select_1ph_2jets_FO_CorrMC/PreselCut_metPt" );
  TH1F* hp2fc = (TH1F*) ff->Get( "select_1ph_2jets_FO_CorrMCISO/PreselCut_metPt" );


  cPhfc->SetLogy(1);

  gPad->Update();
  cPhfc->Update();


  TH1F * hp1fcRebin = (TH1F*) hp1fc->Rebin(binEdges.size() - 1, hp1fc->GetName(), &(binEdges.front()));
  TH1F * hp2fcRebin = (TH1F*) hp2fc->Rebin(binEdges.size() - 1, hp2fc->GetName(), &(binEdges.front()));

  if (hp1fcRebin->GetSumw2N() == 0)
    hp1fcRebin->Sumw2();
  if (hp2fcRebin->GetSumw2N() == 0)
    hp2fcRebin->Sumw2();

  //  hp1fcRebin->Scale(1,"width");
  hp1fcRebin->SetMinimum(0.005);
  hp1fcRebin->SetMaximum(5000);
  hp1fcRebin->SetMarkerStyle(20);
  hp1fcRebin->SetMarkerSize(1.1);
  hp1fcRebin->SetMarkerColor(2);
  hp1fcRebin->SetLineColor(2);

  //  hp1fcRebin->GetXaxis()->SetRangeUser(0.,500.);
  hp1fcRebin->GetXaxis()->SetTitle("#slash{E}_{T} [GeV]");
  hp1fcRebin->GetYaxis()->SetTitle("Number of Events / GeV");
  hp1fcRebin->Draw("E X0");

  //  hp2fcRebin->Scale(1,"width");
  //  hp2fcRebin->GetXaxis()->SetRangeUser(0.,500.);
  hp2fcRebin->SetMarkerStyle(21);
  hp2fcRebin->SetMarkerSize(0.9);
  hp2fcRebin->SetMarkerColor(4);
  hp2fcRebin->SetLineColor(4);
  hp2fcRebin->Draw("E X0 same");

  cPhfc->Update();

  legend->Clear();
  legend->SetHeader("#gamma/QCD (Sim.)"+lSave);
  legend->AddEntry(hp1fRebin,"#gamma_{jet} Corr - oldIso","p");
  legend->AddEntry(hp2fRebin,"#gamma_{jet} Corr - newIso","p");

  legend->Draw();
  as->DrawLatex(0.18, 0.92, outLumi.c_str() );

  cPhf->Update();

  cPhfc->SetBottomMargin(0.2 + 0.8 * cPhfc->GetBottomMargin() - 0.2 * cPhfc->GetTopMargin());


  TPad *ratioPadfc = new TPad("BottomPadfc", "", 0, 0, 1, 1);
  ratioPadfc->SetTopMargin(0.8 - 0.8 * ratioPadfc->GetBottomMargin() + 0.2 * ratioPadfc->GetTopMargin());
  ratioPadfc->SetFillStyle(0);
  ratioPadfc->SetFrameFillColor(10);
  ratioPadfc->SetFrameBorderMode(0);

  ratioPadfc->Draw();
  ratioPadfc->cd();
  ratioPadfc->SetLogy(0);

  TH1F *hpRatiofc = (TH1F*)hp1fcRebin->Clone("hpRatiofc");
  hpRatiofc->Divide(hp2fcRebin,hp1fcRebin,1,1);
  hpRatiofc->SetMinimum(0.);
  hpRatiofc->SetMaximum(2.);
  hpRatiofc->GetXaxis()->SetNdivisions(505);
  hpRatiofc->GetYaxis()->SetTitle("oldIso/newIso");
  //  hpRatiofc->GetYaxis()->SetTitle("");
  hpRatiofc->GetYaxis()->SetTitleSize(0.03);
  hpRatiofc->GetYaxis()->SetLabelSize(0.03);
  hpRatiofc->GetYaxis()->SetNdivisions(503);
  hpRatiofc->SetMarkerStyle(20);
  hpRatiofc->SetMarkerSize(1);
  hpRatiofc->SetMarkerColor(1);
  hpRatiofc->SetLineColor(1);
  hpRatiofc->Draw("E X0");

  line->Draw("same");

  hp1fcRebin->GetXaxis()->SetLabelSize(0);
  hp1fcRebin->GetXaxis()->SetTitle("");
  cPhfc->RedrawAxis();

  gPad->Update();
  cPhfc->Update();

  if(saveC){
    cPhfc->SaveAs(outDir+"c_METcomp_FO_CorrMC"+vsSave+".eps");
    cPhfc->SaveAs(outDir+"c_METcomp_FO_CorrMC"+vsSave+".pdf");
  }


  return;
}
