# wave_0.dat
# readbinaryV2.py
# appends to "summary.txt"

import struct
import numpy as np
import myfilter
dbg=0

def     getStats( listname, list, alow, ahgh ) :
	print '========================================================================================='
        newlist=[]
        listLength =  len(list)
	print 'alow,ahgh = ', alow, ahgh
        for i in range(listLength) :
                if list[i] >= alow and list[i] < ahgh :
                        newlist.append( list[i] )
	print listname,' length, max, min, mean, std'
        print 'Raw:      ',len(list),    np.max(list), np.min(list), np.mean(list), np.std(list)
        print 'Selected: ',len(newlist), np.max(newlist), np.min(newlist), np.mean(newlist), np.std(newlist)
	list2=[]
	alowV2 = np.mean(newlist)-1.0*np.std(newlist)
	ahghV2 = np.mean(newlist)+1.0*np.std(newlist)
	print 'alowV2,ahghV2 = ', alowV2, ahghV2
	for i in range(listLength) :
		if list[i] >= alowV2  and list[i] < ahghV2 :
			list2.append( list[i] )
	print '          ', len(list2), np.max(list2), np.min(list2), np.mean(list2), np.std(list2)
	print '========================================================================================='
        return ( len(list2), np.max(list2), np.min(list2), np.mean(list2), np.std(list2) )




def getInterpolationResults( times, waves, threshold, nbin2interp ) :
	#print 'in getInterpolationResults: len times = ',len(times)
	#print 'in getInterpolationResults: len waves = ',len(waves)
	#print 'in getInterpolationResults: threshold =  ', threshold

	timesAtThreshold=[]
	timeIndxsAtThreshold=[]
	#print "In getInterpolationResults: length of times =",len(times)
	for n in range(len(times)) :
		time=times[n]
		wave=waves[n]
		#print 'In getInterpolationResults: at n=',n,'length of time =', len(time)
		#ntime=np.linspace(time[0], time[-1], 200)
		if len(time) <= 0 : 
			#print 'len(time) is <=0'
			timesAtThreshold.append(0.0)
 			timeIndxsAtThreshold.append(0)
		if len(time) > 0 :
			ntime=np.linspace(time[0], time[-1], nbin2interp)
			nwave= np.interp(ntime,time,wave)
			aa = np.array(nwave)
			at = np.ma.masked_where(aa>threshold, aa)
			atindices = np.nonzero(at)
			if len(atindices[0]) == 0 :
				firstIndex=0
				firstIndex= len(ntime)-1
			else :
				firstIndex = atindices[0][0]
			timesAtThreshold.append(ntime[firstIndex])
			timeIndxsAtThreshold.append(firstIndex)
	#print 'In getInterpolationResults: length of timesAtThreshold, timeIndxsAtThreshold =',
	#print len(timesAtThreshold),len(timeIndxsAtThreshold)
	return ( timesAtThreshold )
	

def getResults(filename, threshold, Nev ) :
	f=open(filename)
	wave=[]
	waves=[]
	#inWave=[]; fwaves=[]
	for n in range(Nev) :
		wave=[]
		for i in range(1024) :
			obj = f.read(4)				# read 4 bytes binary to get float
			if len( obj ) > 0 :
				#wave.append( struct.unpack('f',obj) )
				wave.append( struct.unpack('f',obj)[0] )
		if len(obj) == 0 : break			# check for EOF
		#waves.append(wave)
		awave = np.array(wave)
		fwave=myfilter.savitzky_golay(awave, window_size=5, order=3)	# 3rd polynomial
		waves.append(fwave)
	if dbg>0:print 'length of waves is ', len(waves)
	if dbg>0:print 'waves[0] = ', waves[0]
	leadingAve=[]
	leadingStd=[]
	for n in range(len(waves)) :
		aWave = waves[n]
		leadingAve.append( np.mean( aWave[0:128] ) )
		leadingStd.append( np.std( aWave[0:128] ) )
	
	waveMins=[]
	waveMinIndexs=[]
	if dbg>0:print 'Length of waves is', len(waves)
	for i in range(len(waves)) :
		aMin = np.min(waves[i])
		aInd = np.argmin(waves[i])
		#print "%d %0.3f %d %0.1f" %(i, aMin,aInd, 0.2*aInd)
		waveMins.append(np.min(waves[i]))
		waveMinIndexs.append(np.argmin(waves[i]))
		
	#print 'Length of Mins is ', len(waveMins)
	#print 'Mins', waveMins
	#print 'Minindexs', waveMinIndexs
	
	#for n in range(len(waves)) :
	#	print "%d %0.3f %d %0.1f %0.3f %0.3f" %( n, waveMins[n], waveMinIndexs[n], 0.2*aInd, 
	#	leadingAve[n], leadingStd[n])
	
	wavesWithOffset=[]
	for n in range(len(waves)) : 
		wave=waves[n]
		waveWithOff=[]
		for i in range( len(wave) ) :
			waveWithOff.append ( wave[i] - leadingAve[n] )
		wavesWithOffset.append( waveWithOff )
	if dbg>0:print '\nwavesWithOffset[0] = ', wavesWithOffset[0]
	# create a time array
	times=[]
	for i in range(1024) : times.append( i * 0.2 )
	
	#for i in range(1024) :
	#  print times[i],wavesWithOffset[0][i][0], wavesWithOffset[1][i][0], wavesWithOffset[3][i][0]
	
	timesAtThreshold=[]
	timeIndxsAtThreshold=[]
	for n in range(len(waves)) :
		waveWithOffset=wavesWithOffset[n]
		aa = np.array(waveWithOffset)
		at = np.ma.masked_where(aa>threshold, aa)
		atindices = np.nonzero(at)
		if len(atindices[0]) == 0 :
			firstIndex=0
		else :  
			firstIndex = atindices[0][0]
		timesAtThreshold.append( 0.2*firstIndex )
		timeIndxsAtThreshold.append(firstIndex)
	#for i in range(len(timesAtThreshold)) :
	#	print i, timesAtThreshold[i]
	f.close()
	return (times, wavesWithOffset, leadingStd, timesAtThreshold, timeIndxsAtThreshold)
	
if __name__ == "__main__":
	import math
	import pylab
	import sys

	Nev=200
	Nev=1000
	n2i = 300	#number of bins to interpolate
	ibs = 15
	thresholds=[-200.0, -12.5, -12.5 ]
	thresholds=[-200.0, -100.0, -100.0 ]	# ok for TR_0, wave_0 and wave_1
	#thresholds=[-200.0, -10.0, -10.0 ]
	thresholds=[-200.0, -5.0, -5.0 ]	# for MCP runs
	thresholds=[-200.0, -5.5, -5.5 ]	# for MCP runs
	thresholds=[-200.0, -6.0, -6.0  ]	# for MCP runs
	thresholds=[-200.0, -7.0, -7.0 ]
	thresholds=[-200.0, -8.0, -8.0 ]
	print 'Using thresholds =', thresholds
	noiseEstRms=[0,0,0]
	runDescrip='Null'
	# if command line has arguements: get Run desription string and 3 thresholds in mV
	if len(sys.argv) >= 2 : runDescrip = sys.argv[1]
	if len(sys.argv) >  2 :
		thresholds[0] = float(sys.argv[2])
		thresholds[1] = float(sys.argv[3])
		thresholds[2] = float(sys.argv[4])

	filename='TR_0_0.dat'; threshold=thresholds[0]
	print 'Reading binary data from ', filename
	(times,TR_0wavesWithOffset,TR_0leadingStd,TR_0timesAtThreshold,TR_0Index)=getResults(
			filename, threshold, Nev )
	print 'length of times,TR_0wavesWithOffset=',len(times),len(TR_0wavesWithOffset)
	noiseEstRms[0]=np.mean(TR_0leadingStd)
	print 'TR_0leadingStd[0:10] = ',TR_0leadingStd[0:10]
	print 'noiseEstRms[0] = ', noiseEstRms[0]
	if dbg == 0 :
	   print 'lengs TR_0,TR_0[0],times',len(TR_0wavesWithOffset),
	   print len(TR_0wavesWithOffset[0]),len(times)
           print 'type times=',type(times), '1 element= ', times[0]
	   print 'type TR_0wavesWithOffset=',type(TR_0wavesWithOffset),
	   print '1 element=', TR_0wavesWithOffset[0][0]
	if dbg>0 :
	    for i in range(len(times)) :
		print i, times[i], TR_0wavesWithOffset[0][i], TR_0wavesWithOffset[1][i],
		print '...',TR_0wavesWithOffset[-1][i]

	print '\n get slice of wave arround threshold.'
	nTR_0times=[]; nTR_0wavesWithOffset=[]
	print '\nlen of TR_0Index = ', len(TR_0Index)
	for n in range(len(TR_0Index)) :
	   if dbg>0 : print 'n=', n, len(TR_0Index), TR_0Index[n],
	   if dbg>0 : print TR_0Index[n]-10, TR_0Index[n]+10
	   nTR_0times.append(  times[TR_0Index[n]-ibs : TR_0Index[n]+ibs] )
	   nTR_0wavesWithOffset.append(TR_0wavesWithOffset[n][TR_0Index[n]-ibs : TR_0Index[n]+ibs])
	print '\n1st length of nTR_0times is ', len(nTR_0times)
	print '\nTR_0Index[0:10] = ',TR_0Index[0:10]
	print '\nnTR_0wavesWithOffset[0:1] = ',nTR_0wavesWithOffset[0:1]


	# next data file wave_X
	#filename='wave_0.dat'; threshold=thresholds[1]		# calibration pulse
	filename='wave_3.dat'; threshold=thresholds[1]		# left mcp pulses
	print 'Reading binary data from ', filename
	(times,W_0wavesWithOffset,W_0leadingStd,W_0timesAtThreshold,W_0Index)=getResults(
			filename, threshold, Nev )
	noiseEstRms[1]=np.mean(W_0leadingStd)
	print 'noiseEstRms[1] = ', noiseEstRms[1]
	nW_0times=[]; nW_0wavesWithOffset=[]
	for n in range(len(W_0Index)) :
	   nW_0times.append(  times[W_0Index[n]-ibs : W_0Index[n]+ibs] )
	   nW_0wavesWithOffset.append(W_0wavesWithOffset[n][W_0Index[n]-ibs : W_0Index[n]+ibs])
	print 'W0 len of nW_0times is', len(nW_0times)
	print 'W0 len of nW_0wavesWithOffset is', len(nW_0wavesWithOffset)
	print '\n get slice of wave arround threshold.'
	nW_0times=[]; nW_0wavesWithOffset=[]
	for n in range(len(W_0Index)) :
	   nW_0times.append(  times[W_0Index[n]-ibs : W_0Index[n]+ibs] )
	   nW_0wavesWithOffset.append(W_0wavesWithOffset[n][W_0Index[n]-ibs : W_0Index[n]+ibs])

	# next data file wave_X
	#filename='wave_1.dat'; threshold=thresholds[2]		# calibration pulse
	filename='wave_5.dat'; threshold=thresholds[2]		# right mcp pulses
	print 'Reading binary data from ', filename
	(times,W_1wavesWithOffset,W_1leadingStd,W_1timesAtThreshold,W_1Index)=getResults(
			filename, threshold, Nev )
	noiseEstRms[2]=np.mean(W_1leadingStd)
	print 'noiseEstRms[2] = ', noiseEstRms[2]
	nW_1times=[]; nW_1wavesWithOffset=[]
	for n in range(len(W_1Index)) :
	   nW_1times.append(  times[W_1Index[n]-ibs : W_1Index[n]+ibs] )
	   nW_1wavesWithOffset.append(W_1wavesWithOffset[n][W_1Index[n]-ibs : W_1Index[n]+ibs])
	print '\n get slice of wave arround threshold.'
	nW_1times=[]; nW_1wavesWithOffset=[]
	for n in range(len(W_1Index)) :
	   nW_1times.append(  times[W_1Index[n]-ibs : W_1Index[n]+ibs] )
	   nW_1wavesWithOffset.append(W_1wavesWithOffset[n][W_1Index[n]-ibs : W_1Index[n]+ibs])

	print '\n2nd length of nTR_0times is ', len(nTR_0times)
	timesAtInterpThresTR_0=getInterpolationResults(nTR_0times, nTR_0wavesWithOffset, thresholds[0], n2i ) 
	print 'len of TR_0timesAtThreshold = ', len(TR_0timesAtThreshold)
	print 'len of timesAtInterpThresTR_0 = ', len(timesAtInterpThresTR_0)
	print 

	print 'i  TR_0timesAtThreshold[i] timesAtInterpThresTR_0[i] difference[i]'
	for i in range(len(nTR_0times)) :
	    if i < 10 :
		print i, TR_0timesAtThreshold[i], timesAtInterpThresTR_0[i],
		print TR_0timesAtThreshold[i]-timesAtInterpThresTR_0[i]

	timesAtInterpThresW_0=getInterpolationResults(nW_0times, nW_0wavesWithOffset, thresholds[1], n2i ) 
	timesAtInterpThresW_1=getInterpolationResults(nW_1times, nW_1wavesWithOffset, thresholds[2], n2i ) 

	W_0mTR_0itimediff=[];W_1mTR_0itimediff=[];W_1mW_0itimediff=[]
	print 'lengths of nTR_0times nW_0times nW_1times =',len(nTR_0times), len(nW_0times), len(nW_1times)
	for i in range(len(nTR_0times)) :
		#print 'at i=',i,'length of timesAtInterpThresW_0 is ',len(timesAtInterpThresW_0)
		#print 'at i=',i,'length of timesAtInterpThresTR_0 is ',len(timesAtInterpThresTR_0)
		W_0mTR_0itimediff.append( timesAtInterpThresW_0[i]-timesAtInterpThresTR_0[i])
	for i in range(len(nTR_0times)) :
		W_1mTR_0itimediff.append( timesAtInterpThresW_1[i]-timesAtInterpThresTR_0[i])
	for i in range(len(nW_0times)) :
		W_1mW_0itimediff.append( timesAtInterpThresW_1[i]-timesAtInterpThresW_0[i])
	print 'Results for interpolation on data:'
	print 'mean itimediff W_0 - TR_0 = ', np.mean(W_0mTR_0itimediff),
	print 'std itimediff W_0 - TR_0 = ', np.std(W_0mTR_0itimediff)
	print 'mean itimediff W_1 - TR_0 = ', np.mean(W_1mTR_0itimediff),
	print 'std itimediff W_1 - TR_0 = ', np.std(W_1mTR_0itimediff)
	print 'mean itimediff W_1 - W_0 = ', np.mean(W_1mW_0itimediff),
	print 'std itimediff W_1 - W_0 = ', np.std(W_1mW_0itimediff)

	import matplotlib.pyplot as plt
	W_0mTR_0itimediffwithOffset=[];W_1mTR_0itimediffwithOffset=[]
	timeOffsets=[np.mean(W_0mTR_0itimediff)-2.0, np.mean(W_1mTR_0itimediff)-1.0]
	for i in range(len(nTR_0times)) :
		W_0mTR_0itimediffwithOffset.append(W_0mTR_0itimediff[i] - timeOffsets[0])
		W_1mTR_0itimediffwithOffset.append(W_1mTR_0itimediff[i] - timeOffsets[1])
	nbins=500
	plt.figure(1)	# Time differences with smoothed and interpolated signal
	plt.hist(W_0mTR_0itimediffwithOffset,bins=nbins,facecolor='red',alpha=0.75, label='W0mTR0 interp')
	plt.hist(W_1mTR_0itimediffwithOffset,bins=nbins,facecolor='green',alpha=0.75, label='W1mTR0 interp')
	plt.hist(W_1mW_0itimediff, bins=nbins, facecolor='yellow', alpha=0.75, label='W1mW0 interp')
	[xlow,xhgh,ylow,yhgh]=pylab.axis()
	print 'bin width = ', (xhgh-xlow)/nbins
	xlow = -20.0; xhgh = 30.0
	pylab.axis([xlow, xhgh, ylow, yhgh])
	plt.title("Time Differences")
	plt.xlabel("time (nsec)")
	plt.ylabel("counts/bin")
	plt.legend()
	plt.title('Time differences after smoothing and interpolation')
	plt.savefig("ana_timeAtInterp.png")
	#plt.show()

	(len1, max1, min1, mean1, std1) = getStats('W_0mTR_0itimediffwithOffset', 
	W_0mTR_0itimediffwithOffset,  5.0, 35.0)
	(len2, max2, min2, mean2, std2) = getStats('W_1mTR_0itimediffwithOffset', 
	W_1mTR_0itimediffwithOffset,  5.0, 35.0)
	(len3, max3, min3, mean3, std3) = getStats('W_1mW_0itimediff',  W_1mW_0itimediff, -15.0, 0.0)

	#(len1, max1, min1, mean1, std1) = getStats('W_0mTR_0itimediffwithOffset', 
	#W_0mTR_0itimediffwithOffset,  0.0, 105.0)
	#(len2, max2, min2, mean2, std2) = getStats('W_1mTR_0itimediffwithOffset', 
	W_1mTR_0itimediffwithOffset,  0.0, 105.0)
	#(len3, max3, min3, mean3, std3) = getStats('W_1mW_0itimediff',  W_1mW_0itimediff, -15.0, 15.0)
	
	
	# select wave file to plot
	wavesWithOffset=TR_0wavesWithOffset
	timesAtThreshold=TR_0timesAtThreshold
	threshold=thresholds[0]; aTitle="TR_0"

	wavesWithOffset=W_0wavesWithOffset; 
	timesAtThreshold=W_0timesAtThreshold; 
	threshold=thresholds[1]; aTitle="W_0"

	#wavesWithOffset=W_1wavesWithOffset; 
	#timesAtThreshold=W_1timesAtThreshold; 
	#threshold=thresholds[2]; aTitle="W_1"
	
	if True :
	   pylab.figure(2)
	   P=pylab.plot(times,wavesWithOffset[0], linewidth=1.0)
	   P=P+pylab.plot(timesAtThreshold[0],threshold, marker='o')
	   for i in [1,2,3,4] :
	      P=P+pylab.plot(times,wavesWithOffset[i], linewidth=1.0)
	      P=P+pylab.plot(timesAtThreshold[i],threshold, marker='o')
	   xl=pylab.xlabel('time (sec)')
	   yl=pylab.ylabel('voltage (mv)')
	   [xlow,xhgh,ylow,yhgh]=pylab.axis()
	   xlow=130.0;xhgh=170.0
	   xlow=40.0;xhgh=140.0
	   pylab.axis([xlow, xhgh, ylow, yhgh])
	   aTitle=aTitle+" thres=%f mv"%threshold
	   aTitle=pylab.title(aTitle)
	   pylab.grid(True)
	   pylab.savefig("ana_timeAtThres.png")
	   #pylab.show(P)


	nwavesWithOffset=nTR_0wavesWithOffset; ntimes=nTR_0times; threshold=thresholds[0]; aTitle="TR_0"
	nwavesWithOffset=nW_0wavesWithOffset; ntimes=nW_0times; threshold=thresholds[1]; aTitle="W_0"
	ntimesAtThreshold=timesAtInterpThresW_0
	#nwavesWithOffset=nW_1wavesWithOffset; ntimes=nW_1times; threshold=thresholds[2]; aTitle="W_1"

	if dbg > 0 :
	   print '\nlengths of ', len(nwavesWithOffset), len(ntimes)
           print '\ntype ntimes=',type(ntimes), 'len =', len(ntimes),'1st elements = ', ntimes[0]
	   print '\ntype nwavesWithOffset=',type(nwavesWithOffset),'len=',
	   print len(nwavesWithOffset),'1st elements =', nwavesWithOffset[0]
	   print 'nTR_0wavesWithOffset = ', nTR_0wavesWithOffset
	   print '\n len of ntimes = ', len(ntimes)
	   print '\n len of nwavesWithOffset = ', len(nwavesWithOffset)
	   print '\n len of ntimes[0] = ', len(ntimes[0])
	   print '\n len of nwavesWithOffset[0] = ', len(nwavesWithOffset[0])
	   print '\n len of ntimes[1] = ', len(ntimes[1])
	   print '\n len of nwavesWithOffset[1] = ', len(nwavesWithOffset[1])

	if True  :
	   pylab.figure(3)	# plot interpolated signals
	   P=pylab.plot(ntimes[0],nwavesWithOffset[0], marker='x', linewidth=1.0)
	   P=P+pylab.plot(ntimesAtThreshold[0],threshold, marker='o')
	   P=P+pylab.plot(ntimes[1],nwavesWithOffset[1], marker='x', linewidth=1.0)
	   P=P+pylab.plot(ntimesAtThreshold[1],threshold, marker='o')
	   P=P+pylab.plot(ntimes[3],nwavesWithOffset[3], marker='x', linewidth=1.0)
	   P=P+pylab.plot(ntimesAtThreshold[3],threshold, marker='o')
	   xl=pylab.xlabel('time (sec)')
	   yl=pylab.ylabel('voltage (mv)')
	   aTitle=aTitle+"Interpolated signals at  thres=%f mv"%threshold
	   aTitle=pylab.title(aTitle)
	   pylab.grid(True)
	   pylab.savefig("ana_InterpolatedSignals.png")
	   #pylab.show(P)


	print "Lengths = ", len(TR_0timesAtThreshold), len(W_0timesAtThreshold), len(W_1timesAtThreshold)
	W0mTR0=[]; W1mTR0=[]; W1mW0=[]
	timeOffset0 = 40.0
	timeOffset1 = 41.0
	for i in range(len(TR_0timesAtThreshold)) :
		W0mTR0.append(W_0timesAtThreshold[i]-TR_0timesAtThreshold[i] - timeOffset0)
		W1mTR0.append(W_1timesAtThreshold[i]-TR_0timesAtThreshold[i] - timeOffset1)
		W1mW0.append(W_1timesAtThreshold[i]-W_0timesAtThreshold[i])
		#print i, W_0timesAtThreshold[i]-TR_0timesAtThreshold[i], 
		#print W_1timesAtThreshold[i]-TR_0timesAtThreshold[i],
		#print W_1timesAtThreshold[i]-W_0timesAtThreshold[i]

	import matplotlib.pyplot as plt
	# the histogram of the data
	print "Histogram the data."
	print 'W0mTR0 rms = ', np.std(W0mTR0),' mean = ', np.mean(W0mTR0)
	print 'W1mTR0 rms = ', np.std(W1mTR0),' mean = ', np.mean(W1mTR0)
	print 'W1mW0 rms = ', np.std(W1mW0),' mean = ', np.mean(W1mW0)
	plt.figure(4) # raw time differences
	mybins=[-2.0,-1.8,-1.6,-1.4,-1.2,-1.0,-0.8,-0.6,-0.4,-0.2,0.0,0.2,0.4,0.6,0.8,1.0]
	plt.hist(W0mTR0, mybins, facecolor='green', alpha=0.75, label='W0mTR0')
	plt.hist(W1mTR0, mybins, facecolor='yellow', alpha=0.75, label='W1mTR0')
	plt.hist(W1mW0, mybins, facecolor='red', alpha=0.75, label='W1mW0')
	plt.title("Time Differences")
	plt.xlabel("time (nsec)")
	plt.ylabel("counts/bin")
	plt.legend()
	plt.savefig("ana_rawtimedifferences.png")
	#plt.show()

	thresTR0=thresholds[2]
	thresW= thresholds[0]
	if False :
	   for n in range(len(W1mW0)) :
		if abs(W1mW0[n]) < 15 :
	   		#P=pylab.plot(times,TR_0wavesWithOffset[n], linewidth=1.0)
	   		P= pylab.plot(TR_0timesAtThreshold[n],thresTR0, marker='o')
	   		P=pylab.plot(times,W_0wavesWithOffset[n], linewidth=1.0)
	   		P=P+pylab.plot(W_0timesAtThreshold[n],thresW, marker='o')
	   		P=pylab.plot(times,W_1wavesWithOffset[n], linewidth=1.0)
	   		P=P+pylab.plot(W_1timesAtThreshold[n],thresW, marker='o')
	   		xl=pylab.xlabel('time (sec)')
	   		yl=pylab.ylabel('voltage (mv)')
	   		aTitle=pylab.title(filename)
	   		pylab.grid(True)
	   		#pylab.show(P)
			raw_input("Press Enter to continue...")

	#raw_input("Press Enter to continue...")
	print '# runDescrip,thres[0],thres[1],thres[2],noiseEstRms[0],noiseEstRms[1],noiseEstRms[2]',
        print ' np.std(W0mTR0),np.std(W1mTR0),np.std(W1mW0)',
	print ' np.std(W_0mTR_0itimediff), np.std(W_1mTR_0itimediff), np.std(W_1mW_0itimediff)'
	print runDescrip,thresholds[0],thresholds[1],thresholds[2],
	print "%0.2f %0.2f %0.2f" % (noiseEstRms[0],noiseEstRms[1],noiseEstRms[2]),
	print "%0.4f %0.4f %0.4f" % (np.std(W0mTR0),np.std(W1mTR0),np.std(W1mW0)),
	print "%0.4f %0.4f %0.4f" % (np.std(W_0mTR_0itimediff), 
	np.std(W_1mTR_0itimediff), np.std(W_1mW_0itimediff)) 
	print 'Using thresholds =', thresholds
	
	print 'Output as append to summary.txt'
	f=open("summary.txt", 'a')
	f.write("%s %0.1f %0.1f %0.1f " % (runDescrip,thresholds[0],thresholds[1],thresholds[2]) )
	f.write("%0.2f %0.2f %0.2f " % (noiseEstRms[0],noiseEstRms[1],noiseEstRms[2]))
	f.write("%0.4f %0.4f %0.4f " % (np.std(W0mTR0),np.std(W1mTR0),np.std(W1mW0)))
	f.write("%0.4f %0.4f %0.4f " % (np.std(W_0mTR_0itimediff), 
	np.std(W_1mTR_0itimediff), np.std(W_1mW_0itimediff)) )
	f.write("%0.4f %0.4f %0.4f " % (std1,std2,std3) )
	f.write("\n")
	f.close

	print "Done, so exit"
	sys.exit()
