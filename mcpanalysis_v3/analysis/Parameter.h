/*************************************************************************
    > File Name: Parameter.h
    > Author: Jingbo Wang
    > mail: wjingbo@anl.gov 
    > Created Time: Wed Aug  6 22:18:26 2014
	> Copyright:Those valid for ANL. Please don't distribute.
 ************************************************************************/
#ifndef PARAMETER
#define PARAMETER

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

class Parameter
{
	private:
		
	
	public: 
		//------------------Parameter file format-------------------------------------------// 
		int				InputFileFormat;
		int				Nacquisition;						// Number of acquisitions
		int				NfastFrame;						// 999 UVevents per acquisition
		int				NChannel;								// number of channels
		float			WavSamplingRate;				//Sampling rate
		float			WavDeltat;
		int				WavDimSize;							// 1032 samples per waveform		
		int				NtrigChannel;
		vector<int>		WhichTrig;
		int				IfSelectChannel;
		int				NChanSelected;
		vector<int>		WhichChannel;
		int				IfDynamicWindow;
		float			FixTrigTwindow_min;
		float			FixTrigTwindow_max;
		float			FixMcpTwindow_min;
		float			FixMcpTwindow_max;
		int				DoFFT;
		float			TrigCutoffFreq;
		float			McpCutoffFreq;
        int             ReflectionCancelling;
        float           ReflectionWindow_min;
        float           ReflectionWindow_max;
		float			TrigFraction_CFD;
		float			McpFraction_CFD;
		float			TrigDelay_CFD;
		float			McpDelay_CFD;
		int				TrigPointsPerSpline;
		int				McpPointsPerSpline;
		int				IfAutoThreshold;
		int				DoAmpCut;
		float			AmpThreshold;
		int				DoTotCut;
		float			TrigTotThreshold;
		float			McpTotThreshold;
		float			TrigMinimumTot;
		float			McpMinimumTot;
		int				DoAnalysis;
		int				DoCalibration;
        int             NIteration;
		int	            NCalibration;
        int             ProfileMode;
        int             BinSizeMode;
        double          DataYmean;
        double          DataYBins;
        double          DataYmin;
        double          DataYmax;
        vector<int>     DataXBins;
        vector<double>  DataXmin;
        vector<double>  DataXmax;
		vector<int>		trigflag;
		vector<int>		selection;
		float**			WavSample;
  
		Parameter();
		~Parameter();
		void ReadParameters(char* par);
		void SetTriggerFlag(int fsign);
		void SetSelectionFlag(int flag);
};
#endif
