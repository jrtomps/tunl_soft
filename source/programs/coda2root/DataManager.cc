
#include "DataManager.hh"

#include "TFile.h"
#include "TTree.h"
#include "TString.h"

DataManager* DataManager::GetInstance()
{ static DataManager *pointerToTheSingletonInstance = new DataManager();
  return pointerToTheSingletonInstance;
}


//-----------------------------------------------------------------------
void DataManager::open(Int_t rn, bool flag)
{

  TString fRootFilePath = getenv("RELEASE_ROOT_FILE_PATH");
  fFileName = fRootFilePath+Form("/run%d_tree.root", rn);
  
  fFile = new TFile(fFileName, "RECREATE");

  TString tree_comment;
  tree_comment = Form("Raw Data tree, Run # %d", rn);

  fEventTree = new TTree("event_tree", tree_comment);
  fEventTree->SetDirectory(fFile);
  fEventTree->SetAutoSave(100000000); // autosave when every 10Mb
  //  fEventTree->SetAutoSave(100000); // autosave when every 1Mb
  //  fEventTree->AutoSave("SaveSelf");
  // fEventTree->SetAutoFlush(30000000);
  // fEventTree->SetCacheSize(1000); //set a 10 MBytes cache 
                                      //(useless when writing local files)
 
  //  fEventTree->Branch("EventBranch", "RawData", &fEvent, 32000, 2);
  fEventTree->Branch("EventBranch", "RawData", &fEvent,1024000, 2);

  fEvent        = new RawData;

  fRunInfo      = new RunInfo;
  fStartInfo    = new RunControlEvent;
  fEndInfo      = new RunControlEvent;

   fFlatTreeFlag=flag;
   if(fFlatTreeFlag)
     {
     fFlatTree = new TTree("flat_tree", tree_comment);
     fFlatTree->SetDirectory(fFile);
     fFlatTree->SetAutoSave(1000000);//autosave every 1 MB
     //     fFlatTree->AutoSave("SaveSelf");
     //     fFlatTree->AutoSave();
     }
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
  //S. Stave modification 3/8/10
  //Don't fill regular tree if flattree is being filled
  if(!fFlatTreeFlag)
    fEventTree->Fill();
  if(fFlatTreeFlag)
    fFlatTree->Fill();
}

void DataManager::AutoSaveTree()
{
  //  fFlatTree->AutoSave("SaveSelf");
  fFlatTree->AutoSave("");
}

//-----------------------------------------------------

void DataManager::AddFlatTreeBranch(const char* name, void* address, const char* leaflist)
{
  fFlatTree->Branch(name, address, leaflist);
}
