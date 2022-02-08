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

	ch->Add("/data0/e12016/70NiAnalysis/final70Ni/cal0043.root");
	ch->Add("/data0/e12016/70NiAnalysis/final70Ni/cal0044.root");
	ch->Add("/data0/e12016/70NiAnalysis/final70Ni/cal0045.root");
	ch->Add("/data0/e12016/70NiAnalysis/final70Ni/cal0046.root");
	ch->Add("/data0/e12016/70NiAnalysis/final70Ni/cal0048.root");
	ch->Add("/data0/e12016/70NiAnalysis/final70Ni/cal0049.root");
	ch->Add("/data0/e12016/70NiAnalysis/final70Ni/cal0060.root");
	ch->Add("/data0/e12016/70NiAnalysis/final70Ni/cal0061.root");
	ch->Add("/data0/e12016/70NiAnalysis/final70Ni/cal0062.root");
	ch->Add("/data0/e12016/70NiAnalysis/final70Ni/cal0063.root");

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

double GetDCEnergy(float en, float beta, float theta){

	return en*(1-beta*cos(theta))/sqrt(1-pow(beta,2));

}

void CheckDoppler(){

	LoadLibs();
	LoadChain();
	LoadCuts();

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

//	float beta = 0.375974;
	float beta = 0.3905;

	TCanvas *c0 = new TCanvas("c0", "Gamma-Particle angular correlation", 1000, 1000);
	c0->Divide(2,2);
	c0->cd(1);
	ch->Draw("gretinacalc.fhits->GetEnergy():gretinacalc.fhits->GetPosition().Theta()*TMath::RadToDeg()>>m_gammaraw_theta(180, 0, 180, 1000, 760, 1760)", "cut_70Ni && abs(gretinacalc.fhits->GetTime()+35) < 4", "colz");	
	c0->cd(2);
	ch->Draw("gretinacalc.fhits->GetDCEnergy():gretinacalc.fhits->GetPosition().Theta()*TMath::RadToDeg()>>m_gammaDC_theta(180, 0, 180, 1000, 760, 1760)", "cut_70Ni && abs(gretinacalc.fhits->GetTime()+35) < 4", "colz");	
	c0->cd(3);
	ch->Draw(Form("GetDCEnergy(gretinacalc.fhits->GetEnergy(), %f, gretinacalc.fhits->GetPosition().Theta()):gretinacalc.fhits->GetPosition().Theta()*TMath::RadToDeg()>>m_gammaNewDC_theta(180, 0, 180, 1000, 760, 1760)", beta), "cut_70Ni && abs(gretinacalc.fhits->GetTime()+35) < 4", "colz");
	c0->cd(4);
	ch->Draw(Form("GetDCEnergy(gretinacalc.fhits->GetEnergy(), %f, gretinacalc.fhits->GetPosition().Theta())>>h_gammaNewDC(1000, 760, 1760)", beta), "cut_70Ni && abs(gretinacalc.fhits->GetTime()+35) < 4");

}
