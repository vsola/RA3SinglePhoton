#ifndef compareHistosMetSigmaAnalysis_C_
#define compareHistosMetSigmaAnalysis_C_
#ifndef __CINT__
#include <TKey.h>
#include <TImage.h>
#include <TError.h>
#include <vector>
#include <TFile.h>
#include <TROOT.h>
#include <TProfile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TGraphAsymmErrors.h>
#include <TGraphErrors.h>
#include <TObject.h>

#include <iostream>
#include <utility>
#endif

#include "Util/OwnUtil/src/HistoDrawUtil.h"

using namespace std;
void cmsPrel(double intLumi = -1, double pos = 0, bool isdata = false, bool isMC = false,
	bool isCMSofficial = false) {
	bool debug = false;
	TLatex latex;
	latex.SetNDC();
	latex.SetTextSize(0.05);
	bool isnb=false;
	if(intLumi<0.01){
		intLumi=intLumi*1000;
		isnb=true;
	}
	double lumiRd = HistoDrawUtil::roundDouble(intLumi, 1);

	if (pos == 1) {
		latex.SetTextAlign(11);
		//latex.DrawLatex(0.63, 0.35, "#font[22]{CMS preliminary 2010}");
		latex.SetTextAlign(11);
		//		if (isdata && !isMC) {
		//			latex.DrawLatex(0.63, 0.25, "Data   #sqrt{s} = 7 TeV");
		//		} else if (!isdata && isMC) {
		//			latex.DrawLatex(0.63, 0.25, "MC   #sqrt{s} = 7 TeV");
		//		} else {
		//			latex.DrawLatex(0.63, 0.25, "#sqrt{s} = 7 TeV");
		//		}
		//lumi nur wenn Daten dabei sind
		if (isdata && intLumi != 0) {
			//			latex.DrawLatex(0.63, 0.2, Form(
			//					"#int #font[12]{L}dt = %.1fpb^{-1}", intLumi));
			if(isnb){
				latex.DrawLatex(0.4, 0.2, Form("2010, #sqrt{s} = 7 TeV, #font[12]{ }%.2fnb^{-1}",
			                  											intLumi));
			}
			else
			latex.DrawLatex(0.4, 0.2, Form("2010, #sqrt{s} = 7 TeV, #font[12]{ }%.2fpb^{-1}",
											intLumi));
		} else {
			latex.DrawLatex(0.4, 0.2, Form("Simulation 2010, #sqrt{s} = 7 TeV", intLumi));
		}

	} else if (pos == 0) {
		latex.SetTextAlign(11);
		//CHRISTIAN:preliminary an/aus
		//latex.DrawLatex(0.2, 0.9, "#font[22]{CMS preliminary 2010}");
		latex.SetTextAlign(11);
		//		if (isdata && !isMC) {
		//			latex.DrawLatex(0.17, 0.75, "Data   #sqrt{s} = 7 TeV");
		//		} else if (!isdata && isMC) {
		//			latex.DrawLatex(0.17, 0.75, "MC   #sqrt{s} = 7 TeV");
		//		} else {
		//			latex.DrawLatex(0.17, 0.75, Form("#sqrt{s} = 7 TeV",
		//					intLumi));
		//		}
		//lumi nur wenn Daten dabei sind
		if (isdata && intLumi != 0) {
			//			latex.DrawLatex(0.17, 0.75, Form(
			//					"#int #font[12]{L}dt = %.1fpb^{-1}", intLumi));
			//CHRISTIAN:format lumi

			if (!intLumi > 0) {
				latex.DrawLatex(0.18, 0.89, Form("2010, #sqrt{s} = 7 TeV"));
			}
			else if(isnb){
				latex.DrawLatex(0.18, 0.89, Form("2010, #sqrt{s} = 7 TeV, #font[12]{ }%.1fnb^{-1}",
																	intLumi));
						}

			else if (lumiRd == 0.0) {
				latex.DrawLatex(0.18, 0.89, Form("2010, #sqrt{s} = 7 TeV, #font[12]{ }%.2fpb^{-1}",
													intLumi));
			} else {
				latex.DrawLatex(0.18, 0.89, Form("2010, #sqrt{s} = 7 TeV, #font[12]{ }%.1fpb^{-1}",
													intLumi));
			}
		} else {
			if (!intLumi > 0) {
				latex.DrawLatex(0.18, 0.89, Form("Simulation, #sqrt{s} = 7 TeV"));
			} else if (lumiRd == 0.0) {
				latex.DrawLatex(0.18, 0.89,
								Form("Simulation, #sqrt{s} = 7 TeV, #font[12]{ }%.2fpb^{-1}",
										intLumi));
			} else {
				latex.DrawLatex(0.18, 0.89, Form("Simulation, #sqrt{s} = 7 TeV", intLumi));
			}
		}
	}

}
void invertHistoXAxis(TH1F * histo) {
	if (histo != 0) {
		histo->Draw();
		for (int b = 0; b <= ((TH1*) histo)->GetNbinsX(); b++) {
			if (histo->GetBinLowEdge(b) > -70 && histo->GetBinLowEdge(b) <= 0) {
				cout << "bin no:" << b << " 	lowEdge:" << histo->GetBinLowEdge(b) << endl;
				int binToFill = histo->FindBin(fabs(histo->GetBinLowEdge(b)));
				cout << "new bin :" << binToFill << " 	lowEdge:" << histo->GetBinLowEdge(binToFill)
					<< endl;
				histo->SetBinContent(binToFill, histo->GetBinContent(b));
				histo->SetBinError(binToFill, histo->GetBinError(b));
				//					histo->GetYaxis()->SetRangeUser(0,60);
				//					histo->GetXaxis()->SetRangeUser(0,70);
				//					histo->SetMarkerStyle(20);
				//					histo->SetMarkerSize(0.6);
			}
		}
		histo->Draw();
	} else {
		cout << "histo not found" << endl;
	}

}
void drawFitInHisto(TF1 * histoFit) {
	bool debug = false;
	histoFit->Draw("same");
	if (debug)
		cout << "Final Fit drawn!" << endl;
	TLatex l;
	l.SetTextAlign(12);
	l.SetTextSize(0.04);
	l.SetTextFont(62);
	l.SetTextColor(histoFit->GetLineColor());
	l.SetNDC();
	//l.DrawLatex(0.13, 0.83, "CMS 2010 Preliminary");

	l.DrawLatex(0.55, 0.35, "f(x)=#sqrt{A^{2}+B^{2}x+C^{2}x^{2}}");
	string sA = "A=";
	sA = sA + Form("%.1f", histoFit->GetParameter(0)) + "#pm" + Form("%.1f",
																		histoFit->GetParError(0))
		+ " GeV";
	string sB = "B=";
	sB = sB + Form("%.2f", histoFit->GetParameter(1)) + "#pm" + Form("%.2f",
																		histoFit->GetParError(1))
		+ " GeV";
	string sC = "C=";
	sC = sC + Form("%.3f", histoFit->GetParameter(2)) + "#pm" + Form("%.3f",
																		histoFit->GetParError(2))
		+ " GeV";
	//		string sD = "D=";
	//		sD=sD+Form("%.3f", histoFit->GetParameter(3))+"#pm"+Form("%.3f",
	//				histoFit->GetParError(3))+ " GeV";
	l.DrawLatex(0.55, 0.3, sA.c_str());
	l.DrawLatex(0.55, 0.25, sB.c_str());
	l.DrawLatex(0.55, 0.2, sC.c_str());
	//l.DrawLatex(0.55, 0.15, sD.c_str());
}
void drawHistosToCanvas(TList * histos, TList * histosMC, bool isOnlyMC, TList * histosFit = 0,
	bool noFillColor = true, bool drawLine = false, bool mcnohisto = false, double maxXLine = 0,
	double minXLine = 0, TList * histosSYST = 0, TList * histosMCSYST = 0,double maxYAxis=0) {
	bool debug = false;
	if (debug)
		cout << "draw Histos!" << endl;
	TIter next(histos);
	TIter nextMC(histosMC);

	TIter nextFit(histosFit);
	int i = 0;
	int entries = histosMC->GetEntries();
	//if(debug)cout<<"ENTRIES:"<<entries<<endl;
	noFillColor = true;
	//	if (entries==1)
	//		noFillColor=false;

	gROOT->ForceStyle(1);
	gStyle->SetErrorX(0);
	gStyle->SetEndErrorSize(0);
	//if(debug)cout<<"Error X:"<<gStyle->GetErrorX()<<endl;
	gStyle->UseCurrentStyle();
	gROOT->ForceStyle(1);
	//if(debug)cout<<"draw MC"<<endl;
	double maxX = 0;
	TH1F * histoMC = 0;



	while ((histoMC = (TH1F *) nextMC())) {
		if(maxYAxis!=0){
			histoMC->GetYaxis()->SetRangeUser(0.5,maxYAxis);
		}
		histoMC->SetMarkerStyle(1);
		if (noFillColor) {
			histoMC->SetFillColor(0);
			histoMC->SetLineWidth(2);
		} else {
			histoMC->SetFillColor(0);
			histoMC->SetFillColor(histoMC->GetLineColor());
			histoMC->SetFillStyle(1);
			histoMC->SetLineStyle(1);

		}
		if (mcnohisto) {
			if(maxYAxis!=0){
						histoMC->GetYaxis()->SetRangeUser(0.5,maxYAxis);
					}
			if (entries != 1) {
				histoMC->SetMarkerColor(histoMC->GetLineColor());
				histoMC->SetMarkerStyle(kFullDotSmall);
			} else {

				histoMC->SetLineStyle(1);
				histoMC->SetLineColor(1);
				histoMC->SetMarkerColor(1);
				histoMC->SetMarkerStyle(kFullDotSmall);
			}
		}
		if (i == 0) {
			if (debug)
				cout << "i=0" << endl;
			if (mcnohisto) {
				histoMC->Draw("E ");
			} else if (!isOnlyMC)
				histoMC->Draw("hist");//hist
			else
				histoMC->Draw("hist");//hist

		} else {
			if (debug)
				cout << "=============weiteres MC" << histoMC->GetMinimum() << endl;
			if (mcnohisto) {
				histoMC->Draw("same E ");
			} else if (!isOnlyMC)
				histoMC->Draw("same hist");//hist
			else
				histoMC->Draw("same hist");//hist

			maxX = histoMC->GetXaxis()->GetXmax();

		}
		if (debug)
			cout << "=============weiteres MC" << histoMC->GetMinimum() << endl;
		++i;
	}

	if (!isOnlyMC) {
		cout << "not only MC: i:" << i << endl;

		TH1F * histo = 0;
		while ((histo = (TH1F *) next())) {
			histo->SetLineColor(histo->GetMarkerColor());
			if(maxYAxis!=0){
				histo->GetYaxis()->SetRangeUser(0.5,maxYAxis);
					}
			if (!noFillColor) {
				histo->SetMarkerColor(1);

			}
			if (i == 0) {
				histo->Draw("E X0");
			} else {
				histo->Draw("same E X0");
			}
			if (debug || true) {
				cout << "==============DATEN Color:" << histo->GetMarkerColor() << endl;
				cout << "==============DATEN size:" << histo->GetMarkerSize() << endl;
				cout << "==============DATEN entries:" << histo->GetEntries() << endl;
			}
			++i;
		}
	}
	if (histosFit != 0 && false) {
		TF1 * histoFit = 0;
		while ((histoFit = (TF1 *) nextFit())) {
			drawFitInHisto(histoFit);
		}
	}
	//DRAW Systematic ErrorBands
	//cout<<"draw systematics!!!!!!!!!!!!!!!1"<<endl;
	if (histosSYST != 0) {
		cout << "Data-draw systematics!!!!!!!!!!!!!!!1" << endl;

		TIter nextSYST(histosSYST);

		TH1F * histoSYST = 0;
		TGraphAsymmErrors* ge = 0;
		if (histosSYST->GetSize() != 0) {
			while ((histoSYST = (TH1F *) nextSYST())) {
				if (histoSYST != 0) {
					cout << "==============data-draw systematics!!!!!!!!!!!!!!!1" << endl;

					ge = new TGraphAsymmErrors(histoSYST);
					for (int b = 0; b <= histoSYST->GetNbinsX(); ++b) {
						double binError = histoSYST->GetBinError(b);
						double binValue = histoSYST->GetBinContent(b);

						ge->SetPointEXhigh(b, 4);
						ge->SetPointEXlow(b, 4);
						if (binValue + binError > 6) {
							ge->SetPointEYhigh(b - 1, binError - (binValue + binError - 6));
						}
					}
					ge->SetFillColor(histoSYST->GetLineColor());
					ge->SetFillStyle(3005);
					ge->Draw("e2");
				}

			}
		}
	}
	if (histosMCSYST != 0) {
		cout << "MC-draw systematics!!!!!!!!!!!!!!!" << histosMCSYST->GetSize() << endl;

		TIter nextMCSYST(histosMCSYST);
		TH1F * histoMCSYST = 0;
		TGraphAsymmErrors* geMC = 0;
		if (histosMCSYST->GetSize() != 0) {
			while (histoMCSYST = (TH1F *) nextMCSYST()) {
				if (histoMCSYST != 0) {
					cout << "MC2-draw systematics!!!!!!!!!!!!!!!" << endl;
					geMC = new TGraphAsymmErrors(histoMCSYST);
					for (int b = 0; b <= histoMCSYST->GetNbinsX(); ++b) {
						double binError = histoMCSYST->GetBinError(b);
						double binValue = histoMCSYST->GetBinContent(b);

						geMC->SetPointEXhigh(b, 4);
						geMC->SetPointEXlow(b, 4);
						if (binValue + binError > 6) {
							geMC->SetPointEYhigh(b - 1, binError - (binValue + binError - 6));
						}

					}
					geMC->SetFillColor(histoMCSYST->GetLineColor());
					geMC->SetFillStyle(3004);
					geMC->Draw("e2");
				}

			}
		}
	}
	if (drawLine) {
		if (debug) {
			cout << "maxXLine" << maxXLine << endl;
			cout << "minXLine" << minXLine << endl;
		}
		if (minXLine > 0)
			minXLine = minXLine - 2;
		TLine * l = new TLine(minXLine, 0, maxXLine + 2, 0);
		l->SetLineColor(1);
		l->Draw("same");
	}
	//cmsPrel();

}

TF1* drawResolutionFit(TH1F * h, double startFitX) {
	bool debug = false;
	if (debug)
		cout << "DRAW RESOLUTION FIT!" << endl;
	Int_t nBins = h->GetXaxis()->GetNbins();

	TH1F *h_sigma2 = new TH1F("h_sigma2", "h_sigma2", nBins, h->GetXaxis()->GetXmin(),
								h->GetXaxis()->GetXmax());
	h_sigma2->SetDirectory(0);
	for (Int_t i = 0; i < (int) nBins; i++) {
		h_sigma2->SetBinContent(i + 1, h->GetBinContent(i + 1) * h->GetBinContent(i + 1));
		h_sigma2->SetBinError(i + 1, 2 * h->GetBinContent(i + 1) * h->GetBinError(i + 1));
	}

	//h_sigma2->SetLineColor(h->GetLineColor());
	h_sigma2->SetMarkerStyle(26);
	//h_sigma2->SetMarkerColor(h->GetMarkerColor());

	//	TF1
	//			*fit =
	//					new TF1("fitRes","pow([0],2)+pow([1],2)*(x-[3])+pow([2]*(x-[3]),2)",h->GetXaxis()->GetXmin(),h->GetXaxis()->GetXmax());

	TF1 *fit = new TF1("fitRes", "pow([0],2)+pow([1],2)*x+pow(([2]*x),2)", startFitX, 30);
	//	fit->SetParameter(0, 0.5);
	//	fit->SetParLimits(0, 0.1, 2);
	//	fit->SetParameter(1, 0.5);
	//	fit->SetParLimits(1, 0, 1.5);
	//	fit->SetParameter(2, 0.02);
	//	fit->SetParLimits(2, 0, 0.2);
	//		fit->SetParameter(3, 3);
	//		fit->SetParLimits(3, 2, 5);
	//	    fit->FixParameter(3, 0);

	h_sigma2->Fit("fitRes", "R");
	TF1 *fittedFunc = h_sigma2->GetFunction("fitRes");
	TF1 * fitClone = (TF1*) fit->Clone();
	if (fittedFunc != 0) {
		fitClone->SetParError(0, fittedFunc->GetParError(0));
		fitClone->SetParError(1, fittedFunc->GetParError(1));
		fitClone->SetParError(2, fittedFunc->GetParError(2));
		if (debug)
			cout << "ParError0:" << fittedFunc->GetParError(0) << endl;
		if (debug)
			cout << "ParError1:" << fittedFunc->GetParError(1) << endl;
		if (debug)
			cout << "ParError2:" << fittedFunc->GetParError(2) << endl;
	}
	delete h_sigma2;
	if (debug)
		cout << "END -DRAW RESOLUTION FIT!" << endl;
	return fitClone;

}

TH1F* removeBadPoints(TH1F* histo) {
	bool debug = false;
	int noBinsX = histo->GetNbinsX();
	for (int b = 0; b <= noBinsX; ++b) {
		//if(debug)cout<<"BinError:"<<histo->GetBinError(b)<<endl;
		//if(debug)cout<<"BinValue:"<<histo->GetBinContent(b)<<endl;
		//cout<<"BinValue:"<<histo->GetBinContent(b)<<endl;
		double binError = histo->GetBinError(b);
		double binValue = histo->GetBinContent(b);
		if ((binError > 0.3 * binValue)) {//||(binError>5)
			//	if(debug)cout<<"remove bin!"<<endl;
			histo->SetBinError(b, 0);
			histo->SetBinContent(b, -10);
		}
	}
	return histo;
}
TH1F* removeBadPointsErrorBar(TH1F* histo) {
	//	bool debug = false;
	//	int noBinsX = histo->GetNbinsX();
	//	int noFirstFilledBin = 0;
	//	double firstBinValue = 0.;
	//	double firstBinError = 0;
	//	for (int b = 0; b <= noBinsX; ++b) {
	//		//if(debug)cout<<"BinError:"<<histo->GetBinError(b)<<endl;
	//		//if(debug)cout<<"BinValue:"<<histo->GetBinContent(b)<<endl;
	//		double binError = histo->GetBinError(b);
	//		double binValue = histo->GetBinContent(b);
	//		//cout<<"bin center:"<<histo->GetBinCenter(b)<<endl;
	//		if (binValue != 0.) {
	//			firstBinValue = binValue;
	//			firstBinError = binError;
	//			noFirstFilledBin = b;
	//			break;
	//		}
	//	}
	//	histo->SetBinError(noFirstFilledBin - 1, 0);
	//	histo->SetBinContent(noFirstFilledBin - 1, firstBinValue);
	//	//		for (int b = 0; b <= noBinsX; ++b) {
	//	//					double binError = histo->GetBinError(b);
	//	//					double binValue = histo->GetBinContent(b);
	//	//					if (binValue==0.) {
	//	//						histo->SetBinError(b, 0);
	//	//						histo->SetBinContent(b, -333);
	//	//					}
	//	//				}
	return histo;
}
TGraphErrors* removeBadPointsGraph(TGraphErrors* gr,bool isPF=false){
	cout<<"!!!!!!!!!!!!!!!!!!!REMOVE GRAPH POINTS:"<<endl;
	bool containsPointForRemoval=true;
	while(containsPointForRemoval){
		cout<<"**START loop over Graph:"<<gr->GetN()<<endl;
		int maxN=gr->GetN();
		bool removePoint = false;
		for (int i = 0; i < maxN; ++i) {

			double gx, gy;
			gr->GetPoint(i, gx, gy);
			cout << "gx:" << gx << " +x:" << gr->GetErrorX(i) << endl;
			cout << "gy:" << gy << " +y:" << gr->GetErrorY(i) << endl;

			if (gr->GetErrorX(i) > 1 * gx) {
				cout << "***REMOVE POINT1" << i << endl;
				removePoint = true;
			}
			if (gr->GetErrorY(i) > 1 * gy) {
				cout << "***REMOVE POINT2" << endl;
				removePoint = true;
			}
							if(isPF&& (gx<3||gx>25)){
								cout<<"***REMOVE POINT3"<<endl;
								removePoint=true;
							}
			//				if(!isPF&& (gx<3||gx>28)){
			//					cout<<"***REMOVE POINT4"<<endl;
			//					removePoint=true;
			//				}
			if (removePoint) {
				gr->RemovePoint(i);

				cout << "***REMOVE POINT" << endl;
				break;
			}

		};
		if (!removePoint) {
			containsPointForRemoval = false;
		}

	};


	return gr;
}
TH1F* removeBadPointsMean(TH1F* histo) {
	bool debug = false;
	int noBinsX = histo->GetNbinsX();
	for (int b = 0; b <= noBinsX; ++b) {
		//if(debug)cout<<"BinError:"<<histo->GetBinError(b)<<endl;
		//if(debug)cout<<"BinValue:"<<histo->GetBinContent(b)<<endl;
		double binError = histo->GetBinError(b);
		double binValue = histo->GetBinContent(b);
		//cout<<"bin center:"<<histo->GetBinCenter(b)<<endl;
		if ((binError > fabs((double) (5 * binValue))) || binError > 5) {//(binError>fabs(5) ||
			//	if(debug)cout<<"remove bin!"<<endl;
			//			histo->SetBinError(b, 0);
			//			histo->SetBinContent(b, -333);
		}
	}
	return histo;
}
void compareHistosMetSigmaAnalysis(TFile * file, TFile * fileMC, string sampleName = "", bool qcd =
	false, bool doUCenergyPlots = true, bool plotTypeRaw = true, bool plotTypeI = true,
	bool plotTypeII = true, bool plotTypeIILocal = true, bool plotTypePF = false, bool plotTypePFI =
		false, bool plotTypePFII = false, bool plotTypePFIIL = false, bool plotTypeTC = false,
	string jetCutPt = "10", double lumi = -1, bool exclJetBins = false) {
	//	HistoDrawUtil::useMyStyle();
	//	gROOT->SetStyle("myStyle");
	bool debug = true;
	cout << "======================================================" << endl;
	cout << "======================================================" << endl;
	TList * trash = new TList();
	bool drawOnlySigmaAll = true;

	HistoDrawUtil::setMyTDRStyle();
	gROOT->SetStyle("mytdrStyle");
	gROOT->LoadMacro("Util/RootMacros/rootFileToPsandJpg.C");
	gStyle->SetOptStat(0);
	gStyle->UseCurrentStyle();
	gStyle->SetOptStat(0);
	//gStyle->SetOptStat(110000);
	//	gStyle->SetOptTitle(0);
  gStyle->SetPadTopMargin(0.05);
	if (debug)
		cout << "style opt stat:" << gStyle->GetOptStat() << endl;
	if (debug)
		cout << "style:" << gStyle->GetTitleXOffset() << endl;

	gROOT->ForceStyle(1);
	gROOT->UseCurrentStyle();
	//return;
	bool isZee = false;
	if (sampleName == "Zee") {

		isZee = true;
	}
	bool isPhotonJet = false;
	if (sampleName == "PhotonJet") {

		isPhotonJet = true;
	}

	bool isOnlyMC = false;
	if (fileMC->GetName() == file->GetName()) {
		isOnlyMC = true;
	}

	string filename = file->GetName();

	int size = filename.size();
	string ende = filename.substr(size - 5, size);
	if (ende == ".root") {
		filename = filename.substr(0, size - 5);
	}
	string basefilename = filename;
	string outfilename = filename;
	filename = filename + "_profiles.root";
	string filenameMC = "";
	if (fileMC != 0) {
		filenameMC = fileMC->GetName();
		int sizeMC = filenameMC.size();
		string ende = filenameMC.substr(sizeMC - 5, sizeMC);
		if (ende == ".root") {
			filenameMC = filenameMC.substr(0, sizeMC - 5);
		}
		filenameMC = filenameMC + "_profiles.root";
	}
	cout << "read File:" << filename << endl;
	cout << "read File MC:" << filenameMC << endl;
	TFile *fileProfiles = new TFile(filename.c_str(), "read");
	TFile *fileProfilesMC = new TFile(filenameMC.c_str(), "read");
	trash->Add(fileProfiles);
	trash->Add(fileProfilesMC);

	string filenameSlices = basefilename + "_slices.root";
	cout << "Test1" << endl;
	string filenameSlicesMC = "";
	if (fileMC != 0) {
		filenameSlicesMC = fileMC->GetName();
		cout << "Test1a" << endl;
		int sizeMC = filenameSlicesMC.size();
		cout << "Test1b" << endl;
		string ende = filenameSlicesMC.substr(sizeMC - 5, sizeMC);
		cout << "Test1c" << endl;
		if (ende == ".root") {
			filenameSlicesMC = filenameSlicesMC.substr(0, sizeMC - 5);
		}
		cout << "Test1d" << endl;
		filenameSlicesMC = filenameSlicesMC + "_slices.root";
		cout << "open File Slices" << filenameSlicesMC << endl;
	}
	cout << "Test2" << endl;
	TFile *fileSlices = new TFile(filenameSlices.c_str(), "update");
	TFile *fileSlicesMC = new TFile(filenameSlicesMC.c_str(), "update");
	//		trash->Add(fileSlices);
	//		trash->Add(fileSlicesMC);
	gROOT->ForceStyle(1);
	if (fileMC != 0) {
		cout << "do MC Comparison!" << endl;

	}
	if (doUCenergyPlots) {
		cout << "doUCEnergyPlots" << endl;
	}
	///Jet Selection
	vector < string > jetSelectionNames;
	if (isZee || isPhotonJet) {
		jetSelectionNames.push_back("All_");
	} else {
		jetSelectionNames.push_back("All_");
		//jetSelectionNames.push_back("1JetTypeI_");
		jetSelectionNames.push_back("2JetTypeI_");
	}
	cout << "Test3" << endl;
	vector < string > jetSelectionTitles;
	if (isZee || isPhotonJet) {
		jetSelectionTitles.push_back("0 Jets (pt>" + jetCutPt + ", loose JetId)  ");
	} else {
		jetSelectionTitles.push_back(">=0 Jets (pt>" + jetCutPt + ", loose JetId)  ");
	}
	string jetSelTitle1 = ">=1 Jets (pt>" + jetCutPt + ", loose JetId)  ";
	string jetSelTitle2 = ">=2 Jets (pt>" + jetCutPt + ", loose JetId)  ";
	jetSelectionTitles.push_back(jetSelTitle1);
	jetSelectionTitles.push_back(jetSelTitle2);

	vector < string > sumEtTypes;
	sumEtTypes.push_back("");
	sumEtTypes.push_back("raw");
	if (fileMC != 0)
		sumEtTypes.push_back("gen");

	vector < pair<double, double> > histoTypes1DRangeX;
	vector < string > histoTypes1D;
	histoTypes1D.push_back("sumEt_");
	if (isZee || isPhotonJet) {

		histoTypes1DRangeX.push_back(make_pair(0., 600.));
	} else if (qcd) {
		histoTypes1DRangeX.push_back(make_pair(0., 900.));
	} else {
		histoTypes1DRangeX.push_back(make_pair(0., 1300.));
	}
	histoTypes1D.push_back("met_");
	if (isZee || isPhotonJet) {
		histoTypes1DRangeX.push_back(make_pair(0., 150.));
	} else if (qcd) {
		histoTypes1DRangeX.push_back(make_pair(0., 150.));
	} else {
		histoTypes1DRangeX.push_back(make_pair(0., 150.));
	}
	histoTypes1D.push_back("metX_");
	if (isZee || isPhotonJet) {
		histoTypes1DRangeX.push_back(make_pair(-100., 150.));
	} else if (qcd) {
		histoTypes1DRangeX.push_back(make_pair(-300., 300.));
	} else {
		histoTypes1DRangeX.push_back(make_pair(-250., 250.));
	}
	histoTypes1D.push_back("metY_");
	if (isZee || isPhotonJet) {
		histoTypes1DRangeX.push_back(make_pair(-100., 150.));
	} else if (qcd) {
		histoTypes1DRangeX.push_back(make_pair(-300., 300.));
	} else {
		histoTypes1DRangeX.push_back(make_pair(-150., 150.));
	}
	histoTypes1D.push_back("metPara_");
	if (isZee || isPhotonJet) {
		histoTypes1DRangeX.push_back(make_pair(-100., 150.));
	} else if (qcd) {
		histoTypes1DRangeX.push_back(make_pair(-300., 300.));
	} else {
		histoTypes1DRangeX.push_back(make_pair(-100., 150.));
	}
	histoTypes1D.push_back("metPerp_");
	if (isZee || isPhotonJet) {
		histoTypes1DRangeX.push_back(make_pair(-100., 150.));
	} else if (qcd) {
		histoTypes1DRangeX.push_back(make_pair(-300., 300.));
	} else {
		histoTypes1DRangeX.push_back(make_pair(-100., 150.));
	}
	histoTypes1D.push_back("metSig_");
	if (isZee || isPhotonJet) {
		histoTypes1DRangeX.push_back(make_pair(0., 10.));
	} else if (qcd) {
		histoTypes1DRangeX.push_back(make_pair(0., 10.));
	} else {
		histoTypes1DRangeX.push_back(make_pair(0., 10.));
	}
	histoTypes1D.push_back("metDivSumEt_");
	if (isZee || isPhotonJet) {
		histoTypes1DRangeX.push_back(make_pair(0., 1.1));
	} else if (qcd) {
		histoTypes1DRangeX.push_back(make_pair(0., 1.1));
	} else {
		histoTypes1DRangeX.push_back(make_pair(0., 1.1));
	}
	histoTypes1D.push_back("recoilmet_");
	if (isZee || isPhotonJet) {
		histoTypes1DRangeX.push_back(make_pair(0., 200.));
	} else if (qcd) {
		histoTypes1DRangeX.push_back(make_pair(0., 100.));
	} else {
		histoTypes1DRangeX.push_back(make_pair(0., 50.));
	}
	histoTypes1D.push_back("recoilmetPara_");
	if (isZee || isPhotonJet) {
		histoTypes1DRangeX.push_back(make_pair(-200., 200.));
	} else if (qcd) {
		histoTypes1DRangeX.push_back(make_pair(-100., 150.));
	} else {
		histoTypes1DRangeX.push_back(make_pair(-50., 50.));
	}
	histoTypes1D.push_back("recoilmetPerp_");
	if (isZee || isPhotonJet) {
		histoTypes1DRangeX.push_back(make_pair(-200., 200.));
	} else if (qcd) {
		histoTypes1DRangeX.push_back(make_pair(-100., 150.));
	} else {
		histoTypes1DRangeX.push_back(make_pair(-100., 150.));
	}
	histoTypes1D.push_back("angleRecoilBisectSum_");
	if (isZee) {
		histoTypes1DRangeX.push_back(make_pair(0., 3.15));
	} else if (qcd) {
		histoTypes1DRangeX.push_back(make_pair(0., 3.15));
	} else {
		histoTypes1DRangeX.push_back(make_pair(0., 3.15));
	}

	vector < string > histoTypes1DMht;
	vector < pair<double, double> > histoTypes1DMhtRangeX;
	histoTypes1DMht.push_back("sumHt_");
	if (isZee) {
		histoTypes1DMhtRangeX.push_back(make_pair(0., 600.));
	} else if (qcd) {
		histoTypes1DMhtRangeX.push_back(make_pair(0., 900.));
	} else {
		histoTypes1DMhtRangeX.push_back(make_pair(0., 400.));
	}
	histoTypes1DMht.push_back("mht_");
	if (isZee) {
		histoTypes1DMhtRangeX.push_back(make_pair(0., 100.));
	} else if (qcd) {
		histoTypes1DMhtRangeX.push_back(make_pair(0., 300.));
	} else {
		histoTypes1DMhtRangeX.push_back(make_pair(0., 100.));
	}
	histoTypes1DMht.push_back("mhtX_");
	if (isZee) {
		histoTypes1DMhtRangeX.push_back(make_pair(-100., 150.));
	} else if (qcd) {
		histoTypes1DMhtRangeX.push_back(make_pair(-300., 300.));
	} else {
		histoTypes1DMhtRangeX.push_back(make_pair(-100., 150.));
	}
	histoTypes1DMht.push_back("mhtY_");
	if (isZee) {
		histoTypes1DMhtRangeX.push_back(make_pair(-100., 150.));
	} else if (qcd) {
		histoTypes1DMhtRangeX.push_back(make_pair(-300., 300.));
	} else {
		histoTypes1DMhtRangeX.push_back(make_pair(-100., 150.));
	}
	histoTypes1DMht.push_back("mhtSig_");
	if (isZee) {
		histoTypes1DMhtRangeX.push_back(make_pair(0., 10.));
	} else if (qcd) {
		histoTypes1DMhtRangeX.push_back(make_pair(0., 10.));
	} else {
		histoTypes1DMhtRangeX.push_back(make_pair(0., 10.));
	}
	histoTypes1DMht.push_back("mhtDivSumHt_");
	if (isZee) {
		histoTypes1DMhtRangeX.push_back(make_pair(0., 1.1));
	} else if (qcd) {
		histoTypes1DMhtRangeX.push_back(make_pair(0., 1.1));
	} else {
		histoTypes1DMhtRangeX.push_back(make_pair(0., 1.1));
	}

	vector < string > histoTypes1DTitle;
	histoTypes1DTitle.push_back("#Sigma E_{T} [GeV]");
	histoTypes1DTitle.push_back("#slash{E}_{T} [GeV]");
	histoTypes1DTitle.push_back("#slash{E}_{T,x} [GeV]");
	histoTypes1DTitle.push_back("#slash{E}_{T,y} [GeV]");
	histoTypes1DTitle.push_back("#slash{E}_{T,#parallel(q_{T})} [GeV]");
	histoTypes1DTitle.push_back("#slash{E}_{T,#perp(q_{    T})} [GeV]");
	histoTypes1DTitle.push_back("#frac{#slash{E}_{T}}{#sqrt{#Sigma #slash{E}_{T}}}");
	histoTypes1DTitle.push_back("#frac{#slash{E}_{T}}{#Sigma #slash{E}_{T}}");
	if (isZee) {
		histoTypes1DTitle.push_back("recoil(#vec{met}+#vec{e1}+#vec{e2}) [GeV]");
		histoTypes1DTitle.push_back("u_{#parallel(q_{T})}(#vec{met}+#vec{e1}+#vec{e2}) [GeV]");
		histoTypes1DTitle.push_back("u_{#perp(q_{    T})}(#vec{met}+#vec{e1}+#vec{e2}) [GeV]");
		histoTypes1DTitle.push_back("#angle recoil - #vec{e1}+#vec{e2}");
	} else if (isPhotonJet) {
		histoTypes1DTitle.push_back("recoil(#vec{met}+#vec{#gamma}) [GeV]");
		histoTypes1DTitle.push_back("u_{#parallel(q_{T})}(#vec{met}+#vec{#gamma}) [GeV]");
		histoTypes1DTitle.push_back("u_{#perp(q_{    T})}(#vec{met}+#vec{#gamma}) [GeV]");
		histoTypes1DTitle.push_back("#angle recoil - #vec{#gamma}");
	} else {
		histoTypes1DTitle.push_back("recoil(#vec{met}+#vec{j1}+#vec{j2}) [GeV]");
		histoTypes1DTitle.push_back("u_{#parallel(q_{T})}(#vec{met}+#vec{j1}+#vec{j2}) [GeV]");
		histoTypes1DTitle.push_back("u_{#perp(q_{    T})}(#vec{met}+#vec{j1}+#vec{j2}) [GeV]");
		histoTypes1DTitle.push_back("#angle recoil - #vec{j1}+#vec{j2}");
	}
	vector < string > histoTypes1DMhtTitle;
	histoTypes1DMhtTitle.push_back("#Sigma H_{T} [GeV]");
	histoTypes1DMhtTitle.push_back("#slash{H}_{T} [GeV]");
	histoTypes1DMhtTitle.push_back("#slash{H}_{T,x} [GeV]");
	histoTypes1DMhtTitle.push_back("#slash{H}_{T,y} [GeV]");
	histoTypes1DMhtTitle.push_back("#frac{#slash{H}_{T}}{#sqrt{#Sigma #slash{H}_{T}}}");
	histoTypes1DMhtTitle.push_back("#frac{#slash{H}_{T}}{#Sigma #slash{H}_{T}}");

	vector < string > histoTypes;
	vector < string > histoTypesSumEt;
	vector < pair<double, double> > histoTypesRangeX;
	vector < pair<double, double> > histoTypesRangeY;
	vector < pair<double, double> > histoTypesRangeYMean;
	histoTypes.push_back("sumEtSigmaMetDivSumet_");
	histoTypesSumEt.push_back("T");
	if (isZee) {
		histoTypesRangeX.push_back(make_pair(0., 300.));
		histoTypesRangeY.push_back(make_pair(0., 1.));
		histoTypesRangeYMean.push_back(make_pair(-5., 10.));
	} else if (qcd) {
		histoTypesRangeX.push_back(make_pair(0., 900.));
		histoTypesRangeY.push_back(make_pair(0., 1.));
		histoTypesRangeYMean.push_back(make_pair(-30., 30.));
	} else {
		histoTypesRangeX.push_back(make_pair(0., 400.));
		histoTypesRangeY.push_back(make_pair(0., 1.));
		histoTypesRangeYMean.push_back(make_pair(-30., 30.));
	}
	histoTypes.push_back("sumEtSigmaMetSqrtSumet_");
	histoTypesSumEt.push_back("T");
	if (isZee) {
		histoTypesRangeX.push_back(make_pair(0., 300.));
		histoTypesRangeY.push_back(make_pair(0., 10.));
		histoTypesRangeYMean.push_back(make_pair(-5., 10.));
	} else if (qcd) {
		histoTypesRangeX.push_back(make_pair(0., 900.));
		histoTypesRangeY.push_back(make_pair(0., 10.));
		histoTypesRangeYMean.push_back(make_pair(-30., 30.));
	} else {
		histoTypesRangeX.push_back(make_pair(0., 400.));
		histoTypesRangeY.push_back(make_pair(0., 30.));
		histoTypesRangeYMean.push_back(make_pair(-30., 30.));
	}
	histoTypes.push_back("sumEtSigmaMetX_");
	histoTypesSumEt.push_back("T");
	if (isZee) {
		histoTypesRangeX.push_back(make_pair(0., 300.));
		histoTypesRangeY.push_back(make_pair(0., 30.));
		histoTypesRangeYMean.push_back(make_pair(-5., 10.));
	} else if (qcd) {
		histoTypesRangeX.push_back(make_pair(0., 900.));
		histoTypesRangeY.push_back(make_pair(0., 30.));
		histoTypesRangeYMean.push_back(make_pair(-30., 30.));
	} else {
		histoTypesRangeX.push_back(make_pair(0., 400.));
		histoTypesRangeY.push_back(make_pair(0., 30.));
		histoTypesRangeYMean.push_back(make_pair(-30., 30.));
	}
	histoTypes.push_back("sumEtSigmaMetY_");
	histoTypesSumEt.push_back("T");
	if (isZee) {
		histoTypesRangeX.push_back(make_pair(0., 300.));
		histoTypesRangeY.push_back(make_pair(0., 30.));
		histoTypesRangeYMean.push_back(make_pair(-5., 10.));
	} else if (qcd) {
		histoTypesRangeX.push_back(make_pair(0., 900.));
		histoTypesRangeY.push_back(make_pair(0., 30.));
		histoTypesRangeYMean.push_back(make_pair(-30., 30.));
	} else {
		histoTypesRangeX.push_back(make_pair(0., 400.));
		histoTypesRangeY.push_back(make_pair(0., 30.));
		histoTypesRangeYMean.push_back(make_pair(-30., 30.));
	}
	histoTypes.push_back("sumEtSigmaMetXY_");
	histoTypesSumEt.push_back("T");
	if (isZee) {
		histoTypesRangeX.push_back(make_pair(0., 300.));
		histoTypesRangeY.push_back(make_pair(0., 30.));
		histoTypesRangeYMean.push_back(make_pair(-5., 10.));
	} else if (qcd) {
		histoTypesRangeX.push_back(make_pair(0., 900.));
		histoTypesRangeY.push_back(make_pair(0., 30.));
		histoTypesRangeYMean.push_back(make_pair(-30., 30.));
	} else {
		histoTypesRangeX.push_back(make_pair(0., 400.));
		histoTypesRangeY.push_back(make_pair(0., 30.));
		histoTypesRangeYMean.push_back(make_pair(-30., 30.));
	}
	//	histoTypes.push_back("sumEtSigmaMetpar_");
	//	histoTypes.push_back("sumEtSigmaMettrans_");
	//	histoTypes.push_back("sumEtSigmaMetpartrans_");

	vector < string > histoTypesMht;
	vector < pair<double, double> > histoTypesRangeX_mht;
	vector < pair<double, double> > histoTypesRangeY_mht;
	vector < pair<double, double> > histoTypesRangeYMean_mht;
	histoTypesMht.push_back("sumEtSigmaMhtX_");

	if (isZee) {
		histoTypesRangeX_mht.push_back(make_pair(0., 300.));
		histoTypesRangeY_mht.push_back(make_pair(0., 30.));
		histoTypesRangeYMean_mht.push_back(make_pair(-5., 10.));
	} else if (qcd) {
		histoTypesRangeX_mht.push_back(make_pair(0., 900.));
		histoTypesRangeY_mht.push_back(make_pair(0., 30.));
		histoTypesRangeYMean_mht.push_back(make_pair(-30., 30.));
	} else {
		histoTypesRangeX_mht.push_back(make_pair(0., 400.));
		histoTypesRangeY_mht.push_back(make_pair(0., 30.));
		histoTypesRangeYMean_mht.push_back(make_pair(-30., 30.));
	}
	histoTypesMht.push_back("sumEtSigmaMhtY_");

	if (isZee) {
		histoTypesRangeX_mht.push_back(make_pair(0., 300.));
		histoTypesRangeY_mht.push_back(make_pair(0., 30.));
		histoTypesRangeYMean_mht.push_back(make_pair(-5., 10.));
	} else if (qcd) {
		histoTypesRangeX_mht.push_back(make_pair(0., 900.));
		histoTypesRangeY_mht.push_back(make_pair(0., 30.));
		histoTypesRangeYMean_mht.push_back(make_pair(-30., 30.));
	} else {
		histoTypesRangeX_mht.push_back(make_pair(0., 400.));
		histoTypesRangeY_mht.push_back(make_pair(0., 30.));
		histoTypesRangeYMean_mht.push_back(make_pair(-30., 30.));
	}
	histoTypesMht.push_back("sumEtSigmaMhtXY_");

	if (isZee) {
		histoTypesRangeX_mht.push_back(make_pair(0., 300.));
		histoTypesRangeY_mht.push_back(make_pair(0., 30.));
		histoTypesRangeYMean_mht.push_back(make_pair(-5., 10.));
	} else if (qcd) {
		histoTypesRangeX_mht.push_back(make_pair(0., 900.));
		histoTypesRangeY_mht.push_back(make_pair(0., 30.));
		histoTypesRangeYMean_mht.push_back(make_pair(-30., 30.));
	} else {
		histoTypesRangeX_mht.push_back(make_pair(0., 400.));
		histoTypesRangeY_mht.push_back(make_pair(0., 30.));
		histoTypesRangeYMean_mht.push_back(make_pair(-30., 30.));
	}
	//	histoTypesMht.push_back("sumEtSigmaMhtpar_");
	//	histoTypesMht.push_back("sumEtSigmaMhttrans_");
	//	histoTypesMht.push_back("sumEtSigmaMhtpartrans_");

	vector < string > histoTypesTitle;
	vector < string > histoTypesTitleX;
	histoTypesTitle.push_back("Met Div Sumet [GeV]");
	histoTypesTitleX.push_back("#Sigma E_{T} [GeV]");
	histoTypesTitle.push_back("Met Sqrt SumEt [GeV]");
	histoTypesTitleX.push_back("#Sigma E_{T} [GeV]");
	histoTypesTitle.push_back("#slash{E}_{x} [GeV]");
	histoTypesTitleX.push_back("#Sigma #slash{E}_{T} [GeV]");

	histoTypesTitle.push_back("#slash{E}_{y} [GeV]");
	histoTypesTitleX.push_back("#Sigma #slash{E}_{T} [GeV]");

	histoTypesTitle.push_back("#slash{E}_{x,y} [GeV]");
	histoTypesTitleX.push_back("#Sigma #slash{E}_{T} [GeV]");

	//	histoTypesTitle.push_back("E_{#parallel(j1)}^{miss} [GeV]");
	//	histoTypesTitleX.push_back("#Sigma E_{T} [GeV]");
	//	histoTypesTitle.push_back("E_{#perp(j1)}^{miss} [GeV]");
	//	histoTypesTitleX.push_back("#Sigma E_{T} [GeV]");
	//	histoTypesTitle.push_back("E_{#parallel,#perp(j1)}^{miss} [GeV]");
	//	histoTypesTitleX.push_back("#Sigma E_{T} [GeV]");

	histoTypes.push_back("sumEtSigmaMettransBisector_");
	histoTypesSumEt.push_back("T");
	histoTypesTitle.push_back("#slash{E}_{T,#perp(q_{    T})}[GeV]");
	histoTypesTitleX.push_back("#Sigma E_{T} [GeV]");
	if (isZee) {
		histoTypesRangeX.push_back(make_pair(0., 300.));
		histoTypesRangeY.push_back(make_pair(0., 30.));
		histoTypesRangeYMean.push_back(make_pair(-5., 5.));
	} else if (qcd) {
		histoTypesRangeX.push_back(make_pair(0., 900.));
		histoTypesRangeY.push_back(make_pair(0., 30.));
		histoTypesRangeYMean.push_back(make_pair(-30., 30.));
	} else {
		histoTypesRangeX.push_back(make_pair(0., 400.));
		histoTypesRangeY.push_back(make_pair(0., 30.));
		histoTypesRangeYMean.push_back(make_pair(-30., 30.));
	}

	histoTypes.push_back("sumEtSigmaMetparBisector_");
	histoTypesSumEt.push_back("T");
	histoTypesTitle.push_back("#slash{E}_{T,#parallel (q_{T})}[GeV]");
	histoTypesTitleX.push_back("#Sigma E_{T} [GeV]");
	if (isZee) {
		histoTypesRangeX.push_back(make_pair(0., 300.));
		histoTypesRangeY.push_back(make_pair(0., 30.));
		histoTypesRangeYMean.push_back(make_pair(-15., 20.));
	} else if (qcd) {
		histoTypesRangeX.push_back(make_pair(0., 900.));
		histoTypesRangeY.push_back(make_pair(0., 30.));
		histoTypesRangeYMean.push_back(make_pair(-30., 30.));
	} else {
		histoTypesRangeX.push_back(make_pair(0., 400.));
		histoTypesRangeY.push_back(make_pair(0., 30.));
		histoTypesRangeYMean.push_back(make_pair(-30., 30.));
	}

	histoTypes.push_back("bisectPtSigmaMetparBisector_");
	histoTypesSumEt.push_back("F");
	if (isZee) {
		histoTypesRangeX.push_back(make_pair(30., 90.));
		histoTypesRangeY.push_back(make_pair(0., 20.));
		histoTypesRangeYMean.push_back(make_pair(-15., 20.));
	} else if (isPhotonJet) {
		histoTypesRangeX.push_back(make_pair(0., 90.));
		histoTypesRangeY.push_back(make_pair(0., 50.));
		histoTypesRangeYMean.push_back(make_pair(-15., 20.));
	} else if (qcd) {
		histoTypesRangeX.push_back(make_pair(30., 140.));
		histoTypesRangeY.push_back(make_pair(0., 20.));
		histoTypesRangeYMean.push_back(make_pair(-10., 6.));
	} else {
		histoTypesRangeX.push_back(make_pair(30., 140.));
		histoTypesRangeY.push_back(make_pair(0., 30.));
		histoTypesRangeYMean.push_back(make_pair(-10., 6.));
	}
	//if(debug)cout<<"histotypes"<<histoTypes.size()<<endl;
	//if(debug)cout<<"histotypesRangeX"<<histoTypesRangeX.size()<<endl;

	histoTypesTitle.push_back("#slash{E}_{T,#parallel (q_{T})} [GeV]");
	if (isZee) {
		histoTypesTitleX.push_back("p_{T } average (e1,e2) [GeV]");
	} else if (isPhotonJet) {
		histoTypesTitleX.push_back("p_{T } #gamma [GeV]");
	} else {
		histoTypesTitleX.push_back("p_{T } average (j1,j2) [GeV]");
	}
	histoTypes.push_back("bisectPtSigmaMettransBisector_");
	histoTypesSumEt.push_back("F");
	if (isZee) {
		histoTypesRangeX.push_back(make_pair(30., 90.));
		histoTypesRangeY.push_back(make_pair(0., 20.));
		histoTypesRangeYMean.push_back(make_pair(-5., 5.));
	} else if (isPhotonJet) {
		histoTypesRangeX.push_back(make_pair(0., 90.));
		histoTypesRangeY.push_back(make_pair(0., 20.));
		histoTypesRangeYMean.push_back(make_pair(-5., 5.));
	} else if (qcd) {
		histoTypesRangeX.push_back(make_pair(30., 140.));
		histoTypesRangeY.push_back(make_pair(0., 20.));
		histoTypesRangeYMean.push_back(make_pair(-5., 10.));
	} else {
		histoTypesRangeX.push_back(make_pair(30., 140.));
		histoTypesRangeY.push_back(make_pair(0., 30.));
		histoTypesRangeYMean.push_back(make_pair(-5., 10.));
	}
	histoTypesTitle.push_back("#slash{E}_{T, #perp(q_{    T})} [GeV]");
	if (isZee) {
		histoTypesTitleX.push_back("p_{T } average (e1,e2) [GeV]");
	} else if (isPhotonJet) {
		histoTypesTitleX.push_back("p_{T } #gamma [GeV]");
	} else {
		histoTypesTitleX.push_back("p_{T} average (j1,j2) [GeV]");
	}

	histoTypes.push_back("ucPtSigmaMetparBisector_");
	histoTypesSumEt.push_back("F");
	if (isZee) {
		histoTypesRangeX.push_back(make_pair(0., 90.));
		histoTypesRangeY.push_back(make_pair(0., 20.));
		histoTypesRangeYMean.push_back(make_pair(-15., 20.));
	} else if (qcd) {
		histoTypesRangeX.push_back(make_pair(0., 30.));
		histoTypesRangeY.push_back(make_pair(0., 20.));
		histoTypesRangeYMean.push_back(make_pair(-30., 30.));
	} else {
		histoTypesRangeX.push_back(make_pair(0., 30.));
		histoTypesRangeY.push_back(make_pair(0., 20.));
		histoTypesRangeYMean.push_back(make_pair(-30., 30.));
	}
	histoTypesTitle.push_back("#slash{E}_{T,#parallel (q_{T})}[GeV]");
	histoTypesTitleX.push_back("U_{T} [GeV]");

	histoTypes.push_back("ucPtSigmaMettransBisector_");
	histoTypesSumEt.push_back("F");
	if (isZee) {
		histoTypesRangeX.push_back(make_pair(0., 90.));
		histoTypesRangeY.push_back(make_pair(0., 20.));
		histoTypesRangeYMean.push_back(make_pair(-5., 5.));
	} else if (qcd) {
		histoTypesRangeX.push_back(make_pair(0., 30.));
		histoTypesRangeY.push_back(make_pair(0., 20.));
		histoTypesRangeYMean.push_back(make_pair(-30., 30.));
	} else {
		histoTypesRangeX.push_back(make_pair(0., 30.));
		histoTypesRangeY.push_back(make_pair(0., 20.));
		histoTypesRangeYMean.push_back(make_pair(-30., 30.));
	}
	histoTypesTitle.push_back("#slash{E}_{T,#perp(q_{    T})}[GeV]");
	histoTypesTitleX.push_back("U_{T} [GeV]");

	histoTypes.push_back("bisectParaSigmaMetparBisector_");
	histoTypesSumEt.push_back("F");
	if (isZee) {
		histoTypesRangeX.push_back(make_pair(0., 90.));
		histoTypesRangeY.push_back(make_pair(0., 60.));
		histoTypesRangeYMean.push_back(make_pair(-15., 20.));
	} else if (qcd) {
		histoTypesRangeX.push_back(make_pair(0., 60.));
		histoTypesRangeY.push_back(make_pair(0., 20.));
		histoTypesRangeYMean.push_back(make_pair(-15., 5.));
	} else {
		histoTypesRangeX.push_back(make_pair(0., 60.));
		histoTypesRangeY.push_back(make_pair(0., 20.));
		histoTypesRangeYMean.push_back(make_pair(-15., 10.));
	}
	histoTypesTitle.push_back("#slash{E}_{T,#parallel (q_{T})}[GeV]");
	if (isZee) {
		histoTypesTitleX.push_back("q_{T} [GeV]");
	} else if (isPhotonJet) {
		histoTypesTitleX.push_back("P_{#gamma} [GeV]");
	} else {
		histoTypesTitleX.push_back("p_{T} #vec{j1}+#vec{j2} [GeV]");
	}
	histoTypes.push_back("bisectParaSigmaMettransBisector_");
	histoTypesSumEt.push_back("F");
	if (isZee) {
		histoTypesRangeX.push_back(make_pair(0., 90.));
		histoTypesRangeY.push_back(make_pair(0., 60.));
		histoTypesRangeYMean.push_back(make_pair(-5., 5.));
	} else if (qcd) {
		histoTypesRangeX.push_back(make_pair(0., 60.));
		histoTypesRangeY.push_back(make_pair(0., 20.));
		histoTypesRangeYMean.push_back(make_pair(-5., 5.));
	} else {
		histoTypesRangeX.push_back(make_pair(0., 70.));
		histoTypesRangeY.push_back(make_pair(0., 20.));
		histoTypesRangeYMean.push_back(make_pair(-5., 5.));
	}
	histoTypesTitle.push_back("#slash{E}_{T,#perp(q_{    T})} [GeV]");
	if (isZee) {
		histoTypesTitleX.push_back("q_{T} [GeV]");
	} else if (isPhotonJet) {
		histoTypesTitleX.push_back("p_{T,#gamma,#parallel}  [GeV]");
	} else {
		histoTypesTitleX.push_back("p_{T,#parallel} #vec{j1}+#vec{j2} [GeV]");
	}

	histoTypes.push_back("bisectParaSigmaRecoilMetparBisector_");
	histoTypesSumEt.push_back("F");
	if (isZee || isPhotonJet) {
		histoTypesRangeX.push_back(make_pair(0., 90.));
		histoTypesRangeY.push_back(make_pair(0., 90.));
		histoTypesRangeYMean.push_back(make_pair(-5., 90.));
	} else if (qcd) {
		histoTypesRangeX.push_back(make_pair(0., 60.));
		histoTypesRangeY.push_back(make_pair(0., 20.));
		histoTypesRangeYMean.push_back(make_pair(-30., 30.));
	} else {
		histoTypesRangeX.push_back(make_pair(0., 70.));
		histoTypesRangeY.push_back(make_pair(0., 20.));
		histoTypesRangeYMean.push_back(make_pair(-30., 90.));
	}
	histoTypesTitle.push_back("u_{#parallel (q_{T})}[GeV]");
	if (isZee) {
		histoTypesTitleX.push_back("p_{T,Z,#parallel (q_{T})} (p_{T} #vec{e1}+#vec{e2}) [GeV]");
	} else if (isPhotonJet) {
		histoTypesTitleX.push_back("p_{T,#gamma}  [GeV]");
	} else {
		histoTypesTitleX.push_back("p_{T,#parallel (q_{T})} #vec{j1}+#vec{j2} [GeV]");
	}
	histoTypes.push_back("bisectParaSigmaRecoilMettransBisector_");
	histoTypesSumEt.push_back("F");
	if (isZee || isPhotonJet) {
		histoTypesRangeX.push_back(make_pair(0., 90.));
		histoTypesRangeY.push_back(make_pair(0., 20.));
		histoTypesRangeYMean.push_back(make_pair(-5., 5.));
	} else if (qcd) {
		histoTypesRangeX.push_back(make_pair(0., 60.));
		histoTypesRangeY.push_back(make_pair(0., 20.));
		histoTypesRangeYMean.push_back(make_pair(-5., 5.));
	} else {
		histoTypesRangeX.push_back(make_pair(0., 70.));
		histoTypesRangeY.push_back(make_pair(0., 20.));
		histoTypesRangeYMean.push_back(make_pair(-5., 5.));
	}
	histoTypesTitle.push_back("u_{#perp(q_{    T})}[GeV]");
	if (isZee) {
		histoTypesTitleX.push_back("p_{T,Z,#parallel (q_{T})} (p_{T} #vec{e1}+#vec{e2}) [GeV]");
	} else if (isPhotonJet) {
		histoTypesTitleX.push_back("p_{T,#gamma}  [GeV]");
	} else {
		histoTypesTitleX.push_back("p_{T,#parallel (q_{T})} #vec{j1}+#vec{j2} [GeV]");
	}
	///bisectSum vs met/recoil para/perp bisect sum
	histoTypes.push_back("bisectSumSigmaMetparBisectSum_");
	histoTypesSumEt.push_back("F");
	if (isZee) {
		histoTypesRangeX.push_back(make_pair(0., 90.));
		histoTypesRangeY.push_back(make_pair(0., 60.));
		histoTypesRangeYMean.push_back(make_pair(-15., 20.));
	} else if (isPhotonJet) {
		histoTypesRangeX.push_back(make_pair(0., 60.));
		histoTypesRangeY.push_back(make_pair(0., 60.));
		histoTypesRangeYMean.push_back(make_pair(-30., 30.));
	} else if (qcd) {
		histoTypesRangeX.push_back(make_pair(0., 60.));
		histoTypesRangeY.push_back(make_pair(0., 20.));
		histoTypesRangeYMean.push_back(make_pair(-30., 30.));
	} else {
		histoTypesRangeX.push_back(make_pair(0., 60.));
		histoTypesRangeY.push_back(make_pair(0., 20.));
		histoTypesRangeYMean.push_back(make_pair(-30., 30.));
	}
	if (isZee) {
		histoTypesTitle.push_back("#slash{E}_{#parallel (Z)}[GeV]");
	} else if (isPhotonJet) {
		histoTypesTitle.push_back("#slash{E}_{#parallel (#gamma)}[GeV]");
	} else {
		histoTypesTitle.push_back("#slash{E}_{#parallel (#vec{j1}+#vec{j2})}[GeV]");
	}

	if (isZee) {
		histoTypesTitleX.push_back("p_{T,Z} (p_{T} #vec{e1}+#vec{e2}) [GeV]");
	} else if (isPhotonJet) {
		histoTypesTitleX.push_back("P_{#gamma} [GeV]");
	} else {
		histoTypesTitleX.push_back("p_{T} #vec{j1}+#vec{j2} [GeV]");
	}
	histoTypes.push_back("bisectSumSigmaMettransBisectSum_");
	histoTypesSumEt.push_back("F");
	if (isZee) {
		histoTypesRangeX.push_back(make_pair(0., 90.));
		histoTypesRangeY.push_back(make_pair(0., 60.));
		histoTypesRangeYMean.push_back(make_pair(-5., 5.));
	} else if (isPhotonJet) {
		histoTypesRangeX.push_back(make_pair(0., 60.));
		histoTypesRangeY.push_back(make_pair(0., 60.));
		histoTypesRangeYMean.push_back(make_pair(-5., 5.));
	} else if (qcd) {
		histoTypesRangeX.push_back(make_pair(0., 60.));
		histoTypesRangeY.push_back(make_pair(0., 20.));
		histoTypesRangeYMean.push_back(make_pair(-5., 5.));
	} else {
		histoTypesRangeX.push_back(make_pair(0., 60.));
		histoTypesRangeY.push_back(make_pair(0., 20.));
		histoTypesRangeYMean.push_back(make_pair(-5., 5.));
	}
	if (isZee) {
		histoTypesTitle.push_back("#slash{E}_{#perp (Z)}[GeV]");
	} else if (isPhotonJet) {
		histoTypesTitle.push_back("#slash{E}_{#perp (#gamma)}[GeV]");
	} else {
		histoTypesTitle.push_back("#slash{E}_{#perp (#vec{j1}+#vec{j2})}[GeV]");
	}
	if (isZee) {
		histoTypesTitleX.push_back("p_{T,Z} (p_{T} #vec{e1}+#vec{e2}) [GeV]");
	} else if (isPhotonJet) {
		histoTypesTitleX.push_back("p_{T,#gamma}  [GeV]");
	} else {
		histoTypesTitleX.push_back("p_{T} #vec{j1}+#vec{j2} [GeV]");
	}

	histoTypes.push_back("bisectSumSigmaRecoilMetparBisectSum_");
	histoTypesSumEt.push_back("F");
	if (isZee || isPhotonJet) {
		histoTypesRangeX.push_back(make_pair(0., 90.));
		histoTypesRangeY.push_back(make_pair(0., 30.));
		histoTypesRangeYMean.push_back(make_pair(-5., 90.));
	} else if (qcd) {
		histoTypesRangeX.push_back(make_pair(0., 60.));
		histoTypesRangeY.push_back(make_pair(0., 20.));
		histoTypesRangeYMean.push_back(make_pair(-30., 30.));
	} else {
		histoTypesRangeX.push_back(make_pair(0., 60.));
		histoTypesRangeY.push_back(make_pair(0., 20.));
		histoTypesRangeYMean.push_back(make_pair(-30., 30.));
	}
	if (isZee) {
		histoTypesTitle.push_back("u_{#parallel (q_{T})} [GeV]");
	} else if (isPhotonJet) {
		histoTypesTitle.push_back("recoil_{#parallel (#gamma)}[GeV]");
	} else {
		histoTypesTitle.push_back("recoil_{#parallel (#vec{j1}+#vec{j2})}[GeV]");
	}
	if (isZee) {
		histoTypesTitleX.push_back("p_{T,Z} (p_{T} #vec{e1}+#vec{e2}) [GeV]");
	} else if (isPhotonJet) {
		histoTypesTitleX.push_back("p_{T,#gamma}  [GeV]");
	} else {
		histoTypesTitleX.push_back("p_{T} #vec{j1}+#vec{j2} [GeV]");
	}
	histoTypes.push_back("bisectSumSigmaRecoilMetparCorrJetBisectSum_");
	histoTypesSumEt.push_back("F");
	if (isZee || isPhotonJet) {
		histoTypesRangeX.push_back(make_pair(0., 90.));
		histoTypesRangeY.push_back(make_pair(0., 20.));
		histoTypesRangeYMean.push_back(make_pair(-5., 90.));
	} else if (qcd) {
		histoTypesRangeX.push_back(make_pair(0., 60.));
		histoTypesRangeY.push_back(make_pair(0., 20.));
		histoTypesRangeYMean.push_back(make_pair(-30., 30.));
	} else {
		histoTypesRangeX.push_back(make_pair(0., 60.));
		histoTypesRangeY.push_back(make_pair(0., 20.));
		histoTypesRangeYMean.push_back(make_pair(-30., 30.));
	}
	if (isZee) {
		histoTypesTitle.push_back(
									"recoil #slash{E}_{#parallel (Z)}-p_{T} #vec{#Delta Jet,GenJet}[GeV]");
	} else if (isPhotonJet) {
		histoTypesTitle.push_back(
									"recoil #slash{E}_{#parallel (#gamma)}-p_{T} #vec{#Delta Jet,GenJet}[GeV]");
	} else {
		histoTypesTitle.push_back(
									"recoil #slash{E}_{#parallel (#vec{j1}+#vec{j2})}-p_{T} #vec{#Delta Jet,GenJet}[GeV]");
	}
	if (isZee) {
		histoTypesTitleX.push_back("p_{T,Z} (p_{T} #vec{e1}+#vec{e2}) [GeV]");
	} else if (isPhotonJet) {
		histoTypesTitleX.push_back("p_{T,#gamma}  [GeV]");
	} else {
		histoTypesTitleX.push_back("p_{T} #vec{j1}+#vec{j2} [GeV]");
	}
	histoTypes.push_back("bisectSumSigmaRecoilMettransBisectSum_");
	histoTypesSumEt.push_back("F");
	if (isZee || isPhotonJet) {
		histoTypesRangeX.push_back(make_pair(0., 90.));
		histoTypesRangeY.push_back(make_pair(0., 30.));
		histoTypesRangeYMean.push_back(make_pair(-5., 90.));
	} else if (qcd) {
		histoTypesRangeX.push_back(make_pair(0., 60.));
		histoTypesRangeY.push_back(make_pair(0., 20.));
		histoTypesRangeYMean.push_back(make_pair(-30., 30.));
	} else {
		histoTypesRangeX.push_back(make_pair(0., 60.));
		histoTypesRangeY.push_back(make_pair(0., 20.));
		histoTypesRangeYMean.push_back(make_pair(-30., 30.));
	}
	if (isZee) {
		histoTypesTitle.push_back("u_{ #perp(q_{    T})}[GeV]");
	} else if (isPhotonJet) {
		histoTypesTitle.push_back("recoil_{#perp (#gamma)}[GeV]");
	} else {
		histoTypesTitle.push_back("recoil_{#perp (#vec{j1}+#vec{j2})}[GeV]");
	}
	if (isZee) {
		histoTypesTitleX.push_back("p_{T,Z} (p_{T} #vec{e1}+#vec{e2}) [GeV]");
	} else if (isPhotonJet) {
		histoTypesTitleX.push_back("p_{T,#gamma}  [GeV]");
	} else {
		histoTypesTitleX.push_back("p_{T} #vec{j1}+#vec{j2} [GeV]");
	}
	///


	histoTypes.push_back("bisectSumPtSigmaRecoilMet_");
	histoTypesSumEt.push_back("F");
	if (isZee) {
		histoTypesRangeX.push_back(make_pair(0., 90.));
		histoTypesRangeY.push_back(make_pair(0., 90.));
		histoTypesRangeYMean.push_back(make_pair(0., 90.));
	} else if (isPhotonJet) {
		histoTypesRangeX.push_back(make_pair(0., 90.));
		histoTypesRangeY.push_back(make_pair(0., 90.));
		histoTypesRangeYMean.push_back(make_pair(0., 90.));
	} else if (qcd) {
		histoTypesRangeX.push_back(make_pair(0., 60.));
		histoTypesRangeY.push_back(make_pair(0., 20.));
		histoTypesRangeYMean.push_back(make_pair(-30., 30.));
	} else {
		histoTypesRangeX.push_back(make_pair(0., 60.));
		histoTypesRangeY.push_back(make_pair(0., 20.));
		histoTypesRangeYMean.push_back(make_pair(-30., 30.));
	}
	histoTypesTitle.push_back("recoil[GeV]");
	if (isZee) {
		histoTypesTitleX.push_back("p_{T,Z} (p_{T} #vec{e1}+#vec{e2}) [GeV]");
	} else if (isPhotonJet) {
		histoTypesTitleX.push_back("p_{T,#gamma}  [GeV]");
	} else {
		histoTypesTitleX.push_back("p_{T} #vec{j1}+#vec{j2} [GeV]");
	}

	histoTypes.push_back("bisectSumPtSigmaAngleRecoilBisectSum_");
	histoTypesSumEt.push_back("F");
	if (isZee) {
		histoTypesRangeX.push_back(make_pair(0., 90.));
		histoTypesRangeY.push_back(make_pair(0., 3.14));
		histoTypesRangeYMean.push_back(make_pair(0., 3.14));
	} else if (qcd) {
		histoTypesRangeX.push_back(make_pair(0., 60.));
		histoTypesRangeY.push_back(make_pair(0., 20.));
		histoTypesRangeYMean.push_back(make_pair(-30., 30.));
	} else {
		histoTypesRangeX.push_back(make_pair(0., 60.));
		histoTypesRangeY.push_back(make_pair(0., 20.));
		histoTypesRangeYMean.push_back(make_pair(-30., 30.));
	}
	histoTypesTitle.push_back("#angle recoil-p_{T,Z} (p_{T} #vec{e1}+#vec{e2})");
	if (isZee) {
		histoTypesTitleX.push_back("p_{T,Z} (p_{T} #vec{e1}+#vec{e2}) [GeV]");
	} else if (isPhotonJet) {
		histoTypesTitleX.push_back("p_{T,#gamma}  [GeV]");
	} else {
		histoTypesTitleX.push_back("p_{T} #vec{j1}+#vec{j2} [GeV]");
	}

	histoTypes.push_back("bisectSumSigmaRecoilDivBisectSum_");
	histoTypesSumEt.push_back("F");
	if (isZee) {
		histoTypesRangeX.push_back(make_pair(0., 90.));
		histoTypesRangeY.push_back(make_pair(0.4, 1.7));
		histoTypesRangeYMean.push_back(make_pair(0.4, 1.7));
	} else if (qcd) {
		histoTypesRangeX.push_back(make_pair(0., 250.));
		histoTypesRangeY.push_back(make_pair(0.4, 1.7));
		histoTypesRangeYMean.push_back(make_pair(0.4, 1.7));
	} else {
		histoTypesRangeX.push_back(make_pair(0., 250.));
		histoTypesRangeY.push_back(make_pair(0.4, 1.7));
		histoTypesRangeYMean.push_back(make_pair(0.4, 1.7));
	}

	if (isZee) {
		histoTypesTitleX.push_back("q_{T} [GeV]");
		histoTypesTitle.push_back("u_{#parallel}/q_{T}");
		//q_{T} [GeV]
	} else if (isPhotonJet) {
		histoTypesTitleX.push_back("p_{T,#gamma} [GeV]");
		histoTypesTitle.push_back("u_{para}/p_{T,#gamma}");
	} else {
		histoTypesTitleX.push_back("p_{T} #vec{j1}+#vec{j2} [GeV]");
		histoTypesTitle.push_back("u_{para}/p_{T} #vec{j1}+#vec{j2}");
	}

	histoTypes.push_back("bisectSumSigmaRecoilPerpDivBisectSum_");
	histoTypesSumEt.push_back("F");
	if (isZee) {
		histoTypesRangeX.push_back(make_pair(0., 90.));
		histoTypesRangeY.push_back(make_pair(0., 1.7));
		histoTypesRangeYMean.push_back(make_pair(0., 1.7));
	} else if (qcd) {
		histoTypesRangeX.push_back(make_pair(0., 250.));
		histoTypesRangeY.push_back(make_pair(0., 1.7));
		histoTypesRangeYMean.push_back(make_pair(0., 1.7));
	} else {
		histoTypesRangeX.push_back(make_pair(0., 250.));
		histoTypesRangeY.push_back(make_pair(0., 1.7));
		histoTypesRangeYMean.push_back(make_pair(0., 1.7));
	}

	if (isZee) {
		histoTypesTitleX.push_back("p_{T,Z} (p_{T} #vec{e1}+#vec{e2}) [GeV]");
		histoTypesTitle.push_back("u_{perp}/q_{T}");
		//q_{T} [GeV]
	} else if (isPhotonJet) {
		histoTypesTitleX.push_back("p_{T,#gamma} [GeV]");
		histoTypesTitle.push_back("u_{perp}/p_{T,#gamma}");
	} else {
		histoTypesTitleX.push_back("p_{T} #vec{j1}+#vec{j2} [GeV]");
		histoTypesTitle.push_back("u_{perp}/p_{T} #vec{j1}+#vec{j2}");
	}

	histoTypes.push_back("bisectSumSigmaRecoilDivCorrJetBisectSum_");
	histoTypesSumEt.push_back("F");
	if (isZee) {
		histoTypesRangeX.push_back(make_pair(0., 90.));
		histoTypesRangeY.push_back(make_pair(0.4, 1.7));
		histoTypesRangeYMean.push_back(make_pair(0.4, 1.7));
	} else if (qcd) {
		histoTypesRangeX.push_back(make_pair(0., 250.));
		histoTypesRangeY.push_back(make_pair(0.4, 1.7));
		histoTypesRangeYMean.push_back(make_pair(0.4, 1.7));
	} else {
		histoTypesRangeX.push_back(make_pair(0., 250.));
		histoTypesRangeY.push_back(make_pair(0.4, 1.7));
		histoTypesRangeYMean.push_back(make_pair(0.4, 1.7));
	}
	histoTypesTitle.push_back("(u_{#parallel}/q_{T})_{#Delta_{jet}}");
	if (isZee) {
		histoTypesTitleX.push_back("q_{T} [GeV]");
	} else if (isPhotonJet) {
		histoTypesTitleX.push_back("q_{T} [GeV]");
	} else {
		histoTypesTitleX.push_back("p_{T} #vec{j1}+#vec{j2} [GeV]");
	}

	///add jet response histos

	histoTypes.push_back("bisectSumSigmaresponsejet_");
	histoTypesSumEt.push_back("F");
	if (isZee) {
		histoTypesRangeX.push_back(make_pair(0., 90.));
		histoTypesRangeY.push_back(make_pair(-5., 10.));
		histoTypesRangeYMean.push_back(make_pair(-5., 10.));
	} else if (qcd) {
		histoTypesRangeX.push_back(make_pair(0., 250.));
		histoTypesRangeY.push_back(make_pair(-5., 10.));
		histoTypesRangeYMean.push_back(make_pair(-5., 10.));
	} else {
		histoTypesRangeX.push_back(make_pair(0., 250.));
		histoTypesRangeY.push_back(make_pair(-5., 10.));
		histoTypesRangeYMean.push_back(make_pair(-5., 10.));
	}
	histoTypesTitle.push_back("#Delta_{jet} [GeV]");
	if (isZee) {
		histoTypesTitleX.push_back("q_{T} [GeV]");
	} else if (isPhotonJet) {
		histoTypesTitleX.push_back("q_{T} [GeV]");
	} else {
		histoTypesTitleX.push_back("p_{T} #vec{j1}+#vec{j2} [GeV]");
	}

	histoTypes.push_back("bisectSumSigmaresponsejetrel_");
	histoTypesSumEt.push_back("F");
	if (isZee) {
		histoTypesRangeX.push_back(make_pair(0., 90.));
		histoTypesRangeY.push_back(make_pair(-2., 2.));
		histoTypesRangeYMean.push_back(make_pair(-2., 2.));
	} else if (qcd) {
		histoTypesRangeX.push_back(make_pair(0., 250.));
		histoTypesRangeY.push_back(make_pair(-2., 2.));
		histoTypesRangeYMean.push_back(make_pair(-2., 2.));
	} else {
		histoTypesRangeX.push_back(make_pair(0., 250.));
		histoTypesRangeY.push_back(make_pair(-2., 2.));
		histoTypesRangeYMean.push_back(make_pair(-2., 2.));
	}
	histoTypesTitle.push_back("#Delta_{jet}/q_{T} ");
	if (isZee) {
		histoTypesTitleX.push_back("q_{T} [GeV]");
	} else if (isPhotonJet) {
		histoTypesTitleX.push_back("q_{T} [GeV]");
	} else {
		histoTypesTitleX.push_back("p_{T} #vec{j1}+#vec{j2} [GeV]");
	}
	//bool test=histoTypesSumEt[16];
	cout << "histotypes size vs histoTypesSumEt" << histoTypes.size() << "--"
		<< histoTypesSumEt[21] << endl;
	//return;

	vector < string > histoTypesTitleGen;
	histoTypesTitleGen.push_back("#slash{E}_{x,Gen} [GeV]");
	histoTypesTitleGen.push_back("#slash{E}_{y,Gen} [GeV]");
	histoTypesTitleGen.push_back("#slash{E}_{x,y,Gen} [GeV]");
	histoTypesTitleGen.push_back("#slash{E}_{#parallel,Gen} [GeV]");
	histoTypesTitleGen.push_back("#slash{E}_{#perp,Gen} [GeV]");
	histoTypesTitleGen.push_back("#slash{E}_{#parallel,#perp,Gen} [GeV]");
	vector < string > histoTypesMhtTitle;
	histoTypesMhtTitle.push_back("#slash{H}_{x} [GeV]");
	histoTypesMhtTitle.push_back("#slash{H}_{y} [GeV]");
	histoTypesMhtTitle.push_back("#slash{H}_{x,y} [GeV]");
	histoTypesMhtTitle.push_back("#slash{H}_{#parallel} [GeV]");
	histoTypesMhtTitle.push_back("#slash{H}_{#perp} [GeV]");
	histoTypesMhtTitle.push_back("#slash{H}_{#perp,#parallel} [GeV]");

	///MET Histos
	vector < string > metHistoNames;
	if (plotTypeRaw)
		metHistoNames.push_back("NoCorr");
	if (plotTypeI)
		metHistoNames.push_back("Type1");
	if (plotTypeII)
		metHistoNames.push_back("Type1UC");
	if (plotTypeIILocal)
		metHistoNames.push_back("Type1UCCorr");
	if (plotTypePF)
		metHistoNames.push_back("PF");
	if (plotTypePFI)
		metHistoNames.push_back("PFTypeI");
	if (plotTypePFII)
		metHistoNames.push_back("PFTypeII");
	if (plotTypePFIIL)
		metHistoNames.push_back("PFTypeIIL");
	if (plotTypeTC)
		metHistoNames.push_back("TC");
	//metHistoNames.push_back("Type1Muon");

	vector < string > metHistoTitles;
	if (plotTypeRaw)
		metHistoTitles.push_back("No Corr.");
	if (plotTypeI)
		metHistoTitles.push_back("Type I");
	if (plotTypeII)
		metHistoTitles.push_back("Type I+II_{M}");
	if (plotTypeIILocal)
		metHistoTitles.push_back("Type I+II");
	if (plotTypePF)
		metHistoTitles.push_back("No Corr.");
	if (plotTypePFI)
		metHistoTitles.push_back("Type I");
	if (plotTypePFII)
		metHistoTitles.push_back("Type I+II_{M}");
	if (plotTypePFIIL)
		metHistoTitles.push_back("Type I+II");
	if (plotTypeTC)
		metHistoTitles.push_back("TC");

	bool isPFOnlyPlot = false;
	if (plotTypePF || plotTypePFI || plotTypePFII || plotTypePFIIL) {
		isPFOnlyPlot = true;
		cout << "is PF!" << endl;
	} else {
		cout << "is Calo!!!" << endl;
	}
	//metHistoTitles.push_back("Type1 & Muon");

	vector < string > mhtHistoNames;
	mhtHistoNames.push_back("NoCorr");
	mhtHistoNames.push_back("L2L3");
	//mhtHistoNames.push_back("L2L3Type1");

	vector < string > mhtHistoTitles;
	mhtHistoTitles.push_back("No Corr.");
	mhtHistoTitles.push_back("L2L3");
	//mhtHistoTitles.push_back("L2L3(only Type1MET)");

	vector < string > genMetHistoNames;
	genMetHistoNames.push_back("genMetTrue");
	//genMetHistoNames.push_back("genMetTrue");

	vector < string > metgenHistoTitles;
	metgenHistoTitles.push_back("Gen #slash{E}_{T}(True)");
	//metgenHistoTitles.push_back("Gen E_{T}^{miss}(True)");

	vector < string > genmetHistoTypes;
	vector < pair<double, double> > genmetHistoTypes1DRangeX;
	genmetHistoTypes.push_back("GenEtVsEt_");
	genmetHistoTypes.push_back("GenSumEtVsSumEt_");

	if (isZee) {
		genmetHistoTypes1DRangeX.push_back(make_pair(0., 100.));
	} else if (qcd) {
		genmetHistoTypes1DRangeX.push_back(make_pair(0., 300.));
	} else {
		genmetHistoTypes1DRangeX.push_back(make_pair(0., 100.));
	}
	if (isZee) {
		genmetHistoTypes1DRangeX.push_back(make_pair(0., 600.));
	} else if (qcd) {
		genmetHistoTypes1DRangeX.push_back(make_pair(0., 900.));
	} else {
		genmetHistoTypes1DRangeX.push_back(make_pair(0., 300.));
	}

	vector<int> dataColorsUC;
	dataColorsUC.push_back(1);
	dataColorsUC.push_back(1);
	//dataColorsUC.push_back(3);
	dataColorsUC.push_back(1);
	dataColorsUC.push_back(1);
	dataColorsUC.push_back(1);
	dataColorsUC.push_back(1);
	dataColorsUC.push_back(1);
	dataColorsUC.push_back(1);
	dataColorsUC.push_back(1);
	dataColorsUC.push_back(1);

	vector<int> mcColorsUC;
	mcColorsUC.push_back(kBlue);
	mcColorsUC.push_back(kBlue - 4);
	//mcColorsUC.push_back(3);
	mcColorsUC.push_back(kBlue - 7);
	mcColorsUC.push_back(kRed - 9);
	mcColorsUC.push_back(kRed - 10);
	mcColorsUC.push_back(kRed - 13);
	mcColorsUC.push_back(kRed - 16);

	vector<int> dataMarkersUC;
	dataMarkersUC.push_back(24);
	dataMarkersUC.push_back(21);
	dataMarkersUC.push_back(22);
	dataMarkersUC.push_back(20);
	dataMarkersUC.push_back(24);
	dataMarkersUC.push_back(25);
	dataMarkersUC.push_back(26);
	dataMarkersUC.push_back(27);

	vector<int> dataColors;
	if (plotTypeRaw)
		dataColors.push_back(1);
	if (plotTypeI)
		dataColors.push_back(4);
	if (plotTypeII)
		dataColors.push_back(3);
	if (plotTypeIILocal)
		dataColors.push_back(2);
	if (plotTypePF)
		dataColors.push_back(1);
	if (plotTypePFI)
		dataColors.push_back(4);
	if (plotTypePFII)
		dataColors.push_back(kOrange - 7);
	if (plotTypePFIIL)
		dataColors.push_back(2);
	if (plotTypeTC)
		dataColors.push_back(kGreen + 2);
	dataColors.push_back(1);
	dataColors.push_back(1);
	dataColors.push_back(1);
	dataColors.push_back(1);
	dataColors.push_back(1);
	//dataColors.push_back(3);
	//dataColors.push_back(32);

	vector<int> dataMarkers;
	if (plotTypeRaw)
		dataMarkers.push_back(24);
	if (plotTypeI)
		dataMarkers.push_back(21);
	if (plotTypeII)
		dataMarkers.push_back(22);
	if (plotTypeIILocal)
		dataMarkers.push_back(20);
	if (plotTypePF)
		dataMarkers.push_back(24);
	if (plotTypePFI)
		dataMarkers.push_back(21);
	if (plotTypePFII)
		dataMarkers.push_back(22);
	if (plotTypePFIIL)
		dataMarkers.push_back(20);
	if (plotTypeTC)
		dataMarkers.push_back(25);
	dataMarkers.push_back(20);
	dataMarkers.push_back(22);
	dataMarkers.push_back(23);
	dataMarkers.push_back(23);
	dataMarkers.push_back(23);
	dataMarkers.push_back(23);
	dataMarkers.push_back(23);
	dataMarkers.push_back(23);
	dataMarkers.push_back(23);

	vector<int> mcLineColors;
	if (plotTypeRaw)
		mcLineColors.push_back(1);
	if (plotTypeI)
		mcLineColors.push_back(4);
	if (plotTypeII)
		mcLineColors.push_back(3);
	if (plotTypeIILocal)
		mcLineColors.push_back(2);
	if (plotTypePF)
		mcLineColors.push_back(1);
	//mcLineColors.push_back(kOrange);
	if (plotTypePFI)
		mcLineColors.push_back(4);
	//mcLineColors.push_back(kOrange - 3);
	if (plotTypePFII)
		mcLineColors.push_back(kOrange - 7);
	if (plotTypePFIIL)
		mcLineColors.push_back(2);
	//mcLineColors.push_back(kOrange + 5);
	if (plotTypeTC)
		mcLineColors.push_back(kGreen + 2);
	mcLineColors.push_back(2);
	mcLineColors.push_back(2);
	mcLineColors.push_back(2);
	mcLineColors.push_back(2);
	mcLineColors.push_back(2);

	vector<int> mcLineStyle;
	if (plotTypeRaw)
		mcLineStyle.push_back(2);
	if (plotTypeI)
		mcLineStyle.push_back(3);
	if (plotTypeII)
		mcLineStyle.push_back(4);
	if (plotTypeIILocal)
		mcLineStyle.push_back(6);
	if (plotTypePF)
		mcLineStyle.push_back(7);
	if (plotTypePFI)
		mcLineStyle.push_back(8);
	if (plotTypePFII)
		mcLineStyle.push_back(9);
	if (plotTypePFIIL)
		mcLineStyle.push_back(5);
	if (plotTypeTC)
		mcLineStyle.push_back(10);
	mcLineStyle.push_back(3);
	mcLineStyle.push_back(3);
	mcLineStyle.push_back(3);
	mcLineStyle.push_back(3);
	mcLineStyle.push_back(3);

	vector<int> mcColors;
	mcColors.push_back(kYellow);
	mcColors.push_back(kYellow - 7);
	mcColors.push_back(kOrange + 7);
	mcColors.push_back(kOrange + 5);
	mcColors.push_back(kOrange + 4);
	mcColors.push_back(kOrange + 3);
	mcColors.push_back(kOrange + 3);
	mcColors.push_back(kOrange + 3);
	mcColors.push_back(kOrange + 3);
	mcColors.push_back(kOrange + 3);

	vector<int> mcStyle;
	mcStyle.push_back(1001);
	if (plotTypeI)
		dataColors.push_back(4);
	mcStyle.push_back(3008);
	mcStyle.push_back(3325);
	mcStyle.push_back(3008);
	mcStyle.push_back(3008);
	mcStyle.push_back(3325);
	mcStyle.push_back(3325);
	mcStyle.push_back(3325);
	mcStyle.push_back(3325);
	mcStyle.push_back(3325);

	string outnameAppendix = "_MetComp";
	if (plotTypeRaw) {
		outnameAppendix = outnameAppendix + "_Raw";
	}
	if (plotTypeI) {
		outnameAppendix = outnameAppendix + "_TypeI";
	}

	if (plotTypeII) {
		outnameAppendix = outnameAppendix + "_TypeII";

	}
	if (plotTypeIILocal) {
		outnameAppendix = outnameAppendix + "_TypeIIL";
	}
	if (plotTypePF) {
		outnameAppendix = outnameAppendix + "_PF";
	}
	if (plotTypePFI) {
		outnameAppendix = outnameAppendix + "_PFI";
	}
	if (plotTypePFII) {
		outnameAppendix = outnameAppendix + "_PFII";
	}
	if (plotTypePFIIL) {
		outnameAppendix = outnameAppendix + "_PFIIL";
	}
	if (plotTypeTC) {
		outnameAppendix = outnameAppendix + "_TC";
	}

	TFile *output = new TFile((outfilename + outnameAppendix + ".root").c_str(), "recreate");
	if (fileMC != 0)
		output->SetName((outfilename + outnameAppendix + ".root").c_str());

	double maxYSigmaPlots = 20;
	double minXSigmaPlots = 0;
	double maxXSigmaPlots = 60;
	double minXSumEtHt = -60;
	double maxXSumEtHt = 60;
	double maxXMet = 60;
	if (qcd) {
		maxYSigmaPlots = 30;
		minXSigmaPlots = 0;
		maxXSigmaPlots = 500;
		minXSumEtHt = -500;
		maxXSumEtHt = 500;
		maxXMet = 300;
	} else if (isZee) {
		maxYSigmaPlots = 30;
		minXSigmaPlots = 0;
		maxXSigmaPlots = 500;
		minXSumEtHt = -500;
		maxXSumEtHt = 500;
		maxXMet = 100;

	}

	/////////////////////////////////DRAW Proj UmeasAlongUgen vs
	vector < string > histoTypesProjUGen;

	histoTypesProjUGen.push_back("ProjUMeasVsUtruePara");
	//histoTypesProjUGen.push_back("corrDeltaTrueVsRaw");
	histoTypesProjUGen.push_back("corrDeltaTrueVsTrueRel");
	//histoTypesProjUGen.push_back("RawVsTrue");
	if (isOnlyMC) {
		histoTypesProjUGen.push_back("ProjUMeasVsUgenPara");
		histoTypesProjUGen.push_back("ProjUMeasVsUgenPerp");
		histoTypesProjUGen.push_back("corrDeltaGenVsRaw");
		histoTypesProjUGen.push_back("corrDeltaGenVsGen");
		histoTypesProjUGen.push_back("corrDeltaGenVsGenRel");
		histoTypesProjUGen.push_back("corrDeltaGenCorrVsGen");
		histoTypesProjUGen.push_back("corrDeltaGenCorrVsRaw");
		histoTypesProjUGen.push_back("corrDeltaGenAppliedVsRaw");
		histoTypesProjUGen.push_back("corrDeltaGenAppliedVsGen");
		histoTypesProjUGen.push_back("RawVsGen");
	}

	vector < string > histoTypesProjUGenVSRAW;
	//histoTypesProjUGenVSRAW.push_back("corrDeltaTrueVsTrue_VSRAWG");
	histoTypesProjUGenVSRAW.push_back("corrDeltaTrueVsTrueRel_VSRAWG");
	histoTypesProjUGenVSRAW.push_back("ProjUMeasVsUtruePara_VSRAWG");
	if (isOnlyMC) {
		histoTypesProjUGenVSRAW.push_back("corrDeltaGenVsGen_VSRAWG");
		histoTypesProjUGenVSRAW.push_back("corrDeltaGenVsGennotpara_VSRAWG");
		histoTypesProjUGenVSRAW.push_back("corrDeltaGenVsGenRel_VSRAWG");
		histoTypesProjUGenVSRAW.push_back("ProjUMeasVsUgenPara_VSRAWG");
	}

	vector < string > histoTypesProjUGen_prefix;

	histoTypesProjUGen_prefix.push_back("");
	//histoTypesProjUGen_prefix.push_back("UC_");
	histoTypesProjUGen_prefix.push_back("UC_");
	//histoTypesProjUGen_prefix.push_back("UC_");
	if (isOnlyMC) {
		histoTypesProjUGen_prefix.push_back("");
		histoTypesProjUGen_prefix.push_back("");
		histoTypesProjUGen_prefix.push_back("UC_");
		histoTypesProjUGen_prefix.push_back("UC_");
		histoTypesProjUGen_prefix.push_back("UC_");
		histoTypesProjUGen_prefix.push_back("UC_");
		histoTypesProjUGen_prefix.push_back("UC_");
		histoTypesProjUGen_prefix.push_back("UC_");
		histoTypesProjUGen_prefix.push_back("UC_");
		histoTypesProjUGen_prefix.push_back("UC_");
	}

	int maxYSigmaPlotsUC = 20;
	int maxYMeanPlotsUC = 40;
	int minXSigmaPlotsUC = 0;
	int maxXSigmaPlotsUC = 50;

	vector<double> histoTypesProjUGen_lowEdgeY;

	histoTypesProjUGen_lowEdgeY.push_back(0);
	//histoTypesProjUGen_lowEdgeY.push_back(0.);
	histoTypesProjUGen_lowEdgeY.push_back(0.);
	//histoTypesProjUGen_lowEdgeY.push_back(0.);
	if (isOnlyMC) {
		histoTypesProjUGen_lowEdgeY.push_back(0);
		histoTypesProjUGen_lowEdgeY.push_back(-5);
		histoTypesProjUGen_lowEdgeY.push_back(0.);
		histoTypesProjUGen_lowEdgeY.push_back(0.);
		histoTypesProjUGen_lowEdgeY.push_back(0.);
		histoTypesProjUGen_lowEdgeY.push_back(0.);
		histoTypesProjUGen_lowEdgeY.push_back(0.);
		histoTypesProjUGen_lowEdgeY.push_back(0.);
		histoTypesProjUGen_lowEdgeY.push_back(0.);
		histoTypesProjUGen_lowEdgeY.push_back(0.);
	}

	vector<double> histoTypesProjUGen_highEdgeY;

	histoTypesProjUGen_highEdgeY.push_back(maxYMeanPlotsUC);
	//histoTypesProjUGen_highEdgeY.push_back(2);
	histoTypesProjUGen_highEdgeY.push_back(2);
	//histoTypesProjUGen_highEdgeY.push_back(maxYMeanPlotsUC);
	if (isOnlyMC) {
		histoTypesProjUGen_highEdgeY.push_back(maxYMeanPlotsUC);
		histoTypesProjUGen_highEdgeY.push_back(5);
		histoTypesProjUGen_highEdgeY.push_back(maxYMeanPlotsUC);
		histoTypesProjUGen_highEdgeY.push_back(maxYMeanPlotsUC);
		histoTypesProjUGen_highEdgeY.push_back(maxYMeanPlotsUC);
		histoTypesProjUGen_highEdgeY.push_back(maxYMeanPlotsUC);
		histoTypesProjUGen_highEdgeY.push_back(maxYMeanPlotsUC);
		histoTypesProjUGen_highEdgeY.push_back(maxYMeanPlotsUC);
		histoTypesProjUGen_highEdgeY.push_back(maxYMeanPlotsUC);
		histoTypesProjUGen_highEdgeY.push_back(maxYMeanPlotsUC);
	}

	vector < string > utypeNames;
	if (!isPFOnlyPlot) {
		utypeNames.push_back("");
		utypeNames.push_back("para_");
		if (fileMC != 0 && isOnlyMC)
			utypeNames.push_back("paraGen_");
		utypeNames.push_back("paraBisectSum_");
	} else {
		utypeNames.push_back("PF");
		utypeNames.push_back("paraPF_");
		if (fileMC != 0 && isOnlyMC)
			utypeNames.push_back("paraGenPF_");

		utypeNames.push_back("paraBisectSumPF_");
	}
	vector < string > histoTypesProjUGenVSRAW_prefix;

	histoTypesProjUGenVSRAW_prefix.push_back("UC_");
	histoTypesProjUGenVSRAW_prefix.push_back("UC_");
	histoTypesProjUGenVSRAW_prefix.push_back("");
	if (isOnlyMC) {

		histoTypesProjUGenVSRAW_prefix.push_back("UC_");
		histoTypesProjUGenVSRAW_prefix.push_back("UC_");
		histoTypesProjUGenVSRAW_prefix.push_back("UC_");
		histoTypesProjUGenVSRAW_prefix.push_back("");
	}
	vector < string > histoTypesProjUGenTitleX;
	histoTypesProjUGenTitleX.push_back("q_{T} [GeV]");

	//histoTypesProjUGenTitleX.push_back("U_{T,meas,raw} [GeV]");
	histoTypesProjUGenTitleX.push_back("q_{T} [GeV]");
	//	histoTypesProjUGenTitleX.push_back("U_{T,true} [GeV]");
	if (isOnlyMC) {
		histoTypesProjUGenTitleX.push_back("U_{T,gen}[GeV]");
		histoTypesProjUGenTitleX.push_back("U_{T,gen}[GeV]");
		histoTypesProjUGenTitleX.push_back("U_{T} [GeV]");
		histoTypesProjUGenTitleX.push_back("U_{T,gen} [GeV]");
		histoTypesProjUGenTitleX.push_back("U_{T,gen} [GeV]");
		histoTypesProjUGenTitleX.push_back("U_{T,gen} [GeV]");
		histoTypesProjUGenTitleX.push_back("U_{T} [GeV]");
		histoTypesProjUGenTitleX.push_back("U_{T} [GeV]");
		histoTypesProjUGenTitleX.push_back("U_{T,gen} [GeV]");
		histoTypesProjUGenTitleX.push_back("U_{T,gen} [GeV]");
	}

	vector < string > histoTypesProjUGenVSRAWTitleX;
	//histoTypesProjUGenVSRAWTitleX.push_back("<U_{T,meas,#parallel,raw} [GeV]>");
	histoTypesProjUGenVSRAWTitleX.push_back("<U_{T,#parallel} [GeV]>");
	histoTypesProjUGenVSRAWTitleX.push_back("<U_{T} [GeV]>");
	if (isOnlyMC) {
		histoTypesProjUGenVSRAWTitleX.push_back("<U_{T,#parallel} [GeV]>");
		histoTypesProjUGenVSRAWTitleX.push_back("<U_{T,#parallel} [GeV]>");
		histoTypesProjUGenVSRAWTitleX.push_back("<U_{T,#parallel} [GeV]>");
		histoTypesProjUGenVSRAWTitleX.push_back("<U_{T} [GeV]>");
	}

	vector < string > histoTypesProjUGenTitleY;
	histoTypesProjUGenTitleY.push_back("U_{T,#parallel}[GeV]");

	//histoTypesProjUGenTitleY.push_back(
	//		"#Delta_{true}=U_{meas,L2L3}-U_{meas}");
	histoTypesProjUGenTitleY.push_back(" R");
	//histoTypesProjUGenTitleY.push_back("U_{meas}");
	if (isOnlyMC) {
		histoTypesProjUGenTitleY.push_back("U_{T,#parallel}[GeV]");
		histoTypesProjUGenTitleY.push_back("U_{T,#perp}[GeV]");
		histoTypesProjUGenTitleY.push_back("#Delta_{Gen}=U_{gen}-U_{meas}");
		histoTypesProjUGenTitleY.push_back("#Delta_{Gen}=U_{gen}-U_{meas}");
		histoTypesProjUGenTitleY.push_back("#Delta_{Gen,rel}");
		histoTypesProjUGenTitleY.push_back("#Delta_{GenCorr}=U_{gen}-U_{meas,corr}");
		histoTypesProjUGenTitleY.push_back("#Delta_{GenCorr}=U_{gen}-U_{meas,corr}");
		histoTypesProjUGenTitleY.push_back("#Delta_{GenApplied}=U_{corr}-U_{meas}");
		histoTypesProjUGenTitleY.push_back("#Delta_{GenApplied}=U_{corr}-U_{meas}");

		histoTypesProjUGenTitleY.push_back("U_{meas}");
	}

	vector < string > histoTypesProjUGenVSRAWTitleY;
	//histoTypesProjUGenVSRAWTitleY.push_back("#Delta_{TrueCorr(<U_{meas}>)}");
	histoTypesProjUGenVSRAWTitleY.push_back("U_{Scale}");
	histoTypesProjUGenVSRAWTitleY.push_back("U_{T,#parallel} [GeV]");
	if (isOnlyMC) {
		histoTypesProjUGenVSRAWTitleY.push_back("#Delta_{GenCorr(<U_{meas}>)}");
		histoTypesProjUGenVSRAWTitleY.push_back("#Delta_{GenCorr(<U_{meas}>)}");
		histoTypesProjUGenVSRAWTitleY.push_back("U_{Scale}");
		histoTypesProjUGenVSRAWTitleY.push_back("U_{T,#parallel} [GeV]");
	}
	if (debug)
		cout << "H1" << endl;
	vector < string > histoTypesUC2D;
	histoTypesUC2D.push_back("rawCaloMetElectronsVsElectrons");
	histoTypesUC2D.push_back("typeICaloMetElectronsVsElectrons");
	histoTypesUC2D.push_back("typeIICaloMetElectronsVsElectrons");
	histoTypesUC2D.push_back("sumGenJetsElectronsUgenVsElectrons");
	histoTypesUC2D.push_back("rawCaloMetPhotonsVsPhotons");
	histoTypesUC2D.push_back("typeICaloMetPhotonsVsPhotons");
	histoTypesUC2D.push_back("typeIICaloMetPhotonsVsPhotons");
	histoTypesUC2D.push_back("sumGenJetsPhotonsUgenVsPhotons");
	histoTypesUC2D.push_back("corrFactorTrueVsRaw");
	histoTypesUC2D.push_back("corrFactorTrueVsRawEta");
	histoTypesUC2D.push_back("corrFactorTrueVsRawEnergy");
	histoTypesUC2D.push_back("corrFactorGenVsRaw");
	histoTypesUC2D.push_back("corrFactorGenVsRawEta");
	histoTypesUC2D.push_back("corrFactorGenVsRawEnergy");
	histoTypesUC2D.push_back("corrFactorAppliedVsRaw");
	histoTypesUC2D.push_back("corrFactorAppliedVsRawEta");
	histoTypesUC2D.push_back("corrFactorAppliedVsRawEnergy");
	histoTypesUC2D.push_back("corrFactorCorrGenVsRaw");
	histoTypesUC2D.push_back("corrFactorGenVsN90");
	histoTypesUC2D.push_back("corrFactorGenVsNjetsBelow");
	histoTypesUC2D.push_back("corrFactorGenVsPercOoC");
	histoTypesUC2D.push_back("corrFactorGenVsRawNotCleaned");

	vector < string > histoTypesUC2DTitleY;
	histoTypesUC2DTitleY.push_back("#slash{E}_{T,raw} [GeV]");
	histoTypesUC2DTitleY.push_back("#slash{E}_{T,TypeI} [GeV]");
	histoTypesUC2DTitleY.push_back("#slash{E}_{T,TypeII} [GeV]");
	histoTypesUC2DTitleY.push_back(
									"p_{T} (#vec{u_{gen}}+#Sigma #vec{GenJets} + #vec{e_{gen}}) [GeV]");
	histoTypesUC2DTitleY.push_back("#slash{E}_{T,raw} [GeV]");
	histoTypesUC2DTitleY.push_back("#slash{E}_{T,TypeI} [GeV]");
	histoTypesUC2DTitleY.push_back("#slash{E}_{T,TypeII} [GeV]");
	histoTypesUC2DTitleY.push_back(
									"p_{T} (#vec{u_{gen}}+#Sigma #vec{GenJets} + #vec{#gamma_{gen}}) [GeV]");
	histoTypesUC2DTitleY.push_back("Correction C_{true}=#frac{U_{meas,L2L3}}{U_{meas,raw}}");
	histoTypesUC2DTitleY.push_back("Correction C_{true}=#frac{U_{meas,L2L3}}{U_{meas,raw}}");
	histoTypesUC2DTitleY.push_back("Correction C_{true}=#frac{U_{meas,L2L3}}{U_{meas,raw}}");
	histoTypesUC2DTitleY.push_back("Correction C_{Gen}=#frac{U_{gen}}{U_{meas,raw}}");
	histoTypesUC2DTitleY.push_back("Correction C_{Gen}=#frac{U_{gen}}{U_{meas,raw}}");
	histoTypesUC2DTitleY.push_back("Correction C_{Gen}=#frac{U_{gen}}{U_{meas,raw}}");
	histoTypesUC2DTitleY.push_back("Correction C_{}=#frac{U_{corr}}{U_{meas,raw}}");
	histoTypesUC2DTitleY.push_back("Correction C_{}=#frac{U_{corr}}{U_{meas,raw}}");
	histoTypesUC2DTitleY.push_back("Correction C_{}=#frac{U_{corr}}{U_{meas,raw}}");
	histoTypesUC2DTitleY.push_back("Correction C_{CorrGen}=#frac{U_{gen}}{U_{meas,corr}}");
	histoTypesUC2DTitleY.push_back("Correction C_{Gen}=#frac{U_{gen}}{U_{meas,raw}}");
	histoTypesUC2DTitleY.push_back("Correction C_{Gen}=#frac{U_{gen}}{U_{meas,raw}}");
	histoTypesUC2DTitleY.push_back("Correction C_{Gen}=#frac{U_{gen}}{U_{meas,raw}}");
	histoTypesUC2DTitleY.push_back("Correction C_{Gen}=#frac{U_{gen}}{U_{meas,raw}}");

	vector < string > histoTypesUC2DTitleX;
	histoTypesUC2DTitleX.push_back("p_{T} #Sigma #vec{e_{meas}} [GeV]");
	histoTypesUC2DTitleX.push_back("p_{T} #Sigma #vec{e_{meas}} [GeV]");
	histoTypesUC2DTitleX.push_back("p_{T} #Sigma #vec{e_{meas}} [GeV]");
	histoTypesUC2DTitleX.push_back("p_{T} #Sigma #vec{e_{meas}} [GeV]");
	histoTypesUC2DTitleX.push_back("p_{T} #Sigma #vec{#gamma_{meas}} [GeV]");
	histoTypesUC2DTitleX.push_back("p_{T} #Sigma #vec{#gamma_{meas}} [GeV]");
	histoTypesUC2DTitleX.push_back("p_{T} #Sigma #vec{#gamma_{meas}} [GeV]");
	histoTypesUC2DTitleX.push_back("p_{T} #Sigma #vec{#gamma_{meas}} [GeV]");
	histoTypesUC2DTitleX.push_back("U_{T} [GeV]");
	histoTypesUC2DTitleX.push_back("#eta U_{T} ");
	histoTypesUC2DTitleX.push_back("energy U_{T} [GeV]");
	histoTypesUC2DTitleX.push_back("U_{T} [GeV]");
	histoTypesUC2DTitleX.push_back("#eta U_{T} ");
	histoTypesUC2DTitleX.push_back("energy U_{T} [GeV]");
	histoTypesUC2DTitleX.push_back("U_{T} [GeV]");
	histoTypesUC2DTitleX.push_back("#eta U_{T} ");
	histoTypesUC2DTitleX.push_back("energy U_{T} [GeV]");
	histoTypesUC2DTitleX.push_back("U_{T} [GeV]");
	histoTypesUC2DTitleX.push_back("N90 jets below threshold");
	histoTypesUC2DTitleX.push_back("# jets below threshold");
	histoTypesUC2DTitleX.push_back("#frac{Out of Cone Pt}{U_{meas,raw}}");
	histoTypesUC2DTitleX.push_back("U_{T,not CLEANED} [GeV]");

	vector < string > histoTypesUC1DTitleX;
	histoTypesUC1DTitleX.push_back("#slash{E}_{T} [GeV]");
	histoTypesUC1DTitleX.push_back("q_{T} [GeV]");
	histoTypesUC1DTitleX.push_back("p_{T} #Sigma #vec{#gamma}  [GeV]");
	histoTypesUC1DTitleX.push_back("p_{T} #Sigma #vec{Jets}  [GeV]");
	histoTypesUC1DTitleX.push_back("U_{T}  [GeV]");
	histoTypesUC1DTitleX.push_back("Correction C_{Gen}=#frac{U_{gen}}{U_{meas,raw}}");
	histoTypesUC1DTitleX.push_back("#Delta_{Gen}=U_{gen}-U_{meas,raw}");
	histoTypesUC1DTitleX.push_back("p_{T} #Sigma #vec{U}  [GeV]");

	vector < string > histoTypesUC1DMET;
	histoTypesUC1DMET.push_back("rawCaloMetElectrons");
	histoTypesUC1DMET.push_back("typeICaloMetElectrons");
	//	histoTypesUC1DMET.push_back("rawCaloMetPhotons");
	//		histoTypesUC1DMET.push_back("typeICaloMetPhotons");

	vector < string > histoTypesUC1DElectrons;
	//histoTypesUC1DElectrons.push_back("sumElectronsGen");
	histoTypesUC1DElectrons.push_back("sumElectronsMeasured");

	vector < string > histoTypesUC1DPhotons;
	histoTypesUC1DPhotons.push_back("sumPhotonsGen");
	histoTypesUC1DPhotons.push_back("sumPhotonsMeasured");

	vector < string > histoTypesUC1DJets;
	histoTypesUC1DJets.push_back("sumGenParticles");
	histoTypesUC1DJets.push_back("sumGenJets");
	histoTypesUC1DJets.push_back("sumRawJets");
	histoTypesUC1DJets.push_back("sumTypeIJets");
	if (debug)
		cout << "H2" << endl;
	vector < string > histoTypesUC1DUnclustered;
	histoTypesUC1DUnclustered.push_back("uMeasRaw");
	//histoTypesUC1DUnclustered.push_back("uMeasTrue");
	//histoTypesUC1DUnclustered.push_back("uMeasGen");
	//histoTypesUC1DUnclustered.push_back("uMeasCorr");
	//histoTypesUC1DUnclustered.push_back("uMeasTrueNoMet");
	//histoTypesUC1DUnclustered.push_back("uMeasGenNoMet");

	vector < string > histoTypesUC1DUnclusteredCorr;
	histoTypesUC1DUnclusteredCorr.push_back("uMeasRaw");
	//histoTypesUC1DUnclusteredCorr.push_back("uMeasTrue");
	//histoTypesUC1DUnclusteredCorr.push_back("uMeasGen");
	//histoTypesUC1DUnclusteredCorr.push_back("uMeasCorr");

	vector < string > histoTypesUC1DUnclusteredCorrFactor;
	histoTypesUC1DUnclusteredCorrFactor.push_back("corrFactorGen");

	vector < string > histoTypesUC1DUnclusteredCorrDelta;
	histoTypesUC1DUnclusteredCorrDelta.push_back("corrDeltaGen");

	vector < string > histoTypesUC1DMETTitle;
	histoTypesUC1DMETTitle.push_back("#slash{E}_{T,raw}+p_{T} #Sigma #vec{e_{meas}}");
	histoTypesUC1DMETTitle.push_back("#slash{E}_{T,TypeI}+p_{T} #Sigma #vec{e_{meas}}");
	histoTypesUC1DMETTitle.push_back("#slash{E}_{T,raw}+p_{T} #Sigma #vec{#gamma_{meas}}");
	histoTypesUC1DMETTitle.push_back("#slash{E}_{T,TypeI}+p_{T} #Sigma #vec{#gamma_{meas}}");

	vector < string > histoTypesUC1DElectronsTitle;
	//histoTypesUC1DElectronsTitle.push_back("p_{T} #Sigma #vec{e_{gen}}");
	histoTypesUC1DElectronsTitle.push_back("p_{T} #Sigma #vec{e_{meas}}");

	vector < string > histoTypesUC1DPhotonsTitle;
	histoTypesUC1DPhotonsTitle.push_back("p_{T} #Sigma #vec{#gamma_{gen}}");
	histoTypesUC1DPhotonsTitle.push_back("p_{T} #Sigma #vec{#gamma_{meas}}");

	vector < string > histoTypesUC1DJetsTitle;
	histoTypesUC1DJetsTitle.push_back("p_{T} #Sigma #vec{GenParticles}");
	histoTypesUC1DJetsTitle.push_back("p_{T} #Sigma #vec{Jets_{gen}}");
	histoTypesUC1DJetsTitle.push_back("p_{T} #Sigma #vec{Jets_{raw}}");
	histoTypesUC1DJetsTitle.push_back("p_{T} #Sigma #vec{Jets_{L2L3}}");

	vector < string > histoTypesUC1DUnclusteredTitle;
	histoTypesUC1DUnclusteredTitle.push_back("U_{T}");
//	histoTypesUC1DUnclusteredTitle.push_back("p_{T} #vec{u_{meas,L2L3}}");
//	histoTypesUC1DUnclusteredTitle.push_back("p_{T} #vec{u_{gen}}");
//	histoTypesUC1DUnclusteredTitle.push_back("p_{T} #vec{u_{corr}}");
//	histoTypesUC1DUnclusteredTitle.push_back("p_{T} #vec{u_{meas,L2L3,no met}}");
//	histoTypesUC1DUnclusteredTitle.push_back("p_{T} #vec{u_{gen,no met}}");
	vector < string > histoTypesUC1DUnclusteredTitleCorr;
	histoTypesUC1DUnclusteredTitleCorr.push_back("U_{T}");
//	histoTypesUC1DUnclusteredTitleCorr.push_back("p_{T} #vec{u_{meas,L2L3}}");
//	histoTypesUC1DUnclusteredTitleCorr.push_back("p_{T} #vec{u_{gen}}");
//	histoTypesUC1DUnclusteredTitleCorr.push_back("p_{T} #vec{u_{corr}}");
//	histoTypesUC1DUnclusteredTitleCorr.push_back("p_{T} #vec{u_{meas,L2L3,no met}}");
//	histoTypesUC1DUnclusteredTitleCorr.push_back("p_{T} #vec{u_{gen,no met}}");

	vector < string > histoTypesUC1DUnclusteredCorrFactorTitle;
	histoTypesUC1DUnclusteredCorrFactorTitle.push_back(
														"Correction C_{Gen}=#frac{U_{gen}}{U_{meas,raw}}");

	vector < string > histoTypesUC1DUnclusteredCorrDeltaTitle;
	histoTypesUC1DUnclusteredCorrDeltaTitle.push_back("#Delta_{Gen}=U_{gen}-U_{meas,raw}");

	if (doUCenergyPlots) {
		if (debug)
			cout << "doUCEnergyPlots" << endl;
		vector < vector<string> > histoTypesUC1D;
		histoTypesUC1D.push_back(histoTypesUC1DMET);
		histoTypesUC1D.push_back(histoTypesUC1DElectrons);
		histoTypesUC1D.push_back(histoTypesUC1DPhotons);
		histoTypesUC1D.push_back(histoTypesUC1DJets);
		histoTypesUC1D.push_back(histoTypesUC1DUnclustered);
		histoTypesUC1D.push_back(histoTypesUC1DUnclusteredCorrFactor);
		//histoTypesUC1D.push_back(histoTypesUC1DUnclusteredCorr);


		vector < string > histoTypesUC1DTitleHisto;
		histoTypesUC1DTitleHisto.push_back("MET");
		histoTypesUC1DTitleHisto.push_back("Electrons");
		histoTypesUC1DTitleHisto.push_back("Photons");
		histoTypesUC1DTitleHisto.push_back("Jets");
		histoTypesUC1DTitleHisto.push_back("UnclusteredEnergy");
		histoTypesUC1DTitleHisto.push_back("CorrectionDelta");
		histoTypesUC1DTitleHisto.push_back("Correction");
		histoTypesUC1DTitleHisto.push_back("UnclusteredEnergyCorr");

		vector < vector<string> > histoTypesUC1DTitle;
		histoTypesUC1DTitle.push_back(histoTypesUC1DMETTitle);
		histoTypesUC1DTitle.push_back(histoTypesUC1DElectronsTitle);
		histoTypesUC1DTitle.push_back(histoTypesUC1DPhotonsTitle);
		histoTypesUC1DTitle.push_back(histoTypesUC1DJetsTitle);
		histoTypesUC1DTitle.push_back(histoTypesUC1DUnclusteredTitle);
		histoTypesUC1DTitle.push_back(histoTypesUC1DUnclusteredCorrDeltaTitle);
		histoTypesUC1DTitle.push_back(histoTypesUC1DUnclusteredCorrFactorTitle);
		histoTypesUC1DTitle.push_back(histoTypesUC1DUnclusteredTitleCorr);

		///////////////////////////////////////////////////
		///////////////start histogram processing
		///////////////////////////////////////////////////

		if (!isOnlyMC) {
			cout << "============DRAW noVertices" << endl;
			string canvasname = "noVertices";

			TCanvas * c = new TCanvas(canvasname.c_str(), canvasname.c_str());
			trash->Add(c);
			TLegend *legend = new TLegend(0.659, 0.586, 0.923, 0.919, "");
			trash->Add(legend);
			legend->SetFillColor(0);
			string histoname = "noVertices_";

			TH1F * histo = (TH1F*) file->FindObjectAny(histoname.c_str());
			TH1F * histoMC = (TH1F*) fileMC->FindObjectAny(histoname.c_str());
			if (histo == 0) {
				cout << "noVertices Histo in data NOT found!" << endl;
			} else if (histoMC == 0) {
				cout << "noVertices Histo in MC NOT found!" << endl;
			} else {
				histoMC->SetLineColor(2);
				histoMC->GetXaxis()->SetTitle("#primary Vertices");
				histo->GetXaxis()->SetTitle("#primary Vertices");
				histoMC->GetYaxis()->SetTitle("fraction of events");
				histo->GetYaxis()->SetTitle("fraction of events");
				histo->Scale(1 / histo->Integral());
				histoMC->Scale(1 / histoMC->Integral());

				histo->Draw();
				histoMC->Draw("same");
				legend->AddEntry(histoMC, "MC", "l");
				legend->AddEntry(histo, "Data", "l");
				legend->Draw("same");
				cmsPrel(lumi, 1, true, true);
				output->WriteTObject(c, 0, "overwrite");

				string canvasnameCorr = "PUScaleForMC";
				TCanvas * cCorr = new TCanvas(canvasnameCorr.c_str(), canvasnameCorr.c_str());
				trash->Add(cCorr);
				TH1F * histoMCCorr = new TH1F("scalePUForMC", "scalePUForMC", 15, 0, 15);
				histoMCCorr->GetXaxis()->SetTitle("#primary Vertices");
				histoMCCorr->GetYaxis()->SetTitle("PU Weight for MC");
				for (int bin = 0; bin <= histoMC->GetNbinsX(); bin++) {
					if (histoMC->GetBinContent(bin) != 0) {
						double scale = histo->GetBinContent(bin) / histoMC->GetBinContent(bin);
						histoMCCorr->SetBinContent(bin, scale);
						int xAxis = bin - 1;
						if (true) {
							cout << "if(*noGoodVertices==" << xAxis << "){" << endl;
							cout << "weightPU=" << scale << ";" << endl;
							cout << "}" << endl;
						}
					}
				}
				histoMCCorr->Draw();
				output->WriteTObject(cCorr, 0, "overwrite");
			}

		}
		//add quark/gluon fraction plot of leading jets, of course only from MC...
		if (true) {
			//1JetTypeI_noGluonJets
			//1JetTypeI_noQuarkJets
			gROOT->ForceStyle(1);
			gStyle->SetErrorX(0);
			gStyle->SetEndErrorSize(0);
			gStyle->SetPadGridX(1);
			gStyle->SetPadGridY(1);
			//if(debug)cout<<"Error X:"<<gStyle->GetErrorX()<<endl;
			gStyle->UseCurrentStyle();

			cout << "============DRAW quarkfraction" << endl;
			string canvasname = "quarkfractionMC";

			TCanvas * c = new TCanvas(canvasname.c_str(), canvasname.c_str());
			trash->Add(c);
			TLegend *legend = new TLegend(0.1984, 0.7587, 0.4296, 0.9108, "");
			trash->Add(legend);
			legend->SetFillColor(0);
			string histonameGluon = "1JetTypeI_noGluonJets";
			string histonameQuark = "1JetTypeI_noQuarkJets";
			TH1F * histoMCQuark = (TH1F*) fileMC->FindObjectAny(histonameQuark.c_str());
			TH1F * histoMCGluon = (TH1F*) fileMC->FindObjectAny(histonameGluon.c_str());

			if (histoMCQuark == 0) {
				cout << "1JetTypeI_noQuarkJets NOT found!" << endl;
			} else if (histoMCGluon == 0) {
				cout << "1JetTypeI_noGluonJets NOT found!" << endl;
			} else {
				histoMCQuark->Sumw2();
				histoMCGluon->Sumw2();
				TH1F * histoMCQuarkFrac = (TH1F*) histoMCQuark->Clone();
				TH1F * histoMCGluonFrac = (TH1F*) histoMCGluon->Clone();
				TH1F * histoSum = (TH1F*) histoMCGluon->Clone();
				histoSum->Add((TH1F*) histoMCQuark->Clone());
				//				histoSum->Sumw2();
				//				histoMCQuarkFrac->Sumw2();
				//				histoMCGluonFrac->Sumw2();

				histoMCQuarkFrac->SetLineColor(2);
				histoMCGluonFrac->SetLineColor(4);
				histoMCQuarkFrac->SetMarkerColor(2);
				histoMCGluonFrac->SetMarkerColor(4);
				histoMCQuarkFrac->SetMarkerStyle(20);
				histoMCGluonFrac->SetMarkerStyle(21);
				histoMCQuarkFrac->SetMarkerSize(2);
				histoMCGluonFrac->SetMarkerSize(2);
				histoMCQuarkFrac->GetXaxis()->SetTitle("q_{T} [GeV]");
				histoMCGluonFrac->GetXaxis()->SetTitle("q_{T} [GeV]");
				histoMCQuarkFrac->GetYaxis()->SetTitle("Jet fraction");
				histoMCGluonFrac->GetYaxis()->SetTitle("Jet fraction");
				//				for (int bin = 0; bin <= histoMCQuarkFrac->GetNbinsX(); bin++) {
				//					if (histoSum->GetBinContent(bin) != 0 && histoMCQuarkFrac->GetBinContent(bin)!=0) {
				//						double relError1=histoMCQuarkFrac->GetBinError(bin)/histoMCQuarkFrac->GetBinContent(bin);
				//						double relError2=histoSum->GetBinError(bin)/histoSum->GetBinContent(bin);
				//						double newBinContent = histoMCQuarkFrac->GetBinContent(bin)
				//								/ histoSum->GetBinContent(bin);
				//						double newBinError=newBinContent*(relError1+relError2);
				//						histoMCQuarkFrac->SetBinContent(bin,newBinContent);
				//						histoMCQuarkFrac->SetBinError(bin,newBinError);
				//					}
				//					else{
				//						histoMCQuarkFrac->SetBinContent(bin,0);
				//												histoMCQuarkFrac->SetBinError(bin,0);
				//					}
				//				}
				//				for (int bin = 0; bin <= histoMCGluonFrac->GetNbinsX(); bin++) {
				//					if (histoSum->GetBinContent(bin) != 0 && histoMCGluonFrac->GetBinContent(bin)!=0) {
				//						double relError1 = histoMCGluonFrac->GetBinError(bin)
				//								/ histoMCGluonFrac->GetBinContent(bin);
				//						double relError2 = histoSum->GetBinError(bin)
				//								/ histoSum->GetBinContent(bin);
				//						cout<<"===bin:"<<bin<<endl;
				//						cout<<"rel error1:"<<relError1<<endl;
				//						cout<<"rel error2:"<<relError2<<endl;
				//						double newBinContent = histoMCGluonFrac->GetBinContent(
				//								bin) / histoSum->GetBinContent(bin);
				//						double newBinError = newBinContent * (relError1
				//								+ relError2);
				//						cout<<"bin error:"<<relError2<<endl;
				//						cout<<"bin value:"<<newBinContent<<endl;
				//						histoMCGluonFrac->SetBinContent(bin,newBinContent);
				//						histoMCGluonFrac->SetBinError(bin,newBinError);
				//					}
				//					else{
				//						histoMCGluonFrac->SetBinContent(bin,0);
				//						histoMCGluonFrac->SetBinError(bin,0);
				//										}
				//				}
				histoMCQuarkFrac->Divide(histoMCQuarkFrac, histoSum, 1, 1, "B");
				histoMCGluonFrac->Divide(histoMCGluonFrac, histoSum, 1, 1, "B");

				histoMCQuarkFrac->GetXaxis()->SetRangeUser(0, 80);
				histoMCGluonFrac->GetXaxis()->SetRangeUser(0, 80);
				histoMCQuarkFrac->GetYaxis()->SetRangeUser(0, 1);
				histoMCGluonFrac->GetYaxis()->SetRangeUser(0, 1);

				histoMCQuarkFrac->Draw("E X0");
				histoMCGluonFrac->Draw("same E X0");
				legend->AddEntry(histoMCQuarkFrac, "quark-jet", "p");
				legend->AddEntry(histoMCGluonFrac, "gluon-jet", "p");
				legend->Draw("same");
				//cmsPrel(lumi, 1, false, true);
				output->WriteTObject(c, 0, "overwrite");

			}
			cout << "============DRAW quarkfraction vs GenJetPt" << endl;
			string canvasnameGJ = "quarkfractionMCGJ";

			TCanvas * cGJ = new TCanvas(canvasnameGJ.c_str(), canvasnameGJ.c_str());
			trash->Add(cGJ);
			TLegend *legendGJ = new TLegend(0.1984, 0.7587, 0.4296, 0.9108, "");
			trash->Add(legendGJ);
			legendGJ->SetFillColor(0);
			string histonameGluonGJ = "1JetTypeI_noGluonJetsVsGenJetPt";
			string histonameQuarkGJ = "1JetTypeI_noQuarkJetsVsGenJetPt";
			TH1F * histoMCQuarkGJ = (TH1F*) fileMC->FindObjectAny(histonameQuarkGJ.c_str());
			TH1F * histoMCGluonGJ = (TH1F*) fileMC->FindObjectAny(histonameGluonGJ.c_str());

			if (histoMCQuarkGJ == 0) {
				cout << "1JetTypeI_noQuarkJetsGJ NOT found!" << endl;
			} else if (histoMCGluonGJ == 0) {
				cout << "1JetTypeI_noGluonJetsGJ NOT found!" << endl;
			} else {
				histoMCQuarkGJ->Sumw2();
				histoMCGluonGJ->Sumw2();
				TH1F * histoMCQuarkFracGJ = (TH1F*) histoMCQuarkGJ->Clone();
				TH1F * histoMCGluonFracGJ = (TH1F*) histoMCGluonGJ->Clone();
				TH1F * histoSumGJ = (TH1F*) histoMCGluonGJ->Clone();
				histoSumGJ->Add((TH1F*) histoMCQuarkGJ->Clone());
				//				histoSum->Sumw2();
				//				histoMCQuarkFrac->Sumw2();
				//				histoMCGluonFrac->Sumw2();

				histoMCQuarkFracGJ->SetLineColor(2);
				histoMCGluonFracGJ->SetLineColor(4);
				histoMCQuarkFracGJ->SetMarkerColor(2);
				histoMCGluonFracGJ->SetMarkerColor(4);
				histoMCQuarkFracGJ->SetMarkerStyle(20);
				histoMCGluonFracGJ->SetMarkerStyle(21);
				histoMCQuarkFracGJ->SetMarkerSize(2);
				histoMCGluonFracGJ->SetMarkerSize(2);
				histoMCQuarkFracGJ->GetXaxis()->SetTitle("q_{T} [GeV]");
				histoMCGluonFracGJ->GetXaxis()->SetTitle("q_{T} [GeV]");
				histoMCQuarkFracGJ->GetYaxis()->SetTitle("Jet fraction");
				histoMCGluonFracGJ->GetYaxis()->SetTitle("Jet fraction");

				histoMCQuarkFracGJ->Divide(histoMCQuarkFracGJ, histoSumGJ, 1, 1, "B");
				histoMCGluonFracGJ->Divide(histoMCGluonFracGJ, histoSumGJ, 1, 1, "B");

				histoMCQuarkFracGJ->GetXaxis()->SetRangeUser(0, 80);
				histoMCGluonFracGJ->GetXaxis()->SetRangeUser(0, 80);
				histoMCQuarkFracGJ->GetYaxis()->SetRangeUser(0, 1);
				histoMCGluonFracGJ->GetYaxis()->SetRangeUser(0, 1);

				histoMCQuarkFracGJ->Draw("E X0");
				histoMCGluonFracGJ->Draw("same E X0");
				legendGJ->AddEntry(histoMCQuarkFracGJ, "quark-jet", "p");
				legendGJ->AddEntry(histoMCGluonFracGJ, "gluon-jet", "p");
				legendGJ->Draw("same");
				//cmsPrel(lumi, 1, false, true);
				output->WriteTObject(cGJ, 0, "overwrite");
			}
		}
		gStyle->SetPadGridX(0);
		gStyle->SetPadGridY(0);
		cout << "============DRAW Sigma and Mean UCGen vs UCMeas" << endl;
		for (int j = 0; j < (int) jetSelectionNames.size(); ++j) {
			for (int h = 0; h < (int) histoTypesProjUGen.size(); ++h) {
				for (int u = 0; u < (int) utypeNames.size(); ++u) {
					string canvasname = "UC_Sigma_" + utypeNames[u] + jetSelectionNames[j] + "_"
						+ histoTypesProjUGen[h];

					TCanvas * c = new TCanvas(canvasname.c_str(), canvasname.c_str());
					trash->Add(c);
					TLegend *legend = new TLegend(0.659, 0.586, 0.923, 0.919, "");
					trash->Add(legend);
					legend->SetFillColor(0);

					string histoname = histoTypesProjUGen_prefix[h] + "" + utypeNames[u]
						+ jetSelectionNames[j] + "" + histoTypesProjUGen[h] + "_2";
					if (debug)
						cout << "read Histo Name:" << histoname << endl;
					TH1F * histo = (TH1F*) fileProfiles->FindObjectAny(histoname.c_str());
					bool isData = !isOnlyMC;
					bool isMC = true;
					if (histo == 0) {
						isData = false;
						if (debug)
							cout << "histo NOT found!" << histoname << endl;
						histo = (TH1F*) fileProfilesMC->FindObjectAny(histoname.c_str());
						if (histo == 0)
							if (debug)
								cout << "histo auch im MC NOT found!" << histoname << endl;
					}
					if (histo != 0) {
						//removeBadPoints(histo);
						if (utypeNames[u] == "paraBisectSum_" || utypeNames[u]
							== "paraBisectSumPF_") {
							invertHistoXAxis(histo);
							cout << "bin content bin 60" << histo->GetBinContent(60) << endl;
						}
						string ytitle = "#sigma (" + histoTypesProjUGenTitleY[h] + " )";
						histo->GetYaxis()->SetTitle(ytitle.c_str());
						histo->GetYaxis()->SetRangeUser(0, maxYSigmaPlotsUC);
						histo->GetXaxis()->SetRangeUser(minXSigmaPlotsUC, maxXSigmaPlotsUC);
						histo->GetXaxis()->SetTitle(histoTypesProjUGenTitleX[h].c_str());
						histo->SetTitle((jetSelectionTitles[j]).c_str());
						histo->Draw();
						cmsPrel(lumi, 0, isData, isMC);
						output->WriteTObject(c, 0, "overwrite");
					}

					string canvasnameMean = "UC_Mean_" + utypeNames[u] + jetSelectionNames[j] + "_"
						+ histoTypesProjUGen[h];
					TCanvas * cMean = new TCanvas(canvasnameMean.c_str(), canvasnameMean.c_str());
					trash->Add(cMean);
					string histonameMean = histoTypesProjUGen_prefix[h] + "" + utypeNames[u]
						+ jetSelectionNames[j] + "" + histoTypesProjUGen[h] + "_1";
					if (debug)
						cout << "read Histo Name:" << histonameMean << endl;
					TH1F * histoMean = (TH1F*) fileProfiles->FindObjectAny(histonameMean.c_str());
					isData = !isOnlyMC;
					isMC = true;
					if (histoMean == 0) {
						isData = false;
						if (debug)
							cout << "histo not found!" << histonameMean << endl;
						histoMean = (TH1F*) fileProfilesMC->FindObjectAny(histonameMean.c_str());
						if (histoMean == 0) {
							if (debug)
								cout << "histo MC not found!" << histonameMean << endl;
						}
					}
					if (histoMean != 0) {
						//removeBadPoints(histoMean);
						if (utypeNames[u] == "paraBisectSum_" || utypeNames[u]
							== "paraBisectSumPF_") {
							invertHistoXAxis(histoMean);
							cout << "bin content bin 60" << histoMean->GetBinContent(60) << endl;
						}
						cMean->Update();
						string ytitleMean = "<" + histoTypesProjUGenTitleY[h] + " >";
						histoMean->GetYaxis()->SetTitle(ytitleMean.c_str());
						histoMean->GetYaxis()->SetRangeUser(histoTypesProjUGen_lowEdgeY[h],
															histoTypesProjUGen_highEdgeY[h]);
						histoMean->GetXaxis()->SetRangeUser(minXSigmaPlotsUC, maxXSigmaPlotsUC);
						histoMean->GetXaxis()->SetTitle(histoTypesProjUGenTitleX[h].c_str());
						histoMean->SetTitle((jetSelectionTitles[j]).c_str());
						cout << "bin content bin 60" << histoMean->GetBinContent(60) << endl;
						histoMean->Draw();
						cmsPrel(lumi, 0, isData, isMC);
						cout << "write histo mean:" << cMean->GetName() << endl;
						output->WriteTObject(cMean, 0, "overwrite");
					}
				}
			}
		}
		cout << "============DRAW 2D Histos UC ProjUGen" << endl;
		debug = true;
		//2D Histo Projections
		for (int j = 0; j < (int) jetSelectionNames.size(); ++j) {
			for (int h = 0; h < (int) histoTypesProjUGen.size(); ++h) {
				for (int u = 0; u < (int) utypeNames.size(); ++u) {
					if (debug)
						cout << "draw LEGO ProjUGen:" << histoTypesProjUGen_prefix[h] + ""
							+ utypeNames[u] + jetSelectionNames[j] << histoTypesProjUGen[h] << endl;
					string canvasname = "2D_" + utypeNames[u] + jetSelectionNames[j] + "_"
						+ histoTypesProjUGen[h];
					TCanvas * c2D = new TCanvas(canvasname.c_str(), canvasname.c_str());
					trash->Add(c2D);
					string histoname = histoTypesProjUGen_prefix[h] + "" + utypeNames[u]
						+ jetSelectionNames[j] + histoTypesProjUGen[h];
					TH2F * histo2D = (TH2F*) file->FindObjectAny(histoname.c_str());
					if (histo2D == 0) {
						if (debug)
							cout << "histo NOT found!" << histoname << endl;
						histo2D = (TH2F*) fileMC->FindObjectAny(histoname.c_str());
						if (histo2D == 0)
							if (debug)
								cout << "histo NOT found!" << histoname << endl;
					}
					if (histo2D != 0) {
						string histoTitle = jetSelectionTitles[j] + " ";
						histo2D->SetTitle(histoTitle.c_str());
						histo2D->GetXaxis()->SetTitle((histoTypesProjUGenTitleX[h]).c_str());
						histo2D->GetYaxis()->SetTitle((histoTypesProjUGenTitleY[h]).c_str());
						histo2D->GetXaxis()->SetRangeUser(0, maxXSigmaPlotsUC);
						gStyle->SetOptTitle(0);
						histo2D->SetFillStyle(0);
						histo2D->Draw("BOX");
						gStyle->SetOptTitle(0);
						cmsPrel(lumi);
						output->WriteTObject(c2D, 0, "overwrite");

					}

				}
			}
		}
		if (false) {
			cout << "============DRAW Correlation Histos 2D UC" << endl;
			for (int j = 0; j < (int) jetSelectionNames.size(); ++j) {

				for (int h = 0; h < (int) histoTypesUC2D.size(); ++h) {
					for (int u = 0; u < (int) utypeNames.size(); ++u) {
						string canvasname = "2D_Corr_" + utypeNames[u] + jetSelectionNames[j] + "_"
							+ histoTypesUC2D[h];
						TCanvas * c2D = new TCanvas(canvasname.c_str(), canvasname.c_str());
						trash->Add(c2D);
						string histoname = "UC_" + utypeNames[u] + jetSelectionNames[j]
							+ histoTypesUC2D[h];
						TH2F * histo2D = (TH2F*) file->FindObjectAny(histoname.c_str());
						if (histo2D == 0) {
							if (debug)
								cout << "histo NOT found!" << histoname << endl;
						} else {
							string histoTitle = jetSelectionTitles[j] + " ";
							histo2D->SetTitle(histoTitle.c_str());
							histo2D->GetXaxis()->SetTitle((histoTypesUC2DTitleX[h]).c_str());
							histo2D->GetYaxis()->SetTitle((histoTypesUC2DTitleY[h]).c_str());
							histo2D->GetXaxis()->SetRangeUser(0, 100);
							gStyle->SetOptTitle(0);
							histo2D->SetFillStyle(0);
							histo2D->Draw("box");
							TProfile * prof = histo2D->ProfileX();
							prof->SetLineColor(2);
							prof->SetMarkerColor(2);
							prof->SetMarkerStyle(1);
							prof->GetYaxis()->SetTitle((histoTypesUC2DTitleY[h]).c_str());
							prof->Draw("same E");
						}
						gStyle->SetOptTitle(0);
						cmsPrel(lumi);
						output->WriteTObject(c2D, 0, "overwrite");

					}
				}
			}
		}
		cout << "============DRAW Sigma and Mean UCGen vs UCMeas  VSRAW" << endl;

		for (int j = 0; j < (int) jetSelectionNames.size(); ++j) {
			for (int h = 0; h < histoTypesProjUGenVSRAW.size(); ++h) {
				for (int u = 0; u < (int) utypeNames.size(); ++u) {

					//					string canvasname="UC_Sigma_"+utypeNames[u]
					//							+jetSelectionNames[j]+"_"
					//							+histoTypesProjUGenVSRAW[h];
					bool doFitOfCorrFunction = true;
					bool doFitOfCorrFunctionRel = false;
					if (histoTypesProjUGenVSRAW[h] == "corrDeltaGenVsGenRel_VSRAWG"
						|| histoTypesProjUGenVSRAW[h] == "corrDeltaTrueVsTrueRel_VSRAWG") {
						doFitOfCorrFunctionRel = true;
					}
					//					TCanvas * c=new TCanvas(canvasname.c_str(),canvasname.c_str());
					//					trash->Add(c);
					//					TLegend *legend = new TLegend(0.675879,0.786713,0.996231,0.996503,"");
					//					trash->Add(legend);
					//					legend->SetFillColor(0);
					//
					//					string histoname=histoTypesProjUGenVSRAW_prefix[h]+""
					//							+utypeNames[u] +jetSelectionNames[j]+""
					//							+histoTypesProjUGenVSRAW[h] +"_2";
					//					if(debug)cout<<"read Histo Name:"<<histoname<<endl;
					//					TH1F
					//							* histo=
					//									(TH1F*)fileProfiles->FindObjectAny(histoname.c_str());
					//					if (histo==0) {
					//						if(debug)cout<<"histo NOT found!"<<histoname<<endl;
					//						histo
					//								= (TH1F*)fileProfilesMC->FindObjectAny(histoname.c_str());
					//						if (histo==0)
					//							if(debug)cout<<"histo auch im MC NOT found!"<<histoname
					//									<<endl;
					//					}
					//					if (histo!=0) {
					//						//removeBadPoints(histo);
					//						string ytitle="#sigma ("
					//								+histoTypesProjUGenVSRAWTitleY[h] +" )";
					//						histo->GetYaxis()->SetTitle(ytitle.c_str());
					//						histo->GetYaxis()->SetRangeUser(0, maxYSigmaPlotsUC);
					//						histo->GetXaxis()->SetRangeUser(minXSigmaPlotsUC,
					//								maxXSigmaPlotsUC);
					//						histo->GetXaxis()->SetTitle(histoTypesProjUGenVSRAWTitleX[h].c_str());
					//						histo->SetTitle((jetSelectionTitles[j]).c_str());
					//						histo->Draw();
					//
					//						output->WriteTObject(c, 0, "overwrite");
					//					}

					string canvasnameMean = "UC_Mean_" + utypeNames[u] + jetSelectionNames[j] + "_"
						+ histoTypesProjUGenVSRAW[h];
					TCanvas * cMean = new TCanvas(canvasnameMean.c_str(), canvasnameMean.c_str());
					trash->Add(cMean);
					string histonameMean = histoTypesProjUGenVSRAW_prefix[h] + "" + utypeNames[u]
						+ jetSelectionNames[j] + "" + histoTypesProjUGenVSRAW[h] + "";
					if (debug)
						cout << "read Histo Name:" << histonameMean << endl;
					if (debug)
						cout << "slicesFile:" << fileSlices->GetName() << endl;
					//TODO

					TGraphErrors * grMean = 0;

					grMean = (TGraphErrors*) fileSlices->FindObjectAny(histonameMean.c_str());
					bool isData = !isOnlyMC;

					if (grMean == 0) {

							cout << "histo not found!" << histonameMean << endl;
						isData = false;
						//						grMean = (TGraphErrors*) fileSlicesMC->FindObjectAny(
						//								histonameMean.c_str());
						if (grMean == 0)
							//if (debug)
								cout << "graph auch im MC not found!" << histonameMean << endl;
					}
					if (grMean != 0) {
						cout<<"Draw Graph!"<<endl;
						//removeBadPoints(histoMean);
						grMean->Draw("ap");
						string ytitleMean = " <" + histoTypesProjUGenVSRAWTitleY[h] + " >";
						if (doFitOfCorrFunctionRel)
							ytitleMean = "" + histoTypesProjUGenVSRAWTitleY[h] + "";
						grMean->GetYaxis()->SetTitle(ytitleMean.c_str());
						grMean->GetYaxis()->SetRangeUser(0, 40);
						if (doFitOfCorrFunctionRel)

							//if (doLinearFit)histoMean->GetYaxis()->SetRangeUser(0, 100);
							grMean->GetXaxis()->SetRangeUser(minXSigmaPlotsUC, maxXSigmaPlotsUC);
						grMean->GetXaxis()->SetTitle(histoTypesProjUGenVSRAWTitleX[h].c_str());
						grMean->SetTitle((jetSelectionTitles[j]).c_str());

						if (doFitOfCorrFunctionRel) {
							grMean->GetYaxis()->SetRangeUser(0, 10);
							grMean->GetXaxis()->SetRangeUser(0, 40);

							bool isPF = false;
							if (HistoDrawUtil::containsSubstr(utypeNames[u], "PF")) {
								isPF = true;
								grMean->GetYaxis()->SetRangeUser(0, 8);
								grMean->GetXaxis()->SetRangeUser(0, 30);
								removeBadPointsGraph(grMean,isPF);
								//TODO hier plots cleanen!

							}else{
								removeBadPointsGraph(grMean,isPF);
							}
							///Add MC driven scale for data/MC
							TF1 *fitRel = 0;
							TF1 *fittedFuncRel = 0;
							TF1 *fittedFuncRelSummer10MC = 0;
							if (!isPF) {
								fitRel = new TF1("fitCorrRel", "[0]+[1]*exp(-[2]*x)", 0, 100);

								//histoMean->Fit("fitCorr", "R");
								fittedFuncRel = fitRel;//histoMean->GetFunction("fitCorr");
								fittedFuncRel->SetParameter(0, 2);
								fittedFuncRel->SetParameter(1, 1.3);
								fittedFuncRel->SetParameter(2, 0.1);

								fittedFuncRelSummer10MC = new TF1("fitCorrRel",
																	"[0]+[1]*exp(-[2]*x)", 0, 100);
								fittedFuncRelSummer10MC->SetParameter(0, 1.5);
								fittedFuncRelSummer10MC->SetParameter(1, 1.8);
								fittedFuncRelSummer10MC->SetParameter(2, 0.06);
							} else {
								fitRel = new TF1("fitCorrRel", "[0]+[1]*exp(-[2]*x)", 0, 100);
								fittedFuncRel = fitRel;
								if ((jetCutPt == "10")) {

									fittedFuncRel->SetParameter(0, 1.5);
								}
								if ((jetCutPt == "6")) {

									fittedFuncRel->SetParameter(0, 1.6);
								}

							}

							fittedFuncRel->SetLineWidth(2);

							fittedFuncRel->SetLineColor(4);

							if(!isData)fittedFuncRel->Draw("same");
							if (fittedFuncRelSummer10MC != 0 && !isData && false) {
								fittedFuncRelSummer10MC->Draw("same");
								fittedFuncRelSummer10MC->SetLineWidth(2);
								fittedFuncRelSummer10MC->SetLineColor(2);
							}
							TLatex l;
							l.SetTextAlign(12);
							l.SetTextSize(0.04);
							l.SetTextFont(62);
							l.SetTextColor(fittedFuncRel->GetLineColor());
							l.SetNDC();
							//l.DrawLatex(0.13, 0.83, "CMS 2010 Preliminary");
							if(!isData){
							l.DrawLatex(0.63, 0.85, "Sim.: ");
							if (!isPF) {

								l.DrawLatex(0.63, 0.8, "f(x)=A+B e^{-Cx/GeV}");
							} else {
								l.DrawLatex(0.63, 0.8, "f(x)=A");
							}
							string sA = "A=";
							sA = sA + Form("%.1f", fittedFuncRel->GetParameter(0)) //+ "#pm"
								+ " GeV";
							l.DrawLatex(0.63, 0.75, sA.c_str());
							if (!isPF) {
								//+Form("%.1f",
								//fittedFunc->GetParError(0))
								string sB = "B=";
								sB = sB + Form("%.1f", fittedFuncRel->GetParameter(1)) //+ "#pm"
									+ " GeV";
								string sC = "C=";
								sC = sC + Form("%.1f", fittedFuncRel->GetParameter(2)) //+ "#pm"
									+ " GeV";
								//		string sD = "D=";
								//		sD=sD+Form("%.3f", histoFit->GetParameter(3))+"#pm"+Form("%.3f",
								//				histoFit->GetParError(3))+ " GeV";
								l.DrawLatex(0.63, 0.7, sB.c_str());
								l.DrawLatex(0.63, 0.65, sC.c_str());

							}
						 }
							///add information for Summer10 MC
							if (fittedFuncRelSummer10MC != 0 && !isData && false) {
								TLatex l;
								l.SetTextAlign(12);
								l.SetTextSize(0.04);
								l.SetTextFont(62);
								l.SetTextColor(fittedFuncRelSummer10MC->GetLineColor());
								l.SetNDC();
								//l.DrawLatex(0.13, 0.83, "CMS 2010 Preliminary");

								l.DrawLatex(0.32, 0.9, "Sim. (Summer10): ");
								l.DrawLatex(0.32, 0.85, "f(x)=A+B e^{-Cx/GeV}");

								string sA = "A=";
								sA = sA + Form("%.1f", fittedFuncRelSummer10MC->GetParameter(0)) //+ "#pm"
									+ " GeV";
								l.DrawLatex(0.32, 0.8, sA.c_str());

								//+Form("%.1f",
								//fittedFunc->GetParError(0))
								string sB = "B=";
								sB = sB + Form("%.1f", fittedFuncRelSummer10MC->GetParameter(1)) //+ "#pm"
									+ " GeV";
								string sC = "C=";
								sC = sC + Form("%.1f", fittedFuncRelSummer10MC->GetParameter(2)) //+ "#pm"
									+ " GeV";
								//		string sD = "D=";
								//		sD=sD+Form("%.3f", histoFit->GetParameter(3))+"#pm"+Form("%.3f",
								//				histoFit->GetParError(3))+ " GeV";
								l.DrawLatex(0.32, 0.75, sB.c_str());
								l.DrawLatex(0.32, 0.7, sC.c_str());

							}
							///Add data driven scale for data only
							if (isData) {
								TF1 *fittedFuncRel = 0;
								if (!isPF) {
									fittedFuncRel = new TF1("fitCorrRel", "[0]+[1]*exp(-[2]*x)", 0,
															100);

									fittedFuncRel->SetParameter(0, 2.3);
									fittedFuncRel->SetParameter(1, 1.9);
									fittedFuncRel->SetParameter(2, 0.2);
								} else {
									fittedFuncRel = new TF1("fitCorrRel", "[0]", 0, 100);

									if ((jetCutPt == "50")) {
										fittedFuncRel->SetParameter(0, 1.2);
									}
									if ((jetCutPt == "10")) {

										fittedFuncRel->SetParameter(0, 1.4);
									}
									if ((jetCutPt == "6")) {

										fittedFuncRel->SetParameter(0, 1.6);
									}

								}

								fittedFuncRel->SetLineWidth(2);
								fittedFuncRel->SetLineColor(2);
								fittedFuncRel->Draw("same");

								TLatex l;
								l.SetTextAlign(12);
								l.SetTextSize(0.04);
								l.SetTextFont(62);
								l.SetTextColor(fittedFuncRel->GetLineColor());
								l.SetNDC();
								//l.DrawLatex(0.13, 0.83, "CMS 2010 Preliminary");
								l.DrawLatex(0.63, 0.85, "Data:");
								if (!isPF) {
									l.DrawLatex(0.63, 0.8, "f(x)=A+B e^{-Cx/GeV}");
								} else {
									l.DrawLatex(0.63, 0.8, "f(x)=A");
								}
								string sA = "A=";
								sA = sA + Form("%.1f", fittedFuncRel->GetParameter(0)) //+ "#pm"
									+ " GeV";
								l.DrawLatex(0.63, 0.75, sA.c_str());
								if (!isPF) {
									//+Form("%.1f",
									//fittedFunc->GetParError(0))
									string sB = "B=";
									sB = sB + Form("%.1f", fittedFuncRel->GetParameter(1)) //+ "#pm"
										+ " GeV";
									string sC = "C=";
									sC = sC + Form("%.1f", fittedFuncRel->GetParameter(2)) //+ "#pm"
										+ " GeV";
									//		string sD = "D=";
									//		sD=sD+Form("%.3f", histoFit->GetParameter(3))+"#pm"+Form("%.3f",
									//				histoFit->GetParError(3))+ " GeV";
									l.DrawLatex(0.63, 0.7, sB.c_str());
									l.DrawLatex(0.63, 0.65, sC.c_str());

								}
							}

						} else if (doFitOfCorrFunction) {
							if (histoTypesProjUGenVSRAW[h] == "ProjUMeasVsUgenPara_VSRAWG"
								|| histoTypesProjUGenVSRAW[h] == "ProjUMeasVsUtruePara_VSRAWG") {
								TF1 *fit = new TF1("fitCorr", "[0]+x", 0, 100);
								grMean->Fit("fitCorr", "R");
								TF1 *fittedFunc = (TF1 *) grMean->GetFunction("fitCorr");
								if (fittedFunc != 0) {
									fittedFunc->SetLineWidth(2);
									fittedFunc->SetLineColor(4);

									fittedFunc->Draw("same");

									TLatex l;
									l.SetTextAlign(12);
									l.SetTextSize(0.04);
									l.SetTextFont(62);
									l.SetTextColor(fittedFunc->GetLineColor());
									l.SetNDC();
									l.DrawLatex(0.7, 0.9, "f(x)=A + x");
									string sA = "A=";
									sA = sA + Form("%.1f", fittedFunc->GetParameter(0));
									l.DrawLatex(0.7, 0.8, sA.c_str());
								}
							} else {
								TF1 *fit =
									new TF1("fitCorr",
											"pow([0],2)+pow([1],2)*log(x)+pow(([2]*log(x)),2)", 0,
											100);

								//histoMean->Fit("fitCorr", "R");
								TF1 *fittedFunc = fit;//histoMean->GetFunction("fitCorr");

								//							if(debug)cout<<"=======parError Sqrt:" <<fit->GetParError(0)
								//									<<endl;

								//							fittedFunc->SetParameter(0, -1.3);
								//							fittedFunc->SetParameter(1, 1.6);
								//							fittedFunc->SetParameter(2, -1.1);

								//							fittedFunc->SetParameter(0, 1.8);
								//							fittedFunc->SetParameter(1, 0.7);
								//							fittedFunc->SetParameter(2, 1.4);

								//							fittedFunc->SetParameter(0,1.2);
								//							fittedFunc->SetParameter(1,2.1);
								//							fittedFunc->SetParameter(2,0.6);

								fittedFunc->SetParameter(0, 1.9);
								fittedFunc->SetParameter(1, 0.9);
								fittedFunc->SetParameter(2, 1.33);

								fittedFunc->SetLineWidth(2);
								fittedFunc->SetLineColor(4);

								fittedFunc->Draw("same");

								TLatex l;
								l.SetTextAlign(12);
								l.SetTextSize(0.04);
								l.SetTextFont(62);
								l.SetTextColor(fittedFunc->GetLineColor());
								l.SetNDC();
								//l.DrawLatex(0.13, 0.83, "CMS 2010 Preliminary");

								l.DrawLatex(0.7, 0.85, "f(x)=A^{2}+B^{2} log(x)+C^{2} log(x)^{2}");
								string sA = "A=";
								sA = sA + Form("%.1f", fittedFunc->GetParameter(0))
								//+ "#pm" + Form("%.1f",fittedFunc->GetParError(0)
									+ " GeV";
								string sB = "B=";
								sB = sB + Form("%.2f", fittedFunc->GetParameter(1))
								//									+ "#pm" + Form("%.2f",
									//									fittedFunc->GetParError(1)
									+ " GeV";
								string sC = "C=";
								sC = sC + Form("%.3f", fittedFunc->GetParameter(2))
								//									+ "#pm" + Form("%.3f",
									//									fittedFunc->GetParError(2)
									+ " GeV";
								//		string sD = "D=";
								//		sD=sD+Form("%.3f", histoFit->GetParameter(3))+"#pm"+Form("%.3f",
								//				histoFit->GetParError(3))+ " GeV";
								l.DrawLatex(0.7, 0.8, sA.c_str());
								l.DrawLatex(0.7, 0.75, sB.c_str());
								l.DrawLatex(0.7, 0.7, sC.c_str());
							}
						}
						//grMean->Draw("same");
						//histoMean->Draw("same");
						cMean->Update();
						cmsPrel(lumi, 0, isData, !isData);
						output->WriteTObject(cMean, 0, "overwrite");
					}
				}
			}
		}

		cout << "============DRAW Correlation Histos 2D UC for Correction Plots" << endl;
		for (int j = 0; j < (int) jetSelectionNames.size(); ++j) {
			for (int h = 0; h < histoTypesProjUGenVSRAW.size(); ++h) {
				for (int u = 0; u < (int) utypeNames.size(); ++u) {
					if (debug)
						cout << "draw LEGO ProjUGen CORR VS RAW:"
							<< histoTypesProjUGenVSRAW_prefix[h] + "" + utypeNames[u]
								+ jetSelectionNames[j] << histoTypesProjUGenVSRAW[h] << endl;
					string canvasname = "2D_" + utypeNames[u] + jetSelectionNames[j] + "_"
						+ histoTypesProjUGenVSRAW[h];
					TCanvas * c2D = new TCanvas(canvasname.c_str(), canvasname.c_str());
					trash->Add(c2D);
					string histoname = histoTypesProjUGenVSRAW_prefix[h] + "" + utypeNames[u]
						+ jetSelectionNames[j] + histoTypesProjUGenVSRAW[h];
					TH2F * histo2D = (TH2F*) fileProfiles->FindObjectAny(histoname.c_str());
					if (histo2D == 0) {
						if (debug)
							cout << "histo NOT found!" << histoname << endl;

						histo2D = (TH2F*) fileProfilesMC->FindObjectAny(histoname.c_str());
						if (histo2D == 0) {
							if (debug)
								cout << "histo auch im MCNOT found!" << histoname << endl;
						}
					}
					if (histo2D != 0) {
						string histoTitle = jetSelectionTitles[j] + " ";
						histo2D->SetTitle(histoTitle.c_str());
						histo2D->GetXaxis()->SetTitle((histoTypesProjUGenVSRAWTitleX[h]).c_str());
						histo2D->GetYaxis()->SetTitle((histoTypesProjUGenVSRAWTitleY[h]).c_str());
						histo2D->GetXaxis()->SetRangeUser(minXSigmaPlotsUC, maxXSigmaPlotsUC);
						gStyle->SetOptTitle(0);
						histo2D->SetFillStyle(0);
						histo2D->Draw("BOX");
						gStyle->SetOptTitle(0);
						cmsPrel(lumi);
						output->WriteTObject(c2D, 0, "overwrite");

					}
				}
			}
		}

		gStyle->SetOptTitle(0);
		gStyle->SetOptLogy(1);
		cout << "============DRAW 1D UC" << endl;

		for (int j = 0; j < (int) jetSelectionNames.size(); ++j) {
			for (int th = 0; th < (int) histoTypesUC1D.size(); ++th) {
				for (int u = 0; u < (int) utypeNames.size(); ++u) {
					//only make 1D plots for default U and UPF
					//					if (u != 0 && u != 4)
					//						break;
					vector < string > histoTypes1DUC = histoTypesUC1D[th];
					vector < string > histoTypes1DTitles = histoTypesUC1DTitle[th];
					string canvasname = "1D_UC_" + utypeNames[u] + jetSelectionNames[j] + "_"
						+ histoTypesUC1DTitleHisto[th];

					TCanvas * c2DUC = new TCanvas(canvasname.c_str(), canvasname.c_str());
					trash->Add(c2DUC);
					TLegend *legend = new TLegend(0.659, 0.7, 0.923, 0.85, "");

					trash->Add(legend);
					legend->SetFillColor(0);
					TList * histos = new TList();
					trash->Add(histos);
					TList * histosMC = new TList();
					trash->Add(histosMC);
					for (int h = 0; h < histoTypes1DUC.size(); ++h) {
						string histoname = "UC_" + utypeNames[u] + jetSelectionNames[j]
							+ histoTypes1DUC[h];
						TH1F * histo1DUC = (TH1F*) file->FindObjectAny(histoname.c_str());

						if (histo1DUC == 0)

							if (debug)
								cout << "histo not found:" << histo1DUC << endl;

						if (histo1DUC != 0) {
							histo1DUC->GetYaxis()->SetRangeUser(0.5, 1000*histo1DUC->GetBinContent(histo1DUC->GetMaximumStored()));
							string histoTitle = jetSelectionTitles[j] + " ";
							histo1DUC->SetTitle(histoTitle.c_str());
							double binwidthUC = histo1DUC->GetXaxis()->GetBinWidth(1);
							histo1DUC->GetYaxis()->SetTitle(("Number of Events /"
								+ HistoDrawUtil::getStringFromInt(binwidthUC) + " GeV").c_str());

							histo1DUC->GetXaxis()->SetTitle((histoTypesUC1DTitleX[th]).c_str());

							histo1DUC->SetMarkerStyle(dataMarkersUC[h]);
							histo1DUC->SetMarkerColor(dataColorsUC[h]);
							histo1DUC->SetLineColor(dataColorsUC[h]);
							histo1DUC->SetLineStyle(1);
							histo1DUC->SetFillStyle(0);

							string legTitle = "Data";//histoTypes1DTitles[h];
							if (histo1DUC->GetMean() > 0 && file != fileMC)
								legend->AddEntry(histo1DUC, legTitle.c_str(), "p");
							gStyle->SetOptTitle(0);
							if (debug)
								cout << "loadMC" << endl;
							if (fileMC != 0) {
								TH1F * histo1DUCMC =
									(TH1F*) fileMC->FindObjectAny(histoname.c_str());
								if (debug)
									cout << "read MC Histo Name:" << histoname << endl;
								if (histo1DUCMC != 0) {
									histo1DUCMC->GetYaxis()->SetTitle(
																		("Number of Events /"
																			+ HistoDrawUtil::getStringFromInt(
																												binwidthUC)
																			+ " GeV").c_str());
									histo1DUCMC->GetYaxis()->SetRangeUser(0.5, 1000*histo1DUCMC->GetBinContent(histo1DUCMC->GetMaximumStored()));
									if (debug)
										cout << "hier:" << th << endl;
									if (debug)
										cout << "histoTypesUC1DTitleX size:"
											<< histoTypesUC1DTitleX.size() << "  -  " << th << endl;
									histo1DUCMC->GetXaxis()->SetTitle(
																		(histoTypesUC1DTitleX[th]).c_str());

									if (debug)
										cout << "h:" << h << endl;
									if (debug)
										cout << dataMarkers.size() << " - " << endl;
									if (debug)
										cout << mcColorsUC.size() << " - " << endl;
									if (debug)
										cout << mcStyle.size() << " - " << endl;
									if (debug)
										cout << histoTypes1DTitles.size() << " - " << endl;
									histo1DUCMC->SetMarkerStyle(dataMarkers[h]);
									histo1DUCMC->SetMarkerColor(mcColorsUC[h]);
									histo1DUCMC->SetLineColor(1);
									histo1DUCMC->SetFillColor(mcColorsUC[h]);
									histo1DUCMC->SetFillStyle(mcStyle[h]);
									if (histo1DUCMC->Integral() != 0 && histo1DUC != 0) {
										if (histo1DUC->Integral() != 0) {
											double scale = histo1DUC->Integral()
												/ histo1DUCMC->Integral();
											histo1DUCMC->Scale(scale);
											//cout << "Scale MC:" << scale << endl;
										}
									}
									if (debug)
										cout << "add MC" << endl;
									histosMC->Add(histo1DUCMC);

									string legTitleMC = "Simulation";//"Sim " + histoTypes1DTitles[h];
									legend->AddEntry(histo1DUCMC, legTitleMC.c_str(), "l");
								}
								if (debug)
									cout << "end loadMC" << endl;
								if (histo1DUC->GetMean() > 0) {
									histos->Add(histo1DUC);

								}
							}
						}
					}
					if (debug)
						cout << "draw..." << endl;
					drawHistosToCanvas(histos, histosMC, histos==histosMC, 0,
						true, false, false,0,
						0, 0, 0,5000.0);

					legend->Draw("same");
					cmsPrel(lumi, 0, true, false);
					output->WriteTObject(c2DUC, 0, "overwrite");
				}
			}
		}
		cout << "1DUC done..." << endl;
	}
	gStyle->SetOptTitle(0);
	gStyle->SetOptLogy(0);
	/////////////////////////////////DRAW Sigma vs Plots ET vs HT
	if (!drawOnlySigmaAll) {
		cout << "============DRAW Sigma vs Plots ET/HT" << endl;
		for (int j = 0; j < (int) jetSelectionNames.size(); ++j) {
			for (int h = 0; h < histoTypes.size() && h < histoTypesMht.size(); ++h) {
				string canvasname = "SumETHTComp_" + jetSelectionNames[j] + "_" + histoTypes[h];
				TCanvas * c = new TCanvas(canvasname.c_str(), canvasname.c_str());
				trash->Add(c);
				TLegend *legend = new TLegend(0.659, 0.586, 0.923, 0.919, "");

				trash->Add(legend);
				legend->SetFillColor(0);
				TList * histos = new TList();
				trash->Add(histos);
				TList * histosMC = new TList();
				trash->Add(histosMC);
				for (int i = 1; i < (int) 2; ++i) {
					string histoname = jetSelectionNames[j] + histoTypes[h] + metHistoNames[i]
						+ "_2";
					if (debug)
						cout << "read Histo Name:" << histoname << endl;
					TH1F * histo = (TH1F*) fileProfiles->FindObjectAny(histoname.c_str());
					removeBadPoints(histo);
					string ytitle = "#sigma " + histoTypesTitle[h];
					histo->GetYaxis()->SetTitle(ytitle.c_str());
					histo->GetYaxis()->SetRangeUser(0, maxYSigmaPlots);
					histo->GetXaxis()->SetRangeUser(minXSigmaPlots, maxXSigmaPlots);
					histo->GetXaxis()->SetTitle("#Sigma E_{T}/H_{T} [GeV]");
					histo->SetMarkerStyle(dataMarkers[i]);
					histo->SetMarkerColor(dataColors[i]);
					histo->SetLineColor(dataColors[i]);

					histo->SetTitle((jetSelectionTitles[j]).c_str());
					histos->Add(histo);
					if (fileMC != 0) {
						TH1F * histoMC = (TH1F*) fileProfilesMC->FindObjectAny(histoname.c_str());
						if (debug)
							cout << "read MC Histo Name:" << histoname << endl;
						removeBadPoints(histoMC);
						if (debug)
							cout << "bad points removed" << endl;
						histoMC->SetTitle((jetSelectionTitles[j]).c_str());
						string ytitleMC = "#sigma " + histoTypesTitle[h];
						histoMC->GetYaxis()->SetTitle(ytitleMC.c_str());
						histoMC->GetYaxis()->SetRangeUser(0, maxYSigmaPlots);
						histoMC->GetXaxis()->SetRangeUser(minXSigmaPlots, maxXSigmaPlots);
						histo->GetXaxis()->SetTitle("#Sigma E_{T}/H_{T} [GeV]");
						histoMC->SetMarkerStyle(i + 2);
						histoMC->SetMarkerColor(mcColors[i]);
						histoMC->SetLineColor(mcLineColors[i]);
						histoMC->SetLineStyle(mcLineStyle[i]);
						histoMC->SetFillColor(mcColors[i]);
						histoMC->SetFillStyle(mcStyle[i]);
						histosMC->Add(histoMC);
						string legTitleMC = "#Sigma E_{T}: MC " + metHistoTitles[i];
						legend->AddEntry(histoMC, legTitleMC.c_str(), "l");
					}
					string legTitle = "#Sigma E_{T}: Data " + metHistoTitles[i];
					if (file != fileMC)
						legend->AddEntry(histo, legTitle.c_str(), "p");
					//Add MHT

					string histonameMHT = jetSelectionNames[j] + histoTypesMht[h]
						+ mhtHistoNames[i] + "_2";
					if (debug)
						cout << "read Histo Name:" << histonameMHT << endl;
					TH1F * histo_mht = (TH1F*) fileProfiles->FindObjectAny(histonameMHT.c_str());
					removeBadPoints(histo_mht);
					histo_mht->SetTitle((jetSelectionTitles[j]).c_str());
					string ytitlemht = "#sigma " + histoTypesTitle[h];
					histo_mht->GetYaxis()->SetTitle(ytitlemht.c_str());
					histo_mht->GetYaxis()->SetRangeUser(0, maxYSigmaPlots);
					histo_mht->GetXaxis()->SetRangeUser(minXSigmaPlots, maxXSigmaPlots);
					histo->GetXaxis()->SetTitle("#Sigma E_{T}/H_{T} [GeV]");
					if (histo_mht == 0)
						if (debug)
							cout << "HISTO not found" << endl;
					histo_mht->SetMarkerStyle(dataMarkers[i + 3]);
					histo_mht->SetLineColor(dataColors[i + 3]);
					histo_mht->SetMarkerColor(dataColors[i + 3]);
					histos->Add(histo_mht);

					if (fileMC != 0) {
						TH1F * histoMC_mht =
							(TH1F*) fileProfilesMC->FindObjectAny(histonameMHT.c_str());
						if (debug)
							cout << "read MC Histo Name:" << histonameMHT << endl;
						removeBadPoints(histoMC_mht);
						//					if (histoMC_mht->GetEntries()!=0) {
						//						histoMC_mht->Scale(histo_mht->GetEntries()
						//								/histoMC_mht->GetEntries());
						//					}

						histoMC_mht->SetMarkerStyle(mcColors[i + 3]);
						histoMC_mht->SetMarkerColor(mcColors[i + 3]);
						histoMC_mht->SetLineColor(mcLineColors[i + 3]);
						histoMC_mht->SetLineStyle(mcLineStyle[i]);
						histoMC_mht->SetFillColor(mcColors[i + 3]);
						histoMC_mht->SetFillStyle(mcStyle[i + 3]);
						string ytitleMCmht = "#sigma " + histoTypesTitle[h];
						histoMC_mht->GetYaxis()->SetTitle(ytitleMCmht.c_str());
						histoMC_mht->GetYaxis()->SetRangeUser(0, maxYSigmaPlots);
						histoMC_mht->GetXaxis()->SetRangeUser(minXSigmaPlots, maxXSigmaPlots);
						histoMC_mht->GetXaxis()->SetTitle("#Sigma E_{T}/H_{T} [GeV]");
						histosMC->Add(histoMC_mht);
						histoMC_mht->Draw("same  hist");
						string legTitleMC = "#Sigma H_{T}: MC " + mhtHistoTitles[i];
						legend->AddEntry(histoMC_mht, legTitleMC.c_str(), "l");
					}
					string legTitle2 = "#Sigma H_{T}: Data " + mhtHistoTitles[i];
					if (debug)
						cout << "leg Title:" << legTitle2 << endl;
					if (file != fileMC)
						legend->AddEntry(histo_mht, legTitle2.c_str(), "p");

				}
				drawHistosToCanvas(histos, histosMC, file == fileMC);

				legend->Draw("same");
				cmsPrel(lumi, 1);
				output->WriteTObject(c, 0, "overwrite");

			}

		}

		/////////////////////////////////DRAW Sigma vs Plots MC/Data for each metHist Corr/NoCorr
		cout << "============DRAW Sigma vs Plots MC/Data only one met type" << endl;
		for (int j = 0; j < (int) jetSelectionNames.size(); ++j) {
			for (int h = 0; h < histoTypes.size(); ++h) {

				for (int i = 0; i < (int) metHistoNames.size(); ++i) {
					string canvasname = jetSelectionNames[j] + "_" + histoTypes[h] + "_"
						+ metHistoNames[i] + "OnlyOne";
					TCanvas * c = new TCanvas(canvasname.c_str(), canvasname.c_str());
					trash->Add(c);
					TList * histos = new TList();
					trash->Add(histos);
					TList * histosMC = new TList();
					trash->Add(histosMC);
					TLegend *legend = new TLegend(0.659, 0.586, 0.923, 0.919, "");

					trash->Add(legend);
					legend->SetFillColor(0);
					string histoname = jetSelectionNames[j] + histoTypes[h] + metHistoNames[i]
						+ "_2";
					//if(debug)if(debug)cout<<"read Histo Name:"<<histoname<<endl;
					TH1F * histo = (TH1F*) fileProfiles->FindObjectAny(histoname.c_str());
					if (histo == 0)
						if (debug)
							cout << "histo not found:" << histoname << endl;
					removeBadPoints(histo);
					string ytitle = "#sigma " + histoTypesTitle[h];
					histo->GetYaxis()->SetTitle(ytitle.c_str());
					histo->GetYaxis()->SetRangeUser(0, maxYSigmaPlots);
					histo->GetXaxis()->SetRangeUser(minXSigmaPlots, maxXSigmaPlots);
					histo->SetMarkerStyle(dataMarkers[i]);
					histo->SetMarkerColor(dataColors[i]);
					histo->SetLineColor(dataColors[i]);
					if (debug)
						cout << "set histo to color:" << histo->GetLineColor() << endl;
					histo->SetTitle((jetSelectionTitles[j]).c_str());
					histos->Add(histo);
					//histo->Draw();

					if (fileMC != 0) {
						TH1F * histoMC = (TH1F*) fileProfilesMC->FindObjectAny(histoname.c_str());
						if (histoMC == 0)
							if (debug)
								cout << "histo not found:" << histoname << endl;
						removeBadPoints(histoMC);
						histoMC->SetTitle((jetSelectionTitles[j]).c_str());
						string ytitleMC = "#sigma " + histoTypesTitle[h];
						histoMC->GetYaxis()->SetTitle(ytitleMC.c_str());
						histoMC->GetYaxis()->SetRangeUser(0, maxYSigmaPlots);
						histoMC->GetXaxis()->SetRangeUser(minXSigmaPlots, maxXSigmaPlots);
						histoMC->SetMarkerStyle(i + 2);
						histoMC->SetMarkerColor(mcColors[i]);
						histoMC->SetLineColor(mcLineColors[i]);
						histoMC->SetLineStyle(mcLineStyle[i]);
						histoMC->SetFillColor(mcColors[i]);
						histoMC->SetFillStyle(mcStyle[i]);
						histosMC->Add(histoMC);
						//histoMC->Draw("same  hist");
						string legTitleMC = "Sim " + metHistoTitles[i];
						legend->AddEntry(histoMC, legTitleMC.c_str(), "l");
					}
					string legTitle = "Data " + metHistoTitles[i];
					if (file != fileMC)
						legend->AddEntry(histo, legTitle.c_str(), "p");
					drawHistosToCanvas(histos, histosMC, file == fileMC);
					legend->Draw("same");
					cmsPrel(lumi, 1);
					output->WriteTObject(c, 0, "overwrite");
				}

			}
			cout << "============DRAW Sigma vs Plots MC/Data only one mht type" << endl;
			for (int h = 0; h < histoTypesMht.size(); ++h) {

				for (int i = 0; i < (int) mhtHistoNames.size(); ++i) {
					string canvasname = jetSelectionNames[j] + "_" + histoTypesMht[h] + "_"
						+ mhtHistoNames[i] + "OnlyOne";
					TCanvas * c_mht = new TCanvas(canvasname.c_str(), canvasname.c_str());
					trash->Add(c_mht);
					TList * histos = new TList();
					trash->Add(histos);
					TList * histosMC = new TList();
					trash->Add(histosMC);
					TLegend *legend_mht = new TLegend(0.70, 0.70, 0.93, 0.91, "");
					trash->Add(legend_mht);
					legend_mht->SetFillColor(0);
					string histoname = jetSelectionNames[j] + histoTypesMht[h] + mhtHistoNames[i]
						+ "_2";
					if (debug)
						cout << "read Histo Name:" << histoname << endl;
					TH1F * histo_mht = (TH1F*) fileProfiles->FindObjectAny(histoname.c_str());
					removeBadPoints(histo_mht);
					histo_mht->SetTitle((jetSelectionTitles[j]).c_str());
					string ytitlemht = "#sigma " + histoTypesMhtTitle[h];
					histo_mht->GetYaxis()->SetTitle(ytitlemht.c_str());
					histo_mht->GetYaxis()->SetRangeUser(0, maxYSigmaPlots);
					histo_mht->GetXaxis()->SetRangeUser(minXSigmaPlots, maxXSigmaPlots);
					if (histo_mht == 0)
						if (debug)
							cout << "HISTO not found" << endl;
					histo_mht->SetMarkerStyle(dataMarkers[i]);
					histo_mht->SetLineColor(dataColors[i]);
					histo_mht->SetMarkerColor(dataColors[i]);
					histos->Add(histo_mht);
					//histo_mht->Draw("");

					if (fileMC != 0) {
						TH1F * histoMC_mht =
							(TH1F*) fileProfilesMC->FindObjectAny(histoname.c_str());
						removeBadPoints(histoMC_mht);
						histoMC_mht->SetMarkerStyle(dataMarkers[i]);
						histoMC_mht->SetMarkerColor(mcColors[i]);
						histoMC_mht->SetLineColor(mcLineColors[i]);
						histoMC_mht->SetLineStyle(mcLineStyle[i]);
						histoMC_mht->SetFillColor(mcColors[i]);
						histoMC_mht->SetFillStyle(mcStyle[i]);
						string ytitleMCmht = "#sigma " + histoTypesMhtTitle[h];
						histoMC_mht->GetYaxis()->SetTitle(ytitleMCmht.c_str());
						histoMC_mht->GetYaxis()->SetRangeUser(0, maxYSigmaPlots);
						histoMC_mht->GetXaxis()->SetRangeUser(minXSigmaPlots, maxXSigmaPlots);
						histosMC->Add(histoMC_mht);
						//histoMC_mht->Draw("same hist");
						string legTitleMC = "Sim " + mhtHistoTitles[i];
						legend_mht->AddEntry(histoMC_mht, legTitleMC.c_str(), "l");
					}
					string legTitle = "Data " + mhtHistoTitles[i];
					if (debug)
						cout << "leg Title:" << legTitle << endl;
					if (file != fileMC)
						legend_mht->AddEntry(histo_mht, legTitle.c_str(), "p");
					drawHistosToCanvas(histos, histosMC, file == fileMC);
					legend_mht->Draw("same");
					cmsPrel(lumi, 1);
					output->WriteTObject(c_mht, 0, "overwrite");
				}

			}
		}

		/////////////////////////////////DRAW Sigma vs Plots MC/MC and Data/Data
		cout << "============DRAW Sigma vs Plots MC/MC and Data/Data for MET" << endl;
		for (int j = 0; j < (int) jetSelectionNames.size(); ++j) {
			for (int h = 0; h < histoTypes.size(); ++h) {
				string canvasname = jetSelectionNames[j] + "_" + histoTypes[h] + "_OnlyMC";
				TCanvas * c = new TCanvas(canvasname.c_str(), canvasname.c_str());
				trash->Add(c);
				TList * histos = new TList();
				trash->Add(histos);
				TList * histosMC = new TList();
				trash->Add(histosMC);
				TLegend *legend = new TLegend(0.659, 0.586, 0.923, 0.919, "");

				trash->Add(legend);
				legend->SetFillColor(0);
				for (int i = 0; i < (int) metHistoNames.size(); ++i) {

					string histoname = jetSelectionNames[j] + histoTypes[h] + metHistoNames[i]
						+ "_2";

					if (fileMC != 0) {
						TH1F * histoMC = (TH1F*) fileProfilesMC->FindObjectAny(histoname.c_str());
						removeBadPoints(histoMC);
						histoMC->SetTitle((jetSelectionTitles[j]).c_str());
						string ytitleMC = "#sigma " + histoTypesTitle[h];
						histoMC->GetYaxis()->SetTitle(ytitleMC.c_str());
						histoMC->GetYaxis()->SetRangeUser(0, maxYSigmaPlots);
						histoMC->GetXaxis()->SetRangeUser(minXSigmaPlots, maxXSigmaPlots);
						histoMC->SetMarkerStyle(dataMarkers[i]);
						histoMC->SetMarkerColor(mcColors[i]);
						histoMC->SetLineColor(mcLineColors[i]);
						histoMC->SetLineStyle(mcLineStyle[i]);
						histoMC->SetFillColor(mcColors[i]);
						histoMC->SetFillStyle(mcStyle[i]);
						histosMC->Add(histoMC);
						string legTitleMC = "Sim " + metHistoTitles[i];
						legend->AddEntry(histoMC, legTitleMC.c_str(), "l");
					}

				}
				drawHistosToCanvas(histos, histosMC, file == fileMC);
				legend->Draw("same");
				cmsPrel(lumi, 1);
				output->WriteTObject(c, 0, "overwrite");

				///Data/Data
				string canvasnameData = jetSelectionNames[j] + "_" + histoTypes[h] + "_OnlyData";
				TCanvas * cData = new TCanvas(canvasnameData.c_str(), canvasnameData.c_str());
				trash->Add(cData);
				histos = new TList();
				trash->Add(histos);
				histosMC = new TList();
				trash->Add(histosMC);
				TLegend *legendData = new TLegend(0.659, 0.586, 0.923, 0.919, "");

				trash->Add(legendData);
				legendData->SetFillColor(0);
				for (int i = 0; i < (int) metHistoNames.size(); ++i) {

					string histoname = jetSelectionNames[j] + histoTypes[h] + metHistoNames[i]
						+ "_2";

					if (debug)
						cout << "read Histo Name:" << histoname << endl;
					TH1F * histo = (TH1F*) fileProfiles->FindObjectAny(histoname.c_str());
					removeBadPoints(histo);
					string ytitle = "#sigma " + histoTypesTitle[h];
					histo->GetYaxis()->SetTitle(ytitle.c_str());
					histo->GetYaxis()->SetRangeUser(0, maxYSigmaPlots);
					histo->GetXaxis()->SetRangeUser(minXSigmaPlots, maxXSigmaPlots);
					histo->SetMarkerStyle(dataMarkers[i]);
					histo->SetMarkerColor(dataColors[i]);
					histo->SetLineColor(dataColors[i]);
					if (debug)
						cout << "set histo to color:" << histo->GetLineColor() << endl;
					histo->SetTitle((jetSelectionTitles[j]).c_str());
					histos->Add(histo);

					string legTitle = "Data " + metHistoTitles[i];

					legendData->AddEntry(histo, legTitle.c_str(), "p");

				}
				drawHistosToCanvas(histos, histosMC, file == fileMC);
				legendData->Draw("same");
				cmsPrel(lumi, 1);
				output->WriteTObject(cData, 0, "overwrite");

			}
			if (debug)
				cout << "============DRAW Sigma vs Plots MC/MC and DAta/Data for MHT" << endl;
			for (int h = 0; h < histoTypesMht.size(); ++h) {
				string canvasname = jetSelectionNames[j] + "_" + histoTypesMht[h] + "_OnlyMC";

				TCanvas * c_mhtMCMC = new TCanvas(canvasname.c_str(), canvasname.c_str());
				trash->Add(c_mhtMCMC);
				TList * histos = new TList();
				trash->Add(histos);
				TList * histosMC = new TList();
				trash->Add(histosMC);
				TLegend *legend_mhtMCMC = new TLegend(0.70, 0.70, 0.93, 0.91, "");
				trash->Add(legend_mhtMCMC);
				legend_mhtMCMC->SetFillColor(0);

				for (int i = 0; i < (int) mhtHistoNames.size(); ++i) {
					string histoname = jetSelectionNames[j] + histoTypesMht[h] + mhtHistoNames[i]
						+ "_2";

					if (fileMC != 0) {
						TH1F * histoMC_mht =
							(TH1F*) fileProfilesMC->FindObjectAny(histoname.c_str());
						removeBadPoints(histoMC_mht);
						histoMC_mht->SetMarkerStyle(dataMarkers[i]);
						histoMC_mht->SetMarkerColor(mcColors[i]);
						histoMC_mht->SetLineColor(mcLineColors[i]);
						histoMC_mht->SetLineStyle(mcLineStyle[i]);
						histoMC_mht->SetFillColor(mcColors[i]);
						histoMC_mht->SetFillStyle(mcStyle[i]);
						string ytitleMCmht = "#sigma " + histoTypesMhtTitle[h];
						histoMC_mht->GetYaxis()->SetTitle(ytitleMCmht.c_str());
						histoMC_mht->GetYaxis()->SetRangeUser(0, maxYSigmaPlots);
						histoMC_mht->GetXaxis()->SetRangeUser(minXSigmaPlots, maxXSigmaPlots);
						histoMC_mht->SetTitle((jetSelectionTitles[j]).c_str());
						histosMC->Add(histoMC_mht);
						string legTitleMC = "Sim " + mhtHistoTitles[i];
						legend_mhtMCMC->AddEntry(histoMC_mht, legTitleMC.c_str(), "l");
					}

				}
				drawHistosToCanvas(histos, histosMC, file == fileMC);
				legend_mhtMCMC->Draw("same");
				cmsPrel(lumi, 1);
				output->WriteTObject(c_mhtMCMC, 0, "overwrite");
				string canvasnameDD = jetSelectionNames[j] + "_" + histoTypesMht[h] + "_OnlyData";
				TCanvas * c_mhtDD = new TCanvas(canvasnameDD.c_str(), canvasnameDD.c_str());
				trash->Add(c_mhtDD);
				histos->Clear();
				histosMC->Clear();
				TLegend *legend_mhtDD = new TLegend(0.659, 0.586, 0.923, 0.919, "");
				trash->Add(legend_mhtDD);
				legend_mhtMCMC->SetFillColor(0);

				for (int i = 0; i < (int) mhtHistoNames.size(); ++i) {
					string histonameDD = jetSelectionNames[j] + histoTypesMht[h] + mhtHistoNames[i]
						+ "_2";
					if (debug)
						cout << "read Histo Name:" << histonameDD << endl;
					TH1F * histo_mhtDD = (TH1F*) fileProfiles->FindObjectAny(histonameDD.c_str());
					removeBadPoints(histo_mhtDD);
					histo_mhtDD->SetTitle((jetSelectionTitles[j]).c_str());
					string ytitlemhtDD = "#sigma " + histoTypesMhtTitle[h];
					histo_mhtDD->GetYaxis()->SetTitle(ytitlemhtDD.c_str());
					histo_mhtDD->GetYaxis()->SetRangeUser(0, maxYSigmaPlots);
					histo_mhtDD->GetXaxis()->SetRangeUser(minXSigmaPlots, maxXSigmaPlots);
					if (histo_mhtDD == 0)
						if (debug)
							cout << "HISTO not found" << endl;
					histo_mhtDD->SetMarkerStyle(dataMarkers[i]);
					histo_mhtDD->SetLineColor(1);
					histo_mhtDD->SetMarkerColor(dataColors[i]);
					histos->Add(histo_mhtDD);

					string legTitleDD = "Data " + mhtHistoTitles[i];
					if (debug)
						cout << "leg Title:" << legTitleDD << endl;
					if (file != fileMC)
						legend_mhtDD->AddEntry(histo_mhtDD, legTitleDD.c_str(), "p");
				}
				drawHistosToCanvas(histos, histosMC, file == fileMC);
				legend_mhtDD->Draw("same");
				cmsPrel(lumi, 1);
				output->WriteTObject(c_mhtDD, 0, "overwrite");
			}
		}
	}
	gStyle->SetOptTitle(0);
	/////////////////////////////////DRAW Sigma vs Plots comparison to MC


	for (int j = 0; j < (int) jetSelectionNames.size(); ++j) {
		if (true) {
			debug = false;
			cout << "============DRAW Sigma vs Plots MC/Data all METs" << endl;
			bool isData = !isOnlyMC;
			for (int h = 0; h < (int) histoTypes.size(); ++h) {
				for (int s = 0; s < sumEtTypes.size(); ++s) {
					cout << "testA" << endl;
					string sumettypestr = sumEtTypes[s];
					bool histosumetBool = false;
					if (histoTypesSumEt[h] == "T")
						histosumetBool = true;
					if (!histosumetBool)
						sumettypestr = "";
					string canvasname = jetSelectionNames[j] + "_" + sumettypestr + ""
						+ histoTypes[h];
					cout << "testA1" << endl;
					TCanvas * c = new TCanvas(canvasname.c_str(), canvasname.c_str());
					trash->Add(c);
					TList * histosFit = new TList();
					trash->Add(histosFit);
					TList * histos = new TList();
					trash->Add(histos);
					TList * histosMC = new TList();
					trash->Add(histosMC);
					cout << "testA2" << endl;
					TLegend *legend = new TLegend(0.659, 0.586, 0.923, 0.919, "");

					trash->Add(legend);
					legend->SetFillColor(0);
					for (int i = 0; i < (int) metHistoNames.size(); ++i) {
						if (debug)
							cout << "met histo names:" << i << endl;
						string histoname = jetSelectionNames[j] + sumettypestr + histoTypes[h]
							+ metHistoNames[i] + "_2";
						string histoname1 = jetSelectionNames[j] + sumettypestr + histoTypes[h]
							+ metHistoNames[i] + "_1";
						bool onlyGen = false;
						if (s == 2)
							onlyGen = true;
						if (debug)
							cout << "draw SigmaVs..." << endl;
						if (debug)
							cout << "read Histo Name:" << histoname << endl;
						TH1F * histo = (TH1F*) fileProfiles->FindObjectAny(histoname.c_str());
						if (debug)
							cout << "histo found?:" << histo << endl;
						if (debug)
							cout << "range get No" << h << endl;
						if (debug)
							cout << "range size A" << histoTypesRangeX.size() << endl;
						if (debug)
							cout << "range size B" << histoTypesRangeY.size() << endl;
						if (debug)
							cout << "range size C" << histoTypesRangeYMean.size() << endl;
						const pair<double, double> histoTypesRangeXPair = histoTypesRangeX[h];
						const pair<double, double> histoTypesRangeYPair = histoTypesRangeY[h];
						const pair<double, double> histoTypesRangeYMeanPair =
							histoTypesRangeYMean[h];
						if (!onlyGen && histo != 0) {
							if (debug)
								cout << "not only gen" << endl;
							if (debug)
								cout << " - histo:" << histo->GetName() << endl;

							removeBadPoints(histo);
							string ytitle = "#sigma " + histoTypesTitle[h];
							histo->GetXaxis()->SetRangeUser(histoTypesRangeXPair.first,
															histoTypesRangeXPair.second);
							histo->GetYaxis()->SetRangeUser(histoTypesRangeYPair.first,
															histoTypesRangeYPair.second);

							string xtitle = "" + histoTypesTitleX[h];
							histo->GetXaxis()->SetTitle(xtitle.c_str());
							histo->SetMarkerStyle(dataMarkers[i]);
							histo->SetMarkerColor(dataColors[i]);
							histo->SetLineColor(1);
							if (debug)
								cout << "set histo to color:" << histo->GetLineColor() << endl;
							histo->SetTitle((jetSelectionTitles[j]).c_str());
							histos->Add(histo);

							if (i == 1 && histosumetBool) {
								double startFitX = 30;
								if (plotTypeII && !plotTypeI)
									startFitX = 90;
								TF1 * fitRes = drawResolutionFit(histo, startFitX);
								cout << "=======parError Sqrt:" << fitRes->GetParError(0) << endl;
								TF1 *final = new TF1("final", "sqrt(fitRes)",
														fitRes->GetXaxis()->GetXmin(),
														fitRes->GetXaxis()->GetXmax());
								trash->Add(final);
								final->SetParErrors(fitRes->GetParErrors());
								if (debug)
									cout << "parError Sqrt:" << final->GetParError(0) << endl;

								final->SetLineWidth(2);
								final->SetLineColor(histo->GetMarkerColor());
								histosFit->Add(final);
								//final->Draw("same");

								//delete fit;
							} else {

								//histo->Draw("same");

								//TF1 *final = new TF1("final","sqrt(fit)",histo->GetXaxis()->GetXmin(),histo->GetXaxis()->GetXmax());

								//final->Draw("same");
								//delete fit;
							}
						}
						if (fileMC != 0) {
							if (debug)
								cout << "TEST" << endl;
							TH1F * histoMC =
								(TH1F*) fileProfilesMC->FindObjectAny(histoname.c_str());
							if (debug)
								cout << "histoMC" << histoMC << endl;
							if (histoMC != 0) {
								removeBadPoints(histoMC);

								histoMC->SetTitle((jetSelectionTitles[j]).c_str());
								string ytitleMC = "#sigma " + histoTypesTitle[h];
								histoMC->GetYaxis()->SetTitle(ytitleMC.c_str());
								histoMC->GetYaxis()->SetRangeUser(0, maxYSigmaPlots);

								histoMC->GetXaxis()->SetRangeUser(histoTypesRangeXPair.first,
																	histoTypesRangeXPair.second);
								histoMC->GetYaxis()->SetRangeUser(histoTypesRangeYPair.first,
																	histoTypesRangeYPair.second);
								//cout<<"y axis starts"<<histoTypesRangeYPair.first<<endl;
								//cout<<"y axis ends"<<histoTypesRangeYPair.second<<endl;
								//cout<<"x axis starts"<<histoTypesRangeXPair.first<<endl;
								//								cout<<"x axis ends"<<histoTypesRangeXPair.second<<endl;
								string xtitle = "" + histoTypesTitleX[h];
								histoMC->GetXaxis()->SetTitle(xtitle.c_str());
								//					if (histoMC->GetEntries()!=0) {
								//
								//						histoMC->Scale(histo->GetEntries()
								//								/histoMC->GetEntries());
								//					}
								histoMC->SetMarkerStyle(dataMarkers[i]);
								histoMC->SetMarkerColor(mcColors[i]);
								histoMC->SetLineColor(mcLineColors[i]);
								histoMC->SetLineStyle(mcLineStyle[i]);
								histoMC->SetFillColor(mcColors[i]);
								histoMC->SetFillStyle(mcStyle[i]);
								histosMC->Add(histoMC);

								string legTitleMC = "Sim " + metHistoTitles[i];
								legend->AddEntry(histoMC, legTitleMC.c_str(), "l");
								if (debug)
									cout << "TEST 2" << endl;
							}
						}
						string legTitle = "Data " + metHistoTitles[i];
						if (!onlyGen) {
							if (file != fileMC)
								legend->AddEntry(histo, legTitle.c_str(), "p");
						}

					}
					if (debug)
						cout << "DRAW" << endl;
					drawHistosToCanvas(histos, histosMC, file == fileMC, histosFit, true, false,
										true);
					legend->Draw("same");
					cmsPrel(lumi, 1, isData, fileMC != 0);
					cout << "write object:" << c->GetName() << endl;
					output->WriteTObject(c, 0, "overwrite");
					cout << "TESTC" << endl;
					///Add code  for ratio of resolutions
					if (isData && histos->GetSize() > 0) {
						cout << "draw ratio plots for data" << endl;
						TCanvas * cRatio = new TCanvas((canvasname + "ratio").c_str(), (canvasname
							+ "ratio").c_str());
						TLegend *legendRat = new TLegend(0.68, 0.66, 0.94, 0.86, "");

						trash->Add(legendRat);
						legendRat->SetFillColor(0);
						//cout<<"histos size:"<<histos->GetSize()<<endl;
						TH1F * rawhist = (TH1F *) histos->At(0)->Clone();
						for (int hrat = 1; hrat < histos->GetSize(); ++hrat) {
							TH1F * histRat = (TH1F *) histos->At(hrat)->Clone();
							histRat->Sumw2();
							histRat->Divide(histRat, rawhist, 1, 1, "B");

							//cout<<"ratio"<<hrat<<endl;
							string legTitleRat = "" + metHistoTitles[hrat] + "";
							legendRat->AddEntry(histRat, legTitleRat.c_str(), "lp");
							histRat->SetLineColor(hrat);
							histRat->SetMarkerColor(hrat);
							histRat->SetMarkerStyle(20 + hrat);
							string ytitle = histoTypesTitle[h];
							ytitle = "#sigma (" + ytitle;
							ytitle = ytitle + ") norm. to raw #slash{E}_{T}";
							//cout<<"ytitle:"<<ytitle<<endl;
							histRat->SetYTitle(ytitle.c_str());
							histRat->SetAxisRange(0, 2, "Y");
							if (hrat == 1)
								histRat->Draw();
							else
								histRat->Draw("same");
							cmsPrel(lumi, 0, isData, false);
						}
						legendRat->Draw("same");
						//cout<<"write ratio plots for data"<<endl;
						output->WriteTObject(cRatio, 0, "overwrite");
					}
					TCanvas * cRatio = new TCanvas((canvasname + "ratioMC").c_str(), (canvasname
						+ "ratioMC").c_str());
					TLegend *legendRat = new TLegend(0.68, 0.66, 0.94, 0.86, "");
					cout << "testB" << endl;
					trash->Add(legendRat);
					legendRat->SetFillColor(0);
					cout << "testB1" << endl;
					if (histosMC->GetSize() != 0) {

						TH1F * rawhist = (TH1F *) histosMC->At(0)->Clone();
						cout << "testB2" << endl;
						for (int hrat = 1; hrat < (int) histosMC->GetSize(); ++hrat) {
							TH1F * histRat = (TH1F *) histosMC->At(hrat)->Clone();
							cout << "ratioA" << hrat << endl;

							histRat->Sumw2();
							histRat->Divide(histRat, rawhist, 1, 1, "B");
							cout << "ratio" << hrat << endl;
							string legTitleMCRat = "Sim " + metHistoTitles[hrat] + "";
							legendRat->AddEntry(histRat, legTitleMCRat.c_str(), "l");
							histRat->SetLineColor(hrat);
							histRat->SetAxisRange(0, 2, "Y");

							string ytitle = histoTypesTitle[h];
							ytitle = "#sigma (" + ytitle;
							ytitle = ytitle + ") norm. to raw #slash{E}_{T}";
							//cout<<"ytitle:"<<ytitle<<endl;
							histRat->SetYTitle(ytitle.c_str());
							if (hrat == 1)
								histRat->Draw();
							else
								histRat->Draw("same");

						}
					}
					TLatex latex;
					latex.SetNDC();
					latex.SetTextSize(0.06);
					if (isPFOnlyPlot) {

						latex.DrawLatex(0.2, 0.75, Form("PF #slash{E}_{T}"));

					} else {

						latex.DrawLatex(0.2, 0.75, Form("Calo #slash{E}_{T}"));

					}
					legendRat->Draw("same");
					output->WriteTObject(cRatio, 0, "overwrite");

					if (!histosumetBool) {
						break;
					}
				}
			}
		}
		//return 0;
		///CHRISTIAN - HIER WERDEN DIE PLOTS GEMACHT...
		cout << "============DRAW Mean vs Plots MC/Data all METs" <<histoTypes.size()<< endl;
		//MEANPLOTS
		for (int h = 0; h < histoTypes.size(); ++h) {
			for (int s = 0; s < sumEtTypes.size(); ++s) {
				bool isData = !isOnlyMC;
				string sumettypestr = sumEtTypes[s];
				bool histosumetBool = false;
				if (histoTypesSumEt[h] == "T")
					histosumetBool = true;
				if (!histosumetBool)
					sumettypestr = "";

				string canvasname = jetSelectionNames[j] + "_" + sumettypestr + "_Mean_"
					+ histoTypes[h];
				if (debug)
					cout << "canvas:" << canvasname << endl;
				if (!histosumetBool)
					if (debug)
						cout << "NO sumEt plots!" << endl;
				TCanvas * c = new TCanvas(canvasname.c_str(), canvasname.c_str());
				trash->Add(c);
				TList * histos = new TList();
				trash->Add(histos);
				TList * histosMC = new TList();
				trash->Add(histosMC);
				TList * histosSYST = new TList();
				trash->Add(histosSYST);
				TList * histosMCSYST = new TList();
				trash->Add(histosMCSYST);
				TLegend *legend = new TLegend(0.68, 0.66, 0.94, 0.86, "");
				if (!isData)
					legend = new TLegend(0.68, 0.66, 0.90, 0.82, "");
				trash->Add(legend);
				legend->SetFillColor(0);
				double maxX = 0;
				double minX = 300;
				string histoname = "";
				bool legendUpperLeft = false;
				int noOfTypesToLoop = metHistoNames.size();
//				if (!isData)
//					noOfTypesToLoop = 1;
				for (int i = 0; i < noOfTypesToLoop; ++i) {

					histoname = jetSelectionNames[j] + sumettypestr + histoTypes[h]
						+ metHistoNames[i] + "_1";

					bool onlyGen = false;
					if (s == 2)
						onlyGen = true;
					if (debug)
						cout << "draw MeanVs..." << endl;
					if (debug)
						cout << "read Histo Name:" << histoname << endl;
					TH1F * histo = (TH1F*) fileProfiles->FindObjectAny(histoname.c_str());
					if (histo != 0) {
						TH1F * histoSYST = 0;
						if (HistoDrawUtil::containsSubstr(metHistoNames[i], "UC")
							|| HistoDrawUtil::containsSubstr(metHistoNames[i], "II")
							|| HistoDrawUtil::containsSubstr(metHistoNames[i], "I")
							|| HistoDrawUtil::containsSubstr(metHistoNames[i], "1")) {
							histoSYST
								= (TH1F*) fileProfiles->FindObjectAny(("SYST_" + histoname).c_str());
						}

						const pair<double, double> histoTypesRangeXPair = histoTypesRangeX[h];
						const pair<double, double> histoTypesRangeYPair = histoTypesRangeY[h];
						const pair<double, double> histoTypesRangeYMeanPair =
							histoTypesRangeYMean[h];

						if (!onlyGen && histo != 0) {

							if (HistoDrawUtil::containsSubstr(histoname, "bisectSumSigmaRecoilDiv")) {
								legendUpperLeft = true;
								removeBadPoints(histo);
							} else {
								legendUpperLeft = true;
								removeBadPointsMean(histo);
							}
							string ytitle = "< " + histoTypesTitle[h] + " >";

							histo->GetYaxis()->SetTitle(ytitle.c_str());
							if (histoSYST != 0) {
								histoSYST->GetYaxis()->SetTitle(ytitle.c_str());
								removeBadPointsErrorBar(histoSYST);
							}
							histo->GetXaxis()->SetRangeUser(histoTypesRangeXPair.first,
															histoTypesRangeXPair.second);
							if (histoSYST != 0)
								histoSYST->GetXaxis()->SetRangeUser(histoTypesRangeXPair.first,
																	histoTypesRangeXPair.second);

							if (histoTypesRangeXPair.second >= maxX)
								maxX = histoTypesRangeXPair.second;
							if (histoTypesRangeXPair.first <= minX)
								minX = histoTypesRangeXPair.first;
							if (debug)
								cout << "RangeX:" << histoTypesRangeXPair.second << endl;
							histo->GetYaxis()->SetRangeUser(histoTypesRangeYMeanPair.first,
															histoTypesRangeYMeanPair.second);
							if (histoSYST != 0)
								histoSYST->GetYaxis()->SetRangeUser(histoTypesRangeYMeanPair.first,
																	histoTypesRangeYMeanPair.second);
							if (histoSYST != 0) {
								cout << "Data SYST found" << endl;
							}
							string xtitle = "" + histoTypesTitleX[h];
							histo->GetXaxis()->SetTitle(xtitle.c_str());
							histo->SetMarkerStyle(dataMarkers[i]);
							histo->SetMarkerColor(dataColors[i]);
							histo->SetLineColor(dataColors[i]);
							//if(debug)if(debug)cout<<"set histo to color:"<<histo->GetLineColor()<<endl;
							histo->SetTitle((jetSelectionTitles[j]).c_str());
							histos->Add(histo);
							if (histoSYST != 0) {
								histoSYST->GetXaxis()->SetTitle(xtitle.c_str());
								histoSYST->SetMarkerStyle(dataMarkers[i]);
								histoSYST->SetMarkerColor(dataColors[i]);
								histoSYST->SetLineColor(dataColors[i]);
								//if(debug)if(debug)cout<<"set histo to color:"<<histo->GetLineColor()<<endl;
								histoSYST->SetTitle((jetSelectionTitles[j]).c_str());
								histosSYST->Add(histoSYST);
							}
							//cout<<"!!!!!!!!!!!!!!!!ADD HISTO"<<endl;
						}

						if (fileMC != 0) {

							TH1F * histoMC =
								(TH1F*) fileProfilesMC->FindObjectAny(histoname.c_str());
							TH1F * histoMCSYST = 0;
							if (HistoDrawUtil::containsSubstr(metHistoNames[i], "UC")
								|| HistoDrawUtil::containsSubstr(metHistoNames[i], "II")
								|| HistoDrawUtil::containsSubstr(metHistoNames[i], "I")
								|| HistoDrawUtil::containsSubstr(metHistoNames[i], "1")) {
								histoMCSYST = (TH1F*) fileProfilesMC->FindObjectAny(("SYST_"
									+ histoname).c_str());
							}
							if (histoMCSYST != 0) {
								cout << "MC SYST found" << endl;
							}
							if (histoMC != 0) {
								removeBadPointsMean(histoMC);
								histoMC->SetTitle((jetSelectionTitles[j]).c_str());
								string ytitleMC = "< " + histoTypesTitle[h] + " >";
								bool drawonlyraw = false;
								if (HistoDrawUtil::containsSubstr(histoTypesTitle[h],
																	"p_{T} #vec{#Delta Jet,GenJet}")) {
									drawonlyraw = true;
								}
								cout << "*******************************************************************************************************************HIER" << endl;

								histoMC->GetYaxis()->SetTitle(ytitleMC.c_str());
								if (histoMCSYST != 0)
									histoMCSYST->GetXaxis()->SetRangeUser(
																			histoTypesRangeXPair.first,
																			histoTypesRangeXPair.second);
								histoMC->GetXaxis()->SetRangeUser(histoTypesRangeXPair.first,
																	histoTypesRangeXPair.second);
								if (histoTypesRangeXPair.second >= maxX)
									maxX = histoTypesRangeXPair.second;
								if (histoTypesRangeXPair.first <= minX)
									minX = histoTypesRangeXPair.first;
								if (debug)
									cout << "RangeX:" << histoTypesRangeXPair.second << endl;
								histoMC->GetYaxis()->SetRangeUser(histoTypesRangeYMeanPair.first,
																	histoTypesRangeYMeanPair.second);
								if (histoMCSYST)
									histoMCSYST->GetYaxis()->SetRangeUser(
																			histoTypesRangeYMeanPair.first,
																			histoTypesRangeYMeanPair.second);
								string xtitle = "" + histoTypesTitleX[h];
								//if(debug)cout<<"histo x title:"<<xtitle<<endl;
								histoMC->GetXaxis()->SetTitle(xtitle.c_str());
								histoMC->SetMarkerStyle(dataMarkers[i]);
								histoMC->SetMarkerColor(mcColors[i]);
								histoMC->SetLineColor(mcLineColors[i]);
								histoMC->SetLineStyle(mcLineStyle[i]);
								histoMC->SetFillColor(mcColors[i]);
								histoMC->SetFillStyle(mcStyle[i]);
								if (drawonlyraw) {
									if (h == 0 || h==2)
										histosMC->Add(histoMC);
									cout<<"=====================================================================================================================s:"<<h<<endl;
								}
								//else
									histosMC->Add(histoMC);
								if (histoMCSYST != 0) {
									removeBadPointsErrorBar(histoMCSYST);
									histoMCSYST->GetXaxis()->SetTitle(xtitle.c_str());
									histoMCSYST->SetMarkerStyle(dataMarkers[i]);
									histoMCSYST->SetMarkerColor(mcColors[i]);
									histoMCSYST->SetLineColor(mcLineColors[i]);
									histoMCSYST->SetLineStyle(mcLineStyle[i]);
									histoMCSYST->SetFillColor(mcColors[i]);
									histoMCSYST->SetFillStyle(mcStyle[i]);
									histosMCSYST->Add(histoMCSYST);
								}
								string legTitleMC = "" + metHistoTitles[i];
								//CHRISTIAN:MC labels in legende aufnehmen
								//legend->AddEntry(histoMC, legTitleMC.c_str(), "l");
								if (!isData) {
									legend->AddEntry(histoMC, legTitleMC.c_str(), "l");
								}
							}
						}
						//string legTitle = "Data " + metHistoTitles[i];
						string legTitle = "" + metHistoTitles[i];
						if (!onlyGen) {
							if (file != fileMC)
								//cout<<"!!!!!!!!!!!!!!!!ADD ENTRY"<<endl;
								//CHRISTIAN:MC labels in legende aufnehmen (und nur p fuer daten)
								//legend->AddEntry(histo, legTitle.c_str(), "p");
								legend->AddEntry(histo, legTitle.c_str(), "lp");
						}
					}
				}
				cout << "histos size A:" << histos->GetSize() << endl;
				drawHistosToCanvas(histos, histosMC, file == fileMC, 0, true, true, true, maxX,
									minX, histosSYST, histosMCSYST);
				cout << "histos size B:" << histos->GetSize() << endl;
				legend->Draw("same");
				if (debug || true)
					cout << "draw lumi:" << lumi << endl;
				if (legendUpperLeft)
					cmsPrel(lumi, 0, isData, fileMC != 0);
				else
					cmsPrel(lumi, 1, isData, fileMC != 0);
				TLatex latex;
				latex.SetNDC();
				latex.SetTextSize(0.06);
				if (isPFOnlyPlot) {
					//cout<<"is PF"<<endl;
					if (legendUpperLeft)
						latex.DrawLatex(0.2, 0.75, Form("PF #slash{E}_{T}"));
					else
						latex.DrawLatex(0.4, 0.3, Form("PF #slash{E}_{T}"));
				} else {
					//cout<<"is Calo"<<endl;
					if (legendUpperLeft)
						latex.DrawLatex(0.2, 0.75, Form("Calo #slash{E}_{T}"));
					else
						latex.DrawLatex(0.4, 0.3, Form("Calo #slash{E}_{T}"));
				}
				cout << "write output" << endl;
				output->WriteTObject(c, 0, "overwrite");
				if (debug || true)
					cout << "histos size" << histos->GetSize() << endl;
				if (!histosumetBool) {

					break;
				}
			}
		}
		//return 0;
		if (false) {
			cout << "============DRAW Sigma vs Plots MC/Data all MHTs" << endl;
			for (int h = 0; h < histoTypesMht.size(); ++h) {
				for (int s = 0; s < 2; ++s) {

					string canvasname = jetSelectionNames[j] + "_" + sumEtTypes[s] + "_"
						+ histoTypesMht[h];
					TList * histos = new TList();
					trash->Add(histos);
					TList * histosMC = new TList();
					trash->Add(histosMC);
					TList * histosFit = new TList();
					trash->Add(histosFit);
					TCanvas * c_mht = new TCanvas(canvasname.c_str(), canvasname.c_str());
					trash->Add(c_mht);
					TLegend *legend_mht = new TLegend(0.71, 0.65, 0.93, 0.91, "");

					trash->Add(legend_mht);
					legend_mht->SetFillColor(0);

					for (int i = 0; i < (int) mhtHistoNames.size(); ++i) {

						string histoname = jetSelectionNames[j] + sumEtTypes[s] + histoTypesMht[h]
							+ mhtHistoNames[i] + "_2";
						if (debug)
							cout << "draw SigmaVs...MHT" << endl;
						if (debug)
							cout << "read Histo Name:" << histoname << endl;
						TH1F * histo_mht = (TH1F*) fileProfiles->FindObjectAny(histoname.c_str());
						removeBadPoints(histo_mht);
						histo_mht->SetTitle((jetSelectionTitles[j]).c_str());
						string ytitlemht = "#sigma " + histoTypesMhtTitle[h];
						histo_mht->GetYaxis()->SetTitle(ytitlemht.c_str());

						const pair<double, double> histoTypesRangeXPair_mht =
							histoTypesRangeX_mht[h];
						const pair<double, double> histoTypesRangeYPair_mht =
							histoTypesRangeY_mht[h];
						histo_mht->GetXaxis()->SetRangeUser(histoTypesRangeXPair_mht.first,
															histoTypesRangeXPair_mht.second);
						histo_mht->GetYaxis()->SetRangeUser(histoTypesRangeYPair_mht.first,
															histoTypesRangeYPair_mht.second);

						if (histo_mht == 0)
							if (debug)
								cout << "HISTO not found" << endl;
						histo_mht->SetMarkerStyle(dataMarkers[i]);
						histo_mht->SetLineColor(dataColors[i]);
						histo_mht->SetMarkerColor(dataColors[i]);
						histos->Add(histo_mht);
						if (i == 1) {
							double startFitX = 30;
							if (plotTypeII && !plotTypeI)
								startFitX = 90;
							TF1 * fitRes = drawResolutionFit(histo_mht, startFitX);
							cout << "=======parError Sqrt:" << fitRes->GetParError(0) << endl;
							TF1 *final = new TF1("final", "sqrt(fitRes)", 0, 150);
							trash->Add(final);
							final->SetParErrors(fitRes->GetParErrors());
							if (debug)
								cout << "parError Sqrt:" << final->GetParError(0) << endl;

							final->SetLineWidth(2);
							final->SetLineColor(histo_mht->GetMarkerColor());
							histosFit->Add(final);
							//final->Draw("same");

							//delete fit;
						}
						if (fileMC != 0) {
							TH1F * histoMC_mht =
								(TH1F*) fileProfilesMC->FindObjectAny(histoname.c_str());
							removeBadPoints(histoMC_mht);
							//					if (histoMC_mht->GetEntries()!=0) {
							//						histoMC_mht->Scale(histo_mht->GetEntries()
							//								/histoMC_mht->GetEntries());
							//					}

							histoMC_mht->SetMarkerStyle(dataMarkers[i]);
							histoMC_mht->SetMarkerColor(mcColors[i]);
							histoMC_mht->SetLineColor(mcLineColors[i]);
							histoMC_mht->SetLineStyle(mcLineStyle[i]);
							histoMC_mht->SetFillColor(mcColors[i]);
							histoMC_mht->SetFillStyle(mcStyle[i]);
							string ytitleMCmht = "#sigma " + histoTypesMhtTitle[h];
							histoMC_mht->GetYaxis()->SetTitle(ytitleMCmht.c_str());
							histoMC_mht->GetXaxis()->SetRangeUser(histoTypesRangeXPair_mht.first,
																	histoTypesRangeXPair_mht.second);
							histoMC_mht->GetYaxis()->SetRangeUser(histoTypesRangeYPair_mht.first,
																	histoTypesRangeYPair_mht.second);
							histoMC_mht->SetTitle((jetSelectionTitles[j]).c_str());
							histosMC->Add(histoMC_mht);
							string legTitleMC = "Sim. " + mhtHistoTitles[i];
							legend_mht->AddEntry(histoMC_mht, legTitleMC.c_str(), "l");
						}
						string legTitle = "Data " + mhtHistoTitles[i];
						if (debug)
							cout << "leg Title:" << legTitle << endl;
						if (file != fileMC)
							legend_mht->AddEntry(histo_mht, legTitle.c_str(), "p");
					}
					drawHistosToCanvas(histos, histosMC, file == fileMC, histosFit);
					legend_mht->Draw("same");
					cmsPrel(lumi, 1);
					output->WriteTObject(c_mht, 0, "overwrite");
				}
			}
		}
	}
	gStyle->SetOptTitle(0);
	//gROOT->ForceStyle(1);

	/////////////////////////////////DRAW 2D Plots
	if (false) {
		cout << "============DRAW LEGO Plots 2D MET" << endl;
		for (int j = 0; j < (int) jetSelectionNames.size(); ++j) {
			for (int h = 0; h < histoTypes.size(); ++h) {
				for (int i = 0; i < (int) metHistoNames.size(); ++i) {
					for (int s = 0; s < sumEtTypes.size(); ++s) {
						string sumettypestr = sumEtTypes[s];
						bool histosumetBool = false;
						if (histoTypesSumEt[h] == "T")
							histosumetBool = true;
						if (!histosumetBool)
							sumettypestr = "";
						string canvasname = "2D_" + jetSelectionNames[j] + "_" + sumettypestr
							+ histoTypes[h] + metHistoNames[i];
						TCanvas * c2D = new TCanvas(canvasname.c_str(), canvasname.c_str());
						trash->Add(c2D);
						string histoname = jetSelectionNames[j] + sumettypestr + histoTypes[h]
							+ metHistoNames[i];
						TH2F * histo2D = (TH2F*) file->FindObjectAny(histoname.c_str());
						if (histo2D != 0) {
							string histoTitle = jetSelectionTitles[j] + " MET " + metHistoTitles[i];
							histo2D->SetTitle(histoTitle.c_str());
							string xtitle = "" + histoTypesTitleX[h];
							histo2D->GetXaxis()->SetTitle(xtitle.c_str());
							histo2D->SetFillStyle(0);
							string t = histoTypesTitle[h];
							histo2D->GetYaxis()->SetTitle(t.c_str());

							const pair<double, double> histoTypesRangeXPair = histoTypesRangeX[h];
							const pair<double, double> histoTypesRangeYMeanPair =
								histoTypesRangeYMean[h];
							histo2D->GetXaxis()->SetRangeUser(histoTypesRangeXPair.first,
																histoTypesRangeXPair.second);
							histo2D->GetYaxis()->SetRangeUser(histoTypesRangeYMeanPair.first,
																histoTypesRangeYMeanPair.second);

							gStyle->SetOptTitle(0);
							histo2D->Draw("BOX");
							//histo2D->Draw("LEGO10");
							gStyle->SetOptTitle(0);
							cmsPrel(lumi, 1);
							output->WriteTObject(c2D, 0, "overwrite");

						}
						if (!histosumetBool) {

							break;
						}

					}
				}
			}
			cout << "============DRAW LEGO Plots 2D MHT" << endl;
			for (int h = 0; h < histoTypesMht.size(); ++h) {
				for (int i = 0; i < (int) mhtHistoNames.size(); ++i) {
					string histoname = jetSelectionNames[j] + histoTypesMht[h] + mhtHistoNames[i];
					string canvasname = "2D_" + jetSelectionNames[j] + "_" + histoTypesMht[h]
						+ mhtHistoNames[i];
					TCanvas * cmht2D = new TCanvas(canvasname.c_str(), canvasname.c_str());
					trash->Add(cmht2D);
					TH2F * histo_mht2D = (TH2F*) file->FindObjectAny(histoname.c_str());
					string histoTitle = jetSelectionTitles[j] + " MHT " + mhtHistoTitles[i];
					histo_mht2D->SetTitle(histoTitle.c_str());
					histo_mht2D->GetXaxis()->SetTitle("#Sigma H_{T}[GeV]");
					string t = histoTypesMhtTitle[h];
					histo_mht2D->GetYaxis()->SetTitle(t.c_str());

					const pair<double, double> histoTypesRangeXPairMht = histoTypesRangeX_mht[h];
					const pair<double, double> histoTypesRangeYMeanPairMht =
						histoTypesRangeYMean_mht[h];
					histo_mht2D->GetXaxis()->SetRangeUser(histoTypesRangeXPairMht.first,
															histoTypesRangeXPairMht.second);
					histo_mht2D->GetYaxis()->SetRangeUser(histoTypesRangeYMeanPairMht.first,
															histoTypesRangeYMeanPairMht.second);

					histo_mht2D->SetLineColor(1);
					histo_mht2D->SetFillStyle(0);
					//histo_mht2D->Draw("LEGO10");
					histo_mht2D->Draw("BOX");
					cmsPrel(lumi);
					output->WriteTObject(cmht2D, 0, "overwrite");
					//delete histo_mht;
				}
			}
		}
	}
	/////////////////////////////////DRAW 1D Plots comparison to MC
	gStyle->SetOptTitle(0);
	gStyle->SetOptLogy(1);
	gStyle->SetEndErrorSize(0);
	gStyle->SetErrorX(0.);
	//gROOT->ForceStyle(1);
	if (fileMC != 0) {
		cout << "============DRAW 1D Plots comparison to MC" << endl;
		for (int j = 0; j < (int) jetSelectionNames.size(); ++j) {
			for (int h = 0; h < histoTypes1D.size(); ++h) {
				//output->ReOpen("update");
				string canvasname = "1D_" + histoTypes1D[h] + jetSelectionNames[j];
				TCanvas * c1D = new TCanvas(canvasname.c_str(), canvasname.c_str());
				trash->Add(c1D);
				TList * histos = new TList();
				trash->Add(histos);
				TList * histosMC = new TList();
				trash->Add(histosMC);
				TLegend *legend_1D = new TLegend(0.659, 0.53, 0.923, 0.89, "");

				trash->Add(legend_1D);
				legend_1D->SetFillColor(0);
				bool negXAxis = false;
				double maxYAxis = 150000;
				for (int i = 0; i < (int) metHistoNames.size(); ++i) {

					string histoname = jetSelectionNames[j] + histoTypes1D[h] + metHistoNames[i];
					if (debug || true)
						cout << "read Histo Name:" << histoname << endl;
					TH1F * histo_1D = (TH1F*) file->FindObjectAny(histoname.c_str());

					if (histo_1D != 0) {
						//histo_1D->SetDirectory(0);
						//output->ReOpen("update");
						cout << "histo found:" << histo_1D << endl;
						cout << "jet sel:" << jetSelectionTitles[j] << endl;
						histo_1D->SetTitle((jetSelectionTitles[j]).c_str());
						//histo_1D->Rebin(2);
						const pair<double, double> histoTypes1DRangeXPair = histoTypes1DRangeX[h];
						histo_1D->GetXaxis()->SetRangeUser(histoTypes1DRangeXPair.first,
															histoTypes1DRangeXPair.second);

						if (histoTypes1DRangeXPair.first < 0)
							negXAxis = true;
						histo_1D->SetMinimum(0.5);

						histo_1D->GetYaxis()->SetRangeUser(0.5, maxYAxis);
						double binwidth = histo_1D->GetXaxis()->GetBinWidth(1);
						cout << "binwidth:" << binwidth << endl;
						if (histoTypes1D[h] == "angleRecoilBisectSum_") {
							histo_1D->GetYaxis()->SetTitle(("Number of Events /"
								+ HistoDrawUtil::getStringFromInt(binwidth) + "").c_str());
						} else {
							histo_1D->GetYaxis()->SetTitle(("Number of Events /"
								+ HistoDrawUtil::getStringFromInt(binwidth) + " GeV").c_str());
							if (debug)
								cout << "binwidth:" << binwidth << endl;
						}
						string title1D = histoTypes1DTitle[h];

						histo_1D->GetXaxis()->SetTitle(title1D.c_str());
						histo_1D->SetMarkerStyle(dataMarkers[i]);
						histo_1D->SetLineColor(dataColors[i]);
						//histo_1D->SetLineWidth(2);
						histo_1D->SetMarkerColor(dataColors[i]);

						histos->Add(histo_1D);

						if (file != fileMC) {
							string legtitData = "" + metHistoTitles[i];
							legend_1D->AddEntry(histo_1D, (legtitData).c_str(), "lp");
						}

						TH1F * histoMC_1D = (TH1F*) fileMC->FindObjectAny(histoname.c_str());

						if (histoMC_1D != 0) {
							//histoMC_1D->SetDirectory(0);
							//output->ReOpen("update");
							cout << "histomc !=0" << endl;
							histoMC_1D->SetTitle((jetSelectionTitles[j]).c_str());
							//histoMC_1D->Rebin(2);
							histoMC_1D->GetXaxis()->SetRangeUser(histoTypes1DRangeXPair.first,
																	histoTypes1DRangeXPair.second);
							//histoMC_1D->GetMaximumStored()

							histoMC_1D->GetYaxis()->SetRangeUser(0.5, maxYAxis);

							string title1DMC = histoTypes1DTitle[h];
							histoMC_1D->GetXaxis()->SetTitle(title1DMC.c_str());
							if (debug)
								cout << "CURRENT 1D histo:" << histo_1D->GetTitle() << endl;
							if (debug)
								cout << "MC " << histoMC_1D->Integral() << endl;
							if (debug)
								cout << "Data " << histo_1D->Integral() << endl;
							int bin50 = histo_1D->FindBin(50);
							int bin70 = histo_1D->FindBin(70);
							if (debug)
								cout << "Data >50: " << histo_1D->Integral(bin50,
																			histo_1D->GetNbinsX())
									<< endl;
							if (debug)
								cout << "Data >70: " << histo_1D->Integral(bin70,
																			histo_1D->GetNbinsX())
									<< endl;
							if (histoMC_1D->Integral() != 0) {
								if (debug || false)
									cout << "Scale " << histo_1D->Integral()
										/ histoMC_1D->Integral() << endl;
							}
							if (histoMC_1D->Integral() != 0) {
								histoMC_1D->Scale(histo_1D->Integral() / histoMC_1D->Integral());
							}
							//return 0;
							if (histoTypes1D[h] == "angleRecoilBisectSum_") {
								histoMC_1D->GetYaxis()->SetTitle(("Number of Events /"
									+ HistoDrawUtil::getStringFromInt(binwidth) + "").c_str());
							} else {
								histoMC_1D->GetYaxis()->SetTitle(("Number of Events /"
									+ HistoDrawUtil::getStringFromInt(binwidth) + " GeV").c_str());
							}
							histoMC_1D->SetMarkerStyle(dataMarkers[i]);
							histoMC_1D->SetMarkerColor(mcColors[i]);
							histoMC_1D->SetLineColor(mcLineColors[i]);
							histoMC_1D->SetFillColor(mcColors[i]);
							histoMC_1D->SetFillStyle(mcStyle[i]);
							histoMC_1D->SetLineStyle(mcLineStyle[i]);
							//if (fileMC!=file) {
							histoMC_1D->SetMinimum(0.5);
							//c1D->Update();
							histosMC->Add(histoMC_1D);
							//histoMC_1D->Draw("same  hist");
							string legTitleMC = "Sim. " + metHistoTitles[i];
							//legend_1D->AddEntry(histoMC_1D, legTitleMC.c_str(), "l");
							//}
							//				for (int g=0; g<genMetHistoNames.size(); ++g) {
							//					histoname=jetSelectionNames[j]+"sumEt_"+metHistoNames[i]
							//							+genMetHistoNames[g];
							//				}
						}

					}

				}
				//return;

				if (debug || true)
					cout << "save" << histos->GetSize() << endl;
				output->ReOpen("update");
				gPad->Update();
				drawHistosToCanvas(histos, histosMC, file == fileMC);

				legend_1D->Draw("same");
				c1D->Update();
				cmsPrel(lumi, 0, true, true);

				output->WriteTObject(c1D, 0, "overwrite");

			}
			cout << "============DRAW 1D Plots comparison to MC-MHT" << endl;
			for (int h = 0; h < histoTypes1DMht.size(); ++h) {
				string canvasnameHt = "1D_" + histoTypes1DMht[h] + jetSelectionNames[j];
				TCanvas * c1DHt = new TCanvas(canvasnameHt.c_str(), canvasnameHt.c_str());
				trash->Add(c1DHt);
				TList * histos = new TList();
				trash->Add(histos);
				TList * histosMC = new TList();
				trash->Add(histosMC);
				TLegend *legend_1DHt = new TLegend(0.659, 0.586, 0.923, 0.919, "");
				trash->Add(legend_1DHt);
				legend_1DHt->SetFillColor(0);
				for (int i = 0; i < (int) mhtHistoNames.size(); ++i) {

					string histonameHt = jetSelectionNames[j] + histoTypes1DMht[h]
						+ mhtHistoNames[i];
					TH1F * histo_1DHt = (TH1F*) file->FindObjectAny(histonameHt.c_str());
					if (histo_1DHt != 0) {
						const pair<double, double> histoTypes1DMhtRangeXPair =
							histoTypes1DMhtRangeX[h];
						histo_1DHt->GetXaxis()->SetRangeUser(histoTypes1DMhtRangeXPair.first,
																histoTypes1DMhtRangeXPair.second);
						//histo_1DHt->GetYaxis()->SetRangeUser(0.5, 1.1*histo_1DHt->GetMaximumStored());
						double binwidthHt = histo_1DHt->GetXaxis()->GetBinWidth(1);
						histo_1DHt->GetYaxis()->SetTitle(("Number of Events /"
							+ HistoDrawUtil::getStringFromInt(binwidthHt) + " GeV").c_str());
						histo_1DHt->SetMarkerStyle(dataMarkers[i]);
						histo_1DHt->SetLineColor(dataColors[i]);
						histo_1DHt->SetMarkerColor(dataColors[i]);
						histo_1DHt->SetTitle((jetSelectionTitles[j]).c_str());
						string title1DMht = histoTypes1DMhtTitle[h];
						histo_1DHt->GetXaxis()->SetTitle(title1DMht.c_str());
						histo_1DHt->SetLineStyle(1);
						histo_1DHt->SetLineColor(1);
						histo_1DHt->SetMinimum(0.5);
						histos->Add(histo_1DHt);
						if (file != fileMC) {
							string legtitleData = "Data " + mhtHistoTitles[i];
							legend_1DHt->AddEntry(histo_1DHt, (legtitleData).c_str(), "p");
						}
						TH1F * histoMC_1DHt = (TH1F*) fileMC->FindObjectAny(histonameHt.c_str());
						if (histoMC_1DHt != 0) {
							histoMC_1DHt->GetXaxis()->SetRangeUser(
																	histoTypes1DMhtRangeXPair.first,
																	histoTypes1DMhtRangeXPair.second);
							//histoMC_1DHt->GetYaxis()->SetRangeUser(0.5, 1.1*histo_1DHt->GetMaximumStored());
							histoMC_1DHt->SetTitle((jetSelectionTitles[j]).c_str());
							string title1DMhtMC = histoTypes1DMhtTitle[h];
							histoMC_1DHt->GetXaxis()->SetTitle(title1DMhtMC.c_str());
							if (histoMC_1DHt->GetEntries() != 0) {
								//						if(debug)cout<<"Sim. b"<<histoMC_1DHt->GetEntries()<<endl;
								//						if(debug)cout<<"Data b"<<histo_1DHt->GetEntries()<<endl;
								//						if(debug)cout<<"Scale MC b:"<<histo_1DHt->GetEntries()
								//								/histoMC_1DHt->GetEntries()<<endl;
								//						if(debug)cout<<"Sim. b"<<histoMC_1DHt->Integral()<<endl;
								//						if(debug)cout<<"Data b"<<histo_1DHt->GetEntries()<<endl;
								//						if(debug)cout<<"Scale MC b:"<<histo_1DHt->GetEntries()
								//								/histoMC_1DHt->GetEntries()<<endl;
								histoMC_1DHt->Scale(histo_1DHt->Integral()
									/ histoMC_1DHt->Integral());

							}
							histoMC_1DHt->GetYaxis()->SetTitle(("Number of Events /"
								+ HistoDrawUtil::getStringFromInt(binwidthHt) + " GeV").c_str());

							histoMC_1DHt->SetMarkerStyle(dataMarkers[i]);
							histoMC_1DHt->SetMarkerColor(mcColors[i]);
							histoMC_1DHt->SetFillColor(mcColors[i]);
							histoMC_1DHt->SetFillStyle(mcStyle[i]);
							histoMC_1DHt->SetLineStyle(mcLineStyle[i]);
							histoMC_1DHt->SetLineColor(mcLineColors[i]);
							histoMC_1DHt->SetMinimum(0.5);
							c1DHt->Update();
							gPad->Update();
							//if (fileMC!=file) {
							histosMC->Add(histoMC_1DHt);
							string legTitleMCHt = "Sim. " + mhtHistoTitles[i];
							legend_1DHt->AddEntry(histoMC_1DHt, legTitleMCHt.c_str(), "l");
							//}
						}

					}
					gPad->Update();
					drawHistosToCanvas(histos, histosMC, file == fileMC);
					legend_1DHt->Draw("same");
					c1DHt->Update();
					cmsPrel(lumi, 0);
					output->WriteTObject(c1DHt, 0, "overwrite");
				}
			}
		}
		//return;

	}
	gStyle->SetOptTitle(0);
	gStyle->SetOptLogy(0);

	//gROOT->ForceStyle(1);
	/////////////////////////////////DRAW Correlation Histos
	if (fileMC != 0 && false) {
		if (debug)
			cout << "Draw Correlation Histos" << endl;
		for (int j = 0; j < (int) jetSelectionNames.size(); ++j) {
			for (int k = 0; k < (int) mhtHistoNames.size(); ++k) {
				int gi = 0;
				for (int i = 0; i < (int) metHistoNames.size(); ++i) {
					string histoCorrName = jetSelectionNames[j] + "EtVsHt_" + metHistoNames[i]
						+ "_" + mhtHistoNames[k];
					string canvasname = "2D_Corr_" + histoCorrName;
					TCanvas * c2D = new TCanvas(canvasname.c_str(), canvasname.c_str());
					trash->Add(c2D);
					if (debug)
						cout << "read Histo:" << histoCorrName << endl;
					TH2F * histo2D = (TH2F*) fileMC->FindObjectAny(histoCorrName.c_str());
					string histoTitle = jetSelectionTitles[j] + " MET " + metHistoTitles[i]
						+ " - MHT " + mhtHistoTitles[k];
					if (debug)
						cout << "set HistoTitle: " << histoTitle << endl;
					histo2D->SetTitle(histoTitle.c_str());
					histo2D->GetXaxis()->SetTitle((histoTypes1DTitle[0].c_str()));
					string t = histoTypes1DMhtTitle[0];
					if (debug)
						cout << "title t:" << t << endl;
					histo2D->GetYaxis()->SetTitle(t.c_str());
					histo2D->GetXaxis()->SetRangeUser(minXSumEtHt, maxXSumEtHt);
					histo2D->GetYaxis()->SetRangeUser(minXSumEtHt, maxXSumEtHt);
					histo2D->Draw("box");
					cmsPrel(lumi);
					output->WriteTObject(c2D, 0, "overwrite");

				}
			}
			if (debug)
				cout << "start met vs genmet" << endl;

			for (int i = 0; i < (int) metHistoNames.size(); ++i) {
				for (int g = 0; g < 1; ++g) {
					for (int gt = 0; gt < genmetHistoTypes.size(); ++gt) {

						string histoGenEtVsEtName = jetSelectionNames[j] + genmetHistoTypes[gt]
							+ genMetHistoNames[g] + "_" + metHistoNames[i];
						string canvasnameMht = "2D_Corr_" + histoGenEtVsEtName;
						if (debug)
							cout << "canvasname" << canvasnameMht << endl;
						TCanvas * c2DMht =
							new TCanvas(canvasnameMht.c_str(), canvasnameMht.c_str());
						trash->Add(c2DMht);
						if (debug)
							cout << "read Histo GenEtVsEt:" << histoGenEtVsEtName << endl;
						TH2F * histo2DMht =
							(TH2F*) fileMC->FindObjectAny(histoGenEtVsEtName.c_str());
						string histoTitle = jetSelectionTitles[j] + " Gen MET " + metHistoTitles[i]
							+ " - MET " + metHistoTitles[i];
						histo2DMht->SetTitle(histoTitle.c_str());
						histo2DMht->GetXaxis()->SetTitle((("Gen " + histoTypes1DTitle[0]).c_str()));
						string t = histoTypes1DTitle[0];
						histo2DMht->GetYaxis()->SetTitle(t.c_str());

						const pair<double, double> genmetHistoTypesRangeXPair =
							genmetHistoTypes1DRangeX[gt];
						histo2DMht->GetXaxis()->SetRangeUser(genmetHistoTypesRangeXPair.first,
																genmetHistoTypesRangeXPair.second);
						histo2DMht->GetYaxis()->SetRangeUser(genmetHistoTypesRangeXPair.first,
																genmetHistoTypesRangeXPair.second);

						histo2DMht->SetFillStyle(0);
						histo2DMht->Draw("box");
						cmsPrel(lumi);
						output->WriteTObject(c2DMht, 0, "overwrite");
					}
				}
			}

			//SumEt vs SumEt
			for (int i = 0; i < (int) metHistoNames.size(); ++i) {
				for (int g = 0; g < metHistoNames.size(); ++g) {

					///////////
					string histoSumEtVsSumEtName = jetSelectionNames[j] + "SumEtVsSumEt_"
						+ metHistoNames[g] + "_" + metHistoNames[i];
					string canvasname = "2D_Corr_" + histoSumEtVsSumEtName;
					if (debug)
						cout << "canvasname" << canvasname << endl;
					TCanvas * c2DMht = new TCanvas(canvasname.c_str(), canvasname.c_str());
					trash->Add(c2DMht);
					if (debug)
						cout << "read Histo SumEtVsSumEt:" << histoSumEtVsSumEtName << endl;
					TH2F * histo2DMht = (TH2F*) file->FindObjectAny(histoSumEtVsSumEtName.c_str());
					string histoTitle = jetSelectionTitles[j] + " SumET " + metHistoTitles[g]
						+ " - SumET " + metHistoTitles[i];
					histo2DMht->SetTitle(histoTitle.c_str());
					histo2DMht->GetXaxis()->SetTitle((("" + histoTypes1DTitle[0]
						+ metHistoTitles[i]).c_str()));
					string t = histoTypes1DTitle[0] + metHistoTitles[g];
					histo2DMht->GetYaxis()->SetTitle(t.c_str());

					histo2DMht->SetFillStyle(0);
					histo2DMht->Draw("box");
					cmsPrel(lumi);
					output->WriteTObject(c2DMht, 0, "overwrite");
					///////////

				}
			}

		}
	}
	/////////////////Draw slices plots for some bins before/after TypeII//////////
	if (fileMC != 0 && true) {
		if (debug)
			cout << "output" << output << endl;
		if (debug)
			cout << "output name" << output->GetName() << endl;

		string filename = file->GetName();
		int size = filename.size();
		string ende = filename.substr(size - 5, size);
		if (ende == ".root") {
			filename = filename.substr(0, size - 5);
		}
		filename = filename + "_slices.root";

		string filenameMC = fileMC->GetName();
		int sizeMC = filenameMC.size();
		ende = filenameMC.substr(sizeMC - 5, sizeMC);
		if (ende == ".root") {
			filenameMC = filenameMC.substr(0, sizeMC - 5);
		}
		filenameMC = filenameMC + "_slices.root";
		if (debug)
			cout << "open File" << filenameMC << endl;

		TFile *input1 = new TFile(filename.c_str(), "update");

		string dirnameBeforeCorr = "UC_paraBisectSum_All_corrDeltaTrueVsTrueRel_d";
		//string dirnameAfterCorr = "UC_paraBisectSum_All_corrDeltaTrueCorrVsTrueRel_d";
		vector < string > dirNames;
		dirNames.push_back(dirnameBeforeCorr);
		//dirNames.push_back(dirnameAfterCorr);
		vector < string > binNames;
		binNames.push_back("30");
		binNames.push_back("32");
		binNames.push_back("35");
		for (int dirn = 0; dirn < (int) dirNames.size(); ++dirn) {
			for (int i = 0; i < (int) binNames.size(); ++i) {
				input1->cd(dirNames[dirn].c_str());
				TDirectory *subdir = gDirectory;
				string canvasname = dirNames[dirn] + "_canv_" + binNames[i];
				TCanvas * c = new TCanvas(canvasname.c_str());
				output->ReOpen("update");
				TH1D * proj = (TH1D*) subdir->FindObjectAny(("projY_" + binNames[i]).c_str());
				if (proj != 0) {
					proj->SetDirectory(0);
					proj->SetMarkerSize(1);
					TF1 * fit = (TF1 *) proj->GetFunction("gaus");
					if (debug||true)
						cout << "read gaus:" << fit << endl;
					fit->SetLineColor(4);
					proj->GetXaxis()->SetTitle("#Delta_{Gen,rel}");
					proj->GetYaxis()->SetTitle("#Entries");
					proj->Draw("");
				}
				//fit->Draw("same");
				c->Update();
				TPaveStats *stats = 0;
				if (proj != 0) {
					(TPaveStats*) proj->GetListOfFunctions()->FindObject("stats");
				}
				if (stats != 0) {
					stats->SetY1NDC(0.835);
					stats->SetY2NDC(0.995);
					stats->SetX1NDC(0.78);
					stats->SetX2NDC(0.98);
					//stats->SetLineColor(fit->GetLineColor());
					stats->Draw("samebr");
				}
				c->Update();

				cmsPrel(lumi, 1,true,false);
				//Draw Mean/RMS of Gaus Fit
				//				string sMean="Mean: "+Form("%.1f", fit->GetParameter(0))+"#pm"
				//						+Form("%.1f", fit->GetParError(0))+" GeV";
				//				string sMean="Widt: "+Form("%.1f", fit->GetParameter(1))+"#pm"
				//						+Form("%.1f", fit->GetParError(1))+" GeV";
				//				l.DrawLatex(0.55, 0.35, sMean);
				//				l.DrawLatex(0.55, 0.3, sRMS);
				//
				output->WriteTObject(c, 0, "overwrite");
			}
		}
	}
	/////////////////////////////////DRAW slices MC/Data in one Histo
	if (fileMC != 0 && false) {
		gStyle->SetOptStat(0);
		string filename = file->GetName();
		int size = filename.size();
		string ende = filename.substr(size - 5, size);
		if (ende == ".root") {
			filename = filename.substr(0, size - 5);
		}
		filename = filename + "_slices.root";

		string filenameMC = fileMC->GetName();
		int sizeMC = filenameMC.size();
		ende = filenameMC.substr(sizeMC - 5, sizeMC);
		if (ende == ".root") {
			filenameMC = filenameMC.substr(0, sizeMC - 5);
		}
		filenameMC = filenameMC + "_slices.root";
		if (debug)
			cout << "open File" << filename << endl;
		TFile *input1 = new TFile(filename.c_str(), "read");
		TFile *input1MC = new TFile(filenameMC.c_str(), "read");

		TIter nextkey(input1->GetListOfKeys());
		TKey *key;
		while ((key = (TKey*) nextkey())) {
			if (key->IsFolder()) {
				if (debug)
					cout << "change to subdir" << key->GetName() << endl;
				input1->cd(key->GetName());
				TDirectory *subdir = gDirectory;
				TDirectory * newDir = output->mkdir(key->GetName());
				if (debug)
					cout << "NEW SUBDIR:" << newDir->GetName() << endl;
				cmsPrel(lumi, 1);
				output->WriteTObject(newDir, 0, "Overwrite");
				if (debug)
					cout << "curr dir" << gDirectory->GetName() << endl;
				if (debug)
					cout << "curr file" << gFile->GetName() << endl;
				TIter nextkeySub(subdir->GetListOfKeys());
				TKey *keySub;
				int noKeys = subdir->GetNkeys();
				if (debug)
					cout << "noKeys" << noKeys << endl;
				noKeys = noKeys / 2;

				string multicName = gDirectory->GetName();
				multicName = "MultiC_" + multicName;
				TCanvas * myMultiCanv = new TCanvas(multicName.c_str(), multicName.c_str());
				if (debug)
					cout << "no Keys:" << noKeys << endl;
				myMultiCanv->Divide(2, 4);
				int noKeyIt = 0;
				while ((keySub = (TKey*) nextkeySub())) {
					if (noKeyIt % 5 == 0) {
						TObject* obj = (TObject*) keySub->ReadObj();
						if (obj->IsA()->InheritsFrom("TCanvas")) {

							TCanvas * canv = (TCanvas *) obj;
							//getCorresponding MC Canv

							TCanvas * canvMC = (TCanvas*) input1MC->FindObjectAny(canv->GetName());
							if (canvMC != 0) {
								//if(debug)if(debug)cout<<"canv MC Found!"<<canvMC<<endl;
								TIter nextkeyCanv(canvMC->GetListOfPrimitives());
								TKey *keyCanv;
								output->ReOpen("Update");

								output->cd(key->GetName());
								if (debug)
									cout << gDirectory->GetName() << " write in Dir" << endl;
								int padNo = (noKeyIt % 8) + 1;
								if (debug)
									cout << "padNo" << padNo << endl;
								if ((noKeyIt % 8 == 0) && noKeyIt != 0) {
									if (debug)
										cout << "write Old Multicanvas!" << endl;
									gDirectory->WriteTObject(myMultiCanv, 0, "Overwrite");
									output->Write();
									if (debug)
										cout << "new Multicanvas!" << endl;
									int canvNro = noKeyIt / 8;
									if (debug)
										cout << "#canv" << canvNro << endl;
									string canvNo = HistoDrawUtil::getStringFromInt(canvNro);
									string newName = multicName;
									newName = newName + "_" + canvNo;
									if (debug)
										cout << "new Name:" << newName << endl;
									//delete myMultiCanv;myMultiCanv=0;
									myMultiCanv = new TCanvas(newName.c_str(), newName.c_str());
									myMultiCanv->Divide(2, 4);
									myMultiCanv->Update();
								}
								if (debug)
									cout << "cd to pad:" << padNo << endl;
								myMultiCanv->cd(padNo);
								//TCanvas * myCanv=new TCanvas(canv->GetName(),canv->GetTitle());
								//myCanv->cd();
								TLegend *mylegend = new TLegend(0.70, 0.70, 0.93, 0.91, "");
								mylegend->SetFillColor(0);
								int counter = 0;
								while ((keyCanv = (TKey*) nextkeyCanv())) {

									double scaleFactor = 1;
									if (keyCanv->IsA()->InheritsFrom("TH1")) {
										//myCanv->cd();
										myMultiCanv->cd(padNo);
										if (debug)
											cout << "Draw really: " << keyCanv->GetName() << endl;
										//myCanv->Update();
										myMultiCanv->Update();
										TH1D * histo = (TH1D*) keyCanv->Clone();
										TH1D * histoOld =
											(TH1D*) input1->FindObjectAny(histo->GetName());
										if (histoOld == 0)
											if (debug)
												cout << "HIST not found>:" << histo->GetName()
													<< endl;
										if (histo->Integral() != 0 && histoOld != 0) {
											scaleFactor = histoOld->Integral() / histo->Integral();
											//if(debug)if(debug)cout<<"scaleFactor!"<<scaleFactor<<endl;
											histo->Scale(scaleFactor);

										}

										//gPad->Update();
										//myCanv->Update();
										myMultiCanv->Update();
										histo->SetDirectory(0);
										histo->AppendPad();
										string oldname = histo->GetName();
										histo->SetName((oldname + "_MC").c_str());
										histo->SetLineColor(2);

										mylegend->AddEntry(oldname.c_str(), "Data");
										mylegend->AddEntry(histo, "MC");
										if (debug)
											cout << "writeHisto:" << histo->GetName() << endl;
										//if(debug)cout<<"write histo "<<histo->GetName()<<endl;
										//delete old fits:
										TF1 * mytmp1 = histoOld->GetFunction("gaus");
										if (mytmp1 != 0) {
											delete mytmp1;
											mytmp1 = 0;
										}
										TF1 * mytmp2 = histo->GetFunction("gaus");
										if (mytmp2 != 0) {
											delete mytmp2;
											mytmp2 = 0;
										}

										histoOld->Fit("gaus", "R", "", (histoOld->GetMean()) - (3
											* histoOld->GetRMS()), (histoOld->GetMean()) + (3
											* histoOld->GetRMS()));
										TF1 *fittedGausOld = histoOld->GetFunction("gaus");
										histo->Fit("gaus", "R", "", (histo->GetMean()) - (3
											* histo->GetRMS()), (histo->GetMean()) + (3
											* histo->GetRMS()));
										TF1 *fittedGaus = histo->GetFunction("gaus");
										if (fittedGaus != 0) {
											histo->GetYaxis()->SetRangeUser(
																			0,
																			fittedGaus->GetMaximum());
										}

										histo->Draw("");
										//myCanv->Update();
										myMultiCanv->Update();
										//gPad->Update();
										histoOld->Draw("sameE");

										if (fittedGaus != 0) {
											fittedGaus->SetLineColor(2);
											fittedGaus->Draw("same");
										}
										if (fittedGausOld != 0)
											fittedGausOld->Draw("same");

										mylegend->Draw("same");
										//myCanv->Update();
										myMultiCanv->Update();
										//								myCanv->Update();
										//								myCanv->cd();
										//								histo->Draw("");
										//								myCanv->Update();
										gPad->Update();
										//								histoOld->Draw("sameE");
										//								if (fittedGaus!=0) {
										//									fittedGaus->SetLineColor(2);
										//									fittedGaus->Draw("same");
										//								}
										//								if (fittedGausOld!=0)
										//									fittedGausOld->Draw("same");
										//
										//								mylegend->Draw("same");
										//								myCanv->Update();
										//								gDirectory->WriteTObject(myCanv, 0, "Overwrite");

									}

								}
							}
							//myCanv->Update();
							myMultiCanv->Update();
							//myCanv->Update();
							if (debug)
								cout << "write canv" << endl;

							//gDirectory->WriteTObject(myCanv, 0, "Overwrite");
							noKeyIt++;
						}
						//if(debug)cout<<"write output"<<endl;

					}
				}
				gDirectory->WriteTObject(myMultiCanv, 0, "Overwrite");
				//myMultiCanv->Write();
				output->Write();
			}
			//break;
		}
		//delete c;
	}
	cout << "results written to directory:" << output->GetName() << endl;

	cout << "delete trash:" << endl;
	TIter nextTrash(trash);
	while (TObject * obj = (TObject *) nextTrash()) {
		//cout << "delete:" << obj->GetName() << endl;
		if (obj != 0)
			delete obj;
		obj = 0;
	}
	cout << "close output" << output->GetName() << endl;
	output->Close();
	delete output;

}
#endif
