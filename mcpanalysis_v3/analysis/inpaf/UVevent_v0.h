//----------APS Analysis 
//----------Author's Name:Jingbo WANG
//----------Copyright:Those valid for ANL
//----------Modified:22/07/2014
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
	int			WavDimSize;
	
public: 

  UVevent(); 
  UVevent(float fsamplerate, int fdimsize);
  virtual ~UVevent(); 
  void          Clear(Option_t *option ="");

  int			evtno;
	TClonesArray	*fwav;            //->array with all waveforms (not used yet)
	int			fnwav;            //Number of waveforms
	int			ClusterSize;			//Number of fired strips

	static TClonesArray *fgWaveforms;
 
	int			Cutflag;		//
	vector<float>	t;
	vector<float>	fz;
	float			tabs;			//
	float			tdiff;
	float			x;		//Parallel postion
	float			y;		//Transverse position

	int				Setevtno(int fevtno)			{ evtno = fevtno; return evtno; }
	float			SetWavSampleRate(float frate)	{WavSampleRate = frate; return WavSampleRate;}
	int				SetWavDimSize(int fsize)		{WavDimSize = fsize; return WavDimSize;}
	int				SetCutflag(int flag)			{ Cutflag = flag; return Cutflag;}
	int				SetWavNumber(int fn)			{ fnwav = fn; return fnwav;}
	int				Getevtno()						const { return evtno; }
	TClonesArray	*GetWaveforms()					const { return fwav; }
	int				GetWavNumber()					const { return fnwav;}
	void			Analyze();
  
  ClassDef(UVevent,1) 

}; 


class Waveform: public TObject {
private:
		
		float		Calculate_baseline(float* fvol); //
		float		Calculate_baseline2(float* fvol);
		float		Waveform_Filter1(float CutoffFrequency, float finput);		//ideal low-pass filter
		float		Waveform_Filter2(float CutoffFrequency, int T, float finput); //Butterworth low-pass filter
		float		Waveform_Filter3(float CutoffFrequency_low, float CutoffFrequency_high, float finput);		//ideal low-pass filter
		void		Calculate_fitrange();

		void		Waveform_FFT();
		void		Waveform_Fit();
		float		CFD_Discriminator1();
		float		CFD_Discriminator2();
		float		GaussFit();
		float		Calculate_amp();
		float		Calculate_Charge();
		int			Calculate_Peaks();
public: 
		int			DoFFT;
		int			Samplerate;		//sampling rate
		float		Deltat;			//time per sample
		int			DimSize;		//Number of samples
		float		baseline;		//Base line of this waveform
		float		qfast;			//fast charge
		float		qtot;			//total charge
		float		gain;
		float		amp;		//amp of the pulse
		double		time;	//leading edge
		int			MinimumTot;
		int			npeaks;
		int			evtno;		//UVevent number
		int			chno;
		double        gmean;
		double        gsigma;
		double        gpeak;
		double        gtime;
		double        grisetime;
		double        gchi2;          //Gaussian parameters
		double		TSplineCFDChi2;
		int			PointsPerSpline; //Number of measured points for one spline
		float		TimeStamp;	//Time stamp of this waveform
		
		vector<float>	vol;
		vector<float>	vol_fft;
		vector<float>	re_fft;
		vector<float>	im_fft;

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
		double		AmpThreshold;
		double		Fraction_CFD;	//fraction of Attenuation 
		int			Delay_CFD;		//
		char*		AnalysisOption;
		
		Waveform();
		virtual		~Waveform();
		void		Clear(Option_t *option="");
		int			Setevtno(int fevtno)		{evtno = fevtno; return evtno;}
		int			Setchno(int fchno)			{chno = fchno; return chno;}
		float		SetSamplingrate(float frate)	{Samplerate = frate; return Samplerate;}
		float		SetDeltat(float fdeltat)	{Deltat = fdeltat; return Deltat;}
		int			SetPointsPerSpline(int fm)		{PointsPerSpline = fm; return PointsPerSpline;};
		int			SetDimSize(int fDimSize)		{DimSize = fDimSize; return DimSize;}
		float		SetTimeStamp(float ft)		{TimeStamp = ft; return TimeStamp;}
		double		SetAmpThreshold(double fth) {AmpThreshold = fth; return AmpThreshold;}
		double		SetFraction_CFD(double fraction) {Fraction_CFD = fraction; return Fraction_CFD;}
		int			SetDelay_CFD(double delay) {Delay_CFD = delay; return Delay_CFD;}
		int			EnableFFT()						{DoFFT = 1; return DoFFT;}
		int			EnableDynamicWindow()			{IfDynamicWindow = 1; return IfDynamicWindow;}
		float		SetCutoffFrequency(float f) {CutoffFrequency = f; return CutoffFrequency;};
		int			SetMinimumTot(int fdt)		{MinimumTot = fdt; return MinimumTot;}
		
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
		float		Getamp()				const { return amp; }
		TH1D        *GetWavHist()			const { return hwav; }
		TSplineFit	*GetWavSplineFit()		const { return fsplinewav; }
		ClassDef(Waveform,2)
};


#endif  
