#!/bin/bash

indir=$1
filename=$2
convertdir=$(pwd)

if [ -d ${indir}txt ]
then
echo "${indir}txt exits"
else
  mkdir -p ${indir}txt 
fi

outdir=${indir}txt

echo "Combining data files >> ${filename}.txt"
echo "This may take a few minutes"
cat ${indir}*board1.txt > ${outdir}/${filename}_board1.txt
cat ${indir}*board2.txt > ${outdir}/${filename}_board2.txt
paste ${outdir}/${filename}_board*.txt > ${outdir}/${filename}_root.txt
echo "Cleaning..."
#rm ${outdir}/*board*
echo "Copying to analysis directory"
cp ${outdir}/*_root* ${convertdir}
cd ${convertdir}
echo "Completed!"

