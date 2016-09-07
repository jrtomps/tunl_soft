#include "DetectorClass.hh"
#include "TClonesArray.h"
#include "DataStructure.hh"

DetectorClass::DetectorClass(TString name)
{
  core_adc =0;
  core_tdc =0;
  shield_adc =0;
  shield_tdc =0;
  fName = name;

}

void DetectorClass::Initialize(TClonesArray *fDataArray)
{

  HardwareData * hd=0;
  for(Int_t k=0; k<fDataArray->GetEntries(); k++)
    {
      hd = (HardwareData*) fDataArray->At(k);

      if(hd->GetName()!=fName) continue;

      if(hd->GetAttribute()=="adc")
	{
	  if(hd->GetID()==0) 
	    SetCoreADC(hd->GetValue());
	  else
	    SetShieldADC(hd->GetValue());
	}
      else if(hd->GetAttribute()=="tdc")
	{
	  if(hd->GetID()==0)
	    SetCoreTDC(hd->GetValue());
	  else 
	    SetShieldTDC(hd->GetValue());
	}
    }

}
