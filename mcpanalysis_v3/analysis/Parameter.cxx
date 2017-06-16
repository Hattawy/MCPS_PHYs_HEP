/*************************************************************************
    > File Name: Parameter.h
    > Author: Jingbo Wang
    > mail: wjingbo@anl.gov 
    > Created Time: Wed Aug  6 22:18:26 2014
	> Copyright:Those valid for ANL. Please don't distribute.
 ************************************************************************/
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include <sys/types.h>
#include "math.h"
#include <string.h>
#include <string>
#include "TROOT.h"
#include "TFrame.h"
#include "TFile.h"
#include "TChain.h"
#include <Riostream.h>
#include "TH1.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TProfile.h"
#include "TTree.h"
#include "TF1.h"
#include "TPostScript.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TSplineFit.h"
#include "UVevent.h"
#include "Parameter.h"
using namespace std;
using std::cout;
using std::endl;

Parameter::Parameter() {
	InputFileFormat = 1;
	Nacquisition = 10;						// Number of acquisitions
	NfastFrame = 1000;						// 999 UVevents per acquisition
	NChannel = 60;								// number of channels
	WavSamplingRate = 1.e10;				//Sampling rate
	WavDeltat = 100;
	WavDimSize = 256;							// 1032 samples per waveform
	NtrigChannel = 2;
	IfSelectChannel = 0;
	NChanSelected = 0;
	IfDynamicWindow = 1;
	FixTrigTwindow_min = 0;
	FixTrigTwindow_max = 25600;
	FixMcpTwindow_min = 0;
	FixMcpTwindow_max = 25600;
	DoFFT = 0;
	TrigCutoffFreq = 1.e9;
	McpCutoffFreq = 5.e8;
    ReflectionCancelling = 0;
    ReflectionWindow_min = 700000000;
    ReflectionWindow_max = 1500000000;
	TrigFraction_CFD = 0.5;
	McpFraction_CFD = 0.5;
	TrigDelay_CFD = 800;
	McpDelay_CFD = 1000;
	TrigPointsPerSpline = 1;
	McpPointsPerSpline = 5;
	IfAutoThreshold = 0;
	DoAmpCut = 1;
	AmpThreshold = 50;
	DoTotCut = 1;
	TrigTotThreshold = 50;
	McpTotThreshold = 50;
	TrigMinimumTot = 800;
	McpMinimumTot = 1500;
	DoAnalysis = 0;
	DoCalibration = 0;
	WavSample = new float*[NChannel];
	for( int i = 0; i < NChannel; i++ ) {
		WavSample[i] = new float[WavDimSize];
	}
}

Parameter::~Parameter() {
	for( int i = 0; i < NChannel; i++ ) {
		delete []WavSample[i];
		WavSample[i] = 0;
	}
	delete []WavSample;
	WavSample = 0;
}

void Parameter::ReadParameters(char* par) {
	string name;
	int fileopt, k;
	ifstream parin;
	parin.open(par, ios::in);					//open input .txt files
	parin>>name>>InputFileFormat>>name>>Nacquisition>>name>>NfastFrame>>name>>NChannel;
	parin>>name>>WavSamplingRate>>name>>WavDeltat>>name>>WavDimSize;
	parin>>name>>NtrigChannel>>name;
	for(int i=0;i<NtrigChannel;i++) {
		parin>>k;
		WhichTrig.push_back(k);
	}
	parin>>name;
	parin>>IfSelectChannel>>name>>NChanSelected>>name;
	for(int i=0;i<NChanSelected;i++) {
		parin>>k;
		WhichChannel.push_back(k);
	}
	parin>>name>>IfDynamicWindow>>name>>FixTrigTwindow_min>>FixTrigTwindow_max>>name>>FixMcpTwindow_min>>FixMcpTwindow_max;
	parin>>name>>DoFFT>>name>>TrigCutoffFreq>>name>>McpCutoffFreq;
    parin>>name>>ReflectionCancelling>>name>>ReflectionWindow_min>>ReflectionWindow_max;
	parin>>name>>TrigFraction_CFD>>name>>McpFraction_CFD>>name>>TrigDelay_CFD>>name>>McpDelay_CFD>>name>>TrigPointsPerSpline>>name>>McpPointsPerSpline;
	parin>>name>>DoAmpCut>>name>>AmpThreshold;
	parin>>name>>DoTotCut>>name>>TrigTotThreshold>>name>>McpTotThreshold>>name>>TrigMinimumTot>>name>>McpMinimumTot;
	parin>>name>>DoAnalysis;
    parin>>name>>ProfileMode;
    parin>>name>>BinSizeMode;
    parin>>name>>NCalibration;
    parin>>name>>NIteration;
    parin>>name>>DataYmean;
    parin>>name>>DataYBins>>DataYmin>>DataYmax;

    int kbins;
    double kmin, kmax;
    for(int i=0;i<NCalibration;i++) {
		parin>>name>>kbins>>kmin>>kmax;
		DataXBins.push_back(kbins);
        DataXmin.push_back(kmin);
        DataXmax.push_back(kmax);
	}
}

void Parameter::SetTriggerFlag(int fsign) {
	for(int i=0;i<NChannel;i++) {trigflag.push_back(0);}	//Set all flag to 0;
	for(int i=0;i<NtrigChannel;i++) {
		int k = WhichTrig.at(i);
		if(k<=NChannel) trigflag.at(k) = fsign;					//Set trigger trigflag to 1; (HEP Format)
		else cout<<"Error: Trigger Channel out of range "<<NChannel<<endl;
	} 
}

void Parameter::SetSelectionFlag(int flag) {
	for(int i=0;i<NChannel;i++) {selection.push_back(0);}	//Set all channel-flag to 0;
	for(int i=0;i<NChanSelected;i++) {
		int k = WhichChannel.at(i);
		if(k<=NChannel) selection.at(k) = 1;					//Set selected channel-flag to 1;
		else cout<<"Error: Selected Channel out of range "<<NChannel<<endl;
	}
}


