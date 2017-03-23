#define Global_analyzer_cxx
#include "Global_analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
 
void Draw_signal(char* inputfile);

void Global_analyzer::Loop()
{

   // some setting for the histograms --------------------------
   gStyle->SetStatFontSize(0.12);
   gStyle->SetStatW(0.2);
   gROOT->Reset();
   gStyle->SetOptStat("emr");
   gStyle->SetPalette(55);   
   gStyle->SetLabelSize(0.03,"xyz"); // size of axis value font 
   gStyle->SetTitleSize(0.035,"xyz"); // size of axis title font 
   gStyle->SetTitleFont(22,"xyz"); // font option 
   gStyle->SetLabelFont(22,"xyz");
   gStyle->SetTitleOffset(1.2,"y");
   gStyle->SetCanvasBorderMode(0);
   gStyle->SetCanvasBorderSize(0);
   gStyle->SetPadBottomMargin(0.15); //margins... 
   gStyle->SetPadTopMargin(0.1);
   gStyle->SetPadLeftMargin(0.15);
   gStyle->SetPadRightMargin(0.1);
   gStyle->SetFrameBorderMode(0);
   gStyle->SetPaperSize(20,24);
   gStyle->SetLabelSize(0.05,"xy");
   gStyle->SetTitleSize(0.06,"xy");

   // define the histograms here ----------------------
   TH1F *h_Gains = new TH1F("h_Gains","", 200, 23800000,24700000);   
   TH1F *h_amp = new TH1F("h_amp","", 200, 14.5,16.5);      
   TH1F *h_timing = new TH1F("h_timing","", 200, -20500,-19000);      

   
   if (fChain == 0) return;
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;

   // Here we do loop over the events to show them ------
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      
         h_Gains->Fill(fwav_gain[1]+fwav_gain[2]);
         h_amp->Fill(fwav_amp[1]);


   } // end the loop over the events 

   gSystem->mkdir("../plots",true);
   cout<<fChain->GetName()<<endl;
   cout<<fChain->GetCurrentFile()->GetName()<<endl;
   Draw_signal(Form("%s",fChain->GetCurrentFile()->GetName()));
   

  // print the output histograms here
   TCanvas *c1=new TCanvas("c1","c1",50,50,750,500);
   c1->SetBottomMargin(0.15);
   c1->SetLeftMargin(0.15);
   c1->cd();


   // plot the amplitudes
   h_amp->GetXaxis()->SetTitle("Signal amplitude [mV]");
   h_amp->GetXaxis()->CenterTitle(true);
   h_amp->GetXaxis()->SetTitleSize(0.05);
   h_amp->GetXaxis()->SetLabelSize(0.04);
   h_amp->GetXaxis()->SetTitleOffset(1.2);
   h_amp->GetYaxis()->SetTitle("Counts");
   h_amp->GetYaxis()->CenterTitle(true);
   h_amp->GetYaxis()->SetTitleSize(0.05);
   h_amp->GetYaxis()->SetLabelSize(0.04);
   h_amp->GetYaxis()->SetTitleOffset(1.2);
   h_amp->SetLineWidth(3);
   h_amp->SetLineColor(28);
   h_amp->SetFillColor(28);
   h_amp->Draw();
   c1->Print("plots/amplitudes.png");

   // plot the gains
   c1->SetLogy();
   h_Gains->GetXaxis()->SetTitle("Gain");
   h_Gains->GetXaxis()->CenterTitle(true);
   h_Gains->GetXaxis()->SetTitleSize(0.05);
   h_Gains->GetXaxis()->SetLabelSize(0.04);
   h_Gains->GetXaxis()->SetTitleOffset(1.2);
   h_Gains->GetYaxis()->SetTitle("Counts");
   h_Gains->GetYaxis()->CenterTitle(true);
   h_Gains->GetYaxis()->SetTitleSize(0.05);
   h_Gains->GetYaxis()->SetLabelSize(0.04);
   h_Gains->GetYaxis()->SetTitleOffset(1.2);
   h_Gains->SetLineWidth(3);
   h_Gains->SetLineColor(28);
   h_Gains->SetFillColor(28);
   h_Gains->Draw();
   c1->Print("plots/gain.png");

} // end of the main loop



//subroutine to draw waveform signals
void Draw_signal(char* inputfile) {
    TTree *lappd;
    TFile *f = new TFile(inputfile,"UPDATE");
    lappd = (TTree*)f->Get("lappd");

    TCanvas *c1=new TCanvas("c1","c1",50,50,750,500);
    c1->SetGridx();
    c1->SetGridy();
    c1->SetBottomMargin(0.15);
    c1->SetLeftMargin(0.15);
    gStyle->SetOptFit(0100);
    gStyle->SetOptStat(0000);
    lappd->Draw("evt.fwav[1].amp>>h1","evt.fwav[1].time>0"); 
    TH1D *h1 = (TH1D*)gDirectory->Get("h1");
    double ampmean = h1->GetMean();
    double amprms = h1->GetRMS();
    double ampmax = ampmean+5*amprms;
    TGraph *temp;
    int n = lappd->Draw("evt.fwav[1].vol_fft:(evt.t/1000)","evt.evtno == 1"); 
    cout << "enm n = " << n << endl;
    temp = (TGraph*)gPad->GetPrimitive("Graph");
    TGraph *gr0 = (TGraph*)temp->Clone("gr0");
    gr0->SetTitle("Signal waveforms");
    gr0->GetXaxis()->SetRangeUser(2,50);
    gr0->GetXaxis()->SetTitle("t [ns]");
    gr0->GetXaxis()->SetTitleSize(0.05);
    gr0->GetXaxis()->SetLabelSize(0.04);
    gr0->GetXaxis()->SetTitleOffset(1.2);
    gr0->GetYaxis()->SetTitle("Output Voltage [mV]");
    gr0->GetYaxis()->SetTitleSize(0.05);
    gr0->GetYaxis()->SetLabelSize(0.04);
    gr0->GetYaxis()->SetTitleOffset(1.2);
    gr0->GetYaxis()->SetRangeUser(-1*ampmax,0.2*ampmax);
    gr0->Draw("al");

    int m = 0;
    int hl=10;
   
    cout << "Using hl = " <<hl<<endl;
    for(int i=1;i<hl;i++) {
    	c1->Update();
        char buff[100];
        sprintf(buff,"evt.evtno == %d && evt.fwav[1].amp>10",i);
        int n = lappd->Draw("evt.fwav[1].vol_fft:(evt.t/1000)",buff,"samel");
        cout<<"evtno = "<<i<<" out of n = "<<n<<endl;
        if(n>0) m++;
    }
   
	TLegend *leg = new TLegend(0.5, 0.6, 0.8, 0.75);
	leg->SetFillColor(10);
	leg->SetBorderSize(1);
	leg->SetTextFont(42);
	leg->SetTextSize(0.04);
	leg->AddEntry(gr0,"HV = -2900 V","pl");
	leg->AddEntry(gr0,"Rise time = 0.54 ns","pl");
	leg->AddEntry(gr0,"Fall time = 1.87 ns","pl");
	leg->Draw();

    c1->Print("plots/signals.png");
}


