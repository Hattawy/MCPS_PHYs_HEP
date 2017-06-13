#
# myUtilities.py
# contains:
#	getStats()
#	getInterpolationResults()
#	getResults()	#reads binary file
#	savitzky_golay()

import struct
import numpy as np
import sys
dbg=0

def getListOfFunctions() :
     # a list of functions contained in this file
     print ("""
     namestr(obj, namespace)
     printTypeOf(variable) 
     getStats( listname, list, alow, ahgh ) 
     getInterpolationResults( times, waves, threshold, nbin2interp ) 
     getResults(filename, threshold, Nev ) 
     savitzky_golay(y, window_size, order, deriv=0, rate=1)
     peakdet(v, delta, x = None)
     movingaverageStandard(values, window)
     movingaverage(values, window)
     runningMeanFast(x, N)
     shift(xs, n)
     getTimeAtThreshold( wave, threshold, deltaTime ) 
     getRiseTime( wave, times, indexTimeOfPeak ) 
     getConstantFractionTimes( wave, times, indexTimeOfPeak,deltaTime ) 
     h_fftfilter( x, y, factor=100 ) 
     """
     )

# ---------------------------------------------------------------------------------------
def namestr(obj, namespace):
    return [name for name in namespace if namespace[name] is obj]

def printTypeOf(variable) :
    print "Type of ", namestr(variable,globals()), "is", type(variable)

# ---------------------------------------------------------------------------------------
        #( len(list2), np.max(list2), np.min(list2), np.mean(list2), np.std(list2) ) =
def     getStats( listname, list, alow, ahgh ) :
	print '========================================================================='
        newlist=[]
        listLength =  len(list)
	print 'alow,ahgh = ', alow, ahgh
        for i in range(listLength) :
                if list[i] >= alow and list[i] < ahgh :
                        newlist.append( list[i] )
	print listname,' length, min, max, mean, std'
        print 'Raw:      ',len(list),    np.min(list), np.max(list), np.mean(list), np.std(list)
	if len(newlist) == 0 :
		return ( len(list), np.min(list), np.max(list), np.mean(list), np.std(list) )
        print 'Selected: ',len(newlist), np.min(newlist), np.max(newlist), np.mean(newlist), np.std(newlist)
	list2=[]
	alowV2 = np.mean(newlist)-1.0*np.std(newlist)
	ahghV2 = np.mean(newlist)+1.0*np.std(newlist)
	for i in range(listLength) :
		if list[i] >= alowV2  and list[i] < ahghV2 :
			list2.append( list[i] )
	if len(list2) == 0 :
		return ( len(list), np.min(list), np.max(list), np.mean(list), np.std(list) )	
	print 'alowV2,ahghV2 = ', alowV2, ahghV2
	print '          ', len(list2), np.min(list2), np.max(list2), np.mean(list2), np.std(list2)
	print '=========================================================================='
        return ( len(list2), np.min(list2), np.max(list2), np.mean(list2), np.std(list2) )

# ---------------------------------------------------------------------------------------
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
	
# ----------------------------------------------------------------------------------------
def getData( filename, Nev ) :
	cnts2mv= 40.0/150.0	# set calibration to convert raw adc data to mV
	f=open(filename)
	wave=[]
	waves=[]
	for n in range(Nev) :
		wave=[]
		for i in range(1024) :
		   obj = f.read(4)		# read 4 bytes binary to get float
		   if len( obj ) > 0 :
		      wave.append( struct.unpack('f',obj)[0] )
		if len(obj) == 0 : break			# check for EOF
		offset = np.mean( wave[0:128] )
		wave = [cnts2mv*(x-offset) for x in wave]
		waves.append(wave)
	f.close()
	return waves
# ----------------------------------------------------------------------------------------
	# get waveforms from a binary file
	#returns (times, wavesWithOffset, leadingStd, timesAtThreshold, timeIndxsAtThreshold)
def getResults(filename, threshold, Nev ) :
	f=open(filename)
	wave=[]
	waves=[]
	#inWave=[]; fwaves=[]
	for n in range(Nev) :
		wave=[]
		for i in range(1024) :
			obj = f.read(4)		# read 4 bytes binary to get float
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
	
# ---------------------------------------------------------------------------------------

# a filter/smoothing code
# see http://scipy.github.io/old-wiki/pages/Cookbook/SavitzkyGolay
#    returns:  np.convolve( m[::-1], y, mode='valid')
def savitzky_golay(y, window_size, order, deriv=0, rate=1):
    r"""Smooth (and optionally differentiate) data with a Savitzky-Golay filter.
    The Savitzky-Golay filter removes high frequency noise from data.
    It has the advantage of preserving the original shape and
    features of the signal better than other types of filtering
    approaches, such as moving averages techniques.
    Parameters
    ----------
    y : array_like, shape (N,)
        the values of the time history of the signal.
    window_size : int
        the length of the window. Must be an odd integer number.
    order : int
        the order of the polynomial used in the filtering.
        Must be less then `window_size` - 1.
    deriv: int
        the order of the derivative to compute (default = 0 means only smoothing)
    Returns
    -------
    ys : ndarray, shape (N)
        the smoothed signal (or it's n-th derivative).
    Notes
    -----
    The Savitzky-Golay is a type of low-pass filter, particularly
    suited for smoothing noisy data. The main idea behind this
    approach is to make for each point a least-square fit with a
    polynomial of high order over a odd-sized window centered at
    the point.
    Examples
    --------
    t = np.linspace(-4, 4, 500)
    y = np.exp( -t**2 ) + np.random.normal(0, 0.05, t.shape)
    ysg = savitzky_golay(y, window_size=31, order=4)
    import matplotlib.pyplot as plt
    plt.plot(t, y, label='Noisy signal')
    plt.plot(t, np.exp(-t**2), 'k', lw=1.5, label='Original signal')
    plt.plot(t, ysg, 'r', label='Filtered signal')
    plt.legend()
    plt.show()
    References
    ----------
    .. [1] A. Savitzky, M. J. E. Golay, Smoothing and Differentiation of
       Data by Simplified Least Squares Procedures. Analytical
       Chemistry, 1964, 36 (8), pp 1627-1639.
    .. [2] Numerical Recipes 3rd Edition: The Art of Scientific Computing
       W.H. Press, S.A. Teukolsky, W.T. Vetterling, B.P. Flannery
       Cambridge University Press ISBN-13: 9780521880688
    """
    import numpy as np
    from math import factorial
    
    try:
        window_size = np.abs(np.int(window_size))
        order = np.abs(np.int(order))
    except ValueError, msg:
        raise ValueError("window_size and order have to be of type int")
    if window_size % 2 != 1 or window_size < 1:
        raise TypeError("window_size size must be a positive odd number")
    if window_size < order + 2:
        raise TypeError("window_size is too small for the polynomials order")
    order_range = range(order+1)
    half_window = (window_size -1) // 2
    # precompute coefficients
    b = np.mat([[k**i for i in order_range] for k in range(-half_window, half_window+1)])
    m = np.linalg.pinv(b).A[deriv] * rate**deriv * factorial(deriv)
    # pad the signal at the extremes with
    # values taken from the signal itself
    firstvals = y[0] - np.abs( y[1:half_window+1][::-1] - y[0] )
    lastvals = y[-1] + np.abs(y[-half_window-1:-1][::-1] - y[-1])
    y = np.concatenate((firstvals, y, lastvals))
    return np.convolve( m[::-1], y, mode='valid')

# --------------------------------------------------------------------------------------------------------

from numpy import NaN, Inf, arange, isscalar, asarray, array

def peakdet(v, delta, x = None):
    """
    Converted from MATLAB script at http://billauer.co.il/peakdet.html
    
    Returns two arrays
    
    function [maxtab, mintab]=peakdet(v, delta, x)
    %PEAKDET Detect peaks in a vector
    %        [MAXTAB, MINTAB] = PEAKDET(V, DELTA) finds the local
    %        maxima and minima ("peaks") in the vector V.
    %        MAXTAB and MINTAB consists of two columns. Column 1
    %        contains indices in V, and column 2 the found values.
    %      
    %        With [MAXTAB, MINTAB] = PEAKDET(V, DELTA, X) the indices
    %        in MAXTAB and MINTAB are replaced with the corresponding
    %        X-values.
    %
    %        A point is considered a maximum peak if it has the maximal
    %        value, and was preceded (to the left) by a value lower by
    %        DELTA.
    
    % Eli Billauer, 3.4.05 (Explicitly not copyrighted).
    % This function is released to the public domain; Any use is allowed.
    
    """
    maxtab = []
    mintab = []
       
    if x is None:
        x = arange(len(v))
    
    v = asarray(v)
    
    if len(v) != len(x):
        sys.exit('Input vectors v and x must have same length')
    
    if not isscalar(delta):
        sys.exit('Input argument delta must be a scalar')
    
    if delta <= 0:
        sys.exit('Input argument delta must be positive')
    
    mn, mx = Inf, -Inf
    mnpos, mxpos = NaN, NaN
    
    lookformax = True
    
    for i in arange(len(v)):
        this = v[i]
        if this > mx:
            mx = this
            mxpos = x[i]
        if this < mn:
            mn = this
            mnpos = x[i]
        
        if lookformax:
            if this < mx-delta:
                maxtab.append((mxpos, mx))
                mn = this
                mnpos = x[i]
                lookformax = False
        else:
            if this > mn+delta:
                mintab.append((mnpos, mn))
                mx = this
                mxpos = x[i]
                lookformax = True

    return array(maxtab), array(mintab)

if __name__=="__test__":
    from matplotlib.pyplot import plot, scatter, show, grid
    series = [0,0,0,2,0,0,0,-2,0,0,0,2,0,0,0,-2,0]
    series = [0.0, 0.5, 1.0, 2.0, 1.5, 0.7, 0.0, 0.0, -2.0, 0.0, 0.0,
              0.0, 0.1, 0.2, 0.3, 0.0, 1.0, 4.0, 4.0,  2.0, 0.0, 1.0, 0.0, 0,0, -0.25, -2,0]
    for i in range(len(series)):
        print i,series[i]
    threshold = 0.3
    threshold = 0.99
    print 'threshold = ', threshold
    maxtab, mintab = peakdet(series,threshold)
    lenOfMaxtab = len(maxtab)
    lenOfMintab = len(mintab)
    print 'number of positive peaks = ',lenOfMaxtab,'maxtab = \n',maxtab
    print 'number of negative peaks = ',lenOfMintab,'mintab = \n',mintab
    plot(series)
    grid(True)
    scatter(array(maxtab)[:,0], array(maxtab)[:,1], color='green')
    scatter(array(mintab)[:,0], array(mintab)[:,1], color='red')
    show()

# --------------------------------------------------------------------------------------------------------
def movingaverageStandard(values, window):
    weights = np.repeat(1.0, window)/window
    sma = np.convolve(values, weights, 'valid')
    #print 'length of values,sma = ', len(values), len(sma)
    return sma

def movingaverage(values, window):
    if window > 7  : 
	print "Window is to big for movingaverage, exit!"
	sys.exit()
    weights = np.repeat(1.0, window)/window
    svalues = []
    svalues = np.append(svalues,0.0)
    if window >= 5 : svalues = np.append(svalues,0.0)
    if window >= 7 : svalues = np.append(svalues,0.0)
    svalues = np.append(svalues,values)
    if window >= 5 : svalues = np.append(svalues,0.0)
    if window >= 7 : svalues = np.append(svalues,0.0)
    svalues = np.append(svalues,0.0)
    #sma = np.convolve(values, weights, 'valid')
    sma = np.convolve(svalues, weights, 'valid')
    #print 'V2 length of values,sma = ', len(values), len(sma)
    #print 'V2 length of svalues,sma = ', len(svalues), len(sma)
    return sma

def runningMeanFast(x, N):
    return np.convolve(x, np.ones((N,))/N)[(N-1):]

def shift(xs, n):
    if n >= 0:
        return np.concatenate((np.full(n, np.nan), xs[:-n]))
    else:
        return np.concatenate((xs[-n:], np.full(-n, np.nan)))

def overThreshold( wave, threshold ) :
	thres = -threshold
	aa = -np.array( wave )
	at = np.ma.masked_where(aa<thres, aa)
	atindices = np.nonzero(at)
	if len(atindices[0]) == 0 :
		return False
	return True

# --------------------------------------------------------------------------------------------------------
def getTimeAtThreshold( wave, threshold, deltaTime ) :
	#print "Entered getTimeAtThreshold: with deltaTime=", deltaTime
	thres = -threshold
	#print "getTimeAtThreshold len(wave), threshold, thres=:", len(wave), threshold, thres
	aa = -np.array( wave )
	#print aa[ int(115./deltaTime) : int(120.0/deltaTime) ]
	at = np.ma.masked_where(aa<thres, aa)
	atindices = np.nonzero(at)
	#print 'atindices = ',atindices
	if len(atindices[0]) == 0 :
               firstIndex=0
        else :
               firstIndex = atindices[0][0]
	timeAtThreshold = deltaTime * firstIndex
	#print "Leaving getTimeAtThreshold"
	return (firstIndex, timeAtThreshold)

# --------------------------------------------------------------------------------------------------------
def getRiseTime( wave, times, indexTimeOfPeak ) :
	peakVoltage = wave[indexTimeOfPeak]
	thresholdAt10PC = 0.1*peakVoltage
	thresholdAt50PC = 0.5*peakVoltage
	thresholdAt90PC = 0.9*peakVoltage
	(indexAt10PC,timeAtThreshold10PC)=getTimeAtThreshold( wave, thresholdAt10PC, 0.200 ) 
	(indexAt10PC,timeAtThreshold50PC)=getTimeAtThreshold( wave, thresholdAt50PC, 0.200 ) 
	(indexAt10PC,timeAtThreshold90PC)=getTimeAtThreshold( wave, thresholdAt90PC, 0.200 ) 
	return (timeAtThreshold90PC - timeAtThreshold10PC, 2*(timeAtThreshold90PC - timeAtThreshold50PC) )
	
	
	
# --------------------------------------------------------------------------------------------------------
def getConstantFractionTimes( wave, times, indexTimeOfPeak,deltaTime ) :
	peakVoltage = wave[indexTimeOfPeak]
	thresholdAt20PC = 0.2*peakVoltage
	thresholdAt30PC = 0.3*peakVoltage
	thresholdAt40PC = 0.4*peakVoltage
	thresholdAt50PC = 0.5*peakVoltage
	(indexAt20PC,timeAtThreshold20PC)=getTimeAtThreshold( wave, thresholdAt20PC,deltaTime ) 
	(indexAt30PC,timeAtThreshold30PC)=getTimeAtThreshold( wave, thresholdAt30PC,deltaTime ) 
	(indexAt40PC,timeAtThreshold40PC)=getTimeAtThreshold( wave, thresholdAt40PC,deltaTime ) 
	(indexAt50PC,timeAtThreshold50PC)=getTimeAtThreshold( wave, thresholdAt50PC,deltaTime ) 
	return (timeAtThreshold20PC,timeAtThreshold30PC, timeAtThreshold40PC, timeAtThreshold50PC) 
# --------------------------------------------------------------------------------------------------------
import scipy.fftpack
import pylab
def h_fftfilter( x, y, factor=100 ) :
   global drawPlots
   N=len(x)
   w = scipy.fftpack.rfft(y)
   f = scipy.fftpack.rfftfreq(N, x[1]-x[0])
   spectrum = w**2
   cutoff_idx = spectrum < (spectrum.max()/factor)
   w2 = w.copy()
   w2[cutoff_idx] = 0
   y2 = scipy.fftpack.irfft(w2)
   if drawPlots :
      cutoff_line=[]
      for i in range(len(f) ): cutoff_line.append(spectrum.max()/factor)
      pylab.figure(101)
      pylab.semilogy(f,spectrum)
      pylab.semilogy(f,cutoff_line, linewidth=1.0)
      [xlow,xhgh,ylow,yhgh]=pylab.axis()
      pylab.axis([xlow, xhgh, 1e-9, 1])
      pylab.grid()
      stitle1='signal'
      pylab.title(stitle1)
      pylab.xlabel('frequency')
      pylab.draw()
      pylab.figure(103)
      pylab.plot(x,y, color='blue', label='wfm')
      pylab.plot(x,y2, marker='.',color='red', label='y2 inverse transform')
      pylab.title(stitle1+" Inverse fft with factor=%f"%factor)
      pylab.xlabel('time (sec)')
      pylab.ylabel('Voltage (volts)')
      pylab.legend()
      pylab.grid()
      pylab.draw()
      pylab.show()
   return(x,y2)
#
#(times,fwave)=fftfilter(x, y, factor=100, drawPlots=True)

import sys
from numpy import NaN, Inf, arange, isscalar, asarray, array

def peakdet(v, delta, x = None):
    """
    Converted from MATLAB script at http://billauer.co.il/peakdet.html
    
    Returns two arrays
    
    function [maxtab, mintab]=peakdet(v, delta, x)
    %PEAKDET Detect peaks in a vector
    %        [MAXTAB, MINTAB] = PEAKDET(V, DELTA) finds the local
    %        maxima and minima ("peaks") in the vector V.
    %        MAXTAB and MINTAB consists of two columns. Column 1
    %        contains indices in V, and column 2 the found values.
    %      
    %        With [MAXTAB, MINTAB] = PEAKDET(V, DELTA, X) the indices
    %        in MAXTAB and MINTAB are replaced with the corresponding
    %        X-values.
    %
    %        A point is considered a maximum peak if it has the maximal
    %        value, and was preceded (to the left) by a value lower by
    %        DELTA.
    
    % Eli Billauer, 3.4.05 (Explicitly not copyrighted).
    % This function is released to the public domain; Any use is allowed.
    
    """
    maxtab = []
    mintab = []
       
    if x is None:
        x = arange(len(v))
    
    v = asarray(v)
    
    if len(v) != len(x):
        sys.exit('Input vectors v and x must have same length')
    
    if not isscalar(delta):
        sys.exit('Input argument delta must be a scalar')
    
    if delta <= 0:
        sys.exit('Input argument delta must be positive')
    
    mn, mx = Inf, -Inf
    mnpos, mxpos = NaN, NaN
    
    lookformax = True
    
    for i in arange(len(v)):
        this = v[i]
        if this > mx:
            mx = this
            mxpos = x[i]
        if this < mn:
            mn = this
            mnpos = x[i]
        
        if lookformax:
            if this < mx-delta:
                maxtab.append((mxpos, mx))
                mn = this
                mnpos = x[i]
                lookformax = False
        else:
            if this > mn+delta:
                mintab.append((mnpos, mn))
                mx = this
                mxpos = x[i]
                lookformax = True

    return array(maxtab), array(mintab)

if __name__=="__main__":
    from matplotlib.pyplot import plot, scatter, show, grid
    series = [0,0,0,2,0,0,0,-2,0,0,0,2,0,0,0,-2,0]
    series = [0.0, 0.5, 1.0, 2.0, 1.5, 0.7, 0.0, 0.0, -2.0, 0.0, 0.0,
              0.0, 0.1, 0.2, 0.3, 0.0, 1.0, 4.0, 4.0,  2.0, 0.0, 1.0, 0.0, 0,0, -0.25, -2,0]
    for i in range(len(series)):
        print i,series[i]
    threshold = 0.3
    threshold = 0.99
    print 'threshold = ', threshold
    maxtab, mintab = peakdet(series,threshold)
    lenOfMaxtab = len(maxtab)
    lenOfMintab = len(mintab)
    print 'number of positive peaks = ',lenOfMaxtab,'maxtab = \n',maxtab
    print 'number of negative peaks = ',lenOfMintab,'mintab = \n',mintab
    plot(series)
    grid(True)
    scatter(array(maxtab)[:,0], array(maxtab)[:,1], color='green')
    scatter(array(mintab)[:,0], array(mintab)[:,1], color='red')
    show()



# --------------------------------------------------------------------------------------------------------
if __name__ == "__main__":
	print "In the file myUtilities.py ..."
	getListOfFunctions()
	exit()
