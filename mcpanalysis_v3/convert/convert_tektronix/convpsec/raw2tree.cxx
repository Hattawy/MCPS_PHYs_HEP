/*************************************************************************
    > File Name: raw2tree.C
    > Author: Jingbo Wang
    > mail: wjingbo@anl.gov 
    > Created Time: Mon Jul  7 12:05:18 2014
 ************************************************************************/

#ifndef __CINT__
#include "iostream"
#include "fstream"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "TStopWatch.h"
using namespace std;
#endif

char rawdata[200]="Data/run13_170409_0421.txt";
char outroot[200]="psec.root";
char treename[200]="h1";

Int_t main(Int_t argc, Char_t* argv[]){

	if(argc<3)exit(0);
	strcpy(rawdata,argv[1]);
	strcpy(outroot,argv[2]);
	TFile f(outroot, "recreate");

	Int_t			nsa = 0;
	Int_t			evtno=0;
	Float_t         t[256];
	Int_t           nChannels;
	Int_t           nSamples;
	Float_t         vol[60][256];
	Float_t         meta[2][256];

	TTree t1(treename, treename);
	t1.Branch("evtno", &evtno, "evtno/I");
	t1.Branch("nChannels", &nChannels, "nChannels/I");
	t1.Branch("nSamples", &nSamples, "nSamples/I");
	t1.Branch("t", &t, "t[256]/F");
	t1.Branch("vol", &vol, "vol[60][256]/F");
	t1.Branch("meta", &meta, "meta[2][256]/F");

	ifstream is;
	is.open(rawdata, ios::in);
	TStopwatch clock;								//runtime clock
	clock.Start();									//clock started	  

	while(is>>nsa
			>>vol[0][nsa]>>vol[1][nsa]>>vol[2][nsa]>>vol[3][nsa]>>vol[4][nsa]
			>>vol[5][nsa]>>vol[6][nsa]>>vol[7][nsa]>>vol[8][nsa]>>vol[9][nsa]
			>>vol[10][nsa]>>vol[11][nsa]>>vol[12][nsa]>>vol[13][nsa]>>vol[14][nsa]
			>>vol[15][nsa]>>vol[16][nsa]>>vol[17][nsa]>>vol[18][nsa]>>vol[19][nsa]
			>>vol[20][nsa]>>vol[21][nsa]>>vol[22][nsa]>>vol[23][nsa]>>vol[24][nsa]
			>>vol[25][nsa]>>vol[26][nsa]>>vol[27][nsa]>>vol[28][nsa]>>vol[29][nsa]
			>>meta[0][nsa]
			>>nsa
			>>vol[59][nsa]>>vol[58][nsa]>>vol[57][nsa]>>vol[56][nsa]>>vol[55][nsa]
			>>vol[54][nsa]>>vol[53][nsa]>>vol[52][nsa]>>vol[51][nsa]>>vol[50][nsa]
			>>vol[49][nsa]>>vol[48][nsa]>>vol[47][nsa]>>vol[46][nsa]>>vol[45][nsa]
			>>vol[44][nsa]>>vol[43][nsa]>>vol[42][nsa]>>vol[41][nsa]>>vol[40][nsa]
			>>vol[39][nsa]>>vol[38][nsa]>>vol[37][nsa]>>vol[36][nsa]>>vol[35][nsa]
			>>vol[34][nsa]>>vol[33][nsa]>>vol[32][nsa]>>vol[31][nsa]>>vol[30][nsa]
			>>meta[1][nsa]) {

		nChannels = 60;
		nSamples = 256;
		if(nsa==nSamples-1) {
			for(Int_t i=0;i<nSamples;i++) {
				t[i] = i*100.;
			}
			t1.Fill();
			evtno++;
			clock.Stop();
			if(evtno%100 == 0) cout<<"converting "<<evtno<<"th event..."<<"\t"<<"CpuTime = "<<clock.CpuTime()<<" s"<<endl;
			clock.Continue();
		}			
	}

	t1.Write();
	f.Close();
	is.close();
} 
