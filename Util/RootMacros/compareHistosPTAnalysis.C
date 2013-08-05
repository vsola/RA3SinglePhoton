#ifndef compareHistosPTAnalysis_C_
#define compareHistosPTAnalysis_C_
#ifndef __CINT__
#include <TKey.h>
#include <TImage.h>
#include <TError.h>
#include <vector>
#include <TFile.h>
#include <TROOT.h>
#include <TH1F.h>
#include <TObject.h>
#include "Util/RootMacros/rootFileToPsandJpg.C"
#include <iostream>
#include <utility>
#include "Util/OwnUtil/src/HistoDrawUtil.h"
#include <TPad>
#endif

#include "Util/OwnUtil/src/HistoDrawUtil.h"
#include <TPad>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

void compareHistosPTAnalysis(TFile * input, bool isdata, double lumi) {

	HistoDrawUtil::setMyTDRStyle();
	gROOT->SetStyle("mytdrStyle");
	gROOT->LoadMacro("Util/RootMacros/rootFileToPsandJpg.C");
	gStyle->SetOptStat(0);
	gStyle->UseCurrentStyle();
	gStyle->SetPadTickY(0);
	gStyle->SetPadTickX(0);
	gStyle->SetHatchesLineWidth(2);
	gStyle->SetFrameFillStyle(1001);
	gStyle->SetFrameFillColor(10);
	gStyle->SetFrameFillColor(10);
	gStyle->SetTitleXOffset(1.2);
	gStyle->SetPadBottomMargin(0.2);

	//


	cout << "style opt stat:" << gStyle->GetOptStat() << endl;
	cout << "style:" << gStyle->GetTitleXOffset() << endl;

	gROOT->ForceStyle(1);

	cout << "start macro compareHistosPTAnalysis" << endl;

	string outputdir = input->GetName();

	cout << "create result.eps and eps-files from file: " << outputdir
			<< "....." << endl;
	int size = outputdir.size();
	string ende = outputdir.substr(size - 5, size);
	if (ende == ".root") {
		outputdir = outputdir.substr(0, size - 5);
	}
	outputdir = "" + outputdir + "";
	TFile * output = new TFile(("" + outputdir + "_plot.root").c_str(),
			"Recreate");

	TIter nextkey(input->GetListOfKeys());
	cout << "keylist size" << (input->GetListOfKeys())->GetSize() << endl;

	TKey *key;

	int counter = 0;
	system(("mkdir " + outputdir).c_str());
	while (key = (TKey*) nextkey()) {
		counter++;
		if (counter > 2000) {
			cout << "WARNING --- More than 2000 keys..." << endl;
			break;
		}

		string name = key->ReadObj()->GetName();
		string endfix = name.substr(name.size() - 4, name.size());
		//cout<<"endfix"<<endfix<<endl;
		gStyle->SetOptLogy(0);
		if (endfix != "Zoom") {

			//cout<<"Set Log Y!"<<endl;
			gStyle->SetOptLogy(1);
		}
		gROOT->ForceStyle(1);
		TObject* obj = (TObject*) key->ReadObj();
		if (obj != 0) {
			string name = key->ReadObj()->GetName();
			cout << "===============================NAME:" << name << endl;
			//cout << "obj" << obj << endl;

			string classname = obj->ClassName();
			//gStyle->SetOptLogy(0);
			if (classname == "TCanvas") {
				string canvasname = obj->GetName();

				TCanvas* canv = (TCanvas*) obj;
				canv->Update();

				HistoDrawUtil::cmsPrel(lumi, 0, isdata);

				TList* listofkeysToUse = (TList*) (canv->GetListOfPrimitives());
				TIter canvkey(listofkeysToUse);

				//cout << "canv keylist size " << listofkeysToUse->GetSize() << endl;
				string meanToDraw = "";
				string sigmaToDraw = "";
				while (keyCanv = (TKey*) canvkey()) {
					//cout << "CANV KEY!" << keyCanv->GetName() << " ref:" << keyCanv << endl;
					if (keyCanv->IsA()->InheritsFrom("TObject")) {
						TObject* currObj = (TObject*) keyCanv;//canvClone->FindObject(keyCanv->GetName());
						if (currObj != 0) {

							if (keyCanv->IsA()->InheritsFrom("TLegend")) {
								//cout << "TLEGEND!!!!!!!!!!!!!!--->"
								//		<< ((TLegend*) currObj)->GetTitle() << endl;
								//cout << "ref: " << currObj << endl;
								string namelegend =
										((TLegend*) currObj)->GetHeader();
								string anfLegend = namelegend.substr(0, 6);

								//								cout << "Name of legend:" << namelegend << endl;
								namelegend = HistoDrawUtil::replaceSubstr(
										namelegend, "ptDijet", "average dijet");

								((TLegend*) currObj)->SetHeader(
										namelegend.c_str());
								((TLegend*) currObj)->SetFillColor(10);
								((TLegend*) currObj)->SetFillStyle(1001);

							} else if (keyCanv->IsA()->InheritsFrom("TPave")) {
								//delete currObj;
								if (name != "tree_Info") {
									//								cout << "TPaveText!!!!!!!!!!!!!!--->"
									//										<< ((TPaveText*) currObj)->GetTitle() << endl;
									//								cout << "ref: " << currObj << endl;
									int
											noOfLines =
													((TList*) ((TPaveText*) currObj)->GetListOfLines())->GetSize();
									TList * newTextLines = new TList();
									newTextLines->Add(new TText());
									for (int n = 0; n < noOfLines; n++) {
										TText
												* line =
														((TPaveText*) currObj)->GetLine(
																n);
										//cout<<"add line1:"<<line<<endl;
										//										cout<<"add line1:"<<line->GetTitle()<<endl;
										newTextLines->Add(
												(TText *) line->Clone());
									}
									//cout << "noOfLines:" << noOfLines << endl;

									((TPaveText*) currObj)->SetFillColor(10);
									((TPaveText*) currObj)->SetFillStyle(1001);
									((TPaveText*) currObj)->SetX1NDC(0.668);
									((TPaveText*) currObj)->SetY1NDC(0.241);
									((TPaveText*) currObj)->SetX2NDC(0.989);
									((TPaveText*) currObj)->SetY2NDC(0.47);
									((TPaveText*) currObj)->SetTextSize(0.03);
									if (noOfLines <= 5) {
										((TPaveText*) currObj)->SetX1NDC(0.683);
										((TPaveText*) currObj)->SetY1NDC(0.241);
										((TPaveText*) currObj)->SetX2NDC(0.989);
										((TPaveText*) currObj)->SetY2NDC(0.400);
										((TPaveText*) currObj)->SetTextSize(
												0.03);
									}
									((TPaveText*) currObj)->Clear();
									cout<<"canvName:"<<canvasname<<endl;
									if (HistoDrawUtil::containsSubstr(canvasname,
											"mjgj")) {
										cout << "MJGJ!" << endl;
										bool drawOnlyMeanAndRMS=false;
										if(HistoDrawUtil::containsSubstr(canvasname,"WoPt_mjgj")){

										}
										if(drawOnlyMeanAndRMS){
										((TPaveText*) currObj)->SetLineColor(0);
										((TPaveText*) currObj)->SetFillColor(0);
										((TPaveText*) currObj)->SetX1NDC(0.668);
										((TPaveText*) currObj)->SetY1NDC(0.668);
										((TPaveText*) currObj)->SetX2NDC(0.668);
										((TPaveText*) currObj)->SetY2NDC(0.668);
										}else{
											int endLoop = (int) newTextLines->GetSize();
																				//cout << "noOfLines NEW:" << endLoop << endl;
																				for (int n = 0; n < endLoop; n++) {
																					string
																					linetext =
																					((TText*) newTextLines->At(
																									n))->GetTitle();
																					((TPaveText*) currObj)->AddText(
																							linetext.c_str());
																				}
										}

									} else {
									int endLoop = (int) newTextLines->GetSize();
									//cout << "noOfLines NEW:" << endLoop << endl;
									for (int n = 0; n < endLoop; n++) {
										string
										linetext =
										((TText*) newTextLines->At(
														n))->GetTitle();
										((TPaveText*) currObj)->AddText(
												linetext.c_str());
									}
									}

								}

							}
							if (keyCanv->IsA()->InheritsFrom("TF1")) {
								string canvName = currObj->GetName();
								cout << "gaus:" << canvName << endl;
								double mean = ((TF1*) currObj)->GetParameter(2);
								double sigma =
										((TF1*) currObj)->GetParameter(1);
								cout << "mean:" << mean << endl;
								cout << "sigma:" << sigma << endl;

								string meanStr = "Mean: "
										+ HistoDrawUtil::getStringFromDoubleN(
												mean, 5);
								string sigmaStr = "Sigma: "
										+ HistoDrawUtil::getStringFromDoubleN(
												sigma, 5);

								string meanToDraw = meanStr;
								string sigmaToDraw = sigmaStr;

							}

							if (keyCanv->IsA()->InheritsFrom("TH1F")) {
								string canvName = currObj->GetName();

								if (!isdata) {

									((TH1*) currObj)->SetMarkerSize(0);
									((TH1*) currObj)->SetLineColor(
											((TH1*) currObj)->GetLineColor());
									int noBins = ((TH1*) currObj)->GetNbinsX();
									for (int b = 0; b <= noBins; b++) {
										((TH1*) currObj)->SetBinError(b, 0);
									}
									((TH1*) currObj)->Paint();

								}
								int xmin =
										((TH1*) currObj)->GetXaxis()->GetXmin();
								int xmax =
										((TH1*) currObj)->GetXaxis()->GetXmax();
								if (xmin == -1) {
									((TH1*) currObj)->GetXaxis()->SetRangeUser(
											-0.8, 1.2);
								}
								if (xmin == -2) {
									((TH1*) currObj)->GetXaxis()->SetRangeUser(
											-0.8, 1.2);
								}

								string
										xaxistitle =
												((TH1*) currObj)->GetXaxis()->GetTitle();
								//cout << "xaxistitle " << xaxistitle << endl;

								if (xaxistitle
										== "#frac{P_{t,Calo}-P_{t,Dijet}}{P_{t,Dijet}} (ptDijet)") {
									xaxistitle = HistoDrawUtil::replaceSubstr(
											xaxistitle, "t,Dijet",
											"t,average DJ");
									xaxistitle = HistoDrawUtil::replaceSubstr(
											xaxistitle, "t,Dijet",
											"t,average DJ");
									xaxistitle = HistoDrawUtil::replaceSubstr(
											xaxistitle, "(ptDijet)", "");
								}
								if (xaxistitle
										== "#frac{P_{t,Calo}-P_{t,Dijet}}{P_{t,Dijet}} (genjet_pt)") {
									xaxistitle = HistoDrawUtil::replaceSubstr(
											xaxistitle, "t,Dijet", "t,Genjet");
									xaxistitle = HistoDrawUtil::replaceSubstr(
											xaxistitle, "t,Dijet", "t,Genjet");
									xaxistitle = HistoDrawUtil::replaceSubstr(
											xaxistitle, "(genjet_pt)", "");
								}

								((TH1*) currObj)->GetXaxis()->SetTitle(
										xaxistitle.c_str());
								if (endfix != "Zoom")
									((TH1*) currObj)->GetYaxis()->SetRangeUser(
											1,
											((TH1*) currObj)->GetMaximumStored());

							}
							if (keyCanv->IsA()->InheritsFrom("THStack")) {
								int
										xmin =
												((THStack*) currObj)->GetXaxis()->GetXmin();
								int
										xmax =
												((THStack*) currObj)->GetXaxis()->GetXmax();
								if (xmin == -1) {
									((THStack*) currObj)->GetXaxis()->SetRangeUser(
											-0.8, 1.2);
								}
								if (xmin == -2) {
									((THStack*) currObj)->GetXaxis()->SetRangeUser(
											-0.8, 1.2);
								}
								if (endfix != "Zoom")
									((THStack*) currObj)->GetYaxis()->SetRangeUser(
											1,
											((THStack*) currObj)->GetYaxis()->GetXmax());
							}
						}
					}
				}



				canv->Update();
				TPad * mypad = (TPad*) gPad;
				mypad->Update();
				canv->Update();
				//canv->Modified();
				//canv->cd();
				//canv->SetSelected(canv);

				//canv->DrawClone();
				if (endfix != "Zoom") {
					cout << "Set Log Y!" << endl;
					gStyle->SetOptLogy(1);
					gROOT->ForceStyle(1);
				}
				canv->Update();
				TPad * mypad = (TPad*) gPad;
				mypad->Update();
				canv->Update();
				TCanvas* canvClone = (TCanvas *) canv->Clone();
				HistoDrawUtil::cmsPrel(lumi, 0, isdata);
				///Draw Gaus Mean/Sigma to mjgj plots

//				TLatex latex;
//				latex.SetNDC();
//				latex.SetTextSize(0.04);
//				latex.SetTextAlign(11);
//
//				latex.DrawLatex(0.7, 0.45, meanToDraw.c_str());
//
//				latex.DrawLatex(0.7, 0.4, sigmaToDraw.c_str());

				//canvClone->Modified();
				canvClone->Paint();
				canvClone->Update();

				canvClone->Update();
				canvClone->Draw("sameaxis");
				canvClone->SaveAs(
						("" + outputdir + "/" + name + ".gif").c_str());
				canvClone->SaveAs(
						("" + outputdir + "/" + name + ".pdf").c_str());
				canvClone->Print(("" + outputdir + "/" + name + ".eps").c_str());
				output->WriteTObject(canvClone, 0, "overwrite");

				delete canvClone;

				delete obj;
			}
		} else {
			cout << "No Canvas!" << endl;

		}

	}
	output->Close();

	//cout<<"done"<<endl;


}
#endif
