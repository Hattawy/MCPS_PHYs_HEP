/*************************************************************************
    > File Name: draw_signal.C
    > Author: Jingbo Wang
    > mail: wjingbo@anl.gov 
    > Created Time: Wed Dec 16 22:12:20 2015
 ************************************************************************/
void draw_frequency(char* foutfile) {
    TTree *lappd;
    TFile *f = new TFile(foutfile,"UPDATE");
	lappd = (TTree*)f->Get("lappd");
    TCanvas *c2=new TCanvas("c2","c2",50,50,600,500);
//    c2->SetGridx();
//	c2->SetGridy();
	c2->SetBottomMargin(0.15);
	c2->SetLeftMargin(0.15);
	gStyle->SetOptFit(0100);
    gStyle->SetOptStat(0000);
    lappd->Draw("evt.fwav[1].mag_fft:evt.fz>>h1(500,0,5e9)","evt.fwav[1].time>0 && evt.evtno<100");
    TH1F *h1;
    h1 = (TH1F*)gDirectory->Get("h1");	
    h1->GetXaxis()->SetTitle("Frequency [Hz]");
    h1->ProfileX()->Draw();
    h1->SetLineColor("kRed");

    TPaveText *pt = new TPaveText(0.5,0.5,0.8,0.8,"blNDC");
    pt->SetFillColor(10);
    pt->SetBorderSize(1);
    TText *text1 = pt->AddText("Red: signal");
    text1->SetTextAngle(0);
    text1->SetTextAlign(22);
    text1->SetTextFont(42);
    text1->SetTextSize(0.04);
    TText *text2 = pt->AddText("Blue: noise");
    text2->SetTextAngle(0);
    text2->SetTextAlign(22);
    text2->SetTextFont(42);
    text2->SetTextSize(0.04);
    pt->Draw();


/*
	TLegend *leg = new TLegend(0.5, 0.7, 0.8, 0.8);
	leg->SetFillColor(10);
//    leg->SetLineColor(10);
	leg->SetBorderSize(1);
	leg->SetTextFont(42);
	leg->SetTextSize(0.04);
	leg->AddEntry(gr1,"HV_{Total} = -3260 V","pl");
	leg->Draw();
//    c2->Print("frequency.ps")
*/

}

