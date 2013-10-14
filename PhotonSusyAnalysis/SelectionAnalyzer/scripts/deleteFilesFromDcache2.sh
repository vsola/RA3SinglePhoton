#!/bin/bash
#DBSInvalidateDataset.py  --DBSURL=https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet --files --datasetPath=


#dirnameTrees=(JetMon)
#dirnameTrees=(SinglePhoton)
#dirnameTrees=(SingleElectron)
dirnameTrees=(PhotonSusyAnalysis)

ini dctools


for dirnameTree in ${dirnameTrees[@]}
  do

  namesfound=`dcls /pnfs/desy.de/cms/tier2/store/user/vsola/$dirnameTree`
  echo "DIRs:"$namesfound

  for dir in ${namesfound[@]}
    do

    echo "DIR: "$dir
    namesub=`dcls /pnfs/desy.de/cms/tier2/store/user/vsola/$dirnameTree/$dir`

    for name in ${namesub[@]}
      do

      echo "NAME:"$name
      filesfound=`dcls /pnfs/desy.de/cms/tier2/store/user/vsola/$dirnameTree/$dir/$name/`

      echo "start filename"
      for foundfile in $filesfound
	do
	echo "file found:" $foundfile
	dcdel /pnfs/desy.de/cms/tier2/store/user/vsola/$dirnameTree/$dir/$name/$foundfile
      done
      echo "endo of filename"

      srmrmdir srm://dcache-se-cms.desy.de:8443//pnfs/desy.de/cms/tier2/store/user/vsola/$dirnameTree/$dir/$name/
    done

    srmrmdir srm://dcache-se-cms.desy.de:8443//pnfs/desy.de/cms/tier2/store/user/vsola/$dirnameTree/$dir/
  done
 
  srmrmdir srm://dcache-se-cms.desy.de:8443//pnfs/desy.de/cms/tier2/store/user/vsola/$dirnameTree/
done
