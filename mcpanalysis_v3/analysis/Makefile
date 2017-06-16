# =============================== 
# Makefile for UVevent 
# =============================== 
# #
#  make clean and make install of this makefile imply that you define the system variable
#ROOTDEV. Exactly as ROOTSYS is a pointer towards the directory containing the include
#files, the libraries and the shared libraries of ROOT, ROOTDEV points towards a directory intended
#to contain the include files, the libraries and the shared libraries of all developments made
#above ROOT, like SplineFit, or the programs you may have developed yourself.
#  $(ROOTDEV) must contain at least 3 subdirectories: bin, lib and include.
#  Only by this way will you be able to write modular code, allowing one of your module
#to call entries of an other of your modules or entries of SplineFit.
#  If you have write access to $(ROOTSYS), you can choose ROOTDEV=ROOTSYS, but this mixing
#of your code with the code of ROOT is to my mind inelegant and the choice of a separate
#ROOTDEV is surely better.
# $(ROOTDEV)/bin  has to be added to PATH
# $(ROOTDEV)/lib  has to be added to LD_LIBRARY_PAT
#

ObjSuf        = o
SrcSuf        = cxx
ExeSuf        = 
DllSuf        = so
OutPutOpt     = -o # keep whitespace after "-o"

ROOTCFLAGS    = $(shell root-config --cflags)
ROOTLIBS      = $(shell root-config --libs)
ROOTGLIBS     = $(shell root-config --glibs)

# Linux with egcs
CXX           = g++
CXXFLAGS      = -g -Wall -fPIC
LD            = g++
LDFLAGS       = -O
SOFLAGS       = -shared

LIBTSPLINEFIT   = libTSplineFit
PROGRAMLIB    = $(LIBTSPLINEFIT).lib
LIBUVHIT       = libUVevent
CXXFLAGS     += $(ROOTCFLAGS)
LIBS          = $(ROOTLIBS) $(SYSLIBS)
GLIBS         = $(ROOTGLIBS) $(SYSLIBS)

#------------------------------------------------------------------------------


HDRS          = TPoly3.h TOnePadDisplay.h TBandedLE.h TZigZag.h \
				TSplineFit.h Calibration.h UVevent.h  Analysis.h Parameter.h
SRCS          = TPoly3.$(SrcSuf) TOnePadDisplay.$(SrcSuf) TBandedLE.$(SrcSuf) \
				TZigZag.$(SrcSuf) TSplineFit.$(SrcSuf) Calibration.$(SrcSuf) \
				UVevent.$(SrcSuf) UVeventDict.$(SrcSuf) Analysis.$(SrcSuf) \
				Parameter.$(SrcSuf)
OBJS          = TPoly3.$(ObjSuf) TOnePadDisplay.$(ObjSuf) \
				TBandedLE.$(ObjSuf) TZigZag.$(ObjSuf) TSplineFit.$(ObjSuf) \
				Calibration.$(ObjSuf) UVevent.$(ObjSuf) UVeventDict.$(ObjSuf) \
				Analysis.$(ObjSuf) Parameter.$(ObjSuf)

TSPLINEFITSO = $(LIBTSPLINEFIT).$(DllSuf)
UVHITSO = $(LIBUVHIT).$(DllSuf)
PROGRAM = lappd$(ExeSuf)

all:        $(UVHITSO) $(PROGRAM)

$(TSPLINEFITSO): $(OBJS)
		@echo "Creating library $(TSPLINEFITSO) ..."
		$(LD) $(SOFLAGS) $(LDFLAGS) $(ROOTFLAGS) $(ROOTLIBS) $^ $(OutPutOpt) $@
		@echo "$(TSPLINEFITSO) done"
$(UVHITSO): $(OBJS)
		@echo "Creating library $(UVHITSO) ..."
		$(LD) $(SOFLAGS) $(LDFLAGS) $(ROOTFLAGS) $(ROOTLIBS) $^ $(OutPutOpt) $@
		@echo "$(UVHITSO) done"
$(PROGRAM): lappd.$(ObjSuf) $(OBJS)
		@echo "Linking $(PROGRAM) ..."
		$(LD) $(LDFLAGS) lappd.$(ObjSuf) $(OBJS) $(LIBS) $(OutPutOpt) $(PROGRAM)
		@echo "$(PROGRAM) done"

clean:
#		@rm -f $(OBJS) lappd.$(ObjSuf) *\~ core SplineFitDict*
		@rm -f $(OBJS) lappd.$(ObjSuf) *\~ core UVeventDict*
		@rm -f $(PROGRAM) $(PROGRAMSO)
		@rm -f $(ROOTDEV)/bin/$(PROGRAM)
		@rm -f $(ROOTDEV)/lib/$(LIBTSPLINEFIT).$(DllSuf)
		@rm -f $(ROOTDEV)/include/TPoly3.h
		@rm -f $(ROOTDEV)/include/TOnePadDisplay.h
		@rm -f $(ROOTDEV)/include/TBandedLE.h
		@rm -f $(ROOTDEV)/include/TZigZag.h
		@rm -f $(ROOTDEV)/include/TSplineFit.h
		@rm -f $(ROOTDEV)/include/UVevent.h
		@rm -f UVevent.o UVeventDict.o UVeventDict.cxx UVeventDict.h libUVevent.so

install:
		@rm -f $(ROOTDEV)/include/UVevent.h	
		@rm -f $(ROOTDEV)/bin/$(PROGRAM)
#		@rm -f $(ROOTDEV)/lib/$(LIBTSPLINEFIT).$(DllSuf)
		@rm -f $(ROOTDEV)/include/TPoly3.h
		@rm -f $(ROOTDEV)/include/TOnePadDisplay.h
		@rm -f $(ROOTDEV)/include/TBandedLE.h
		@rm -f $(ROOTDEV)/include/TZigZag.h
		@rm -f $(ROOTDEV)/include/TSplineFit.h
		@cp UVevent.h $(ROOTDEV)/include/UVevent.h
		@cp $(PROGRAM) $(ROOTDEV)/bin/$(PROGRAM)
		@echo "installing......"
#		@cp $(LIBTSPLINEFIT).$(DllSuf) $(ROOTDEV)/lib/$(LIBTSPLINEFIT).$(DllSuf)
		@cp TPoly3.h $(ROOTDEV)/include/TPoly3.h
		@cp TOnePadDisplay.h $(ROOTDEV)/include/TOnePadDisplay.h
		@cp TBandedLE.h $(ROOTDEV)/include/TBandedLE.h
		@cp TZigZag.h $(ROOTDEV)/include/TZigZag.h
		@cp TSplineFit.h $(ROOTDEV)/include/TSplineFit.h
		@cp Calibration.h $(ROOTDEV)/include/Calibration.h
		@cp UVevent.h $(ROOTDEV)/include/UVevent.h
		@cp UVevent.h $(ROOTDEV)/include/UVeventDict.h
		@cp Analysis.h $(ROOTDEV)/include/Analysis.h
		@cp Parameter.h $(ROOTDEV)/include/Parameter.h
		@cp libUVevent.so $(ROOTDEV)/lib/libUVevent.so
		@echo "libraries, shared libraries and includes copied to $(ROOTDEV)"

###
TPoly3.$(ObjSuf):         TPoly3.h
TOnePadDisplay.$(ObjSuf): TOnePadDisplay.h
TBandedLE.$(ObjSuf):      TBandedLE.h
TZigZag.$(ObjSuf):        TZigZag.h
TSplineFit.$(ObjSuf):     TPoly3.h TOnePadDisplay.h TBandedLE.h TZigZag.h TSplineFit.h
Calibration.$(ObjSuf):	  Calibration.h
UVevent.$(ObjSuf):     	  TPoly3.h TOnePadDisplay.h TBandedLE.h TZigZag.h TSplineFit.h UVevent.h
Analysis.$(ObjSuf):	  Analysis.h
Parameter.$(ObjSuf):	  Parameter.h


.SUFFIXES: .$(SrcSuf)

###

#TSplineFitDict.$(SrcSuf): $(HDRS)
#	@echo "Generating Dictionary for TSplineFitDict.cxx ..."
#	@$(ROOTSYS)/bin/rootcint -f TSplineFitDict.$(SrcSuf) -c $(HDRS) TSplineFitLinkDef.h

UVeventDict.$(SrcSuf): $(HDRS)
	@echo "Generating Dictionary for UVevent.cxx ..."
	@$(ROOTSYS)/bin/rootcint -f UVeventDict.$(SrcSuf) -c $(HDRS) UVeventLinkDef.h

.$(SrcSuf).$(ObjSuf):
	$(CXX) $(CXXFLAGS) -c $<

