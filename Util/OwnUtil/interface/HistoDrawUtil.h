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


/*
 * namespace is used for definition of Constants,
 * file configurations, Variables, etc
 */
namespace HistoDrawUtil {

// fixOverlay: Redraws the axis


// tdrGrid: Turns the grid lines on (true) or off (false)

void tdrGrid(bool gridOn, TStyle *tdrStyle);

// fixOverlay: Redraws the axis

void fixOverlay();


void setMyTDRStyle();

void useMyStyle();
void drawStatPave(int nr, TH1F* histo, TCanvas* c);
std::string getStringFromInt(int i);
double roundDouble(double xin, int n =1);
std::string getStringFromDouble(double i, int n = 1);

std::string getStringFromDoubleMin(double i, int n = 1);

std::string getStringFromDoubleN(double i, int n);

void drawCmsPrel(double intLumi, std::string METCut, bool onlyChannelInfo, int noJets, bool isBestjet, std::string jetLabel = "", bool drawChannelInfo = true, bool drawCMS = false, bool drawLumiOnly = false, bool largerMarginRight=false);

void cmsPrel(double intLumi = -1, double pos = 0, bool isData = false,
		bool isMC = false);
TLegend* getLegendSmall(std::string label = "");
std::vector<double> fitGausToPeak(TH1F* h, int linecolor);
void writeStatusBar(int totEvents, double currEvent, int nSteps = 1);
std::string replaceSubstr(std::string phrase, std::string sought, std::string replacement);
bool containsSubstr(std::string phrase, std::string sought);

std::string replaceAllBeforeLastOccurenceOf(std::string phrase, std::string sought);
std::string replaceAllBeforeFirstOccurenceOf(std::string phrase, std::string sought);
std::string replaceAllAfterFirstOccurenceOf(std::string phrase, std::string sought);

std::string removeSpaces(std::string phrase);


class PlotConfig {
public:
	PlotConfig() {
	}
	;
	PlotConfig(double plumi, bool pisMC, std::string psampleName, std::string platexname,
			std::string pdirName, std::string pfilename, int plinecolor,
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
	std::string sampleName, latexname;
	std::string dirName;
	std::string filename;
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
	void printRelSystCountsLatex(double totSyst,std::string filename) {
		 std::string prefix="";

                if(containsSubstr(filename,"100")){
                        prefix="LOW";
                }
                if(containsSubstr(filename,"350")){
                                        prefix="HI";
                                }
                 if(containsSubstr(filename,"2j")){
                                        prefix="jTWO"+prefix;;
                                }

		std::string systErrUpStr = "";
		systErrUpStr = systErrUpStr + "echo " + "'\\'def'\\'"+prefix + latexname
				+ "systErrUpRel{" + (std::string) getStringFromDouble(100
				* systErrUp / totSyst, 1) + "} >> " + filename + ";";
		system((systErrUpStr).c_str());
		std::string systErrDownStr = "";
		systErrDownStr = systErrDownStr + "echo " + "'\\'def'\\'" +prefix + latexname
				+ "systErrDownRel{" + (std::string) getStringFromDouble(100
				* systErrDown / totSyst, 1) + "} >> " + filename + ";";
		system((systErrDownStr).c_str());
	}
	void printCountsLatex(std::string filename) {
		round();
		std::string prefix="";
		
		if(containsSubstr(filename,"100")){
			prefix="LOW";
		}
		if(containsSubstr(filename,"350")){
					prefix="HI";
				}
		 if(containsSubstr(filename,"2j")){
                                        prefix="jTWO"+prefix;;
                                }
		std::string noEvtsStr = "";
		if (!isMC&&(latexname!="SMBkgTot")) {
			noEvtsStr = noEvtsStr + "echo " + "'\\'" + "def" + "'\\'"
					+prefix+ latexname + "noEvts{" + (std::string) getStringFromInt(noEvts)
					+ "} >> " + filename + ";";
		} else {
			noEvtsStr = noEvtsStr + "echo " + "'\\'" + "def" + "'\\'"
					+prefix+ latexname + "noEvts{" + (std::string) getStringFromDoubleMin(
					noEvts) + "} >> " + filename + ";";
		}
		system((noEvtsStr).c_str());
		std::string statErrStr = "";
		statErrStr = statErrStr + "echo " + "'\\'def'\\'"+prefix + latexname
				+ "statErr{" + (std::string) getStringFromDoubleMin(statErr) + "} >> "
				+ filename + "";
		system((statErrStr).c_str());

		std::string systErrUpStr = "";
		systErrUpStr = systErrUpStr + "echo " + "'\\'def'\\'"+prefix + latexname
				+ "systErrUp{" + (std::string) getStringFromDoubleMin(systErrUp)
				+ "} >> " + filename + ";";
		system((systErrUpStr).c_str());

		std::string systErrDownStr = "";
		systErrDownStr = systErrDownStr + "echo " + "'\\'def'\\'" +prefix+ latexname
				+ "systErrDown{" + (std::string) getStringFromDoubleMin(systErrDown)
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
		std::cout << samplename << ":" << noEvts << "+/- " << systErrUp
				<< " (syst.) +/- " << statErr << " (stat.)" << std::endl;
		if (noOverflows > 0 && !isMC) {
			std::cout << "WARNING - histogram has entries in overflow bin!!!"
					<< std::endl;
		}

	}
	;
	std::string samplename, latexname;
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
