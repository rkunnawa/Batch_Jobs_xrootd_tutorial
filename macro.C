//  Raghav Kunnawalkam Elayavalli
//  created: 21th Feb 2014

//  sample macro to read in forest files from a file list which is given to us through a condor script. the output file will 
//  be sent to hadoop. 

#include <iostream>
#include <fstream>
#include <TRandom.h>
#include <TH1F.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TTree.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TFile.h>
#include <TStyle.h>
#include <TStopwatch.h>
#include <TRandom3.h>
#include <TChain.h>
#include <TProfile.h>
#include <TStopwatch.h>
#include <TCut.h>
#include <cstdlib>
#include <cmath>
#include "TLegend.h"
#include "TLatex.h"
#include "TMath.h"
#include "TLine.h"

using namespace std;

TStopwatch timer;

void macro(const int startfile=0, const int endfile=1){

  TH1::SetDefaultSumw2();
  bool printDebug = true;
  
  timer.Start();
  
  //create the trees and set the branch address
  //jet tree
  int nrefe;
  float pt[1000];
  //float old_pt3[1000];
  float raw[1000];
  float eta[1000];
  float phi[1000];


  //event tree
  int evt;
  int run;
  int lumi;
  float vz;


  std::string infile;
  
  infile = "jetRAA_pp_mc_forest.txt";
  
  std::ifstream instr(infile.c_str(), std::ifstream::in);
  
  std::string filename;
  int nFiles = endfile - startfile;
  
  cout<<"Running on "<<nFiles<<" forest files"<<endl;
  // we are not TChaining here since its easier to just open and close one file at a time. 
  
  //just to read the files till the start number. 
  cout<<"reading from "<<startfile<<" to "<<endfile<<endl;  
  for(int ifile=0;ifile<startfile;ifile++){
    instr >> filename;
  }

  //output file:
  TFile f(Form("test_outputFile_%d.root",endfile),"RECREATE");

  // declare the output histograms/ntuples or whatever you want
  TH1F * hvz = new TH1F("hvz","",40,-20, 20);

  //now we are taking only the files from the given start number to the end number. 
  for(int ifile=startfile;ifile<endfile;ifile++){
    instr >> filename;
    
    cout<<"File: "<<filename<<std::endl;

    TFile *fin = TFile::Open(filename.c_str());
    
    TTree* jetTree = (TTree*)fin->Get("akPu3PFJetAnalyzer/t");
    TTree* skimTree_in = (TTree*)fin->Get("skimanalysis/HltTree");
    //TTree* trackTree_in = (TTree*)fin->Get("ppTrack/trackTree");
    TTree* evtTree_in = (TTree*)fin->Get("hiEvtAnalyzer/HiTree");
    TTree* hltTree_in = (TTree*)fin->Get("hltanalysis/HltTree");
    
    jetTree->AddFriend(evtTree_in);

    jetTree->SetBranchAddress("evt",&evt);
    jetTree->SetBranchAddress("run",&run);
    jetTree->SetBranchAddress("lumi",&lumi);
    jetTree->SetBranchAddress("vz",&vz);
   
    jetTree->SetBranchAddress("nref",&nrefe);
    jetTree->SetBranchAddress("jtpt",&pt);
    jetTree->SetBranchAddress("jteta",&eta);
    jetTree->SetBranchAddress("jtphi",&phi);

    Long64_t nentries = jetTree->GetEntries();
    if(printDebug)nentries = 100;
    
    for (int i = 0; i < nentries; i++){ //start of event loop. 

      jetTree->GetEntry(i);
      if(i%1000==0)cout<<"event = "<<i<<"; run = "<<run<<endl;

      // apply your event selection cuts here:
      if(fabs(vz)>15) continue;
      hvz->Fill(vz);

      // jet loop
      for(int g = 0; g<nrefe; ++g){

	// fill your jet histograms here: 
	
      }
      
    }// event loop 
    
    fin->Close();
    
  }//end of file loop
  f.cd();
  f.Write();
  f.Close();

  timer.Stop();
  float rtime  = timer.RealTime();
  float ctime  = timer.CpuTime();
  
  std::cout<<"\t"<<std::endl;
  std::cout<<Form("RealTime=%f seconds, CpuTime=%f seconds",rtime,ctime)<<std::endl;
  std::cout<<"\t"<<std::endl;
  std::cout<<"Good bye : " <<"\t"<<std::endl;
  
}
