#########################################################################
# File Name: install.sh
# Author: Mohammad Hattawy
# mail: mohammad.hattawy@gmail.com
# Created Time: July 3rd, 2017
#########################################################################
#!/bin/bash
cd convert/convert_caen/
cp Bin2TxtConv_CAEN.cc $ROOTDEV/bin
cd ../../analysis
make clean
make
make install
cd ../
echo "Installation done!"
