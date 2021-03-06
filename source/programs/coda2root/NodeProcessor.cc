#include "NodeProcessor.hh"
#include "DataStructure.hh"
#include "ConfigManager.hh"
#include "DataManager.hh"

using namespace std;
using namespace evio;

//#define DEBUG_PARSER 1

#define STORE_DATA 1


NodeProcessor::NodeProcessor()
{
  fConfigManager = ConfigManager::GetInstance();

#ifdef STORE_DATA
  fDataManager =  DataManager::GetInstance();
     
  fEvent = fDataManager->GetEvent();
  fHardwareData = new HardwareData;
  char FlatNames[255][255];
  //  int Flat_id[200];

  if(fConfigManager->GetFlatTreeFlag())
    {
      fDataManager->AddFlatTreeBranch("EventNumber", &EventNumber, "EventNumber/I");
      fDataManager->AddFlatTreeBranch("RunNumber", &RunNumber, "RunNumber/I");
      
      //Aram's original version
      //------------------------------------------------------
      int i=0;
      /*
      for(TTableIter iter = fConfigManager->GetTranslationTableBegin();
 	  iter!=fConfigManager->GetTranslationTableEnd(); iter++, i++)
 	{
 	  TString BranchName = (&(iter->second))->GetName();
 	  //BranchName+=(&(iter->second))->GetAttr();
	  //BranchName+=(&(iter->second))->GetID);
	  fDataManager->AddFlatTreeBranch(BranchName, &RawDatArray[i], BranchName+"/D");
	}
      */
      //------------------------------------------------------

      //S. Stave modifications 3/8/10
      //Changed to auto assign 5/20/10
      i=0;
      printf("Using flat tree: ID numbers automatically assigned\n");
      printf("%8s %20s\n","ID#","Name");
      for(TTableIter iter = fConfigManager->GetTranslationTableBegin();
 	  iter!=fConfigManager->GetTranslationTableEnd(); iter++, i++)
 	{
 	  TString BranchName = (&(iter->second))->GetName();
	  //	  Flat_id[i]=(&(iter->second))->GetID();
	  //Override the id that is set in the ro_config.xml
	  (&(iter->second))->SetID(i);
	  sprintf( FlatNames[i],"%s",BranchName.Data());
	  //	  fDataManager->AddFlatTreeBranch(FlatNames[i], &RawDatArray[Flat_id[i]], 
	  fDataManager->AddFlatTreeBranch(FlatNames[i], &RawDatArray[i], 
					  Form("%s/D",FlatNames[i]));
	  //	  printf("%8i %20s\n",Flat_id[i],FlatNames[i]);
	  printf("%8i %20s\n",i,FlatNames[i]);
 	}
      //--------------------------------------------------

    }
#endif
}

//-----------------------------------------------------------------//

bool NodeProcessor::isEventID(const evioDOMNodeP nodePtr)
{ 
  bool flag=false;
  if(nodePtr->tag==0xC000 && nodePtr->getContentType()==1 && nodePtr->num==0) 
    {
#ifdef DEBUG_PARSER
      cout<<"Event ID bank:::->>  ";
#endif

#ifdef STORE_DATA
      fEvent->Clear("C");
#endif
      flag=true;
      const vector<uint32_t> *vec = nodePtr->getVector<uint32_t>();
      if(vec!=0) 
	{
#ifdef DEBUG_PARSER
	  if((*vec)[0]>4) exit(0);
#endif

#ifdef STORE_DATA
	  fEvent->SetEventNumber((*vec)[0]);
	  fEvent->SetRunNumber(fRunInfo->GetRunNumber());
	  fEvent->SetEventName("Physics");
#endif

    // Print ticker once in a while
	  static time_t last_time = 0;
	  static int last_N_events = 0;
	  time_t now = time(NULL);
	  if(now-last_time > 0)
	    {
	      if(last_time>0)
		{
		  float Ndelta = (float)((*vec)[0] - last_N_events);
		  float t_delta = (float)(now - last_time);
		  float rate = Ndelta/t_delta;
		  cout<<"\r  "<<(*vec)[0]<<" events processed  ";
		  cout<<"("<<rate<<" Hz)     ";
		  cout.flush();
		  fDataManager->AutoSaveTree();
		}
	      last_N_events = (*vec)[0];
	      last_time = now;
	      
	    }


#ifdef DEBUG_PARSER
	  cout << dec<<"EventNumber = "<< (*vec)[0] 
	       <<", EventCalss = "<<  (*vec)[1]
	       <<", EventStatus = "<< (*vec)[2]<<endl;
#endif
	} 
      else 
	cerr << "?getVector<int> returned NULL" << endl;
    }
  return flag;
}

//--------------------------------------------------------------------//

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

//-----------------------------------------------------------------//

bool NodeProcessor::isPreStartEvent(const evioDOMNodeP nodePtr)
{
  bool flag=false;
  if(nodePtr->tag==17 && nodePtr->getContentType()==1 && nodePtr->num==0xCC) 
    {
#ifdef DEBUG_PARSER    
      cout<<"PreStartEvent:::->>  ";
#endif

#ifdef STORE_DATA
      fRunInfo = fDataManager->GetRunInfo();
#endif
      flag=true;
      const vector<uint32_t> *vec = nodePtr->getVector<uint32_t>();
      if(vec!=0) 
	{

#ifdef STORE_DATA
	  fRunInfo->SetTime((*vec)[0]);
	  fRunInfo->SetRunNumber((*vec)[1]);
	  fRunInfo->SetRunType("test");
	  fRunInfo->SetName("RunInfo");
#endif
	  
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

//-----------------------------------------------------------//

bool NodeProcessor::isGoEvent(const evioDOMNodeP nodePtr)
{
  bool flag=false;
  if(nodePtr->tag==18 && nodePtr->getContentType()==1 && nodePtr->num==0xCC)
    { 
#ifdef DEBUG_PARSER    
      cout<<"GoEvent:::->>  ";
#endif

#ifdef STORE_DATA
      fStartInfo = fDataManager->GetStartInfo();
      fStartInfo->SetName("StartInfo");
#endif
      flag=true;
      const vector<uint32_t> *vec = nodePtr->getVector<uint32_t>();
      if(vec!=0) 
	{
#ifdef STORE_DATA
	  fStartInfo->SetTime((*vec)[0]);
	  fStartInfo->SetNumEvents((*vec)[2]);
#endif

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

//-----------------------------------------------------------//

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

//----------------------------------------------------------//

bool NodeProcessor::isEndEvent(const evioDOMNodeP nodePtr)
{
  bool flag=false;
  if(nodePtr->tag==20 && nodePtr->getContentType()==1 && nodePtr->num==0xCC)
    {
#ifdef DEBUG_PARSER    
      cout<<"EndEvent:::->>  ";
#endif
#ifdef STORE_DATA 
      fEndInfo = fDataManager->GetEndInfo();
      fEndInfo->SetName("EndInfo");
#endif
      flag=true;
      const vector<uint32_t> *vec = nodePtr->getVector<uint32_t>();
      if(vec!=0) 
	{

#ifdef STORE_DATA
	  fEndInfo->SetTime((*vec)[0]);
	  fEndInfo->SetNumEvents((*vec)[2]);
#endif

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

//----------------------------------------------------------//

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

//---------------------------------------------------------//

bool NodeProcessor::isScalerEvent(const evioDOMNodeP nodePtr)
{ 
  bool flag=false;
  if(nodePtr->tag==130) 
    { 
#ifdef STORE_DATA
      uint32_t e_num = fEvent->GetEventNumber();   //this might cause a 
      uint32_t r_num = fRunInfo->GetRunNumber();   //problem if used with 
                                                   //TChains
      
      fEvent->Clear("C");
      fEvent->SetEventName("ScalerEvent");
      fEvent->SetEventNumber(e_num+1);
      fEvent->SetRunNumber(r_num);
#endif

      flag=true;
#ifdef DEBUG_PARSER
      cout<<"Found a Scaler Event: tag = "<<hex<<showbase<<nodePtr->tag<<endl;
      cout<<endl<<"content type = "<<nodePtr->getContentType()<<" num =  "<<(int)nodePtr->num<<endl;

      const vector<uint32_t> *vec = nodePtr->getVector<uint32_t>();
      if(vec!=0)  
	{
	  cout<<"vector size: "<<dec<<vec->size()<<endl;
	  for(unsigned int i=0; i<vec->size();i++)
	    if(i==0)	
	      cout<<dec<<i+1<<" "<<hex<<showbase<<(*vec)[i]<<endl;
	    else
	      cout<<dec<<i+1<<" "<<(*vec)[i]<<endl;
	}
#endif
    }
  return flag;
}

//---------------------------------------------------------------------

void NodeProcessor::parse_db4a(uint32_t longword, int DATA_MASK, 
			       int CHAN_MASK, int CHAN_SHIFT)
{
 int channel = (longword & CHAN_MASK) >> CHAN_SHIFT;

#ifdef STORE_DATA
 fHardwareData->SetChannel(channel);
 fHardwareData->SetValue(longword & DATA_MASK);

 TTableIter iter = fConfigManager->GetTTElement(fHardwareData->GetIndex(), channel);
 if(iter!=fConfigManager->GetTranslationTableEnd())
   {
     fHardwareData->SetID((&(iter->second))->GetID());
     fHardwareData->SetAttribute(((&(iter->second))->GetAttr()).data());
     fHardwareData->SetName(((&(iter->second))->GetName()).data());
   }
 else
   {
     fHardwareData->SetID(-1);
     fHardwareData->SetAttribute("NO_Attr");
     fHardwareData->SetName("NO_NAME");
   }
 fEvent->AddHardwareData(fHardwareData);
#endif

#ifdef DEBUG_PARSER
 int data_val = longword & DATA_MASK;

 cout<<"channel = "   << dec << channel
     << " data_val = "<< dec << data_val <<endl;
#endif
}

//--------------------------------------------------------------------

void NodeProcessor::parse_db4b(uint32_t longword, int &ch, int DATA_MASK)
{

#ifdef STORE_DATA
  //sequential readout
  fHardwareData->SetChannel(ch);
  fHardwareData->SetValue(longword & DATA_MASK);
  
  TTableIter iter = fConfigManager->GetTTElement(fHardwareData->GetIndex(), ch);

  if(iter!=fConfigManager->GetTranslationTableEnd())
    {
      fHardwareData->SetID((&(iter->second))->GetID());
      fHardwareData->SetAttribute(((&(iter->second))->GetAttr()).data());
      fHardwareData->SetName(((&(iter->second))->GetName()).data());
    }
 else
   {
     fHardwareData->SetID(-1);
     fHardwareData->SetAttribute("NO_Attr");
     fHardwareData->SetName("NO_NAME");
   }
  fEvent->AddHardwareData(fHardwareData);
#endif

#ifdef DEBUG_PARSER
  int data_val = longword & DATA_MASK;
  
  cout<<"channel = "   << dec << ch
      << " data_val = "<< dec << data_val <<endl;
#endif
  ch++;
}

//---------------------------------------------------------------------

void NodeProcessor::parse_db2a(uint32_t longword, int DATA_MASK, int CHAN_MASK, 
                              int CHAN_SHIFT, int &ch, unsigned int word_num)
{
  int word  =  longword & 0x0000FFFF;
  int wordU = (longword & 0xFFFF0000) >> 16;

  int data_val = (wordU & DATA_MASK);
  int channel  = (wordU & CHAN_MASK) >> CHAN_SHIFT;

#ifdef STORE_DATA
  fHardwareData->SetChannel(channel);
  fHardwareData->SetValue(data_val);

  TTableIter iter = fConfigManager->GetTTElement(fHardwareData->GetIndex(), channel);
  if(iter!=fConfigManager->GetTranslationTableEnd())
    {
      fHardwareData->SetID((&(iter->second))->GetID());
      fHardwareData->SetAttribute(((&(iter->second))->GetAttr()).data());
      fHardwareData->SetName(((&(iter->second))->GetName()).data());
    }
 else
   {
     fHardwareData->SetID(-1);
     fHardwareData->SetAttribute("NO_Attr");
     fHardwareData->SetName("NO_NAME");
   }
  fEvent->AddHardwareData(fHardwareData);
#endif

#ifdef DEBUG_PARSER
  cout<<"channel = "   <<dec<< channel
      << " data_val = "<<dec<< data_val<<endl;
#endif
  ch++;
  if(ch>=word_num) return;

  channel  = (word & CHAN_MASK) >> CHAN_SHIFT;
  data_val = word & DATA_MASK;

#ifdef STORE_DATA
  fHardwareData->SetChannel(channel);
  fHardwareData->SetValue(data_val);

  iter = fConfigManager->GetTTElement(fHardwareData->GetIndex(), channel);
  if(iter!=fConfigManager->GetTranslationTableEnd())
    {
      fHardwareData->SetID((&(iter->second))->GetID());
      fHardwareData->SetAttribute(((&(iter->second))->GetAttr()).data());
      fHardwareData->SetName(((&(iter->second))->GetName()).data());
    }
 else
   {
     fHardwareData->SetID(-1);
     fHardwareData->SetAttribute("NO_Attr");
     fHardwareData->SetName("NO_NAME");
   }
  fEvent->AddHardwareData(fHardwareData);
#endif
#ifdef DEBUG_PARSER
  cout<<"channel = "   <<dec<< channel
      << " data_val = "<<dec<< data_val <<endl;
#endif
  ch++;  

}

//--------------------------------------------------------------------

void NodeProcessor::parse_db2b(uint32_t longword, int DATA_MASK, 
                               int &ch, unsigned int word_num)
{
  // sequential readout
  int word  =  longword & 0x0000FFFF;
  int wordU = (longword & 0xFFFF0000) >> 16;

  int data_val = wordU & DATA_MASK;

#ifdef STORE_DATA
  fHardwareData->SetChannel(ch);
  fHardwareData->SetValue(data_val);

  TTableIter iter = fConfigManager->GetTTElement(fHardwareData->GetIndex(), ch);

  if(iter!=fConfigManager->GetTranslationTableEnd())
    {
      fHardwareData->SetID((&(iter->second))->GetID());
      fHardwareData->SetAttribute(((&(iter->second))->GetAttr()).data());
      fHardwareData->SetName(((&(iter->second))->GetName()).data());
    }
 else
   {
     fHardwareData->SetID(-1);
     fHardwareData->SetAttribute("NO_Attr");
     fHardwareData->SetName("NO_NAME");
   }
  fEvent->AddHardwareData(fHardwareData);
#endif
#ifdef DEBUG_PARSER
  cout<<"channel = "   <<dec<< ch
      << " data_val = "<<dec<< data_val << endl;
#endif

  ch++;
  if(ch>=word_num) return;  
  data_val = word & DATA_MASK;

#ifdef STORE_DATA
  fHardwareData->SetChannel(ch);
  fHardwareData->SetValue(data_val);
  iter = fConfigManager->GetTTElement(fHardwareData->GetIndex(), ch);
  if(iter!=fConfigManager->GetTranslationTableEnd())
    {
      fHardwareData->SetID((&(iter->second))->GetID());
      fHardwareData->SetAttribute(((&(iter->second))->GetAttr()).data());
      fHardwareData->SetName(((&(iter->second))->GetName()).data());
    }
 else
   {
     fHardwareData->SetID(-1);
     fHardwareData->SetAttribute("NO_Attr");
     fHardwareData->SetName("NO_NAME");
   }
  fEvent->AddHardwareData(fHardwareData);
#endif

#ifdef DEBUG_PARSER
  cout<<"channel = "   <<dec<< ch
      << " data_val = "<<dec<< data_val << endl;
#endif
  ch++;  

}


//-------------------------------------------------------------------------------


void NodeProcessor::ProcessNodes(const evioDOMNodeP nodePtr) 
{
#ifdef DEBUG_PARSER
  if(nodePtr->isContainer())
    isPhysicsEvent(nodePtr);
#endif

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
	       << " num: " << setw(6) << (int)nodePtr->num << endl;
#endif
	  
	  isScalerEvent(nodePtr);

	  const vector<uint32_t> *vec = nodePtr->getVector<uint32_t>();

	  if(vec!=0) 
	    {
	      int roc_num = nodePtr->tag&0x001F;

	      for(unsigned int i=0; i<vec->size();i++)
		{
		  unsigned int crate_num = ((*vec)[i]&CRATE_MASK)>>CRATE_SHIFT;
		  unsigned int slot_num  = ((*vec)[i]&SLOT_MASK)>>SLOT_SHIFT;
		  unsigned int word_num  = ((*vec)[i]&WDCNT_MASK)>>WDCNT_SHIFT;
		  unsigned int ro_type   = ((*vec)[i]&ReadOutType);
#ifdef DEBUG_PARSER
		  cout << dec << "ROC = " << roc_num << ", CRATE = "
		       << crate_num << ", SLOT = " << slot_num 
		       << ", WORDs =" << word_num << ", RO_type = " 
		       << hex << showbase << ro_type << endl;
#endif
 		  ROTableIter fROTableIter = 
 		    fConfigManager->GetROModel(roc_num, crate_num, slot_num);

 		  if(fROTableIter == fConfigManager->GetROModelEnd())
 		    { 
		      //#ifdef WARN
		      cout<<"roc = "<<roc_num<<" crate = "<<crate_num<<" slot = "<<slot_num<<endl;
		      cout<<"!!!Warning!!! --- unknown ROC, CRATE, SLOT"<<endl;
		      //#endif
		      break;
  		    }

		  AttrTableIter fAttrTableIter =
		    fConfigManager->GetROAttributes((fROTableIter->second).GetModel());

		  if(fAttrTableIter == fConfigManager->GetROAttrTableEnd())
		    {
		      //#ifdef WARN
		      cout<<"!!!Warning!!! "<< (fROTableIter->second).GetModel()
			  <<" ---- is unknown hardware"<<endl;
		      //#endif
		      break;
		    }
#ifdef STORE_DATA

		  fHardwareData->SetIndex((fROTableIter->second).GetIndex());
#endif
		  ROModelAttributes fROModelAttributes= fAttrTableIter->second;

		  int DATA_MASK  = fROModelAttributes.GetDataMask();
		  int CHAN_MASK  = fROModelAttributes.GetChanMask();
		  int CHAN_SHIFT = fROModelAttributes.GetChanShift();
		  int HEADER     = fROModelAttributes.GetHeader();
		  int chan=0;
                  unsigned int coda_word_num = 0;
		  i+= (HEADER+1);

                  switch(ro_type)
                    {
                    case DBI4_WA:
                      word_num+=i;
                      for(; i<word_num; i++)
			parse_db4a((*vec)[i], DATA_MASK, CHAN_MASK, CHAN_SHIFT);
                      break;

                    case DBI4_WOA:
                      word_num+=i;
                      for(; i<word_num; i++)
			parse_db4b((*vec)[i], chan, DATA_MASK);
                      break;

                    case DBI2_WA:
                      coda_word_num = word_num - word_num/2;
                      coda_word_num+=i;
                      for(; i<coda_word_num && chan < word_num; i++)
                        parse_db2a((*vec)[i], DATA_MASK, CHAN_MASK, CHAN_SHIFT, chan, word_num);
                      break;

                    case DBI2_WOA:
                      coda_word_num = word_num - word_num/2;
                      coda_word_num+=i;
                      for(; i<coda_word_num && chan < word_num; i++)
                        parse_db2b((*vec)[i], DATA_MASK, chan, word_num);
                      break;

                    default:
                      cout<<"!!!Warning!!! --- unknown readout type"<<endl;
                    }
		  i--;
		}
	      
#ifdef DEBUG_PARSER
	      cout<<endl;
#endif
	    } 
	  else 
	    cerr << "?getVector<int> returned NULL" << endl;

#ifdef STORE_DATA
	  if(fConfigManager->GetFlatTreeFlag())
	    {

	      for(int k=0; k<200; k++)RawDatArray[k]=0.;
	      
	      TClonesArray*  raw_data_array = fEvent->GetRawData();
	      HardwareData* hd;
	      //	      EventNumber = (int)fEvent->GetEventNumber();
	      //	      RunNumber   = fEvent->GetRunNumber();
	      
	      for(int k=0; k<fEvent->GetNDataEntries(); k++)
		{
		  hd=(HardwareData*)raw_data_array->At(k);
		  
		  //---------------------------------------------------
		  //Aram's original version
		  /*
		  int index = hd->GetIndex();
		  int chan = hd->GetChannel();
		  int m=0;
		  std::string name;
		  for(TTableIter iter = fConfigManager->GetTranslationTableBegin();
		      iter!=fConfigManager->GetTranslationTableEnd(); iter++, m++)
		    {
		      name = (iter->second).GetName();
		      if(strcmp(hd->GetName(), name.data())==0)
			{
			  RawDatArray[m]= hd->GetValue();
			  break;
			}
		    }
		  */
		  //S. Stave modification (3/8/10)
		  //---------------------------------
		  //		  printf("%i %s\n",hd->GetID(),hd->GetName());
		  RawDatArray[hd->GetID()]= hd->GetValue();
		  //---------------------------------

		}
	    }
	  //These need to be set here because they are getting zeroed out when
	  // defined above
	  EventNumber = fEvent->GetEventNumber();
	  RunNumber   = fEvent->GetRunNumber();
	  fDataManager->FillEvent();
	  fDataManager->GetEvent()->Clear("C");
#endif	  
	}
   }
}



//-------------------------------------------------------------------------------


void NodeProcessor::SkipNodes(const evioDOMNodeP nodePtr) 
{
#ifdef DEBUG_PARSER
  if(nodePtr->isContainer())
    isPhysicsEvent(nodePtr);
#endif

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
	       << " num: " << setw(6) << (int)nodePtr->num << endl;
#endif
	  
	  isScalerEvent(nodePtr);

	  const vector<uint32_t> *vec = nodePtr->getVector<uint32_t>();

	  if(vec!=0) 
	    {
	      int roc_num = nodePtr->tag&0x001F;

	      for(unsigned int i=0; i<vec->size();i++)
		{
		  unsigned int crate_num = ((*vec)[i]&CRATE_MASK)>>CRATE_SHIFT;
		  unsigned int slot_num  = ((*vec)[i]&SLOT_MASK)>>SLOT_SHIFT;
		  unsigned int word_num  = ((*vec)[i]&WDCNT_MASK)>>WDCNT_SHIFT;
		  unsigned int ro_type   = ((*vec)[i]&ReadOutType);
#ifdef DEBUG_PARSER
		  cout << dec << "ROC = " << roc_num << ", CRATE = "
		       << crate_num << ", SLOT = " << slot_num 
		       << ", WORDs =" << word_num << ", RO_type = " 
		       << hex << showbase << ro_type << endl;
#endif
 		  ROTableIter fROTableIter = 
 		    fConfigManager->GetROModel(roc_num, crate_num, slot_num);

 		  if(fROTableIter == fConfigManager->GetROModelEnd())
 		    { 
		      //#ifdef WARN
		      cout<<"roc = "<<roc_num<<" crate = "<<crate_num<<" slot = "<<slot_num<<endl;
		      cout<<"!!!Warning!!! --- unknown ROC, CRATE, SLOT"<<endl;
		      //#endif
		      break;
  		    }

		  AttrTableIter fAttrTableIter =
		    fConfigManager->GetROAttributes((fROTableIter->second).GetModel());

		  if(fAttrTableIter == fConfigManager->GetROAttrTableEnd())
		    {
		      //#ifdef WARN
		      cout<<"!!!Warning!!! "<< (fROTableIter->second).GetModel()
			  <<" ---- is unknown hardware"<<endl;
		      //#endif
		      break;
		    }
		  /*
#ifdef STORE_DATA

		  fHardwareData->SetIndex((fROTableIter->second).GetIndex());
#endif
		  */
		  ROModelAttributes fROModelAttributes= fAttrTableIter->second;

		  int DATA_MASK  = fROModelAttributes.GetDataMask();
		  int CHAN_MASK  = fROModelAttributes.GetChanMask();
		  int CHAN_SHIFT = fROModelAttributes.GetChanShift();
		  int HEADER     = fROModelAttributes.GetHeader();
		  int chan=0;
                  unsigned int coda_word_num = 0;
		  i+= (HEADER+1);

                  switch(ro_type)
                    {
                    case DBI4_WA:
                      word_num+=i;
                      for(; i<word_num; i++)
			parse_db4a((*vec)[i], DATA_MASK, CHAN_MASK, CHAN_SHIFT);
                      break;

                    case DBI4_WOA:
                      word_num+=i;
                      for(; i<word_num; i++)
			parse_db4b((*vec)[i], chan, DATA_MASK);
                      break;

                    case DBI2_WA:
                      coda_word_num = word_num - word_num/2;
                      coda_word_num+=i;
                      for(; i<coda_word_num && chan < word_num; i++)
                        parse_db2a((*vec)[i], DATA_MASK, CHAN_MASK, CHAN_SHIFT, chan, word_num);
                      break;

                    case DBI2_WOA:
                      coda_word_num = word_num - word_num/2;
                      coda_word_num+=i;
                      for(; i<coda_word_num && chan < word_num; i++)
                        parse_db2b((*vec)[i], DATA_MASK, chan, word_num);
                      break;

                    default:
                      cout<<"!!!Warning!!! --- unknown readout type"<<endl;
                    }
		  i--;
		}
	      
#ifdef DEBUG_PARSER
	      cout<<endl;
#endif
	    } 
	  else 
	    cerr << "?getVector<int> returned NULL" << endl;

	  /*	  
#ifdef STORE_DATA
	  if(fConfigManager->GetFlatTreeFlag())
	    {

	      for(int k=0; k<200; k++)RawDatArray[k]=0.;
	      
	      TClonesArray*  raw_data_array = fEvent->GetRawData();
	      HardwareData* hd;
	      //	      EventNumber = (int)fEvent->GetEventNumber();
	      //	      RunNumber   = fEvent->GetRunNumber();
	      
	      for(int k=0; k<fEvent->GetNDataEntries(); k++)
		{
		  hd=(HardwareData*)raw_data_array->At(k);
		  
		  //---------------------------------------------------
		  //Aram's original version
		  //		  int index = hd->GetIndex();
		  //		  int chan = hd->GetChannel();
		  //		  int m=0;
		  //		  std::string name;
		  //		  for(TTableIter iter = fConfigManager->GetTranslationTableBegin();
		  //		      iter!=fConfigManager->GetTranslationTableEnd(); iter++, m++)
		  //		    {
		  //		      name = (iter->second).GetName();
		  //		      if(strcmp(hd->GetName(), name.data())==0)
		  //			{
		  //			  RawDatArray[m]= hd->GetValue();
		  //			  break;
		  //			}
		  //		    }
		  //S. Stave modification (3/8/10)
		  //---------------------------------
		  //		  printf("%i %s\n",hd->GetID(),hd->GetName());
		  RawDatArray[hd->GetID()]= hd->GetValue();
		  //---------------------------------

		}
	    }
	  //These need to be set here because they are getting zeroed out when
	  // defined above
	  EventNumber = fEvent->GetEventNumber();
	  RunNumber   = fEvent->GetRunNumber();
	  //	  fDataManager->FillEvent();
	  fDataManager->GetEvent()->Clear("C");
#endif	  
	  */
	}
   }
}


