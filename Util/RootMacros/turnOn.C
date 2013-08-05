#include <TFile.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TString.h>
#include <TStyle.h>
#include <TGraphAsymmErrors.h>
#include <TMath.h>
#include <TF1.h>
#include <TLatex.h>
#include <TLegend.h>
#include <TText.h>
#include <Util/OwnUtil/src/HistoDrawUtil.h>

double turnOn_curve(double* x, double* p) {
  double plateau = p[0];
  double center = p[1];
  double width = p[2]*sqrt(2);

  return (plateau/2) * (1 + TMath::Erf((x[0]-center)/width));
}


void turnOn(TString ds = "Photon", bool print=false) {

HistoDrawUtil::setMyTDRStyle();
	gROOT->SetStyle("mytdrStyle");

	gStyle->SetHistLineWidth(2);
	gStyle->UseCurrentStyle();
	gROOT->ForceStyle(1);
  gStyle->SetPadGridX(1);
  gStyle->SetPadGridY(1);
  gStyle->SetOptFit(0);

  bool useFit = false;

  float window = 5.0;


  // trigger period
  // before 165970, n90 >= 2 was used for HT
  // after 165970, n90hits was used for HT
  // after 170249, |eta| < 3 is used for HT. It was 5 before

  // period0 : pho32_26, 160329 - 164923 (191.5/pb)
  // period1 : pho36_22, 161205 - 166978 (820.8/pb)
  // period2 : pho40_28, 164924 - 173211 (1612.6/pb)
  // period3 : pho44_34, 170065 - 178410 (968/pb, upto 178078)
  // period4 : pho36_iso_pho22_iso, 165922 - 178410 (2781/pb)
  // period5 : pho36_iso_pho22_iso, 178411 - 180252 (1520/pb) total period4+5 = 4301/pb

  const int NP = 10;

  TString targetTrigger[NP] = {
    "HLT_Photon32_CaloIdL_Photon26_CaloIdL_v",
    "HLT_Photon36_CaloIdL_Photon22_CaloIdL_v",
    "HLT_Photon40_CaloIdL_Photon28_CaloIdL_v",
    "HLT_Photon44_CaloIdL_Photon34_CaloIdL_v",
    "HLT_Photon36_CaloIdL_IsoVL_Photon22_CaloIdL_IsoVL_v",
    "HLT_Photon70_CaloIdL_HT200_v",
    "HLT_Photon70_CaloIdL_HT300_v",
    "HLT_Photon70_CaloIdL_HT350_v",
    "HLT_Photon70_CaloIdL_HT400_v",
    "HLT_Photon70_CaloIdXL_HT400_v"
  };

  const int threshold[NP][2] = {
    {32,26},
    {36,22},
    {40,28},
    {44,34},
    {36,22},
    {70,200},
    {70,300},
    {70,350},
    {70,400},
    {70,400}
  };

  std::vector<TString> baseTriggers[NP];
  int run_ranges[NP][2];

  // HLT_Photon32_CaloIdL_Photon26_CaloIdL_v
  baseTriggers[0].push_back("HLT_Photon26_Photon18_v");
  run_ranges[0][0] = 160329;
  run_ranges[0][1] = 164923;

  // HLT_Photon36_CaloIdL_Photon22_CaloIdL_v
  baseTriggers[1].push_back("HLT_Photon26_Photon18_v");
  run_ranges[1][0] = 161205;
  run_ranges[1][1] = 166978;

  // HLT_Photon40_CaloIdL_Photon28_CaloIdL_v
  baseTriggers[2].push_back("HLT_Photon36_CaloIdVL_Photon22_CaloIdVL_v");
  run_ranges[2][0] = 164924;
  run_ranges[2][1] = 173211;

  // HLT_Photon44_CaloIdL_Photon34_CaloIdL_v
  baseTriggers[3].push_back("HLT_Photon36_CaloIdVL_Photon22_CaloIdVL_v");
  run_ranges[3][0] = 170065;
  run_ranges[3][1] = 178410;

  // HLT_Photon36_CaloIdL_IsoVL_Photon22_CaloIdL_IsoVL_v
  baseTriggers[4].push_back("HLT_Photon26_Photon18_v");
  run_ranges[4][0] = 165922;
  run_ranges[4][1] = 180252;

  // HLT_Photon70_CaloIdL_HT200_v
  baseTriggers[5].push_back("HLT_Photon30_CaloIdVL_v");
  run_ranges[5][0] = 160329;
  run_ranges[5][1] = 164923;

  // HLT_Photon70_CaloIdL_HT300_v
  baseTriggers[6].push_back("HLT_Photon50_CaloIdVL_v");
  run_ranges[6][0] = 161205;
  run_ranges[6][1] = 166978;

  // HLT_Photon70_CaloIdL_HT350_v
  baseTriggers[7].push_back("HLT_Photon50_CaloIdVL_v");
  run_ranges[7][0] = 164924;
  run_ranges[7][1] = 173211;

  // HLT_Photon70_CaloIdL_HT400_v
  baseTriggers[8].push_back("HLT_Photon50_CaloIdVL_v");
  run_ranges[8][0] = 170065;
  run_ranges[8][1] = 178410;

  // HLT_Photon70_CaloIdXL_HT400_v
  baseTriggers[9].push_back("HLT_Photon50_CaloIdVL_v");
  baseTriggers[9].push_back("HLT_Photon60_CaloIdL_HT300_v");
  run_ranges[9][0] = 178411;
  run_ranges[9][1] = 180252;


  TString leg1_xlabel = "1st photon p_{T} [GeV]";
  TString leg2_xlabel[NP] = {
    "trailing photon p_{T} (GeV/c)",
    "trailing photon p_{T} (GeV/c)",
    "trailing photon p_{T} (GeV/c)",
    "trailing photon p_{T} (GeV/c)",
    "trailing photon p_{T} (GeV/c)",
    "HT [GeV]",
    "HT [GeV]",
    "HT [GeV]",
    "HT [GeV]",
    "HT [GeV]"
  };

  TString lumi[NP] = {
    "195",
    "790",
    "1560",
    "2595",
    "4150",
    "195",
    "790",
    "1560",
    "2.6",
    "835"
  };


  TFile* f = new TFile("hist_trigger_"+ds+".root","READ");


  const int NH = 2; // for denominator, numerator
  TString tag_hist[NH] = {"denom", "numer"};
  enum TAG_HIST {DENOM=0,NUMER};

  TH1F* pt_eff_leg1[NP][NH];
  TH1F* pt_eff_leg2[NP][NH];

  TH1F* pt_purity_leg1[NP][NH];
  TH1F* pt_purity_leg2[NP][NH];

  TH1F* pt70_eff[NH];

  int rebin = 1;

  for(int i=0; i<NP; i++) {
    for(int k=0; k<NH; k++) {



      bool had = targetTrigger[i].Contains("HT");
      if(had) rebin = 5;

      pt_eff_leg1[i][k] = (TH1F*) f->Get("pt_eff_leg1_"+targetTrigger[i]+"_"+tag_hist[k]);
      pt_eff_leg1[i][k]->Sumw2();
      pt_eff_leg1[i][k]->Rebin(rebin);
      pt_purity_leg1[i][k] = (TH1F*) f->Get("pt_purity_leg1_"+targetTrigger[i]+"_"+tag_hist[k]);
      pt_purity_leg1[i][k]->Sumw2();
      pt_purity_leg1[i][k]->Rebin(rebin);

      if(had){
	if(targetTrigger[i].Contains("HT200")) pt70_eff[k] = (TH1F*)pt_eff_leg1[i][k]->Clone("_70");
	else pt70_eff[k]->Add(pt_eff_leg1[i][k]);
      }

      pt_eff_leg2[i][k] = (TH1F*) f->Get("pt_eff_leg2_"+targetTrigger[i]+"_"+tag_hist[k]);
      pt_eff_leg2[i][k]->Sumw2();
      pt_eff_leg2[i][k]->Rebin(rebin);
      pt_purity_leg2[i][k] = (TH1F*) f->Get("pt_purity_leg2_"+targetTrigger[i]+"_"+tag_hist[k]);
      pt_purity_leg2[i][k]->Sumw2();
      pt_purity_leg2[i][k]->Rebin(rebin);



    }
  } // for i

  TGraphAsymmErrors* eff_leg1[NP];
  TGraphAsymmErrors* eff_leg2[NP];
  TGraphAsymmErrors* purity_leg1[NP];
  TGraphAsymmErrors* purity_leg2[NP];

  TCanvas* can[NP];

//  TLatex* lat = new TLatex(0.16,0.8,"CMS Preliminary 2011");
//  lat->SetNDC(true);
//  lat->SetTextSize(0.04);

  for(int i=0; i<NP; i++) {
  	if(targetTrigger[i].Contains("HLT_Photon70_CaloIdL_HT400")){
    float leg1_width = threshold[i][0]*0.1; 
    float leg2_width = threshold[i][1]*0.1; 

    // for eff leg1
//    eff_leg1[i] = new TGraphAsymmErrors;
//    eff_leg1[i]->Divide(pt_eff_leg1[i][NUMER],pt_eff_leg1[i][DENOM]);
//    eff_leg1[i]->SetTitle(";"+leg1_xlabel+";Efficiency");
//    can[i] = new TCanvas("trigger_eff_leg1_"+targetTrigger[i],"trigger_eff_leg1_"+targetTrigger[i],800,600);
//    TF1* f1_leg1 = new TF1("f1_eff_leg1_"+targetTrigger[i],turnOn_curve,10,100,3);
//    f1_leg1->SetParNames("plateau","center","width");
//    f1_leg1->SetParameters(1,threshold[i][0],leg1_width);
//    eff_leg1[i]->Draw("AP");
//    if(useFit) eff_leg1[i]->Fit(f1_leg1,"r","",threshold[i][0]-window*leg1_width,threshold[i][0]+window*leg1_width);
//    eff_leg1[i]->GetXaxis()->SetRangeUser(threshold[i][0]-window*leg1_width,threshold[i][0]+window*leg1_width);
//    eff_leg1[i]->GetYaxis()->SetRangeUser(0,1.2);
//  //  lat->Draw("same");
    TLatex* lat1 = new TLatex(0.16,0.85,"#int#it{L}dt = "+lumi[i] + " fb^{-1}");
    lat1->SetNDC(true);
    lat1->SetTextSize(0.04);
//    lat1->Draw("same");
//    TLatex* lat2 = new TLatex(0.16,0.85,targetTrigger[i].ReplaceAll("_v","").Data());
//    lat2->SetNDC(true);
//    lat2->SetTextSize(0.04);
//    //lat2->Draw("same");
//
//    if(print){
//      can[i]->Print("",".gif");
//      can[i]->Print("",".eps");
//    }
    
    // for eff leg2
    eff_leg2[i] = new TGraphAsymmErrors;
    eff_leg2[i]->Divide(pt_eff_leg2[i][NUMER],pt_eff_leg2[i][DENOM]);
    eff_leg2[i]->SetTitle(";"+leg2_xlabel[i]+";Efficiency");
    can[i] = new TCanvas("trigger_eff_leg2_"+targetTrigger[i],"trigger_eff_leg2_"+targetTrigger[i]);
    TF1* f1_leg2 = new TF1("f1_eff_leg2_"+targetTrigger[i],turnOn_curve,10,100,3);
    f1_leg2->SetParNames("plateau","center","width");
    f1_leg2->SetParameters(1,threshold[i][1],leg2_width);
    eff_leg2[i]->Draw("AP");
    if(useFit) eff_leg2[i]->Fit(f1_leg2,"r","",threshold[i][1]-window*leg2_width,threshold[i][1]+window*leg2_width);
    eff_leg2[i]->GetXaxis()->SetRangeUser(threshold[i][1]-window*leg2_width,threshold[i][1]+window*leg2_width);
    eff_leg2[i]->GetYaxis()->SetRangeUser(0,1.2);
    //lat->Draw("same");
    //lat1->Draw("same");
    HistoDrawUtil::drawCmsPrel((double)2600, "", false, 0, false," ",false,false,true);
    //lat2->Draw("same");
    if(true){
    //  can[i]->Print("",".gif");
      can[i]->Print("",".eps");
      can[i]->Print("",".pdf");
    }
  	}
  }// for i


  // combined histograms for the first leg of photon_HT triggers

  TCanvas* can70 = new TCanvas("trigger_eff_leg1_Photon70_CaloIdL_HT","trigger_eff_leg1_Photon70_CaloIdL_HT");

  leg1_width = 70*0.1;

  TGraphAsymmErrors* eff_pt70 = new TGraphAsymmErrors;
  eff_pt70->Divide(pt70_eff[1],pt70_eff[0]);
  eff_pt70->SetTitle(";"+leg1_xlabel+";Efficiency");
  TF1* f1_leg1 = new TF1("f1_eff_leg1_Photon70_CaloIdL_HT",turnOn_curve,10,100,3);
  f1_leg1->SetParNames("plateau","center","width");
  f1_leg1->SetParameters(1,70,leg1_width);
  eff_pt70->Draw("AP");
  if(useFit) eff_pt70->Fit(f1_leg1,"r","",70-window*leg1_width,70+window*leg1_width);
  eff_pt70->GetXaxis()->SetRangeUser(70-window*leg1_width,70+window*leg1_width);
  eff_pt70->GetYaxis()->SetRangeUser(0,1.2);
  //lat->Draw("same");
  TLatex* lat1 = new TLatex(0.16,0.85,"#int#it{L}dt = 4.2 fb^{-1}");
  lat1->SetNDC(true);
  lat1->SetTextSize(0.04);
  //lat1->Draw("same");
  TLatex* lat2 = new TLatex(0.16,0.85,"Photon70_CaloIdL_HT");
  lat2->SetNDC(true);
  lat2->SetTextSize(0.04);
 // lat2->Draw("same");
  HistoDrawUtil::drawCmsPrel((double)4200.0, "", false, 0, false," ",false,false,true);
   if(true){
  //  can70->Print("",".gif");
    can70->Print("",".eps");
    can70->Print("",".pdf");
  }


}
