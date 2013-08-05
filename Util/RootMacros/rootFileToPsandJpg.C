#ifndef rootFileToPsandJpg_C_
#define rootFileToPsandJpg_C_
#ifndef __CINT__ 
#include <TKey.h>
#include <TImage.h>
#include <TError.h>
#include <TROOT.h>

#endif
#include "Util/OwnUtil/src/HistoDrawUtil.h"
using namespace std;

void rootFileToPsandJpg(TFile* input, string outname = "") {

	cout << "start macro rootFileToPsandJpg" << endl;
	//	HistoDrawUtil::setMyTDRStyle();
	//		gROOT->SetStyle("mytdrStyle");
	//		gROOT->LoadMacro("Util/RootMacros/rootFileToPsandJpg.C");
	//		gStyle->SetOptStat(0);
	//		gStyle->UseCurrentStyle();
	//		gStyle->SetOptStat(0);
	//
	//
	//		cout << "style opt stat:" << gStyle->GetOptStat()<< endl;
	//		cout << "style:" << gStyle->GetTitleXOffset() << endl;
	//
	//		gROOT->ForceStyle(1);
	//		gROOT->UseCurrentStyle();

	//	cout << "OPT TITLE------------------" << gStyle->GetOptTitle() << endl;

	//gROOT->UseCurrentStyle();

	string outputdir = input->GetName();
	cout << "create result.eps and eps-files from file: " << outputdir
			<< "....." << endl;
	int size = outputdir.size();
	string ende = outputdir.substr(size - 5, size);
	if (ende == ".root") {
		outputdir = outputdir.substr(0, size - 5);
	}
	if (outname != "") {
		outputdir = outname;
	}
	TIter nextkey(input->GetListOfKeys());
	//cout << "keylist size" << (input->GetListOfKeys())->GetSize() << endl;
	TKey *key;

	TCanvas *c = new TCanvas;

	system(("mkdir " + outputdir).c_str());
	//const char* outputfile=(outputdir+"/results.eps[").c_str();
	//c->Print(outputfile); // No actual print, just open ps file
	int counter = 0;
	while ((key = (TKey*) nextkey())) {
		counter++;
		if (counter > 2000) {
			break;
		}
		c->Clear();
		string name = key->ReadObj()->GetName();
		//cout << "NAME:" << name << endl;
		TObject* obj = (TObject*) key->ReadObj();
		//cout << "obj" << obj << endl;
		string classname = obj->ClassName();
		if (classname == "TCanvas") {
			//			HistoDrawUtil::setMyTDRStyle();
			//					gROOT->SetStyle("mytdrStyle");
			//			gStyle->SetOptLogy(1);
			//			gROOT->ForceStyle(1);
			TCanvas* canv = (TCanvas*) obj;
			//			HistoDrawUtil::cmsPrel(5.3,0);

			canv->Update();

			//	canv->Print((""+outputdir+"/"+name+".png").c_str());
			//canv->SaveAs(("" + outputdir + "/" + name + ".gif").c_str());
			canv->SaveAs(("" + outputdir + "/" + name + ".pdf").c_str());
			canv->Print(("" + outputdir + "/" + name + ".eps").c_str());
			//		canv->Print((""+outputdir+"/"+name+".pdf").c_str());
			//			TImage *img = TImage::Create();
			//			img->FromPad(canv);
			//			img->WriteImage((outputdir+"/"+name+".gif").c_str());
			//			delete img;
			//canv->Print((outputdir+"/results.eps").c_str(), "");

			delete obj;

		} else {
			cout << "No Canvas!" << endl;
			//      obj->Draw(obj->GetDrawOption());
			//      c->Update();
			//      TImage *img = TImage::Create();
			//      img->FromPad(c);
			//      img->WriteImage((outputdir+"/"+name+".jpg").c_str());
			//      c->Print((outputdir+"/results.eps").c_str(),"");
			//      delete obj;
			//      delete img;
		}

	}
	c->Clear();
	//c->Print((outputdir+"/results.eps]").c_str()); // No actual print, just close the file 
	delete c;
	c = 0;

	//cout<<"done"<<endl;
}
#endif
