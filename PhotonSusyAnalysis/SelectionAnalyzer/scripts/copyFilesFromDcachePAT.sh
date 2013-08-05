#!/bin/bash



dirnameTrees=(PhotonSusyAnalysis)

### cd /pnfs/desy.de/cms/tier2/store/user/vsola/; ls */photonJetSelection_V2/*
#namesfound=()


versionStr="PAT"
###################################################################################
###################################################################################

ini dctools;

for dirnameTree in ${dirnameTrees[@]};
 do;
 
 dirnameResult=Plots_$dirnameTree
# mkdir $dirnameResult
 cd $dirnameResult
 echo "cd to" $dirnameResult
 #ls
 for name in `dcls /pnfs/desy.de/cms/tier2/store/user/vsola/$dirnameTree/`;
 #for name in ${namesfound[@]}
 do
  if [[  $name == *V05w*  ]]
#  if [[  $name == *T09*  ]]
#  if [[ $name == *PhotonHadReReco_22Jan2013*_V05* ]]

  then 
  echo "name:" $name
  nameFrom=$dirnameTree/$name
  nameTo=$name
  
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

if [[  1 == 0 ]]
then
 
vers        = V07b
versQCD     = V07b_qcd
versData    = V07b_data
versPat     = V07b_PAT
versPatQCD  = V07b_PATqcd
versPatData = V07b_PATdata

 mkdir Merged_Data_$versPatData
 cd Merged_Data_$versPatData
 hadd -f mergedHistos.root  ../PhotonHadPromptReco_Aug5_$versPatData/mergedHistos.root ../PhotonHadPromptReco_v4_$versPatData/mergedHistos.root ../PhotonHadPromptReco_v6_$versPatData/mergedHistos.root ../PhotonHadPromptReco_B_$versPatData/mergedHistos.root

 cd ..
 
 mkdir Merged_EWK_$vers
 cd Merged_EWK_$vers
 hadd -f mergedHistos.root ../WJets_$versPat/mergedHistos.root ../TTBar_$versPat/mergedHistos.root
 cd ..
 
 mkdir Merged_QCD_bins_$versQCD
 cd Merged_QCD_bins_$versQCD
 hadd -f mergedHistos.root ../QCD_1000_1400_$versPatQCD/mergedHistos.root ../QCD_120_170_$versPatQCD/mergedHistos.root  ../QCD_170_300_$versPatQCD/mergedHistos.root ../QCD_1800_$versPatQCD/mergedHistos.root ../QCD_300_470_$versPatQCD/mergedHistos.root ../QCD_470_600_$versPatQCD/mergedHistos.root ../QCD_600_800_$versPatQCD/mergedHistos.root ../QCD_800_1000_$versPatQCD/mergedHistos.root 
 cd ..


 mkdir Merged_QCD_PhotonJet_$versQCD
 cd Merged_QCD_PhotonJet_$versQCD
 hadd -f mergedHistos.root ../Merged_QCD_bins_$versQCD/mergedHistos.root ../PhotonJet_$versPatQCD/mergedHistos.root
 cd ..

 mkdir Merged_EWKandQCD_$vers
 cd Merged_EWKandQCD_$vers
 hadd -f mergedHistos.root ../Merged_EWK_$vers/mergedHistos.root ../Merged_QCD_PhotonJet_$versQCD/mergedHistos.root
 cd ..

 mkdir Merged_AllSM_$vers
 cd Merged_AllSM_$vers
 hadd -f mergedHistos.root ../Merged_EWK_$vers/mergedHistos.root ../Merged_QCD_PhotonJet_$versQCD/mergedHistos.root ../PhotonVJets_$versPat/mergedHistos.root
 cd ..


 mkdir Merged_GGM_A_AllSM_$vers
 cd Merged_GGM_A_AllSM_$vers
 hadd -f mergedHistos.root ../Merged_AllSM_$vers/mergedHistos.root ../GGM_A_V20/histoGGMA.root
 cd ..

 mkdir Merged_GGM_B_AllSM_$vers
 cd Merged_GGM_B_AllSM_$vers
 hadd -f mergedHistos.root ../Merged_AllSM_$vers/mergedHistos.root ../GGM_B_V20/histoGGMB.root
 cd ..




fi

cd ..
