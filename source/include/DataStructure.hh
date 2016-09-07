#ifndef DataStructure_h
#define DataStructure_h 1

#include "TNamed.h"
#include "TClonesArray.h"
#include <string>

//-----------------------------------------------------
class RunInfo:public TNamed
{
  //class holds information about the run
  //  Int_t   fTime;        time stamp from PreStartEvent
  //  Int_t   fRunNumber;   Run Number from PreStartEvent
  //  TString fRunType;     RunType, ignore for now a place holder

public:
  RunInfo();
  RunInfo(const RunInfo& orig);
  ~RunInfo(){};
  
  void SetTime(Int_t t)                  { fTime = t;      }
  void SetRunNumber(Int_t n)             { fRunNumber = n; }
  void SetRunType(TString type)          { fRunType = type;}

  Int_t   GetTime()      { return fTime;      }
  Int_t   GetRunNumber() { return fRunNumber; }
  TString GetRunType()   { return fRunType;   }

private:
  Int_t   fTime;
  Int_t   fRunNumber;
  TString fRunType;

  ClassDef(RunInfo,1)  //[Analyze]  /*do not remove this comment*/
};


//---------------------------------------------------

class RunControlEvent:public TNamed
{
public:
  RunControlEvent();
  RunControlEvent(const RunControlEvent& orig);
  ~RunControlEvent(){};
  
  void SetTime(Int_t t)                  { fTime = t;          }
  void SetNumEvents(Int_t n)             { fNumberOfEvents= n;}

  Int_t   GetTime()      { return fTime;           }
  Int_t   GetNumEvents() { return fNumberOfEvents; }

private:
  Int_t   fTime;
  Int_t   fNumberOfEvents;    // Number of events in the run thus far 

  ClassDef(RunControlEvent,1)  //[Analyze]  /*do not remove this comment*/
};

//----------------------------------------------------

class HardwareData:public TNamed
{
public:
  HardwareData();
  HardwareData(const HardwareData& orig);
  ~HardwareData(){};

  virtual void Clear(Option_t*);

  void SetIndex(Int_t i)         { fIndex   = i;   }
  void SetChannel(Int_t ch)      { fChannel = ch;  }
  void SetValue(Int_t val)       { fVal     = val; }
  void SetAttribute(const char* str) { fAttr    = str; }
  void SetID(Int_t id)           { fID      = id;  }

  Int_t   GetIndex()    { return fIndex;   }
  Int_t   GetChannel()  { return fChannel; }
  Int_t   GetValue()    { return fVal;     }
  TString GetAttribute(){ return fAttr;    }
  Int_t   GetID()       { return fID;      }

private:
  Int_t   fIndex;
  Int_t   fChannel;
  Int_t   fVal;
  TString fAttr;
  Int_t   fID;

  ClassDef(HardwareData,1)  //[Analyze]  /*do not remove this comment*/
};

//------------------------------------------------------
class RawData:public TObject
{
public:
  RawData();
  ~RawData();

  void Clear(Option_t *option ="");

  void SetEventNumber(Int_t n)    { fEventNumber = n;    };
  void SetRunNumber(Int_t num)   { fRunNumber = num; };
  void SetEventName(const char* name) { fEventName=name;};

  HardwareData *AddHardwareData(HardwareData *dataPtr);

  Int_t GetEventNumber()    { return fEventNumber; };
  Int_t GetRunNumber()      { return fRunNumber; };
  Int_t GetNDataEntries()   { return fN_DataEntries; };
  TString GetEventName()    { return fEventName;   };

  TClonesArray *GetRawData()  { return fDataArray; };

  //the next few Get methods loop over the HardwareData ("fDataArray")
  //and return the fVal stored in the first element of the fDataArray
  //matching the selection criteria, if no element matches the criteria 
  // a zero is returned; 
  // WARNING!!! this methods should be used for quick checks only
  Double_t GetByName(const char* name);
  Double_t GetByIndexChannel(Int_t index, Int_t chan);
  Double_t GetByNameID(const char* name, Int_t id);
  Double_t GetByNameAttr(const char* name, const char* attr);
  Double_t GetByNameAttrId(const char* name, const char* attr, Int_t id);

private:
  Int_t          fEventNumber;
  Int_t          fRunNumber;
  Int_t          fN_DataEntries;
  TString        fEventName;      //
  TClonesArray*  fDataArray;      //->array with hardware data /*do not remove this comment*/

  ClassDef(RawData,1)  //[Analyze] Event structure /*do not remove this comment*/
};

#endif

