#!/bin/bash
#DBSInvalidateDataset.py  --DBSURL=https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet --files --datasetPath=

#dirnameTrees=(WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball/photonJetSel_WJetsToLNu_V09)
#dirnameTrees=(PhotonHad/photonJetSel_2012A_22Jan_T02)
#dirnameTrees=(TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola/photonJetSel_TTJets_MassiveBin_V08)
#dirnameTrees=(GVJets_Incl_8TeV-madgraph/photonJetSel_GVJets_Incl_V08)
dirnameTrees=(HT/HTTrigger_2012A_22Jan2013_V01)

#dirnameTrees=(PhotonSusyAnalysis)


ini dctools

for dirnameTree in ${dirnameTrees[@]}
  do

  namesfound=`dcls /pnfs/desy.de/cms/tier2/store/user/vsola/$dirnameTree`

  for name in ${namesfound[@]}
    do
    echo "NAME:"$name
    echo "File:" `dcls /pnfs/desy.de/cms/tier2/store/user/vsola/$dirnameTree`
 
    filesfound=`dcls /pnfs/desy.de/cms/tier2/store/user/vsola/$dirnameTree/$name/`

    echo "start filename"
    for foundfile in $filesfound
      do
      echo "file found:" $foundfile
#     echo "delete file:" dcdel /pnfs/desy.de/cms/tier2/store/user/vsola/$dirnameTree/$name/$foundfile
      dcdel /pnfs/desy.de/cms/tier2/store/user/vsola/$dirnameTree/$name/$foundfile
    done
    echo "endo of filename"

    srmrmdir srm://dcache-se-cms.desy.de:8443//pnfs/desy.de/cms/tier2/store/user/vsola/$dirnameTree/$name/
  done
 
  srmrmdir srm://dcache-se-cms.desy.de:8443//pnfs/desy.de/cms/tier2/store/user/vsola/$dirnameTree/
done
