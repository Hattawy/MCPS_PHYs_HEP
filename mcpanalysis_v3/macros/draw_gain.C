/*************************************************************************
    > File Name: draw_gain.C
    > Author: Jingbo Wang
    > mail: wjingbo@anl.gov 
    > Created Time: Thu Dec 17 02:23:25 2015
 ************************************************************************/

#include<stdio.h>
void draw_gain(char* foutfile) {
    TTree *lappd;
    TFile *f = new TFile(foutfile,"UPDATE");
	lappd = (TTree*)f->Get("lappd");
    TCanvas *c3=new TCanvas("c3","c3",50,50,600,500);
    c3->SetLogy();
//    c3->SetGridx();
//	c3->SetGridy();
	c3->SetBottomMargin(0.15);
	c3->SetLeftMargin(0.15);
	gStyle->SetOptFit(0100);
    gStyle->SetOptStat(0000);
    lappd->Draw("evt.fwav[1].gain+evt.fwav[2].gain>>h1"); 
    TH1F *h1 = (TH1F*)gDirectory->Get("h1");
    h1->GetXaxis()->SetTitle("Gain");
	h1->GetXaxis()->SetTitleSize(0.05);
   	h1->GetXaxis()->SetLabelSize(0.04);
   	h1->GetXaxis()->SetTitleOffset(1.2);
	h1->GetYaxis()->SetTitle("Counts");
	h1->GetYaxis()->SetTitleSize(0.05);
   	h1->GetYaxis()->SetLabelSize(0.04);
   	h1->GetYaxis()->SetTitleOffset(1.2);
    h1->SetLineWidth(3);
    h1->SetLineColor(4);
    h1->SetFillColor(4);
    h1->Draw();
    lappd->Draw("evt.fwav[1].gain+evt.fwav[2].gain>>h2","evt.fwav[1].time>0 && evt.fwav[2].time>0 && evt.fwav[1].risingtime>400&&evt.fwav[1].amp>2&&evt.fwav[2].amp>2","same"); 
    TH1F *h2 = (TH1F*)gDirectory->Get("h2");
    h2->GetXaxis()->SetTitle("Gain");
	h2->GetXaxis()->SetTitleSize(0.05);
   	h2->GetXaxis()->SetLabelSize(0.04);
   	h2->GetXaxis()->SetTitleOffset(1.2);
	h2->GetYaxis()->SetTitle("Counts");
	h2->GetYaxis()->SetTitleSize(0.05);
   	h2->GetYaxis()->SetLabelSize(0.04);
   	h2->GetYaxis()->SetTitleOffset(1.2);
    h2->SetLineWidth(3);
    h2->SetLineColor(kCyan);
    h2->SetFillColor(kCyan);
    h1->Draw();
    h2->Draw("Bsame");
    h2->Draw("AxisSame");
	TLegend *leg = new TLegend(0.5, 0.7, 0.8, 0.8);
	leg->SetFillColor(10);
	leg->SetBorderSize(1);
	leg->SetTextFont(42);
	leg->SetTextSize(0.04);
	leg->AddEntry(h1,"All pulses including pedestal","pl");
    leg->AddEntry(h2,"Pulses with quality cut","pl");
	leg->Draw();

}
