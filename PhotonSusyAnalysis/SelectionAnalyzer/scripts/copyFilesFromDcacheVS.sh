#!/bin/bash


dirnameTrees=(PhotonHad/photonJetSel_2012Cv2_V06)
nameTo="PhotonHad"
versionStr="2012Cv2_V06"

###################################################################################
###################################################################################

ini dctools;

for dirnameTree in ${dirnameTrees[@]};
 do;
 
 dirnameResult=Plots_PhotonSusyAnalysis
 mkdir $dirnameResult
 cd $dirnameResult
 echo "cd to" $dirnameResult
 #ls
 for name in `dcls /pnfs/desy.de/cms/tier2/store/user/vsola/$dirnameTree/`;
 #for name in ${namesfound[@]}
 do
  if [[  $name == **  ]]

 
  then 
  echo "name:" $name
  nameFrom=$dirnameTree/$name
  #nameTo=$name
  
  dummy='_'
  nameTo=$nameTo$dummy$versionStr
  #rm -r $nameTo
  mkdir $nameTo
  allfilesAlreadyCopied=0
  echo "get: "/pnfs/desy.de/cms/tier2/store/user/vsola/$nameFrom/
  echo "to: " $nameTo
  for ff in `dcls /pnfs/desy.de/cms/tier2/store/user/vsola/$nameFrom/`;
  do
    if [[ $ff == *histo* ]]
 	then 
	  if [[ $ff == *histo_*_[2-9]_* ]]
	  then
	   FILE1app=`echo  $ff | awk -v FS='_[2-9]_[a-zA-Z0-9][a-zA-Z0-9][a-zA-Z0-9]' '{print $1}'`
	   FILEno=`echo  $ff | awk -v FS='_' '{print $3}'`
	   #echo "filename: " $FILE1app
	   #echo "current file number:"$FILEno
	   for i in {1..$FILEno};do;
	    if [[ $i -lt $FILEno ]] 
	    then
	     #echo "file "$ff": corresponding lower file "$i" already copied?"
	     filename1=$FILE1app'_'$i'_'
	     #echo "rm corresponding file.. " $filename1
	     rm $nameTo/$filename1*
	    fi
	   done;
	  fi
	  ff2=dummy
	  higherfilealreadycopied=0
	  if [[ $ff == *histo_*_[1-8]_* ]]
	  then
	   #echo "check if file "$ff" already copied in higher version!"
	   FILE2app=`echo  $ff | awk -v FS="_[1-8]_[a-zA-Z0-9][a-zA-Z0-9][a-zA-Z0-9]" '{print $1}'`
	   FILE2pre=`echo  $ff | awk -v FS="histo_[0-9]+_[1-8]_" '{print $2}'`	  
	   FILEno=`echo  $ff | awk -v FS='_' '{print $3}'` 
	   for i in {2..9};do;
	    if [[ $i -gt $FILEno ]] 
	    then
	     ff2=$FILE2app'_'$i'_'
	     #echo "file "$ff2" already copied?"
	     for ffTarget in `ls $nameTo/`;
         do
          if [[ $ffTarget ==  *$ff2* ]]
	      then
	       echo "file "$i" already copied!"
	       higherfilealreadycopied=1
	      fi
         done
	     
	    fi
	   done;
	  fi
	  if [ -f $nameTo/$ff ]
	  then
	   echo "file already copied!"
	  elif [[  $higherfilealreadycopied == 0 ]]
	   then
	    echo "copy..."$ff
	    allfilesAlreadyCopied=1
	    dcget /pnfs/desy.de/cms/tier2/store/user/vsola/$nameFrom/$ff $nameTo/
	  fi 	  
	fi
   
  done
  #allfilesAlreadyCopied=1
  if [[  $allfilesAlreadyCopied == 1 ]]
  then
   cd $nameTo
   echo "merge..."
   hadd -f mergedHistos.root histo*
   cd ..
  fi
  fi
 done
 
done





cd ..
