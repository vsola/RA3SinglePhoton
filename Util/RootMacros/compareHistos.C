#ifndef rootFileToPsandJpg_C_
#define rootFileToPsandJpg_C_
#ifndef __CINT__ 
#include <TKey.h>
#include <TImage.h>
#include <TError.h>
#include <TFile.h>

#endif

using namespace std;
void compareHistos() {
	gStyle->SetTitleSize(0.06, "XY");
	gStyle->SetLabelSize(0.04, "XY");
	gStyle->SetTitleOffset(1.2, "XY");

	gStyle->SetPadBottomMargin(0.2);
	gStyle->SetPadLeftMargin(0.2);
	gStyle->SetPadRightMargin(0.15);
	gStyle->SetDrawOption("tics");

	vector<string> canvasnames;
	canvasnames.push_back("tree_E_Etrue");
	canvasnames.push_back("Comp_all_met_Evt_DataLevel");

	vector<string> histnames;
	histnames.push_back("compHisto");
	histnames.push_back("metCompHisto");

	vector<string> legs;
	legs.push_back("LM1");
	//	legs.push_back("LM4");
	//	legs.push_back("TT Jets");
	//legs.push_back("W Jets");
	//legs.push_back("Z Jets");
	//legs.push_back("Z invisible");
	legs.push_back("QCD Jets(Pythia)");

	std::vector<string> colors;
	colors.push_back("2");
	colors.push_back("1");
	colors.push_back("3");
	colors.push_back("4");
	colors.push_back("5");
	colors.push_back("6");
	colors.push_back("7");

	TFile *output = new TFile(("PtComparisonResults.root"),"recreate");

	vector<string> inputfiles;
	inputfiles.push_back("tree_SUSY_LM1.root");
	//inputfiles.push_back("tree_Pt_SUSY_LM4.root");
	//inputfiles.push_back("tree_Pt_TTJets.root");
	//inputfiles.push_back("tree_Pt_WJets.root");
	//inputfiles.push_back("tree_Pt_ZJets.root");
	//inputfiles.push_back("tree_Pt_ZinvisibleJets.root");
	inputfiles.push_back("tree_PythiaQCD.root");

	//---------compare 'compHisto' mj-gj/gj
	TFile *input1 = new TFile((inputfiles.at(0)).c_str(),"read");
	TIter nextkey(input1->GetListOfKeys());
	// cout<<"keylist size"<<(input->GetListOfKeys())->GetSize()<<endl;
	TKey *key;

	while (key = (TKey*)nextkey() ) {

		string name=key->ReadObj()->GetName();
		cout<<"NAME:"<<name<<endl;
		TObject* obj=(TObject*)key->ReadObj();
		for (int canv=0; canv!=canvasnames.size(); canv++) {
			string canvasName=canvasnames.at(canv);

			if (canvasName==obj->GetName()) {

				TCanvas * c=new TCanvas(canvasName.c_str(),canvasName.c_str());
				TLegend *legend = new TLegend(0.675879,0.786713,0.996231,0.996503,"");

				for (int i=0; i!=inputfiles.size(); ++i) {

					TFile *input = new TFile((inputfiles.at(i)).c_str(),"");

					TH1F * compHisto = (TH1F*)input->FindObjectAny((histnames.at(canv)).c_str());

					compHisto->SetLineColor(atof(colors.at(i).c_str()));
					legend->AddEntry(compHisto, (legs.at(i)).c_str(), "l");

					if (i==0) {

						compHisto->Draw("");

					} else {
						compHisto->Draw("same");

					}

				}

				c->SetLogy(1);

				legend->SetTextSize(0.03);
				legend->Draw("same");
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
