// // writefloat.cpp 
// 
// A program to write a float to a file 
// 
// Note that the order of the bytes stored in memory 
// is architecture dependent. Intel/AMD x86 processors 
// are little-endian. PowerPC processors are big-endian. 
// 
#include <iostream> 
#include <iomanip> 
#include <fstream> 
using namespace std; 
void write_binary() 
{ 
  ofstream outfile; 
  char *outname = "f1.bin"; 
  unsigned i; 
  float x; 
   
  /* make a pointer whose address is the address of x, but * will 
   use the pointer to read the bytes, one at a time * for 
  debug purposes */ 
  unsigned char *cXpoint = (unsigned char *)&x; 
  x = 1234.171875; /* note that this is exactly representable internally */ 
  cout << "x = " << fixed << setprecision(6) << x << endl; 
  cout << "The bytes of x in memory : "; 

  for(i = 0; i < sizeof(float); i++) { 
      cout << "0x" 
           << hex << setfill('0') << setw(2) << (int)cXpoint[i] << " "; 
   } 
   cout << endl << endl; 
   outfile.open(outname, ios::binary); 
   if (!outfile) { 
       cout << "There was a problem opening file " << outname 
            << " for writing" << endl; 
   } 
   else { 
       cout << "Writing the bytes of x to file " << outname << endl; 
       outfile.write((char *)&x, sizeof(float)); 
       outfile.close(); 
    } 

 }
