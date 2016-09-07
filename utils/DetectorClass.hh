
#ifndef DetectorClass_h 
#define DetectorClass_h 1

#include "TString.h"
#include "TNamed.h"


class TClonesArray;
class DetectorClass:public TNamed
{
public:
  DetectorClass(TString name);
  ~DetectorClass(){}

public:
  void Initialize(TClonesArray *fDataArray);

  Double_t GetCoreEnergy()
  {return  core_adc;}
  Double_t GetShieldEnergy()
  {return shield_adc;}

  Double_t GetCoreTime()
  {return core_tdc;}
  
  Double_t GetShieldTime()
  {return shield_tdc;}

private:
  void SetCoreADC(Int_t a){core_adc = a;}
  void SetCoreTDC(Int_t t){core_tdc = t;}

  void SetShieldTDC(Int_t t){shield_tdc = t;}
  void SetShieldADC(Int_t a){shield_adc += a;}

private:
  Int_t core_adc;
  Int_t shield_adc;

  Int_t core_tdc;
  Int_t shield_tdc;

  ClassDef(DetectorClass,1)
};
#endif
