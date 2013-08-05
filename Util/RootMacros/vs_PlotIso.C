#include <TKey.h>
#include <TImage.h>
#include <TError.h>
#include <vector>
#include <TFile.h>
#include <TROOT.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TLine.h>
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
void vs_PlotIso() {

  Bool_t saveC = true;

  TString vsSave;
  vsSave = "_T03";
  TString lSave;
  lSave = "";

  TString outDir;
  outDir = "Plots_PhotonSusyAnalysis/plotIso/";


  string inputFile1 = "/data/user/vsola/CMSSW_Releases/CMSSW_5_3_5/src/Plots_PhotonSusyAnalysis/Merged_QCD_PhotonJet_T03_PAT/mergedHistos.root";
  //  string inaputFile2 = "";
  
  

  setMyTDRStyle();
  gROOT->SetStyle("mytdrStyle");

  gStyle->SetHistLineWidth(2);
  gStyle->UseCurrentStyle();
  gROOT->ForceStyle(1);

  /*
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
  */
  
  TLegend *legend = new TLegend(0.70, 0.70, 0.88, 0.85, "");
  legend->SetFillColor(10);
  legend->SetFillStyle(1001);
  legend->SetTextSize(0.04);
  legend->SetBorderSize(0);
  legend->SetShadowColor(0);


  TLatex *as = new TLatex();
  as->SetNDC(true);
  as->SetTextColor(12);
  as->SetTextFont(43);
  as->SetTextSize(12);

  std::string outLumi1 = "CMS Work in Progress - QCD MC #sqrt{s} = 8 TeV - All events";
  std::string outLumi2 = "CMS Work in Progress - QCD MC #sqrt{s} = 8 TeV - #geq 1 #gamma, #geq 2 j";
  std::string outLumi3 = "CMS Work in Progress - QCD MC #sqrt{s} = 8 TeV - #geq 1 #gamma_{jet}, #geq 2 jets";
  //  std::string outLumi = "CMS Work in Progress - 9.4 fb^{-1} #sqrt{s} = 8 TeV  #geq 1 #gamma, #geq 2 jets";


  TLine *l1 = new TLine();
  l1->SetLineWidth(3);
  l1->SetLineStyle(2);

  TLine *l2 = new TLine();
  l2->SetLineWidth(1);
  l2->SetLineStyle(2);


  TFile* f1 = TFile::Open( inputFile1.c_str() );
  //  TFile* f2 = TFile::Open( inputFile2.c_str() );


  //Iso Deposit Variables - All Events
  TCanvas * cIsoD = new TCanvas("cIsoDep","cIsoDep");
  cIsoD->Clear();
  cIsoD->Divide(2,2);

  TH1F* hio1 = (TH1F*) f1->Get( "select_All/PreselCut_trackiso;1" );
  TH1F* hio2 = (TH1F*) f1->Get( "select_All/PreselCut_ecaliso;1" );
  TH1F* hio3 = (TH1F*) f1->Get( "select_All/PreselCut_hcaliso;1" );
  TH1F* hio4 = (TH1F*) f1->Get( "select_All/PreselCut_combiso;1" );

  

  cIsoD->Update();
  cIsoD->cd(1);
  gPad->Update();
  gPad->SetLogy(1);

  //  TH1F * hio1Rebin = (TH1F*) hp1->Rebin(binEdges.size() - 1, hp1->GetName(), &(binEdges.front()));
  //  if (hio1Rebin->GetSumw2N() == 0)
  //    hio1Rebin->Sumw2();
  
  hio1->Scale(1,"width");
  hio1->SetMinimum(100);
  hio1->SetMaximum(200000);
  hio1->SetMarkerStyle(20);
  hio1->SetMarkerSize(0.8);
  hio1->SetMarkerColor(2);
  hio1->SetLineColor(2);
  hio1->Draw();
  
  //  hio1->GetXaxis()->SetRangeUser(50.,1500.);
  hio1->GetXaxis()->SetTitle("Track Iso Dep [GeV]");
  hio1->GetYaxis()->SetTitle("Number of Events / Bin");
  hio1->Draw("E X0");
  

  /*
  cIsoD->Update();

  legend->SetHeader("Data"+lSave);
  legend->AddEntry(hp1Rebin,"#gamma - 532p1","p");
  legend->AddEntry(hp2Rebin,"#gamma - 535","p");
  legend->Draw();
  */
  as->DrawLatex(0.02, 0.93, outLumi1.c_str() );

  cIsoD->cd(2);
  gPad->Update();
  gPad->SetLogy(1);
  
  hio2->Scale(1,"width");
  hio2->SetMinimum(100);
  hio2->SetMaximum(200000);
  hio2->SetMarkerStyle(20);
  hio2->SetMarkerSize(0.8);
  hio2->SetMarkerColor(2);
  hio2->SetLineColor(2);
  hio2->Draw();
  
  hio2->GetXaxis()->SetTitle("ECAL Iso Dep [GeV]");
  hio2->GetYaxis()->SetTitle("Number of Events / Bin");
  hio2->Draw("E X0");
  

  cIsoD->cd(3);
  gPad->Update();
  gPad->SetLogy(1);
  
  hio3->Scale(1,"width");
  hio3->SetMinimum(100);
  hio3->SetMaximum(200000);
  hio3->SetMarkerStyle(20);
  hio3->SetMarkerSize(0.8);
  hio3->SetMarkerColor(2);
  hio3->SetLineColor(2);
  hio3->Draw();
  
  hio3->GetXaxis()->SetTitle("HCAL Iso Dep [GeV]");
  hio3->GetYaxis()->SetTitle("Number of Events / Bin");
  hio3->Draw("E X0");
  

  cIsoD->cd(4);
  gPad->Update();
  gPad->SetLogy(1);
  
  hio4->Scale(1,"width");
  hio4->SetMinimum(100);
  hio4->SetMaximum(200000);
  hio4->SetMarkerStyle(20);
  hio4->SetMarkerSize(0.8);
  hio4->SetMarkerColor(2);
  hio4->SetLineColor(2);
  hio4->Draw();
  
  hio4->GetXaxis()->SetTitle("Combined Iso Dep [GeV]");
  hio4->GetYaxis()->SetTitle("Number of Events / Bin");
  hio4->Draw("E X0");
  
  l1->DrawLine(6.,100.,6.,200000.);


  cIsoD->cd();
  cIsoD->Update();

  if(saveC){
    cIsoD->SaveAs(outDir+"c_IsoDepVarsAll"+vsSave+".eps");
    cIsoD->SaveAs(outDir+"c_IsoDepVarsAll"+vsSave+".pdf");
  }


  //Iso Alternate Variables - All Events
  TCanvas * cIsoA = new TCanvas("cIsoAlt","cIsoAlt");
  cIsoA->Clear();
  cIsoA->Divide(2,2);

  TH1F* hin1 = (TH1F*) f1->Get( "select_All/PreselCut_chargedIso;1" );
  TH1F* hin2 = (TH1F*) f1->Get( "select_All/PreselCut_neutralIso;1" );
  TH1F* hin3 = (TH1F*) f1->Get( "select_All/PreselCut_photonIso;1" );

  cIsoA->Update();
  cIsoA->cd(1);
  gPad->Update();
  gPad->SetLogy(1);

  hin1->Scale(1,"width");
  hin1->SetMinimum(100);
  hin1->SetMaximum(200000);
  hin1->SetMarkerStyle(20);
  hin1->SetMarkerSize(0.8);
  hin1->SetMarkerColor(2);
  hin1->SetLineColor(2);
  hin1->Draw();
  
  hin1->GetXaxis()->SetTitle("PF Charged Iso Dep [GeV]");
  hin1->GetYaxis()->SetTitle("Number of Events / Bin");
  hin1->Draw("E X0");
  
  as->DrawLatex(0.02, 0.93, outLumi1.c_str() );

  l1->DrawLine(2.6,100.,2.6,200000.);

  cIsoA->cd(2);
  gPad->Update();
  gPad->SetLogy(1);
  
  hin2->Scale(1,"width");
  hin2->SetMinimum(100);
  hin2->SetMaximum(200000);
  hin2->SetMarkerStyle(20);
  hin2->SetMarkerSize(0.8);
  hin2->SetMarkerColor(2);
  hin2->SetLineColor(2);
  hin2->Draw();
  
  hin2->GetXaxis()->SetTitle("PF Neutral Iso Dep [GeV]");
  hin2->GetYaxis()->SetTitle("Number of Events / Bin");
  hin2->Draw("E X0");

  l1->DrawLine(6.7,100.,6.7,200000.);
  l2->DrawLine(23.5,100.,23.5,200000.);
  
  cIsoA->cd(3);
  gPad->Update();
  gPad->SetLogy(1);
  
  hin3->Scale(1,"width");
  hin3->SetMinimum(100);
  hin3->SetMaximum(200000);
  hin3->SetMarkerStyle(20);
  hin3->SetMarkerSize(0.8);
  hin3->SetMarkerColor(2);
  hin3->SetLineColor(2);
  hin3->Draw();
  
  hin3->GetXaxis()->SetTitle("PF Photons Iso Dep [GeV]");
  hin3->GetYaxis()->SetTitle("Number of Events / Bin");
  hin3->Draw("E X0");

  l1->DrawLine(1.7,100.,1.7,200000.);
  l2->DrawLine(3.8,100.,3.8,200000.);
  
  cIsoA->cd();
  cIsoA->Update();

  if(saveC){
    cIsoA->SaveAs(outDir+"c_IsoAltVarsAll"+vsSave+".eps");
    cIsoA->SaveAs(outDir+"c_IsoAltVarsAll"+vsSave+".pdf");
  }


  //Iso Threshold Variables - All Events
  TCanvas * cIsoT = new TCanvas("cIsoThr","cIsoThr");
  cIsoT->Clear();
  cIsoT->Divide(2,2);

  TH1F* hit1 = (TH1F*) f1->Get( "select_All/PreselCut_combisoTh;1" );
  TH1F* hit2 = (TH1F*) f1->Get( "select_All/PreselCut_combIsoCorTh;1" );
  TH2F* hit3 = (TH2F*) f1->Get( "select_All/PreselCut_combIsoOldVsNew;1" );

  cIsoT->Update();
  cIsoT->cd(1);
  gPad->Update();
  gPad->SetLogy(1);

  hit1->Scale(1,"width");
  hit1->SetMinimum(100);
  hit1->SetMaximum(200000);
  hit1->SetMarkerStyle(20);
  hit1->SetMarkerSize(0.8);
  hit1->SetMarkerColor(2);
  hit1->SetLineColor(2);
  hit1->Draw();
  
  hit1->GetXaxis()->SetTitle("Combined Iso Dep Thr [GeV]");
  hit1->GetYaxis()->SetTitle("Number of Events / Bin");
  hit1->Draw("E X0");
  
  as->DrawLatex(0.02, 0.93, outLumi1.c_str() );

  l1->DrawLine(0.,100.,0.,200000.);

  cIsoT->cd(2);
  gPad->Update();
  gPad->SetLogy(1);
  
  hit2->Scale(1,"width");
  hit2->SetMinimum(100);
  hit2->SetMaximum(200000);
  hit2->SetMarkerStyle(20);
  hit2->SetMarkerSize(0.8);
  hit2->SetMarkerColor(2);
  hit2->SetLineColor(2);
  hit2->Draw();
  
  hit2->GetXaxis()->SetTitle("Combined Iso Alt Thr [GeV]");
  hit2->GetYaxis()->SetTitle("Number of Events / Bin");
  hit2->Draw("E X0");

  l1->DrawLine(0.,100.,0.,200000.);
  
  cIsoT->cd(3);
  gPad->Update();
  gPad->SetLogy(0);
  
  hit3->GetXaxis()->SetTitle("Combined Iso Dep Thr [GeV]");
  hit3->GetYaxis()->SetTitle("Combined Iso Alt Thr [GeV]");
  hit3->Draw("colz");
  
  l1->DrawLine(-30.,0.,30.,0.);
  l1->DrawLine(0.,-30.,0.,30.);

  cIsoT->cd();
  cIsoT->Update();

  if(saveC){
    cIsoT->SaveAs(outDir+"c_IsoThrVarsAll"+vsSave+".eps");
    cIsoT->SaveAs(outDir+"c_IsoThrVarsAll"+vsSave+".pdf");
  }



  //Iso Deposit Variables - Sel Events
  TCanvas * cIsoDS = new TCanvas("cIsoDepSel","cIsoDepSel");
  cIsoDS->Clear();
  cIsoDS->Divide(2,2);

  TH1F* hios1 = (TH1F*) f1->Get( "select_1ph_2jets/PreselCut_trackiso;1" );
  TH1F* hios2 = (TH1F*) f1->Get( "select_1ph_2jets/PreselCut_ecaliso;1" );
  TH1F* hios3 = (TH1F*) f1->Get( "select_1ph_2jets/PreselCut_hcaliso;1" );
  TH1F* hios4 = (TH1F*) f1->Get( "select_1ph_2jets/PreselCut_combiso;1" );

  TH1F* hiof1 = (TH1F*) f1->Get( "select_1ph_2jets_FO/PreselCut_trackiso;1" );
  TH1F* hiof2 = (TH1F*) f1->Get( "select_1ph_2jets_FO/PreselCut_ecaliso;1" );
  TH1F* hiof3 = (TH1F*) f1->Get( "select_1ph_2jets_FO/PreselCut_hcaliso;1" );
  TH1F* hiof4 = (TH1F*) f1->Get( "select_1ph_2jets_FO/PreselCut_combiso;1" );
  
  cIsoDS->Update();
  cIsoDS->cd(1);
  gPad->Update();
  gPad->SetLogy(1);

  //  TH1F * hio1Rebin = (TH1F*) hp1->Rebin(binEdges.size() - 1, hp1->GetName(), &(binEdges.front()));
  //  if (hio1Rebin->GetSumw2N() == 0)
  //    hio1Rebin->Sumw2();
  
  hios1->Scale(1,"width");
  hios1->SetMinimum(0.0001);
  hios1->SetMaximum(2000);
  hios1->SetMarkerStyle(20);
  hios1->SetMarkerSize(0.8);
  hios1->SetMarkerColor(2);
  hios1->SetLineColor(2);
  hios1->Draw();
  //  hios1->GetXaxis()->SetRangeUser(50.,1500.);
  hios1->GetXaxis()->SetTitle("Track Iso Dep [GeV]");
  hios1->GetYaxis()->SetTitle("Number of Events / Bin");
  hios1->Draw("E X0");
  
  hiof1->Scale(1,"width");
  hiof1->SetMarkerStyle(21);
  hiof1->SetMarkerSize(0.8);
  hiof1->SetMarkerColor(4);
  hiof1->SetLineColor(4);
  //  hiof1->GetXaxis()->SetRangeUser(50.,1500.);
  hiof1->Draw("E X0 same");
  
  legend->SetHeader("QCD MC"+lSave);
  legend->AddEntry(hios1,"#gamma Sample","p");
  legend->AddEntry(hiof1,"#gamma_{jet} FO","p");
  legend->Draw();
  
  as->DrawLatex(0.02, 0.93, outLumi2.c_str() );

  cIsoDS->cd(2);
  gPad->Update();
  gPad->SetLogy(1);
  
  hios2->Scale(1,"width");
  hios2->SetMinimum(0.0001);
  hios2->SetMaximum(2000);
  hios2->SetMarkerStyle(20);
  hios2->SetMarkerSize(0.8);
  hios2->SetMarkerColor(2);
  hios2->SetLineColor(2);
  hios2->Draw();  
  hios2->GetXaxis()->SetTitle("ECAL Iso Dep [GeV]");
  hios2->GetYaxis()->SetTitle("Number of Events / Bin");
  hios2->Draw("E X0");
  
  hiof2->Scale(1,"width");
  hiof2->SetMarkerStyle(21);
  hiof2->SetMarkerSize(0.8);
  hiof2->SetMarkerColor(4);
  hiof2->SetLineColor(4);
  hiof2->Draw("E X0 same");

  cIsoDS->cd(3);
  gPad->Update();
  gPad->SetLogy(1);
  
  hios3->Scale(1,"width");
  hios3->SetMinimum(0.0001);
  hios3->SetMaximum(2000);
  hios3->SetMarkerStyle(20);
  hios3->SetMarkerSize(0.8);
  hios3->SetMarkerColor(2);
  hios3->SetLineColor(2);
  hios3->Draw();  
  hios3->GetXaxis()->SetTitle("HCAL Iso Dep [GeV]");
  hios3->GetYaxis()->SetTitle("Number of Events / Bin");
  hios3->Draw("E X0");
  
  hiof3->Scale(1,"width");
  hiof3->SetMarkerStyle(21);
  hiof3->SetMarkerSize(0.8);
  hiof3->SetMarkerColor(4);
  hiof3->SetLineColor(4);
  hiof3->Draw("E X0 same");
  
  cIsoDS->cd(4);
  gPad->Update();
  gPad->SetLogy(1);
  
  hios4->Scale(1,"width");
  hios4->SetMinimum(0.0001);
  hios4->SetMaximum(2000);
  hios4->SetMarkerStyle(20);
  hios4->SetMarkerSize(0.8);
  hios4->SetMarkerColor(2);
  hios4->SetLineColor(2);
  hios4->Draw();  
  hios4->GetXaxis()->SetTitle("Combined Iso Dep [GeV]");
  hios4->GetYaxis()->SetTitle("Number of Events / Bin");
  hios4->Draw("E X0");
  
  hiof4->Scale(1,"width");
  hiof4->SetMarkerStyle(21);
  hiof4->SetMarkerSize(0.8);
  hiof4->SetMarkerColor(4);
  hiof4->SetLineColor(4);
  hiof4->Draw("E X0 same");
  
  l1->DrawLine(6.,0.0001,6.,2000.);


  cIsoDS->cd();
  cIsoDS->Update();

  if(saveC){
    cIsoDS->SaveAs(outDir+"c_IsoDepVars"+vsSave+".eps");
    cIsoDS->SaveAs(outDir+"c_IsoDepVars"+vsSave+".pdf");
  }


  //Iso Alternate Variables - Sel Events
  TCanvas * cIsoAS = new TCanvas("cIsoAltSel","cIsoAltSel");
  cIsoAS->Clear();
  cIsoAS->Divide(2,2);

  TH1F* hins1 = (TH1F*) f1->Get( "select_1ph_2jets/PreselCut_chargedIso;1" );
  TH1F* hins2 = (TH1F*) f1->Get( "select_1ph_2jets/PreselCut_neutralIso;1" );
  TH1F* hins3 = (TH1F*) f1->Get( "select_1ph_2jets/PreselCut_photonIso;1" );

  TH1F* hinf1 = (TH1F*) f1->Get( "select_1ph_2jets_FO/PreselCut_chargedIso;1" );
  TH1F* hinf2 = (TH1F*) f1->Get( "select_1ph_2jets_FO/PreselCut_neutralIso;1" );
  TH1F* hinf3 = (TH1F*) f1->Get( "select_1ph_2jets_FO/PreselCut_photonIso;1" );

  cIsoAS->Update();
  cIsoAS->cd(1);
  gPad->Update();
  gPad->SetLogy(1);

  hins1->Scale(1,"width");
  hins1->SetMinimum(0.0001);
  hins1->SetMaximum(2000);
  hins1->SetMarkerStyle(20);
  hins1->SetMarkerSize(0.8);
  hins1->SetMarkerColor(2);
  hins1->SetLineColor(2);
  hins1->Draw();  
  hins1->GetXaxis()->SetTitle("PF Charged Iso Dep [GeV]");
  hins1->GetYaxis()->SetTitle("Number of Events / Bin");
  hins1->Draw("E X0");

  hinf1->Scale(1,"width");
  hinf1->SetMarkerStyle(21);
  hinf1->SetMarkerSize(0.8);
  hinf1->SetMarkerColor(4);
  hinf1->SetLineColor(4);
  hinf1->Draw("E X0 same");
    
  legend->Draw();

  as->DrawLatex(0.02, 0.93, outLumi2.c_str() );

  l1->DrawLine(2.6,0.0001,2.6,2000.);

  cIsoAS->cd(2);
  gPad->Update();
  gPad->SetLogy(1);
  
  hins2->Scale(1,"width");
  hins2->SetMinimum(0.0001);
  hins2->SetMaximum(2000);
  hins2->SetMarkerStyle(20);
  hins2->SetMarkerSize(0.8);
  hins2->SetMarkerColor(2);
  hins2->SetLineColor(2);
  hins2->Draw();
  hins2->GetXaxis()->SetTitle("PF Neutral Iso Dep [GeV]");
  hins2->GetYaxis()->SetTitle("Number of Events / Bin");
  hins2->Draw("E X0");

  hinf2->Scale(1,"width");
  hinf2->SetMarkerStyle(21);
  hinf2->SetMarkerSize(0.8);
  hinf2->SetMarkerColor(4);
  hinf2->SetLineColor(4);
  hinf2->Draw("E X0 same");

  l1->DrawLine(6.7,0.0001,6.7,2000.);
  l2->DrawLine(23.5,0.0001,23.5,2000.);
  
  cIsoAS->cd(3);
  gPad->Update();
  gPad->SetLogy(1);
  
  hins3->Scale(1,"width");
  hins3->SetMinimum(0.0001);
  hins3->SetMaximum(2000);
  hins3->SetMarkerStyle(20);
  hins3->SetMarkerSize(0.8);
  hins3->SetMarkerColor(2);
  hins3->SetLineColor(2);
  hins3->Draw();
  hins3->GetXaxis()->SetTitle("PF Photons Iso Dep [GeV]");
  hins3->GetYaxis()->SetTitle("Number of Events / Bin");
  hins3->Draw("E X0");

  hinf3->Scale(1,"width");
  hinf3->SetMarkerStyle(21);
  hinf3->SetMarkerColor(4);
  hinf3->SetLineColor(4);
  hinf3->Draw("E X0 same");

  l1->DrawLine(1.7,0.0001,1.7,2000.);
  l2->DrawLine(3.8,0.0001,3.8,2000.);
  
  cIsoAS->cd();
  cIsoAS->Update();

  if(saveC){
    cIsoAS->SaveAs(outDir+"c_IsoAltVars"+vsSave+".eps");
    cIsoAS->SaveAs(outDir+"c_IsoAltVars"+vsSave+".pdf");
  }


  //Iso Threshold Variables - Sel Events
  TCanvas * cIsoTS = new TCanvas("cIsoThrSel","cIsoThrSel");
  cIsoTS->Clear();
  cIsoTS->Divide(2,2);

  TH1F* hits1 = (TH1F*) f1->Get( "select_1ph_2jets/PreselCut_combisoTh;1" );
  TH1F* hits2 = (TH1F*) f1->Get( "select_1ph_2jets/PreselCut_combIsoCorTh;1" );
  TH2F* hits3 = (TH2F*) f1->Get( "select_1ph_2jets/PreselCut_combIsoOldVsNew;1" );

  TH1F* hitf1 = (TH1F*) f1->Get( "select_1ph_2jets_FO/PreselCut_combisoTh;1" );
  TH1F* hitf2 = (TH1F*) f1->Get( "select_1ph_2jets_FO/PreselCut_combIsoCorTh;1" );
  TH2F* hitf3 = (TH2F*) f1->Get( "select_1ph_2jets_FO/PreselCut_combIsoOldVsNew;1" );

  cIsoTS->Update();
  cIsoTS->cd(1);
  gPad->Update();
  gPad->SetLogy(1);

  hits1->Scale(1,"width");
  hits1->SetMinimum(0.0001);
  hits1->SetMaximum(2000);
  hits1->SetMarkerStyle(20);
  hits1->SetMarkerSize(0.8);
  hits1->SetMarkerColor(2);
  hits1->SetLineColor(2);
  hits1->Draw();
  hits1->GetXaxis()->SetTitle("Combined Iso Dep Thr [GeV]");
  hits1->GetYaxis()->SetTitle("Number of Events / Bin");
  hits1->Draw("E X0");
  
  hitf1->Scale(1,"width");
  hitf1->SetMarkerStyle(21);
  hitf1->SetMarkerSize(0.8);
  hitf1->SetMarkerColor(4);
  hitf1->SetLineColor(4);
  hitf1->Draw("E X0 same");
  
  legend->Draw();

  as->DrawLatex(0.02, 0.93, outLumi1.c_str() );

  l1->DrawLine(0.,0.0001,0.,2000.);

  cIsoTS->cd(2);
  gPad->Update();
  gPad->SetLogy(1);
  
  hits2->Scale(1,"width");
  hits2->SetMinimum(0.0001);
  hits2->SetMaximum(2000);
  hits2->SetMarkerStyle(20);
  hits2->SetMarkerSize(0.8);
  hits2->SetMarkerColor(2);
  hits2->SetLineColor(2);
  hits2->Draw();
  hits2->GetXaxis()->SetTitle("Combined Iso Alt Thr [GeV]");
  hits2->GetYaxis()->SetTitle("Number of Events / Bin");
  hits2->Draw("E X0");

  hitf2->Scale(1,"width");
  hitf2->SetMarkerStyle(21);
  hitf2->SetMarkerSize(0.8);
  hitf2->SetMarkerColor(4);
  hitf2->SetLineColor(4);
  hitf2->Draw("E X0 same");

  l1->DrawLine(0.,0.0001,0.,2000.);
  
  cIsoTS->cd(3);
  gPad->Update();
  gPad->SetLogy(0);
  
  hits3->GetXaxis()->SetTitle("Combined Iso Dep Thr [GeV]");
  hits3->GetYaxis()->SetTitle("Combined Iso Alt Thr [GeV]");
  hits3->SetTitle("#gamma Sample");
  hits3->Draw("colz");
  
  l1->DrawLine(-30.,0.,30.,0.);
  l1->DrawLine(0.,-30.,0.,30.);

  cIsoTS->cd(4);
  gPad->Update();
  gPad->SetLogy(0);
  
  hitf3->GetXaxis()->SetTitle("Combined Iso Dep Thr [GeV]");
  hitf3->GetYaxis()->SetTitle("Combined Iso Alt Thr [GeV]");
  hitf3->SetTitle("#gamma_{jet} FO");
  hitf3->Draw("colz");
  
  l1->DrawLine(-30.,0.,30.,0.);
  l1->DrawLine(0.,-30.,0.,30.);

  cIsoTS->cd();
  cIsoTS->Update();

  if(saveC){
    cIsoTS->SaveAs(outDir+"c_IsoThrVars"+vsSave+".eps");
    cIsoTS->SaveAs(outDir+"c_IsoThrVars"+vsSave+".pdf");
  }


  return;
}
