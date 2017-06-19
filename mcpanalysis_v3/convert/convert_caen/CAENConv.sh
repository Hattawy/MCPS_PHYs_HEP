#!/bin/bash

indir=$1
filename=$2


echo "Converting CAEN binary data files "
echo "----> Files Tr_0_0.dat, wave_0.dat, wave_2.dat >> ${filename}.txt"
echo "Start processing"
root -b -q "Bin2TxtConv_CAEN.cc("${indir}")"

echo "Conversion Completed!"

