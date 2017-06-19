//----------APS Analysis 
//----------Author's Name:Jingbo WANG
//----------Modified:22/07/2014
//----------Copyright:Those valid for ANL. Please don't distribute.
////  Run this Code by command :
//		(1) ./lappd inputfile XXX.root parameterfile
//		(2) ./lappd inputfile XXX.root parameterfile UVeventnumber
//		(3) ./lappd inputfile XXX.root parameterfile StartUVeventNumber EndUVeventNumber
//
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include <sys/types.h>
#include "math.h"
#include <string.h>
#include <string>
#ifndef __CINT__
#include "TROOT.h"
#include "TFrame.h"
#include "TFile.h" 
#include "TChain.h"
#include <Riostream.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
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
#include "TStopwatch.h"
#include "Calibration.h"
#include "TSplineFit.h"
#include "UVevent.h"
#include "Analysis.h"
#include "Parameter.h"
using namespace std;
using std::cout;
using std::endl;
#endif


char*	treename="lappd"; 
int		MaximumEntry = 100;	// anslyze a user defined number of UVevents
int		StartEntry = 0;		// if(argc==4) Start analysis from this entry
int		EndEntry = 100;		// if(argc==4) End analysis at this entry

void SetParameters(char *par);
//Slewing correction
int		ProfileMode = 0;
int		BinSizeMode = 1;
vector<double>  CalibY[20];	        // Amplitude
vector<double>  CalibX[20];		// Time

//===========================================================================================================
//	Start main() function
//-----------------------------------------------------------------------------------------------------------
int main(int argc, char **argv) {
	
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"-------------------------------------------------------------------"<<endl;

	//------------------Set input and output filenames------------------------------// 
	
	TStopwatch clock;			        //runtime clock
	clock.Start();					//clock started	  
	char *FileInput = "test.fff";			//default input file
	char *FileOutput = "otp.root";			//default output file
	char *FileParameters = "paf";
	switch(argc){
		case 1: {
                          cout<<"Error: File name required as the 2nd statement"<<endl; 
                          break;
                          } 
		case 2: {
                          FileInput = argv[1];
                          char* stype = ".root";
                          int len=strlen(FileInput)+strlen(stype)+1;
                          FileOutput=(char *)malloc(len);
                          snprintf(FileOutput, len, "%s%s", FileInput, stype);
                          MaximumEntry = 1e12; // a big number
                          break; 
                          }
		case 3: { 
                          FileInput = argv[1]; 
                          FileOutput = argv[2]; 
                          break;
                          } 
		case 4: {
                          FileInput = argv[1]; 
                          FileOutput = argv[2]; 
                          FileParameters = argv[3]; 
                          break;
                          }
		case 5: {
                          FileInput = argv[1]; 
                          FileOutput = argv[2]; 
                          FileParameters = argv[3]; 
                          MaximumEntry = atoi(argv[4]); 
                          break;
                          }
		case 6: {
                          FileInput = argv[1]; 
                          FileOutput = argv[2]; 
                          FileParameters = argv[3]; 
                          StartEntry = atoi(argv[4]); 
                          EndEntry = atoi(argv[5]); 
                          break;
                          }
        }
	cout<<"Input file:"<<"\t"<< FileInput << endl;
	cout<< "Output file:"<<"\t" << FileOutput << endl;
	cout<<"Parameter file:"<<"\t"<< FileParameters << endl;

	//--------------------------Set parameters----------------------------------------------------//
	Parameter par;
	par.ReadParameters(FileParameters);
	par.SetTriggerFlag(1);
	par.SetSelectionFlag(1);
        cout<<" Done setting the parameters"<<endl;

	//------------------Create a root file--------------------------------------------------------//
	TFile *f = new TFile(FileOutput, "RECREATE");	//open a file
	TTree lappd(treename, treename);		//create a tree
	UVevent *evt = new UVevent();			//point to class UVevent
	lappd.Branch("evt", &evt, 16000, 99);	        //Set branches with "split" option
	f->mkdir("wav");				//histograms of waveform
	f->mkdir("cfd");				//constant fraction discrimination
	f->mkdir("raw");
	f->mkdir("cor");
	f->mkdir("raw2");
	f->mkdir("cor2");
	f->mkdir("plots");
	Analysis Ana;

        if(par.DoAnalysis) {
         Ana.SetProfileMode(par.ProfileMode);
     	 Ana.SetBinSizeMode(par.BinSizeMode);
         Ana.SetNIteration(par.NIteration);
         Ana.SetNCalibration(par.NCalibration);
         Ana.SetDataYmean(par.DataYmean);
         Ana.SetDataYBins(par.DataYBins, par.DataYmin, par.DataYmax);
         Ana.SetDataXBins(par.DataXBins, par.DataXmin, par.DataXmax);
        }
        cout<<" Done setting the root file"<<endl;

	//---------------------Fill a tree------------------------------------------------------------//
	ifstream *isin = new ifstream();
	isin->open(FileInput, ios::in);			   //open input .txt files
	// float** WavSample;
	float WavSample[par.NChannel][par.WavDimSize];
	int Nentries = par.Nacquisition*par.NfastFrame;	   //number of entries
	
	cout<<"Total # of UVevents = "<<Nentries<<endl;

	
	for (int i=0;i<Nentries;i++) {
		if(argc==5) {if(i>=MaximumEntry) break;}
		if(argc==6) {if(i<StartEntry) continue; if(i>=EndEntry) break;}
		clock.Stop();
		if(i%100 == 0) cout<<"processing "<<i<<"th UVevent..."<<"\t"<<"CpuTime = "<<clock.CpuTime()<<" s"<<endl;
		clock.Continue();		
		evt->Setevtno(i);			   //Set UVevent number
		evt->SetWavDimSize(par.WavDimSize);
		evt->SetWavSampleRate(par.WavSamplingRate);
		evt->Initialize();

	//------------------------------------read Chicago-scope APS data file----------------------------
		if(par.InputFileFormat == 0) {
			for(int m=0;m<par.NChannel;m++) {
				for(int n=0;n<par.WavDimSize;n++) {	
				*isin>>WavSample[m][n];
				if(par.trigflag.at(m) == 1) WavSample[m][n] *= 1;
				else WavSample[m][n] *= -1;				
				}
			}
		}

	//------------------------------------read psec data file-----------------------------------------
		if(par.InputFileFormat == 1) {
			int nsa = 0;					//read waveforms
			float meta = 0;
			for(int n=0;n<par.WavDimSize;n++) {
				*isin>>nsa;
				for(int m=0;m<par.NChannel/2;m++) {
					*isin>>WavSample[m][n];
					if(par.trigflag.at(m) == 1) WavSample[m][n] *= 1;
					else WavSample[m][n] *= 1;
				}
				*isin>>meta;
				*isin>>nsa;
				for(int m=par.NChannel-1;m>=par.NChannel/2;m--) {
					*isin>>WavSample[m][n];
					if(par.trigflag.at(m) == 1) WavSample[m][n] *= -1;
					else WavSample[m][n] *= 1;
				}
				*isin>>meta;
			}
		}

	//------------------------------------read Chicago-scope HEP data file----------------------------
		if(par.InputFileFormat == 2) {
			
			for(int m=0;m<par.NChannel;m++) {
				for(int n=0;n<par.WavDimSize;n++) {	
				*isin>>WavSample[m][n];
				if(par.trigflag.at(m) == 1) WavSample[m][n] *= -1;
				else WavSample[m][n] *= -1;
				
				}
			}
		}

	//--------------------------------------read .cvs scope data--------------------------------------
		if(par.InputFileFormat == 3) {
			
			string line;
			string volt;
			if(isin->tellg()==0) {
				getline(*isin, line);
				getline(*isin, line);
				getline(*isin, line);
			}
			for(int n=0;n<par.WavDimSize;n++) {
				getline(*isin, line);
				// cout<<line<<endl;
				istringstream sin(line);
				for(int m=0;m<par.NChannel;m++) {
					getline(sin, volt, ',');
					getline(sin, volt, ',');
					WavSample[m][n] = atof(volt.c_str());
					WavSample[m][n] *= 1000;
					// cout<<WavSample[m][n]<<"\t";
					if(par.trigflag.at(m) == 1) WavSample[m][n] *= 1;
					else WavSample[m][n] *= 1;
				}
				// cout<<endl;
			}
		}
	//----------------------------------------------------------------------------------
	//---------------------------------read JLab scope data-----------------------------
		if(par.InputFileFormat == 4) {

			for(int n=0;n<par.WavDimSize;n++) {
				for(int m=0;m<par.NChannel;m++) {	
				*isin>>WavSample[m][n];
				WavSample[m][n] *= 1000;
				if(par.trigflag.at(m) == 1) WavSample[m][n] *= 1;
				else WavSample[m][n] *= 1;
				}
			}
		}
	//-----------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------
	//-----------------------------read Agilent scope data-------------------------------
		if(par.InputFileFormat == 5) {

			string line;
			getline(*isin, line);
			// cout<<line<<endl;
			for(int n=0;n<par.WavDimSize;n++) {
				for(int m=0;m<par.NChannel;m++) {	
					*isin>>WavSample[m][n];
					WavSample[m][n] = WavSample[m][n]*1000;
				}
			}
			*isin>>line;
		}
	//-----------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------
	//-----------------read Anatoly scope data-------------------------------------------
		if(par.InputFileFormat == 6) {
			
			for(int m=0;m<par.NChannel;m++) {
				for(int n=0;n<par.WavDimSize;n++) {	
				*isin>>WavSample[m][n];
				if(par.trigflag.at(m) == 1) WavSample[m][n] *= 1;
				else WavSample[m][n] *= 1;				
				}
			}
		}
	//-----------------------------------------------------------------------------------
        //-----------------read Agilent scope data at AWA------------------------------------
		if(par.InputFileFormat == 7) {

			string line;
			getline(*isin, line);
			// cout<<line<<endl;
			for(int n=0;n<par.WavDimSize;n++) {
				for(int m=0;m<par.NChannel;m++) {	
					*isin>>WavSample[m][n];
					if(m==0) WavSample[m][n] = -1.0*WavSample[m][n]*1000;
                    else  WavSample[m][n] = WavSample[m][n]*1000;
				}
			}
			*isin>>line;
		}
	//-----------------------------------------------------------------------------------

        // cout<<isin->eof()<<endl;
        if(isin->eof()) break;
        int fnwav = 0;
		for(int m=0;m<par.NChannel;m++) {	//loop over channels								
			
			if(par.IfSelectChannel==1) {if(par.selection.at(m)==0) continue;}
			int WavID = (i+1)*100+m;		//Waveform ID = evtno*100+ChannalNum
			Waveform *waveform = (Waveform*)(evt->fwav->ConstructedAt(evt->fnwav++));
			waveform->Setevtno(i);
			waveform->Setchno(m);
			waveform->SetSamplingrate(par.WavSamplingRate);
			waveform->SetDeltat(par.WavDeltat);
			waveform->SetDimSize(par.WavDimSize);
			waveform->Initialize(&WavSample[m][0]);
			if(par.AmpThreshold>=0) waveform->SetAmpThreshold(par.AmpThreshold);
			if(par.trigflag.at(m)==1) {		//trigger
                                waveform->SetTriggerMarker(1);
				if(par.TrigTotThreshold>=0) waveform->SetTotThreshold(par.TrigTotThreshold);
				waveform->SetMinimumTot(par.TrigMinimumTot);
				waveform->SetCutoffFrequency(par.TrigCutoffFreq);
				waveform->SetPointsPerSpline(par.TrigPointsPerSpline);
				waveform->SetFraction_CFD(par.TrigFraction_CFD);
				waveform->SetDelay_CFD(par.TrigDelay_CFD);
				waveform->SetFitWindow(par.FixTrigTwindow_min, par.FixTrigTwindow_max);
			}
			else {									//mcp
                                waveform->SetTriggerMarker(0);
				if(par.McpTotThreshold>=0) waveform->SetTotThreshold(par.McpTotThreshold);
				waveform->SetMinimumTot(par.McpMinimumTot);
				waveform->SetCutoffFrequency(par.McpCutoffFreq);
				waveform->SetPointsPerSpline(par.McpPointsPerSpline);
				waveform->SetFraction_CFD(par.McpFraction_CFD);
				waveform->SetDelay_CFD(par.McpDelay_CFD);
				waveform->SetFitWindow(par.FixMcpTwindow_min, par.FixMcpTwindow_max);
			}
			if(par.DoFFT==1) waveform->EnableFFT();
                        if(par.ReflectionCancelling==1) waveform->EnableReflectionCancelling();
			if(par.IfDynamicWindow == 1) waveform->EnableDynamicWindow();
			waveform->Analyze();		//analyze waveform
			f->cd("wav");			//go to folder "/waveform"
			if(i<100 && waveform->amp>0.5) 
                          waveform->hwav->Write();	//write histograms for waveforms
			f->cd("cfd");
			if(i<100 && waveform->amp>0.5) waveform->hcfd->Write();
		}
		if(par.DoAnalysis) Ana.SetVarsForAnalysis(evt);
		lappd.Fill();				//Fill tree
		
		evt->Clear();				//free memory (! to be carefully checked)		
	}

	f->cd();				        //home folder
	if(par.DoAnalysis) Ana.Analyze(f);									
	lappd.Write();					//write tree
	isin->close();
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"-------------------------------------------------------------------"<<endl;
        // if(par.DoAnalysis) Ana.Plot(f);
	f->Close();
        // delete f; f=0;
	return 0;
}
//-----------------------------------------------------------------------------------------------------------
//	End main() function
//===========================================================================================================
