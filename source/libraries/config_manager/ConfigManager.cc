#include "ConfigManager.hh"
#include "ConfigElements.hh"
#include "TXMLEngine.h"

#include <iostream>

//#define DEBUG_CONFIG 1

using namespace std;

ConfigManager* ConfigManager::GetInstance()
{ static ConfigManager *pointerToTheSingletonInstance = new ConfigManager();
  return pointerToTheSingletonInstance;
}

//__________________________________________________________

ConfigManager::ConfigManager()
{
  fXML_Engine=0;

  fRO_ModelElement  = new ROModel();
  fROAttrElement    = new ROModelAttributes();
  fTT_Element       = new SubSystem();
}
//_________________________________________________________
ConfigManager::~ConfigManager()
{
  if(fRO_ModelElement) delete fRO_ModelElement;
  if(fROAttrElement)   delete fROAttrElement;
  if(fTT_Element)      delete fTT_Element;
}


void ConfigManager::ReadXMLfile(const char* filename)
{  
  fRO_ModelTable.clear();
  fTranslationTable.clear();
  fROModelAttrTable.clear();

  fXML_Engine=new TXMLEngine();

  // Trying to parse xml file
  // Only file with restricted xml syntax are supported
  XMLDocPointer_t xmldoc = fXML_Engine->ParseFile(filename);
  if (xmldoc==0)
    {
      cout<<" Failed to open file "<<filename<<endl;
      return;
    }
  
  // take access to main node  
  XMLNodePointer_t mainnode = fXML_Engine->DocGetRootElement(xmldoc);

  XMLNodePointer_t  child = fXML_Engine->GetChild(mainnode);

  string NodeName="";

  while(child!=NULL){
    NodeName = fXML_Engine->GetNodeName(child);
  
    if(NodeName=="ROModelTable")LoadROModelTable(child);
    if(NodeName=="TranslationTable")LoadTranslationTable(child);
    if(NodeName=="ROModelAttributes")LoadROAttributeTable(child);
    if(NodeName=="FlatTreeFlag")
      if(strcmp(fXML_Engine->GetNodeContent(child), "yes")==0)
	fFlatTreeFlag=true;
      else
	fFlatTreeFlag=false;
    
    child = fXML_Engine->GetNext(child);
  }

  // Release memory before exit
  fXML_Engine->FreeDoc(xmldoc);
  if(fXML_Engine)delete fXML_Engine;
}
//____________________________________________________________________________

void ConfigManager::LoadROModelTable(XMLNodePointer_t node)
{  
  XMLNodePointer_t  child = fXML_Engine->GetChild(node);

  char roc=0, crate=0, slot=0;
  int tmp=0;
 
  if(child==0) return;
  while(child!=NULL){
#ifdef DEBUG_CONFIG
    cout<<fXML_Engine->GetAttr(child,"index")<<" "
	<<fXML_Engine->GetAttr(child,"roc")<<" "
	<<fXML_Engine->GetAttr(child,"crate")<<" "
	<<fXML_Engine->GetAttr(child,"slot")<<" "
	<<fXML_Engine->GetAttr(child,"ch_min")<<" "
	<<fXML_Engine->GetAttr(child,"ch_max")<<" "
	<<fXML_Engine->GetAttr(child,"model")<<endl;
#endif
    roc   = atoi(fXML_Engine->GetAttr(child,"roc"));
    crate = atoi(fXML_Engine->GetAttr(child,"crate"));
    slot  = atoi(fXML_Engine->GetAttr(child,"slot"));

    fRO_ModelElement->SetIndex(atoi(fXML_Engine->GetAttr(child,"index")));
    fRO_ModelElement->SetMinCh(atoi(fXML_Engine->GetAttr(child,"ch_min")));
    fRO_ModelElement->SetMaxCh(atoi(fXML_Engine->GetAttr(child,"ch_max")));
    fRO_ModelElement->SetModel(fXML_Engine->GetAttr(child,"model"));
    
    tmp = (roc<<16)+(crate<<8)+slot;
    fRO_ModelTable.insert(std::pair<int, ROModel>(tmp, *fRO_ModelElement));

    child = fXML_Engine->GetNext(child);
  } 

  fRO_TableEnd    = fRO_ModelTable.end();
  fRO_TableBegin  = fRO_ModelTable.begin();
}

//______________________________________________________________

void ConfigManager::LoadROAttributeTable(XMLNodePointer_t node)
{
  XMLNodePointer_t  child = fXML_Engine->GetChild(node);

  string model="";
 
  if(child==0) return;
  while(child!=NULL){
#ifdef DEBUG_CONFIG
    cout<<fXML_Engine->GetAttr(child,"model")<<" "
	<<fXML_Engine->GetAttr(child,"header")<<" "
	<<fXML_Engine->GetAttr(child,"data_mask")<<" "
	<<fXML_Engine->GetAttr(child,"chan_mask")<<" "
	<<fXML_Engine->GetAttr(child,"chan_shift")<<endl;
#endif

    model   = fXML_Engine->GetAttr(child,"model");

    fROAttrElement->SetHeader(strtol(fXML_Engine->GetAttr(child,"header"), 0, 10));
    fROAttrElement->SetDataMask(strtol(fXML_Engine->GetAttr(child,"data_mask"), 0, 16));
    fROAttrElement->SetChanMask(strtol(fXML_Engine->GetAttr(child,"chan_mask"), 0, 16));
    fROAttrElement->SetChanShift(strtol(fXML_Engine->GetAttr(child,"chan_shift"), 0, 10));
   
    for(fRO_TableIter= fRO_TableBegin; fRO_TableIter!=fRO_TableEnd; fRO_TableIter++)
      {
	if(model == (fRO_TableIter->second).GetModel())  
	  fROModelAttrTable.insert(std::pair<string, ROModelAttributes>(model, *fROAttrElement));
      }

    child = fXML_Engine->GetNext(child);
  } 

  fAttrTableEnd   = fROModelAttrTable.end();
  fAttrTableBegin = fROModelAttrTable.begin();
}


//_____________________________________________________________

void ConfigManager::LoadTranslationTable(XMLNodePointer_t node)
{ 
  XMLNodePointer_t  child = fXML_Engine->GetChild(node);

  char index=0, channel=0;
  int tmp=0;
  
  if(child==0) return;
  while(child!=NULL){
#ifdef DEBUG_CONFIG
    cout<<fXML_Engine->GetAttr(child,"index")<<" "
	<<fXML_Engine->GetAttr(child,"ch")<<" "
	<<fXML_Engine->GetAttr(child,"id")<<" "
	<<fXML_Engine->GetAttr(child,"attribute")<<" "
	<<fXML_Engine->GetAttr(child,"name")<<endl;
#endif
    index   = atoi(fXML_Engine->GetAttr(child,"index"));
    channel = atoi(fXML_Engine->GetAttr(child,"ch"));
    //S. Stave: Ignore the ID in the ro_config.xml file
    //    fTT_Element->SetID(atoi(fXML_Engine->GetAttr(child,"id")));
    fTT_Element->SetAttr(fXML_Engine->GetAttr(child,"attribute"));
    fTT_Element->SetName(fXML_Engine->GetAttr(child,"name"));
    
    tmp = (index<<8)+channel;
    fTranslationTable.insert(std::pair<int, SubSystem>(tmp, *fTT_Element));
    
    child = fXML_Engine->GetNext(child);
  }

  fTT_end         = fTranslationTable.end();
  fTT_begin       = fTranslationTable.begin();  
}
//______________________________________________________________

ROTableIter ConfigManager::GetROModel(int roc, int crate, int slot)
{
  return fRO_ModelTable.find((roc<<16)+(crate<<8)+slot);
}

//______________________________________________________________

TTableIter ConfigManager::GetTTElement(int index, int channel)
{
  return fTranslationTable.find((index<<8)+channel);
}


//______________________________________________________________

AttrTableIter ConfigManager::GetROAttributes(string model)
{
  return fROModelAttrTable.find(model);
}

//__________________________________________________________
void ConfigManager::DumpConfig()
{
  for(fRO_TableIter= fRO_TableBegin; fRO_TableIter!=fRO_TableEnd; fRO_TableIter++)
    {
      int key = fRO_TableIter->first;
      ROModel ro_element = fRO_TableIter->second;
      cout<<dec<<"index "<<ro_element.GetIndex();
      cout<<", roc "<<((key&0x00FF0000)>>16)<<", crate "<<((key&0x0000FF00)>>8)<<", slot "<<(key&0x000000FF);
      cout<<", ch_min "<<ro_element.GetMinCh()<<", ch_max "<<ro_element.GetMaxCh()<<", model "<<ro_element.GetModel()<<endl;
    }

  for(fTT_iter=fTT_begin; fTT_iter!=fTT_end; fTT_iter++)
    {
      int key = fTT_iter->first;
      cout<<dec<<"index "<<((key&0x0000FF00)>>8)<<", ch "<<(key&0x000000FF);
      SubSystem tt_element = fTT_iter->second;
      cout<<", id "<<tt_element.GetID()<<", attribute "<<tt_element.GetAttr()<<", name "<<tt_element.GetName()<<endl;
    }

  for(fAttrTableIter=fAttrTableBegin; fAttrTableIter!=fAttrTableEnd; fAttrTableIter++)
    {     
      ROModelAttributes ro_model_attrib = fAttrTableIter->second;
      cout<<"model "<<fAttrTableIter->first<<", header "<<ro_model_attrib.GetHeader()
	  <<", data_mask "<<hex<<showbase<<ro_model_attrib.GetDataMask()
	  <<", chan_mask "<<ro_model_attrib.GetChanMask()
	  <<", chan_shift "<<dec<<ro_model_attrib.GetChanShift()<<endl;
    }
}





