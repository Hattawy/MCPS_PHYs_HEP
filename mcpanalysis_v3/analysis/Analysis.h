/*************************************************************************
    > File Name: Analysis.h
    > Author: Jingbo Wang
    > mail: wjingbo@anl.gov 
    > Created Time: Wed Aug  6 22:18:26 2014
	> Copyright:Those valid for ANL. Please don't distribute.
 ************************************************************************/
#ifndef ANALYSIS
#define ANALYSIS

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
using namespace std;
using std::cout;
using std::endl;

class Analysis
{
	private:
		int ProfileMode;
		int BinSizeMode;
	
	public: 
		
		vector<double> CalibY[20];						
		vector<double> CalibX[20];
        int NIteration;
		int	NCalibration;
        double DataYmean;
        double DataYBins;
        double DataYmin;
        double DataYmax;
        vector<int> DataXBins;
        vector<double> DataXmin;
        vector<double> DataXmax;
        
  
		Analysis();
		~Analysis() {}
		void SetVarsForAnalysis(UVevent* fevent);
		void Analyze(TFile *f);
		void Plot(TFile *f);
		int SetProfileMode(int fopt) {ProfileMode = fopt; return ProfileMode;}
		int SetBinSizeMode(int fopt) {BinSizeMode = fopt; return BinSizeMode;}
		int SetNIteration(int fn)	{NIteration = fn; return NIteration;}
		int SetNCalibration(int fn)	{NCalibration = fn; return NCalibration;}
        double SetDataYmean(double fymean)  {DataYmean = fymean; return DataYmean;}
        void SetDataYBins(int fbins, double fymin, double fymax) {
            DataYBins = fbins;
            DataYmin = fymin;
            DataYmax = fymax;
        }
        void SetDataXBins(vector<int> fxbins, vector<double> fxmin, vector<double> fxmax) {
            DataXBins = fxbins;
            DataXmin = fxmin;
            DataXmax = fxmax;
        }
  
};
#endif
