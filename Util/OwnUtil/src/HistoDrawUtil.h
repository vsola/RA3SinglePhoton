#ifndef Util_h
#define Util_h
#include <TMath.h>
#include <TLorentzVector.h>
#include <TStyle.h>
#include <TTree.h>
#include <TKey.h>
#include <TError.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <TPaletteAxis.h>
#include <TPaveStats.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TVirtualHistPainter.h>
#include <TPaveText.h>
#include <TCanvas.h>
#include <TList.h>
#include <TLegend.h>
#include <TH1F.h>
#include <TF1.h>
#include <THStack.h>
#include <TLatex.h>


using namespace std;
/*
 * namespace is used for definition of Constants,
 * file configurations, Variables, etc
 */
namespace HistoDrawUtil {

// fixOverlay: Redraws the axis


// tdrGrid: Turns the grid lines on (true) or off (false)

void tdrGrid(bool gridOn, TStyle *tdrStyle) {
	tdrStyle->SetPadGridX(gridOn);
	tdrStyle->SetPadGridY(gridOn);
}

// fixOverlay: Redraws the axis

void fixOverlay() {
	gPad->RedrawAxis();
}


void setMyTDRStyle() {
	TStyle *tdrStyle = new TStyle("mytdrStyle", "Style for P-TDR");
	cout << "load tdr style..." << endl;
	// For the canvas:
	tdrStyle->SetCanvasBorderMode(0);
	tdrStyle->SetCanvasColor(kWhite);
	tdrStyle->SetCanvasDefH(600); //Height of canvas
	tdrStyle->SetCanvasDefW(600); //Width of canvas
	tdrStyle->SetCanvasDefX(0); //POsition on screen
	tdrStyle->SetCanvasDefY(0);

	// For the Pad:
	tdrStyle->SetPadBorderMode(0);
	// tdrStyle->SetPadBorderSize(Width_t size = 1);
	tdrStyle->SetPadColor(kWhite);
	tdrStyle->SetPadGridX(false);
	tdrStyle->SetPadGridY(false);
	tdrStyle->SetGridColor(0);
	tdrStyle->SetGridStyle(3);
	tdrStyle->SetGridWidth(1);

	// For the frame:
	tdrStyle->SetFrameBorderMode(0);
	tdrStyle->SetFrameBorderSize(1);
	tdrStyle->SetFrameFillColor(0);
	tdrStyle->SetFrameFillStyle(0);
	tdrStyle->SetFrameLineColor(1);
	tdrStyle->SetFrameLineStyle(1);
	tdrStyle->SetFrameLineWidth(1);

	// For the histo:
	// tdrStyle->SetHistFillColor(1);
	// tdrStyle->SetHistFillStyle(0);
	tdrStyle->SetHistLineColor(1);
	tdrStyle->SetHistLineStyle(0);
	tdrStyle->SetHistLineWidth(1);
	// tdrStyle->SetLegoInnerR(Float_t rad = 0.5);
	// tdrStyle->SetNumberContours(Int_t number = 20);

	tdrStyle->SetEndErrorSize(2);
	//  tdrStyle->SetErrorMarker(20);
	//tdrStyle->SetErrorX(0.);

	tdrStyle->SetMarkerStyle(20);

	//For the fit/function:
	tdrStyle->SetOptFit(0);
	tdrStyle->SetFitFormat("5.4g");
	tdrStyle->SetFuncColor(2);
	tdrStyle->SetFuncStyle(1);
	tdrStyle->SetFuncWidth(1);

	//For the date:
	tdrStyle->SetOptDate(0);
	// tdrStyle->SetDateX(Float_t x = 0.01);
	// tdrStyle->SetDateY(Float_t y = 0.01);

	// For the statistics box:
	tdrStyle->SetOptFile(0);
	tdrStyle->SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");
	tdrStyle->SetStatColor(kWhite);
	tdrStyle->SetStatFont(42);
	tdrStyle->SetStatFontSize(0.025);
	tdrStyle->SetStatTextColor(1);
	tdrStyle->SetStatFormat("6.4g");
	tdrStyle->SetStatBorderSize(1);
	tdrStyle->SetStatH(0.1);
	tdrStyle->SetStatW(0.15);
	// tdrStyle->SetStatStyle(Style_t style = 1001);
	// tdrStyle->SetStatX(Float_t x = 0);
	// tdrStyle->SetStatY(Float_t y = 0);

	// Margins:
	tdrStyle->SetPadTopMargin(0.1);
	//tdrStyle->SetPadTopMargin(0.04);
	tdrStyle->SetPadBottomMargin(0.16);
	tdrStyle->SetPadLeftMargin(0.16);
	tdrStyle->SetPadRightMargin(0.05);

	// For the Global title:
	tdrStyle->SetTextSize(0.04);
	tdrStyle->SetOptTitle(0);
	tdrStyle->SetTitleFont(42);
	tdrStyle->SetTitleColor(1);
	tdrStyle->SetTitleTextColor(1);
	tdrStyle->SetTitleFillColor(10);
	tdrStyle->SetTitleFontSize(0.05);
	// tdrStyle->SetTitleH(0); // Set the height of the title box
	// tdrStyle->SetTitleW(0); // Set the width of the title box
	// tdrStyle->SetTitleX(0); // Set the position of the title box
	// tdrStyle->SetTitleY(0.985); // Set the position of the title box
	// tdrStyle->SetTitleStyle(Style_t style = 1001);
	// tdrStyle->SetTitleBorderSize(2);

	// For the axis titles:

	tdrStyle->SetTitleColor(1, "XYZ");
	tdrStyle->SetTitleFont(42, "XYZ");
	tdrStyle->SetTitleSize(0.06, "XYZ");
	// tdrStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
	// tdrStyle->SetTitleYSize(Float_t size = 0.02);
	tdrStyle->SetTitleXOffset(1);
	tdrStyle->SetTitleYOffset(1.25);
	// tdrStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset

	// For the axis labels:

	tdrStyle->SetLabelColor(1, "XYZ");
	tdrStyle->SetLabelFont(42, "XYZ");
	tdrStyle->SetLabelOffset(0.007, "XYZ");
	tdrStyle->SetLabelSize(0.05, "XYZ");

	// For the axis:

	tdrStyle->SetAxisColor(1, "XYZ");
	tdrStyle->SetStripDecimals(kTRUE);
	tdrStyle->SetTickLength(0.03, "XYZ");
	tdrStyle->SetNdivisions(510, "XYZ");
	tdrStyle->SetPadTickX(1); // To get tick marks on the opposite side of the frame
	tdrStyle->SetPadTickY(1);

	//// Change for log plots:
	//  tdrStyle->SetOptLogx(0);
	//  tdrStyle->SetOptLogy(0);
	//  tdrStyle->SetOptLogz(0);

	// Postscript options:
	tdrStyle->SetPaperSize(20., 20.);
	// tdrStyle->SetLineScalePS(Float_t scale = 3);
	// tdrStyle->SetLineStyleString(Int_t i, const char* text);
	// tdrStyle->SetHeaderPS(const char* header);
	// tdrStyle->SetTitlePS(const char* pstitle);

	// tdrStyle->SetBarOffset(Float_t baroff = 0.5);
	// tdrStyle->SetBarWidth(Float_t barwidth = 0.5);
	// tdrStyle->SetPaintTextFormat(const char* format = "g");
	// tdrStyle->SetPalette(Int_t ncolors = 0, Int_t* colors = 0);
	// tdrStyle->SetTimeOffset(Double_t toffset);
	// tdrStyle->SetHistMinimumZero(kTRUE);

	//tdrStyle->cd();

	Int_t fPaletteColor[50] = { 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62,
			63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
			80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96,
			97, 98, 99, 100 };
	gStyle->SetPalette(50, fPaletteColor);

}


void useMyStyle() {
	Int_t fPaletteColor[50] = { 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62,
			63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
			80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96,
			97, 98, 99, 100 };
	gStyle->SetPalette(50, fPaletteColor);
	gErrorIgnoreLevel = 1001;

	TStyle *myStyle = new TStyle("myStyle", "Style for my Plots");
	//setTDRStyle();


	myStyle->SetPalette(1, 0);
	myStyle->SetHistLineWidth(2);
	myStyle->SetCanvasBorderMode(0);
	myStyle->SetPadBorderMode(0);
	myStyle->SetPadColor(10);
	myStyle->SetFrameFillColor(10);
	myStyle->SetFrameBorderMode(0);
	myStyle->SetCanvasColor(10);
	myStyle->SetTitleColor(1);
	myStyle->SetStatColor(10);
	myStyle->SetStatTextColor(1);
	myStyle->SetOptTitle(1);
	myStyle->SetTitleSize(0.06, "XY");
	myStyle->SetLabelSize(0.05, "XY");
	myStyle->SetTitleOffset(1.2, "XY");
	myStyle->SetPadBottomMargin(0.2);
	myStyle->SetPadLeftMargin(0.2);
	myStyle->SetPadRightMargin(0.15);

	//myStyle->SetPadTickX(1);
	//myStyle->SetPadTickY(1);
	//myStyle->SetOptStat(110000);
	myStyle->SetOptTitle(1);
	myStyle->SetTitleFillColor(0);
	myStyle->SetTitleTextColor(1);
	myStyle->SetTitleBorderSize(0);
	myStyle->SetTitleStyle(1);
	//myStyle->SetCanvasDefH(600); //Height of canvas
	//myStyle->SetCanvasDefW(600); //Width of canvas
	//myStyle->SetCanvasDefX(0);   //POsition on screen
	//myStyle->SetCanvasDefY(0);

	myStyle->SetMarkerSize(2);

}
void drawStatPave(int nr, TH1F* histo, TCanvas* c) {

	if (gStyle->GetOptStat() != 0) {
		c->Update();
		TPaveStats *s = (TPaveStats*) histo->GetListOfFunctions()->FindObject(
				"stats");
		if (s != NULL) {
			if (nr == 1) {
				s->SetY1NDC(0.835);
				s->SetY2NDC(0.995);
			}
			if (nr == 2) {
				s->SetY1NDC(0.635);
				s->SetY2NDC(0.795);
			}
			if (nr == 3) {
				s->SetY1NDC(0.435);
				s->SetY2NDC(0.595);
			}
			if (nr == 4) {
				s->SetY1NDC(0.235);
				s->SetY2NDC(0.395);
			}
			if (nr == 5) {
				s->SetY1NDC(0.035);
				s->SetY2NDC(0.195);
			}
			s->SetX1NDC(0.78);
			s->SetX2NDC(0.98);
			s->SetLineColor(histo->GetLineColor());
			s->Draw("samebr");
			c->Update();
		}
	}
}
string getStringFromInt(int i) {
	//---------
	//	if (i < 2) {
	//		return "";
	//	}
	//cout<<"i"<<i<<endl;
	char result[100];
	sprintf(result, "%d", i);
	string ret = result;
	return " " + ret;
	//---------
}
double roundDouble(double xin = 0, int n = 2) {
	double d = pow(10.0, n);
	double x = floor(xin * d + 0.5) / d;
	//	if(x==0){
	//		double d=pow(10.0, 3);
	//		x=floor(xin*d+0.5)/d;
	//	}
	return x;
}
string getStringFromDouble(double i, int n = 1) {
	//---------
	if(i<0.05&&n==1)n=n+1;
	i = roundDouble(i,n);
	char result[100];
	if (n == 4)
		sprintf(result, "%1.4f", i);
	if (n == 3)
		sprintf(result, "%1.3f", i);
	if (n == 2)
		sprintf(result, "%1.2f", i);
	if (n == 1)
		sprintf(result, "%1.1f", i);
	if (n == 0)
		sprintf(result, "%1.0f", i);

	return result;
	//---------
}

string getStringFromDoubleMin(double i, int n = 1) {
	//---------
	if(i>=10)n=0;
	string result=getStringFromDouble(i,n);
	if(i<=0.01)result="'\\'ensuremath{'\\'leq 0.01}";
	return result;
	//---------
}

string getStringFromDoubleN(double i, int n) {
	//---------
	i = roundDouble(i, n);
	char result[100];
	sprintf(result, "%1.4f", i);
	//cout<<"resultL:"<<result<<endl;
	return result;
	//---------
}

void drawCmsPrel(double intLumi, string METCut, bool onlyChannelInfo, int noJets, bool isBestjet, string jetLabel = "", bool drawChannelInfo = true, bool drawCMS = false, bool drawLumiOnly = false, bool largerMarginRight=false) {
	//std::cout<<"draw cms prel"<<std::endl;
	intLumi = intLumi / 1000;

	TLatex as;
	as.SetNDC(true);
	as.SetTextColor(12);
	as.SetTextFont(43);
	as.SetTextSize(20);
	//as.SetTextFont(42);//ms.SetTextColor(12);
	std::string outLumi = "";
	if (drawChannelInfo) {
		//out = "#int #font[12]{L}dt = %.1ffb^{  -1}  #sqrt{s} = 7 TeV";
		outLumi = "%.1ffb^{  -1}  #sqrt{s} = 8 TeV";
	} else {
		//out = "                                     #sqrt{s} = 7 TeV";
		outLumi = "               #sqrt{s} = 8 TeV";
	}

	TLatex as2;
	as2.SetNDC(true);
	as2.SetTextFont(43);
	as2.SetTextSize(22);
	as2.SetTextColor(1);
	std::string out = "";
	if (drawChannelInfo) {
		//1#gamma, >=3 jets, MET>"+getStringFromInt(METCut)+" GeV ";
		out = "#geq1#gamma, #geq" + getStringFromInt(noJets) + " jets";
		if (isBestjet)
			out = "#geq1#gamma, #geq2/3 jets";
		//cout<<"HistoDraw-jetLabel:"<<jetLabel<<endl;
		if (jetLabel != "")
			out = jetLabel;
		if (METCut != "") {
			cout<<"HistoDraw-met Cut:"<<METCut<<endl;
			if (isdigit(METCut[0])) {
				out = out + ", #slash{E}_{T} #geq " + METCut + " GeV";
			} else {
				out = out + ", " + METCut + "";
			}
			cout<<"HistoDraw-out:"<<out<<endl;
		}

	}

	if (drawCMS || METCut == "") {


if(largerMarginRight){
	as.DrawLatex(0.35, 0.905, Form(outLumi.c_str(), intLumi));
			as2.DrawLatex(0.65, 0.905, Form(out.c_str()));
}else{
	as.DrawLatex(0.45, 0.905, Form(outLumi.c_str(), intLumi));
			as2.DrawLatex(0.75, 0.905, Form(out.c_str()));
}
		if (drawCMS) {
			as.SetTextSize(22);
			//			as.DrawLatex(0.16, 0.905, "CMS preliminary"); //VS!!!
			// as.SetTextSize(20);
			// as.DrawLatex(0.18, 0.875, "preliminary");
			// as.DrawLatex(0.0, 0.905, "CMS preliminary");
		}
	} else {

		as.DrawLatex(0.2, 0.905, Form(outLumi.c_str(), intLumi));
		as2.DrawLatex(0.5, 0.905, Form(out.c_str()));
	}
}

void cmsPrel(double intLumi = -1, double pos = 0, bool isData = false,
		bool isMC = false) {
	TLatex latex;
	latex.SetNDC();
	latex.SetTextSize(0.04);
	//change lumi to fb
	intLumi=intLumi/1000;
	if (pos == 0) {
		latex.SetTextAlign(11);
		latex.DrawLatex(0.65, 0.75, "#font[22]{CMS preliminary}");
		if (isData) {
			latex.SetTextAlign(11);
			if (isData && !isMC)
				latex.DrawLatex(0.65, 0.65, "Data   #sqrt{s} = 8 TeV");
			else
				latex.DrawLatex(0.65, 0.65, "#sqrt{s} = 8 TeV");
		} else {
			latex.DrawLatex(0.65, 0.65, "Sim.   #sqrt{s} = 8 TeV");
		}

		if (intLumi > 0.) {
			latex.SetTextAlign(11); // align right
			latex.DrawLatex(0.65, 0.55, Form(
					"#int #font[12]{L}dt = %.2ffb^{  -1}", intLumi));
		}

	} else if (pos == 1) {
		latex.SetTextAlign(11);
		latex.DrawLatex(0.17, 0.96, "#font[22]{CMS preliminary}");
		latex.SetTextAlign(11);

		if (isData) {
			latex.SetTextAlign(11);
			if (isData && !isMC)
				latex.DrawLatex(0.18, 0.9, "Data #sqrt{s} = 8 TeV");
			else
				latex.DrawLatex(0.18, 0.9, "#sqrt{s} = 8 TeV");
		} else {
			latex.DrawLatex(0.18, 0.9, "Simulation  #sqrt{s} = 8 TeV");
		}

		if (intLumi > 0.) {
			latex.DrawLatex(0.17, 0.82, Form(
					"#int #font[12]{L}dt = %.2ffb^{  -1}", intLumi));
		}

	}

}
TLegend* getLegendSmall(string label = "") {
	return new TLegend(0.76, 0.78, 0.95, 0.97, label.c_str(), "brNDC");
	//legend->SetTextSize(0.03);
}
vector<double> fitGausToPeak(TH1F* h, int linecolor) {

	h->Fit("gaus", "R+", "sames", (h->GetMean()) - (1.5 * h->GetRMS()),
			(h->GetMean()) + (1.5 * h->GetRMS()));
	TF1 *f1 = h->GetFunction("gaus");
	double mean = f1->GetParameter(1);
	double sigma = f1->GetParameter(2);
	f1->SetRange(mean - 3 * sigma, mean + 3 * sigma);
	f1->SetLineColor(linecolor);
	vector<double> result;
	result.push_back(mean);
	result.push_back(sigma);
	return result;
}
void writeStatusBar(int totEvents, double currEvent, int nSteps = 1) {
	double onePerCent = floor(totEvents / 100);
	//cout<<onePerCent<<endl;
	if (fmod(currEvent, nSteps * onePerCent) == 0) {
		int procentCounter = 0;
		if (currEvent != 0)
			procentCounter = (int) floor(currEvent / (nSteps * onePerCent));
		if (procentCounter <= 100) {
			cout << "\r\r";
			cout << "[";
			string blanks((100 - procentCounter), ' ');
			string striche(procentCounter, '-');
			cout << striche << blanks << "]";
			cout << procentCounter << "%";
		}
		if (procentCounter == 100) {
			//cout<<endl;
		}
	}
}
string replaceSubstr(string phrase, string sought, string replacement) {

	int pos = phrase.find(sought); // pos=9
	if ((int) pos != (int) string::npos)
		phrase.replace(pos, sought.size(), replacement);
	return phrase;
}
bool containsSubstr(string phrase, string sought) {

	int pos = phrase.find(sought); // pos=9
	if ((int) pos != (int) string::npos)
		return true;
	else
		return false;
}

string replaceAllBeforeLastOccurenceOf(string phrase, string sought) {
	int pos = phrase.find_last_of(sought); // pos=9
	if ((int) pos != (int) string::npos)
		phrase.replace(0, pos, "");
	return phrase;
}
string replaceAllBeforeFirstOccurenceOf(string phrase, string sought) {
	int pos = phrase.find(sought); // pos=9
	//cout << "PHRASE START: " << phrase << endl;
	if ((int) pos != (int) string::npos) {
		//cout << "PHRASE POS: " << pos << endl;
		phrase.replace(0, pos + sought.size(), "");
	}
	//cout << "PHRASE END: " << phrase << endl;
	return phrase;
}
string replaceAllAfterFirstOccurenceOf(string phrase, string sought) {
	//	cout << "PHRASE START: " << phrase << endl;
	//	cout << "PHRASE SEARCH: " << sought << endl;
	int pos = phrase.find(sought); // pos=9
	if ((int) pos != (int) string::npos) {
		//cout << "PHRASE POS: " << pos << endl;
		phrase.replace(pos, phrase.size() - pos + 1, "");
	}
	//cout << "PHRASE END: " << phrase << endl;
	return phrase;
}

string removeSpaces(string phrase) {
	//cout<<"PHRASE START: "<<phrase<<endl;
	int pos = phrase.find(" ");
	while ((int) pos != (int) string::npos) {
		phrase.replace(pos, 1, "");
		pos = phrase.find(" ");
		//cout<<"PHRASE: "<<phrase<<endl;
	}

	return phrase;
}


class PlotConfig {
public:
	PlotConfig() {
	}
	;
	PlotConfig(double plumi, bool pisMC, string psampleName, string platexname,
			string pdirName, string pfilename, int plinecolor,
			int pmarkerstyle, bool pIsPutOnStack, int pFillcolor = 0,
			int pFillstyle = 0) {
		lumi = plumi;
		isMC = pisMC;
		isPutOnStack = pIsPutOnStack;
		sampleName = psampleName;
		dirName = pdirName;
		linecolor = plinecolor;
		markerstyle = pmarkerstyle;
		fillcolor = pFillcolor;
		fillstyle = pFillstyle;
		filename = pfilename;
		latexname = platexname;
		MConlySyst=0;
	}

	double lumi;
	bool isMC, isPutOnStack;
	double MConlySyst;//==ISRFSR scale factor
	string sampleName, latexname;
	string dirName;
	string filename;
	int linecolor, markerstyle, fillcolor, fillstyle;
};

class FitResultsQCDEst {
public:
	FitResultsQCDEst() {
	}
	;
	FitResultsQCDEst(double pParA, double pParB, double pParC, double pChiProb,
			double pRelErr) {
		parA = pParA;
		parB = pParB;
		parC = pParC;
		chiProb = pChiProb;
		relErr = pRelErr;
	}
	double parA;
	double parB;
	double parC;
	double chiProb;
	double relErr;

};

class EventCounts {
public:

	EventCounts() {
		samplename = "";
		latexname = "";
		noOverflows = 0;

		noEvts = 0;
		systErrUp = 0;
		systErrDown = 0;
		statErr = 0;
		combErr = 0;



	}
	void printRelSystCountsLatex(double totSyst,string filename) {
		 string prefix="";

                if(containsSubstr(filename,"100")){
                        prefix="LOW";
                }
                if(containsSubstr(filename,"350")){
                                        prefix="HI";
                                }
                 if(containsSubstr(filename,"2j")){
                                        prefix="jTWO"+prefix;;
                                }

		string systErrUpStr = "";
		systErrUpStr = systErrUpStr + "echo " + "'\\'def'\\'"+prefix + latexname
				+ "systErrUpRel{" + (string) getStringFromDouble(100
				* systErrUp / totSyst, 1) + "} >> " + filename + ";";
		system((systErrUpStr).c_str());
		string systErrDownStr = "";
		systErrDownStr = systErrDownStr + "echo " + "'\\'def'\\'" +prefix + latexname
				+ "systErrDownRel{" + (string) getStringFromDouble(100
				* systErrDown / totSyst, 1) + "} >> " + filename + ";";
		system((systErrDownStr).c_str());
	}
	void printCountsLatex(string filename) {
		round();
		string prefix="";
		
		if(containsSubstr(filename,"100")){
			prefix="LOW";
		}
		if(containsSubstr(filename,"350")){
					prefix="HI";
				}
		 if(containsSubstr(filename,"2j")){
                                        prefix="jTWO"+prefix;;
                                }
		string noEvtsStr = "";
		if (!isMC&&(latexname!="SMBkgTot")) {
			noEvtsStr = noEvtsStr + "echo " + "'\\'" + "def" + "'\\'"
					+prefix+ latexname + "noEvts{" + (string) getStringFromInt(noEvts)
					+ "} >> " + filename + ";";
		} else {
			noEvtsStr = noEvtsStr + "echo " + "'\\'" + "def" + "'\\'"
					+prefix+ latexname + "noEvts{" + (string) getStringFromDoubleMin(
					noEvts) + "} >> " + filename + ";";
		}
		system((noEvtsStr).c_str());
		string statErrStr = "";
		statErrStr = statErrStr + "echo " + "'\\'def'\\'"+prefix + latexname
				+ "statErr{" + (string) getStringFromDoubleMin(statErr) + "} >> "
				+ filename + "";
		system((statErrStr).c_str());

		string systErrUpStr = "";
		systErrUpStr = systErrUpStr + "echo " + "'\\'def'\\'"+prefix + latexname
				+ "systErrUp{" + (string) getStringFromDoubleMin(systErrUp)
				+ "} >> " + filename + ";";
		system((systErrUpStr).c_str());

		string systErrDownStr = "";
		systErrDownStr = systErrDownStr + "echo " + "'\\'def'\\'" +prefix+ latexname
				+ "systErrDown{" + (string) getStringFromDoubleMin(systErrDown)
				+ "} >> " + filename + ";";
		system((systErrDownStr).c_str());

	}
	;
	void round(int n = 2){
		//if(noEvts){}else
		noEvts = roundDouble(noEvts, n);
		systErrUp = roundDouble(systErrUp, n+1);
		systErrDown = roundDouble(systErrDown, n+1);
		noOverflows = roundDouble(noOverflows, n);
		statErr = roundDouble(statErr, n);
		combErr = roundDouble(combErr, n);
		if(!(systErrUp<0.1)){systErrUp = roundDouble(systErrUp, n);}
		if(!(systErrDown<0.1)){systErrDown = roundDouble(systErrDown, n);}
	}
	void printCounts() {
		combErr = sqrt(statErr * statErr + systErrUp * systErrUp);
		cout << samplename << ":" << noEvts << "+/- " << systErrUp
				<< " (syst.) +/- " << statErr << " (stat.)" << endl;
		if (noOverflows > 0 && !isMC) {
			cout << "WARNING - histogram has entries in overflow bin!!!"
					<< endl;
		}

	}
	;
	string samplename, latexname;
	double noEvts;
	double systErrUp;
	double statErr;
	double combErr;
	double systErrDown;
	double noOverflows;
	bool isMC;

};



}

#endif
