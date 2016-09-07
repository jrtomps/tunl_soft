#ifndef MCEvent_H
#define MCEvent_H
                                            
#include "TObject.h"
#include "TClonesArray.h"
#include "TRefArray.h"
#include "TVector3.h"

class DetectorHit : public TObject {

private:  
  Int_t      fTrackID;          
  Int_t      fParentID;           
  TString    fProcessName;
  TString    fParticleName;
  Double_t   fCharge;
  TVector3   fVertexPosition;
  Double_t   fVertexKineticEnergy;
  Int_t      fModuleID;          
  Double_t   fModuleTheta;
  Double_t   fModulePhi;
  Int_t      fDetectorID;            
  Double_t   fTotalEnergyDeposit; 
  Double_t   fDeltaEnergy;
  Double_t   fTotalEnergy;
  TVector3   fHitPosition;
  Double_t   fKineticEnergy;
  Double_t   fLocalTime;
  Double_t   fGlobalTime;

public:
  DetectorHit();
  DetectorHit(const DetectorHit& orig);
  virtual ~DetectorHit() {}

  virtual void Clear(Option_t*);
 
  inline void SetTrackID(Int_t id)            { fTrackID = id; }          
  inline void SetParentID(Int_t id)           { fParentID = id; }           
  inline void SetProcessName(TString name)    { fProcessName = name; }
  inline void SetParticleName(TString name)   { fParticleName = name; }
  inline void SetCharge(Double_t ch)          { fCharge = ch; }
  inline void SetVertexPosition(TVector3 pos) { fVertexPosition = pos; }
  inline void SetVertexKineticE(Double_t e)   { fVertexKineticEnergy = e; }
  inline void SetModuleID(Int_t id)           { fModuleID = id; }          
  inline void SetModuleTheta(Double_t theta)  { fModuleTheta = theta; }
  inline void SetModulePhi(Double_t phi)      { fModulePhi = phi; }
  inline void SetDetectorID(Int_t id)         { fDetectorID = id; }            
  inline void SetEnergyDeposit(Double_t de)   { fTotalEnergyDeposit = de; } 
  inline void SetDeltaEnergy(Double_t de)     { fDeltaEnergy = de; }
  inline void SetTotalEnergy(Double_t e)      { fTotalEnergy = e; }
  inline void SetHitPosition(TVector3 pos)    { fHitPosition = pos; }
  inline void SetKineticEnergy(Double_t e)    { fKineticEnergy = e; }
  inline void SetLocalTime(Double_t time)     { fLocalTime = time; }
  inline void SetGlobalTime(Double_t time)    { fGlobalTime = time;}

  inline void AddEnergyDeposit(Double_t de)   { fTotalEnergyDeposit += de; }
  inline void AddDeltaEnergy(Double_t de)     { fDeltaEnergy += de; }
  inline void AddLocalTime(Double_t lt)       { fLocalTime += lt; }
  inline void AddGlobalTime(Double_t gt)      { fGlobalTime +=gt; }

  inline Int_t    GetTrackID()         { return fTrackID; }          
  inline Int_t    GetParentID()        { return fParentID; }           
  inline TString  GetProcessName()     { return fProcessName; }
  inline TString  GetParticleName()    { return fParticleName; }
  inline Double_t GetCharge()          { return fCharge; }
  inline TVector3 GetVertexPosition()  { return fVertexPosition; }
  inline Double_t GetVertexKineticE()  { return fVertexKineticEnergy; }
  inline Int_t    GetModuleID()        { return fModuleID; }
  inline Double_t GetModuleTheta()     { return fModuleTheta; }
  inline Double_t GetModulePhi()       { return fModulePhi; }
  inline Int_t    GetDetectorID()      { return fDetectorID; }
  inline Double_t GetEnergyDeposit()   { return fTotalEnergyDeposit; }
  inline Double_t GetDeltaEnergy()     { return fDeltaEnergy; }
  inline Double_t GetTotalEnergy()     { return fTotalEnergy; }
  inline TVector3 GetHitPosition()     { return fHitPosition; }
  inline Double_t GetKineticEnergy()   { return fKineticEnergy; }
  inline Double_t GetLocalTime()       { return fLocalTime; }
  inline Double_t GetGlobalTime()      { return fGlobalTime; }
  ClassDef(DetectorHit,1)  //[Analyze] HIND event /*do not remove this coment*/
};

//--------------------------------------------------------------------

class TargetHit : public TObject {

private:  
  Int_t      fTrackID;          
  Int_t      fParentID;           
  TString    fProcessName;
  TString    fParticleName;
  Double_t   fCharge;
  TVector3   fVertexPosition;
  Double_t   fVertexKineticEnergy;
  Int_t      fDiskID;            
  Double_t   fTotalEnergyDeposit; 
  Double_t   fNonIonizingEnergyDeposit;
  Double_t   fDeltaEnergy;
  Double_t   fTotalEnergy;
  TVector3   fHitPosition;
  Double_t   fKineticEnergy;
  Double_t   fN_Photons;
  Double_t   fEEEdeposit;
  Double_t   fLocalTime;
  Double_t   fGlobalTime;

public:
  TargetHit();
  TargetHit(const TargetHit& orig);
  virtual ~TargetHit() {}

  virtual void Clear(Option_t*);

  inline void SetTrackID(Int_t id)            { fTrackID = id; }          
  inline void SetParentID(Int_t id)           { fParentID = id; }           
  inline void SetProcessName(TString name)    { fProcessName = name; }
  inline void SetParticleName(TString name)   { fParticleName = name; }
  inline void SetCharge(Double_t ch)          { fCharge = ch; }
  inline void SetVertexPosition(TVector3 pos) { fVertexPosition = pos; }
  inline void SetVertexKineticE(Double_t e)   { fVertexKineticEnergy = e; }
  inline void SetDiskID(Int_t id)             { fDiskID = id; }            
  inline void SetEnergyDeposit(Double_t de)   { fTotalEnergyDeposit = de; } 
  inline void SetNonIonizingEdep(Double_t de) { fNonIonizingEnergyDeposit =de;}; 
  inline void SetDeltaEnergy(Double_t de)     { fDeltaEnergy = de; }
  inline void SetTotalEnergy(Double_t e)      { fTotalEnergy = e; }
  inline void SetHitPosition(TVector3 pos)    { fHitPosition = pos; }
  inline void SetKineticEnergy(Double_t e)    { fKineticEnergy = e; }
  inline void SetNumPhotons(Double_t n)       { fN_Photons = n;}
  inline void SetEEEdeposit(Double_t de)      { fEEEdeposit = de; }
  inline void SetLocalTime(Double_t time)     { fLocalTime = time; }
  inline void SetGlobalTime(Double_t time)    { fGlobalTime = time; }
  
  inline void AddNumPhotons(Int_t n)          { fN_Photons += n; };
  inline void AddEEEdeposit(Double_t de)      { fEEEdeposit += de; };
  inline void AddEnergyDeposit(Double_t de)   { fTotalEnergyDeposit += de; }
  inline void AddNonIonizingEdep(Double_t de) { fNonIonizingEnergyDeposit += de;};
  inline void AddDeltaEnergy(Double_t de)     { fDeltaEnergy += de; }
  inline void AddLocalTime(Double_t lt)       { fLocalTime += lt; }
  inline void AddGlobalTime(Double_t gt)      { fGlobalTime +=gt; }

  inline Int_t    GetTrackID()        { return fTrackID; }          
  inline Int_t    GetParentID()       { return fParentID; }           
  inline TString  GetProcessName()    { return fProcessName; }
  inline TString  GetParticleName()   { return fParticleName; }
  inline Double_t Getcharge()         { return fCharge; }
  inline TVector3 GetVertexPosition() { return fVertexPosition; }
  inline Double_t GetVertexKineticE() { return fVertexKineticEnergy; }
  inline Int_t    GetDiskID()         { return fDiskID; }
  inline Double_t GetEnergyDeposit()  { return fTotalEnergyDeposit; }
  inline Double_t GetNonIonizingEdep(){ return fNonIonizingEnergyDeposit; }; 
  inline Double_t GetDeltaEnergy()    { return fDeltaEnergy; }
  inline Double_t GetTotalEnergy()    { return fTotalEnergy; }
  inline TVector3 GetHitPosition()    { return fHitPosition; }
  inline Double_t GetKineticEnergy()  { return fKineticEnergy; }
  inline Double_t GetNumPhotons()     { return fN_Photons; }
  inline Double_t GetEEEdeposit()     { return fEEEdeposit; }
  inline Double_t GetLocalTime()      { return fLocalTime; }
  inline Double_t GetGlobalTime()     { return fGlobalTime; }
  ClassDef(TargetHit,1)  //[Analyze] Target Event /*do not remove this comment*/
};


//------------------------------------------------------------------------------
class EventPrimary : public TObject 
{
public:
  EventPrimary();
  EventPrimary(const EventPrimary& orig);
  virtual ~EventPrimary() {};

  virtual void Clear(Option_t*);

  inline void SetTrackID(Int_t id)                { fTrackID       = id;}
  inline void SetName(TString name)               { fName          = name; }
  inline void SetMass(Double_t mass)              { fMass          = mass; } 
  inline void SetCharge(Double_t charge)          { fCharge        = charge; }
  inline void SetTotalEnergy(Double_t energy)     { fTotalEnergy   = energy; }
  inline void SetPolarization(TVector3 pol)       { fPolarization  = pol; }
  inline void SetMomentum(TVector3 momentum)      { fMomentum      = momentum; }
  
  inline Int_t    GetPrimaryTrackID() { return fTrackID; }
  inline TString  GetPrimaryName()    { return fName; }
  inline Double_t GetMass()           { return fMass; }
  inline Double_t GetCharge()         { return fCharge; }
  inline Double_t GetTotalEnertgy()   { return fTotalEnergy; }
  inline TVector3 GetPolarization()   { return fPolarization; } 
  inline TVector3 GetMomentum()       { return fMomentum; }

private:
  Int_t    fTrackID; 
  TString  fName;
  Double_t fMass;
  Double_t fCharge;
  Double_t fTotalEnergy;
  TVector3 fPolarization;
  TVector3 fMomentum;

  ClassDef(EventPrimary,1)  //[Analyze] event primary /*do not remove this comment*/
};


class MCEvent : public TObject {

private:  
  TString        fEventName;         //name in character format
  Int_t          fEventNumber;  
  Int_t          fN_Primaries;
  Int_t          fN_DetectorHits;       
  Int_t          fN_TargetHits;  
  TClonesArray*  fEventPrimaries;   //->array with primaries
  TClonesArray*  fTargetHits;       //->array with all target hits /*do not remove this comment*/
  TClonesArray*  fDetectorHits;     //->array with all hind hits /*do not remove this comment*/

public:
  MCEvent();
  virtual ~MCEvent();

  void Clear(Option_t *option ="");
  
  inline void SetEventNumber(Int_t e_num )     { fEventNumber = e_num; }
  inline void SetEventName(TString name)       { fEventName   = name; }  

  EventPrimary *AddPrimary(EventPrimary *primaryPtr);
  TargetHit    *AddTargetHit(TargetHit *hitPtr);
  DetectorHit  *AddDetectorHit(DetectorHit *hitPtr); 
  
  inline TString       GetEventName()      { return fEventName; }
  inline Int_t         GetEventNumber()    { return fEventNumber; }
  inline Int_t         GetN_Primaries()    { return fN_Primaries; }
  inline Int_t         GetN_DetectorHits() { return fN_DetectorHits; }
  inline Int_t         GetN_TargetHits()   { return fN_TargetHits; }

  inline TClonesArray *GetPrimaries()      { return fEventPrimaries; }
  inline TClonesArray *GetTargetHits()     { return fTargetHits;}
  inline TClonesArray *GetDetectorHits()   { return fDetectorHits;}
  
   ClassDef(MCEvent,1)  //[Analyze] MCEvent structure /*do not remove this comment*/
};

#endif
