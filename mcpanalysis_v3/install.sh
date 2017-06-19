#########################################################################
# File Name: install.sh
# Author: Jingbo Wang
# mail: wjingbo@anl.gov
# Created Time: Thu 19 May 2016 10:01:19 AM CDT
#########################################################################
#!/bin/bash
cd convert/convert_agilent/
make
cp BinToASCII $ROOTDEV/bin
chmod +x AgilentConv.sh
cp AgilentConv.sh $ROOTDEV/bin
cd ../../analysis/
make
make install
cd ../
echo "Installation done!"
