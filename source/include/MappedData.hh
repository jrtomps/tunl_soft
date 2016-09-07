
#ifndef MappedData_HH 
#define MappedData_HH 1

#include "DataStructure.hh"
#include "ConfigElements.hh"

#include <string>

class ConfigManager;

class MappedData:public HardwareData
{
  //class that maps the "roc", "slot", "crate", 
  //(this 3 numbers are equivalent to the "index" 
  //in readout model table) channel pairs to 
  //detector name detector id pairs; plus some additional functionality

public:
  MappedData();
  MappedData(const HardwareData& d);
  ~MappedData(){};

public:

  void Map(HardwareData* p);

  inline std::string GetSubSystemName()     {return fSubSystem->GetName();}
  inline std::string GetSubSytemAttr()      {return fSubSystem->GetAttr();}
  inline int GetID()                        {return fSubSystem->GetID();}

private:
  ConfigManager* fConfigManager;
  SubSystem*     fSubSystem;  
};

#endif
