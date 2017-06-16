 // ---------------------------------------------------------\\
 //                                                          \\
 //                 read_binary_CAEN.cc                      \\
 //                                                          \\
 // Written by: Mohammad Hattawy (mohammad.hattawy@gmail.com)\\
 // Date      : May 18th, 2017                               \\
 //                                                          \\
 // Function: reads float values from CAEN binary file       \\
 //           and write them in txt format                   \\
 // requirments: root and gcc                                \\
 // compile:root -b -q "read_binary_CAEN.cc(\"data_dir\")"   \\
 //----------------------------------------------------------\\

 
 #include <iostream> 
 #include <iomanip> 
 #include <fstream>
 #include <string> 
 #include <map>
 #include <sys/stat.h>
 #include <dirent.h>

 using namespace std; 
 struct stat sb;

 // reading the data directory---------------------------------------------
 std::vector<std::string> get_files_in_directory(std::string path = "data/.") {
 std::vector<std::string> files;
 if (stat(path.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode)) {
   DIR*    dir;
   dirent* pdir;
   dir = opendir(path.c_str());
   while( pdir = readdir(dir) ){
       string rfile=path + "/" + pdir->d_name;
       if (rfile.find(".dat") != std::string::npos)
            files.push_back(rfile);
   }
   } else {
       cout << "Directory " << path << " does not exist!!" << endl;
       std::exit(0);
       }
   return files;
 }


 // the main reading and writing scripts --------------------------------- 
 void read_binary_CAEN(const char* DIRNAME = "data") 
 {

     auto files        = get_files_in_directory(DIRNAME);
     for(auto aFile : files) cout<<"hi   "<<aFile<<endl;

     const int Nev = 2000; 

     ifstream infile_left; 
     char *inname = "/home/mhattawy/work/mcp-PMTs/scripts_Moh/data/CAENData1021/wave_2.dat"; 
     unsigned i; 
     float x; 
     unsigned char *cXpoint = (unsigned char *)&x; 

     infile_left.open(inname, ios::binary); 
     if (!infile_left) { 
         cout << "There was a problem opening file " << inname 
              << " for reading." << endl; 
     } 

     for( int j=0; j<Nev; j++){
        for(int k=0; k<1024; k++){ 
           infile_left.read((char *)&x, sizeof(float)); 
           if (!infile_left) { 
               cout << "There was a problem reading " << sizeof(float) 
                    << " bytes from " << inname << endl; 
           }
           // print the following if you want to see the bytes ------------- 
           // cout << "Successfully read a float" << inname <<endl << endl; 
           // cout << "The bytes of x in memory : "; 
           // for (i = 0; i < sizeof(float); i++) { 
           //    cout << "0x" 
           //         << hex << setfill('0') << setw(2) << (int)cXpoint[i] << " "; 
           // }

           // print the floats -----------------------------------------------
           cout << "float for bin (i = " <<k<<") = "<< fixed <<setprecision(6)<< x << endl; 
           //cout << "float for bin (i = " <<k<<") = "<< x << endl; 

        }
     }

  }
