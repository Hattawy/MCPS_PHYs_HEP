/*************************************************************************
    > File Name: load_all.C
    > Author: Jingbo Wang
    > mail: wjingbo@anl.gov 
    > Created Time: Fri Dec 18 15:46:50 2015
 ************************************************************************/

void load_all() {
    gROOT->LoadMacro("fitres.C");
    gROOT->LoadMacro("draw_signal.C");
    gROOT->LoadMacro("draw_gain.C");
    gROOT->LoadMacro("draw_frequency.C");
    gROOT->LoadMacro("draw_timing.C");

}

