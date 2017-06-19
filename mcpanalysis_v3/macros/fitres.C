/*************************************************************************
    > File Name: Fit.C
    > Author: Jingbo Wang
    > mail: wjingbo@anl.gov 
    > Created Time: Mon Dec  1 15:20:39 2014
 ************************************************************************/
void fitres(char* foutfile){
//	if (!TClassTable::GetDict("UVevent")) {
//      gSystem->Load("libUVevent.so");
//   }
	
	TTree *lappd;
    TH1F *h1, *h2, *h3, *h4;
    TFile *f = new TFile(foutfile,"UPDATE");
	lappd = (TTree*)f->Get("lappd");
    
	TCanvas *c1=new TCanvas("c1","c1",50,50,1000,600);
	gStyle->SetOptFit(0100);
//	gStyle->SetOptStat(0000);
	c1->Divide(3,2);

    c1->cd(1)->Update();
    lappd->Draw("evt.fwav[1].vol_fft:evt.t","evt.evtno<10 && evt.fwav[1].time>0");   
    c1->cd(2)->Update();
    c1->cd(2)->SetLogy();
	lappd->Draw("evt.fwav[1].risingtime>>h3(200,200,1600)");
    h3 = (TH1F*)gDirectory->Get("h3");	
    h3->GetXaxis()->SetTitle("t [ps]");
    c1->cd(3)->Update();
    c1->cd(3)->SetLogy();
	lappd->Draw("evt.fwav[1].amp>>h1");
    h1 = (TH1F*)gDirectory->Get("h1");	
    h1->GetXaxis()->SetTitle("Amp [mV]");
    c1->cd(4)->Update();
    c1->cd(4)->SetLogy();
    lappd->Draw("evt.fwav[1].gain+evt.fwav[2].gain");
	c1->cd(5)->Update();
    c1->cd(5)->SetLogy();
	lappd->Draw("evt.fwav[1].gain+evt.fwav[2].gain>>h2","evt.fwav[1].time>0 && evt.fwav[2].time>0");
    h2 = (TH1F*)gDirectory->Get("h2");	
    h2->GetXaxis()->SetTitle("Gain");
//    h2->Fit("gaus","r","",2e6,1e8);

	c1->cd(6)->Update();
	c1->cd(6)->SetLogy();
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
	lappd->Draw("(evt.fwav[1].time+evt.fwav[2].time)/2-evt.fwav[0].time>>h4(400,-18500,-17500)","evt.fwav[1].amp>0 && evt.fwav[2].amp>0 && evt.fwav[1].time>0","H"); //tube44
//	lappd->Draw("evt.fwav[0].time>>h4(200,34800,36200)","evt.fwav[1].amp>1&&evt.fwav[2].amp>1&&evt.evtno<50000",""); //planacon
	h4 = (TH1F*)gDirectory->Get("h4");		
	h4->SetMarkerStyle(20);
    h4->GetXaxis()->SetTitle("#Deltat [ps]");
	double par[12];
	double rms = h4->GetRMS();
	double mean = h4->GetMean();
	int binmax = h4->GetMaximumBin();
	double xpeak = h4->GetBinCenter(binmax);
//	h4->Fit("f1","r","",34400,34700); //tube44
	h4->Fit("f1","r","",xpeak-rms,xpeak+rms/2); //tube44
	f1->GetParameters(&par[0]);
	par[3] = 1./5*par[0];
	par[4] = par[1]+180;
	par[5] = par[2]*2;
	f3->SetParameters(&par[0]);
	f3->SetParLimits(1,par[1]-20,par[1]+20);
	f3->SetParLimits(4,par[4]-50,par[4]+50);
//	h4->Fit("f3","r","",28000,30000); //tube32
	h4->Fit("f3","r","",mean-5*rms,mean+5*rms); //tube32
	f3->GetParameters(&par[0]);
	f1->SetParameters(&par[0]);
	f2->SetParameters(&par[3]);
	f3->SetParameters(&par[6]);
	f1->Draw("same");
	f2->Draw("same");
	f3->Draw("same");
//	cout<<"backscattering % = "<<f2->Integral(-7000,-4000)*1.0/f3->Integral(-7000,-4000)<<endl;
	

}
