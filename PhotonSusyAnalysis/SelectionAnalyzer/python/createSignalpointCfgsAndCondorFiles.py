import re
import sys
import os.path
import StringIO
import glob
import shutil

from SignalScanDefs import *

from tempfile import mkstemp
from shutil import move
from os import remove, close

def replace(file, pattern, subst):
    #Create temp file
    fh, abs_path = mkstemp()
    new_file = open(abs_path,'w')
    old_file = open(file)
    for line in old_file:
        new_file.write(line.replace(pattern, subst))
    #close temp file
    new_file.close()
    close(fh)
    old_file.close()
    #Remove original file
    remove(file)
    #Move new file
    move(abs_path, file)

doCfgs=1
doCondors=1
doV10=11
useDefault = str(input("create all cfgs & condor files for new scan (Winter11)? (1/0) "))
if int(useDefault) == 0 :
 doV10 = str(input("summer 11 (10) or winter 11 (11) MC? (10/11): "))
 doCfgs = str(input("create cmsRun python files? (1/0) "))
 doCondors = str(input("create condor submission files? (1/0) "))

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



scanloc=''

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
  
noQueues=8
noEvents=2500

scanName='Wino'
if doWinoNeutr == 1 :
 scanName='WinoNeutr'
elif doBinoNeutr == 1 :
 scanName='BinoNeutr'
 noQueues=4
 noEvents=2500
elif doBino == 1 :
 scanName='Bino'
 noQueues=4
 noEvents=2500

if int(doV10) == 11 :
 scanName=scanName+'Winter11'
elif int(doV10) == 10 :
 scanName=scanName+'Summer11'
 
print "Create cfg files for signalscan..."
print "NeutralinoType:",scanName
print "sq points:",sqpoints
print "gl points:",glpoints
print "neutr points:",neutrpoints
print "noEvents per Queue:",noEvents
print "noQueues:",noQueues
print "doCfgs:",doCfgs
print "doCondors:",doCondors
print "........................................."
savedPath = os.getcwd()

if int(doCfgs) == 1 :
 scanDirPath="PhotonSusyAnalysis/SelectionAnalyzer/pythonScriptsFullEvent"
 os.chdir(scanDirPath)
 scanDir="GGM_Scan"+scanName
 print scanDir
 if os.path.exists(scanDir):
  shutil.rmtree(scanDir)
 os.mkdir(scanDir)

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
	 
	    filename=scanDir+'/selectionanalyzer_MC_GGM_'+squarkm+gluinom+neutrm+'cfg.py'
	    filenameOld=sampleFileName
	    print filename
	   
	    os.system('cp '+ filenameOld +' '+scanDir+'/.')
	    sedOutput='sed s/Bino_1440_1520_375/'+scanName+'_'+squarkm+gluinom+neutrm+'/g'+' '+scanDir+'/'+filenameOld+' >'+filename
	     
	    print "sedoutput: ",sedOutput
	    os.system(sedOutput)
	    ###adapt path to correct signal file...
	    replace(filename,'1440_1520_375',squarkm+gluinom+neutrmass)
	    ###adapt path to correct signal scan location...
	    print "adapt path to correct signal scan location..."
	    replace(filename,sampleFileScanLoc,scanloc)
	    
	    ###for the Winter11 scan - update PU configuration
	    if int(doV10) == 11 :
	     replace(filename,'PUDistributionMC=0','PUDistributionMC='+PUDistributionMCWinter11Scan)
	     replace(filename,'PUDistributionData=0','PUDistributionData='+PUDistributionDataWinter11Scan)

os.chdir(savedPath)  
if int(doCondors) == 1 :
 
 scanDirPath="PhotonSusyAnalysis/SelectionAnalyzer"
 os.chdir(scanDirPath)
 print'current dir:',os.getcwd()
 scanDir="GGM_Scan"+scanName
 print scanDir
 if os.path.exists(scanDir):
  shutil.rmtree(scanDir)
 os.mkdir(scanDir)


 os.system('cp '+ sampleFileNameCondor +' '+scanDir+'/.')

 replace(scanDir+'/'+sampleFileNameCondor,'SCANNAME',scanName)
 replace(scanDir+'/'+sampleFileNameCondor,'NOQUEUES',str(noQueues))
 replace(scanDir+'/'+sampleFileNameCondor,'NOEVENTS',str(noEvents))

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
	
	    filename='scanSignalPointCondor_'+squarkm+gluinom+neutrmass
	    print 'new filename:',filename
	    
	    sedOutput=''
	    sedOutput='sed s/1440_1520_375/'+squarkm+gluinom+neutrmass+'/g '+' '+scanDir+'/'+sampleFileNameCondor+' >'+scanDir+'/'+filename
	    print 'sedOutput',sedOutput
	    os.system(sedOutput)
	    
	    replace(scanDir+'/'+filename,'1440_1520_375',squarkm+gluinom+neutrmass)
	   # replace(scanDir+'/'+filename,'GGMScanBino','GGMScan'+scanName)
	   # replace(scanDir+'/'+filename,'GGM_ScanBino','GGM_Scan'+scanName)
   
	   
