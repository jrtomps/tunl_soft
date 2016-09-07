
#include "DataManager.hh"

#include "TFile.h"
#include "TTree.h"
#include "TString.h"

DataManager* DataManager::GetInstance()
{ static DataManager *pointerToTheSingletonInstance = new DataManager();
  return pointerToTheSingletonInstance;
}


//-----------------------------------------------------------------------
void DataManager::open(Int_t rn)
{

  TString fRootFilePath = getenv("RELEASE_ROOT_FILE_PATH");
  fFileName = fRootFilePath+Form("/run%d_tree.root", rn);
  
  fFile = new TFile(fFileName, "RECREATE");

  TString tree_comment;
  tree_comment = Form("Raw Data tree, Run # %d", rn);

  fEventTree = new TTree("event_tree", tree_comment);
  fEventTree->SetDirectory(fFile);
  //  fEventTree->SetAutoSave(20480000);   // autosave when every 20Mb
  //fEventTree->SetAutoFlush(-30000000); //flush baskets to disk every 30 MB
  // fEventTree->SetCacheSize(1000);   //set a 10 MBytes cache 

  fEventTree->Branch("EventBranch", "RawData", &fEvent, 1024000, 99);

  fEvent        = new RawData;

  fRunInfo      = new RunInfo;
  fStartInfo    = new RunControlEvent;
  fEndInfo      = new RunControlEvent;
}

//---------------------------------------------------
void DataManager::close()
{
  if(fFile)
    {
      fRunInfo->Write();
      fStartInfo->Write();
      fEndInfo->Write();
      fFile->Write(); 
      fFile->Close();
    }
  if(fRunInfo)   delete fRunInfo;
  if(fStartInfo) delete fStartInfo;
  if(fEndInfo)   delete fEndInfo;
  if(fEvent)     delete fEvent;
}

//-------------------------------------------
void DataManager::FillEvent()
{
  fEventTree->Fill();
}

