/*************************************************************************
    > File Name: Graph1.C
    > Author: Jingbo Wang
    > mail: wjingbo@anl.gov 
    > Created Time: Wed Jun 24 23:39:38 2015
 ************************************************************************/
#include <vector>
#include "TGraph.h"
vector<float> vx, vy;
double num[10];
void Graph1(char* finput)
{
	TCanvas *c1 = new TCanvas("c1", "c1", 20,20,600,500);
	c1->SetGridx();
	c1->SetGridy();
	c1->SetBottomMargin(0.15);
	c1->SetLeftMargin(0.15);
	ifstream *isin = new ifstream();
	isin->open(finput, ios::in);					//open input .txt files	
	while(*isin>>num[0]>>num[1])
	{
		vx.push_back(num[0]);
		vy.push_back(num[1]);
		cout<<vx.at(vx.size()-1)<<"\t"<<vy.at(vx.size()-1)<<endl;
	}
	TGraphErrors *gr = new TGraphErrors(vx.size(), &(vx[0]), &(vy[0]));
	gr->SetTitle("");
	gr->Draw("alp");
	gr->SetMarkerStyle(21);
	gr->GetXaxis()->SetTitle("X Title");
	gr->GetXaxis()->SetTitleSize(0.05);
   	gr->GetXaxis()->SetLabelSize(0.04);
   	gr->GetXaxis()->SetTitleOffset(1.2);
	gr->GetYaxis()->SetTitle("Y Title");
	gr->GetYaxis()->SetTitleSize(0.05);
   	gr->GetYaxis()->SetLabelSize(0.04);
   	gr->GetYaxis()->SetTitleOffset(1.2);
	TLegend *leg = new TLegend(0.5, 0.7, 0.8, 0.8);
	leg->SetFillColor(10);
	leg->SetBorderSize(1);
	leg->SetTextFont(42);
	leg->SetTextSize(0.04);
	leg->AddEntry(gr,"SetEntryLable","pl");
	leg->Draw();
}
