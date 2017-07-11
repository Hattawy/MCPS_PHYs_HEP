//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Mar 22 15:07:39 2017 by ROOT version 6.09/01
// from TChain ch/Global_analyzer
//////////////////////////////////////////////////////////

#ifndef Global_analyzer_h
#define Global_analyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "TObject.h"

class Global_analyzer {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
 //UVevent         *evt;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   Float_t         WavSampleRate;
   Int_t           WavDimSize;
   Float_t         WavDeltat;
   Int_t           evtno;
   Int_t           fwav_;
   UInt_t          fwav_fUniqueID[3];   //[fwav_]
   UInt_t          fwav_fBits[3];   //[fwav_]
   Int_t           fwav_DoFFT[3];   //[fwav_]
   Int_t           fwav_ReflectionCancelling[3];   //[fwav_]
   Float_t         fwav_Samplerate[3];   //[fwav_]
   Float_t         fwav_Deltat[3];   //[fwav_]
   Int_t           fwav_DimSize[3];   //[fwav_]
   Float_t         fwav_baseline[3];   //[fwav_]
   Float_t         fwav_noiserms[3];   //[fwav_]
   Float_t         fwav_qfast[3];   //[fwav_]
   Float_t         fwav_qtot[3];   //[fwav_]
   Float_t         fwav_peaktime[3];   //[fwav_]
   Float_t         fwav_gain[3];   //[fwav_]
   Float_t         fwav_amp[3];   //[fwav_]
   Double_t        fwav_time[3];   //[fwav_]
   Double_t        fwav_risingtime[3];   //[fwav_]
   Double_t        fwav_fallingtime[3];   //[fwav_]
   Double_t        fwav_TotThreshold[3];   //[fwav_]
   Int_t           fwav_MinimumTot[3];   //[fwav_]
   Int_t           fwav_npeaks[3];   //[fwav_]
   Int_t           fwav_evtno[3];   //[fwav_]
   Int_t           fwav_chno[3];   //[fwav_]
   Int_t           fwav_WavID[3];   //[fwav_]
   Int_t           fwav_TriggerMarker[3];   //[fwav_]
   Double_t        fwav_gmean[3];   //[fwav_]
   Double_t        fwav_gsigma[3];   //[fwav_]
   Double_t        fwav_gpeak[3];   //[fwav_]
   Double_t        fwav_gtime[3];   //[fwav_]
   Double_t        fwav_grisetime[3];   //[fwav_]
   Double_t        fwav_gchi2[3];   //[fwav_]
   Char_t          fwav_WavName[3][100];   //[fwav_]
   Char_t          fwav_SplineName[3][100];   //[fwav_]
   Char_t          fwav_SplineTitle[3][100];   //[fwav_]
   Int_t           fwav_PointsPerSpline[3];   //[fwav_]
   Char_t          fwav_CFDName[3][100];   //[fwav_]
   Char_t          fwav_CFDTitle[3][100];   //[fwav_]
   Char_t          fwav_CFDSplineName[3][100];   //[fwav_]
   Char_t          fwav_CFDSplineTitle[3][100];   //[fwav_]
   Float_t         fwav_TimeStamp[3];   //[fwav_]
   vector<float>   fwav_vol[3];
   vector<float>   fwav_vol_cfd[3];
   vector<float>   fwav_vol_fft[3];
   vector<float>   fwav_re_fft[3];
   vector<float>   fwav_im_fft[3];
   vector<float>   fwav_mag_fft[3];
   vector<float>   fwav_mag_processed[3];
   Int_t           fwav_IfDynamicWindow[3];   //[fwav_]
   Double_t        fwav_FitWindow_min[3];   //[fwav_]
   Double_t        fwav_FitWindow_max[3];   //[fwav_]
   Double_t        fwav_DisWindow_min[3];   //[fwav_]
   Double_t        fwav_DisWindow_max[3];   //[fwav_]
   Float_t         fwav_CutoffFrequency[3];   //[fwav_]
   Float_t         fwav_ReflectionWindow_min[3];   //[fwav_]
   Float_t         fwav_ReflectionWindow_max[3];   //[fwav_]
   Double_t        fwav_AmpThreshold[3];   //[fwav_]
   Double_t        fwav_Fraction_CFD[3];   //[fwav_]
   Int_t           fwav_Delay_CFD[3];   //[fwav_]
   char*           fwav_AnalysisOption[3];   //[fwav_]
   Int_t           fnwav;
   Int_t           ClusterSize;
   Int_t           cutflag;
   vector<float>   t;
   vector<float>   fz;
   Float_t         tabs;
   Float_t         tdiff;
   Float_t         x;
   Float_t         y;

   // List of branches
   TBranch        *b_evt_fUniqueID;   //!
   TBranch        *b_evt_fBits;   //!
   TBranch        *b_evt_WavSampleRate;   //!
   TBranch        *b_evt_WavDimSize;   //!
   TBranch        *b_evt_WavDeltat;   //!
   TBranch        *b_evt_evtno;   //!
   TBranch        *b_evt_fwav_;   //!
   TBranch        *b_fwav_fUniqueID;   //!
   TBranch        *b_fwav_fBits;   //!
   TBranch        *b_fwav_DoFFT;   //!
   TBranch        *b_fwav_ReflectionCancelling;   //!
   TBranch        *b_fwav_Samplerate;   //!
   TBranch        *b_fwav_Deltat;   //!
   TBranch        *b_fwav_DimSize;   //!
   TBranch        *b_fwav_baseline;   //!
   TBranch        *b_fwav_noiserms;   //!
   TBranch        *b_fwav_qfast;   //!
   TBranch        *b_fwav_qtot;   //!
   TBranch        *b_fwav_peaktime;   //!
   TBranch        *b_fwav_gain;   //!
   TBranch        *b_fwav_amp;   //!
   TBranch        *b_fwav_time;   //!
   TBranch        *b_fwav_risingtime;   //!
   TBranch        *b_fwav_fallingtime;   //!
   TBranch        *b_fwav_TotThreshold;   //!
   TBranch        *b_fwav_MinimumTot;   //!
   TBranch        *b_fwav_npeaks;   //!
   TBranch        *b_fwav_evtno;   //!
   TBranch        *b_fwav_chno;   //!
   TBranch        *b_fwav_WavID;   //!
   TBranch        *b_fwav_TriggerMarker;   //!
   TBranch        *b_fwav_gmean;   //!
   TBranch        *b_fwav_gsigma;   //!
   TBranch        *b_fwav_gpeak;   //!
   TBranch        *b_fwav_gtime;   //!
   TBranch        *b_fwav_grisetime;   //!
   TBranch        *b_fwav_gchi2;   //!
   TBranch        *b_fwav_WavName;   //!
   TBranch        *b_fwav_SplineName;   //!
   TBranch        *b_fwav_SplineTitle;   //!
   TBranch        *b_fwav_PointsPerSpline;   //!
   TBranch        *b_fwav_CFDName;   //!
   TBranch        *b_fwav_CFDTitle;   //!
   TBranch        *b_fwav_CFDSplineName;   //!
   TBranch        *b_fwav_CFDSplineTitle;   //!
   TBranch        *b_fwav_TimeStamp;   //!
   TBranch        *b_fwav_vol;   //!
   TBranch        *b_fwav_vol_cfd;   //!
   TBranch        *b_fwav_vol_fft;   //!
   TBranch        *b_fwav_re_fft;   //!
   TBranch        *b_fwav_im_fft;   //!
   TBranch        *b_fwav_mag_fft;   //!
   TBranch        *b_fwav_mag_processed;   //!
   TBranch        *b_fwav_IfDynamicWindow;   //!
   TBranch        *b_fwav_FitWindow_min;   //!
   TBranch        *b_fwav_FitWindow_max;   //!
   TBranch        *b_fwav_DisWindow_min;   //!
   TBranch        *b_fwav_DisWindow_max;   //!
   TBranch        *b_fwav_CutoffFrequency;   //!
   TBranch        *b_fwav_ReflectionWindow_min;   //!
   TBranch        *b_fwav_ReflectionWindow_max;   //!
   TBranch        *b_fwav_AmpThreshold;   //!
   TBranch        *b_fwav_Fraction_CFD;   //!
   TBranch        *b_fwav_Delay_CFD;   //!
   TBranch        *b_fwav_AnalysisOption;   //!
   TBranch        *b_evt_fnwav;   //!
   TBranch        *b_evt_ClusterSize;   //!
   TBranch        *b_evt_cutflag;   //!
   TBranch        *b_evt_t;   //!
   TBranch        *b_evt_fz;   //!
   TBranch        *b_evt_tabs;   //!
   TBranch        *b_evt_tdiff;   //!
   TBranch        *b_evt_x;   //!
   TBranch        *b_evt_y;   //!

   Global_analyzer(TTree *tree=0);
   virtual ~Global_analyzer();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Global_analyzer_cxx
Global_analyzer::Global_analyzer(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {

#ifdef SINGLE_TREE
      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Memory Directory");
      if (!f || !f->IsOpen()) {
         f = new TFile("Memory Directory");
      }
      f->GetObject("ch",tree);

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("ch","Global_analyzer");
      chain->Add("run2028.root/lappd");
      //chain->Add("../data/Run1181_2017-05-04_tube_74_laser__2700V/run1181.root/lappd");
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

Global_analyzer::~Global_analyzer()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Global_analyzer::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Global_analyzer::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Global_analyzer::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_evt_fUniqueID);
   fChain->SetBranchAddress("fBits", &fBits, &b_evt_fBits);
   fChain->SetBranchAddress("WavSampleRate", &WavSampleRate, &b_evt_WavSampleRate);
   fChain->SetBranchAddress("WavDimSize", &WavDimSize, &b_evt_WavDimSize);
   fChain->SetBranchAddress("WavDeltat", &WavDeltat, &b_evt_WavDeltat);
   fChain->SetBranchAddress("evtno", &evtno, &b_evt_evtno);
   fChain->SetBranchAddress("fwav", &fwav_, &b_evt_fwav_);
   fChain->SetBranchAddress("fwav.fUniqueID", fwav_fUniqueID, &b_fwav_fUniqueID);
   fChain->SetBranchAddress("fwav.fBits", fwav_fBits, &b_fwav_fBits);
   fChain->SetBranchAddress("fwav.DoFFT", fwav_DoFFT, &b_fwav_DoFFT);
   fChain->SetBranchAddress("fwav.ReflectionCancelling", fwav_ReflectionCancelling, &b_fwav_ReflectionCancelling);
   fChain->SetBranchAddress("fwav.Samplerate", fwav_Samplerate, &b_fwav_Samplerate);
   fChain->SetBranchAddress("fwav.Deltat", fwav_Deltat, &b_fwav_Deltat);
   fChain->SetBranchAddress("fwav.DimSize", fwav_DimSize, &b_fwav_DimSize);
   fChain->SetBranchAddress("fwav.baseline", fwav_baseline, &b_fwav_baseline);
   fChain->SetBranchAddress("fwav.noiserms", fwav_noiserms, &b_fwav_noiserms);
   fChain->SetBranchAddress("fwav.qfast", fwav_qfast, &b_fwav_qfast);
   fChain->SetBranchAddress("fwav.qtot", fwav_qtot, &b_fwav_qtot);
   fChain->SetBranchAddress("fwav.peaktime", fwav_peaktime, &b_fwav_peaktime);
   fChain->SetBranchAddress("fwav.gain", fwav_gain, &b_fwav_gain);
   fChain->SetBranchAddress("fwav.amp", fwav_amp, &b_fwav_amp);
   fChain->SetBranchAddress("fwav.time", fwav_time, &b_fwav_time);
   fChain->SetBranchAddress("fwav.risingtime", fwav_risingtime, &b_fwav_risingtime);
   fChain->SetBranchAddress("fwav.fallingtime", fwav_fallingtime, &b_fwav_fallingtime);
   fChain->SetBranchAddress("fwav.TotThreshold", fwav_TotThreshold, &b_fwav_TotThreshold);
   fChain->SetBranchAddress("fwav.MinimumTot", fwav_MinimumTot, &b_fwav_MinimumTot);
   fChain->SetBranchAddress("fwav.npeaks", fwav_npeaks, &b_fwav_npeaks);
   fChain->SetBranchAddress("fwav.evtno", fwav_evtno, &b_fwav_evtno);
   fChain->SetBranchAddress("fwav.chno", fwav_chno, &b_fwav_chno);
   fChain->SetBranchAddress("fwav.WavID", fwav_WavID, &b_fwav_WavID);
   fChain->SetBranchAddress("fwav.TriggerMarker", fwav_TriggerMarker, &b_fwav_TriggerMarker);
   fChain->SetBranchAddress("fwav.gmean", fwav_gmean, &b_fwav_gmean);
   fChain->SetBranchAddress("fwav.gsigma", fwav_gsigma, &b_fwav_gsigma);
   fChain->SetBranchAddress("fwav.gpeak", fwav_gpeak, &b_fwav_gpeak);
   fChain->SetBranchAddress("fwav.gtime", fwav_gtime, &b_fwav_gtime);
   fChain->SetBranchAddress("fwav.grisetime", fwav_grisetime, &b_fwav_grisetime);
   fChain->SetBranchAddress("fwav.gchi2", fwav_gchi2, &b_fwav_gchi2);
   fChain->SetBranchAddress("fwav.WavName[100]", fwav_WavName, &b_fwav_WavName);
   fChain->SetBranchAddress("fwav.SplineName[100]", fwav_SplineName, &b_fwav_SplineName);
   fChain->SetBranchAddress("fwav.SplineTitle[100]", fwav_SplineTitle, &b_fwav_SplineTitle);
   fChain->SetBranchAddress("fwav.PointsPerSpline", fwav_PointsPerSpline, &b_fwav_PointsPerSpline);
   fChain->SetBranchAddress("fwav.CFDName[100]", fwav_CFDName, &b_fwav_CFDName);
   fChain->SetBranchAddress("fwav.CFDTitle[100]", fwav_CFDTitle, &b_fwav_CFDTitle);
   fChain->SetBranchAddress("fwav.CFDSplineName[100]", fwav_CFDSplineName, &b_fwav_CFDSplineName);
   fChain->SetBranchAddress("fwav.CFDSplineTitle[100]", fwav_CFDSplineTitle, &b_fwav_CFDSplineTitle);
   fChain->SetBranchAddress("fwav.TimeStamp", fwav_TimeStamp, &b_fwav_TimeStamp);
   fChain->SetBranchAddress("fwav.vol", fwav_vol, &b_fwav_vol);
   fChain->SetBranchAddress("fwav.vol_cfd", fwav_vol_cfd, &b_fwav_vol_cfd);
   fChain->SetBranchAddress("fwav.vol_fft", fwav_vol_fft, &b_fwav_vol_fft);
   fChain->SetBranchAddress("fwav.re_fft", fwav_re_fft, &b_fwav_re_fft);
   fChain->SetBranchAddress("fwav.im_fft", fwav_im_fft, &b_fwav_im_fft);
   fChain->SetBranchAddress("fwav.mag_fft", fwav_mag_fft, &b_fwav_mag_fft);
   fChain->SetBranchAddress("fwav.mag_processed", fwav_mag_processed, &b_fwav_mag_processed);
   fChain->SetBranchAddress("fwav.IfDynamicWindow", fwav_IfDynamicWindow, &b_fwav_IfDynamicWindow);
   fChain->SetBranchAddress("fwav.FitWindow_min", fwav_FitWindow_min, &b_fwav_FitWindow_min);
   fChain->SetBranchAddress("fwav.FitWindow_max", fwav_FitWindow_max, &b_fwav_FitWindow_max);
   fChain->SetBranchAddress("fwav.DisWindow_min", fwav_DisWindow_min, &b_fwav_DisWindow_min);
   fChain->SetBranchAddress("fwav.DisWindow_max", fwav_DisWindow_max, &b_fwav_DisWindow_max);
   fChain->SetBranchAddress("fwav.CutoffFrequency", fwav_CutoffFrequency, &b_fwav_CutoffFrequency);
   fChain->SetBranchAddress("fwav.ReflectionWindow_min", fwav_ReflectionWindow_min, &b_fwav_ReflectionWindow_min);
   fChain->SetBranchAddress("fwav.ReflectionWindow_max", fwav_ReflectionWindow_max, &b_fwav_ReflectionWindow_max);
   fChain->SetBranchAddress("fwav.AmpThreshold", fwav_AmpThreshold, &b_fwav_AmpThreshold);
   fChain->SetBranchAddress("fwav.Fraction_CFD", fwav_Fraction_CFD, &b_fwav_Fraction_CFD);
   fChain->SetBranchAddress("fwav.Delay_CFD", fwav_Delay_CFD, &b_fwav_Delay_CFD);
   fChain->SetBranchAddress("fwav.AnalysisOption", fwav_AnalysisOption, &b_fwav_AnalysisOption);
   fChain->SetBranchAddress("fnwav", &fnwav, &b_evt_fnwav);
   fChain->SetBranchAddress("ClusterSize", &ClusterSize, &b_evt_ClusterSize);
   fChain->SetBranchAddress("cutflag", &cutflag, &b_evt_cutflag);
   fChain->SetBranchAddress("t", &t, &b_evt_t);
   fChain->SetBranchAddress("fz", &fz, &b_evt_fz);
   fChain->SetBranchAddress("tabs", &tabs, &b_evt_tabs);
   fChain->SetBranchAddress("tdiff", &tdiff, &b_evt_tdiff);
   fChain->SetBranchAddress("x", &x, &b_evt_x);
   fChain->SetBranchAddress("y", &y, &b_evt_y);
   Notify();
}

Bool_t Global_analyzer::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Global_analyzer::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Global_analyzer::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Global_analyzer_cxx
