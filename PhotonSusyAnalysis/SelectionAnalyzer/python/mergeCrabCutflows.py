import re
import sys
import os.path
import math

mcscalefactor=46.18
#43.22
##percentage of ISRFSR uncert applied to MC
isrfsrcorrfactor=0.5

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

def applyISRFSRUncert(base):
    print '!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!try to weight ',(base)
    xRet=[]
    count=0
    if (len(base) == 0 ):
     return base;
    for x in base:
     xN=base[count]*isrfsrcorrfactor
     count+=1
     print 'new ele ',xN
     xRet.append(xN)
    print 'result:',xRet # test
    return xRet;
	
def addVector(base,addition):
	#print 'try to add vector  ',(addition)
	#print 'to ',(base)
	xRet=[]
	count=0
	if (len(base) == 0 ):
	 return addition;
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
	
	
    
    
    accTrigger=0
    accTriggerN90Hits=0
    acc=0
    acc200=0
    acc350=0
    contP=0
    contP200=0
    contP350=0
    contFO=0
    contFO200=0
    contFO350=0
    
    acc2j=0
    acc2002j=0
    acc3502j=0
    contP2j=0
    contP2002j=0
    contP3502j=0
    contFO2j=0
    contFO2002j=0
    contFO3502j=0
    
    accUp=0
    accDown=0
    contPUp=0
    contPDown=0   
    contFOUp=0
    contFODown=0
    ####Presel
    accPresel=0
    accUpPresel=0
    accDownPresel=0
    contPPresel=0
    contPUpPresel=0
    contPDownPresel=0
    contFOPresel=0
    contFOUpPresel=0
    contFODownPresel=0
    #######
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
    
    
    tokens4 = ['WrappedSelectionAnalyzer:select_1ph_2jets@','WrappedSelectionAnalyzer:select_1ph_3jets@','WrappedSelectionAnalyzer:select_1ph_2jets_FO_Corr@','WrappedSelectionAnalyzer:select_1ph_3jets_FO_Corr@','WrappedSelectionAnalyzer:select_1ph_2jets_PixelSeedCorr@','WrappedSelectionAnalyzer:select_1ph_3jets_PixelSeedCorr@','WrappedSelectionAnalyzer:select_1ph_2jets_GenEleVeto@','WrappedSelectionAnalyzer:select_1ph_3jets_GenEleVeto@']
    #['WrappedSelectionAnalyzer:select_1ph_3jets@','WrappedSelectionAnalyzer:select_1ph_3jets_FO@','WrappedSelectionAnalyzer:select_1ph_3jets_GenElectron@','WrappedSelectionAnalyzer:select_1ph_2jets@']
    #'WrappedSelectionAnalyzer:select_1ph_3jets_PixelSeed@',
    #,'WrappedSelectionAnalyzer:select_1ph_3jets_GenElectron@','WrappedSelectionAnalyzer:select_1ph_3jets_GenPhoton@'
    for s in tokens4:
        print '================================================'
        print '================================================'
        print '',s
        print '================================================'
        onlyCurr=[]
        onlyCurrSel=[]
        onlyCurrPresel=[]
        onlyCurrMET=[]
        for i in range(0,len(arguments) ) :
            #print 'Opening file ' + (arguments)[i]
            infile = open((arguments)[i], 'r')
            appendLine=0
            appendLineSel=0
            appendLinePresel=0
            appendLineMET=0
            tokenFound=0
            for line in infile :
                if ( line.find(s) >= 0 ) :
                   #print '3Jet:',line
                   appendLine=1
                   appendLineSel=1
                   if ( tokenFound==1 ) :
                    appendLineSel=0
                    appendLine=0
                   tokenFound=1
                if not  ( line.find(s) >= 0 ) :
                 if ( appendLine==1 ) :
                  if ( line.find('Selected Events (Presel)') >= 0 ) :
                   appendLineSel=0
                   appendLinePresel=1
                  if ( line.find('SELECTED HIGH MET EVENTS:') >= 0 ) :
                   appendLinePresel=0
                   appendLineSel=0
                  if (line.find('WrappedSelectionAnalyzer') >= 0) :
                     appendLine=0
                     appendLinePresel=0
                     appendLineSel=0
                     appendLineMET=0
                  if (line.find('TrigReport') >= 0) :
                     appendLine=0
                     appendLinePresel=0
                     appendLineSel=0
                     appendLineMET=0	 
                  if ( appendLinePresel==1 ) :
                   onlyCurrPresel.append(line)
                  if ( appendLineSel==1 ) :
                   onlyCurrSel.append(line)
                  if ( appendLineMET==1 ) :
                   onlyCurrMET.append(line)
                  if ( line.find('SELECTED HIGH MET EVENTS:') >= 0 ) :
                   appendLineMET=1
                   
            infile.close()
    
        #UNCOMMENT TO print 'HIGH MET TAIL:'
        for line in onlyCurrMET:
         if ( line.find(':') >= 0 ) :
          print '',line 
        tokensSel = ['Selected Events Met>100 (binned-STAT UP/DOWN):','Selected Events Met>100 (binned-SYST UP/DOWN):','Selected Events Met>100 (binned-Presel):','Selected Events Met100:','Selected Events Met200:','Selected Events Met350:','Selected Events (Presel):','Weighted)','photonEta','jetEta','deltaRPhotonJet','>= 2 Photons','= 1 Photons','= 2 Jets','>= 3 Jets','HT','HTHLT','MHT','leptonVeto','jetPt','jet2Pt','photonPt','MET']
        print '==========FULL SELECTION';  
        for sel in tokensSel:
         noSel=0
         accSel=[]
         isOn=0
         for line in onlyCurrSel:
          if not (line.find('WrappedSelectionAnalyzer') >= 0) :
           #print 'choosen SEL LINE:',line
           noLen=len(p.split(line))
           if ( line.find(sel) >= 0 ) :
            #print 'DEBUG:',p.split(line)[noLen-2])
	    partition=(p.split(line)[noLen-2]).partition('.')
            if ( (p.split(line)[noLen-2].isdigit()) or (partition[0].isdigit() and partition[1]=='.' and partition[2].isdigit()) or (partition[0]=='' and partition[1]=='.' and partition[2].isdigit()) or (partition[0].isdigit() and partition[1]=='.' and partition[2]=='')):
             isOn=1
             #print float(p.split(line)[noLen-2])
             noSel+= float(p.split(line)[noLen-2])
     
             #print 'choosen SEL LINE:',line
            
            if ( line.find('binned-') >= 0 ) :
             #print 'choosen SEL LINE:',line
             if not "(binned-STAT UP/DOWN)" in sel:
              #print 'add VECTOR'
              accSel=addVector(accSel,readVector(line,sel))
             else:
              #print 'add VECTOR QUADR'
              accSel=addVectorQuadr(accSel,readVector(line,sel))
             
             #print 'curr token:',sel
             #print 'curr token s:',s         
         if (isOn==1):
          print '',sel,' :',noSel;
         #if (isOn!=1):
          #print '',sel,' :NOT FOUND';
         # accBinned+= 
         #print 'SEL:',sel,' !!!!!!!!!!!!!!!!!!!'
         #print 's:',s,' ========='
         #!!!!!!!!!!!!!!!3j
         #!!!!!!!!!!!!!!!eventyield
         if ( sel == 'Selected Events Met>100 (binned-Presel):' and s == 'WrappedSelectionAnalyzer:select_1ph_3jets@' ):
          #print '',sel,' !!!!!!!!!!!!!!!!!!!';
          accBinned=addVector(accBinned,accSel)
          #accBinned+=accSel
          
         if ( sel == 'Selected Events Met>100 (binned-Presel):' and s == 'WrappedSelectionAnalyzer:select_1ph_3jets_FO_Corr@' ):
          bkgQCDBinned=addVector(bkgQCDBinned,accSel)
          print '',sel,' !3JET!!!!!!!!!!!!!!!!!!';
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
          bkgFSRBinnedSYSTUP=applyISRFSRUncert(bkgFSRBinnedSYSTUP)
          
         #!!!!!!!!!!!!!!!3j
         #!!!!!!!!!!!!!!!STAT ERR
         if ( sel == 'Selected Events Met>100 (binned-STAT UP/DOWN):' and s == 'WrappedSelectionAnalyzer:select_1ph_3jets@' ):
          accBinnedSTATERR=addVectorQuadr(accBinnedSTATERR,accSel)
         
         if ( sel == 'Selected Events Met>100 (binned-STAT UP/DOWN):' and s == 'WrappedSelectionAnalyzer:select_1ph_3jets_FO_Corr@' ):
          bkgQCDBinnedSTATERR=addVectorQuadr(bkgQCDBinnedSTATERR,accSel)
          print '',sel,' !3JET!===============';
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
          bkgFSRBinned2jSYSTUP=applyISRFSRUncert(bkgFSRBinned2jSYSTUP)
          
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
          print '',sel,' !2JET!!!!!!!!!!!!!!!!!!';
         if ( sel == 'Selected Events Met>100 (binned-STAT UP/DOWN):' and s == 'WrappedSelectionAnalyzer:select_1ph_2jets_FO_Corr@' ):
          bkgQCDBinned2jSTATERR=addVectorQuadr(bkgQCDBinned2jSTATERR,accSel)
         if ( sel == 'Selected Events Met>100 (binned-STAT UP/DOWN):' and s == 'WrappedSelectionAnalyzer:select_1ph_2jets_PixelSeedCorr@' ):
          bkgEWKBinned2jSTATERR=addVectorQuadr(bkgEWKBinned2jSTATERR,accSel)
         if ( sel == 'Selected Events Met>100 (binned-STAT UP/DOWN):' and s == 'WrappedSelectionAnalyzer:select_1ph_2jets_GenEleVeto@' ):
          bkgFSRBinned2jSTATERR=addVectorQuadr(bkgFSRBinned2jSTATERR,mcScale(accSel))
          
          
         #============================================old 'unbinned' values
         if ( sel == 'Selected Events Met100:' and s == 'WrappedSelectionAnalyzer:select_1ph_3jets@' ):
          acc+= noSel
         if ( sel == 'Selected Events Met200:' and s == 'WrappedSelectionAnalyzer:select_1ph_3jets@' ):
          acc200+= noSel
         if ( sel == 'Selected Events Met350:' and s == 'WrappedSelectionAnalyzer:select_1ph_3jets@' ):
          acc350+= noSel
         if ( sel == 'Selected Events Met100:' and s == 'WrappedSelectionAnalyzer:select_1ph_3jets_FO_Corr@' ):
          contFO+= noSel
         if ( sel == 'Selected Events Met200:' and s == 'WrappedSelectionAnalyzer:select_1ph_3jets_FO_Corr@' ):
          contFO200+= noSel
         if ( sel == 'Selected Events Met350:' and s == 'WrappedSelectionAnalyzer:select_1ph_3jets_FO_Corr@' ):
          contFO350+= noSel
         if ( sel == 'Selected Events Met100:' and s == 'WrappedSelectionAnalyzer:select_1ph_3jets_PixelSeedCorr@' ):
          contP+= noSel
         if ( sel == 'Selected Events Met200:' and s == 'WrappedSelectionAnalyzer:select_1ph_3jets_PixelSeedCorr@' ):
          contP200+= noSel
         if ( sel == 'Selected Events Met350:' and s == 'WrappedSelectionAnalyzer:select_1ph_3jets_PixelSeedCorr@' ):
          contP350+= noSel
         if ( sel == 'Selected Events Met100:' and s == 'WrappedSelectionAnalyzer:select_1ph_2jets@' ):
          acc2j+= noSel
         if ( sel == 'Selected Events Met200:' and s == 'WrappedSelectionAnalyzer:select_1ph_2jets@' ):
          acc2002j+= noSel
         if ( sel == 'Selected Events Met350:' and s == 'WrappedSelectionAnalyzer:select_1ph_2jets@' ):
          acc3502j+= noSel
         if ( sel == 'Selected Events Met100:' and s == 'WrappedSelectionAnalyzer:select_1ph_2jets_FO_Corr@' ):
          contFO2j+= noSel
         if ( sel == 'Selected Events Met200:' and s == 'WrappedSelectionAnalyzer:select_1ph_2jets_FO_Corr@' ):
          contFO2002j+= noSel
         if ( sel == 'Selected Events Met350:' and s == 'WrappedSelectionAnalyzer:select_1ph_2jets_FO_Corr@' ):
          contFO3502j+= noSel
         if ( sel == 'Selected Events Met100:' and s == 'WrappedSelectionAnalyzer:select_1ph_2jets_PixelSeedCorr@' ):
          contP2j+= noSel
         if ( sel == 'Selected Events Met200:' and s == 'WrappedSelectionAnalyzer:select_1ph_2jets_PixelSeedCorr@' ):
          contP2002j+= noSel
         if ( sel == 'Selected Events Met350:' and s == 'WrappedSelectionAnalyzer:select_1ph_2jets_PixelSeedCorr@' ):
          contP3502j+= noSel
         if ( sel == 'Weighted)' and s == 'WrappedSelectionAnalyzer:select_AllN90Hits@' ):
          accTriggerN90Hits+= noSel
         if ( sel == 'Weighted)' and s == 'WrappedSelectionAnalyzer:select_All@' ):
          accTrigger+= noSel
         
         
         #if (isOn==0):
         # print '',sel,': OFF';   
        print '==========PRE-SELECTION';   
        for sel in tokensSel:
         noSel=0
         isOn=0
         for line in onlyCurrPresel:
          if not (line.find('WrappedSelectionAnalyzer') >= 0) :
           noLen=len(p.split(line))
           #print p.split(line)
           if ( line.find(sel) >= 0 ) :
            #print 'token found',p.split(line)
            partition=(p.split(line)[noLen-2]).partition('.')
            if ( (p.split(line)[noLen-2].isdigit()) or (partition[0].isdigit() and partition[1]=='.' and partition[2].isdigit()) or (partition[0]=='' and partition[1]=='.' and partition[2].isdigit()) or (partition[0].isdigit() and partition[1]=='.' and partition[2]=='')):
             isOn=1
             #print float(p.split(line)[noLen-2])
             noSel+= float(p.split(line)[noLen-2])
         if (isOn==1):
          print '',sel,' :',noSel;   
         if ( sel == 'Weighted)' and s == 'WrappedSelectionAnalyzer:select_1ph_3jets@' ):
          accPresel+= noSel
         if ( sel == 'Weighted)' and s == 'WrappedSelectionAnalyzer:select_1ph_3jets_FO_Corr@' ):
          contFOPresel+= noSel
         if ( sel == 'Weighted)' and s == 'WrappedSelectionAnalyzer:select_1ph_3jets_PixelSeedCorr@' ):
          contPPresel+= noSel
         #if (isOn==0):
         # print '',sel,': OFF';   
    
    ###########################################################################################
    
    p = re.compile(r'\W+')
    if ( doTriggerReport==1 ):
     print "\\begin{tabular}{lll}"
     print '\\textbf{Cut}  & \\textbf{passed} & \\textbf{failed} \\\\'
     
     tokens = ['oneGoodVertexFilter']
     my_dic = {"oneGoodVertexFilter":"primary Vtx"}
     
     #tokens = []
     #my_dic = {}
     
     for st in tokens:
        #print 'Looking at string ' + st
        
        nvisit = 0
        npass = 0
        nfail = 0
        nerror = 0
        for i in range(0,len(arguments) ) :
            #print 'Opening file ' + arguments[i]
            infile = open(arguments[i], 'r')
        
            for line in infile :
                if ( line.find(st) >= 0 and line.find('TrigReport')>=0 ) :
                    #print 'found! line = ',line
                    #print p.split(line)
                    nvisit += int(p.split(line)[3])
                    npass  += int(p.split(line)[4])
                    nfail  += int(p.split(line)[5])
                    #nerror += int(p.split(line)[6])
                    break
            infile.close()
        #print '%20s' % (s),' : visited %10d' % nvisit,', pass %10d' % npass,', fail %10d' % nfail 
           
        print '%20s' % my_dic[(st)],'& %10d' % npass,'& %10d' % nfail,'\\\\' 
        if( nEvts == 0 ):
          nEvts=npass
    
     print '\end{tabular}'
    
    print "=============================="
    print "scanresult",acc," ",contFO+contP," ",nEvts," ",accPresel-acc," ",(contFOPresel+contPPresel)-(contFO+contP)," ",accUp," ",accDown," ",accUpPresel-accUp," ",accDownPresel-accDown," ",contFOUp+contPUp," ",contFODown+contPDown," ",(contFOUpPresel+contPUpPresel)-(contFOUp+contPUp)," ",(contFODownPresel+contPDownPresel)-(contFODown+contPDown)
    print 'signal.acceptance = ',acc
    
    print 'signal.acceptance200 = ',acc200
    print 'signal.acceptance350 = ',acc350
    print 'signal.bkgcont = ',contFO+contP
    print 'signal.bkgcont200 = ',contFO200+contP200
    print 'signal.bkgcont350 = ',contFO350+contP350
    
    print 'control.acceptance = ',accPresel-acc
    print 'control.bkgcont = ',(contFOPresel+contPPresel)-(contFO+contP)
    
    print 'signal.ngen = ',nEvts
    
    print 'signal.triggeracc =',accTrigger
    print 'signal.triggeraccN90Hits =',accTriggerN90Hits
    ###binned output
    print 'BINNED OUTPUT'
    print 'selEvents = ',accBinned
    print 'selEventsSYSTUP = ',accBinnedSYSTUP
    print 'selEvents2j = ',accBinned2j
    print 'selEventsSYSTUP2j = ',accBinned2jSYSTUP
    print 'bkgQCDBinned = ',bkgQCDBinned
    print 'bkgQCDBinnedSYSTUP = ',bkgQCDBinnedSYSTUP
    print 'bkgEWKBinned = ',bkgEWKBinned
    print 'bkgEWKBinnedSYSTUP = ',bkgEWKBinnedSYSTUP
    print 'bkgFSRBinned = ',bkgFSRBinned
    print 'bkgFSRBinnedSYSTUP = ',bkgFSRBinnedSYSTUP
   
    ###final output used for mkInput skript
    signalscanresultBinned = "totalGenEvents = "+str(nEvts)+":selEvents = "+str(printVector(accBinned))+":selEventsSYSTUP="+str(printVector(accBinnedSYSTUP))+":selEventsSTATERR="+str(printVector(accBinnedSTATERR))+":bkgQCDBinned="+str(printVector(bkgQCDBinned))+":bkgQCDBinnedSYSTUP="+str(printVector(bkgQCDBinnedSYSTUP))+":bkgQCDBinnedSTATERR="+str(printVector(bkgQCDBinnedSTATERR))+":bkgEWKBinned="+str(printVector(bkgEWKBinned))+":bkgEWKBinnedSYSTUP="+str(printVector(bkgEWKBinnedSYSTUP))+":bkgEWKBinnedSTATERR="+str(printVector(bkgEWKBinnedSTATERR))+":bkgFSRBinned="+str(printVector(bkgFSRBinned))+":bkgFSRBinnedSYSTUP="+str(printVector(bkgFSRBinnedSYSTUP))+":bkgFSRBinnedSTATERR="+str(printVector(bkgFSRBinnedSTATERR));
    signalscanresultBinned2j = ":selEvents2j = "+str(printVector(accBinned2j))+":selEvents2jSYSTUP="+str(printVector(accBinned2jSYSTUP))+":selEvents2jSTATERR="+str(printVector(accBinned2jSTATERR))+":bkgQCDBinned2j="+str(printVector(bkgQCDBinned2j))+":bkgQCDBinned2jSYSTUP="+str(printVector(bkgQCDBinned2jSYSTUP))+":bkgQCDBinned2jSTATERR="+str(printVector(bkgQCDBinned2jSTATERR))+":bkgEWKBinned2j="+str(printVector(bkgEWKBinned2j))+":bkgEWKBinned2jSYSTUP="+str(printVector(bkgEWKBinned2jSYSTUP))+":bkgEWKBinned2jSTATERR="+str(printVector(bkgEWKBinned2jSTATERR))+":bkgFSRBinned2j="+str(printVector(bkgFSRBinned2j))+":bkgFSRBinned2jSYSTUP="+str(printVector(bkgFSRBinned2jSYSTUP))+":bkgFSRBinned2jSTATERR="+str(printVector(bkgFSRBinned2jSTATERR));
    signalscanresultBinned=signalscanresultBinned+signalscanresultBinned2j

    #print 'outputbinned:',signalscanresultBinned
    signaloutput= signalscanresultBinned.rstrip('\n')
    signaloutput_listSep = [str(x) for x in signaloutput.split(':')]
    signaloutputbinned=(signaloutput_listSep)
    for signaloutfield in signaloutputbinned:
     print (""+str(signaloutfield)+"")
    ####
    return signalscanresultBinned
    
 #
	

if __name__ == "__main__":
    main(sys.argv[1:])


