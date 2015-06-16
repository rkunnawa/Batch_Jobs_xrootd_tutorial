# Batch_Jobs_xrootd_tutorial

Get a CMSSW_5_3_20 environment: 
$ cmsrel CMSSW_5_3_20
$ cd CMSSW_5_3_20/src/
$ cmsenv
$ voms-proxy-init --voms cms -hours 120 
the last command makes sure you have a proxy for a long time 

pull this repository

The sample macro reads a text file and plots simple histogram with the loop structure. make sure you change the macro to do what you want. 

the number of jobs and files per job are mentioned in the lxplusbatchscript.sh as nJobs and in the line "start=i*2" where 2 is the files read per job. We are reading a file, getting information from it and then closing that file before going on to the next one. 
