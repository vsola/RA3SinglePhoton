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
void BEFilterHistos() {
	HistoDrawUtil::setMyTDRStyle();
		gROOT->SetStyle("mytdrStyle");
		gStyle->UseCurrentStyle();
	TFile *_file0 = TFile::Open("punchThroughTree4.root");
	TTree * newtree=_file0->FindObjectAny("ptTree");
	gStyle->UseCurrentStyle();
	if(true){
	string name = "BEVariousTPs_EB";
				TCanvas * c = new TCanvas(name.c_str(), name.c_str());
				gPad->SetLogy(1);
				TH1F * beVsTp10 = new TH1F("beVsTp10",
						"beVsTp10;boundary energy [GeV];", 75, 0, 150);

				newtree->Draw("anEcalVars.v_boundaryInfoDeadCells_EB.boundaryEnergy>>beVsTp10(75, 0, 150)","anEcalVars.v_boundaryInfoDeadCells_EB.channelStatus==13&&anEcalVars.v_boundaryInfoDeadCells_EB.tpEt<10&&anEcalVars.v_boundaryInfoDeadCells_EB.recHits[].energy_>10","");
				gPad->Update();
				c->Update();
				beVsTp10 = (TH1F*) gPad->GetPrimitive("beVsTp10");
				gPad->Update();
				c->Update();
				if (beVsTp10 != 0) {
					beVsTp10->SetXTitle("BE E_{T}[GeV]");
					beVsTp10->SetYTitle("fraction of events / 2 GeV");
					beVsTp10->Scale(1/beVsTp10->Integral());
					beVsTp10->SetLineWidth(2);
					beVsTp10->Draw("");
					c->Update();
					gPad->Update();
				}
				TH1F * beVsTp30 = new TH1F("beVsTp30",
						"beVsTp30;BE E_{T} [GeV];", 75, 0, 150);

				newtree->Draw(
						"anEcalVars.v_boundaryInfoDeadCells_EB.boundaryEnergy>>beVsTp30(75, 0, 150)",
						"anEcalVars.v_boundaryInfoDeadCells_EB.channelStatus==13&&anEcalVars.v_boundaryInfoDeadCells_EB.tpEt<40&&anEcalVars.v_boundaryInfoDeadCells_EB.tpEt>30&&anEcalVars.v_boundaryInfoDeadCells_EB.recHits[].energy_>10",
						"same");
				//&&anEcalVars.v_boundaryInfoDeadCells_EB.@recHits.size()>23&&anEcalVars.v_boundaryInfoDeadCells_EB.@recHits.size()<28
				gPad->Update();
				c->Update();
				beVsTp30 = (TH1F*) gPad->GetPrimitive("beVsTp30");
				gPad->Update();
				c->Update();
				if (beVsTp30 != 0) {
					beVsTp30->SetLineColor(2);
					beVsTp30->SetXTitle("boundary energy [GeV]");
					beVsTp30->Scale(1/beVsTp30->Integral());
					beVsTp30->SetLineWidth(2);
					beVsTp30->Draw("same");
					c->Update();
					gPad->Update();
				}
//				TH1F * beVsTp40 = new TH1F("beVsTp40",
//										"beVsTp40;BE E_{T} [GeV];", 75, 0, 150);
//
//								newtree->Draw(
//										"anEcalVars.v_boundaryInfoDeadCells_EB.boundaryEnergy>>beVsTp40(75, 0, 150)",
//										"anEcalVars.v_boundaryInfoDeadCells_EB.channelStatus==13&&anEcalVars.v_boundaryInfoDeadCells_EB.tpEt<60&&anEcalVars.v_boundaryInfoDeadCells_EB.tpEt>50",
//										"same");
//								gPad->Update();
//								c->Update();
//								beVsTp40 = (TH1F*) gPad->GetPrimitive("beVsTp40");
//								gPad->Update();
//								c->Update();
//								if (beVsTp40 != 0) {
//									beVsTp40->SetLineColor(2);
//									beVsTp40->SetXTitle("boundary energy [GeV]");
//									beVsTp40->Scale(1/beVsTp40->Integral());
//									beVsTp40->SetLineWidth(2);
//									beVsTp40->Draw("same");
//									c->Update();
//									gPad->Update();
//								}
				TH1F * beVsTp60 = new TH1F("beVsTp60",
						"beVsTp60;BE E_{T} [GeV];", 75, 0, 150);

				newtree->Draw("anEcalVars.v_boundaryInfoDeadCells_EB.boundaryEnergy>>beVsTp60(75, 0, 150)","anEcalVars.v_boundaryInfoDeadCells_EB.channelStatus==13&&anEcalVars.v_boundaryInfoDeadCells_EB.tpEt>63&&anEcalVars.v_boundaryInfoDeadCells_EB.recHits[].energy_>10","same");
				gPad->Update();
				c->Update();
				beVsTp60 = (TH1F*) gPad->GetPrimitive("beVsTp60");
				gPad->Update();
				c->Update();
				if (beVsTp60 != 0) {
					beVsTp60->SetLineColor(4);
					beVsTp60->SetXTitle("BE E_{T}[GeV]");
					beVsTp60->SetYTitle("fraction of events / 2 GeV");
					beVsTp60->Scale(1/beVsTp60->Integral());
					beVsTp60->SetLineWidth(2);
					beVsTp60->Draw("same");
					c->Update();
					gPad->Update();
				}
				TLegend *legend = new TLegend(0.535, 0.776, 0.947, 0.945, "");
							legend->SetFillColor(0);
							legend->AddEntry(beVsTp10, "TP E_{T} < 10 GeV", "l");
							//legend->AddEntry(beVsTp30, "30 GeV < TP E_{T} > 40 GeV", "l");
							legend->AddEntry(beVsTp60, "TP E_{T} > 63 GeV", "l");

							legend->Draw("same");
				///
				c->Update();
	}
	if(false){
		string name = "BEVariousTPs_EE";
					TCanvas * c = new TCanvas(name.c_str(), name.c_str());
					gPad->SetLogy(1);
					TH1F * beVsTp10 = new TH1F("beVsTp10",
							"beVsTp10;boundary energy [GeV];", 75, 0, 150);

					newtree->Draw(
							"anEcalVars.v_boundaryInfoDeadCells_EE.boundaryEnergy>>beVsTp10(75, 0, 150)","anEcalVars.v_boundaryInfoDeadCells_EE.tpEt<10","");
					gPad->Update();
					c->Update();
					beVsTp10 = (TH1F*) gPad->GetPrimitive("beVsTp10");
					gPad->Update();
					c->Update();
					if (beVsTp10 != 0) {
						beVsTp10->SetXTitle("BE E_{T} [GeV]");
						beVsTp10->Scale(1/beVsTp10->Integral());
						beVsTp10->SetLineWidth(2);
						beVsTp10->Draw("");
						c->Update();
						gPad->Update();
					}
					TH1F * beVsTp30 = new TH1F("beVsTp30",
							"beVsTp30;BE E_{T} [GeV];", 75, 0, 150);

					newtree->Draw(
							"anEcalVars.v_boundaryInfoDeadCells_EE.boundaryEnergy>>beVsTp30(75, 0, 150)",
							"anEcalVars.v_boundaryInfoDeadCells_EE.tpEt<40&&anEcalVars.v_boundaryInfoDeadCells_EE.tpEt>30",
							"same");
					gPad->Update();
					c->Update();
					beVsTp30 = (TH1F*) gPad->GetPrimitive("beVsTp30");
					gPad->Update();
					c->Update();
					if (beVsTp30 != 0) {
						beVsTp30->SetLineColor(2);
						beVsTp30->SetXTitle("boundary energy [GeV]");
						beVsTp30->Scale(1/beVsTp30->Integral());
						beVsTp30->SetLineWidth(2);
						beVsTp30->Draw("same");
						c->Update();
						gPad->Update();
					}
					TH1F * beVsTp60 = new TH1F("beVsTp60",
							"beVsTp60;BE E_{T} [GeV];", 75, 0, 150);

					newtree->Draw(
							"anEcalVars.v_boundaryInfoDeadCells_EE.boundaryEnergy>>beVsTp60(75, 0, 150)",
							"anEcalVars.v_boundaryInfoDeadCells_EE.tpEt>63",
							"same");
					gPad->Update();
					c->Update();
					beVsTp60 = (TH1F*) gPad->GetPrimitive("beVsTp60");
					gPad->Update();
					c->Update();
					if (beVsTp60 != 0) {
						beVsTp60->SetLineColor(4);
						beVsTp60->SetXTitle("boundary energy [GeV]");
						beVsTp60->Scale(1/beVsTp60->Integral());
						beVsTp60->SetLineWidth(2);
						beVsTp60->Draw("same");
						c->Update();
						gPad->Update();
					}
					TLegend *legend = new TLegend(0.535, 0.776, 0.947, 0.945, "");
												legend->SetFillColor(0);
												legend->AddEntry(beVsTp10, "TP E_{T} < 10 GeV", "l");
												legend->AddEntry(beVsTp30, "30 GeV < TP E_{T} > 40 GeV", "l");
												legend->AddEntry(beVsTp60, "TP E_{T} > 63 GeV", "l");

												legend->Draw("same");
					///
					c->Update();
		}
}

//void writeBEFilterHistos() {
//		cout << "init Tree" << endl;
//		//			PtTreeVariables * ptVariablesNew =  new PtTreeVariables();
//		//			newtree->SetBranchAddress("ptVariables", &ptVariablesNew);
//		if (true) {
//			//======================
//			string name = "BEVariousTPs_EB";
//			TCanvas * c = new TCanvas(name.c_str(), name.c_str());
//			TH1F * beVsTp10 = new TH1F("beVsTp10",
//					"beVsTp10;boundary energy [GeV];TP E_{T}[GeV];", 300, 0,
//					300);
//
//			newtree->Draw(
//					"anEcalVars.v_boundaryInfoDeadCells_EB.boundaryEnergy>>beVsTp10(300, 0, 300)","anEcalVars.v_boundaryInfoDeadCells_EB.channelStatus==13&&anEcalVars.v_boundaryInfoDeadCells_EB.tpEt<10","");
//			gPad->Update();
//			c->Update();
//			beVsTp10 = (TH1F*) gPad->GetPrimitive("beVsTp10");
//			gPad->Update();
//			c->Update();
//			if (beVsTp10 != 0) {
//				beVsTp10->SetXTitle("boundary energy [GeV]");
//				beVsTp10->SetYTitle("TP E_{T} [GeV]");
//				beVsTp10->Draw("");
//				c->Update();
//				gPad->Update();
//			}
//			TH1F * beVsTp30 = new TH1F("beVsTp30",
//					"beVsTp30;boundary energy [GeV];TP E_{T}[GeV];", 300, 0,
//					300);
//
//			newtree->Draw(
//					"anEcalVars.v_boundaryInfoDeadCells_EB.boundaryEnergy>>beVsTp30(300, 0, 300)",
//					"anEcalVars.v_boundaryInfoDeadCells_EB.channelStatus==13&&anEcalVars.v_boundaryInfoDeadCells_EB.tpEt<40&&anEcalVars.v_boundaryInfoDeadCells_EB.tpEt>30",
//					"");
//			gPad->Update();
//			c->Update();
//			beVsTp30 = (TH1F*) gPad->GetPrimitive("beVsTp30");
//			gPad->Update();
//			c->Update();
//			if (beVsTp30 != 0) {
//				beVsTp30->SetLineColor(2);
//				beVsTp30->SetXTitle("boundary energy [GeV]");
//				beVsTp30->SetYTitle("TP E_{T} [GeV]");
//				beVsTp30->Draw("same");
//				c->Update();
//				gPad->Update();
//			}
//			TH1F * beVsTp60 = new TH1F("beVsTp60",
//					"beVsTp60;boundary energy [GeV];TP E_{T}[GeV];", 300, 0,
//					300);
//
//			newtree->Draw(
//					"anEcalVars.v_boundaryInfoDeadCells_EB.boundaryEnergy>>beVsTp60(300, 0, 300)",
//					"anEcalVars.v_boundaryInfoDeadCells_EB.channelStatus==13&&anEcalVars.v_boundaryInfoDeadCells_EB.tpEt>63",
//					"");
//			gPad->Update();
//			c->Update();
//			beVsTp60 = (TH1F*) gPad->GetPrimitive("beVsTp60");
//			gPad->Update();
//			c->Update();
//			if (beVsTp60 != 0) {
//				beVsTp60->SetLineColor(4);
//				beVsTp60->SetXTitle("boundary energy [GeV]");
//				beVsTp60->SetYTitle("TP E_{T} [GeV]");
//				beVsTp60->Draw("same");
//				c->Update();
//				gPad->Update();
//			}
//
//			///
//			c->Update();
//			newfile->WriteTObject(c, 0, "overwrite");
//			delete c;
//		}
//		if (true) {
//			//======================
//			string name = "BEvsTP_EB";
//			TCanvas * c = new TCanvas(name.c_str(), name.c_str());
//			TH2F * beVsTp = new TH2F("bevstpEB",
//					"bevstpEB;boundary energy [GeV];TP E_{T}[GeV];", 300, 0,
//					700, 100, 0, 70);
//			cout << "draw BEVSTP!" << endl;
//			newtree->Draw("anEcalVars.v_boundaryInfoDeadCells_EB.tpEt:anEcalVars.v_boundaryInfoDeadCells_EB.boundaryEnergy>>bevstpEB(300, 0, 700,	100, 0, 70)","anEcalVars.v_boundaryInfoDeadCells_EB.channelStatus==13&&anEcalVars.v_boundaryInfoDeadCells_EB.tpEt>5","box");
//			cout << "=draw BEVSTP!" << endl;
//			gPad->Update();
//			c->Update();
//			cout << "read BEVSTP!" << endl;
//			beVsTp = (TH2F*) gPad->GetPrimitive("bevstpEB");
//			gPad->Update();
//			c->Update();
//			if (beVsTp != 0) {
//				cout << "BEVSTP!" << beVsTp->GetEntries() << endl;
//				beVsTp->SetXTitle("boundary energy [GeV]");
//				beVsTp->SetYTitle("TP E_{T} [GeV]");
//				beVsTp->Draw("BOX");
//
//				c->Update();
//				gPad->Update();
//			}
//			c->Update();
//			newfile->WriteTObject(c, 0, "overwrite");
//			delete c;
//		}
//		if (true) {
//			//======================
//			string name = "BE_TPSat_EB";
//			TCanvas * c = new TCanvas(name.c_str(), name.c_str());
//			TH1F * beVsTp = new TH1F("betpSatEB",
//					"betpSatEB;boundary energy [GeV];TP E_{T}[GeV];", 300, 0,
//					300);
//			cout << "draw BEVSTP!" << endl;
//			newtree->Draw(
//					"anEcalVars.v_boundaryInfoDeadCells_EB.boundaryEnergy>>betpSatEB(300, 0, 300)",
//					"anEcalVars.v_boundaryInfoDeadCells_EB.channelStatus==13&&anEcalVars.v_boundaryInfoDeadCells_EB.tpEt>63",
//					"");
//			cout << "=draw BEVSTP!" << endl;
//			gPad->Update();
//			c->Update();
//			cout << "read BEVSTP!" << endl;
//			beVsTp = (TH1F*) gPad->GetPrimitive("betpSatEB");
//			gPad->Update();
//			c->Update();
//			if (beVsTp != 0) {
//				cout << "BEVSTP!" << beVsTp->GetEntries() << endl;
//				beVsTp->SetXTitle("boundary energy [GeV]");
//				beVsTp->SetYTitle("# Entries");
//				beVsTp->Draw("");
//
//				c->Update();
//				gPad->Update();
//			}
//			c->Update();
//			newfile->WriteTObject(c, 0, "overwrite");
//			delete c;
//		}
//		if (true) {
//			//======================
//			string name = "BEvsTP_EE";
//			TCanvas * c = new TCanvas(name.c_str(), name.c_str());
//			TH2F * beVsTp = new TH2F("bevstpEE",
//					"bevstpEE;boundary energy [GeV];TP E_{T}[GeV];", 300, 0,
//					700, 100, 0, 70);
//			cout << "draw BEVSTP!" << endl;
//			newtree->Draw(
//					"anEcalVars.v_boundaryInfoDeadCells_EE.tpEt:anEcalVars.v_boundaryInfoDeadCells_EE.boundaryEnergy>>bevstpEE(300, 0, 700,	100, 0, 70)",
//					"anEcalVars.v_boundaryInfoDeadCells_EE.channelStatus==13&&anEcalVars.v_boundaryInfoDeadCells_EE.tpEt>5",
//					"box");
//			cout << "=draw BEVSTP!" << endl;
//			gPad->Update();
//			c->Update();
//			cout << "read BEVSTP!" << endl;
//			beVsTp = (TH2F*) gPad->GetPrimitive("bevstpEE");
//			gPad->Update();
//			c->Update();
//			if (beVsTp != 0) {
//				cout << "BEVSTP!" << beVsTp->GetEntries() << endl;
//				beVsTp->SetXTitle("boundary energy [GeV]");
//				beVsTp->SetYTitle("TP E_{T} [GeV]");
//				beVsTp->Draw("BOX");
//
//				c->Update();
//				gPad->Update();
//			}
//			c->Update();
//			newfile->WriteTObject(c, 0, "overwrite");
//			delete c;
//		}
//		if (true) {
//			//======================
//			string name = "BE_TPSat_EE";
//			TCanvas * c = new TCanvas(name.c_str(), name.c_str());
//			TH1F * beVsTp = new TH1F("betpSatEE",
//					"betpSatEE;boundary energy [GeV];TP E_{T}[GeV];", 300, 0,
//					500);
//			cout << "draw BEVSTP!" << endl;
//			newtree->Draw(
//					"anEcalVars.v_boundaryInfoDeadCells_EE.boundaryEnergy>>betpSatEE(300, 0, 500)",
//					"anEcalVars.v_boundaryInfoDeadCells_EE.channelStatus==13&&anEcalVars.v_boundaryInfoDeadCells_EE.tpEt>63",
//					"");
//			cout << "=draw BEVSTP!" << endl;
//			gPad->Update();
//			c->Update();
//			cout << "read BEVSTP!" << endl;
//			beVsTp = (TH1F*) gPad->GetPrimitive("betpSatEE");
//			gPad->Update();
//			c->Update();
//			if (beVsTp != 0) {
//				cout << "BEVSTP!" << beVsTp->GetEntries() << endl;
//				beVsTp->SetXTitle("boundary energy [GeV]");
//				beVsTp->SetYTitle("# Entries");
//				beVsTp->Draw("");
//
//				c->Update();
//				gPad->Update();
//			}
//			c->Update();
//			newfile->WriteTObject(c, 0, "overwrite");
//			delete c;
//		}
//		newfile->Write();
//	}
//	;
#endif
