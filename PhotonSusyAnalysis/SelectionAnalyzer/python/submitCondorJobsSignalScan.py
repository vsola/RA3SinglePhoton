import re
import sys
import os.path
import StringIO
import glob
import shutil

from SignalScanDefs import *

doV10=11
doV10 = str(input("summer 11 (10) or winter 11 (11) MC? (10/11): "))

scanId = raw_input("bino or wino or binoneutr scan? (b/w/bn): ")


doBino=0
doWino=0
doBinoNeutr=0
doWinoNeutr=0
doOld=0
doNew=0



if scanId=='b':
 doBino=1
 doWino=0
 doBinoNeutr=0
elif scanId=='bn':
 doBino=0
 doWino=0
 doBinoNeutr=1
elif scanId=='wn':
 doBino=0
 doWino=0
 doBinoNeutr=0
 doWinoNeutr=1
 if int(doV10) == 10 :
  print 'Wino Neutralino Scan not supported for old Summer 2010 signal scan...exiting'
  exit
 print 'Wino Neutralino Scan not yet supported...exiting'
 exit
elif scanId=='w':
 doBino=0
 doWino=1
 doBinoNeutr=0
else:
 print 'neither bino nor wino nor binoneutr...exiting'
 exit


if int(doV10) == 10 :
 sqpoints = sqglpointsOld
 glpoints = sqglpointsOld
 neutrpoints = neutrpointsSqGlScanOld
 
 if doBinoNeutr == 1 :
  neutrpoints = neutrpointsOld
  sqpoints = decoupledMassOld
 
 if doWinoNeutr == 1 :
  neutrpoints = neutrpointsOld
  sqpoints = decoupledMassOld
 
elif int(doV10) == 11 :
 sqpoints = sqpointsNew
 glpoints = glpointsNew
 neutrpoints = neutrpointsSqGlScanNew

 if doBinoNeutr == 1 :
  glpoints = glpointsGlNeutrScanNew
  neutrpoints = neutrpointsNew
  sqpoints = decoupledMassNew
 
 if doWinoNeutr == 1 :
  neutrpoints = neutrpointsNew
  sqpoints = decoupledMassNew
  
else:
 print 'neither old nor new scans?!...exiting'
 exit
  
scanName='Wino'
if doWinoNeutr == 1 :
 scanName='WinoNeutr'
elif doBinoNeutr == 1 :
 scanName='BinoNeutr'
elif doBino == 1 :
 scanName='Bino'
 
if int(doV10) == 11 :
 scanName=scanName+'Winter11'
elif int(doV10) == 10 :
 scanName=scanName+'Summer11'
 
print "Create cfg files for signalscan..."
print "NeutralinoType:",scanName
print "sq points:",sqpoints
print "gl points:",glpoints
print "neutr points:",neutrpoints

print "........................................."

for sqmass in sqpoints:
  for glmass in glpoints:
   for neutrmass in neutrpoints:
   ###only create point if sq/gl > neutrmass
    if int(sqmass) > int(neutrmass):
     if int(glmass) > int(neutrmass):
	    squarkm=sqmass+'_'
	    gluinom=glmass+'_'
	    neutrm=neutrmass+'_'
	    print "squark:",squarkm
	    print "gluino:",gluinom
	    print "neutralino:",neutrm
	    
	    filename='GGM_Scan'+scanName+'/scanSignalPointCondor_'+squarkm+gluinom+neutrmass
	    jobsubmit='condor_submit '+'PhotonSusyAnalysis/SelectionAnalyzer/'+filename
	    
	    print 'jobsubmit',jobsubmit
	    os.system(jobsubmit)
