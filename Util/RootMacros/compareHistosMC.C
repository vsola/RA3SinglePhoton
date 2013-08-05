#ifndef rootFileToPsandJpg_C_
#define rootFileToPsandJpg_C_
#ifndef __CINT__ 
#include <TKey.h>
#include <TImage.h>
#include <TError.h>
#include <TFile.h>

#endif

using namespace std;
void compareHistosMC() {
	gStyle->SetTitleSize(0.06, "XY");
	gStyle->SetLabelSize(0.04, "XY");
	gStyle->SetTitleOffset(1.2, "XY");

	gStyle->SetPadBottomMargin(0.2);
	gStyle->SetPadLeftMargin(0.2);
	gStyle->SetPadRightMargin(0.15);
	gStyle->SetDrawOption("tics");

	vector<string> canvasnames;
	canvasnames.push_back("NoiseCleanUpjetpt_DataLevel");
	canvasnames.push_back("NoiseCleanUpmet_Evt_DataLevel");
	canvasnames.push_back("NoiseCleanUpmjgj_DataLevel_DijetBalance");

	vector<string> histnames;
	histnames.push_back("cleanedAlljetpt_DataLevel");
	histnames.push_back("cleanedAllmet_Evt_DataLevel");
	histnames.push_back("cleanedAllmjgj_DataLevel_DijetBalance");

	TFile *output = new TFile(("HistoMCComparisonResults.root"),"recreate");
	TH1F * compHisto=0;
	
	TH1F * oldHisto=0;
	TCanvas * c=0;
	TLegend *legend=0;

	vector<string> inputfiles;
	inputfiles.push_back("tree_FCV1_Pt33Bc17_2360GeV.root");
	inputfiles.push_back("tree_FCV1_Pt33Bc17_2360GeVMC.root");

	//---------compare 'compHisto' mj-gj/gj
	TFile *input1 = new TFile((inputfiles.at(0)).c_str(),"read");
	cout<<"inputfile:"<<input1->GetName()<<endl;
	TIter nextkey(input1->GetListOfKeys());
	TKey *key;

	while (key = (TKey*)nextkey() ) {

		string name=key->ReadObj()->GetName();
		//cout<<"NAME:"<<name<<endl;
		TObject* obj=(TObject*)key->ReadObj();
		for (int canvN=0; canvN!=canvasnames.size(); ++canvN) {
			string canvasName=canvasnames.at(canvN);

			if (canvasName==obj->GetName()) {
				cout<<"orig canvas name:"<<canvasName<<endl;
				compHisto=0;
				c=(TCanvas*) obj;
				legend=(TLegend*)c->FindObject("TPave");
				c->Draw("");
				c->Update();
				for (int i=1; i!=inputfiles.size(); ++i) {

					TFile *input = new TFile((inputfiles.at(i)).c_str(),"read");
					cout<<"inputfile2:"<<input->GetName()<<endl;
					string histname=histnames.at(canvN);
					cout<<"read comp histo:"<<histname<<endl;
					TCanvas * compCanvas = (TCanvas*)input->FindObjectAny((canvasnames.at(canvN)).c_str());
					cout<<"compCanvas:"<<compCanvas<<endl;
					cout<<"compCanvasName:"<<compCanvas->GetName()<<endl;

					compHisto = (TH1F*)compCanvas->FindObject(histname.c_str());
					compHisto->Sumw2();
					cout<<"compHisto:"<<compHisto<<endl;
					input->Close();

					c->cd();
					c->Update();
					//compHisto->AppendPad();
					compHisto->SetLineColor(44);
					compHisto->SetFillColor(44);
					compHisto->SetFillStyle(3004);
					cout<<"compHist: "<<compHisto->GetEntries()<<endl;
					oldHisto=(TH1F*)c->FindObject(histname.c_str());
					cout<<"oldHist: "<<oldHisto<<endl;
					if (compHisto->GetEntries()!=0 && oldHisto->GetEntries()!=0) {
						compHisto->Scale(oldHisto->GetEntries()
								/compHisto->GetEntries());
					}
					cout<<"compHist: "<<compHisto->GetEntries()<<endl;
					cout<<"oldHist: "<<oldHisto->GetEntries()<<endl;
					compHisto->Draw("same hist");
					//input->Close();

					c->Update();

					legend->AddEntry(compHisto, "MC", "l");

					c->Update();

				}

				c->SetLogy(1);

				legend->SetTextSize(0.03);
				legend->Draw("same");
				c->Update();
				output->WriteTObject(c, 0, "overwrite");

			}
		}

	}

	//  input1->Close();
	//      	 input2->Close();
	//delete c;
	//cout<<"done"<<endl;
}
#endif
