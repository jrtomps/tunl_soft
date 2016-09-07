#include "MappedData.hh"
#include "ConfigManager.hh"

#ifdef VERBOSE_MAPPING
#include <iostream>
#endif

using namespace std;

MappedData::MappedData():HardwareData()
{
  fConfigManager = ConfigManager::GetInstance();
}

MappedData::MappedData(const HardwareData& d):HardwareData(d)
{
  fConfigManager = ConfigManager::GetInstance();
}

void MappedData::Map(HardwareData* p)
{
  SetIndex(p->GetIndex());
  SetChannel(p->GetChannel());
  SetValue(p->GetValue());

  TTableIter iter = fConfigManager->GetTTElement(p->GetIndex(), p->GetChannel());
  if(iter!=fConfigManager->GetTranslationTableEnd())
     {
       int key = iter->first;
#ifdef VERBOSE_MAPPING
       cout<<dec<<"index "<<((key&0x0000FF00)>>8)<<", ch "<<(key&0x000000FF);
#endif
       fSubSystem = &(iter->second);
#ifdef VERBOSE_MAPPING
       cout<<", id "<<fSubSystem->GetID()<<", attribute "<<fSubSystem->GetAttr()<<", name "<<fSubSystem->GetName()<<endl;
#endif
    }
}
