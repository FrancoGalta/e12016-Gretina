TChain *ch;

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

bool iscoinc(Short_t reg) {
	return reg & (1 << 1);
}

void MakeChain_68Ni(){

	LoadLibs();

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
