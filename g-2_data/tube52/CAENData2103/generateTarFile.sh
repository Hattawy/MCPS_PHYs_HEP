#!/bin/bash

echo $1



if [ "$1" == "" ]; then
	echo "Usage: $0 <run number>"
	exit
fi

RUN=$1

#tar -czf CAENData$RUN.tar.gz TR*.dat wave_[0135].dat runDescription.txt WaveDumpConfig.txt *.sh

tar -czf CAENData$RUN.tar.gz TR*.dat wave_[0246].dat run${RUN}Description.txt WaveDumpConfig.txt *.sh

#tar -czf CAENData$RUN.tar.gz TR*.dat wave_*.dat runDescription.txt runsCAEN.txt WaveDumpConfig.txt *.sh

tar -vtzf CAENData$RUN.tar.gz


