 // ---------------------------------------------------------\\
 //                                                          \\
 //                 Bin2TxtConv_CAEN.cc                      \\
 //                                                          \\
 // Written by: Mohammad Hattawy (mohammad.hattawy@gmail.com)\\
 // Date      : July 3rd, 2017                               \\
 //                                                          \\
 // Function: - reads CAEN binary files                      \\
 //           - applies the offset to the waveforms          \\
 //           - applies ADCTomV calibrations                 \\
 //           - and write them in txt format                 \\
 // requirments: root and gcc                                \\
 // compile:root -b -q "Bin2TxtConv_CAEN.cc(\"data_dir\")"   \\
 //----------------------------------------------------------\\

 
 #include <iostream> 
 #include <iomanip> 
 #include <fstream>
 #include <string> 

 using namespace std;

 // function to find the run number from the data directory--------------
 int Find_runNumber(const char* DIRNAME)
 {
    int RunNumber= 0;
    int fullNameLength = strlen(DIRNAME);
    string StringRunNumber;
    int  FNP = fullNameLength - 4;   // first number position
 
    for (int ii = FNP; ii<FNP+4; ii++)  StringRunNumber += DIRNAME[ii];
 
    std::istringstream iss(StringRunNumber);
    iss >> RunNumber;
   return RunNumber;
  } 

 // the main reading and writing scripts --------------------------------- 
 void Bin2TxtConv_CAEN(const char* DIRNAME = "data") 
 {
     // Calibration converstion to mV --------------------- 
     const float cnts2mv= (40.0/150.0) /1000.00; // lappd mutiply by 1000.00, we divide by it to set it to one 

     // input files ----------------------------------------
     const int Nevt = 5000;   // number of events to be read from each file 
     const int Nch = 3;      // number of channels to be read

     // trigger of the MCP is [0] --------------------------
     // left side of the MCP is [1] ------------------------
     // right side of the MCP is [2] -----------------------

     ifstream infile[Nch]; 
     char *inname[Nch]; 
     inname[0] = Form("%s/TR_0_0.dat",DIRNAME); 
     inname[1] = Form("%s/wave_0.dat",DIRNAME); 
     inname[2] = Form("%s/wave_2.dat",DIRNAME); 
     float XX[Nch]; 

     for(int ii=0; ii<Nch; ii++) {
        cout<<inname[ii]<<endl;
        infile[ii].open(inname[ii], ios::binary); 
        if (!infile[ii]) { 
              cout << "There was a problem reading file " << inname[ii]<< endl;
        }
     } 


     // output txt file ------------------------------------------------
     const int runNumber = Find_runNumber(DIRNAME);
     ofstream outfile;
     outfile.open(Form("run%d.txt",runNumber));



     // loop over the events from the three input files ---------------
     for( int jj=0; jj<Nevt; jj++){
 
        // write the title of the event in the output file ------------
        outfile<<"trig Evt "<<jj<<"      "<<"left Evt "<<jj<<"      "<<"right Evt "<<jj<<endl;  
        
        // define the arrays to save individual data bins
        const int n_bins = 1024;
        vector<float> bins_TR_0(n_bins);
        vector<float> bins_Wave_0(n_bins);
        vector<float> bins_Wave_2(n_bins);
               
        for(int kk=0; kk<n_bins; kk++){

           infile[0].read((char *)&XX[0], sizeof(float)); 
           infile[1].read((char *)&XX[1], sizeof(float)); 
           infile[2].read((char *)&XX[2], sizeof(float)); 
           
           bins_TR_0[kk]   = XX[0]; 
           bins_Wave_0[kk] = XX[1];
           bins_Wave_2[kk] = XX[2];
           
           //if(jj%1000 == 0 ) cout<<" Event # "<< jj<<"  bin "<<kk<<"    "
           //                 << bins_TR_0[kk]<<"     "<<fixed <<setprecision(6)<<XX[0]<<endl;
        }

        // find the offset from the first 128 timebins in each channel --------

        const int noise_bins = 128;

        float sum_offset_TR_0   = 0.0;
        float sum_offset_Wave_0 = 0.0;
        float sum_offset_Wave_2 = 0.0; 

        float mean_offset_TR_0   = 0.0;
        float mean_offset_Wave_0 = 0.0;
        float mean_offset_Wave_2 = 0.0;
 
        for(int kk=0; kk<noise_bins; kk++){
           
           sum_offset_TR_0   += bins_TR_0[kk];
           sum_offset_Wave_0 += bins_Wave_0[kk];
           sum_offset_Wave_2 += bins_Wave_2[kk];
        }
        mean_offset_TR_0   = sum_offset_TR_0  /128.0;
        mean_offset_Wave_0 = sum_offset_Wave_0/128.0;
        mean_offset_Wave_2 = sum_offset_Wave_2/128.0;
   


        // Apply correction/calibration to waveform data and -------
        // write after bin 23 -----------------------

        for(int mm=0; mm<n_bins; mm++){
           
           bins_TR_0[mm]   = (bins_TR_0[mm]   - mean_offset_TR_0)*cnts2mv;
           bins_Wave_0[mm] = (bins_Wave_0[mm] - mean_offset_Wave_0)*cnts2mv;
           bins_Wave_2[mm] = (bins_Wave_2[mm] - mean_offset_Wave_2)*cnts2mv;

           if( mm > 23 )
           outfile<<bins_TR_0[mm]<<"        "<<bins_Wave_0[mm]<<"        "<<bins_Wave_2[mm]<<endl;  

        }

     } // end the loop on Nevt



     // closing the inut and the output data files --------------------
     for(int ii=0; ii<Nch; ii++) infile[ii].close();
     outfile.close();

 }  // endl the main function 
