//----------APS Analysis 
//----------Author's Name:Jingbo WANG
//----------Modified:22/07/2014
//----------Copyright:Those valid for ANL. Please don't distribute.
#ifndef UVEVENT 
#define UVEVENT

#include <TObject.h>
#include <TFile.h>
#include <TF1.h>
#include <TROOT.h>
#include <TH1F.h>
#include "TVirtualFFT.h"
#include "TClonesArray.h"
#include "TSplineFit.h"
#include "Calibration.h"
#include <vector>

class UVevent: public TObject { 

private: 
	float			WavSampleRate;
	int				WavDimSize;
	float			WavDeltat;
	
public: 

  UVevent(); 
  virtual ~UVevent(); 
  void          Clear(Option_t *option ="");

  int			evtno;
	TClonesArray	*fwav;            //->array with all waveforms (not used yet)
	int			fnwav;            //Number of waveforms
	int			ClusterSize;			//Number of fired strips

	static TClonesArray *fgWaveforms;
 
	int			cutflag;		//
	vector<float>	t;
	vector<float>	fz;
	float			tabs;			//
	float			tdiff;
	float			x;		//Parallel postion
	float			y;		//Transverse position

	void			Initialize();
	int				Setevtno(int fevtno)			{ evtno = fevtno; return evtno; }
	float			SetWavSampleRate(float frate)	{WavSampleRate = frate; return WavSampleRate;}
	int				SetWavDimSize(int fsize)		{WavDimSize = fsize; return WavDimSize;}
	int				SetCutflag(int flag)			{ cutflag = flag; return cutflag;}
	float			SetTransitTime(float ftabs)		{ tabs = ftabs; return tabs;}
	float			SetDifferentialTime(float ftdiff)		{ tdiff = ftdiff; return tdiff;}
	int				SetWavNumber(int fn)			{ fnwav = fn; return fnwav;}
	int				Getevtno()						const { return evtno; }
	TClonesArray	*GetWaveforms()					const { return fwav; }
	int				GetWavNumber()					const { return fnwav;}
	void			UVeventAnalysis();
  
  ClassDef(UVevent,1) 

}; 

class Waveform: public TObject {
private:
		
		float		Calculate_baseline(float* fvol); //
		float		Calculate_baseline2(float* fvol);
		float		Waveform_Filter1(float CutoffFrequency, float finput);		//ideal low-pass filter
		float		Waveform_Filter2(float CutoffFrequency, int T, float finput); //Butterworth low-pass filter
		float		Waveform_Filter3(float CutoffFrequency, int T, float finput);		//Butterworth high-pass filter
		float		Waveform_Filter4(float CutoffFrequency_low, float CutoffFrequency_high, int T, float finput); 
		void		Calculate_fitrange();
		float		Calculate_noiserms(float* fvol);

		void		Waveform_FFT();
		void		Waveform_Fit();
		float		CFD_Discriminator1(); //CFD + Spline interpolation
		float		CFD_Discriminator2(); //ARC + Spline fit
		float		CFD_Discriminator3(); //CFD + Linear interpolation
		float		CFD_Discriminator4(); //Spline interpolation + ARC + Spline fit
		float		GaussFit();
		float		Calculate_amp();
		float		Calculate_Charge();
		int			Calculate_Peaks();
		float		Calculate_peaktime();
		double		Calculate_RisingTime();
		double		Calculate_FallingTime();
public: 
		int			DoFFT;
		int			ReflectionCancelling;
		float		Samplerate;		//sampling rate
		float		Deltat;			//time per sample
		int			DimSize;		//Number of samples
		float		baseline;		//Base line of this waveform
		float		noiserms;
		float		qfast;			//fast charge
		float		qtot;			//total charge
		float		peaktime;
		float		gain;
		float		amp;		//amp of the pulse
		double		time;	//leading edge
		double		risingtime;		//
		double		fallingtime;
		double		TotThreshold;
		int			MinimumTot;
		int			npeaks;
		int			evtno;		//UVevent number
		int			chno;
		int			WavID;		//each waveform must have an ID, ID = 100*evtno + Channel_Number
        int         TriggerMarker;
		double      gmean;
		double      gsigma;
		double      gpeak;
		double		gtime;
		double      grisetime;
		double      gchi2;          //Gaussian parameters
		char		WavName[100];
		char		SplineName[100];
		char		SplineTitle[100];
		int			PointsPerSpline; //Number of measured points for one spline
		char		CFDName[100];
		char		CFDTitle[100];
		char		CFDSplineName[100];
		char		CFDSplineTitle[100];
		float		TimeStamp;	//Time stamp of this waveform
		
		vector<float>	vol;
		vector<float>	vol_cfd;
		vector<float>	vol_fft;
		vector<float>	re_fft;
		vector<float>	im_fft;
		vector<float>	mag_fft;
//		vector<float>	re_fft_background;
//		vector<float>	im_fft_background;
//		vector<float>	mag_fft_background;
		vector<float>	mag_processed;

//		float		vol[256];		//Y value of the samples
//		float		vol_fft[256];	//reconstruced Y value
//		float		re_fft[256];
//		float		im_fft[256];
		TH1D*		hwav;			//Waveform plot
		TH1D*		hcfd;			//histogram for CFD
		TSplineFit	*fsplinewav;		//SplineFit function
		TSplineFit	*fsplinecfd;
		int			IfDynamicWindow;
		double		FitWindow_min;	//Xmin for SplineFit
		double		FitWindow_max;	//Xmax for SplineFit
		double		DisWindow_min;
		double		DisWindow_max;
		float		CutoffFrequency;
        float       ReflectionWindow_min;
        float       ReflectionWindow_max;
		double		AmpThreshold;
		double		Fraction_CFD;	//fraction of Attenuation 
		int			Delay_CFD;		//
		char*		AnalysisOption;
		
		Waveform();
		virtual ~Waveform();
		void        Clear(Option_t *option="");
		float		SetSamplingrate(float frate)	{Samplerate = frate; return Samplerate;}
		float		SetDeltat(float fdeltat)		{Deltat = fdeltat; return Deltat;}
		int			SetPointsPerSpline(int fm)		{PointsPerSpline = fm; return PointsPerSpline;};
		int			Setevtno(int fevtno)			{evtno = fevtno; return evtno;}
		int			Setchno(int fchno)				{chno = fchno; return chno;}
        int         SetTriggerMarker(int fmarker)   {TriggerMarker = fmarker; return TriggerMarker;}
		int			SetDimSize(int fDimSize)		{DimSize = fDimSize; return DimSize;}
		float		SetTimeStamp(float ft)			{TimeStamp = ft; return TimeStamp;}
		double		SetAmpThreshold(double fth)		{AmpThreshold = fth; return AmpThreshold;}
		double		SetFraction_CFD(double fraction) {Fraction_CFD = fraction; return Fraction_CFD;}
		int			SetDelay_CFD(double delay)		{Delay_CFD = delay; return Delay_CFD;}
		int			EnableFFT()						{DoFFT = 1; return DoFFT;}
		int			EnableReflectionCancelling()	{ReflectionCancelling = 1; return ReflectionCancelling;}
		int			EnableDynamicWindow()			{IfDynamicWindow = 1; return IfDynamicWindow;}
		float		SetCutoffFrequency(float f)		{CutoffFrequency = f; return CutoffFrequency;};
		double		SetTotThreshold(double fth)		{TotThreshold = fth; return TotThreshold;}
		int			SetMinimumTot(int fdt)			{MinimumTot = fdt; return MinimumTot;}
        void        SetReflectionCancellingWindow(float fmin, float fmax)  {ReflectionWindow_min = fmin; ReflectionWindow_max = fmax;}
		
		void		Initialize(float* par); //call it with Set(&par[0])
		void		Analyze();
		void		SetFitWindow(double fxmin, double fxmax) {FitWindow_min = fxmin; FitWindow_max = fxmax;}
		void		SetDisWindow(double fxmin, double fxmax) {DisWindow_min = fxmin; DisWindow_max = fxmax;}
		char*		SetAnalysisOption(char* foption) {AnalysisOption = foption; return AnalysisOption;}
		int			Getevtno()				const { return evtno; }
		float		GetTimeStamp()			const { return TimeStamp;}
		int			GetDimSize()			const { return DimSize; }
		float		Getbaseline()			const { return baseline; } 
		float		Getqfast()				const { return qfast; }
		float		Getqtot()				const { return qtot;}
		float		Getpeaktime()			const { return peaktime;}
		float		Getamp()				const { return amp; }
		TH1D        *GetWavHist()			const { return hwav; }
		TSplineFit	*GetWavSplineFit()		const { return fsplinewav; }
		ClassDef(Waveform,2)
};


#endif  
