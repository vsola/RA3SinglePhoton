import re
import sys
import os.path
import math

mcscalefactor=46.18

def readVector(line,sel):
	#print 'try to read vector from line ',(line)
	#print 'try to read vector for selection ',(sel)
	x0 = []
	line = line.rstrip('\n')
	line_listSep = [str(x) for x in line.split(':')]
	#print 'try to split line: ',line_listSep[1],'-->' ,line_listSep[1].split(',') # test
	line_list = [float(x) for x in line_listSep[1].split(',')]
	x0=(line_list)
	#print 'result:',x0 # test
	return x0;
	
def mcScale(addition):
	xRet=[]
	count=0
	for x in addition:
	 xN=x*mcscalefactor
	 count+=1
	
	 xRet.append(xN)
	return xRet;

	
def addVector(base,addition):
	#print 'try to add vector  ',(addition)
	#print 'to ',(base)
	xRet=[]
	count=0
	if (len(base) == 0 ):
	 return addition;
	if (len(addition) == 0 ):
	 return base;
	for x in addition:
	 xN=x+base[count]
	 count+=1
	 #print 'new ele ',xN
	 xRet.append(xN)
	#print 'result:',xRet # test
	return xRet;

def addVectorQuadr(base,addition):
	#print 'try to add vector QUAD ',(addition)
	#print 'to ',(base)
	xRet=[]
	count=0
	if (len(base) == 0 ):
	 return addition;
	for x in addition:
	 xN=math.sqrt(x*x+base[count]*base[count])
	 count+=1
	 #print 'new ele ',xN
	 xRet.append(xN)
	#print 'result:',xRet # test
	return xRet;
	
def printVector(vec):
	strvec=str(vec)
	strvec=strvec.strip('[')
	strvec=strvec.strip(']')
	strvec=strvec.replace(',','')
	return strvec;

def main(arguments):
    #print 'Opening file ',(arguments)
    #print 'lengtharguments',len(arguments)
    p = re.compile(r'[ ,\n]+')
	#r'\W+'
    doTriggerReport=1
	    
	
    
    
       
    #######Erstelle liste von vorhandenen signal punkten
    sigpointTag='***SIGNALSCANPOINT_'
    sigpointEndTag='===ENDSIGNALSCANPOINT'
    sigpoints=[]
    
    sigpoint_dic = {}
    countsigpoints=0
    dParPoint = re.compile(r'[_,\n]+')
    print '================================================'
    print '================================================'
    print '',sigpointTag
    print '================================================'
    for i in range(0,len(arguments) ) :
     print 'Opening file ' + (arguments)[i]
     infile = open((arguments)[i], 'r')
     for line in infile :
      if ( line.find(sigpointTag) >= 0 ) :
       parpoint=dParPoint.split(line)
       
       msquark=parpoint[1]
       mgluino=parpoint[2]
       mneutr=parpoint[3]
       parpointid=parpoint[1]+parpoint[2]+parpoint[3]  
       #print 'msquark',msquark
       #print 'mgluino',mgluino
       #print 'mneutr',mneutr
       #if ( mgluino == '525' ):
       if not ( parpoint in sigpoints ):
         #if (countsigpoints < 1 ) :
         countsigpoints=countsigpoints+1
         sigpoints.append(parpoint)
         #print 'new parpoint:',parpointid
         
       currfilelist=[]
       if ( parpointid in sigpoint_dic ):
        currfilelist=sigpoint_dic[parpointid]
       if not ( (arguments)[i] in currfilelist ):
        currfilelist.append((arguments)[i])
       sigpoint_dic[parpointid]=currfilelist
       #print 'new parpointFileList:',sigpoint_dic[parpointid]
    #######
    scanName='T1gg'
    outfilename='signalAcceptance'+scanName+'.dat'
    os.system("rm "+outfilename)
    f = open(outfilename, 'a')
    count=0
    ########Loope ueber liste von signal punkten
    #print 'filemap:',sigpoint_dic
    for parpoint, filelist in sigpoint_dic.iteritems():
     #print 'parpoint:',parpoint
     #print 'filelist:',filelist
     parpointCURRLIST=[]
     parpointCURRLIST.append(parpoint)
     nEvts=0
    
     accBinned=[]
     bkgQCDBinned=[]
     bkgEWKBinned=[]
     bkgFSRBinned=[]
    
     accBinnedSYSTUP=[]
     bkgQCDBinnedSYSTUP=[]
     bkgEWKBinnedSYSTUP=[]
     bkgFSRBinnedSYSTUP=[]
    
     accBinned2j=[]
     bkgQCDBinned2j=[]
     bkgEWKBinned2j=[]
     bkgFSRBinned2j=[]
    
     accBinned2jSYSTUP=[]
     bkgQCDBinned2jSYSTUP=[]
     bkgEWKBinned2jSYSTUP=[]
     bkgFSRBinned2jSYSTUP=[]
    
     accBinnedSTATERR=[]
     bkgQCDBinnedSTATERR=[]
     bkgEWKBinnedSTATERR=[]
     bkgFSRBinnedSTATERR=[]
    
     accBinned2jSTATERR=[]
     bkgQCDBinned2jSTATERR=[]
     bkgEWKBinned2jSTATERR=[]
     bkgFSRBinned2jSTATERR=[]
     
     tokens = ['WrappedSelectionAnalyzer:select_1ph_2jets@','WrappedSelectionAnalyzer:select_1ph_3jets@','WrappedSelectionAnalyzer:select_1ph_2jets_FO_Corr@','WrappedSelectionAnalyzer:select_1ph_3jets_FO_Corr@','WrappedSelectionAnalyzer:select_1ph_2jets_PixelSeedCorr@','WrappedSelectionAnalyzer:select_1ph_3jets_PixelSeedCorr@']
     #
     parpointAsList=[]
     for s in tokens:
      
      for filename in filelist :
       #print 'Selection: ' + s
       #print 'Opening file ' + filename
          
       infile = open(filename, 'r')
       onlyCurrSigpoint=[]
       appendLine=0
       appendLineSigPoint=0
       appendLineSel=0
       for line in infile :
        if ( line.find(s) >= 0 ) :
         appendLine=1
        if not  ( line.find(s) >= 0 ) :
         if ( appendLine==1 ) :
          if ( line.find(sigpointTag) >= 0 ) :
           parpointThis=dParPoint.split(line)
           
           parpointid=parpointThis[1]+parpointThis[2]+parpointThis[3]
           #print '!!!!!!!!!!!!!!parpoint:',parpointid
           #print '==============parpoint:',parpoint
           if ( parpointid in parpointCURRLIST ) :
            parpointAsList=parpointThis
            appendLineSigPoint=1
            #print 'new parpoint:',parpoint
          if ( appendLineSigPoint==1) :
           if ( line.find(sigpointEndTag) >= 0 ) :
            appendLineSigPoint=0
            appendLine=0
          if ( appendLineSigPoint==1 ) :
           onlyCurrSigpoint.append(line)
       infile.close()        
       #print '================================================'
       #print '================================================'
       #print '',parpoint
       #print '',s
       #print 'onlyCurrSigpoint',onlyCurrSigpoint
       #print '================================================'
       tokensSel = ['Selected Events Met>100 (binned-STAT UP/DOWN):','Selected Events Met>100 (binned-SYST UP/DOWN):','Selected Events Met>100 (binned-Presel):']
       #print '==========FULL SELECTION';  
       
       for sel in tokensSel:
        #print '',sel,' *************************************************';
        noSel=0
        accSel=[]
        #print 'onlyCurrSigpoint',onlyCurrSigpoint
        for line in onlyCurrSigpoint:
        
         noLen=len(p.split(line))
         if ( line.find(sel) >= 0 ) :
          partition=(p.split(line)[noLen-2]).partition('.')
          if ( (p.split(line)[noLen-2].isdigit()) or (partition[0].isdigit() and partition[1]=='.' and partition[2].isdigit()) or (partition[0]=='' and partition[1]=='.' and partition[2].isdigit()) or (partition[0].isdigit() and partition[1]=='.' and partition[2]=='')):
           isOn=1
           #print float(p.split(line)[noLen-2])
           noSel+= float(p.split(line)[noLen-2])
          if ( line.find('binned-') >= 0 ) :
           #print 'choosen SEL LINE:',line
           if not "(binned-STAT UP/DOWN)" in sel:
            #print 'add VECTOR'
            accSel=addVector(accSel,readVector(line,sel))
           else:
            #print 'add VECTOR QUADR'
            accSel=addVectorQuadr(accSel,readVector(line,sel))
       
        if ( sel == 'Selected Events Met>100 (binned-Presel):' and s == 'WrappedSelectionAnalyzer:select_1ph_3jets@' ):
         #print '',sel,' !!!!!!!!!!!!!!!!!!!';
         accBinned=addVector(accBinned,accSel)
         #accBinned+=accSel
         
        if ( sel == 'Selected Events Met>100 (binned-Presel):' and s == 'WrappedSelectionAnalyzer:select_1ph_3jets_FO_Corr@' ):
         bkgQCDBinned=addVector(bkgQCDBinned,accSel)
         #print '',sel,' !3JET!!!!!!!!!!!!!!!!!!';
        if ( sel == 'Selected Events Met>100 (binned-Presel):' and s == 'WrappedSelectionAnalyzer:select_1ph_3jets_PixelSeedCorr@' ):
         bkgEWKBinned=addVector(bkgEWKBinned,accSel)
        if ( sel == 'Selected Events Met>100 (binned-Presel):' and s == 'WrappedSelectionAnalyzer:select_1ph_3jets_GenEleVeto@' ):
         bkgFSRBinned=addVector(bkgFSRBinned,mcScale(accSel))
       
         #!!!!!!!!!!!!!!!3j
         #!!!!!!!!!!!!!!!SYST UP
        if ( sel == 'Selected Events Met>100 (binned-SYST UP/DOWN):' and s == 'WrappedSelectionAnalyzer:select_1ph_3jets@' ):
         accBinnedSYSTUP=addVector(accBinnedSYSTUP,accSel)
        if ( sel == 'Selected Events Met>100 (binned-SYST UP/DOWN):' and s == 'WrappedSelectionAnalyzer:select_1ph_3jets_FO_Corr@' ):
         bkgQCDBinnedSYSTUP=addVector(bkgQCDBinnedSYSTUP,accSel)
        if ( sel == 'Selected Events Met>100 (binned-SYST UP/DOWN):' and s == 'WrappedSelectionAnalyzer:select_1ph_3jets_PixelSeedCorr@' ):
         bkgEWKBinnedSYSTUP=addVector(bkgEWKBinnedSYSTUP,accSel)
        if ( sel == 'Selected Events Met>100 (binned-SYST UP/DOWN):' and s == 'WrappedSelectionAnalyzer:select_1ph_3jets_GenEleVeto@' ):
         bkgFSRBinnedSYSTUP=addVector(bkgFSRBinnedSYSTUP,mcScale(accSel))
        
        #!!!!!!!!!!!!!!!3j
        #!!!!!!!!!!!!!!!STAT ERR
        if ( sel == 'Selected Events Met>100 (binned-STAT UP/DOWN):' and s == 'WrappedSelectionAnalyzer:select_1ph_3jets@' ):
         accBinnedSTATERR=addVectorQuadr(accBinnedSTATERR,accSel)
        
        if ( sel == 'Selected Events Met>100 (binned-STAT UP/DOWN):' and s == 'WrappedSelectionAnalyzer:select_1ph_3jets_FO_Corr@' ):
         bkgQCDBinnedSTATERR=addVectorQuadr(bkgQCDBinnedSTATERR,accSel)
         #print '',sel,' !3JET!===============';
        if ( sel == 'Selected Events Met>100 (binned-STAT UP/DOWN):' and s == 'WrappedSelectionAnalyzer:select_1ph_3jets_PixelSeedCorr@' ):
         bkgEWKBinnedSTATERR=addVectorQuadr(bkgEWKBinnedSTATERR,accSel)
        if ( sel == 'Selected Events Met>100 (binned-STAT UP/DOWN):' and s == 'WrappedSelectionAnalyzer:select_1ph_3jets_GenEleVeto@' ):
         bkgFSRBinnedSTATERR=addVectorQuadr(bkgFSRBinnedSTATERR,mcScale(accSel))
        
        
        #!!!!!!!!!!!!!!!2j
        #!!!!!!!!!!!!!!!event yields
        if ( sel == 'Selected Events Met>100 (binned-Presel):' and s == 'WrappedSelectionAnalyzer:select_1ph_2jets@' ):
         accBinned2j=addVector(accBinned2j,accSel)
         #print '',sel,' !2JET!!!!!!!!!!!!!!!!!!';
        if ( sel == 'Selected Events Met>100 (binned-Presel):' and s == 'WrappedSelectionAnalyzer:select_1ph_2jets_FO_Corr@' ):
         bkgQCDBinned2j=addVector(bkgQCDBinned2j,accSel)
        if ( sel == 'Selected Events Met>100 (binned-Presel):' and s == 'WrappedSelectionAnalyzer:select_1ph_2jets_PixelSeedCorr@' ):
         bkgEWKBinned2j=addVector(bkgEWKBinned2j,accSel)
        if ( sel == 'Selected Events Met>100 (binned-Presel):' and s == 'WrappedSelectionAnalyzer:select_1ph_2jets_GenEleVeto@' ):
         bkgFSRBinned2j=addVector(bkgFSRBinned2j,mcScale(accSel))
        
        #!!!!!!!!!!!!!!!2j
        #!!!!!!!!!!!!!!!SYST UP
        if ( sel == 'Selected Events Met>100 (binned-SYST UP/DOWN):' and s == 'WrappedSelectionAnalyzer:select_1ph_2jets@' ):
         accBinned2jSYSTUP=addVector(accBinned2jSYSTUP,accSel)
        if ( sel == 'Selected Events Met>100 (binned-SYST UP/DOWN):' and s == 'WrappedSelectionAnalyzer:select_1ph_2jets_FO_Corr@' ):
         bkgQCDBinned2jSYSTUP=addVector(bkgQCDBinned2jSYSTUP,accSel)
        if ( sel == 'Selected Events Met>100 (binned-SYST UP/DOWN):' and s == 'WrappedSelectionAnalyzer:select_1ph_2jets_PixelSeedCorr@' ):
         bkgEWKBinned2jSYSTUP=addVector(bkgEWKBinned2jSYSTUP,accSel)
        if ( sel == 'Selected Events Met>100 (binned-SYST UP/DOWN):' and s == 'WrappedSelectionAnalyzer:select_1ph_2jets_GenEleVeto@' ):
         bkgFSRBinned2jSYSTUP=addVector(bkgFSRBinned2jSYSTUP,mcScale(accSel))
         
        #!!!!!!!!!!!!!!!2j
        #!!!!!!!!!!!!!!!STAT ERR
        if ( sel == 'Selected Events Met>100 (binned-STAT UP/DOWN):' and s == 'WrappedSelectionAnalyzer:select_1ph_2jets@' ):
         accBinned2jSTATERR=addVectorQuadr(accBinned2jSTATERR,accSel)
         #print '',sel,' !2JET!!!!!!!!!!!!!!!!!!';
        if ( sel == 'Selected Events Met>100 (binned-STAT UP/DOWN):' and s == 'WrappedSelectionAnalyzer:select_1ph_2jets_FO_Corr@' ):
         bkgQCDBinned2jSTATERR=addVectorQuadr(bkgQCDBinned2jSTATERR,accSel)
        if ( sel == 'Selected Events Met>100 (binned-STAT UP/DOWN):' and s == 'WrappedSelectionAnalyzer:select_1ph_2jets_PixelSeedCorr@' ):
         bkgEWKBinned2jSTATERR=addVectorQuadr(bkgEWKBinned2jSTATERR,accSel)
        if ( sel == 'Selected Events Met>100 (binned-STAT UP/DOWN):' and s == 'WrappedSelectionAnalyzer:select_1ph_2jets_GenEleVeto@' ):
         bkgFSRBinned2jSTATERR=addVectorQuadr(bkgFSRBinned2jSTATERR,mcScale(accSel))
        #print "+++++++++++++++++++++++++++"
        
        #end tokens    
     #print "=============================="
        
     print 'signal.ngen = ',nEvts
      
     ###binned output
     print 'BINNED OUTPUT:',parpoint
     print 'selEvents = ',accBinned
     print 'selEventsSYSTUP = ',accBinnedSYSTUP
     print 'selEvents2j = ',accBinned2j
     print 'selEventsSYSTUP2j = ',accBinned2jSYSTUP
     print 'bkgQCDBinned = ',bkgQCDBinned
     print 'bkgQCDBinnedSYSTUP = ',bkgQCDBinnedSYSTUP
     print 'bkgEWKBinned = ',bkgEWKBinned
     print 'bkgEWKBinnedSYSTUP = ',bkgEWKBinnedSYSTUP
       
     
     ###final output used for mkInput skript
     signalscanresultBinned = "totalGenEvents = "+str(nEvts)+":selEvents = "+str(printVector(accBinned))+":selEventsSYSTUP="+str(printVector(accBinnedSYSTUP))+":selEventsSTATERR="+str(printVector(accBinnedSTATERR))+":bkgQCDBinned="+str(printVector(bkgQCDBinned))+":bkgQCDBinnedSYSTUP="+str(printVector(bkgQCDBinnedSYSTUP))+":bkgQCDBinnedSTATERR="+str(printVector(bkgQCDBinnedSTATERR))+":bkgEWKBinned="+str(printVector(bkgEWKBinned))+":bkgEWKBinnedSYSTUP="+str(printVector(bkgEWKBinnedSYSTUP))+":bkgEWKBinnedSTATERR="+str(printVector(bkgEWKBinnedSTATERR));
     signalscanresultBinned2j = ":selEvents2j = "+str(printVector(accBinned2j))+":selEvents2jSYSTUP="+str(printVector(accBinned2jSYSTUP))+":selEvents2jSTATERR="+str(printVector(accBinned2jSTATERR))+":bkgQCDBinned2j="+str(printVector(bkgQCDBinned2j))+":bkgQCDBinned2jSYSTUP="+str(printVector(bkgQCDBinned2jSYSTUP))+":bkgQCDBinned2jSTATERR="+str(printVector(bkgQCDBinned2jSTATERR))+":bkgEWKBinned2j="+str(printVector(bkgEWKBinned2j))+":bkgEWKBinned2jSYSTUP="+str(printVector(bkgEWKBinned2jSYSTUP))+":bkgEWKBinned2jSTATERR="+str(printVector(bkgEWKBinned2jSTATERR));
     signalscanresultBinned=signalscanresultBinned+signalscanresultBinned2j
	
     #print 'outputbinned:',signalscanresultBinned
     signaloutput= signalscanresultBinned.rstrip('\n')
     signaloutput= signaloutput.rstrip('\n')
     signaloutput_listSep = [str(x) for x in signaloutput.split(':')]
     signaloutputbinned=(signaloutput_listSep)
     #print 'result:',signaloutputbinned # test
     count+=1
     msquark=parpointAsList[1]
     mgluino=parpointAsList[2]
     mneutr=parpointAsList[3]
     f.write("signalpoint"+str(count)+"_gluino ="+str(mgluino)+"\n")
     f.write("signalpoint"+str(count)+"_squark ="+str(msquark)+"\n")
     f.write("signalpoint"+str(count)+"_NLSP ="+str(mneutr)+"\n")
     for signaloutfield in signaloutputbinned:
      f.write("signalpoint"+str(count)+"_"+str(signaloutfield)+"\n")
     
    
   
    ####
     
         
if __name__ == "__main__":
    main(sys.argv[1:])


