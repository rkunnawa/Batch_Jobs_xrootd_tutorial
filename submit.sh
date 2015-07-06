#!/bin/bash

cd /afs/cern.ch/work/i/ihuntisa/xrootd/CMSSW_5_3_20/src/Batch_Jobs_xrootd_tutorial/
#cmsenv
eval `scramv1 runtime -sh`


#Added by Ian
export X509_USER_PROXY=~/x509_user_proxy/proxy
voms-proxy-init --noregen
#</Ian>

cd /afs/cern.ch/work/i/ihuntisa/xrootd/CMSSW_5_3_20/src/Batch_Jobs_ xrootd_tutorial/

echo "root -l -b -q macro.C++"
echo "First = $FIRST and last file = $LAST"   

root -b > macro${FIRST}.log <<EOF
.x macro.C($FIRST,$LAST);
.q
EOF


echo "Done all jobs!"

#destination="/path/to/output/file/"

#echo "Copying output files to " $destination

#mv test_outputFile_$LAST.root $destination 

