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

public:
  void open(Int_t RN);

  void close();
  inline void SetFileName(TString name) { fFileName=name; }

  inline RunInfo* GetRunInfo()          { return fRunInfo;   }
  inline RunControlEvent* GetStartInfo(){ return fStartInfo; }
  inline RunControlEvent* GetEndInfo()  { return fEndInfo;   }
  inline RawData* GetEvent()            { return fEvent;     }

  void FillEvent();

};

namespace
{ struct ForceSingletonInit
  { ForceSingletonInit() { DataManager::GetInstance(); } } Instance;
}

#endif




