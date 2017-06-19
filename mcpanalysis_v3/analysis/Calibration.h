//----------For MRPC TOF Calibration only
//----------Author's Name:Jingbo WANG
//----------Copyright:Those valid for Tsinghua University
//----------Modified:17/03/2012
#ifndef CALIBRATION
#define CALIBRATION

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
using namespace std;
using std::cout;
using std::endl;



class Calibration
{
 public:   
  int ProfileMode; //0-use ProfileX(), 1-use FitSliceY()
  int BinSizeMode; //0-fixed binsize, 1-variable binsize
  int Niteration; //iteration time, >1
  int Nchannel; //number of channels 
  int size;
  vector<double> X,Y;
  double Xmin,Xmax,Ymin,Ymax;
  int NbinsX,NbinsY;
  double Sigma;
  Double_t Error;
  
  float tot[6][500000];
  float tdc[6][500000];
  float tof[500000];
  TH1D *DeltaT, *DeltaT_cor;
  TH2D *Channel, *Channel_cor;
  TH1D *htsf;
  TSplineFit *tsf;
  TF1 *f1;
  TF1 *f2;
  int tsfm; //number of measurements per spline. >1
  Char_t Fitfunction[100];
  
  Calibration();
  Calibration(vector<double> &fx, vector<double> &fy, int fNiteration, int fNchannel, int fProfileMode, int fBinSizeMode);
  Calibration(vector<double> &fx, vector<double> &fy, int fNiteration, int fNchannel, int fProfileMode, int fBinSizeMode, int fNbinsX, int fNbinsY);
  Calibration(vector<double> &fx, vector<double> &fy, int fNiteration, int fNchannel, int fProfileMode, int fBinSizeMode, int fNbinsX, double fXmin, double fXmax, int fNbinsY, double fYmin, double fYmax);
  ~Calibration();
  TH2D *Slewing(bool fOption); //fOption = "true": do correction; fOption = "false": do nothing
  float SetXmin(float fxmin) {Xmin = fxmin; return Xmin;}
  float SetXmax(float fxmax) {Xmax = fxmax; return Xmax;}
  float SetYmin(float fymin) {Ymin = fymin; return Ymin;}
  float SetYmax(float fymax) {Ymax = fymax; return Ymax;}
  int	SetNbinsX(int fn)	 {NbinsX = fn; return NbinsX;}
  int	SetNbinsY(int fn)	 {NbinsY = fn; return NbinsY;}
  int	SetProfileMode(int fn) {ProfileMode = fn; return ProfileMode;}
  int	SetBinSizeMode(int fn) {BinSizeMode = fn; return BinSizeMode;}
  int	SetNiteration(int fn)  {Niteration = fn; return Niteration;}
  int	SetNchannel(int fn)		{Nchannel = fn; return Nchannel;}
private:
  
  void SetBounds(vector<double> &fx, vector<double> &fy);
  void InitBin(vector<double> &fx, int fBinSizeMode);
};
#endif







