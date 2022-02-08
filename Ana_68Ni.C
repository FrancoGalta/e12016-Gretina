#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <map>
#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

TChain* ch = NULL;
TCutG* cutNiOut = NULL;
//TCutG* cut66NiOut = NULL;
TCutG* cut67NiOut = NULL;
TCutG* cut68NiOut = NULL;
//TCutG* cut66NiIn = NULL;
TCutG* cut67NiIn = NULL;
TCutG* cut68NiIn = NULL;

bool iscoinc(Short_t reg) {
	return reg & (1 << 1);
}

double rotateXrescale(double x, double y, double scale, double theta) {
	return x * cos(theta) + y * scale * sin(theta);
}

double rotateYrescale(double x, double y, double scale, double theta){
	return -x * sin(theta) + y * scale * cos(theta);
}

void SetHistoStyle(TH1* h, string title, string xlab, string ylab){

	h->SetTitle(title.c_str());
	h->GetXaxis()->CenterTitle();
	h->GetXaxis()->SetTitleSize(0.05);
	h->GetXaxis()->SetLabelSize(0.05);
	h->GetXaxis()->SetTitleFont(132);
	h->GetXaxis()->SetLabelFont(132);
	h->GetXaxis()->SetTitle(xlab.c_str());
	h->GetYaxis()->CenterTitle();
	h->GetYaxis()->SetTitleSize(0.05);
	h->GetYaxis()->SetLabelSize(0.05);
	h->GetYaxis()->SetTitleFont(132);
	h->GetYaxis()->SetLabelFont(132);
	h->GetYaxis()->SetTitle(ylab.c_str());

}

void SetMatrixStyle(TH2* mat, string title, string xlab, string ylab){

	mat->SetTitle(title.c_str());
	mat->SetMinimum(1);
	mat->GetXaxis()->CenterTitle();
	mat->GetXaxis()->SetTitleSize(0.05);
	mat->GetXaxis()->SetLabelSize(0.05);
	mat->GetXaxis()->SetTitleFont(132);
	mat->GetXaxis()->SetLabelFont(132);
	mat->GetXaxis()->SetTitle(xlab.c_str());
	mat->GetYaxis()->CenterTitle();
	mat->GetYaxis()->SetTitleSize(0.05);
	mat->GetYaxis()->SetLabelSize(0.05);
	mat->GetYaxis()->SetTitleFont(132);
	mat->GetYaxis()->SetLabelFont(132);
	mat->GetYaxis()->SetTitle(ylab.c_str());

}

void LoadLibs(){

	gSystem->Load("/data0/e12016/GrROOT_v4ObjPin/src/libS800.so");
	gSystem->Load("/data0/e12016/GrROOT_v4ObjPin/src/libGretina.so");
	gSystem->Load("/data0/e12016/GrROOT_v4ObjPin/src/libCommandLineInterface.so");
	gSystem->Load("/data0/e12016/GrROOT_v4ObjPin/src/libRunInfo.so");
	gSystem->Load("/data0/e12016/GrROOT_v4ObjPin/src/libScaler.so");
	gSystem->Load("/data0/e12016/GrROOT_v4ObjPin/src/libFit.so");
	gSystem->Load("/data0/e12016/GrROOT_v4ObjPin/src/libPeaks.so");
	gSystem->Load("/data0/e12016/GrROOT_v4ObjPin/src/libSettings.so");

}

void LoadChain(){

	ch = new TChain("ctr");

	ch->Add("/data0/e12016/68NiAnalysis/final68Ni/cal0018.root");
	ch->Add("/data0/e12016/68NiAnalysis/final68Ni/cal0022.root");
	ch->Add("/data0/e12016/68NiAnalysis/final68Ni/cal0023.root");
	ch->Add("/data0/e12016/68NiAnalysis/final68Ni/cal0025.root");
	ch->Add("/data0/e12016/68NiAnalysis/final68Ni/cal0027.root");
	ch->Add("/data0/e12016/68NiAnalysis/final68Ni/cal0028.root");
	ch->Add("/data0/e12016/68NiAnalysis/final68Ni/cal0029.root");
	ch->Add("/data0/e12016/68NiAnalysis/final68Ni/cal0030.root");
	ch->Add("/data0/e12016/68NiAnalysis/final68Ni/cal0031.root");

}

void LoadCuts(){

	TFile *f_Ni_cut = new TFile("cuts/rotated68NiOutCut.root", "READ");
	cutNiOut = (TCutG*)f_Ni_cut->FindObjectAny("rotated68NiOutCut");
	TFile *f_PID_Out_cuts = new TFile("cuts/PID_Out_cuts_68Ni.root", "READ");
	//cut66NiOut = (TCutG*)f_PID_Out_cuts->FindObjectAny("cut_66Ni_out");
	cut67NiOut = (TCutG*)f_PID_Out_cuts->FindObjectAny("cut_67Ni_out");
	cut68NiOut = (TCutG*)f_PID_Out_cuts->FindObjectAny("cut_68Ni_out");
	TFile *f_PID_In_cuts = new TFile("cuts/PID_In_cuts_68Ni.root", "READ");
	//cut66NiIn = (TCutG*)f_PID_In_cuts->FindObjectAny("cut_66Ni_in");
	cut67NiIn = (TCutG*)f_PID_In_cuts->FindObjectAny("cut_67Ni_in");
	cut68NiIn = (TCutG*)f_PID_In_cuts->FindObjectAny("cut_68Ni_in");

}

void Ana_68Ni(){

	LoadLibs();
	LoadChain();
	LoadCuts();

	//gStyle->SetPalette(kDeepSea);

//Nice colours for the matrices
   const Int_t NRGBs = 5;
   const Int_t NCont = 255;
   Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
   Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
   Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
   Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
   TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
   gStyle->SetNumberContours(NCont);
   gStyle->SetOptStat("neI");

	TCanvas *c0 = new TCanvas("c0", "pId Out", 1800, 600);
	c0->Divide(3,1);	
	c0->cd(1);
	gPad->SetLogz();
	gPad->SetLeftMargin(0.17);
	ch->Draw("fIC.fde:fTOF.ftac_objc>>m_pidout(1000, 2250, 2500, 900, 1000, 1300)","","colz");
	TH2F *m_pidout = (TH2F*)gDirectory->Get("m_pidout");
	SetMatrixStyle(m_pidout, "PID Out", "ToF objc (arb. units)", "#DeltaE_{IC} (arb. units)");
	c0->cd(2);
	gPad->SetLeftMargin(0.17);
	gPad->SetLogz();
	ch->Draw("fIC.fde:fTOF.ftac_objc>>m_pidout_coinc(1000, 2250, 2500, 900, 1000, 1300)","iscoinc(fregistr)","colz");
	TH2F *m_pidout_coinc = (TH2F*)gDirectory->Get("m_pidout_coinc");
	SetMatrixStyle(m_pidout_coinc, "PID Out (Coincidence)", "ToF objc (arb. units)", "#DeltaE_{IC} (arb. units)");
	//cut66NiOut->Draw("same");
	cut67NiOut->Draw("same");
	cut68NiOut->Draw("same");
	c0->cd(3);
	gPad->SetLeftMargin(0.17);
	gPad->SetLogz();
	double scale = (2390.-2372.)/(1105.-1071.);
	double tanTheta = (1065.-1120.) * scale / 50.;
	double theta = atan(tanTheta);
	ch->Draw(Form("rotateYrescale(fTOF.ftac_objc, fIC.fde, %f, %f):rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)>>m_pidout_coinc_rot(1000, 1650, 1850, 900, 1600, 1900)", scale, theta, scale, theta), "iscoinc(fregistr)", "colz");
	TH2F *m_pidout_coinc_rot = (TH2F*)gDirectory->Get("m_pidout_coinc_rot");
	SetMatrixStyle(m_pidout_coinc_rot, "PID Out (Coincidence & Rotated)", "ToF objc (arb. units)", "#DeltaE_{IC} (arb. units)");
	cutNiOut->SetLineColor(kRed);
	cutNiOut->SetLineWidth(2);
	cutNiOut->Draw("same");


	TCanvas *c1 = new TCanvas("c1", "Correlation gamma-particle", 1000, 1000);
	//ch->Draw(Form("rotateYrescale(fTOF.ftac_objc, fIC.fde, %f, %f):rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)>>m_pidout_coinc_rot(1000, 1600, 1800, 1000, 1450, 1600)", scale, theta, scale, theta), "iscoinc(fregistr)", "colz");
	c1->Divide(2,2);

	c1->cd(1);
	gPad->SetLeftMargin(0.17);
	gPad->SetLogz();
	ch->Draw(Form("gretinacalc.fhits->GetDCEnergy():rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)>>m_gamma_ion(200, 1700, 1800, 3000, 0, 3000)", scale, theta), "rotated68NiOutCut", "colz");
	TH2F *m_gamma_ion = (TH2F*)gDirectory->Get("m_gamma_ion");
	SetMatrixStyle(m_gamma_ion, "Correlation #gamma-particle", "ToF objc (arb. units)", "DC E_{#gamma} (keV)");

	c1->cd(2);
	gPad->SetLeftMargin(0.17);
	ch->Draw("gretinacalc.fhits->GetTime()>>h_time_68Ni(700, -70, 0)", Form("rotated68NiOutCut && rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)>1720 && rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)<1750", scale, theta, scale, theta));
	TH1F *h_time_68Ni = (TH1F*)gDirectory->Get("h_time_68Ni");
	SetHistoStyle(h_time_68Ni, "#gamma-particle time spectrum", "#Deltat_{p-#gamma} (arb. units)", "Counts");
	//c1->Modified();
	gPad->Update();
	double ymax = gPad->GetUymax();
	TLine *line1 = new TLine(-38,6,-38,ymax);
	line1->SetLineColor(kGreen+2);	
	line1->SetLineStyle(2);
	line1->SetLineWidth(1);
	line1->Draw();
	TLine *line2 = new TLine(-30,6,-30,ymax);
	line2->SetLineColor(kGreen+2);
	line2->SetLineStyle(2);
	line2->SetLineWidth(1);
	line2->Draw();
	gPad->SetLogy();

	c1->cd(3);
	gPad->SetLeftMargin(0.17);
	gPad->SetLogz();	
	ch->Draw(Form("gretinacalc.fhits->GetDCEnergy():rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)>>m_gamma_ion_timecoinc(140, 1700, 1800, 3000, 0, 3000)", scale, theta), "rotated68NiOutCut && abs(gretinacalc.fhits->GetTime()+34) < 4", "colz");
	TH2F *m_gamma_ion_timecoinc = (TH2F*)gDirectory->Get("m_gamma_ion_timecoinc");
	SetMatrixStyle(m_gamma_ion_timecoinc, "Correlation #gamma-particle (time coincidence)", "ToF objc (arb. units)", "DC E_{#gamma} (keV)");

	c1->cd(4);
	gPad->SetLeftMargin(0.17);
	gPad->SetLogy();
	h_time_68Ni->SetLineColor(kRed);
	h_time_68Ni->Draw();
	ch->Draw("gretinacalc.fhits->GetTime()>>h_time_67Ni(700, -70, 0)", Form("rotated68NiOutCut && rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)>1750 && rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)<1770", scale, theta, scale, theta), "same");
	TH1F *h_time_67Ni = (TH1F*)gDirectory->Get("h_time_67Ni");
	h_time_67Ni->SetLineColor(kBlack);
	//ch->Draw("gretinacalc.fhits->GetTime()>>h_time_68Ni(700, -70, 0)", Form("rotated68NiOutCut && rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)>1729 && rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)<1750", scale, theta, scale, theta), "same");
	//TH1F *h_time_68Ni = (TH1F*)gDirectory->Get("h_time_68Ni");
	//h_time_68Ni->SetLineColor(kGreen+2);


	TCanvas *c2 = new TCanvas("c2", "Gamma spectra", 800, 1000);
	c2->Divide(1,2);

	c2->cd(1);
	ch->Draw("gretinacalc.fhits->GetDCEnergy()>>h_68NiTimeCut(3000, 0, 3000)", Form("rotated68NiOutCut && rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)>1720 && rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)<1750 && abs(gretinacalc.fhits->GetTime()+34) < 4", scale, theta, scale, theta));
	TH1F *h_68NiTimeCut = (TH1F*)gDirectory->Get("h_68NiTimeCut");
	SetHistoStyle(h_68NiTimeCut, "^{68}Ni #gamma spectrum", "DC E_{#gamma} (keV)", "Counts / keV");
	h_68NiTimeCut->SetLineColor(kBlack);
	ch->Draw("gretinacalc.fhits->GetDCEnergy()>>h_68Ni_singlecut(3000, 0, 3000)", "cut_68Ni_out && abs(gretinacalc.fhits->GetTime()+34) < 4", "same");
	TH1F *h_68Ni_singlecut = (TH1F*)gDirectory->Get("h_68Ni_singlecut");
	SetHistoStyle(h_68Ni_singlecut, "^{68}Ni #gamma spectrum single cut Out", "DC E_{#gamma} (keV)", "Counts / keV");
	h_68Ni_singlecut->SetLineColor(kRed);
	ch->Draw("gretinacalc.fhits->GetDCEnergy()>>h_68Ni_cutInOut(3000, 0, 3000)", "cut_68Ni_out && cut_68Ni_in && abs(gretinacalc.fhits->GetTime()+34) < 4", "same");
	TH1F *h_68Ni_cutInOut = (TH1F*)gDirectory->Get("h_68Ni_cutInOut");
	SetHistoStyle(h_68Ni_cutInOut, "^{68}Ni #gamma spectrum cut In & Out", "DC E_{#gamma} (keV)", "Counts / keV");
	h_68Ni_cutInOut->SetLineColor(kGreen+2);
	
	c2->cd(2);
	ch->Draw("gretinacalc.fhits->GetDCEnergy()>>h_67NiTimeCut(3000, 0, 3000)", Form("rotated68NiOutCut && rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)>1750 && rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)<1770 && abs(gretinacalc.fhits->GetTime()+34) < 4", scale, theta, scale, theta));
	TH1F *h_67NiTimeCut = (TH1F*)gDirectory->Get("h_67NiTimeCut");
	SetHistoStyle(h_67NiTimeCut, "^{67}Ni #gamma spectrum", "DC E_{#gamma} (keV)", "Counts / keV");
	h_67NiTimeCut->SetLineColor(kBlack);
	ch->Draw("gretinacalc.fhits->GetDCEnergy()>>h_67Ni_singlecut(3000, 0, 3000)", "cut_67Ni_out && abs(gretinacalc.fhits->GetTime()+34) < 4", "same");
	TH1F *h_67Ni_singlecut = (TH1F*)gDirectory->Get("h_67Ni_singlecut");
	SetHistoStyle(h_67Ni_singlecut, "^{67}Ni #gamma spectrum single cut Out", "DC E_{#gamma} (keV)", "Counts / keV");
	h_67Ni_singlecut->SetLineColor(kRed);
	ch->Draw("gretinacalc.fhits->GetDCEnergy()>>h_67Ni_cutInOut(3000, 0, 3000)", "cut_67Ni_out && cut_67Ni_in && abs(gretinacalc.fhits->GetTime()+34) < 4", "same");
	TH1F *h_67Ni_cutInOut = (TH1F*)gDirectory->Get("h_67Ni_cutInOut");
	SetHistoStyle(h_67Ni_cutInOut, "^{67}Ni #gamma spectrum cut In & Out", "DC E_{#gamma} (keV)", "Counts / keV");
	h_67Ni_cutInOut->SetLineColor(kGreen+2);

/*	c2->cd(3);
	ch->Draw("gretinacalc.fhits->GetDCEnergy()>>h_68NiTimeCut(3000, 0, 3000)", Form("rotated68NiOutCut && rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)>1729 && rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)<1750 && abs(gretinacalc.fhits->GetTime()+35) < 4", scale, theta, scale, theta));
	TH1F *h_68NiTimeCut = (TH1F*)gDirectory->Get("h_68NiTimeCut");
	h_68NiTimeCut->SetLineColor(kBlack);
	SetHistoStyle(h_68NiTimeCut, "^{68}Ni #gamma spectrum", "DC E_{#gamma} (keV)", "Counts / keV");
	ch->Draw("gretinacalc.fhits->GetDCEnergy()>>h_68Ni_singlecut(3000, 0, 3000)", "cut_68Ni && abs(gretinacalc.fhits->GetTime()+35) < 4", "same");
	TH1F *h_68Ni_singlecut = (TH1F*)gDirectory->Get("h_68Ni_singlecut");
	SetHistoStyle(h_68Ni_singlecut, "^{68}Ni #gamma spectrum single cut Out", "DC E_{#gamma} (keV)", "Counts / keV");
	h_68Ni_singlecut->SetLineColor(kRed);
	ch->Draw("gretinacalc.fhits->GetDCEnergy()>>h_68Ni_cutInOut(3000, 0, 3000)", "cut_68Ni && cut_68Ni_in && abs(gretinacalc.fhits->GetTime()+35) < 4", "same");
	TH1F *h_68Ni_cutInOut = (TH1F*)gDirectory->Get("h_68Ni_cutInOut");
	SetHistoStyle(h_68Ni_cutInOut, "^{68}Ni #gamma spectrum cut In & Out", "DC E_{#gamma} (keV)", "Counts / keV");
	h_68Ni_cutInOut->SetLineColor(kGreen+2);
*/

	TCanvas *c3 = new TCanvas("c3", "PID In", 1000, 1000);
	c3->Divide(2,2);

	c3->cd(1);
	gPad->SetLeftMargin(0.17);
	gPad->SetLogz();
	ch->Draw("fTOF.ftac_objc:fTOF.ftac_xfpc>>m_pidin(1000, 1550, 1950, 1000, 2300, 2500)","","colz");
	TH2F *m_pidin = (TH2F*)gDirectory->Get("m_pidin");
	SetMatrixStyle(m_pidin, "PID In", "ToF xfpc (arb. units)", "ToF objc (arb. units)");

	c3->cd(2);
	gPad->SetLeftMargin(0.17);
	gPad->SetLogz();
	ch->Draw("fTOF.ftac_objc:fTOF.ftac_xfpc>>m_pidin_coinc(1000, 1500, 1950, 1000, 2300, 2500)", "iscoinc(fregistr)", "colz");
	TH2F *m_pidin_coinc = (TH2F*)gDirectory->Get("m_pidin_coinc");
	SetMatrixStyle(m_pidin_coinc, "PID In (coincidence)", "ToF xfpc (arb. units)", "ToF objc (arb. units)");
	//cut66NiIn->Draw("same");
	cut67NiIn->Draw("same");
	cut68NiIn->Draw("same");

	c3->cd(3);
	gPad->SetLeftMargin(0.17);
	ch->Draw("fTOF.ftac_objc-fTOF.ftac_xfpc>>h_tof_diff(300, 500, 800)", "iscoinc(fregistr)");
	TH1F *h_tof_diff = (TH1F*)gDirectory->Get("h_tof_diff");
	SetHistoStyle(h_tof_diff, "PID In ToF difference", "ToF objc - ToF xfpc (arb. units)", "Counts");
	c3->cd(4);
	gPad->SetLeftMargin(0.17);
	gPad->SetLogz();
	ch->Draw("fTOF.ftac_objc-fTOF.ftac_xfpc:fTOF.ftac_objc>>m_pidin_tofcorr(1000, 2300, 2500, 200, 600, 700)", "iscoinc(fregistr)", "colz");
	TH2F *m_pidin_tofcorr = (TH2F*)gDirectory->Get("m_pidin_tofcorr");
	SetMatrixStyle(m_pidin_tofcorr, "PID In ToF correlation", "ToF objc (arb. units)", "ToF objc - ToF xfpc (arb. units)");


	TCanvas *c4 = new TCanvas("c4", "PID In & Out cross checks", 1000, 1000);
	c4->Divide(2,2);

	c4->cd(1);
	//gPad->SetLeftMargin(0.17);
	//ch->Draw("fTOF.ftac_objc-fTOF.ftac_xfpc:fTOF.ftac_objc>>m_pidin_tofcorr_68Ni(800, 2200, 2360, 200, 700, 800)", "iscoinc(fregistr) && cut_68Ni", "");
	//TH2F *m_pidin_tofcorr_68Ni = (TH2F*)gDirectory->Get("m_pidin_tofcorr_68Ni");
	//SetMatrixStyle(m_pidin_tofcorr_68Ni, "PID In ToF correlation (gate 68Ni out)", "ToF objc (arb. units)", "ToF objc - ToF xfpc (arb. units)");
	ch->Draw("fTOF.ftac_objc-fTOF.ftac_xfpc:fTOF.ftac_objc>>m_pidin_tofcorr_67Ni(1000, 2300, 2500, 200, 600, 700)", "iscoinc(fregistr) && cut_67Ni_out", "");
	TH2F *m_pidin_tofcorr_67Ni = (TH2F*)gDirectory->Get("m_pidin_tofcorr_67Ni");
	SetMatrixStyle(m_pidin_tofcorr_67Ni, "PID In ToF correlation (gate 67Ni out)", "ToF objc (arb. units)", "ToF objc - ToF xfpc (arb. units)");
	ch->Draw("fTOF.ftac_objc-fTOF.ftac_xfpc:fTOF.ftac_objc>>m_pidin_tofcorr_68Ni(1000, 2300, 2500, 200, 600, 700)", "iscoinc(fregistr) && cut_68Ni_out", "same");
	TH2F *m_pidin_tofcorr_68Ni = (TH2F*)gDirectory->Get("m_pidin_tofcorr_68Ni");
	SetMatrixStyle(m_pidin_tofcorr_68Ni, "PID In ToF correlation (gate 68Ni out)", "ToF objc (arb. units)", "ToF objc - ToF xfpc (arb. units)");

	c4->cd(2);
	//ch->Draw(Form("rotateYrescale(fTOF.ftac_objc, fIC.fde, %f, %f):rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)>>m_pidout_coinc_rot_68Ni(1000, 1600, 1800, 1000, 1450, 1600)", scale, theta, scale, theta), "iscoinc(fregistr) && cut_68Ni_in", "");
	//TH2F *m_pidout_coinc_rot_68Ni = (TH2F*)gDirectory->Get("m_pidout_coinc_rot_68Ni");
	//SetMatrixStyle(m_pidout_coinc_rot_68Ni, "PID Out Coincidence & Rotated (gate 68Ni in)", "ToF objc (arb. units)", "#DeltaE_{IC} (arb. units)");
	ch->Draw(Form("rotateYrescale(fTOF.ftac_objc, fIC.fde, %f, %f):rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)>>m_pidout_coinc_rot_67Ni(1000, 1650, 1850, 900, 1600, 1900)", scale, theta, scale, theta), "iscoinc(fregistr) && cut_67Ni_in", "");
	TH2F *m_pidout_coinc_rot_67Ni = (TH2F*)gDirectory->Get("m_pidout_coinc_rot_67Ni");
	SetMatrixStyle(m_pidout_coinc_rot_67Ni, "PID Out Coincidence & Rotated (gate 67Ni in)", "ToF objc (arb. units)", "#DeltaE_{IC} (arb. units)");
	ch->Draw(Form("rotateYrescale(fTOF.ftac_objc, fIC.fde, %f, %f):rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)>>m_pidout_coinc_rot_68Ni(1000, 1650, 1850, 900, 1600, 1900)", scale, theta, scale, theta), "iscoinc(fregistr) && cut_68Ni_in", "same");
	TH2F *m_pidout_coinc_rot_68Ni = (TH2F*)gDirectory->Get("m_pidout_coinc_rot_68Ni");
	SetMatrixStyle(m_pidout_coinc_rot_68Ni, "PID Out Coincidence & Rotated (gate 68Ni in)", "ToF objc (arb. units)", "#DeltaE_{IC} (arb. units)");

	c4->cd(3);
	//ch->Draw("fTOF.ftac_objc:fTOF.ftac_xfpc>>m_pidin_coinc_68Ni(1000, 1400, 1650, 800, 2200, 2360)", "iscoinc(fregistr) && cut_68Ni", "");
	ch->Draw("fTOF.ftac_objc:fTOF.ftac_xfpc>>m_pidin_coinc_67Ni(1000, 1550, 1950, 1000, 2300, 2500)", "iscoinc(fregistr) && cut_67Ni_out", "");
	ch->Draw("fTOF.ftac_objc:fTOF.ftac_xfpc>>m_pidin_coinc_68Ni(1000, 1550, 1950, 1000, 2300, 2500)", "iscoinc(fregistr) && cut_68Ni_out", "same");

	c4->cd(4);
	//ch->Draw("fIC.fde:fTOF.ftac_objc>>m_pidout_coinc_68Ni(1000, 2150, 2350, 1000, 1000, 1400)", "iscoinc(fregistr) && cut_68Ni_in", "");
	ch->Draw("fIC.fde:fTOF.ftac_objc>>m_pidout_coinc_67Ni(1000, 2300, 2500, 9000, 1000, 1300)", "iscoinc(fregistr) && cut_67Ni_in", "");
	ch->Draw("fIC.fde:fTOF.ftac_objc>>m_pidout_coinc_68Ni(1000, 2300, 2500, 9000, 1000, 1300)", "iscoinc(fregistr) && cut_68Ni_in", "same");

	TCanvas *c5 = new TCanvas("c5", "68Ni gamma spectrum", 1000, 700);
	h_68NiTimeCut->Draw();


	TFile *outfile = new TFile("out/spectra_68Ni.root", "RECREATE");

	m_pidout->Write();
	m_pidout_coinc->Write();
	m_pidout_coinc_rot->Write();
	m_gamma_ion->Write();
	h_time_68Ni->Write();
	m_gamma_ion_timecoinc->Write();
	h_68NiTimeCut->Write();
	h_67NiTimeCut->Write();
	//h_66NiTimeCut->Write();
	h_68Ni_singlecut->Write();
	h_67Ni_singlecut->Write();
	//h_66Ni_singlecut->Write();
	m_pidin->Write();
	m_pidin_coinc->Write();
	h_tof_diff->Write();
	m_pidin_tofcorr->Write();
	//m_pidin_tofcorr_66Ni->Write();
	m_pidin_tofcorr_67Ni->Write();
	m_pidin_tofcorr_68Ni->Write();
	//m_pidout_coinc_rot_66Ni->Write();
	m_pidout_coinc_rot_67Ni->Write();
	m_pidout_coinc_rot_68Ni->Write();

	outfile->Close();
	
}
