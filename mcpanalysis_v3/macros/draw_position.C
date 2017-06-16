/*************************************************************************
    > File Name: draw_position.C
    > Author: Jingbo Wang
    > mail: wjingbo@anl.gov 
    > Created Time: Thu Dec 17 02:52:44 2015
 ************************************************************************/
void draw_position(char* foutfile) {
    TTree *lappd;
    TFile *f = new TFile(foutfile,"UPDATE");
	lappd = (TTree*)f->Get("lappd");
    TCanvas *c5=new TCanvas("c5","c5",50,50,600,500);
    c5->SetLogy();
//    c5->SetGridx();
//	c5->SetGridy();
	c5->SetBottomMargin(0.15);
	c5->SetLeftMargin(0.15);
	gStyle->SetOptFit(0100);
    gStyle->SetOptStat(0000);
    TF1 *f1 = new TF1("f1","gaus",-100,100);
	f1->SetNpx(1000);
	f1->SetLineColor(2);
	f1->SetLineStyle(1);
	TF1 *f2 = new TF1("f2","gaus",-100,100);
	f2->SetNpx(1000);
	f2->SetLineColor(2);
	f2->SetLineStyle(3);
	
    lappd->Draw("(evt.fwav[1].time-evt.fwav[2].time)/2*0.2>>h1(4000,-500,500)","evt.fwav[1].time>0 && evt.fwav[2].time>0","H");
    h1 = (TH1F*)gDirectory->Get("h1");		
	h1->GetXaxis()->SetTitle("X position [mm]");
	h1->GetXaxis()->SetTitleSize(0.05);
   	h1->GetXaxis()->SetLabelSize(0.04);
   	h1->GetXaxis()->SetTitleOffset(1.2);
	h1->GetYaxis()->SetTitle("Counts");
	h1->GetYaxis()->SetTitleSize(0.05);
   	h1->GetYaxis()->SetLabelSize(0.04);
   	h1->GetYaxis()->SetTitleOffset(1.2);
    h1->GetYaxis()->SetRangeUser(1,1.5*h1->GetMaximum());
    h1->SetLineWidth(1);
    h1->SetOption("B");
    h1->SetFillColor(kCyan);
    double par[12];
	double rms = h1->GetRMS();
	double mean = h1->GetMean();
	int binmax = h1->GetMaximumBin();
	double xpeak = h1->GetBinCenter(binmax);
	double fwhm = 0;
	for(int i=0;;i++) {
		if(h1->GetBinContent(binmax+i)<0.5*h1->GetMaximum()) {
			fwhm = i*2*2; //i(bins)*0.02(mm/ps)*100(ps/bin)*2
			break;
		}
	}
	h1->GetXaxis()->SetRangeUser(xpeak-3*fwhm, xpeak+3*fwhm);
//	h1->Fit("f1","r","",34400,34700); //tube44
	h1->Fit("f1","r","",xpeak-rms,xpeak+rms/2); 
	f1->GetParameters(&par[0]);
    h1->Fit("f1","r","",par[1]-2*par[2],par[1]+2*par[2]); 
    f1->GetParameters(&par[0]);
	f2->SetParameters(&par[0]);
    f2->Draw("same");
}    
