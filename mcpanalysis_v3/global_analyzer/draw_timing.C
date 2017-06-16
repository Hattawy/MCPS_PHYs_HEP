/*************************************************************************
    > File Name: draw_gain.C
    > Author: Jingbo Wang
    > mail: wjingbo@anl.gov 
    > Created Time: Thu Dec 17 02:23:25 2015
 ************************************************************************/

#include<stdio.h>
void draw_timing(char* foutfile) {
    TTree *lappd;
    TFile *f = new TFile(foutfile,"UPDATE");
	lappd = (TTree*)f->Get("lappd");
    TCanvas *c1=new TCanvas("c1","c1",50,50,600,500);
    c1->SetLogy();
//    c1->SetGridx();
//	c1->SetGridy();
	c1->SetBottomMargin(0.15);
	c1->SetLeftMargin(0.15);
	gStyle->SetOptFit(0100);
    gStyle->SetOptStat(0000);
    TF1 *f1 = new TF1("f1","gaus",-10000,40000);
	f1->SetNpx(10000);
	f1->SetLineColor(2);
	f1->SetLineStyle(2);
	TF1 *f2 = new TF1("f2","gaus",-10000,40000);
	f2->SetNpx(10000);
	f2->SetLineColor(4);
	f2->SetLineStyle(3);
	TF1 *f3 = new TF1("f3","f1+f2",-10000,40000);
	f3->SetNpx(10000);
	f3->SetLineColor(8);
	f3->SetParNames("constant1","mean1","sigma1","constant2","mean2","sigma2");
	f3->SetLineColor(1);
	lappd->Draw("(evt.fwav[1].time+evt.fwav[2].time)/2-evt.fwav[0].time>>h1(10000,-100000,100000)","evt.fwav[1].amp>0 && evt.fwav[2].amp>0 && evt.fwav[1].time>0","H");  
//	lappd->Draw("(evt.fwav[1].time+evt.fwav[2].time)/2-evt.fwav[0].time>>h1(400,-18500,-15000)","evt.fwav[1].amp>0 && evt.fwav[2].amp>0 && evt.fwav[1].time>0","H");  
    TH1F *h1 = (TH1F*)gDirectory->Get("h1");
    h1 = (TH1F*)gDirectory->Get("h1");		
	h1->GetXaxis()->SetTitle("#DeltaT [ps]");
    h1->GetXaxis()->SetNdivisions(509);
	h1->GetXaxis()->SetTitleSize(0.05);
   	h1->GetXaxis()->SetLabelSize(0.04);
   	h1->GetXaxis()->SetTitleOffset(1.2);
	h1->GetYaxis()->SetTitle("Counts");
	h1->GetYaxis()->SetTitleSize(0.05);
   	h1->GetYaxis()->SetLabelSize(0.04);
   	h1->GetYaxis()->SetTitleOffset(1.2);
    h1->GetYaxis()->SetRangeUser(1,1.5*h1->GetMaximum());
    h1->SetLineWidth(1);
    h1->SetMarkerStyle(8);
    h1->SetMarkerSize(0.6);
    h1->SetOption("BP");
    h1->SetFillColor(kCyan);
    
	double par[12];
	double rms = h1->GetRMS();
	double mean = h1->GetMean();
	int binmax = h1->GetMaximumBin();
	double xpeak = h1->GetBinCenter(binmax);
	double fwhm = 0;
	for(int i=0;;i++) {
		if(h1->GetBinContent(binmax+i)<0.5*h1->GetMaximum()) {
			fwhm = i*100*2;
			break;
		}
	}
	h1->GetXaxis()->SetRangeUser(xpeak-3*fwhm, xpeak+4*fwhm);
//	h1->Fit("f1","r","",34400,34700); //tube44
	h1->Fit("f1","r","",xpeak-rms,xpeak+rms/2); //tube44
	f1->GetParameters(&par[0]);
	par[3] = 1./5*par[0];
	par[4] = par[1]+180;
	par[5] = par[2]*2;
	f3->SetParameters(&par[0]);
	f3->SetParLimits(1,par[1]-20,par[1]+20);
	f3->SetParLimits(4,par[4]-50,par[4]+50);
//	h1->Fit("f3","r","",28000,30000); //tube32
	h1->Fit("f3","r","",mean-5*rms,mean+5*rms); //tube32
	f3->GetParameters(&par[0]);
	f1->SetParameters(&par[0]);
	f2->SetParameters(&par[3]);
	f3->SetParameters(&par[6]);
	f1->Draw("same");
	f2->Draw("same");
	f3->Draw("same");
}

