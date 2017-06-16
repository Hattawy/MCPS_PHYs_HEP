//----------APS Analysis 
//----------Author's Name:Jingbo WANG
//----------Modified:22/07/2014
//----------Copyright:Those valid for ANL. Please don't distribute.
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

// ------------------------------------------------------ 
// UVevent 
// ------------------------------------------------------
UVevent::UVevent() 
{ 
  // Create an UVevent object.
   // When the constructor is invoked for the first time, the class static
   // variable fgTracks is 0 and the TClonesArray fgTracks is created.
	if (!fgWaveforms) fgWaveforms = new TClonesArray("Waveform", 1000);
	fwav = fgWaveforms;
	fnwav = 0;
	WavDimSize = 1032;
	WavSampleRate = 1.e10;
	WavDeltat = 100;
}

UVevent::~UVevent() {
	Clear();
}  

void UVevent::Initialize() {
	for(int i=0;i<WavDimSize;i++) {
		WavDeltat = 1.e12/WavSampleRate;
		t.push_back(i*1.e12/WavSampleRate);
		fz.push_back(i*WavSampleRate/WavDimSize); //Hz
//		cout<<WavSampleRate<<"\t"<<WavDimSize<<endl;
	}
}

void UVevent::UVeventAnalysis()
{	}

void UVevent::Clear(Option_t * /*option*/)
{
   fwav->Clear("C"); //will also call Waveform::Clear
   fnwav = 0;
   t.clear();
   fz.clear();
//	for(int i=0;i<60;i++) {wav[i].Clear();}  

//   delete fwav;
   
}

// ------------------------------------------------------ 
// Waveform 
// ------------------------------------------------------
Waveform::Waveform()
{
//	cout<<"Class Waveform"<<endl;
//	hwav = new TH1F("wav","wav",DimSize,0,103.2);
	 fsplinewav = 0;
	 fsplinecfd = 0;
	 hwav = 0;
	 hcfd = 0;
	Samplerate = 1e10; //Hz
	Deltat = 100;
	DimSize = 256;
	baseline = 0;
	noiserms = 0;
	peaktime = 0;
	risingtime = 0;
	fallingtime = 0;
	amp = 0;
	time = 0;
	CutoffFrequency = 5e8;
	PointsPerSpline = 5;
	Fraction_CFD = 0.5;
	Delay_CFD = 0;
	DisWindow_min = 0;
	DisWindow_max = DimSize*Deltat;
	FitWindow_min = 0;
	FitWindow_max = DimSize*Deltat;
	npeaks = 0;
	MinimumTot = 100;
	DoFFT = 0;
    ReflectionCancelling = 0;
    ReflectionWindow_min = 700000000;
    ReflectionWindow_max = 1500000000;
	IfDynamicWindow = 0;
    TriggerMarker = 0;
}

Waveform::~Waveform() {
	Clear();
//	delete hwav;
//	delete froot;
//	delete fsplinewav;
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
	vol_cfd.clear();
	vol_fft.clear();
//	re_fft_background.clear();
//	im_fft_background.clear();
	re_fft.clear();
	im_fft.clear();
	mag_fft.clear();
	mag_processed.clear();
}

void Waveform::Initialize(float* fvol) //call it with Set(&fvol[0])
{
//Set values for the Waveform members
	
	sprintf(WavName, "wav_ch%d_%d", chno, evtno);
	sprintf(CFDName, "CFD_ch%d_%d", chno, evtno);
	hwav = new TH1D(WavName, WavName, DimSize, 0, DimSize*Deltat);
	hcfd = new TH1D(CFDName, CFDName, DimSize, 0, DimSize*Deltat);
	
//	Calculate_baseline(&fvol[0]);
	Calculate_baseline2(&fvol[0]);
	Calculate_noiserms(&fvol[0]);
//	TF1 *fsin = new TF1("fsin", "40*sin(2*3.14*1e9*x)", 0,1);
	double Fs = Samplerate; //sampling rate = 10GHz
	double Ts = 1.e12/Fs; //100ps/point
	for(int i=0;i<DimSize;i++) {
		vol.push_back(*(fvol+i)-baseline);
//		vol[i] = *(fvol+i)-baseline;
		hwav->SetBinContent(i+1, vol[i]);
	}
	AmpThreshold = 4*noiserms;
	TotThreshold = 4*noiserms;
	npeaks = 0;
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
	for(int i=10;i<100;i++) {
//		SetVol(i, *(fvol+i));
		acc += *(fvol+i);
	}
	baseline = acc*1.0/90;
	return baseline;
}

float Waveform::Calculate_noiserms(float* fvol) {
	for(int i=0;i<100;i++) {
		noiserms += (*(fvol+i)-baseline)*(*(fvol+i)-baseline);
	}
	noiserms = sqrt(noiserms/100);
	return noiserms;
}



int Waveform::Calculate_Peaks() {
	npeaks = 0;
	double threshold = TotThreshold;
	double vol = 0, vollast = 0;
	int nbin = hwav->GetNbinsX();
	int length = 0;
	int MinimumTotBin = (int)(MinimumTot/Deltat);
/*	for(int i=0;i<nbin;i++) {
		vol = TMath::Abs(hwav->GetBinContent(i+1));
		if(vol>threshold) {length++;}
		else {
			if(length<MinimumTotBin) {length=0;}
			else {npeaks++; length = 0;}	
		}	
	}*/
	for(int i=0;i<1100;i++) {
		vol = TMath::Abs(hwav->GetBinContent(i+1));
		if(vol>threshold) {
			length++;
			if(length == MinimumTotBin) npeaks++;
		}
		else {
			length = 0;	
		}	
	}
	return npeaks;
}

float Waveform::Calculate_amp() { 
//	amp = TMath::Abs(fsplinewav->V(hwav->GetMaximumBin()));
	amp = TMath::Abs(hwav->GetMinimum());
	return amp;
}

float Waveform::Calculate_peaktime() {
	int minbin = hwav->GetMinimumBin();
	peaktime = hwav->GetBinCenter(minbin);
}

double Waveform::Calculate_RisingTime() {
	if(amp <= AmpThreshold || npeaks==0) {return 0;}
	int bin = hwav->GetMinimumBin();
	int peakbin = bin;
	double x0,x1,y0,y1,k;
	double peaktime = hwav->GetBinCenter(peakbin);
	while(hwav->GetBinContent(bin)<-amp*0.9) {bin--;}
	x1 = hwav->GetBinCenter(bin+1);
	x0 = hwav->GetBinCenter(bin);
	y1 = hwav->GetBinContent(bin+1);
	y0 = hwav->GetBinContent(bin);
	k = (y1-y0)/(x1-x0);
	double hightime = (-amp*0.9-y0+k*x0)/k;
	while(hwav->GetBinContent(bin)<-amp*0.1) {bin--;}
	x1 = hwav->GetBinCenter(bin+1);
	x0 = hwav->GetBinCenter(bin);
	y1 = hwav->GetBinContent(bin+1);
	y0 = hwav->GetBinContent(bin);
	k = (y1-y0)/(x1-x0);
	double lowtime = (-amp*0.1-y0+k*x0)/k;
	risingtime = hightime - lowtime;
	return risingtime;
	
}

double Waveform::Calculate_FallingTime() {
	if(amp <= AmpThreshold || npeaks==0) return 0;
	int bin = hwav->GetMinimumBin();
	int peakbin = bin;
	double x0,x1,y0,y1,k;
	double peaktime = hwav->GetBinCenter(peakbin);
	while(hwav->GetBinContent(bin)<-amp*0.9) {bin++;}
	x1 = hwav->GetBinCenter(bin);
	x0 = hwav->GetBinCenter(bin-1);
	y1 = hwav->GetBinContent(bin);
	y0 = hwav->GetBinContent(bin-1);
	k = (y1-y0)/(x1-x0);
	double lowtime = (-amp*0.9-y0+k*x0)/k;
	while(hwav->GetBinContent(bin)<-amp*0.1) {bin++;}
	x1 = hwav->GetBinCenter(bin);
	x0 = hwav->GetBinCenter(bin-1);
	y1 = hwav->GetBinContent(bin);
	y0 = hwav->GetBinContent(bin-1);
	k = (y1-y0)/(x1-x0);
	double hightime = (-amp*0.1-y0+k*x0)/k;
	fallingtime = hightime - lowtime;
	return fallingtime;
}

float Waveform::Calculate_Charge() {
	qtot = -1.0*hwav->Integral()*Deltat/50; //fC = 1e-15C
	if(IfDynamicWindow == 1) qfast = -1.0*(hwav->Integral((peaktime-4*risingtime)/Deltat, (peaktime+4*fallingtime)/Deltat)*Deltat/50);
    else qfast = -1.0*hwav->Integral(FitWindow_min/Deltat, FitWindow_max/Deltat)*Deltat/50;
//    cout<<qfast<<endl;
	gain = qfast/1.6e-4; //number of electrons
//	if(amp <= AmpThreshold || npeaks==0) { qfast = 0; qtot=0; gain=0;} //TDC threshold
}


float Waveform::Waveform_Filter1(float CutoffFrequency, float finput) {
	double f = 0;
	if(finput<CutoffFrequency) f=1;
		else f=0;
	return f;
}

float Waveform::Waveform_Filter2(float CutoffFrequency, int T, float finput) { //low pass
	double f = 1.0/(1+TMath::Power(finput/CutoffFrequency, 2*T));
//	TF1 *f1 = new TF1("f1","1/(1+(x/[0])^[1])",0,Samplerate);
	return f;
}

float Waveform::Waveform_Filter3(float CutoffFrequency, int T, float finput) { //high pass
	double f = 1.0/(1+TMath::Power((2*CutoffFrequency - finput)/CutoffFrequency, 2*T));
//	TF1 *f1 = new TF1("f1","1/(1+(x/[0])^[1])",0,Samplerate);
	return f;
}

float Waveform::Waveform_Filter4(float CutoffFrequency_low, float CutoffFrequency_high, int T, float finput) { // band pass
	double f;
	if(finput<(CutoffFrequency_low+CutoffFrequency_high)/2) f = 1.0/(1+TMath::Power(finput/CutoffFrequency_low, 2*T));
		else f = 1.0/(1+TMath::Power((2*CutoffFrequency_high - finput)/CutoffFrequency_high, 2*T));
//	TF1 *f1 = new TF1("f1","1/(1+(x/[0])^[1])",0,Samplerate);
	return f;
}


void Waveform::Waveform_FFT() {
/*//	Internal_Background_Estimate();
		//look at the magnitude of the noise
	TH1D *hwav_background = new TH1D("hwav_background", "hwav_background", DimSize, 0, DimSize*Deltat);
	for(int i=0;i<400;i++) {
		hwav_background->SetBinContent(i+1,hwav->GetBinContent(i+1));
	}
	for(int i=400;i<DimSize;i++) {
		hwav_background->SetBinContent(i+1,0);
	}

	TH1 *hmag_background = 0;
	hmag_background = hwav_background->FFT(hmag_background, "MAG");
	hmag_background->SetName("hmag_background");
	hmag_background->SetTitle("Magnitude of the 1st transform");
	hmag_background->GetXaxis()->Set(DimSize,0,Samplerate);

   //That's the way to get the current transform object:
   TVirtualFFT *fft = TVirtualFFT::GetCurrentTransform();
   //Use the following method to get the full output:
   double *re_background = new double[DimSize];
   double *im_background = new double[DimSize];
   fft->GetPointsComplex(re_background,im_background);
   for(int i=0;i<DimSize;i++) {
	if(i<DimSize/2) {
		re_fft_background.push_back(re_background[i]);
		im_fft_background.push_back(im_background[i]);
		mag_fft_background.push_back(hmag_background->GetBinContent(i+1));
	}
	   
   }
   delete hwav_background;
   delete hmag_background;
//   delete fft;
   hwav_background=0;
   hmag_background=0;
//   fft=0;*/
	
	//Look at the real part of the output
/*	TH1 *hr = 0;
	hr = hwav->FFT(hr, "RE");
	hr->SetName("hr");
	hr->SetTitle("Real part of the 1st transform");
   hr->GetXaxis()->Set(DimSize,0,Samplerate); //Hz

	//Look at the imaginary part of the output
	 TH1 *him = 0;
	him = hwav->FFT(him, "IM");
	him->SetName("him");
	him->SetTitle("Imaginary part of the 1st transform");
	him->GetXaxis()->Set(DimSize,0,Samplerate);*/

	//Look at the magnitude of the output
	TH1D *hmag = 0;
	hmag = (TH1D*)hwav->FFT(hmag, "MAG");
	hmag->SetName("hmag");
	hmag->SetTitle("Magnitude of the 1st transform");
	//NOTE: for "real" frequencies you have to divide the x-axes range (in this case 1032) with the range of your function 
   //(in this case 103200.e-12 s); y-axes has to be rescaled by a factor of 1/SQRT(n) to be right: this is not done automatically!
	hmag->GetXaxis()->Set(DimSize,0,Samplerate);
	hmag->Scale(1./sqrt(DimSize)); //scale to 1/SQRT(n)

	//Look at the DC component and the Nyquist harmonic:
   double re, im;
   //That's the way to get the current transform object:
   TVirtualFFT *fft = TVirtualFFT::GetCurrentTransform();
   //Use the following method to get the full output:
   double *re_full = new double[DimSize];
   double *im_full = new double[DimSize];
   fft->GetPointsComplex(re_full,im_full);

//________________________frequency spectrum processing____________________________

    double f;
    double cor = 0;
    double *r_raw = new double[DimSize]; //amplitude of the frequency component
    double *r_cor = new double[DimSize]; //corrected amplitude of the frequency component
    //Spectrum bump removal
    TH1D *hmag_cor = new TH1D("hmag_cor","hmag_cor",DimSize, 0, Samplerate); 
    TF1 *fl = new TF1("fl","[0]*x+[1]", 0, Samplerate); //linear function
    TF1 *fp = new TF1("fp","pol5",0, Samplerate); //5 order polynomial function
    
    if(ReflectionCancelling == 1) {
        for(int i=0;i<DimSize;i++) {
            hmag_cor->SetBinContent(i+1, 20*log10(hmag->GetBinContent(i+1))); //copy the raw requency spectrum and translate it to dB unit
        }
        hmag_cor->Fit("fl","NQ","", 0, ReflectionWindow_min); //linear fit for the signal components
        hmag_cor->Fit("fp","NQ","",ReflectionWindow_min, ReflectionWindow_max); //polynomial fit for the unwanted bump components. 
        for(int i=0;i<DimSize;i++) {
            r_raw[i] = hmag->GetBinContent(i+1);
            r_cor[i] = hmag_cor->GetBinContent(i+1); //log scale
            if(i>ReflectionWindow_min/(Samplerate/DimSize) && i<ReflectionWindow_max/(Samplerate/DimSize)) {
                cor = fl->Eval(hmag_cor->GetBinCenter(i+1)) - fp->Eval(hmag_cor->GetBinCenter(i+1)); //log scale
                r_cor[i] = r_cor[i]+cor; //log scale
            }
            r_cor[i] = TMath::Power(10,r_cor[i]/20); //tranfer back to linear scale
            hmag_cor->SetBinContent(i+1, r_cor[i]); //linear scale, non-bump spectrum
        }
    }
    
    
    //Frequency filtering
    for(int i=0;i<DimSize;i++) {
        f = Waveform_Filter2(CutoffFrequency, 8, i*Samplerate/DimSize);
		if(ReflectionCancelling == 1) f = f * r_cor[i]/r_raw[i]; //modified Butterworth filter
        if(i<DimSize/2) {
           re_fft.push_back(re_full[i]);
           im_fft.push_back(im_full[i]);
           mag_fft.push_back(20*log10(hmag->GetBinContent(i+1))); //Note: the power has already been scaled by sqrt(n). Y axis is translated to 20*log(mag_fft) dB
        }          
//Spectrum filtering
        re_full[i] = (re_full[i])*f;
		im_full[i] = (im_full[i])*f;
        if(i<DimSize/2) mag_processed.push_back(20*log10(sqrt(re_full[i]*re_full[i]+im_full[i]*im_full[i])/sqrt(DimSize)));
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
//	re_fft.push_back(hr->GetBinContent(i+1));
//	im_fft.push_back(him->GetBinContent(i+1));
//	mag_fft.push_back(hmag->GetBinContent(i+1));
   }
//   delete hr;
//   delete him;
   delete hmag;
   delete hb;
   delete re_full;
   delete im_full;
   delete fft;
   delete fft_back;
//   hr=0;
//   him=0;
   hmag=0;
   hb=0;
   re_full=0;
   im_full=0;
   fft=0;
   fft_back=0;
   delete hmag_cor; hmag_cor=0;
	
}

void Waveform::Calculate_fitrange() {
	double xmin = peaktime - 3*risingtime;
	double xmax = peaktime + Delay_CFD;
	if(xmin<0 || xmax>DimSize*Deltat) return;
	FitWindow_min = xmin;
	FitWindow_max = xmax;
}

void Waveform::Waveform_Fit() {
	sprintf(SplineName, "SplineFit_ch%d_%d", chno, evtno);
	sprintf(SplineTitle, "SplineFit | SplineFit_ch%d_%d", chno, evtno);
	if(amp <= AmpThreshold || npeaks==0) return;
	else {
		if(IfDynamicWindow == 1) Calculate_fitrange();
		fsplinewav = new TSplineFit(SplineName, SplineTitle, 20, PointsPerSpline, hwav, FitWindow_min, FitWindow_max); 
//		fsplinewav->UpdateFile(true); //SplineFit database:  Skip this line for fast analysis
		fsplinewav->ReduceMemory();	//Store only X and Y. Apply this line for fast analysis
	}
	
}

float	Waveform::CFD_Discriminator1() { //CFD1
	if(amp <= AmpThreshold) { time = 0; } //TDC threshold
	else {
		if(IfDynamicWindow == 1) Calculate_fitrange();
        Waveform_Fit();
		sprintf(SplineName, "SplineFit_ch%d_%d", chno, evtno);
		sprintf(SplineTitle, "SplineFit | SplineFit_ch%d_%d", chno, evtno);
		fsplinewav = new TSplineFit(SplineName, SplineTitle, 20, PointsPerSpline, hwav, FitWindow_min, FitWindow_max); 
		fsplinewav->ReduceMemory();	//Store only X and Y. Apply this line for fast analysis
		SetFraction_CFD(Fraction_CFD);
		double th = -1.0 * Fraction_CFD * amp;
//		double th = -40;
		double eps = 1e-3;

		int bin = hwav->GetMinimumBin();
		while(hwav->GetBinContent(bin)<=th) {bin--;}
		double xlow = hwav->GetBinCenter(bin);
		double xhigh = hwav->GetBinCenter(bin+1)+eps;

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


float	Waveform::CFD_Discriminator2() {	// CFD2: ARC discriminator
	sprintf(CFDSplineName, "CFDSpline_ch%d_%d", chno, evtno);
	sprintf(CFDSplineTitle, "CFDSpline | CFDSpline_ch%d_%d", chno, evtno);
	if(amp <= AmpThreshold || npeaks==0) { time = 0; } //TDC threshold
	else {
		int Delay_CFDBin = (int)(Delay_CFD/Deltat);
		for(int i=0;i<DimSize;i++) {hcfd->SetBinContent(i+1, hwav->GetBinContent(i+1));} //copy
		TH1D *hinv = new TH1D("hinv","hinv",DimSize,0,DimSize*Deltat);
/*		for(int i=0;i<DimSize;i++) {
			if(i+Delay_CFDBin<DimSize) hinv->SetBinContent(i+1, hwav->GetBinContent(i+1+Delay_CFDBin)); //copy and delay
			else hinv->SetBinContent(i+1,0);
		}*/
		for(int i=0;i<DimSize;i++) {
			hinv->SetBinContent(i+1,-1. * Fraction_CFD * hwav->GetBinContent(i+1)); //copy and attenuate
			if(i<Delay_CFDBin) hcfd->SetBinContent(i+1, 0); //copy and delay
			else hcfd->SetBinContent(i+1,hwav->GetBinContent(i+1-Delay_CFDBin));
		}
//		hinv->Scale(-1. * Fraction_CFD); //inverse and attenuate
		hcfd->Add(hinv);
		for(int i=0;i<DimSize;i++) {vol_cfd.push_back(hcfd->GetBinContent(i+1));}
//		if(IfDynamicWindow == 1) Calculate_fitrange();
//		fsplinecfd = new TSplineFit(CFDSplineName,CFDSplineTitle,50,PointsPerSpline, hcfd,FitWindow_min, FitWindow_max); 
		int binlow = hcfd->GetMaximumBin();
		int binhigh = hcfd->GetMinimumBin();
        if(binlow < binhigh) fsplinecfd = new TSplineFit(CFDSplineName,CFDSplineTitle,50,PointsPerSpline, hcfd,hcfd->GetBinCenter(binlow), hcfd->GetBinCenter(binhigh));
        else fsplinecfd = new TSplineFit(CFDSplineName,CFDSplineTitle,50,PointsPerSpline, hcfd,hcfd->GetBinCenter(binhigh)-3*risingtime, hcfd->GetBinCenter(binhigh));
//		fsplinecfd->UpdateFile(true); //SplineFit database:  Skip this line for fast analysis
		fsplinecfd->ReduceMemory();
	
//solve equation
		double eps = 1e-3;
//		double xhigh = hcfd->GetMinimumBin()*Deltat;
//		double xlow = hcfd->GetMaximumBin()*Deltat;
        int bin = hcfd->GetMinimumBin();
        while(hcfd->GetBinContent(bin)<=0) {bin--;}
		double xlow = hcfd->GetBinCenter(bin);
		double xhigh = hcfd->GetBinCenter(bin+1)+eps;
		
//		double xlow = hcfd->GetMinimumBin()*Deltat-1.5*risingtime; //fermilab beam test
//		int bin = hwav->GetMinimumBin();
//		while(hcfd->GetBinContent(bin)<=0) {bin--;}
//		double xlow = hwav->GetBinCenter(bin);
//		double xhigh = hwav->GetBinCenter(bin+1)+eps;
//		cout<<xlow<<"\t"<<xhigh<<endl;
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

float	Waveform::CFD_Discriminator3() { //CFD1
	if(amp <= AmpThreshold) { time = 0; } //TDC threshold
	else {
		if(IfDynamicWindow == 1) Calculate_fitrange();
//		Waveform_Fit();
		SetFraction_CFD(Fraction_CFD);
		double th = -1.0 * Fraction_CFD * amp;
//		double th = -40;
		double eps = 1e-3;
		int bin = hwav->GetMinimumBin();
		while(hwav->GetBinContent(bin)<=th) {bin--;}
		double x1 = hwav->GetBinCenter(bin);
		double y1 = hwav->GetBinContent(bin);
		double x2 = hwav->GetBinCenter(bin+1);
		double y2 = hwav->GetBinContent(bin+1);
		time = (th-y1)*(x2-x1)/(y2-y1)+x1;
	}
	return time;
}

float	Waveform::CFD_Discriminator4() { //
	if(amp <= AmpThreshold) { time = 0; } //TDC threshold
	else {
		if(IfDynamicWindow == 1) Calculate_fitrange();
		SetFraction_CFD(Fraction_CFD);
		double th = -1.0 * Fraction_CFD * amp;
		double eps = 1e-3;
		int bin = hwav->GetMinimumBin();
		while(hwav->GetBinContent(bin)<=th) {bin--;}
		double x1 = hwav->GetBinCenter(bin);
		double y1 = hwav->GetBinContent(bin);
		double x2 = hwav->GetBinCenter(bin+1);
		double y2 = hwav->GetBinContent(bin+1);
		time = (th-y1)*(x2-x1)/(y2-y1)+x1;
	}
	return time;
}

float Waveform::GaussFit() {
	char gausname[100];
	sprintf(gausname, "gausfit_ch%d_%d", chno, evtno);
	if(amp <= AmpThreshold || npeaks==0) { time = 0; } //TDC threshold
	else {
		TF1* mgf = new TF1(gausname,"[0]*exp(-0.5*((x-[1])/[2])^2)+[3]", 0, DimSize*Deltat);
		int bin = hwav->GetMinimumBin();
		double peaktime = hwav->GetBinCenter(bin);
		mgf->SetParameter(0, -amp);
		mgf->SetParameter(1, Deltat*hwav->GetMinimumBin()-Deltat/2);
		mgf->SetParameter(2, risingtime/2);
		mgf->SetParameter(3, 0);
		if(IfDynamicWindow == 1) Calculate_fitrange();
		hwav->Fit(gausname,"QR", "", FitWindow_min, peaktime);
		double par[4];
		mgf->GetParameters(&par[0]);
		double y = -0.4*amp;
		time = par[2]*sqrt(-2*log((y-par[3])/par[0]))+par[1];
		delete mgf; mgf = 0;
	}
	return time;
}


void Waveform::Analyze() {
	DisWindow_min = 0;
	DisWindow_max = DimSize*Deltat;
	hwav->GetXaxis()->SetRange(DisWindow_min/Deltat,DisWindow_max/Deltat);
	hcfd->GetXaxis()->SetRange(DisWindow_min/Deltat,DisWindow_max/Deltat);
	
	if(DoFFT==1)	Waveform_FFT();
	Calculate_Peaks();
	Calculate_amp();
	Calculate_peaktime();
	Calculate_RisingTime();
	Calculate_FallingTime();
	Calculate_Charge();
//	Waveform_Fit();
//	CFD_Discriminator1();	// CFD
	CFD_Discriminator2();	 // ARC
//	CFD_Discriminator3();	//linear interpolation
//	GaussFit();

}

