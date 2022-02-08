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

void MakeChain_70Ni(){

	LoadLibs();

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
