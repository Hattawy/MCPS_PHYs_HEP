/*************************************************************************
    > File Name: draw_signal.C
    > Author: Jingbo Wang
    > mail: wjingbo@anl.gov 
    > Created Time: Wed Dec 16 22:12:20 2015
 ************************************************************************/
void draw_signal(char* foutfile) {
    TTree *lappd;
    TFile *f = new TFile(foutfile,"UPDATE");
	lappd = (TTree*)f->Get("lappd");
    TCanvas *c1=new TCanvas("c1","c1",50,50,600,500);
//    c1->SetGridx();
//	c1->SetGridy();
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
    temp = (TGraph*)gPad->GetPrimitive("Graph");
    TGraph *gr0 = (TGraph*)temp->Clone("gr0");
    gr0->SetTitle("Signal waveforms");
    gr0->GetXaxis()->SetRangeUser(22,30);
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
//    lappd->Draw("evt.fwav[1].vol_fft:(evt.t/1000)","evt.evtno == 10","samel");


    int m = 0;
    for(int i=1;i<10000;i++) {
    	c1->Update();
        char buff[100];
        sprintf(buff,"evt.evtno == %d && evt.fwav[1].amp>10",i);
        int n = lappd->Draw("evt.fwav[1].vol_fft:(evt.t/1000)",buff,"samel");
        cout<<"evtno = "<<i<<": "<<n<<endl;
        if(n>0) m++;
        if(m>10) break;
    }
 
 /*   
	TLegend *leg = new TLegend(0.5, 0.7, 0.8, 0.8);
	leg->SetFillColor(10);
	leg->SetBorderSize(1);
	leg->SetTextFont(42);
	leg->SetTextSize(0.04);
	leg->AddEntry(gr1,"HV = -2900 V","pl");
    leg->AddEntry(gr1,"Rise time = 0.54 ns","pl");
    leg->AddEntry(gr1,"Fall time = 1.87 ns","pl");
	leg->Draw();*/
    c1->Print("signal.ps");
}
