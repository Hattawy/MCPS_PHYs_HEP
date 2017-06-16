#!/bin/bash

indir=$1
filename=$2

echo "Converting data files >> ${filename}.txt"
echo "This may take a few minutes"
BinToASCII ${indir}*1.bin ${indir}${filename}_1.txt > log
echo "Channel 1 finshed..."
BinToASCII ${indir}*2.bin ${indir}${filename}_2.txt > log
echo "Channel 2 finshed..."
BinToASCII ${indir}*3.bin ${indir}${filename}_3.txt > log
echo "Channel 3 finshed..."
#BinToASCII ${indir}wave_6.bin ${indir}${filename}_4.txt > log
#echo "Channel 4 finshed..."
echo "Combining 3 channels..."
paste ${indir}${filename}_*.txt > ${indir}${filename}.txt
echo "Cleaning..."
rm ${indir}${filename}_*.txt
rm log
echo "Conversion Completed!"

