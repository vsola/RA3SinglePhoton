#ifndef CUTOPTIMIZER_H_
#define CUTOPTIMIZER_H_
#include <string>
#include <TH1F.h>
#include <TH1.h>
#include <TAxis.h>
using namespace std;
/*
 * This namespace carries classes and methods needed for optimizing of cuts.
 * 
 */
namespace CutOptimizer {
enum CompType
{
	diff,
	sgToBg,
	sgToSqrtBg
};
/*
 * This class carries the value of signal/sqrt(bg) and the belonging upper and lower cut
 * 
 */
class CutVariables {
public:
	CutVariables() {
		name_="";
		maxSB_=0;
		cut1x_=0;
		cut2x_=0;
		cutBin1x_=0;
		cutBin2x_=0;
		isValid_=false;

	}
	;
	CutVariables(double maxSB, double cut1x, double cut2x, int cutBin1x,
			int cutBin2x) {
		maxSB_=maxSB;
		cut1x_=cut1x;
		cut2x_=cut2x;
		cutBin1x_=cutBin1x;
		cutBin2x_=cutBin2x;
		name_="";
		isValid_=true;
	}
	;

	~CutVariables() {

	}
	;
	void setName(string name) {
		name_=name;
	}
	;
	string getName() {
		return name_;
	}
	;
	double getSB() {
		return maxSB_;
	}
	;
	double getCut1() {
		return cut1x_;
	}
	;
	double getCut2() {
		return cut2x_;
	}
	;
	double getBin1() {
		return cutBin1x_;
	}
	;
	double getBin2() {
		return cutBin2x_;
	}
	;
	void setCut1(double iCut) {
		cut1x_=iCut;
	}
	;
	void setCut2(double iCut) {
		cut2x_=iCut;
	}
	;
	void setValid(bool iValid) {
		isValid_=iValid;
	}
	;
	bool isValid() {
		return isValid_;
	}
	;
private:
	double maxSB_;
	double cut1x_;
	double cut2x_;
	int cutBin1x_;
	int cutBin2x_;
	string name_;
	bool isValid_;
};
double getIntegralError(TH1F * signal,int bin1=0, int bin2=-1){
	double err=0;
	if(bin1<0){
			bin1=0;
		}
	if(bin2<bin1){
		bin2=signal->GetNbinsX()+1;
	}
	for(int b=bin1;b<=bin2;++b){
		err+=signal->GetBinError(b)*signal->GetBinError(b);
	}
	return sqrt(err);
}
/*
 * This method determines the upper and lower cut for selection of optimum sg/sqrt(bg) value
 * 
 * parameter: - signal and background histo 
 *            - bool onlyUpper/LowerCur
 * returns: -'CutVariables' filled with optimal cut values for maximum value of Efficiency*Purity (N_s/sqrt(N_bg))
 *   		- allvalues in CutVariables = 0 if histograms have same binning or one of them is NULL!
 * */
CutVariables* getOptCuts(TH1F* signal, TH1F* background,
		bool onlyLowerCut=false, bool onlyUpperCut=false,
		CompType pCompType=sgToSqrtBg) {

	if (onlyUpperCut&&onlyLowerCut) {
		cout
				<<"ERROR - getOptCuts called - but no cut should be done?! (onlyLowerCut and onlyUpperCut are true)"
				<<endl;
	}

	CutVariables* cutVars=new CutVariables();

	//validate parameters
	if (signal==NULL||background==NULL) {
		cout<<"ERROR - CutOptimizer getOptCuts called with NULL - Histograms!"
				<<endl;
		return cutVars;
	}

	int numberBinsSignal=signal->GetNbinsX();
	int numberBinsBg=background->GetNbinsX();

	if (numberBinsBg!=numberBinsSignal) {
		cout
				<<"ERROR - CutOptimizer getOptCuts called with histograms having different binning!"
				<<endl;
		return cutVars;
	}

	if (signal->GetEntries()==0 && background->GetEntries()==0) {
		cout <<"ERROR - CutOptimizer getOptCuts called with empty Histograms!"
				<<endl;
		return cutVars;
	}
	TAxis* xAxis=signal->GetXaxis();

	//set start values

	double opt_SB=0;
	double opt_cut1;
	double opt_cut2;
	int opt_bin1;
	int opt_bin2;
//	signal->Scale(1/signal->Integral());
//	background->Scale(1/background->Integral());
	double totalBgIntegral=background->Integral();
	Double_t totalSgIntegralErr=0;
	double totalSgIntegral=signal->Integral();
	//cout<<"total sig +/- bkg:"<<totalSgIntegral<<" +/- "<<getIntegralError(signal)<<endl;

	for (int bin_1=0; bin_1<numberBinsSignal; bin_1++) {
		//cout<<"bin 1:"<<bin_1<<endl;
		for (int bin_2=numberBinsSignal+1; bin_2>bin_1; bin_2--) {
			//cout<<"bin 2:"<<bin_2<<endl;
			double trueIntegral=signal->Integral(bin_1, bin_2,"");
			double trueIntegralErr=getIntegralError(signal,bin_1, bin_2);
			double falseIntegral=background->Integral(bin_1, bin_2,"");
			double falseIntegralErr=getIntegralError(background,bin_1, bin_2);
			//cout<<"trueIntegral "<<signal->Integral()<<endl;
			//cout<<"falseIntegral "<<background->Integral()<<endl;
			//double SB_temp=trueIntegral/falseIntegral;//sqrt(falseIntegral);
			double SB_temp;
			if (pCompType==diff) {
				if (falseIntegral==0) {
					//falseIntegral=1/background->Integral("");

				}
				//				if (falseIntegral<1) {
				//					SB_temp=(trueIntegral-falseIntegral)*((falseIntegral
				//							*falseIntegral));
				//				} else
				//(totalSgIntegral/totalBgIntegral)*
				SB_temp=(((trueIntegral)-(falseIntegral)));//((sqrt(falseIntegral+trueIntegral)));
				//SB_temp=(trueIntegral-falseIntegral);
			} else if (pCompType==sgToBg) {
				if (falseIntegral==0) {
					falseIntegral=1/background->Integral();

				}
				if (falseIntegral==0) {
					SB_temp=trueIntegral;
				} else
					SB_temp=trueIntegral/falseIntegral;
			} else if (pCompType==sgToSqrtBg) {
				if (falseIntegral==0) {
					falseIntegral=1/background->Integral();

				}

				SB_temp=trueIntegral/(sqrt(trueIntegral+falseIntegral));
			}
//			cout<<"trueIntegral "<<trueIntegral<<endl;
//			cout<<"falseIntegral "<<falseIntegral<<endl;

			//cout<<"SB temp "<<SB_temp<<endl;
			//if new SB-value is bigger than the old one - save it.
			if (SB_temp>=opt_SB) {
				opt_SB = SB_temp;
//				cout
//						<< "New Best Ratio(cuts):---------------------------------"
//						<< opt_SB << endl;
				//get value of cuts in axis units not in bins!
				opt_cut1=xAxis->GetBinLowEdge(bin_1);
				opt_cut2=xAxis->GetBinUpEdge(bin_2);
				opt_bin1=bin_1;
				opt_bin2=bin_2;
//				cout<<"trueIntegral= "<<trueIntegral<<" +/- "<<trueIntegralErr<<endl;
//				cout<<"bgIntegral= "<<falseIntegral<<" +/- "<<falseIntegralErr<<endl;
//				cout<<"bin_1 "<<bin_1<<endl;
//				cout<<"bin_2 "<<bin_2<<endl;
//				cout<<"optCut1 "<<opt_cut1<<endl;
//				cout<<"optCut2 "<<opt_cut2<<endl;
			}

			//if only one lower cut should be used break here
			if (onlyLowerCut) {
				//cout<<"onlyLowerCut"<<endl;
				break;
			}

		}
		//if only one Upper cut should be used break here
		if (onlyUpperCut) {
			break;
		}
	}
	//set opt values in container and return it
	//cout<<"optCut1 "<<opt_cut1<<endl;
	//cout<<"optCut2 "<<opt_cut2<<endl;
	//cout<<"optSB "<<opt_SB<<endl;
	cutVars=new CutVariables(opt_SB,opt_cut1,opt_cut2,opt_bin1,opt_bin2);
	return cutVars;
}

}
#endif /*CUTOPTIMIZER_H_*/
