#include "DataStructure.hh"

#include <string>

ClassImp(RunInfo)
ClassImp(RunControlEvent)
ClassImp(HardwareData)
ClassImp(RawData)



//------------------------------------------------------------

RunInfo::RunInfo():TNamed()
{
  fTime      = -1;
  fRunNumber = -1;
  fRunType   = "";
}

RunInfo::RunInfo(const RunInfo& orig):TNamed(orig)
{
  fTime      = orig.fTime;
  fRunNumber = orig.fRunNumber;
  fRunType   = orig.fRunType;
}

//-------------------------------------------------------------

RunControlEvent::RunControlEvent():TNamed()
{
  fTime           = -1;
  fNumberOfEvents = -1;
}

RunControlEvent::RunControlEvent(const RunControlEvent& orig):TNamed(orig)
{
  fTime           = orig.fTime;
  fNumberOfEvents = orig.fNumberOfEvents;
}

//-----------------------------------------------------------

HardwareData::HardwareData():TNamed()
{
  fIndex   = 0;
  fChannel = 0;
  fVal     = 0;
  fAttr    = "";
  fID      = 0;
}

HardwareData::HardwareData(const HardwareData& orig):TNamed(orig)
{
  fIndex   = orig.fIndex;
  fChannel = orig.fChannel;
  fVal     = orig.fVal;
  fAttr    = orig.fAttr;
  fID      = orig.fID;
}

void HardwareData::Clear(Option_t* opt)
{
  fIndex   = -1;
  fChannel = -1;
  fVal     = -1.;
  fAttr    = "";
  fID      = -1;
  TNamed::Clear(opt);
}


//--------------------------------------------------------------

RawData::RawData():TObject()
{
  fEventNumber  = 0;
  fRunNumber  = 0;
  fN_DataEntries  = 0;
  fEventName    = "";
  fDataArray = new TClonesArray("HardwareData", 50);
}

RawData::~RawData()
{
  Clear("C");
  if(fDataArray) delete fDataArray;  
}


HardwareData* RawData::AddHardwareData(HardwareData* dataPtr)
{
  TClonesArray &raw_data = *fDataArray;
  HardwareData *h_data = new(raw_data[fN_DataEntries++]) (HardwareData)(*dataPtr);

  return h_data;
}


void RawData::Clear(Option_t *opt)
{
  fEventNumber    = 0;
  fRunNumber    = 0;
  fN_DataEntries  = 0; 
  fEventName      = "";
  if(fDataArray) fDataArray->Clear(opt); //also calls HardwareData::Clear 
}

//--------------------------------------------------------------

Double_t RawData::GetByName(const char* name)
{
  HardwareData* hd=0;
  
  for(Int_t j=0; j<fN_DataEntries; j++)
     {
       if(!strcmp(((HardwareData*)fDataArray->At(j))->GetName(), name))
	 {      
	   hd=(HardwareData*)fDataArray->At(j);
	 }
     }

   if(hd) return hd->GetValue();
   else  return 0;
}

//--------------------------------------------------------------

Double_t RawData::GetByIndexChannel(Int_t index, Int_t chan)
{
  HardwareData* hd=0;
   for(Int_t j=0; j<fN_DataEntries; j++)
     {
       if(((HardwareData*)fDataArray->At(j))->GetIndex()==index &&
	  ((HardwareData*)fDataArray->At(j))->GetChannel()==chan)
	 {      
	   hd=(HardwareData*)fDataArray->At(j);
	 }
     }

   if(hd) return hd->GetValue();
   else  return 0;
}

//--------------------------------------------------------------

Double_t RawData::GetByNameID(const char* name, Int_t id)
{
  HardwareData* hd=0;
   for(Int_t j=0; j<fN_DataEntries; j++)
     {
       if(!strcmp(((HardwareData*)fDataArray->At(j))->GetName(), name)&&
	  ((HardwareData*)fDataArray->At(j))->GetID()==id)
	 {      
	   hd=(HardwareData*)fDataArray->At(j);
	 }
     }

   if(hd) return hd->GetValue();
   else  return 0;
}

//----------------------------------------------------------------

Double_t RawData::GetByNameAttr(const char* name, const char* attr)
{
  HardwareData* hd=0;
   for(Int_t j=0; j<fN_DataEntries; j++)
     {
       if(!strcmp(((HardwareData*)fDataArray->At(j))->GetName(), name)&&
	  ((HardwareData*)fDataArray->At(j))->GetAttribute()==attr)
	 {      
	   hd=(HardwareData*)fDataArray->At(j);
	 }
     }

   if(hd) return hd->GetValue();
   else  return 0;
}

//--------------------------------------------------------------

Double_t RawData::GetByNameAttrId(const char* name, const char* attr, Int_t id)
{
  HardwareData* hd=0;
   for(Int_t j=0; j<fN_DataEntries; j++)
     {
       if(!strcmp(((HardwareData*)fDataArray->At(j))->GetName(), name)&&
	  ((HardwareData*)fDataArray->At(j))->GetAttribute()==attr &&
	  ((HardwareData*)fDataArray->At(j))->GetChannel()==id)
	 {      
	   hd=(HardwareData*)fDataArray->At(j);
	 }
     }

   if(hd) return hd->GetValue();
   else  return 0;
}
