/*************************************************************************
    > File Name: Parameter.h
    > Author: Jingbo Wang
    > mail: wjingbo@anl.gov 
    > Created Time: Wed Aug  6 22:18:26 2014
	> Copyright:Those valid for ANL. Please don't distribute.
 ************************************************************************/
#ifndef NOISESPECTRUM
#define NOISESPECTRUM

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

class NoiseSpectrum
{
	private:
		
	
	public: 
		//------------------Parameter file format-------------------------------------------// 
		TH1F *
  
		NoiseSpectrum();
		~NoiseSpectrum();
		void ReadNoiseSpectrum(char* par);
};
#endif
