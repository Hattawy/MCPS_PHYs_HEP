//----------For MRPC TOF Calibration only 
//----------Author's Name:Jingbo WANG
//----------Copyright:Those valid for Tsinghua University
//----------Modified:17/03/2012

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
#include "Calibration.h"
using namespace std;
using std::cout;
using std::endl;

/*************************************************************************************************
  ProfileMode = 0:        use ProfileX() (recommended)
  ProfileMode = 1:     use FitSliceY()
  BinSizeMode = 0:   use fixed bin size (recommended)
  BinSizeMode = 1:      use variable bin size
  
  tsfm>1:                   measured points in a splinefit, use small number to get high resolution
  fNiteration:            iteration ID
  fNchannel:              channel ID         
*************************************************************************************************/

Calibration::Calibration() {cout<<"Error!"<<endl;}
Calibration::Calibration(vector<double> &fx, vector<double> &fy, int fNiteration, int fNchannel, int fProfileMode, int fBinSizeMode)
{
//  cout<<"---------"<<fNiteration+1<<"-st iteration!--------------------"<<endl;
  ProfileMode = fProfileMode; 
  BinSizeMode = fBinSizeMode;
  tsfm = 5; 
  size = fx.size();
  X = fx;
  Y = fy;
  Niteration = fNiteration;
  Nchannel = fNchannel; 
  SetBounds(X, Y); //Explore bounds atomatically
  InitBin(X,BinSizeMode); 
  
}

Calibration::Calibration(vector<double> &fx, vector<double> &fy, int fNiteration, int fNchannel, int fProfileMode, int fBinSizeMode, int fNbinsX, int fNbinsY)
{
//  cout<<"---------"<<fNiteration+1<<"-st iteration!--------------------"<<endl;
  ProfileMode = fProfileMode; 
  BinSizeMode = fBinSizeMode;
  tsfm = 5; 
  size = fx.size();
  X = fx;
  Y = fy;
  Niteration = fNiteration;
  Nchannel = fNchannel; 
  SetBounds(X, Y); //Explore bounds atomatically
  NbinsX = fNbinsX;
  NbinsY = fNbinsY;
  InitBin(X,BinSizeMode); 
  
}

Calibration::Calibration(vector<double> &fx, vector<double> &fy, int fNiteration, int fNchannel, int fProfileMode, int fBinSizeMode, int fNbinsX, double fXmin, double fXmax, int fNbinsY, double fYmin, double fYmax)
{
//  cout<<"---------construct calibration manually-------------------"<<endl;
  ProfileMode = fProfileMode;
  BinSizeMode = fBinSizeMode;
  tsfm = 5;
  size = fx.size();

  X = fx;
  Y = fy;
  Niteration = fNiteration;
  Nchannel = fNchannel;
  NbinsX = fNbinsX;
  Xmin = fXmin;
  Xmax = fXmax;
  NbinsY = fNbinsY;
  Ymin = fYmin;
  Ymax = fYmax;  
  InitBin(X,BinSizeMode);
}
Calibration::~Calibration() {
	delete DeltaT; DeltaT=0;
	delete DeltaT_cor; DeltaT_cor=0;
	delete Channel; Channel=0;
	delete Channel_cor; Channel_cor = 0;
	delete htsf; htsf = 0;
	delete tsf; tsf = 0;
	delete f1; f1 = 0;
	delete f2; f2 = 0;
}

TH2D *Calibration::Slewing(bool fOption)
{  
//   cout<<"-----------Come to Slewing Correction!---------"<<endl;

	Char_t function[100];
   sprintf(function, "f1_%d_%d", Niteration, Nchannel);
   f1 = new TF1(function, "gaus");
   for(int i=0;i<size;i++) { 
     DeltaT->Fill(Y.at(i));
//     DeltaT->SetBit(TH1::kCanRebin);
     Channel->Fill(X.at(i), Y.at(i));
//     Channel->SetBit(TH1::kCanRebin);   
     }
    
   int bin = DeltaT->GetMaximumBin();
   f1->SetRange(DeltaT->GetBinCenter(bin)-DeltaT->GetRMS(), DeltaT->GetBinCenter(bin)+DeltaT->GetRMS());
   DeltaT->Fit(function,"NQR");   
   double para[3], paraerror[3];
   f1->GetParameters(&para[0]);

   f1->SetRange(para[1]-3.0*para[2], para[1]+3.0*para[2]); 
   DeltaT->Fit(function,"QR");
   f1->GetParameters(&para[0]);
   Sigma = para[2];
   Error = f1->GetParError(2);

   
   Char_t buf[100];
   if(ProfileMode == 0){
   Channel->ProfileX();
   sprintf(buf, "Channel_%d_%d_pfx",Niteration, Nchannel);
   htsf=(TProfile *)gDirectory->Get(buf);
   }
     else {
     Channel->FitSlicesY();
     sprintf(buf, "Channel_%d_%d_1",Niteration, Nchannel);
     htsf=(TH1D *)gDirectory->Get(buf);
     }
   Char_t buff[100];
   sprintf(buf, "Spline Fit Channel_%d_%d", Niteration, Nchannel);
   sprintf(buff, "Spline Fit | Channel_%d_%d", Niteration, Nchannel);  
   tsf = new TSplineFit(buf, buff, 50, tsfm, htsf, Xmin, Xmax);
// start loop for calibration
   double cor;
   for(int i=0;i<size;i++)
   { 
     if(fOption == true) cor = tsf->V(X.at(i));
       else cor = 0;
     Y.at(i) -= cor;
     DeltaT_cor->Fill(Y.at(i));
     Channel_cor->Fill(X.at(i), Y.at(i));
     }
   return Channel;

}

//input vectors, find lower and upper bounds and bin number
void Calibration::SetBounds(vector<double> &fx, vector<double> &fy)
{
  vector<double> x = fx;
  vector<double> y = fy;
  double Xmintmp,Xmaxtmp,Ymintmp,Ymaxtmp,Width;
  double factor;
  int i = 0;
  int size = x.size();
  std::sort(x.begin(), x.end());
  while(i*1.0/size<0.02) {i++;}
  if(i>0 && i<size) Xmintmp = x.at(i);
    else {Xmintmp=x.at(0);cout<<"Xmin error!"<<endl;}
  i = size;
  while((size-i)*1.0/size<0.02) {i--;}
  if(i>0 && i<size) Xmaxtmp = x.at(i);
    else {Xmaxtmp = x.at(size-1); cout<<"Xmax error!"<<endl;}
  Width = Xmaxtmp-Xmintmp;
  Xmin = Xmintmp-(0.2*Width);
  Xmax = Xmaxtmp;
  Width = Xmax-Xmin;
  NbinsX = (int)floor(Width);
  if(NbinsX>100) NbinsX = min(100, NbinsX);

//  NbinsX = 50; //Open: use fixed bin number

  i = 0;
  std::sort(y.begin(), y.end());
  while(i*1.0/size<0.02) {i++;}
  if(i>0 && i<size) Ymintmp = y.at(i);
    else {Ymintmp=y.at(0);cout<<"Ymin error!"<<endl;}
  i = size;
  while((size-i)*1.0/size<0.02) {i--;}
  if(i>0 && i<size) Ymaxtmp = y.at(i);
    else {Ymaxtmp = y.at(size-1); cout<<"Ymax error!"<<endl;}
  Width = Ymaxtmp-Ymintmp;
  Ymin = Ymintmp-(0.4*Width);
  Ymax = Ymaxtmp+(0.4*Width);
  Width = Ymax-Ymin;
  if(Width>150) NbinsY = (int)floor(0.5*Width); 
    else NbinsY = (int)floor(Width);
  if(NbinsY<=80) NbinsY = 40*NbinsY;
  if(NbinsY>150) NbinsY = min(100, NbinsY);
//  cout<<NbinsY<<"\t"<<Ymin<<"\t"<<Ymax<<endl;
//  NbinsY = 100; //use fixed bin number
  
//  cout<<NbinsX<<"\t"<<Xmin<<"\t"<<Xmax<<"\t"<<NbinsY<<"\t"<<Ymin<<"\t"<<Ymax<<endl;
} 

void Calibration::InitBin(vector<double> &fx, int fBinSizeMode)
{
//Set binning preferences for <vector> X:
//fBinSizeMode = 0(fixed bin size)
//fBinSizeMode = 1(varible bin size)
//begion X-binning
  
  vector<double> x = fx;
  int MaxNbin = NbinsX; 
//  int MaxNbin = 50;
  double xBins[MaxNbin+1];
  int size = x.size();
  int step = size/MaxNbin; // (int)size/maxNBin is less than (float)size/maxNBin -> more entries in last bin
  std::sort(x.begin(), x.end());
  xBins[0] = x.at(0);
  xBins[MaxNbin] = x.at(size-1);
  double tmp;
    
  for(int j=1; j<MaxNbin; j++) {
    xBins[j] = (x.at(step*j)+x.at(step*j-1))/2.0;
//    tmp = 0.;
//    for(int k=step*(j-1); k<step*j; k++) {tmp += x.at(k);}
//    x[j-1] = tmp/step;
    }
//  tmp = 0;
//  for(int k=step*(MaxNbin-1); k<size; k++) {tmp += x.at(k);}
//  x[MaxNbin-1] = tmp/(size-step*(MaxNbin-1));
//end X-binning
  Char_t buf[100];
  sprintf(buf, "Channel_%d_%d",Niteration, Nchannel);
  if(BinSizeMode==1) Channel = new TH2D(buf, buf, MaxNbin,xBins, NbinsY, Ymin, Ymax);
    else Channel = new TH2D(buf, buf, NbinsX,Xmin, Xmax, NbinsY, Ymin, Ymax);
  Channel->SetOption("colz");
  sprintf(buf, "Channel_cor_%d_%d",Niteration, Nchannel);
  if(BinSizeMode==1) Channel_cor = new TH2D(buf, buf, MaxNbin,xBins, NbinsY, Ymin, Ymax);
    else Channel_cor = new TH2D(buf, buf, NbinsX,Xmin, Xmax, NbinsY, Ymin, Ymax);
  Channel_cor->SetOption("colz");
  
  sprintf(buf, "DeltaT_%d_%d",Niteration, Nchannel);
  DeltaT = new TH1D(buf, buf, NbinsY, Ymin, Ymax);
  sprintf(buf, "DeltaT_cor_%d_%d",Niteration, Nchannel);
  DeltaT_cor = new TH1D(buf, buf, NbinsY, Ymin, Ymax);


}






