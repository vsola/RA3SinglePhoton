import re
import sys
import os.path
import StringIO
import glob
import shutil

from SignalScanDefs import *

#scan locations
oldFileLocBino='dcap:///pnfs/cms/WAX/11/store/user/lpcpjm/PrivateMC/FastSim/binolikegrid2/gen/'
oldFileLocWino='dcap:///pnfs/cms/WAX/11/store/user/lpcpjm/PrivateMC/FastSim/winolikegrid2/gen/'
oldFileLocBinoNeutr='dcap:///pnfs/cms/WAX/resilient/lpcpjm/PrivateMC/FastSim/binochigrids/gen/'
newFileLocBino='file:///eos/uscms/store/user/lpcpjm/PrivateMC/FastSim/Spectra_gsq_B/gen/'
newFileLocWino=''
newFileLocBinoNeutr=''
newFileLocWinoNeutr=''

#sampleFile parameters
sampleFileName='selectionanalyzer_MC_GMSBBino_1440_1520_375_cfg.py'
sampleFileScanLoc='dcap:///pnfs/cms/WAX/11/store/user/lpcpjm/PrivateMC/FastSim/binolikegrid2/gen/'
sampleFileNameCondor='scanSignalPointCondor_GGM_1440_1520_375'

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
 if doWino == 1 :
  scanloc = oldFileLocWino
 if doBino == 1 :
  scanloc = oldFileLocBino
 if doBinoNeutr == 1 :
  neutrpoints = neutrpointsOld
  sqpoints = decoupledMassOld
  scanloc = oldFileLocBinoNeutr
 if doWinoNeutr == 1 :
  neutrpoints = neutrpointsOld
  sqpoints = decoupledMassOld
  scanloc = ''
elif int(doV10) == 11 :
 sqpoints = sqpointsNew
 glpoints = glpointsNew
 neutrpoints = neutrpointsSqGlScanNew
 if doWino == 1 :
  scanloc = newFileLocWino
 if doBino == 1 :
  scanloc = newFileLocBino
 if doBinoNeutr == 1 :
  glpoints = glpointsGlNeutrScanNew
  neutrpoints = neutrpointsNew
  sqpoints = decoupledMassNew
  scanloc = newFileLocBinoNeutr
 if doWinoNeutr == 1 :
  neutrpoints = neutrpointsNew
  sqpoints = decoupledMassNew
  scanloc = newFileLocWinoNeutr
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
 
outfilename='signalAcceptance'+scanName+'.dat'

os.system("rm "+outfilename)

print "Create cfg files for signalscan..."
print "NeutralinoType:",scanName
print "sq points:",sqpoints
print "gl points:",glpoints
print "neutr points:",neutrpoints
print "outfilename:",outfilename
print "........................................."
from mergeCrabCutflows import main as mainMerge
count=0
for sqmass in sqpoints:
  for glmass in glpoints:
   for neutrmass in neutrpoints:
   ###only create point if sq/gl > neutrmass
    if int(sqmass) > int(neutrmass):
     if int(glmass) > int(neutrmass):
      print 'squarkmass:',sqmass,' gluinomass:',glmass,' neutralinomass:',neutrmass
      sqglm="batch_"+sqmass+"_"+glmass+"_"+neutrmass+"_*.log"
      matches =  glob.glob(sqglm)
      if matches:
       matches.sort()
      signaloutput=mainMerge(matches)
      f = open(outfilename, 'a')
      signaloutputbinned = []
      signaloutput= signaloutput.rstrip('\n')
      signaloutput_listSep = [str(x) for x in signaloutput.split(':')]
      signaloutputbinned=(signaloutput_listSep)
      #print 'result:',signaloutputbinned # test
      count+=1
      f.write("signalpoint"+str(count)+"_gluino ="+str(glmass)+"\n")
      f.write("signalpoint"+str(count)+"_squark ="+str(sqmass)+"\n")
      f.write("signalpoint"+str(count)+"_NLSP ="+str(neutrmass)+"\n")
      for signaloutfield in signaloutputbinned:
       f.write("signalpoint"+str(count)+"_"+str(signaloutfield)+"\n")
   


