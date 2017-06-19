 // ---------------------------------------------------------\\
 //                                                          \\
 //                 Bin2TxtConv_CAEN.cc                      \\
 //                                                          \\
 // Written by: Mohammad Hattawy (mohammad.hattawy@gmail.com)\\
 // Date      : May 18th, 2017                               \\
 //                                                          \\
 // Function: reads float values from CAEN binary file       \\
 //           and write them in txt format                   \\
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
     // input files ------------------------------------------------------
     const int Nevt = 2;   // number of events to be read from each file 
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
     unsigned char *cXpoint[Nch]; 

     for(int ii=0; ii<Nch; ii++) {
        cout<<inname[ii]<<endl;
        cXpoint[ii] = (unsigned char *)&XX[ii];
        infile[ii].open(inname[ii], ios::binary); 
        if (!infile[ii]) { 
              cout << "There was a problem opening file " << inname[ii] 
              << " for reading." << endl; 
        }
     } 

     // output txt file ------------------------------------------------
     const int runNumber = Find_runNumber(DIRNAME);
     ofstream outfile;
     outfile.open(Form("run%d.txt",runNumber));

     for( int jj=0; jj<Nevt; jj++){
        outfile<<"trig Evt "<<jj<<"         "<<"left Evt "<<jj<<"         "<<"right Evt "<<jj<<endl;  
        for(int mm=0; mm<1024; mm++){ 
           
           infile[0].read((char *)&XX[0], sizeof(float)); 
           infile[1].read((char *)&XX[1], sizeof(float)); 
           infile[2].read((char *)&XX[2], sizeof(float)); 
           
           // write after bin 23 -----------------------
           if( mm > 23 )
           outfile<<fixed <<setprecision(6)<<XX[0]<<"        "<<XX[1]<<"        "<<XX[2]<<endl;  

           // print the floats --------------------------
           // cout<< fixed <<setprecision(6)<< XX[0] <<"    "<<XX[1]<<"    "<<XX[2]<<endl; 

        }
     } // end the loop on Nevt

     // closing the inut and the output data files --------------------
     for(int ii=0; ii<Nch; ii++) infile[ii].close();
     outfile.close();

 }  // endl the main function 
