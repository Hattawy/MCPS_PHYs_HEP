/*************************************************************************
    > File Name: Plot.C
    > Author: Jingbo Wang
    > mail: wjingbo@anl.gov 
    > Created Time: Fri Aug  8 09:03:27 2014
 ************************************************************************/
int ProfileMode = 0;
void Plot(char* foutfile){
	if (!TClassTable::GetDict("UVevent")) {
      gSystem->Load("libUVevent.so");
   }
	TFile *f = new TFile(foutfile,"UPDATE");
	gStyle->SetOptStat(0000);
	gStyle->SetOptFit(111);
	gStyle->SetPalette(1);
	TCanvas *canvas_raw = new TCanvas("canvas_raw","canvas_raw",0,0,800,600);
	canvas_raw->SetFillColor(kWhite);
	canvas_raw->GetFrame()->SetFillColor(21);
	canvas_raw->GetFrame()->SetBorderSize(6);
	canvas_raw->GetFrame()->SetBorderMode(-1);
	canvas_raw->Divide(4,2);
	canvas_raw->Update();
	f->cd();

	int ir = 0;
	for(int ichan=0;ichan<4;ichan++) {
		gStyle->SetOptFit(1111);
	    Char_t buf[100];
		sprintf(buf, "raw/DeltaT_%d_%d",ir, ichan);
			TH1D *Deltat = (TH1D*)gDirectory->Get(buf);
			canvas_raw->cd(ichan+1)->SetLogy();
			Deltat->GetXaxis()->SetTitle("#Deltat [ps]");
			Deltat->Draw();
			sprintf(buf, "raw/f1_%d_%d", ir, ichan);
			TF1 *f1 = (TF1*)gDirectory->Get(buf);
			TF1 *f2 = new TF1("f2", "gaus", -1000, 1000);
			double para[3];
			f1->GetParameters(&para[0]);
			f2->SetParameters(&para[0]);
			f2->SetLineStyle(2);
			f2->Draw("same");
		sprintf(buf, "raw/Channel_%d_%d", ir, ichan);
		TH1D *Channel = (TH1D*)gDirectory->Get(buf);
		canvas_raw->cd(ichan+5);
		if(ichan<2) Channel->GetXaxis()->SetTitle("Amp [mV]");
			else	Channel->GetXaxis()->SetTitle("Rise time [ps]");
		Channel->Draw("colz");
		if(ProfileMode ==0) sprintf(buf, "raw/Channel_%d_%d_pfx",ir, ichan);
		else sprintf(buf, "raw/Channel_%d_%d_1",ir, ichan);
		TH1D *htsf = (TH1D*)gDirectory->Get(buf);
		htsf->SetMarkerStyle(4);
		htsf->Draw("same");
    } 
	f->cd("plots");
//	canvas_raw->Write();
	
	f->cd();
//	TCanvas *canvas_cor[5];
	for(int ir=3;ir<4;ir++){
		cout<<"ir="<<ir<<endl;
//		gStyle->SetOptFit(1);
		Char_t cname[100];
		sprintf(cname, "canvas_cor_%d",ir);
//		cout<<"cname="<<cname<<endl;
		TCanvas *canvas_cor = new TCanvas(cname,cname,0,0,800,600);
		canvas_cor = new TCanvas(cname,cname,0,0,800,600);
		canvas_cor->SetFillColor(kWhite);
		canvas_cor->GetFrame()->SetFillColor(21);
		canvas_cor->GetFrame()->SetBorderSize(6);
		canvas_cor->GetFrame()->SetBorderMode(-1);
		canvas_cor->Divide(4,2);	
		
		for(int ichan=0;ichan<4;ichan++){
			canvas_cor->Update();
			Char_t buf[100];
			sprintf(buf, "cor/DeltaT_%d_%d",ir, ichan);
			TH1D *Deltat = (TH1D*)gDirectory->Get(buf);
			canvas_cor->cd(ichan+1)->SetLogy();
			cout<<buf<<endl;
			Deltat->GetXaxis()->SetTitle("t [ps]");
			Deltat->Draw();
			
			sprintf(buf, "cor/f1_%d_%d", ir, ichan);
			TF1 *f1 = (TF1*)gDirectory->Get(buf);
			TF1 *f2 = new TF1("f2", "gaus", -1000, 1000);
			double para[3];
			f1->GetParameters(&para[0]);
			f2->SetParameters(&para[0]);
			f2->SetLineStyle(2);
			f2->Draw("same");

			sprintf(buf, "cor/Channel_%d_%d",ir, ichan);
			TH1D *Channel = (TH1D*)gDirectory->Get(buf);
			canvas_cor->cd(ichan+5);
			if(ichan<2) Channel->GetXaxis()->SetTitle("Amp [mV]");
				else	Channel->GetXaxis()->SetTitle("Rise time [ps]");
			Channel->GetYaxis()->SetTitle("t [ps]");
			Channel->Draw("colz");
			if(ProfileMode == 0) sprintf(buf, "cor/Channel_%d_%d_pfx",ir, ichan);
			else sprintf(buf, "cor/Channel_%d_%d_1",ir, ichan);
			TH1D *htsf = (TH1D*)gDirectory->Get(buf);
			htsf->SetMarkerStyle(4);
			htsf->Draw("same");
		}   
		
		f->cd("plots");
//		canvas_cor->Write();
	}
//	f->Close();
}
