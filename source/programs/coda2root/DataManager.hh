#ifndef DataManager_h
#define DataManager_h 1

#include "DataStructure.hh"

class TTree;
class TFile;

class DataManager //a singleton class
{
public:
    static DataManager* GetInstance();

private:
  DataManager():fFile(0), fFileName(0), fEventTree(0), fEvent(0), fRunInfo(0), fStartInfo(0), fEndInfo(0){}
  DataManager(DataManager const& ); //not defined, not copyable
  DataManager& operator= (DataManager const& ); //not defined, not assignable
  ~DataManager(){};

private:
  TFile*           fFile; 
  TString          fFileName;
  TTree*           fEventTree;

  RawData*         fEvent;

  RunInfo*         fRunInfo;
  RunControlEvent* fStartInfo;
  RunControlEvent* fEndInfo;
  //legacy tree support
  bool             fFlatTreeFlag;
  TTree*           fFlatTree;
public:
  void open(Int_t RN, bool flag);

  void close();
  void SetFileName(TString name) { fFileName=name; }


  RunInfo* GetRunInfo()          { return fRunInfo;   }
  RunControlEvent* GetStartInfo(){ return fStartInfo; }
  RunControlEvent* GetEndInfo()  { return fEndInfo;   }
  RawData* GetEvent()            { return fEvent;     }
  TFile*   GetRootFilePtr()      { return fFile;      }

  void AddFlatTreeBranch(const char* name, void* address, const char* leaflist);
  
  void FillEvent();
  void AutoSaveTree();

};

namespace
{ struct ForceSingletonInit
  { ForceSingletonInit() { DataManager::GetInstance(); } } Instance;
}

#endif




