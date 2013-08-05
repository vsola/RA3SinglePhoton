#ifndef rootFileToPsandJpg_C_
#define rootFileToPsandJpg_C_
#ifndef __CINT__ 
#include <TKey.h>
#include <TImage.h>
#include <TError.h>
#include <TFile.h>

#endif

using namespace std;
void mergeMetHistos() {
	//	HistoDrawUtil::useMyStyle();
	//	gROOT->SetStyle("myStyle");
	//	gStyle->UseCurrentStyle();
	//	gStyle->SetOptStat(110000);
	//	gStyle->SetOptTitle(1);


	TFile *input = new TFile("MetSigmaComp_metSigma900GeVFineBins.root","");
	TFile *input2 = new TFile("MetSigmaComp_metSigma900GeVFineBinsMinPt0.root","");
	TFile *output = new TFile("MergeMetHistos.root","recreate");

	string canvasname="1D_met_All_";
	string histoname="All_met_Type1UC";
	TH1F* histo=0;
	TLegend* legend=0;
	TCanvas * c=(TCanvas*)input->FindObjectAny(canvasname.c_str());
	cout<<"canvas read:"<<c->GetName()<<endl;
	cout<<"open second canvas"<<endl;
	TCanvas * c2=(TCanvas*)input2->FindObjectAny(canvasname.c_str());
	TIter nextkeyCanv(c->GetListOfPrimitives());
	while ((keyCanv = (TKey*)nextkeyCanv())) {
		if (keyCanv->IsA()->InheritsFrom("TLegend") ) {
			legend=(TLegend*)keyCanv;
		}
		if (keyCanv->IsA()->InheritsFrom("TH1") ) {
			cout<<"histoname:"<<keyCanv->GetName()<<endl;
			if (keyCanv->GetName()==histoname) {
				histo=(TH1F*)keyCanv;
				cout<<"histo found"<<endl;
				c2->Update();
				histo->Draw("same");
				c2->Update();
			}
		}
	}
	legend->Draw("same");
	output->WriteTObject(c2, 0, "overwrite");

	string canvasname_2="1D_met_All_";
	string histoname_2="All_met_Type1";
	TH1F* histo_2=0;
	TLegend* legend_2=0;
	TCanvas * c_2=(TCanvas*)input->FindObjectAny(canvasname_2.c_str());
	cout<<"canvas read:"<<c->GetName()<<endl;

	cout<<"open second canvas"<<endl;
	TCanvas * c2_2=(TCanvas*)input2->FindObjectAny(canvasname_2.c_str());
	TIter nextkeyCanv2_2(c2_2->GetListOfPrimitives());

	while ((keyCanv = (TKey*)nextkeyCanv2_2())) {
		if (keyCanv->IsA()->InheritsFrom("TLegend") ) {
			legend_2=(TLegend*)keyCanv;
		}
		if (keyCanv->IsA()->InheritsFrom("TH1") ) {
			cout<<"histoname:"<<keyCanv->GetName()<<endl;
			if (keyCanv->GetName()==histoname) {

			}
		}
	}
	TIter nextkeyCanv_2(c_2->GetListOfPrimitives());
	int i=0;
	while ((keyCanv = (TKey*)nextkeyCanv_2())) {

		if (keyCanv->IsA()->InheritsFrom("TH1") ) {
			cout<<"histoname:"<<keyCanv->GetName()<<endl;
			if (keyCanv->GetName()==histoname_2) {
				i++;
				histo_2=(TH1F*)keyCanv;
				histo_2->SetMarkerStyle(4);
				histo_2->SetLineStyle(2);
				if (i==2) {
					histo_2->SetLineColor(6);
					histo_2->SetMarkerColor(6);
				}
				if (i==1) {
					histo_2->SetLineColor(35);
					histo_2->SetMarkerColor(35);
				}
				legend_2->AddEntry(histo_2, "Test", "p");
				cout<<"histo found"<<histo_2->GetTitle()<<endl;
				c2_2->Update();
				histo_2->Draw("same");
				c2_2->Update();
			}
		}
	}
	legend_2->Draw("same");
	output->WriteTObject(c2_2, "metMinPt0Corr", "overwrite");

	string canvasname_3="1D_met_All_";
	string canvasname_4="1D_mht_All_";
	string histoname_3="All_met_Type1";
	TH1F* histo_3=0;
	TLegend* legend_3=0;
	TCanvas * c_3=(TCanvas*)input2->FindObjectAny(canvasname_3.c_str());
	cout<<"canvas read:"<<c_3->GetName()<<endl;
	
	cout<<"open second canvas"<<endl;
	TCanvas * c2_3=(TCanvas*)input2->FindObjectAny(canvasname_4.c_str());
	TIter nextkeyCanv2_3(c2_3->GetListOfPrimitives());
	while ((keyCanv = (TKey*)nextkeyCanv2_3())) {
			if (keyCanv->IsA()->InheritsFrom("TLegend") ) {
				legend_3=(TLegend*)keyCanv;
			}
		}
	TIter nextkeyCanv_3(c_3->GetListOfPrimitives());
	int i=0;
	while ((keyCanv = (TKey*)nextkeyCanv_3())) {
		
		if (keyCanv->IsA()->InheritsFrom("TH1") ) {
			cout<<"histoname:"<<keyCanv->GetName()<<endl;
			if (keyCanv->GetName()==histoname_3) {
				histo_3=(TH1F*)keyCanv;
				cout<<"histo found"<<histo_3->GetName()<<endl;
				histo_3->SetMarkerStyle(4);
				histo_3->SetLineStyle(2);
				i++;
				if (i==2) {
					histo_3->SetLineColor(6);
					histo_3->SetMarkerColor(6);
				}
				if (i==1) {
					histo_3->SetLineColor(35);
					histo_3->SetMarkerColor(35);
				}
				legend_3->AddEntry(histo_3, "Test", "p");

				c2_3->Update();
				histo_3->Draw("same");
				c2_3->Update();
			}
		}
	}
	legend_3->Draw("same");
	output->WriteTObject(c2_3, "metVsMhtMinPt0", "overwrite");
}
#endif
