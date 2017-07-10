# readbinaryV0.py
"""
script to read in binary data from CAEN waveform data, display raw data for
selected dataset and trigger files, make simple (threshold based) analysis
show plots and summary of results.
Basically a sanity check on the collected data 

                       Path to data file        nEvt  threshold(mV)
python readbinaryV0.py Data_withMcp/wave_4.dat  1000 -4

Ed May Mar 14, 2017
"""

import struct		# to unpack binary float data files
import numpy as np
import math
import pylab		# to plot graphs
import sys

#	( len(list2), np.max(list2), np.min(list2), np.mean(list2), np.std(list2) ) =
def     getStats( listname, list, alow, ahgh ) :
	# calculate means and standard deviations for list of data
        print '========================================================================================='
        newlist=[]
        listLength =  len(list)
	print 'getStats listname =', listname
        print 'range for statitics calculation: alow,ahgh = ', alow, ahgh
        for i in range(listLength) :
                if list[i] >= alow and list[i] < ahgh :
                        newlist.append( list[i] )
        print listname,' length, max, min, mean, std'
        print 'Raw:          ',len(list),    np.max(list), np.min(list), np.mean(list), np.std(list)
	if len(newlist) == 0 :
		return (0,0.0,0.0,0.0,0.0)
        print 'Selected:     ',len(newlist),np.max(newlist),np.min(newlist),np.mean(newlist),np.std(newlist)
        list2=[]	# make a new list selected on +/- nsigma about mean
	nsigma=2.0
        alowV2 = np.mean(newlist)-nsigma*np.std(newlist)
        ahghV2 = np.mean(newlist)+nsigma*np.std(newlist)
        for i in range(listLength) :
                if list[i] >= alowV2  and list[i] < ahghV2 :
                        list2.append( list[i] )
        print nsigma,'signma select', len(list2), np.max(list2), np.min(list2), np.mean(list2),np.std(list2)
        print 'where range is alowV2,ahghV2 = ', alowV2, ahghV2

        print '========================================================================================='
        return ( len(list2), np.max(list2), np.min(list2), np.mean(list2), np.std(list2) )

	
intv1=[30.,   60.]	# rough location of leading data group
intv2=[100., 130.]	# rough location of trailing data group

ledge=0.0; redge=200	# is full range of time(nsec)

# choose a binary data input file name
#filename='TR_0_0.dat'; threshold = -100.0; ledge=30.; redge=60.;
#filename='TR_0_0.dat'; threshold = -100.0; ledge=100.; redge=130.;
filenameTr='data/CAENData1021/TR_0_0.dat'; thresholdTr = -100.0;

#filename='TR_0_1.dat'; threshold = -100.0

#filename='wave_0.dat'; threshold = -10.0
#filename='wave_1.dat'; threshold = -10.0

#filename='wave_2.dat'; threshold = -1.0	# un used

filename='data/CAENData1021/wave_2.dat'; threshold = -3.0; ledge=30.0; redge=60
filename='data/CAENData1021/wave_2.dat'; threshold = -2.0; ledge=100.0; redge=130

#filename='wave_4.dat'; threshold = -1.0;	#unused

#filename='wave_5.dat'; threshold = -3.0; ledge=000.0; redge=60.
#filename='wave_5.dat'; threshold = -3.0; ledge=20.0; redge=30.
#filename='wave_5.dat'; threshold = -3.0; ledge=30.0; redge=60.
#filename='wave_5.dat'; threshold = -2.0; ledge=100.0; redge=130.

#ledge=0.0; redge=200	                       # is full range of time(nsec)
Nev= 1
if len(sys.argv) > 1 :
	filename=sys.argv[1]
	filenameTr='data/CAENData1021/TR_0_0.dat'; thresholdTr = -100.0;
	Nev=int(sys.argv[2])
	threshold=float(sys.argv[3])
	
f=open(filename,'r')
ftr=open(filenameTr,'r')	# trigger wave data

print 'Using filename = ', filename

wave=[]
waves=[]
print 'Reading ',Nev,'events'
for n in range(Nev) :
	wave=[]
	for i in range(1024) :
		obj = f.read(4)		# read 4 bytes binary to get float
		if len( obj ) > 0 :
			wave.append( struct.unpack('f',obj) )
	if len(obj) == 0 : break	# check for EOF
	waves.append(wave)
	if n%100 == 0 : print 'reached wave ',n,'of',filename
print 'length of waves is ', len(waves)
NevRead=len(waves)

waveTr=[]
wavesTr=[]
for n in range(Nev) :
	waveTr=[]
	for i in range(1024) :
		obj = ftr.read(4)	# read 4 bytes binary to get float
		if len( obj ) > 0 :
			waveTr.append( struct.unpack('f',obj) )
                        print ' floats = ', struct.unpack('f',obj)
	if len(obj) == 0 : break	# check for EOF
	wavesTr.append(waveTr)
	if n%100 == 0 : print 'reached wave ',n,'of',filenameTr
print 'length of wavesTr is ', len(wavesTr)


print '\nCalculate 128 leading timebins to estimate mean and std(noise)'
leadingAve=[]; leadingStd=[]
leadingTrAve=[]; leadingTrStd=[]
for n in range(len(waves)) :
	aWave = waves[n]
	leadingAve.append( np.mean( aWave[0:128] ) )
	leadingStd.append( np.std( aWave[0:128] ) )
	aWaveTr = wavesTr[n]
	leadingTrAve.append( np.mean( aWaveTr[0:128] ) )
	leadingTrStd.append( np.std( aWaveTr[0:128] ) )


waveMins=[]
waveMinIndexs=[]
print 'Length of waves is', len(waves)
print '# columns \n #evt  Index  aMin  aInd 0.2*aInd \n'
for i in range(len(waves)) :
	aMin = np.min(waves[i])
	aInd = np.argmin(waves[i])
	if i <= 10: print "%d %0.3f %d %0.1f" %(i, aMin,aInd, 0.2*aInd)
	waveMins.append(np.min(waves[i]))
	waveMinIndexs.append(np.argmin(waves[i]))
print '# columns \n #evt  Index  aMin  aInd  0.2*aInd \n'
	
print 'Length of Mins is', len(waveMins)
print
print 'Mins', waveMins[0:10]
print
print 'Minindexs', waveMinIndexs[0:10]
print

print '# evInd waveMins waveMinIndx 0.2*aInd leadingAve leadingStd'
for n in range(len(waves)) :
	if n <=10: print "%d %0.3f %d %0.1f %0.3f %0.3f" %( n, waveMins[n], waveMinIndexs[n], 0.2*aInd, 
	leadingAve[n], leadingStd[n])
print '# evInd waveMins waveMinIndx 0.2*aInd leadingAve leadingStd'
print


wavesWithOffset=[]
wavesTrWithOffset=[]
cnts2mv= 40.0/150.0
print '\nCalibration converstion to mV cnts2mv =', cnts2mv
print 'Apply correction/calibration to waveform data'
wavesWithOffMins=[]
wavesTrWithOffMins=[]
print 'Based on ',len(wavesTr),'events'
for n in range(len(waves)) : 
	wave=waves[n]
	waveWithOff=[]
	waveTr=wavesTr[n]
	waveTrWithOff=[]
	for i in range( len(wave) ) :
		waveWithOff.append ( (wave[i] - leadingAve[n])*cnts2mv )
	wavesWithOffset.append( waveWithOff )
	wavesWithOffMins.append( np.min( waveWithOff ) )
	for i in range( len(waveTr) ) :
		waveTrWithOff.append ( (waveTr[i] - leadingTrAve[n])*cnts2mv )
	wavesTrWithOffset.append( waveTrWithOff )
	wavesTrWithOffMins.append( np.min( waveTrWithOff ) )
	if n%100 == 0 : print 'Reached event ', n

meanOfMins = np.mean(wavesWithOffMins)
stdOfMins  = np.std(wavesWithOffMins)
print '\nmeanOfMins, stdOfMins = ',meanOfMins, stdOfMins
NPE = (meanOfMins/stdOfMins)**2
print 'est npe = ', (meanOfMins/stdOfMins)**2
leadingVAve=[]
leadingVStd=[]
for n in range(len(waves)) :
	aWave = wavesWithOffset[n]
	leadingVAve.append( np.mean( aWave[0:128] ) )
	leadingVStd.append( np.std( aWave[0:128] ) )
print "mean of leading means is ", np.mean(leadingVAve)
print "mean of leading stds  is ", np.mean(leadingVStd),'5 values=', leadingVStd[0:5]



# create a time array
times=[]
for i in range(1024) : times.append( i * 0.2 )

if False :
   print '# time(ns)  wave0(mV)  wave1(mV)  wave3(mV)'
   for i in range(1024) :
	print "%0.1f\t%0.2f\t%0.2f\t%0.2f " % (times[i],wavesWithOffset[0][i][0], 
	wavesWithOffset[1][i][0], wavesWithOffset[3][i][0] )
   print '# time(ns)  wave0(mV)  wave1(mV)  wave3(mV)'
print


timesAtThreshold=[]
print 'length of waves is ', len(waves)
nunderthres=0
noverthres=0
for n in range(len(waves)) :
	waveWithOffset=wavesWithOffset[n]
	aa = np.array(waveWithOffset)
	at = np.ma.masked_where(aa>threshold, aa)
	atindices = np.nonzero(at)
	if len(atindices[0]) == 0 :
		timesAtThreshold.append( -1.0  )
		nunderthres += 1
	else :
		timesAtThreshold.append( 0.2*atindices[0][0] )
		noverthres += 1

timesTrAtThreshold=[]
print 'length of wavesTr is ', len(wavesTr)
for n in range(len(wavesTr)) :
	waveTrWithOffset=wavesTrWithOffset[n]
	aa = np.array(waveTrWithOffset)
	at = np.ma.masked_where(aa>thresholdTr, aa)
	atindices = np.nonzero(at)
	if len(atindices[0]) == 0 :
		timesTrAtThreshold.append( -1.0  )
	else :
		timesTrAtThreshold.append( 0.2*atindices[0][0] )

print 'length of timesTrAtThreshold = ',len(timesTrAtThreshold)

print 'nunderthres, noverthres, sum = ', nunderthres, noverthres, nunderthres+noverthres
print "# index timeAtThreshold (when thres = %f )" % threshold
for i in range(len(timesAtThreshold)) :
	if i <= 10:print i, timesAtThreshold[i]
print "# index timeAtThreshold (when thres = %f )" % threshold

print 'Using filename = ', filename
print 'Nev = ', Nev


print 'nunderthres, noverthres, sum = ', nunderthres, noverthres, nunderthres+noverthres
print "# index timeAtThreshold (when thres = %f )" % threshold
for i in range(len(timesAtThreshold)) :
	if i <= 10:print i, timesAtThreshold[i]
print "# index timeAtThreshold (when thres = %f )" % threshold

print 'Using filename = ', filename
print 'Nev = ', Nev

print '\nCreating figure 10'
pylab.figure(10)
NumberWaves=1000
P=pylab.plot(times,wavesWithOffset[0], linewidth=1.0)            #plot waveform
P=P+pylab.plot(timesAtThreshold[0],threshold, marker='o')       #plot threshold
for i in range(NumberWaves) :
	P=P+pylab.plot(times,wavesWithOffset[i+1], linewidth=1.0)
	P=P+pylab.plot(timesAtThreshold[i+1],threshold, marker='o')
xl=pylab.xlabel('time (sec)')
yl=pylab.ylabel('calibrated to mV')
stitle="fig 10: "+filename+" first %d events"%NumberWaves
aTitle=pylab.title(stitle)
pylab.grid(True)
[xlow,xhgh,ylow,yhgh]=pylab.axis()
pylab.axis([0.0, 200.0, ylow, yhgh])
pylab.savefig(filename+"_raw_waveforms.png")
print '\nsaving figure 10 as',filename+"_raw_waveforms.png"
#pylab.show(P)

print '\nCreating figure 11'
pylab.figure(11)
P=pylab.plot(times,wavesTr[0], linewidth=1.0)                                #plot waveform
#P=P+pylab.plot(timesAtThreshold[0],threshold, marker='o') #plot threshold
for i in range(NumberWaves) :
	P=P+pylab.plot(times,wavesTr[i+1], linewidth=1.0)
	#P=P+pylab.plot(timesAtThreshold[i+1],threshold, marker='o')
xl=pylab.xlabel('time (sec)')
yl=pylab.ylabel('calibrated to mV')
stitle="fig 11: "+filename+" first %d trigger events"%NumberWaves
aTitle=pylab.title(stitle)
pylab.grid(True)
[xlow,xhgh,ylow,yhgh]=pylab.axis()
pylab.axis([0.0, 200.0, ylow, yhgh])
pylab.savefig(filename+"_raw_waveforms_trigger.png")
print '\nsaving figure 11 as',filename+"_raw_waveforms_trigger.png"
#pylab.show(P)


print '\nCreating figure 1'
pylab.figure(1)
NumbWaves=NevRead-1
#NumbWaves=10
#NumbWaves=20
mcpTimeMtrig=[]
newTimes=[]
print '\nlengths of times timesTrAtThreshold = ', len(times), len(timesTrAtThreshold)
timeOffset = 120.0
timeOffset = 105.0
for i in range(len(times)) :
	newTimes.append( times[i] - timesTrAtThreshold[0] + timeOffset )
P=pylab.plot(newTimes,wavesWithOffset[0], linewidth=1.0)				#plot waveform
P=P+pylab.plot(timesAtThreshold[0]-timesTrAtThreshold[0] + timeOffset,threshold, marker='o') #plot thresh pt

print 'first wave :',timesAtThreshold[0]-timesTrAtThreshold[0] + timeOffset
mcpTimeMtrig.append(timesAtThreshold[0]-timesTrAtThreshold[0] + timeOffset)

#P=pylab.plot(newTimes,wavesTrWithOffset[0], linewidth=1.0)
#P=P+pylab.plot(timesTrAtThreshold[0],thresholdTr, marker='o')
for i in range(NumbWaves) :
	newTimes=[]
	for j in range(len(times)) :
		newTimes.append( times[j] - timesTrAtThreshold[i+1] + timeOffset )
	P=P+pylab.plot(newTimes,wavesWithOffset[i+1], linewidth=1.0)
	P=P+pylab.plot(timesAtThreshold[i+1]-timesTrAtThreshold[i+1] + timeOffset,threshold, marker='o')
	if i<10:print 'next wave :',i,timesAtThreshold[i+1]-timesTrAtThreshold[i+1] + timeOffset
	mcpTimeMtrig.append(timesAtThreshold[i+1]-timesTrAtThreshold[i+1] + timeOffset)

xl=pylab.xlabel('time (sec)')
yl=pylab.ylabel('calibrated to mV')
stitle="fig 1: "+filename+" aligned by trigger at threshold"
aTitle=pylab.title(stitle)
pylab.grid(True)
[xlow,xhgh,ylow,yhgh]=pylab.axis()
pylab.axis([ledge, redge, ylow, yhgh])

pylab.savefig(filename+"_waveforms.png")
print '\nsaving figure 1 as',filename+"_waveforms.png"
#pylab.show(P)

print
print 'Creating figure 2'
nbins=500
pylab.figure(2)   # 
npts=len(mcpTimeMtrig)
mean=np.mean(mcpTimeMtrig)
std =np.std (mcpTimeMtrig) 
print 'mcpTimeMtrig: npts,mean,std = ', npts, mean, std
pylab.hist(mcpTimeMtrig,bins=nbins,facecolor='red',alpha=0.75, label='mcp-trig')
pylab.title("fig 2: "+filename+" time diff at  Threshold = %0.2f"%threshold)
pylab.xlabel("time (nsec)")
pylab.ylabel("counts/bin")
pylab.legend()
pylab.grid(True)
[xlow,xhgh,ylow,yhgh]=pylab.axis()
[xlow,xhgh,ylow,yhgh]=pylab.axis([100., 140., ylow, yhgh])
xoff = xlow + abs(xhgh-xlow)*0.05 
yoff = yhgh - abs(yhgh-ylow)*0.15 
#       ( len(list2), np.max(list2), np.min(list2), np.mean(list2), np.std(list2) ) =
#def     getStats( listname, list, alow, ahgh ) 
(npts, amax, amin, mean, std) = getStats('mcpTimeMtrig', mcpTimeMtrig, 100.0, 140.0)
s_npts=npts; s_mean=mean; s_std=std	# collect best estimates for summary
pylab.text(xoff,yoff,"cnt=%d mean=%0.1f std=%0.3f npe=%0.1f"%(npts,mean,std,NPE), fontsize=15)
pylab.savefig(filename+"_timeDiffsAtThreshold.png")
print '\nsaving figure 2 as',filename+"_timeDiffsAtThreshold.png"
#pylab.show()


print '\nCreating figure 3'
nbins=100
pylab.figure(3)   # 
npts=len(timesAtThreshold)
mean=np.mean(timesAtThreshold)
std =np.std (timesAtThreshold) 
pylab.hist(timesAtThreshold,bins=nbins,facecolor='red',alpha=0.75, label='timesAtThreshold')
#pylab.hist(W_1mW_0itimediff, bins=nbins, facecolor='yellow', alpha=0.75, label='W1mW0 interp')
pylab.title("fig 3: "+filename+" Time At Threshold = %0.2f"%threshold)
pylab.xlabel("time (nsec)")
pylab.ylabel("counts/bin")
pylab.legend()
[xlow,xhgh,ylow,yhgh]=pylab.axis()
xoff = xlow + abs(xhgh-xlow)*0.05 
yoff = yhgh - abs(yhgh-ylow)*0.15 
pylab.text(xoff,yoff,"cnt=%d mean=%0.1f std=%0.3f npe=%0.1f"%(npts,mean,std,NPE), fontsize=15)
pylab.savefig(filename+"_timesAtThreshold.png")
print '\nsaving figure 3 as', filename+"_timesAtThreshold.png"
#pylab.show()

print '\nCreating figure 4'
nbins=50
pylab.figure(4)   #
npts=len(wavesWithOffMins)
mean=np.mean(wavesWithOffMins)
std =np.std (wavesWithOffMins) 
estNPE= (mean/std)**2
pylab.hist(wavesWithOffMins,bins=nbins,facecolor='red',alpha=0.75, label='wave pulse maximums')
pylab.title("fig 4: "+filename+"_Pulse height")
pylab.xlabel("Voltage (mV)")
pylab.ylabel("counts/bin")
pylab.legend()
[xlow,xhgh,ylow,yhgh]=pylab.axis()
xoff = xlow + abs(xhgh-xlow)*0.05 
yoff = yhgh - abs(yhgh-ylow)*0.15 
pylab.text(xoff,yoff,"cnt=%d mean=%0.1f std=%0.1f npe=%0.1f"%(npts,mean,std,estNPE), fontsize=15)
pylab.savefig(filename+"_PulseHeightAtThreshold.png")
print '\nsaving figure 4 as', filename+"_PulseHeight.png"
#pylab.show()

print
print 'Summary Results'
print '# filename Nev noiseMean noiseRMS meanOfMins stdOfMins NPE threshold timeMean timeStd'
print "%s %d %0.4f %0.4f " % (filename, NevRead, np.mean(leadingVAve), np.mean(leadingVStd)), 
print "%0.4f %0.4f %0.2f " % (meanOfMins, stdOfMins, NPE ),
print "%0.1f %d %0.1f %0.3f " % (threshold, s_npts, s_mean, s_std) 

pylab.show()

f.close()
