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
/*    int n = lappd->Draw("evt.fwav[1].mag_fft:evt.fz","evt.evtno == 0"); 
    TGraph *temp;
    temp = (TGraph*)gPad->GetPrimitive("Graph");
    TGraph *gr1 = (TGraph*)temp->Clone("gr1");
    gr1->SetTitle("Frequency components");
    gPad->Clear();
    gr1->GetXaxis()->SetTitle("Frequency [Hz]");
	gr1->GetXaxis()->SetTitleSize(0.05);
   	gr1->GetXaxis()->SetLabelSize(0.04);
   	gr1->GetXaxis()->SetTitleOffset(1.2);
	gr1->GetYaxis()->SetTitle("Amplitude [dB]");
	gr1->GetYaxis()->SetTitleSize(0.05);
   	gr1->GetYaxis()->SetLabelSize(0.04);
   	gr1->GetYaxis()->SetTitleOffset(1.2);
    gr1->Draw("al");*/

    TGraph *temp, *gr1, *gr2;
//draw signal frequency
    int m = 0;
    for(int i=0;i<10000;i++) {
        char buff[100];
        sprintf(buff,"evt.evtno == %d && evt.fwav[1].amp>1",i); //modify the amplitude here
        int n = lappd->Draw("evt.fwav[1].mag_fft:evt.fz",buff);
        temp = (TGraph*)gPad->GetPrimitive("Graph");
        gr1 = (TGraph*)temp->Clone("gr1");
        cout<<"evtno = "<<i<<": "<<n<<endl;
        if(n>0) m++;
        if(m>1) break;
    }

    gr1->SetTitle("Frequency components");
    gr1->GetXaxis()->SetTitleSize(0.05);
   	gr1->GetXaxis()->SetLabelSize(0.04);
   	gr1->GetXaxis()->SetTitleOffset(1.2);
    gr1->GetXaxis()->SetTitle("Frequency [Hz]");
	gr1->GetYaxis()->SetTitle("Amplitude [dB]");
	gr1->GetYaxis()->SetTitleSize(0.05);
   	gr1->GetYaxis()->SetLabelSize(0.04);
   	gr1->GetYaxis()->SetTitleOffset(1.2);
    gr1->SetLineColor(2);
    gr1->Draw("al");
//draw noise frequency
    for(int i=m;i<10000;i++) {
        char buff[100];
        sprintf(buff,"evt.evtno == %d && evt.fwav[1].time == 0",i);
        int n = lappd->Draw("evt.fwav[1].mag_fft:evt.fz",buff,"samel");
        cout<<"evtno = "<<i<<": "<<n<<endl;
        if(n>0) m++;
        if(m>2) break;
    }

    TPaveText *pt = new TPaveText(0.5,0.5,0.8,0.6,"blNDC");
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

