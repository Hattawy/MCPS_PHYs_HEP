/*************************************************************************
    > File Name: Analysis.h
    > Author: Jingbo Wang
    > mail: wjingbo@anl.gov 
    > Created Time: Wed Aug  6 22:18:26 2014
 ************************************************************************/
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include <sys/types.h>
#include "math.h"
#include "string.h"
#include "TROOT.h"
#include "TFrame.h"
#include "TFile.h"
#include "TChain.h"
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
#include "Analysis.h"
using namespace std;
using std::cout;
using std::endl;

Analysis::Analysis() {
	ProfileMode = 0;
	BinSizeMode = 0;
}

void Analysis::SetVarsForAnalysis(UVevent* fevt) {
//	cout<<"-------------------------Get Vars for Analysis------------------------------------------"<<endl;
	//--------- Calculate variables of interest ------
	float t[100], q[100];
	t[0] = ((Waveform*)(fevt->fwav->ConstructedAt(0)))->time;
	t[1] = ((Waveform*)(fevt->fwav->ConstructedAt(1)))->time;
	t[2] = ((Waveform*)(fevt->fwav->ConstructedAt(2)))->time;
	t[3] = ((Waveform*)(fevt->fwav->ConstructedAt(3)))->time;
	t[4] = ((Waveform*)(fevt->fwav->ConstructedAt(0)))->risingtime;
	t[5] = ((Waveform*)(fevt->fwav->ConstructedAt(1)))->risingtime;
	t[6] = ((Waveform*)(fevt->fwav->ConstructedAt(2)))->risingtime;
	t[7] = ((Waveform*)(fevt->fwav->ConstructedAt(3)))->risingtime;
	q[0] = ((Waveform*)(fevt->fwav->ConstructedAt(0)))->amp;
	q[1] = ((Waveform*)(fevt->fwav->ConstructedAt(1)))->amp;
	q[2] = ((Waveform*)(fevt->fwav->ConstructedAt(2)))->amp;
	q[3] = ((Waveform*)(fevt->fwav->ConstructedAt(3)))->amp;
	

	float tref = t[0];
	float tabs = (t[1]+t[2])/2.-t[0];
	float tdiff = t[1] - t[2];

	//---------- Add cuts here ---------
	if(t[1]==0 || t[2]==0)			return;
	if(t[5]>1300 || t[6]>1300)		return;
	if(q[1]<0.5 || q[1]>4.5)				return;
	if(q[2]<0.5 || q[2]>4.5)				return;
//	if(tabs < -8000 || tabs > -6000)			return;
	fevt->SetCutflag(1);

	//---------- Add variables to UVevent --------------
	fevt->SetTransitTime(tabs);
	fevt->SetDifferentialTime(tdiff);

	//------- Store variables for Calibration ----------
	CalibY[0].push_back(tref);
	CalibY[1].push_back(tabs);
	CalibY[2].push_back(tdiff);
	CalibX[0].push_back(q[1]);
	CalibX[1].push_back(q[2]);
	CalibX[2].push_back(t[5]);
	CalibX[3].push_back(t[6]);
	
}

void Analysis::Analyze(TFile *f) {
	cout<<endl<<endl;
	cout<<"-------------------------Come to Analysis------------------------------------------"<<endl;
	TF1 *f1 = new TF1("f1","gaus");
	TCanvas *canvas_raw = new TCanvas("canvas_raw","canvas_raw",0,0,1000,800);
	int size, nbins;
	float mean, rms;
	double para[3];
/*	//--------------------------- reference time resolution ---------------------------
	f->cd();
	mean = -25760;
	TH1D *tref = new TH1D("tref","tref",400,-100,100);
	for(int i=0;i<CalibY[0].size();i++) {
		CalibY[0].at(i) += mean;
		tref->Fill(CalibY[0].at(i));
	}
	mean = tref->GetMean();
	rms = tref->GetRMS();
	tref->Fit("f1", "nqr", "", mean-3*rms, mean+3*rms);
	f1->GetParameters(&para[0]);
	tref->Fit("f1", "qr", "", para[1]-3*para[2], para[1]+3*para[2]);
	tref->Write();
	cout<<"Sigma_ref = "<<f1->GetParameter(2)<<"/1.414 = "<<f1->GetParameter(2)/1.414<<" ps"<<endl<<endl;
	delete tref; tref = 0;*/
	
	//----------------------------transit time resolution------------------------------	
	f->cd();
//	mean = -9679; //run8
	mean = 6125; //run9
	TH1D *tabs = new TH1D("tabs","tabs",200,-1000,1000);
	for(int i=0;i<CalibY[1].size();i++) {
		CalibY[1].at(i) += mean;
		tabs->Fill(CalibY[1].at(i));
	}
	mean = tabs->GetMean();
	rms = tabs->GetRMS();
	tabs->Fit("f1", "nqr", "", mean-3*rms, mean+3*rms);
	f1->GetParameters(&para[0]);
	tabs->Fit("f1", "qr", "", para[1]-3*para[2], para[1]+3*para[2]);
	tabs->Write();
	cout<<"Sigma_abs = "<<f1->GetParameter(2)<<" +- "<<f1->GetParError(2)<<endl<<endl;
	delete tabs; tabs = 0;

	//------------------------------ Slewing correction ----------------------------------------
	int NCalib = 2;
	f->cd("raw");
	int ir = 0;
	double xmin[4] = {0, 0, 800, 800};
	double xmax[4] = {4.5, 4.5, 1200, 1200};
	while(ir<5) {
		if(ir == 0){
			cout<<"=======================... raw time resolution ... =======================" << endl;
			for(int ichan=0;ichan<4;ichan++){
				Calibration *docalib = new Calibration(CalibX[ichan], CalibY[1], ir, ichan, ProfileMode, BinSizeMode, 20, xmin[ichan], xmax[ichan], 100,-400, 400); 
				docalib->Slewing(false); //"true": do correction; "false": do nothing
				f->cd("raw");
				docalib->DeltaT->Write();
				docalib->Channel->Write();
				docalib->htsf->Write();
				docalib->f1->Write();
				cout<<"sigma["<<ichan<<"]\t=\t"<<docalib->Sigma<<" +- "<<docalib->Error<<endl;
				delete docalib; docalib = 0;
			}
		}

			cout<<endl;
			cout<<"=======================... "<<ir<< "-th iteration ... =======================" << endl;
			for(int ichan=0;ichan<4;ichan++){
				Calibration *docalib = new Calibration(CalibX[ichan], CalibY[1], ir, ichan, ProfileMode, BinSizeMode, 20, xmin[ichan], xmax[ichan], 100,-400, 400); 
				docalib->Slewing(true); //"true": do correction; "false": do nothing
				f->cd("cor");
				docalib->DeltaT->Write();
				docalib->Channel->Write();
				docalib->htsf->Write();
				docalib->f1->Write();
				CalibY[1] = docalib->Y; //vector after correction
				cout<<"sigma["<<ichan<<"]\t=\t"<<docalib->Sigma<<" +- "<<docalib->Error<<endl;
				delete docalib; docalib = 0;
			}	
		
		ir++;
		cout<<endl;
	}

	//---------------------------------------------------------------------------------
	//----------------------------differential time resolution---------------------------------
	f->cd();
//	mean = -2481; //run8
	mean = -1382; //run9
	TH1D *tdiff = new TH1D("tdiff","tdiff",200,-500,500);
	for(int i=0;i<CalibY[2].size();i++) {
		CalibY[2].at(i) += mean;
		tdiff->Fill(CalibY[2].at(i));
	}
	mean = tdiff->GetMean();
	rms = tdiff->GetRMS();
	tdiff->Fit("f1", "nqr", "", mean-3*rms, mean+3*rms);
	f1->GetParameters(&para[0]);
	tdiff->Fit("f1", "qr", "", para[1]-3*para[2], para[1]+3*para[2]);
	tdiff->Write();
	cout<<"Sigma_differential = "<<f1->GetParameter(2)<<" +- "<<f1->GetParError(2)<<endl<<endl;
	delete tdiff; tdiff = 0;
	
	//---------------------------------------------------------------------------------
	//----------------------------free memory---------------------------------
	delete f1; f1 = 0;
	delete canvas_raw; canvas_raw = 0;
}

//Plot
void Analysis::Plot(TFile *f) {
}
