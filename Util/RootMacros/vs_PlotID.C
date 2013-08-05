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
void vs_PlotID() {

  Bool_t saveC = true;

  TString vsSave;
  vsSave = "_T03";
  TString lSave;
  lSave = "";

  TString outDir;
  outDir = "Plots_PhotonSusyAnalysis/plotID/";

  string inputFile = "/data/user/vsola/CMSSW_Releases/CMSSW_5_3_5/src/Plots_PhotonSusyAnalysis/Merged_QCD_PhotonJet_T03_PAT/mergedHistos.root";


  setMyTDRStyle();
  gROOT->SetStyle("mytdrStyle");

  gStyle->SetHistLineWidth(2);
  gStyle->UseCurrentStyle();
  gROOT->ForceStyle(1);


  TLegend *legend = new TLegend(0.6, 0.2, 0.9, 0.4, "");
  legend->SetFillColor(10);
  legend->SetFillStyle(1001);
  legend->SetTextSize(0.04);
  legend->SetBorderSize(0);
  legend->SetShadowColor(0);

  TLatex *as = new TLatex();
  as->SetNDC(true);
  as->SetTextColor(12);
  as->SetTextFont(43);
  as->SetTextSize(13);
  std::string outLumi = "CMS Work in Progress - MC  #sqrt{s} = 8 TeV  #geq 1 #gamma, #geq 2 jets";

  TLine *l1 = new TLine();
  l1->SetLineWidth(3);
  l1->SetLineStyle(2);

  TLine *l2 = new TLine();
  l2->SetLineWidth(1);
  l2->SetLineStyle(2);

  TFile* ff = TFile::Open( inputFile.c_str() );


  // Sigma variables
  TCanvas * cSig = new TCanvas("cSig","cSig");
  cSig->Clear();
  cSig->Divide(2,2);

  TH1F* hsie1 = (TH1F*) ff->Get( "select_1ph_2jets/PreselCut_sigmaietaieta" );
  TH1F* hsie2 = (TH1F*) ff->Get( "select_1ph_2jets_FO/PreselCut_sigmaietaieta" );
  TH1F* hsie3 = (TH1F*) ff->Get( "select_1ph_2jetsISO/PreselCut_sigmaietaieta" );
  TH1F* hsie4 = (TH1F*) ff->Get( "select_1ph_2jets_FOISO/PreselCut_sigmaietaieta" );

  cSig->Update();
  cSig->cd(1);
  gPad->Update();
  gPad->SetLogy(1);

  hsie1->SetMinimum(0.001);
  hsie1->SetMaximum(3000);
  hsie1->SetMarkerStyle(20);
  hsie1->SetMarkerSize(0.8);
  hsie1->SetMarkerColor(2);
  hsie1->SetLineColor(2);
  hsie1->Draw();
  
  hsie1->GetXaxis()->SetNdivisions(505);
  hsie1->GetXaxis()->SetTitle("#sigma_{i#etai#eta}");
  hsie1->GetYaxis()->SetTitle("Number of Events");
  hsie1->Draw("E X0");

  hsie2->SetMarkerStyle(21);
  hsie2->SetMarkerSize(0.8);
  hsie2->SetMarkerColor(4);
  hsie2->SetLineColor(4);
  hsie2->Draw("E X0 same");

  l1->DrawLine(0.001,0.001,0.001,3000.);
  l1->DrawLine(0.011,0.001,0.011,3000.);
  l2->DrawLine(0.012,0.001,0.012,3000.);


  legend->SetHeader("Sim."+lSave);
  legend->AddEntry(hsie1,"#gamma - Old ID","p");
  legend->AddEntry(hsie2,"#gamma - New ID","p");
  legend->Draw();

  as->DrawLatex(0.01, 0.93, outLumi.c_str() );


  cSig->Update();
  cSig->cd(2);
  gPad->Update();
  gPad->SetLogy(1);

  hsie3->SetMinimum(0.001);
  hsie3->SetMaximum(3000);
  hsie3->SetMarkerStyle(20);
  hsie3->SetMarkerSize(0.8);
  hsie3->SetMarkerColor(2);
  hsie3->SetLineColor(2);
  hsie3->Draw();
  
  hsie3->GetXaxis()->SetNdivisions(505);
  hsie3->GetXaxis()->SetTitle("#sigma_{i#etai#eta}");
  hsie3->GetYaxis()->SetTitle("Number of Events");
  hsie3->Draw("E X0");

  hsie4->SetMarkerStyle(21);
  hsie4->SetMarkerSize(0.8);
  hsie4->SetMarkerColor(4);
  hsie4->SetLineColor(4);
  hsie4->Draw("E X0 same");

  l1->DrawLine(0.011,0.001,0.011,3000.);
  l2->DrawLine(0.012,0.001,0.012,3000.);
  l1->DrawLine(0.014,0.001,0.014,3000.);
  l2->DrawLine(0.015,0.001,0.015,3000.);

  legend->Clear();
  legend->SetHeader("Sim."+lSave);
  legend->AddEntry(hsie3,"#gamma_{jet} - Old ID","p");
  legend->AddEntry(hsie4,"#gamma_{jet} - New ID","p");
  legend->Draw();


  TH1F* hsip1 = (TH1F*) ff->Get( "select_1ph_2jets/PreselCut_sigmaiphiiphi" );
  TH1F* hsip2 = (TH1F*) ff->Get( "select_1ph_2jets_FO/PreselCut_sigmaiphiiphi" );
  TH1F* hsip3 = (TH1F*) ff->Get( "select_1ph_2jetsISO/PreselCut_sigmaiphiiphi" );
  TH1F* hsip4 = (TH1F*) ff->Get( "select_1ph_2jets_FOISO/PreselCut_sigmaiphiiphi" );

  cSig->Update();
  cSig->cd(3);
  gPad->Update();
  gPad->SetLogy(1);

  hsip1->SetMinimum(0.0001);
  hsip1->SetMaximum(2000);
  hsip1->SetMarkerStyle(20);
  hsip1->SetMarkerSize(0.8);
  hsip1->SetMarkerColor(2);
  hsip1->SetLineColor(2);
  hsip1->Draw();
  
  hsip1->GetXaxis()->SetNdivisions(505);
  hsip1->GetXaxis()->SetTitle("#sigma_{i#phii#phi}");
  hsip1->GetYaxis()->SetTitle("Number of Events");
  hsip1->Draw("E X0");

  hsip2->SetMarkerStyle(21);
  hsip2->SetMarkerSize(0.8);
  hsip2->SetMarkerColor(4);
  hsip2->SetLineColor(4);
  hsip2->Draw("E X0 same");


  cSig->Update();
  cSig->cd(4);
  gPad->Update();
  gPad->SetLogy(1);

  hsip3->SetMinimum(0.0001);
  hsip3->SetMaximum(2000);
  hsip3->SetMarkerStyle(20);
  hsip3->SetMarkerSize(0.8);
  hsip3->SetMarkerColor(2);
  hsip3->SetLineColor(2);
  hsip3->Draw();
  
  hsip3->GetXaxis()->SetNdivisions(505);
  hsip3->GetXaxis()->SetTitle("#sigma_{i#eta i#eta}");
  hsip3->GetYaxis()->SetTitle("Number of Events");
  hsip3->Draw("E X0");

  hsip4->SetMarkerStyle(21);
  hsip4->SetMarkerSize(0.8);
  hsip4->SetMarkerColor(4);
  hsip4->SetLineColor(4);
  hsip4->Draw("E X0 same");


  cSig->cd();
  cSig->Update();

  if(saveC){
    cSig->SaveAs(outDir+"c_SigmaVars"+vsSave+".eps");
    cSig->SaveAs(outDir+"c_SigmaVars"+vsSave+".pdf");
  }



  // hadOverEm variables
  TCanvas * cHad = new TCanvas("cHad","cHad");
  cHad->Clear();
  cHad->Divide(2,2);

  TH1F* hhoe1 = (TH1F*) ff->Get( "select_1ph_2jets/PreselCut_hadronicOverEm" );
  TH1F* hhoe2 = (TH1F*) ff->Get( "select_1ph_2jets_FO/PreselCut_hadronicOverEm" );
  TH1F* hhoe3 = (TH1F*) ff->Get( "select_1ph_2jetsISO/PreselCut_hadronicOverEm" );
  TH1F* hhoe4 = (TH1F*) ff->Get( "select_1ph_2jets_FOISO/PreselCut_hadronicOverEm" );

  cHad->Update();
  cHad->cd(1);
  gPad->Update();
  gPad->SetLogy(1);

  hhoe1->SetMinimum(0.001);
  hhoe1->SetMaximum(3000);
  hhoe1->SetMarkerStyle(20);
  hhoe1->SetMarkerSize(0.8);
  hhoe1->SetMarkerColor(2);
  hhoe1->SetLineColor(2);
  hhoe1->Draw();
  
  hhoe1->GetXaxis()->SetNdivisions(505);
  hhoe1->GetXaxis()->SetTitle("hadronicOverEm");
  hhoe1->GetYaxis()->SetTitle("Number of Events");
  hhoe1->Draw("E X0");

  hhoe2->SetMarkerStyle(21);
  hhoe2->SetMarkerSize(0.8);
  hhoe2->SetMarkerColor(4);
  hhoe2->SetLineColor(4);
  hhoe2->Draw("E X0 same");

  l1->DrawLine(0.05,0.001,0.05,3000.);

  
  legend->Clear();
  legend->SetHeader("Sim."+lSave);
  legend->AddEntry(hhoe1,"#gamma - Old ID","p");
  legend->AddEntry(hhoe2,"#gamma - New ID","p");
  legend->Draw();
  
  as->DrawLatex(0.02, 0.93, outLumi.c_str() );


  cHad->Update();
  cHad->cd(2);
  gPad->Update();
  gPad->SetLogy(1);

  hhoe3->SetMinimum(0.001);
  hhoe3->SetMaximum(3000);
  hhoe3->SetMarkerStyle(20);
  hhoe3->SetMarkerSize(0.8);
  hhoe3->SetMarkerColor(2);
  hhoe3->SetLineColor(2);
  hhoe3->Draw();
  
  hhoe3->GetXaxis()->SetNdivisions(505);
  hhoe3->GetXaxis()->SetTitle("hadronicOverEm");
  hhoe3->GetYaxis()->SetTitle("Number of Events");
  hhoe3->Draw("E X0");

  hhoe4->SetMarkerStyle(21);
  hhoe4->SetMarkerSize(0.8);
  hhoe4->SetMarkerColor(4);
  hhoe4->SetLineColor(4);
  hhoe4->Draw("E X0 same");

  l1->DrawLine(0.05,0.001,0.05,3000.);
  
  legend->Clear();
  legend->SetHeader("Sim."+lSave);
  legend->AddEntry(hhoe3,"#gamma_{jet} - Old ID","p");
  legend->AddEntry(hhoe4,"#gamma_{jet} - New ID","p");
  legend->Draw();
  

  TH1F* hhtoe1 = (TH1F*) ff->Get( "select_1ph_2jets/PreselCut_hadTowOverEm" );
  TH1F* hhtoe2 = (TH1F*) ff->Get( "select_1ph_2jets_FO/PreselCut_hadTowOverEm" );
  TH1F* hhtoe3 = (TH1F*) ff->Get( "select_1ph_2jetsISO/PreselCut_hadTowOverEm" );
  TH1F* hhtoe4 = (TH1F*) ff->Get( "select_1ph_2jets_FOISO/PreselCut_hadTowOverEm" );

  cHad->Update();
  cHad->cd(3);
  gPad->Update();
  gPad->SetLogy(1);

  hhtoe1->SetMinimum(0.001);
  hhtoe1->SetMaximum(3000);
  hhtoe1->SetMarkerStyle(20);
  hhtoe1->SetMarkerSize(0.8);
  hhtoe1->SetMarkerColor(2);
  hhtoe1->SetLineColor(2);
  hhtoe1->Draw();
  
  hhtoe1->GetXaxis()->SetNdivisions(505);
  hhtoe1->GetXaxis()->SetTitle("hadTowOverEm");
  hhtoe1->GetYaxis()->SetTitle("Number of Events");
  hhtoe1->Draw("E X0");

  hhtoe2->SetMarkerStyle(21);
  hhtoe2->SetMarkerSize(0.8);
  hhtoe2->SetMarkerColor(4);
  hhtoe2->SetLineColor(4);
  hhtoe2->Draw("E X0 same");

  l1->DrawLine(0.05,0.001,0.05,3000.);


  cHad->Update();
  cHad->cd(4);
  gPad->Update();
  gPad->SetLogy(1);

  hhtoe3->SetMinimum(0.001);
  hhtoe3->SetMaximum(3000);
  hhtoe3->SetMarkerStyle(20);
  hhtoe3->SetMarkerSize(0.8);
  hhtoe3->SetMarkerColor(2);
  hhtoe3->SetLineColor(2);
  hhtoe3->Draw();
  
  hhtoe3->GetXaxis()->SetNdivisions(505);
  hhtoe3->GetXaxis()->SetTitle("hadTowOverEm");
  hhtoe3->GetYaxis()->SetTitle("Number of Events");
  hhtoe3->Draw("E X0");

  hhtoe4->SetMarkerStyle(21);
  hhtoe4->SetMarkerSize(0.8);
  hhtoe4->SetMarkerColor(4);
  hhtoe4->SetLineColor(4);
  hhtoe4->Draw("E X0 same");

  l1->DrawLine(0.05,0.001,0.05,3000.);

  cHad->cd();
  cHad->Update();

  if(saveC){
    cHad->SaveAs(outDir+"c_HadOvEmVars"+vsSave+".eps");
    cHad->SaveAs(outDir+"c_HadOvEmVars"+vsSave+".pdf");
  }



  // Met vs sigmaIetaIeta
  TCanvas * cMvsSie = new TCanvas("cMvsSie","cMvsSie");
  cMvsSie->Clear();
  cMvsSie->Divide(2,2);

  TH1F* hmse1 = (TH1F*) ff->Get( "select_1ph_2jets/PreselCut_metVssigmaietaieta" );
  TH1F* hmse2 = (TH1F*) ff->Get( "select_1ph_2jets_FO/PreselCut_metVssigmaietaieta" );
  TH1F* hmse3 = (TH1F*) ff->Get( "select_1ph_2jetsISO/PreselCut_metVssigmaietaieta" );
  TH1F* hmse4 = (TH1F*) ff->Get( "select_1ph_2jets_FOISO/PreselCut_metVssigmaietaieta" );

  cMvsSie->Update();
  cMvsSie->cd(1);
  gStyle->SetOptTitle(1);
  gStyle->SetTitleColor(1);
  gStyle->SetTitleBorderSize(0);
  gPad->Update();

  hmse1->SetTitle("Old ID - #gamma sel");
  hmse1->GetXaxis()->SetRangeUser(0.,500.);
  hmse1->GetXaxis()->SetNdivisions(510);
  hmse1->GetXaxis()->SetTitle("#slash{E}_{T} [GeV]");
  hmse1->GetYaxis()->SetTitle("#sigma_{i#etai#eta}");
  hmse1->Draw("colz");

  cMvsSie->Update();
  cMvsSie->cd(2);
  gPad->Update();

  hmse2->SetTitle("Old ID - #gamma_{jet} sel");
  hmse2->GetXaxis()->SetRangeUser(0.,500.);
  hmse2->GetXaxis()->SetNdivisions(510);
  hmse2->GetXaxis()->SetTitle("#slash{E}_{T} [GeV]");
  hmse2->GetYaxis()->SetTitle("#sigma_{i#etai#eta}");
  hmse2->Draw("colz");

  cMvsSie->Update();
  cMvsSie->cd(3);
  gPad->Update();

  hmse3->SetTitle("New ID - #gamma sel");
  hmse3->GetXaxis()->SetRangeUser(0.,500.);
  hmse3->GetXaxis()->SetNdivisions(510);
  hmse3->GetXaxis()->SetTitle("#slash{E}_{T} [GeV]");
  hmse3->GetYaxis()->SetTitle("#sigma_{i#etai#eta}");
  hmse3->Draw("colz");

  cMvsSie->Update();
  cMvsSie->cd(4);
  gPad->Update();

  hmse4->SetTitle("New ID - #gamma_{jet} sel");
  hmse4->GetXaxis()->SetRangeUser(0.,500.);
  hmse4->GetXaxis()->SetNdivisions(510);
  hmse4->GetXaxis()->SetTitle("#slash{E}_{T} [GeV]");
  hmse4->GetYaxis()->SetTitle("#sigma_{i#etai#eta}");
  hmse4->Draw("colz");



  cMvsSie->cd();
  cMvsSie->Update();

  if(saveC){
    cMvsSie->SaveAs(outDir+"c_MetVsSigEta"+vsSave+".eps");
    cMvsSie->SaveAs(outDir+"c_MetVsSigEta"+vsSave+".pdf");
  }


  // Met vs sigmaIphiIphi
  TCanvas * cMvsSip = new TCanvas("cMvsSip","cMvsSip");
  cMvsSip->Clear();
  cMvsSip->Divide(2,2);

  TH1F* hmsp1 = (TH1F*) ff->Get( "select_1ph_2jets/PreselCut_metVssigmaiphiiphi" );
  TH1F* hmsp2 = (TH1F*) ff->Get( "select_1ph_2jets_FO/PreselCut_metVssigmaiphiiphi" );
  TH1F* hmsp3 = (TH1F*) ff->Get( "select_1ph_2jetsISO/PreselCut_metVssigmaiphiiphi" );
  TH1F* hmsp4 = (TH1F*) ff->Get( "select_1ph_2jets_FOISO/PreselCut_metVssigmaiphiiphi" );

  cMvsSip->Update();
  cMvsSip->cd(1);
  gPad->Update();

  hmsp1->SetTitle("Old ID - #gamma sel");
  hmsp1->GetXaxis()->SetRangeUser(0.,500.);
  hmsp1->GetXaxis()->SetNdivisions(510);
  hmsp1->GetXaxis()->SetTitle("#slash{E}_{T} [GeV]");
  hmsp1->GetYaxis()->SetTitle("#sigma_{i#phii#phi}");
  hmsp1->Draw("colz");

  cMvsSip->Update();
  cMvsSip->cd(2);
  gPad->Update();

  hmsp2->SetTitle("Old ID - #gamma_{jet} sel");
  hmsp2->GetXaxis()->SetRangeUser(0.,500.);
  hmsp2->GetXaxis()->SetNdivisions(510);
  hmsp2->GetXaxis()->SetTitle("#slash{E}_{T} [GeV]");
  hmsp2->GetYaxis()->SetTitle("#sigma_{i#phii#phi}");
  hmsp2->Draw("colz");

  cMvsSip->Update();
  cMvsSip->cd(3);
  gPad->Update();

  hmsp3->SetTitle("New ID - #gamma sel");
  hmsp3->GetXaxis()->SetRangeUser(0.,500.);
  hmsp3->GetXaxis()->SetNdivisions(510);
  hmsp3->GetXaxis()->SetTitle("#slash{E}_{T} [GeV]");
  hmsp3->GetYaxis()->SetTitle("#sigma_{i#phii#phi}");
  hmsp3->Draw("colz");

  cMvsSip->Update();
  cMvsSip->cd(4);
  gPad->Update();

  hmsp4->SetTitle("New ID - #gamma_{jet} sel");
  hmsp4->GetXaxis()->SetRangeUser(0.,500.);
  hmsp4->GetXaxis()->SetNdivisions(510);
  hmsp4->GetXaxis()->SetTitle("#slash{E}_{T} [GeV]");
  hmsp4->GetYaxis()->SetTitle("#sigma_{i#phii#phi}");
  hmsp4->Draw("colz");


  cMvsSip->cd();
  cMvsSip->Update();

  if(saveC){
    cMvsSip->SaveAs(outDir+"c_MetVsSigPhi"+vsSave+".eps");
    cMvsSip->SaveAs(outDir+"c_MetVsSigPhi"+vsSave+".pdf");
  }


  // Met vs hadronicOverEm
  TCanvas * cMvsHoe = new TCanvas("cMvsHoe","cMvsHoe");
  cMvsHoe->Clear();
  cMvsHoe->Divide(2,2);

  TH1F* hmhe1 = (TH1F*) ff->Get( "select_1ph_2jets/PreselCut_metVshadronicOverEm" );
  TH1F* hmhe2 = (TH1F*) ff->Get( "select_1ph_2jets_FO/PreselCut_metVshadronicOverEm" );
  TH1F* hmhe3 = (TH1F*) ff->Get( "select_1ph_2jetsISO/PreselCut_metVshadronicOverEm" );
  TH1F* hmhe4 = (TH1F*) ff->Get( "select_1ph_2jets_FOISO/PreselCut_metVshadronicOverEm" );

  cMvsHoe->Update();
  cMvsHoe->cd(1);
  gPad->Update();

  hmhe1->SetTitle("Old ID - #gamma sel");
  hmhe1->GetXaxis()->SetRangeUser(0.,500.);
  hmhe1->GetXaxis()->SetNdivisions(510);
  hmhe1->GetXaxis()->SetTitle("#slash{E}_{T} [GeV]");
  hmhe1->GetYaxis()->SetTitle("hadronicOverEm");
  hmhe1->Draw("colz");

  cMvsHoe->Update();
  cMvsHoe->cd(2);
  gPad->Update();

  hmhe2->SetTitle("Old ID - #gamma_{jet} sel");
  hmhe2->GetXaxis()->SetRangeUser(0.,500.);
  hmhe2->GetXaxis()->SetNdivisions(510);
  hmhe2->GetXaxis()->SetTitle("#slash{E}_{T} [GeV]");
  hmhe2->GetYaxis()->SetTitle("hadronicOverEm");
  hmhe2->Draw("colz");

  cMvsHoe->Update();
  cMvsHoe->cd(3);
  gPad->Update();

  hmhe3->SetTitle("New ID - #gamma sel");
  hmhe3->GetXaxis()->SetRangeUser(0.,500.);
  hmhe3->GetXaxis()->SetNdivisions(510);
  hmhe3->GetXaxis()->SetTitle("#slash{E}_{T} [GeV]");
  hmhe3->GetYaxis()->SetTitle("hadronicOverEm");
  hmhe3->Draw("colz");

  cMvsHoe->Update();
  cMvsHoe->cd(4);
  gPad->Update();

  hmhe4->SetTitle("New ID - #gamma_{jet} sel");
  hmhe4->GetXaxis()->SetRangeUser(0.,500.);
  hmhe4->GetXaxis()->SetNdivisions(510);
  hmhe4->GetXaxis()->SetTitle("#slash{E}_{T} [GeV]");
  hmhe4->GetYaxis()->SetTitle("hadronicOverEm");
  hmhe4->Draw("colz");


  cMvsHoe->cd();
  cMvsHoe->Update();

  if(saveC){
    cMvsHoe->SaveAs(outDir+"c_MetVsHadEm"+vsSave+".eps");
    cMvsHoe->SaveAs(outDir+"c_MetVsHadEm"+vsSave+".pdf");
  }


  // Met vs hadTowOverEm
  TCanvas * cMvsHtoe = new TCanvas("cMvsHtoe","cMvsHtoe");
  cMvsHtoe->Clear();
  cMvsHtoe->Divide(2,2);

  TH1F* hmhte1 = (TH1F*) ff->Get( "select_1ph_2jets/PreselCut_metVshadTowOverEm" );
  TH1F* hmhte2 = (TH1F*) ff->Get( "select_1ph_2jets_FO/PreselCut_metVshadTowOverEm" );
  TH1F* hmhte3 = (TH1F*) ff->Get( "select_1ph_2jetsISO/PreselCut_metVshadTowOverEm" );
  TH1F* hmhte4 = (TH1F*) ff->Get( "select_1ph_2jets_FOISO/PreselCut_metVshadTowOverEm" );

  cMvsHtoe->Update();
  cMvsHtoe->cd(1);
  gPad->Update();

  hmhte1->SetTitle("Old ID - #gamma sel");
  hmhte1->GetXaxis()->SetRangeUser(0.,500.);
  hmhte1->GetXaxis()->SetNdivisions(510);
  hmhte1->GetXaxis()->SetTitle("#slash{E}_{T} [GeV]");
  hmhte1->GetYaxis()->SetTitle("hadTowOverEm");
  hmhte1->Draw("colz");

  cMvsHtoe->Update();
  cMvsHtoe->cd(2);
  gPad->Update();

  hmhte2->SetTitle("Old ID - #gamma_{jet} sel");
  hmhte2->GetXaxis()->SetRangeUser(0.,500.);
  hmhte2->GetXaxis()->SetNdivisions(510);
  hmhte2->GetXaxis()->SetTitle("#slash{E}_{T} [GeV]");
  hmhte2->GetYaxis()->SetTitle("hadTowOverEm");
  hmhte2->Draw("colz");

  cMvsHtoe->Update();
  cMvsHtoe->cd(3);
  gPad->Update();

  hmhte3->SetTitle("New ID - #gamma sel");
  hmhte3->GetXaxis()->SetRangeUser(0.,500.);
  hmhte3->GetXaxis()->SetNdivisions(510);
  hmhte3->GetXaxis()->SetTitle("#slash{E}_{T} [GeV]");
  hmhte3->GetYaxis()->SetTitle("hadTowOverEm");
  hmhte3->Draw("colz");

  cMvsHtoe->Update();
  cMvsHtoe->cd(4);
  gPad->Update();

  hmhte4->SetTitle("New ID - #gamma_{jet} sel");
  hmhte4->GetXaxis()->SetRangeUser(0.,500.);
  hmhte4->GetXaxis()->SetNdivisions(510);
  hmhte4->GetXaxis()->SetTitle("#slash{E}_{T} [GeV]");
  hmhte4->GetYaxis()->SetTitle("hadTowOverEm");
  hmhte4->Draw("colz");


  cMvsHtoe->cd();
  cMvsHtoe->Update();

  if(saveC){
    cMvsHtoe->SaveAs(outDir+"c_MetVsHadTowEm"+vsSave+".eps");
    cMvsHtoe->SaveAs(outDir+"c_MetVsHadTowEm"+vsSave+".pdf");
  }



  return;
}
