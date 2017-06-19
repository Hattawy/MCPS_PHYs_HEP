//----------APS Analysis 
//----------Author's Name:Jingbo WANG
//----------Copyright:Those valid for ANL
//----------Modified:22/07/2014
#include "RVersion.h"
#include "TRandom.h"
#include "TDirectory.h"
#include "TProcessID.h"
#include "TMath.h"
#include "UVevent.h" 

using namespace std;

ClassImp(UVevent)
ClassImp(Waveform)

TClonesArray *UVevent::fgWaveforms = 0;

// ----------------------------------------------------------------------------------------------------------------------------------------------// 
// UVevent 
// ----------------------------------------------------------------------------------------------------------------------------------------------//
UVevent::UVevent() 
{ 
  // Create an UVevent object.
   // When the constructor is invoked for the first time, the class static
   // variable fgTracks is 0 and the TClonesArray fgTracks is created.
	if (!fgWaveforms) fgWaveforms = new TClonesArray("Waveform", 1000);
	fwav = fgWaveforms;
	fnwav = 0;
	WavDimSize = 2000;
}
UVevent::UVevent(float fsamplerate, int fdimsize) {
	if (!fgWaveforms) fgWaveforms = new TClonesArray("Waveform", 1000);
	fwav = fgWaveforms;
	fnwav = 0;
	WavSampleRate = fsamplerate;
	WavDimSize = fdimsize;
	for(int i=0;i<WavDimSize;i++) {
		t.push_back(i*100);
		fz.push_back(i*WavSampleRate/WavDimSize); //Hz
	}
}

 
UVevent::~UVevent() {
	Clear();
}  

void UVevent::Analyze()
{	
	
}

void UVevent::Clear(Option_t * /*option*/)
{
	fwav->Clear("C"); //will also call Waveform::Clear
   t.clear();
   fz.clear();
/*   for(int i=0;i<fnwav;i++) {
	Waveform *waveform = (Waveform*)(fwav->ConstructedAt(i));
	waveform->Clear();
   }*/
	fnwav = 0;
   
}



// ----------------------------------------------------------------------------------------------------------------------------------------------// 
// Waveform 
// ----------------------------------------------------------------------------------------------------------------------------------------------//
Waveform::Waveform()
{
	 fsplinewav = 0;
	 fsplinecfd = 0;
	 hwav = 0;
	 hcfd = 0;
	Samplerate = 1e10; //Hz
	Deltat = 100;
	DimSize = 256;
	baseline = 0;
	CutoffFrequency = 5e8;
	PointsPerSpline = 5;
	Fraction_CFD = 0.5;
	Delay_CFD = 100;
	DisWindow_min = 0;
	DisWindow_max = DimSize*Deltat;
	FitWindow_min = 0;
	FitWindow_max = DimSize*Deltat;
	npeaks = 0;
	MinimumTot = 100;
	DoFFT = 0;
	IfDynamicWindow = 0;
	TSplineCFDChi2 = 0;
	evtno = 0;
	chno = 0;
}

Waveform::~Waveform() {
	Clear();
}

void Waveform::Clear(Option_t * /*option*/)
{
	// Note that we intend on using TClonesArray::ConstructedAt, so we do not
   // need to delete any of the arrays.
   TObject::Clear();
	delete hwav; hwav = 0;
	delete hcfd; hcfd = 0;
	delete fsplinewav; fsplinewav = 0;
	delete fsplinecfd; fsplinecfd = 0;
	vol.clear();
	vol_fft.clear();
	re_fft.clear();
	im_fft.clear();
}

void Waveform::Initialize(float* fvol) //call it with Set(&fvol[0])
{
//Set values for the Waveform members
	
	char WavName[100], CFDName[100];
	sprintf(WavName, "wav_ch%d_%d", chno, evtno);
	sprintf(CFDName, "CFD_ch%d_%d", chno, evtno);
	hwav = new TH1D(WavName, WavName, DimSize, 0, DimSize*Deltat);
	hcfd = new TH1D(CFDName, CFDName, DimSize, 0, DimSize*Deltat);
//	Calculate_baseline(&fvol[0]);
	Calculate_baseline2(&fvol[0]);
//	TF1 *fsin = new TF1("fsin", "40*sin(2*3.14*1e9*x)", 0,1);
	double Fs = 1e10; //sampling rate = 10GHz
	double Ts = 1.0/Fs; //100ps/point

	for(int i=0;i<DimSize;i++) {
		vol.push_back(*(fvol+i)-baseline);
//		vol[i] = *(fvol+i)-baseline;
		hwav->SetBinContent(i+1, vol[i]);
	}
	AmpThreshold = 60;
	Fraction_CFD = 0.5;
	Delay_CFD = 10;
	AnalysisOption = "normal";
}


float Waveform::Calculate_baseline(float* fvol) {
	TH1D *hwavbaseline = new TH1D("hwavbaseline","hwavbaseline",DimSize,0,DimSize*Deltat);
	for(int i=0;i<200;i++) {
//		SetVol(i, *(fvol+i));
		hwavbaseline->SetBinContent(i+1,*(fvol+i));
	}
	TF1 *f1 = new TF1("f1", "[0]");
	hwavbaseline->Fit("f1","NQR");
	baseline = f1->GetParameter(0);
	delete hwavbaseline;
	hwavbaseline = NULL;
	delete f1;
	f1 = NULL;
	return baseline;
}

float Waveform::Calculate_baseline2(float* fvol) {
	double acc = 0;
	for(int i=30;i<90;i++) {
//		SetVol(i, *(fvol+i));
		acc += *(fvol+i);
	}
	baseline = acc/200;
	return baseline;
}



int Waveform::Calculate_Peaks() {
	double threshold = 50;
	double vol = 0, vollast = 0;
	int nbin = hwav->GetNbinsX();
	int length = 0;
	int MinimumTotBin = (int)(MinimumTot/Deltat);
	for(int i=0;i<nbin;i++) {
		vol = TMath::Abs(hwav->GetBinContent(i+1));
		if(vol>threshold) {length++;}
		else {
			if(length<MinimumTotBin) {length=0;}
			else {npeaks++; length = 0;}	
		}
		
	}
	return npeaks;
}

float Waveform::Calculate_amp() { 
//	amp = TMath::Abs(fsplinewav->V(hwav->GetMaximumBin()));
	amp = TMath::Abs(hwav->GetMinimum());
	return amp;
}

float Waveform::Calculate_Charge() {
	qtot = TMath::Abs(hwav->Integral()*100/50); //fC = 1e-15C
	qfast = TMath::Abs(hwav->Integral(FitWindow_min/100, FitWindow_max/100)*100/50);
	gain = qfast/1.6e-4; //number of electrons
}


float Waveform::Waveform_Filter1(float CutoffFrequency, float finput) {
	double f = 0;
	if(finput<CutoffFrequency) f=1;
		else f=0;
	return f;
}

float Waveform::Waveform_Filter2(float CutoffFrequency, int T, float finput) {
	double f = 1.0/(1+TMath::Power(finput/CutoffFrequency, 2*T));
//	TF1 *f1 = new TF1("f1","1/(1+(x/[0])^[1])",0,1e10);
	return f;
}


void Waveform::Waveform_FFT() {
	//Look at the real part of the output
	TH1 *hr = 0;
	hr = hwav->FFT(hr, "RE");
	hr->SetName("hr");
	hr->SetTitle("Real part of the 1st transform");
   hr->GetXaxis()->Set(DimSize,0,1e10); //Hz

/*	//Look at the imaginary part of the output
	 TH1 *him = 0;
	him = hwav->FFT(him, "IM");
	him->SetName("him");
	him->SetTitle("Imaginary part of the 1st transform");
	him->GetXaxis()->Set(DimSize,0,1e10);*/

	//Look at the DC component and the Nyquist harmonic:
   double re, im;
   //That's the way to get the current transform object:
   TVirtualFFT *fft = TVirtualFFT::GetCurrentTransform();
   //Use the following method to get the full output:
   double *re_full = new double[DimSize];
   double *im_full = new double[DimSize];
   fft->GetPointsComplex(re_full,im_full);
   //filter
	for(int i=0;i<DimSize;i++) {
//		double f = Waveform_Filter1(5e8, i*1.0e10/DimSize);
		double f = Waveform_Filter2(CutoffFrequency, 4, i*1.0e10/DimSize); 
		re_full[i] = re_full[i]*f;
		im_full[i] = im_full[i]*f;
	}
	//Now let's make a backward transform:
   TVirtualFFT *fft_back = TVirtualFFT::FFT(1, &DimSize, "C2R M K");
   fft_back->SetPointsComplex(re_full,im_full);
   fft_back->Transform();
   TH1 *hb = 0;
   //Let's look at the output
   hb = TH1::TransformHisto(fft_back,hb,"Re");
   hb->SetTitle("The backward transform result");
   hb->Scale(1.0/DimSize);
   hb->GetXaxis()->Set(DimSize,0,DimSize*Deltat); //ps
   for(int i=0;i<DimSize;i++) {
	hwav->SetBinContent(i+1, hb->GetBinContent(i+1));
	vol_fft.push_back(hb->GetBinContent(i+1));
	re_fft.push_back(hr->GetBinContent(i+1));
//	im_fft.push_back(him->GetBinContent(i+1));
//	vol_fft[i] = hb->GetBinContent(i+1);
//	re_fft[i] = hr->GetBinContent(i+1);
//	im_fft[i] = him->GetBinContent(i+1);
	
   }
   delete hr;
//   delete him;
   delete hb;
   delete re_full;
   delete im_full;
   delete fft;
   delete fft_back;
   hr=0;
//   him=0;
   hb=0;
   re_full=0;
   im_full=0;
   fft=0;
   fft_back=0;
	
}

void Waveform::Calculate_fitrange() {
	int bin = hwav->GetMinimumBin();
	int peakbin = bin;
	double peaktime = hwav->GetBinCenter(peakbin);
	if(npeaks==0) return;
	while(hwav->GetBinContent(bin)<-amp/2) {bin--;}
	double lowtime = hwav->GetBinCenter(bin);
	double fwhm = 2*(peaktime-lowtime);
	double xmin = peaktime-fwhm;
	double xmax = peaktime+fwhm;
	if(xmin<FitWindow_min || xmax>FitWindow_max) return;
//	if(3*fwhm<700) return;
	FitWindow_min = peaktime - fwhm;
	FitWindow_max = peaktime + 2*fwhm;
//	FitWindow_min = peaktime - 1500;
//	FitWindow_max = peaktime + 1500;
}

void Waveform::Waveform_Fit() {
	char SplineName[100], SplineTitle[100];
	sprintf(SplineName, "SplineFit_ch%d_%d", chno, evtno);
	sprintf(SplineTitle, "SplineFit | SplineFit_ch%d_%d", chno, evtno);
	if(amp <= AmpThreshold || npeaks==0) { return; } //TDC threshold
	else{
		if(IfDynamicWindow == 1) Calculate_fitrange();
		fsplinewav = new TSplineFit(SplineName, SplineTitle, 60, PointsPerSpline, hwav, FitWindow_min, FitWindow_max); 
//		fsplinewav->UpdateFile(true); //SplineFit database:  Skip this line for fast analysis
		fsplinewav->ReduceMemory();	//Store only X and Y. Apply this line for fast analysis
	}
}

float	Waveform::CFD_Discriminator1() { //Appoximate CFD
	if(amp <= AmpThreshold || npeaks==0) { time = 0; } //TDC threshold
	else {
		if(IfDynamicWindow == 1) Calculate_fitrange();
		Waveform_Fit();
		SetFraction_CFD(0.5);
		double th = -1.0 * Fraction_CFD * amp;
//		double th = -40;
		double eps = 1e-4;
		int bin = hwav->GetMinimumBin();
//		while(fsplinewav->V(hwav->GetBinCenter(bin))<=th) {bin--;}
		double xlow = FitWindow_min;
		double xhigh = hwav->GetBinCenter(bin);

		double xmid = (xlow+xhigh)/2;
		if(fsplinewav->V(xmid)-th==0) time = xmid;

		while ((xhigh-xlow) >= eps) {
			xmid = (xlow + xhigh) / 2;
			if (fsplinewav->V(xmid)-th == 0)
				time = xmid;
			if ((fsplinewav->V(xlow)-th)*(fsplinewav->V(xmid)-th) < 0)
				xhigh = xmid;
			else
				xlow = xmid;
		}
		time = xlow;
	}
	return time;
}	


float	Waveform::CFD_Discriminator2() {	//Exact CFD
	
	char CFDSplineName[100], CFDSplineTitle[100];
	sprintf(CFDSplineName, "CFDSpline_ch%d_%d", chno, evtno);
	sprintf(CFDSplineTitle, "CFDSpline | CFDSpline_ch%d_%d", chno, evtno);
	if(amp <= AmpThreshold || npeaks==0) { time = 0; } //TDC threshold
	else {
		if(IfDynamicWindow == 1) Calculate_fitrange();
		int Delay_CFDBin = (int)(Delay_CFD/Deltat);
		for(int i=0;i<DimSize;i++) {hcfd->SetBinContent(i+1, hwav->GetBinContent(i+1));} //copy
		TH1D *hinv = new TH1D("hinv","hinv",DimSize,0,DimSize*Deltat);
		for(int i=0;i<DimSize;i++) {
			if(i+Delay_CFDBin<DimSize) hinv->SetBinContent(i+1, hwav->GetBinContent(i+1+Delay_CFDBin)); //copy and delay
			else hinv->SetBinContent(i+1,0);
		}
		hinv->Scale(-1. * Fraction_CFD); //inverse and attenuate
		hcfd->Add(hinv);
		fsplinecfd = new TSplineFit(CFDSplineName,CFDSplineTitle,50,PointsPerSpline, hcfd,FitWindow_min, FitWindow_max);
		TSplineCFDChi2 = fsplinecfd->Chi2(1);
//		cout<<TSplineChi2<<endl;
//		fsplinecfd->UpdateFile(true); //SplineFit database:  Skip this line for fast analysis
		fsplinecfd->ReduceMemory();
	
//solve equation
		double eps = 1e-4;
		double xhigh = hcfd->GetMinimumBin()*100;
//		double xlow = hcfd->GetMaximumBin()*100;
		double xlow = FitWindow_min;
		double xmid = (xlow+xhigh)/2;
	
		if(fsplinecfd->V(xmid)==0) time = xmid;

		while ((xhigh-xlow) >= eps) {
			xmid = (xlow + xhigh) / 2;
			if (fsplinecfd->V(xmid) == 0)
				time =  xmid;
			if (fsplinecfd->V(xlow)*fsplinecfd->V(xmid) < 0)
				xhigh = xmid;
			else
				xlow = xmid;
		}
		time = xlow;
		delete hinv;
		hinv = NULL;
	}
	return time;
}

float	Waveform::GaussFit() {

	double amp = TMath::Abs(hwav->GetMinimum());
	int maxbin = hwav->GetMaximumBin();
	double lowrange = hwav->GetBinCenter(maxbin-6);
	double hirange = hwav->GetBinCenter(maxbin+6);

	gmean=0;
	gpeak=0;
	gsigma=0;
	gtime=0;
	gchi2=0;
	
	if( (hwav->GetBinCenter(maxbin)<45000)&&(hwav->GetBinCenter(maxbin)>25000) ){
	  TF1* mgf = new TF1("mgf","gaus",lowrange,hirange);
	  hwav->Fit("mgf","QR");
	  
	  double peaktime = mgf->GetParameter(1);
	  
	  double flowrange = peaktime-2450.;
	  double fhirange = peaktime+400.;
	  
	  if(peaktime<45000&&peaktime>25000){
	    TF1* mgf2 = new TF1("mgf2","gaus",flowrange,fhirange);
	    hwav->Fit("mgf2","QR");
	    
	    double mgpeak = mgf2->GetParameter(0);
	    double mgmean = mgf2->GetParameter(1);
	    double mgsigma = mgf2->GetParameter(2);
	    double mgchi2= mgf2->GetChisquare();
	    
	    gmean=mgmean;
	    gpeak=mgpeak;
	    gsigma=mgsigma;
	    gtime=mgmean-sqrt(-mgsigma*mgsigma*log(0.1));
	    gchi2=mgchi2;
	  } 
	  //	cout<<mgpeak<<" "<<mgmean<<" "<<mgsigma<<endl;
	}
	
	time=gtime;
	
	return time;
}


void Waveform::Analyze() {
	DisWindow_min = 0;
	DisWindow_max = DimSize*Deltat;
	hwav->GetXaxis()->SetRange(DisWindow_min/100,DisWindow_max/100);
	hcfd->GetXaxis()->SetRange(DisWindow_min/100,DisWindow_max/100);
	
	if(DoFFT==1)	Waveform_FFT();
	Calculate_Peaks();
	Calculate_amp();
	Calculate_Charge();
//	CFD_Discriminator1();	//approximate CFD
//	Waveform_Fit();
	CFD_Discriminator2();	 // exact CFD

}
