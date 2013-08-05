#ifndef rootFileToPsandJpg_C_
#define rootFileToPsandJpg_C_
#ifndef __CINT__ 
#include <TKey.h>
#include <TImage.h>
#include <TError.h>
#include <TFile.h>
#include "Util/OwnUtil/src/HistoDrawUtil.h"

#endif

using namespace std;
void invertHistosTypeIIForDPG11() {
	HistoDrawUtil::setMyTDRStyle();
	gROOT->SetStyle("mytdrStyle");
	gStyle->UseCurrentStyle();
	//TFile *_file0 = TFile::Open("DPG11_Plots/KorrekturVsZpt.root");
	TFile *_file0 = TFile::Open("DPG11_Plots/UmeasVsZpt.root");
	gStyle->UseCurrentStyle();
	_file0->FindObjectAny("c1");
	//TH1F * histo = (TH1F*) c1->FindObject("UC_paraBisectSum_All_corrDeltaTrueVsTrueRel_1");
	TH1F * histo = (TH1F*) c1->FindObject("paraBisectSum_All_ProjUMeasVsUtruePara_1");
	TCanvas * c2=new TCanvas("inverted");

	if (histo != 0) {
		histo->Draw();
		for (int b = 0; b <= ((TH1*) histo)->GetNbinsX(); b++) {
			if (histo->GetBinLowEdge(b) > -70 && histo->GetBinLowEdge(b) <= 0) {
				cout<<"bin no:"<<b<<" 	lowEdge:"<<histo->GetBinLowEdge(b)<<endl;
				int binToFill=histo->FindBin(abs(histo->GetBinLowEdge(b)));
				histo->SetBinContent(binToFill,histo->GetBinContent(b));
				histo->SetBinError(binToFill,histo->GetBinError(b));
				histo->GetYaxis()->SetRangeUser(0,60);
				histo->GetXaxis()->SetRangeUser(0,70);
				histo->SetMarkerStyle(20);
				histo->SetMarkerSize(0.6);
			}
		}
		histo->Draw();
	} else {
		cout << "histo not found" << endl;
	}

}
;
#endif
