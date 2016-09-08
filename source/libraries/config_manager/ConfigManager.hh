#ifndef ConfigManager_h
#define ConfigManager_h 1 

#include <map>
#include "ConfigElements.hh"

class TXMLEngine;

typedef std::map<int, ROModel> ROModelTable;
typedef std::map<int, ROModel>::iterator ROTableIter;

typedef std::map<int, SubSystem> TranslationTable;
typedef std::map<int, SubSystem>::iterator TTableIter;

typedef std::map<std::string, ROModelAttributes> ROModelAttrTable;
typedef std::map<std::string, ROModelAttributes>::iterator AttrTableIter;

class ConfigManager
{
public:
  static ConfigManager* GetInstance();

private:
  ConfigManager();
  ConfigManager(ConfigManager const& );             //not defined, 
                                                    // not copyable

  ConfigManager& operator= (ConfigManager const& ); //not defined, 
                                                    // not assignable
public:
  ~ConfigManager(); 
  void ReadXMLfile(const char* filename);
  void DumpConfig();
  bool GetFlatTreeFlag(){return fFlatTreeFlag;}

  ROTableIter GetROModel(int roc, int crate, int slot);
  ROTableIter GetROModelEnd(){return fRO_TableEnd;}
  ROTableIter GetROModelBegin(){return fRO_TableBegin;}

  TTableIter GetTTElement(int index, int channel);
  TTableIter GetTranslationTableEnd(){return fTT_end;}
  TTableIter GetTranslationTableBegin(){return fTT_begin;}

  AttrTableIter GetROAttributes(std::string model);
  AttrTableIter GetROAttrTableEnd(){return fAttrTableEnd;};
  AttrTableIter GetROAttrTableBegin(){return fAttrTableBegin;}
private:
  TXMLEngine*        fXML_Engine;

  ROModelTable       fRO_ModelTable;
  ROTableIter        fRO_TableIter;
  ROTableIter        fRO_TableEnd;
  ROTableIter        fRO_TableBegin;

  ROModelAttrTable   fROModelAttrTable;
  AttrTableIter      fAttrTableIter;
  AttrTableIter      fAttrTableEnd;
  AttrTableIter      fAttrTableBegin;

  TranslationTable   fTranslationTable;
  TTableIter         fTT_iter;
  TTableIter         fTT_end;
  TTableIter         fTT_begin;

  ROModel*           fRO_ModelElement;
  ROModelAttributes* fROAttrElement;
  SubSystem*         fTT_Element;

  bool               fFlatTreeFlag;

private:  
  void LoadROModelTable(void* node);
  void LoadTranslationTable(void* node);
  void LoadROAttributeTable(void* node);
};


namespace
{ struct ForceSingletonInitialization
  { ForceSingletonInitialization() { ConfigManager::GetInstance(); } } GetInstance;
}

#endif
