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
TCutG* cut68NiOut = NULL;
TCutG* cut69NiOut = NULL;
TCutG* cut70NiOut = NULL;
TCutG* cut68NiIn = NULL;
TCutG* cut69NiIn = NULL;
TCutG* cut70NiIn = NULL;

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

	ch->Add("/data0/e12016/70NiAnalysis/final70NiFranco/cal0043.root");
	ch->Add("/data0/e12016/70NiAnalysis/final70NiFranco/cal0044.root");
	ch->Add("/data0/e12016/70NiAnalysis/final70NiFranco/cal0045.root");
	ch->Add("/data0/e12016/70NiAnalysis/final70NiFranco/cal0046.root");
	ch->Add("/data0/e12016/70NiAnalysis/final70NiFranco/cal0048.root");
	ch->Add("/data0/e12016/70NiAnalysis/final70NiFranco/cal0049.root");
	ch->Add("/data0/e12016/70NiAnalysis/final70NiFranco/cal0060.root");
	ch->Add("/data0/e12016/70NiAnalysis/final70NiFranco/cal0061.root");
	ch->Add("/data0/e12016/70NiAnalysis/final70NiFranco/cal0062.root");
	ch->Add("/data0/e12016/70NiAnalysis/final70NiFranco/cal0063.root");

}

void LoadCuts(){

	TFile *f_Ni_cut = new TFile("cuts/rotated70NiOutCut.root", "READ");
	cutNiOut = (TCutG*)f_Ni_cut->FindObjectAny("rotated70NiOutCut");
	TFile *f_PID_Out_cuts = new TFile("cuts/PID_Out_cuts_70Ni.root", "READ");
	cut68NiOut = (TCutG*)f_PID_Out_cuts->FindObjectAny("cut_68Ni");
	cut69NiOut = (TCutG*)f_PID_Out_cuts->FindObjectAny("cut_69Ni");
	cut70NiOut = (TCutG*)f_PID_Out_cuts->FindObjectAny("cut_70Ni");
	TFile *f_PID_In_cuts = new TFile("cuts/PID_In_cuts_70Ni.root", "READ");
	cut68NiIn = (TCutG*)f_PID_In_cuts->FindObjectAny("cut_68Ni_in");
	cut69NiIn = (TCutG*)f_PID_In_cuts->FindObjectAny("cut_69Ni_in");
	cut70NiIn = (TCutG*)f_PID_In_cuts->FindObjectAny("cut_70Ni_in");

}

void Ana_70Ni(){

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
	ch->Draw("fIC.fde:fTOF.ftac_objc>>m_pidout(1000, 2150, 2350, 1000, 1000, 1400)","","colz");
	TH2F *m_pidout = (TH2F*)gDirectory->Get("m_pidout");
	SetMatrixStyle(m_pidout, "PID Out", "ToF objc (arb. units)", "#DeltaE_{IC} (arb. units)");
	c0->cd(2);
	gPad->SetLeftMargin(0.17);
	gPad->SetLogz();
	ch->Draw("fIC.fde:fTOF.ftac_objc>>m_pidout_coinc(1000, 2150, 2350, 1000, 1000, 1400)","iscoinc(fregistr)","colz");
	TH2F *m_pidout_coinc = (TH2F*)gDirectory->Get("m_pidout_coinc");
	SetMatrixStyle(m_pidout_coinc, "PID Out (Coincidence)", "ToF objc (arb. units)", "#DeltaE_{IC} (arb. units)");
	cut68NiOut->Draw("same");
	cut69NiOut->Draw("same");
	cut70NiOut->Draw("same");
	c0->cd(3);
	gPad->SetLeftMargin(0.17);
	gPad->SetLogz();
	double scale = (2260.-2240.)/(1272.-1218.);
	double tanTheta = (1193.-1246.) * scale / (2281.-2248.);
	double theta = atan(tanTheta);
	ch->Draw(Form("rotateYrescale(fTOF.ftac_objc, fIC.fde, %f, %f):rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)>>m_pidout_coinc_rot(1000, 1600, 1800, 1000, 1450, 1600)", scale, theta, scale, theta), "iscoinc(fregistr)", "colz");
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
	ch->Draw(Form("gretinacalc.fhits->GetDCEnergy():rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)>>m_gamma_ion(140, 1680, 1750, 3000, 0, 3000)", scale, theta), "rotated70NiOutCut", "colz");
	TH2F *m_gamma_ion = (TH2F*)gDirectory->Get("m_gamma_ion");
	SetMatrixStyle(m_gamma_ion, "Correlation #gamma-particle", "ToF objc (arb. units)", "DC E_{#gamma} (keV)");

	c1->cd(2);
	gPad->SetLeftMargin(0.17);
	ch->Draw("gretinacalc.fhits->GetTime()>>h_time_70Ni(700, -70, 0)", Form("rotated70NiOutCut && rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)>1685 && rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)<1708", scale, theta, scale, theta));
	TH1F *h_time_70Ni = (TH1F*)gDirectory->Get("h_time_70Ni");
	SetHistoStyle(h_time_70Ni, "#gamma-particle time spectrum", "#Deltat_{p-#gamma} (arb. units)", "Counts");
	//c1->Modified();
	gPad->Update();
	double ymax = gPad->GetUymax();
	TLine *line1 = new TLine(-39,6,-39,ymax);
	line1->SetLineColor(kGreen+2);	
	line1->SetLineStyle(2);
	line1->SetLineWidth(1);
	line1->Draw();
	TLine *line2 = new TLine(-31,6,-31,ymax);
	line2->SetLineColor(kGreen+2);
	line2->SetLineStyle(2);
	line2->SetLineWidth(1);
	line2->Draw();
	gPad->SetLogy();

	c1->cd(3);
	gPad->SetLeftMargin(0.17);
	gPad->SetLogz();	
	ch->Draw(Form("gretinacalc.fhits->GetDCEnergy():rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)>>m_gamma_ion_timecoinc(140, 1680, 1750, 3000, 0, 3000)", scale, theta), "rotated70NiOutCut && abs(gretinacalc.fhits->GetTime()+35) < 4", "colz");
	TH2F *m_gamma_ion_timecoinc = (TH2F*)gDirectory->Get("m_gamma_ion_timecoinc");
	SetMatrixStyle(m_gamma_ion_timecoinc, "Correlation #gamma-particle (time coincidence)", "ToF objc (arb. units)", "DC E_{#gamma} (keV)");

	c1->cd(4);
	gPad->SetLeftMargin(0.17);
	gPad->SetLogy();
	h_time_70Ni->SetLineColor(kRed);
	h_time_70Ni->Draw();
	ch->Draw("gretinacalc.fhits->GetTime()>>h_time_69Ni(700, -70, 0)", Form("rotated70NiOutCut && rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)>1708 && rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)<1729", scale, theta, scale, theta), "same");
	TH1F *h_time_69Ni = (TH1F*)gDirectory->Get("h_time_69Ni");
	h_time_69Ni->SetLineColor(kBlack);
	ch->Draw("gretinacalc.fhits->GetTime()>>h_time_68Ni(700, -70, 0)", Form("rotated70NiOutCut && rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)>1729 && rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)<1750", scale, theta, scale, theta), "same");
	TH1F *h_time_68Ni = (TH1F*)gDirectory->Get("h_time_68Ni");
	h_time_68Ni->SetLineColor(kGreen+2);


	TCanvas *c2 = new TCanvas("c2", "Gamma spectra", 800, 1000);
	c2->Divide(1,3);

	c2->cd(1);
	ch->Draw("gretinacalc.fhits->GetDCEnergy()>>h_70NiTimeCut(3000, 0, 3000)", Form("rotated70NiOutCut && rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)>1685 && rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)<1708 && abs(gretinacalc.fhits->GetTime()+35) < 4", scale, theta, scale, theta));
	TH1F *h_70NiTimeCut = (TH1F*)gDirectory->Get("h_70NiTimeCut");
	SetHistoStyle(h_70NiTimeCut, "^{70}Ni #gamma spectrum", "DC E_{#gamma} (keV)", "Counts / keV");
	h_70NiTimeCut->SetLineColor(kBlack);
	ch->Draw("gretinacalc.fhits->GetDCEnergy()>>h_70Ni_singlecut(3000, 0, 3000)", "cut_70Ni && abs(gretinacalc.fhits->GetTime()+35) < 4", "same");
	TH1F *h_70Ni_singlecut = (TH1F*)gDirectory->Get("h_70Ni_singlecut");
	SetHistoStyle(h_70Ni_singlecut, "^{70}Ni #gamma spectrum single cut Out", "DC E_{#gamma} (keV)", "Counts / keV");
	h_70Ni_singlecut->SetLineColor(kRed);
	ch->Draw("gretinacalc.fhits->GetDCEnergy()>>h_70Ni_cutInOut(3000, 0, 3000)", "cut_70Ni && cut_70Ni_in && abs(gretinacalc.fhits->GetTime()+35) < 4", "same");
	TH1F *h_70Ni_cutInOut = (TH1F*)gDirectory->Get("h_70Ni_cutInOut");
	SetHistoStyle(h_70Ni_cutInOut, "^{70}Ni #gamma spectrum cut In & Out", "DC E_{#gamma} (keV)", "Counts / keV");
	h_70Ni_cutInOut->SetLineColor(kGreen+2);
	
	c2->cd(2);
	ch->Draw("gretinacalc.fhits->GetDCEnergy()>>h_69NiTimeCut(3000, 0, 3000)", Form("rotated70NiOutCut && rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)>1708 && rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)<1729 && abs(gretinacalc.fhits->GetTime()+35) < 4", scale, theta, scale, theta));
	TH1F *h_69NiTimeCut = (TH1F*)gDirectory->Get("h_69NiTimeCut");
	SetHistoStyle(h_69NiTimeCut, "^{69}Ni #gamma spectrum", "DC E_{#gamma} (keV)", "Counts / keV");
	h_69NiTimeCut->SetLineColor(kBlack);
	ch->Draw("gretinacalc.fhits->GetDCEnergy()>>h_69Ni_singlecut(3000, 0, 3000)", "cut_69Ni && abs(gretinacalc.fhits->GetTime()+35) < 4", "same");
	TH1F *h_69Ni_singlecut = (TH1F*)gDirectory->Get("h_69Ni_singlecut");
	SetHistoStyle(h_69Ni_singlecut, "^{69}Ni #gamma spectrum single cut Out", "DC E_{#gamma} (keV)", "Counts / keV");
	h_69Ni_singlecut->SetLineColor(kRed);
	ch->Draw("gretinacalc.fhits->GetDCEnergy()>>h_69Ni_cutInOut(3000, 0, 3000)", "cut_69Ni && cut_69Ni_in && abs(gretinacalc.fhits->GetTime()+35) < 4", "same");
	TH1F *h_69Ni_cutInOut = (TH1F*)gDirectory->Get("h_69Ni_cutInOut");
	SetHistoStyle(h_69Ni_cutInOut, "^{69}Ni #gamma spectrum cut In & Out", "DC E_{#gamma} (keV)", "Counts / keV");
	h_69Ni_cutInOut->SetLineColor(kGreen+2);

	c2->cd(3);
	ch->Draw("gretinacalc.fhits->GetDCEnergy()>>h_68NiTimeCut(3000, 0, 3000)", Form("rotated70NiOutCut && rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)>1729 && rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)<1750 && abs(gretinacalc.fhits->GetTime()+35) < 4", scale, theta, scale, theta));
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


	TCanvas *c3 = new TCanvas("c3", "PID In", 1000, 1000);
	c3->Divide(2,2);

	c3->cd(1);
	gPad->SetLeftMargin(0.17);
	gPad->SetLogz();
	ch->Draw("fTOF.ftac_objc:fTOF.ftac_xfpc>>m_pidin(1000, 1400, 1650, 800, 2200, 2360)","","colz");
	TH2F *m_pidin = (TH2F*)gDirectory->Get("m_pidin");
	SetMatrixStyle(m_pidin, "PID In", "ToF xfpc (arb. units)", "ToF objc (arb. units)");

	c3->cd(2);
	gPad->SetLeftMargin(0.17);
	gPad->SetLogz();
	ch->Draw("fTOF.ftac_objc:fTOF.ftac_xfpc>>m_pidin_coinc(1000, 1400, 1650, 800, 2200, 2360)", "iscoinc(fregistr)", "colz");
	TH2F *m_pidin_coinc = (TH2F*)gDirectory->Get("m_pidin_coinc");
	SetMatrixStyle(m_pidin_coinc, "PID In (coincidence)", "ToF xfpc (arb. units)", "ToF objc (arb. units)");
	cut68NiIn->Draw("same");
	cut69NiIn->Draw("same");
	cut70NiIn->Draw("same");

	c3->cd(3);
	gPad->SetLeftMargin(0.17);
	ch->Draw("fTOF.ftac_objc-fTOF.ftac_xfpc>>h_tof_diff(300, 600, 900)", "iscoinc(fregistr)");
	TH1F *h_tof_diff = (TH1F*)gDirectory->Get("h_tof_diff");
	SetHistoStyle(h_tof_diff, "PID In ToF difference", "ToF objc - ToF xfpc (arb. units)", "Counts");
	c3->cd(4);
	gPad->SetLeftMargin(0.17);
	gPad->SetLogz();
	ch->Draw("fTOF.ftac_objc-fTOF.ftac_xfpc:fTOF.ftac_objc>>m_pidin_tofcorr(800, 2200, 2360, 200, 700, 800)", "iscoinc(fregistr)", "colz");
	TH2F *m_pidin_tofcorr = (TH2F*)gDirectory->Get("m_pidin_tofcorr");
	SetMatrixStyle(m_pidin_tofcorr, "PID In ToF correlation", "ToF objc (arb. units)", "ToF objc - ToF xfpc (arb. units)");


	TCanvas *c4 = new TCanvas("c4", "PID In & Out cross checks", 1000, 1000);
	c4->Divide(2,2);

	c4->cd(1);
	//gPad->SetLeftMargin(0.17);
	ch->Draw("fTOF.ftac_objc-fTOF.ftac_xfpc:fTOF.ftac_objc>>m_pidin_tofcorr_68Ni(800, 2200, 2360, 200, 700, 800)", "iscoinc(fregistr) && cut_68Ni", "");
	TH2F *m_pidin_tofcorr_68Ni = (TH2F*)gDirectory->Get("m_pidin_tofcorr_68Ni");
	SetMatrixStyle(m_pidin_tofcorr_68Ni, "PID In ToF correlation (gate 68Ni out)", "ToF objc (arb. units)", "ToF objc - ToF xfpc (arb. units)");
	ch->Draw("fTOF.ftac_objc-fTOF.ftac_xfpc:fTOF.ftac_objc>>m_pidin_tofcorr_69Ni(800, 2200, 2360, 200, 700, 800)", "iscoinc(fregistr) && cut_69Ni", "same");
	TH2F *m_pidin_tofcorr_69Ni = (TH2F*)gDirectory->Get("m_pidin_tofcorr_69Ni");
	SetMatrixStyle(m_pidin_tofcorr_69Ni, "PID In ToF correlation (gate 69Ni out)", "ToF objc (arb. units)", "ToF objc - ToF xfpc (arb. units)");
	ch->Draw("fTOF.ftac_objc-fTOF.ftac_xfpc:fTOF.ftac_objc>>m_pidin_tofcorr_70Ni(800, 2200, 2360, 200, 700, 800)", "iscoinc(fregistr) && cut_70Ni", "same");
	TH2F *m_pidin_tofcorr_70Ni = (TH2F*)gDirectory->Get("m_pidin_tofcorr_70Ni");
	SetMatrixStyle(m_pidin_tofcorr_70Ni, "PID In ToF correlation (gate 70Ni out)", "ToF objc (arb. units)", "ToF objc - ToF xfpc (arb. units)");

	c4->cd(2);
	ch->Draw(Form("rotateYrescale(fTOF.ftac_objc, fIC.fde, %f, %f):rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)>>m_pidout_coinc_rot_68Ni(1000, 1600, 1800, 1000, 1450, 1600)", scale, theta, scale, theta), "iscoinc(fregistr) && cut_68Ni_in", "");
	TH2F *m_pidout_coinc_rot_68Ni = (TH2F*)gDirectory->Get("m_pidout_coinc_rot_68Ni");
	SetMatrixStyle(m_pidout_coinc_rot_68Ni, "PID Out Coincidence & Rotated (gate 68Ni in)", "ToF objc (arb. units)", "#DeltaE_{IC} (arb. units)");
	ch->Draw(Form("rotateYrescale(fTOF.ftac_objc, fIC.fde, %f, %f):rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)>>m_pidout_coinc_rot_69Ni(1000, 1600, 1800, 1000, 1450, 1600)", scale, theta, scale, theta), "iscoinc(fregistr) && cut_69Ni_in", "same");
	TH2F *m_pidout_coinc_rot_69Ni = (TH2F*)gDirectory->Get("m_pidout_coinc_rot_69Ni");
	SetMatrixStyle(m_pidout_coinc_rot_69Ni, "PID Out Coincidence & Rotated (gate 69Ni in)", "ToF objc (arb. units)", "#DeltaE_{IC} (arb. units)");
	ch->Draw(Form("rotateYrescale(fTOF.ftac_objc, fIC.fde, %f, %f):rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)>>m_pidout_coinc_rot_70Ni(1000, 1600, 1800, 1000, 1450, 1600)", scale, theta, scale, theta), "iscoinc(fregistr) && cut_70Ni_in", "same");
	TH2F *m_pidout_coinc_rot_70Ni = (TH2F*)gDirectory->Get("m_pidout_coinc_rot_70Ni");
	SetMatrixStyle(m_pidout_coinc_rot_70Ni, "PID Out Coincidence & Rotated (gate 70Ni in)", "ToF objc (arb. units)", "#DeltaE_{IC} (arb. units)");

	c4->cd(3);
	ch->Draw("fTOF.ftac_objc:fTOF.ftac_xfpc>>m_pidin_coinc_68Ni(1000, 1400, 1650, 800, 2200, 2360)", "iscoinc(fregistr) && cut_68Ni", "");
	ch->Draw("fTOF.ftac_objc:fTOF.ftac_xfpc>>m_pidin_coinc_69Ni(1000, 1400, 1650, 800, 2200, 2360)", "iscoinc(fregistr) && cut_69Ni", "same");
	ch->Draw("fTOF.ftac_objc:fTOF.ftac_xfpc>>m_pidin_coinc_70Ni(1000, 1400, 1650, 800, 2200, 2360)", "iscoinc(fregistr) && cut_70Ni", "same");

	c4->cd(4);
	ch->Draw("fIC.fde:fTOF.ftac_objc>>m_pidout_coinc_68Ni(1000, 2150, 2350, 1000, 1000, 1400)", "iscoinc(fregistr) && cut_68Ni_in", "");
	ch->Draw("fIC.fde:fTOF.ftac_objc>>m_pidout_coinc_69Ni(1000, 2150, 2350, 1000, 1000, 1400)", "iscoinc(fregistr) && cut_69Ni_in", "same");
	ch->Draw("fIC.fde:fTOF.ftac_objc>>m_pidout_coinc_70Ni(1000, 2150, 2350, 1000, 1000, 1400)", "iscoinc(fregistr) && cut_70Ni_in", "same");

	TCanvas *c5 = new TCanvas("c5", "Gamma-Particle angular correlation", 1400, 700);
	c5->Divide(2,1);
	c5->cd(1);
	ch->Draw("gretinacalc.fhits->GetEnergy():gretinacalc.fhits->GetPosition().Theta()*TMath::RadToDeg()>>m_gammaraw_theta(180, 0, 180, 3000, 0, 3000)", Form("rotated70NiOutCut && rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)>1685 && rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)<1708 && abs(gretinacalc.fhits->GetTime()+35) < 4", scale, theta, scale, theta), "colz");	
	TH2F *m_gammaraw_theta = (TH2F*)gDirectory->Get("m_gammaraw_theta");
	SetMatrixStyle(m_gammaraw_theta, "Raw gamma-particle angle", "#theta_{GRETINA} (deg)", "E_{#gamma} (keV)");

	c5->cd(2);
	ch->Draw("gretinacalc.fhits->GetDCEnergy():gretinacalc.fhits->GetPosition().Theta()*TMath::RadToDeg()>>m_gammaDC_theta(180, 0, 180, 3000, 0, 3000)", Form("rotated70NiOutCut && rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)>1685 && rotateXrescale(fTOF.ftac_objc, fIC.fde, %f, %f)<1708 && abs(gretinacalc.fhits->GetTime()+35) < 4", scale, theta, scale, theta), "colz");	
	TH2F *m_gammaDC_theta = (TH2F*)gDirectory->Get("m_gammaDC_theta");
	SetMatrixStyle(m_gammaDC_theta, "DC gamma-particle angle", "#theta_{GRETINA} (deg)", "DC E_{#gamma} (keV)");

//h_70NiTimeCut->Draw();


	TFile *outfile = new TFile("out/spectra_70Ni_beta0.3950.root", "RECREATE");

	m_pidout->Write();
	m_pidout_coinc->Write();
	m_pidout_coinc_rot->Write();
	m_gamma_ion->Write();
	h_time_70Ni->Write();
	m_gamma_ion_timecoinc->Write();
	h_70NiTimeCut->Write();
	h_69NiTimeCut->Write();
	h_68NiTimeCut->Write();
	h_70Ni_singlecut->Write();
	h_69Ni_singlecut->Write();
	h_68Ni_singlecut->Write();
	m_pidin->Write();
	m_pidin_coinc->Write();
	h_tof_diff->Write();
	m_pidin_tofcorr->Write();
	m_pidin_tofcorr_68Ni->Write();
	m_pidin_tofcorr_69Ni->Write();
	m_pidin_tofcorr_70Ni->Write();
	m_pidout_coinc_rot_68Ni->Write();
	m_pidout_coinc_rot_69Ni->Write();
	m_pidout_coinc_rot_70Ni->Write();
	m_gammaraw_theta->Write();
	m_gammaDC_theta->Write();

	outfile->Close();
	
}
