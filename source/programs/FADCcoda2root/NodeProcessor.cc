#include "NodeProcessor.hh"
#include "DataStructure.hh"
#include "ConfigManager.hh"
#include "DataManager.hh"

using namespace std;
using namespace evio;


NodeProcessor::NodeProcessor()
{
  fConfigManager = ConfigManager::GetInstance();
  fDataManager =  DataManager::GetInstance();
     
  fEvent = fDataManager->GetEvent();
  fHardwareData = new HardwareData;
}

//-------------------------------------------------

bool NodeProcessor::isEventID(const evioDOMNodeP nodePtr)
{ 
  bool flag=false;
  if(nodePtr->tag==0xC000 && nodePtr->getContentType()==1 && nodePtr->num==0) 
    {
#ifdef DEBUG_PARSER
      cout<<"Event ID bank:::->>  ";
#endif
      fEvent->Clear("C");
      flag=true;
      const vector<uint32_t> *vec = nodePtr->getVector<uint32_t>();
      if(vec!=0) 
	{
	  fEvent->SetEventNumber((*vec)[0]);
	  fEvent->SetRunNumber(fRunInfo->GetRunNumber());
	  fEvent->SetEventName("Physics");

#ifdef DEBUG_PARSER
	  cout  << dec<<"EventNumber = "<< (*vec)[0] 
		<<", EventCalss = "<<  (*vec)[1]
		<<", EventStatus = "<< (*vec)[2]<<endl;
#endif
	} 
      else 
	cerr << "?getVector<int> returned NULL" << endl;
    }
  return flag;
}

bool NodeProcessor::isSyncEvent(const evioDOMNodeP nodePtr)
{ 
  bool flag=false;
  if(nodePtr->tag==16 && nodePtr->getContentType()==1 && nodePtr->num==0xCC) 
    {
#ifdef DEBUG_PARSER
      cout<<"SyncEvent:"<<endl;
#endif
      flag=true;
    }
  return flag;
}

bool NodeProcessor::isPreStartEvent(const evioDOMNodeP nodePtr)
{
  bool flag=false;
  if(nodePtr->tag==17 && nodePtr->getContentType()==1 && nodePtr->num==0xCC) 
    {
#ifdef DEBUG_PARSER    
      cout<<"PreStartEvent:::->>  ";
#endif
      fRunInfo = fDataManager->GetRunInfo();
      fRunInfo->SetName("RunInfo");

      flag=true;
      const vector<uint32_t> *vec = nodePtr->getVector<uint32_t>();
      if(vec!=0) 
	{
	  fRunInfo->SetTime((*vec)[0]);
	  fRunInfo->SetRunNumber((*vec)[1]);
	  fRunInfo->SetRunType("test");

#ifdef DEBUG_PARSER
	  cout  << dec<<"Time = " << (*vec)[0] 
		<<", RunNumber = "<< (*vec)[1]
		<<", RunType = "  << (*vec)[2]<<endl;
#endif
	} 
      else 
	cerr << "?getVector<int> returned NULL" << endl;
    }
  return flag;
}

bool NodeProcessor::isGoEvent(const evioDOMNodeP nodePtr)
{
  bool flag=false;
  if(nodePtr->tag==18 && nodePtr->getContentType()==1 && nodePtr->num==0xCC)
    { 
#ifdef DEBUG_PARSER    
      cout<<"GoEvent:::->>  ";
#endif
      fStartInfo = fDataManager->GetStartInfo();
      fStartInfo->SetName("StartInfo");

      flag=true;
      const vector<uint32_t> *vec = nodePtr->getVector<uint32_t>();
      if(vec!=0) 
	{
	  fStartInfo->SetTime((*vec)[0]);
	  fStartInfo->SetNumEvents((*vec)[2]);
#ifdef DEBUG_PARSER    
	  cout  << dec<<"Time = " << (*vec)[0] 
		<<", Reserved internal variable = "<< (*vec)[1]
		<<", NumberOfEvents = "  << (*vec)[2]<<endl;
#endif
	} 
      else 
	cerr << "?getVector<int> returned NULL" << endl;
    }
  return flag;
}

bool NodeProcessor::isPauseEvent(const evioDOMNodeP nodePtr)
{
  bool flag=false;
  if(nodePtr->tag==19 && nodePtr->getContentType()==1 && nodePtr->num==0xCC) 
    {
#ifdef DEBUG_PARSER    
      cout<<"PauseEvent:::->>  ";
#endif
      flag=true;
      const vector<uint32_t> *vec = nodePtr->getVector<uint32_t>();
      if(vec!=0) 
	{
#ifdef DEBUG_PARSER
	  cout  << dec<<"Time = " << (*vec)[0] 
		<<", Reserved internal variable = "<< (*vec)[1]
		<<", NumberOfEvents = "  << (*vec)[2]<<endl;
#endif
	} 
      else 
	cerr << "?getVector<int> returned NULL" << endl;
    }

  return flag;
}

bool NodeProcessor::isEndEvent(const evioDOMNodeP nodePtr)
{
  bool flag=false;
  if(nodePtr->tag==20 && nodePtr->getContentType()==1 && nodePtr->num==0xCC)
    {
#ifdef DEBUG_PARSER    
      cout<<"EndEvent:::->>  ";
#endif
      fEndInfo = fDataManager->GetEndInfo();
      fEndInfo->SetName("EndInfo");

      flag=true;
      const vector<uint32_t> *vec = nodePtr->getVector<uint32_t>();
      if(vec!=0) 
	{
	  fEndInfo->SetTime((*vec)[0]);
	  fEndInfo->SetNumEvents((*vec)[2]);
#ifdef DEBUG_PARSER    
	  cout  << dec<<"Time = " << (*vec)[0] 
		<<", Reserved internal variable = "<< (*vec)[1]
		<<", NumberOfEvents = "  << (*vec)[2]<<endl;
#endif
	} 
      else 
	cerr << "?getVector<int> returned NULL" << endl;
    }
  return flag;
}

bool NodeProcessor::isPhysicsEvent(const evioDOMNodeP nodePtr)
{
  bool flag=false;
  if(nodePtr->getContentType()==16 && nodePtr->num==204) 
    { 
      flag=true;
#ifdef DEBUG_PARSER
      cout<<"Found a PhysicsEvent: tag = "<<hex<<showbase<<nodePtr->tag<<endl;
#endif
    }
  return flag;
}



//--------------------------------------------------------------------
void NodeProcessor::parse_word(uint32_t longword, int DATA_MASK, int chanL, int chanU)
{
  // sequential readout
  int word  =  longword & 0x0000FFFF;
  int wordU = (longword & 0xFFFF0000) >> 16;

  int data_val = wordU & DATA_MASK;

  fHardwareData->SetChannel(chanU);
  fHardwareData->SetValue(data_val);


  TTableIter iter = fConfigManager->GetTTElement(fHardwareData->GetIndex(), chanU);
  if(iter!=fConfigManager->GetTranslationTableEnd())
    {
      fHardwareData->SetID((&(iter->second))->GetID());
      fHardwareData->SetAttribute(((&(iter->second))->GetAttr()).data());
      fHardwareData->SetName(((&(iter->second))->GetName()).data());
    }
  fEvent->AddHardwareData(fHardwareData);

#ifdef DEBUG_PARSER
  cout<<"channel = "   <<dec<< chanU
      << " data_val = "<<dec<< data_val << endl;
#endif

  data_val = word & DATA_MASK;

  fHardwareData->SetChannel(chanL);
  fHardwareData->SetValue(data_val);
  iter = fConfigManager->GetTTElement(fHardwareData->GetIndex(), chanL);
  if(iter!=fConfigManager->GetTranslationTableEnd())
    {
      fHardwareData->SetID((&(iter->second))->GetID());
      fHardwareData->SetAttribute(((&(iter->second))->GetAttr()).data());
      fHardwareData->SetName(((&(iter->second))->GetName()).data());
    }
  fEvent->AddHardwareData(fHardwareData);

#ifdef DEBUG_PARSER
  cout<<"channel = "   <<dec<< chanL
      << " data_val = "<<dec<< data_val << endl;
#endif
}


//-------------------------------------------------------------------------------


void NodeProcessor::ProcessNodes(const evioDOMNodeP nodePtr) 
{
  if(nodePtr->isContainer())
    isPhysicsEvent(nodePtr);
  
  if(nodePtr->isLeaf())
    {
      if( isEventID(nodePtr)      ==false && isSyncEvent(nodePtr)    ==false &&
	  isPreStartEvent(nodePtr)==false && isGoEvent(nodePtr)      ==false &&
	  isPauseEvent(nodePtr)   ==false && isEndEvent(nodePtr)     ==false)
	{
#ifdef DEBUG_PARSER
	  cout << hex << showbase <<"ContentType: " 
	       << setw(6) << nodePtr->getContentType() 
	       << " tag: " << setw(6) << nodePtr->tag 
	       << " num: " << setw(6) << dec<<(int)nodePtr->num << endl;
#endif

	  const vector<uint32_t> *vec = nodePtr->getVector<uint32_t>();

	  if(vec!=0) 
	    {
	      int roc_num = nodePtr->tag&0x001F;

	      for(unsigned int i=0; i<vec->size();i++)
		{
		  if(((*vec)[i]==0xdb4b01e2)&&((*vec)[i+1]==0x0))
		    i+=2;
		  unsigned int crate_num = ((*vec)[i]&CRATE_MASK)>>CRATE_SHIFT;
		  unsigned int slot_num  = ((*vec)[i]&SLOT_MASK)>>SLOT_SHIFT;

		  unsigned int ro_type = ((*vec)[i]&ReadOutType);
		  

#ifdef DEBUG_PARSER
		  cout << dec << "ROC = " << roc_num << ", CRATE = "
		       << crate_num << ", SLOT = " << slot_num 
		    //<< ", WORDs =" << word_num << 
		       <<", RO_type = " 
		       << hex << showbase << ro_type << endl;
#endif
 		  ROTableIter fROTableIter = 
 		    fConfigManager->GetROModel(roc_num, crate_num, slot_num);

 		  if(fROTableIter == fConfigManager->GetROModelEnd())
 		    { 
#ifdef WARN
		      cout<<"!!!Warning!!! --- unknown ROC, CRATE, SLOT"<<endl;
#endif
		      break;
  		    }

		  AttrTableIter fAttrTableIter =
		    fConfigManager->GetROAttributes((fROTableIter->second).GetModel());

		  if(fAttrTableIter == fConfigManager->GetROAttrTableEnd())
		    {
#ifdef WARN
		      cout<<"!!!Warning!!! --- unknown hardware"<<endl;
#endif
		      break;
		    }

		  fHardwareData->SetIndex((fROTableIter->second).GetIndex());

		  ROModelAttributes fROModelAttributes= fAttrTableIter->second;

		  int DATA_MASK  = fROModelAttributes.GetDataMask();
		  int CHAN_MASK  = fROModelAttributes.GetChanMask();
		  int CHAN_SHIFT = fROModelAttributes.GetChanShift();
		  int HEADER     = fROModelAttributes.GetHeader();

		  int chanL=((*vec)[i]&CHAN_MASK)>>CHAN_SHIFT;
		  int chanU= chanL-1;

		  i+= (HEADER+1);
		  
		  unsigned int word_num  = ((*vec)[i]&WDCNT_MASK)>>WDCNT_SHIFT;

		  word_num+=i;

		  switch(ro_type)
		    {
		    case DBI4:
		      for(; i<4*word_num; i++)
			{


			  if(i==1028||i==2054||i==3080)
			    {
			      chanL = ((*vec)[i]&CHAN_MASK)>>CHAN_SHIFT;
			      chanU = chanL-1;
			      i+=1;

			    }
			  else if(i>2)
			    parse_word((*vec)[i], DATA_MASK, chanL, chanU);
			}
		      break;

		    default:
		      cout<<"!!!Warning!!! --- unknown readout type"<<endl;
		    }
		}
	      
#ifdef DEBUG_PARSER
	      cout<<endl;
#endif
	    } 
	  else 
	    cerr << "?getVector<int> returned NULL" << endl;
	  fDataManager->FillEvent();
	}
    }
}


//---------------------------------------------------------------------
