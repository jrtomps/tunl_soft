
#include "MCEvent.hh"

ClassImp(DetectorHit)
ClassImp(TargetHit)
ClassImp(EventPrimary)
ClassImp(MCEvent)


//______________________________________________________________________________
DetectorHit::DetectorHit() : TObject()
{
  fTrackID              = 0;          
  fParentID             = 0;           
  fProcessName          = "";
  fParticleName         = "";
  fCharge               = 0;
  fVertexPosition.SetXYZ(0.,0.,0.);
  fVertexKineticEnergy  = 0;
  fModuleID             = 0;          
  fModuleTheta          = 0.;
  fModulePhi            = 0.;
  fDetectorID           = 0;            
  fTotalEnergyDeposit   = 0.; 
  fDeltaEnergy          = 0.;
  fTotalEnergy          = 0.;
  fHitPosition.SetXYZ(0.,0.,0.);
  fKineticEnergy        = 0.;
  fLocalTime            = 0.;
  fGlobalTime           = 0.;
}

//______________________________________________________________________________
DetectorHit::DetectorHit(const DetectorHit &orig) : TObject(orig)
{ 
  fTrackID             = orig.fTrackID;          
  fParentID            = orig.fParentID;           
  fProcessName         = orig.fProcessName;
  fParticleName        = orig.fParticleName;
  fCharge              = orig.fCharge;
  fVertexPosition      = orig.fVertexPosition;
  fVertexKineticEnergy = orig.fVertexKineticEnergy;
  fModuleID            = orig.fModuleID;          
  fModuleTheta         = orig.fModuleTheta;
  fModulePhi           = orig.fModulePhi;
  fDetectorID          = orig.fDetectorID;            
  fTotalEnergyDeposit  = orig.fTotalEnergyDeposit; 
  fDeltaEnergy         = orig.fDeltaEnergy;
  fTotalEnergy         = orig.fTotalEnergy;
  fHitPosition         = orig.fHitPosition;
  fKineticEnergy       = orig.fKineticEnergy;
  fLocalTime           = orig.fLocalTime;
  fGlobalTime          = orig.fGlobalTime;
}

//______________________________________________________________________________
void DetectorHit::Clear(Option_t* opt)
{
  fTrackID              = 0;          
  fParentID             = 0;           
  fProcessName          = "";
  fParticleName         = "";
  fCharge               = 0;
  fVertexPosition.SetXYZ(0.,0.,0.);
  fVertexKineticEnergy  = 0;
  fModuleID             = 0;          
  fModuleTheta          = 0.;
  fModulePhi            = 0.;
  fDetectorID           = 0;            
  fTotalEnergyDeposit   = 0.; 
  fDeltaEnergy          = 0.;
  fTotalEnergy          = 0.;
  fHitPosition.SetXYZ(0.,0.,0.);
  fKineticEnergy        = 0.;
  fLocalTime            = 0.;
  fGlobalTime           = 0.;
  TObject::Clear(opt);
}

//______________________________________________________________________________


//______________________________________________________________________________
TargetHit::TargetHit() : TObject()
{
  fTrackID             = 0;          
  fParentID            = 0;           
  fProcessName         = "";
  fParticleName        = "";
  fCharge              = 0.;
  fVertexPosition.SetXYZ(0.,0.,0.);
  fVertexKineticEnergy = 0.;
  fDiskID              = 0;                
  fTotalEnergyDeposit  = 0.; 
  fDeltaEnergy         = 0.;
  fTotalEnergy         = 0.;
  fHitPosition.SetXYZ(0.,0.,0.);
  fKineticEnergy       = 0.;
  fN_Photons           = 0.;
  fEEEdeposit          = 0.;
  fLocalTime           = 0.;
  fGlobalTime          = 0.;
}

//______________________________________________________________________________
TargetHit::TargetHit(const TargetHit &orig) : TObject(orig)
{
  fTrackID             = orig.fTrackID;          
  fParentID            = orig.fParentID;           
  fProcessName         = orig.fProcessName;
  fParticleName        = orig.fParticleName;
  fCharge              = orig.fCharge;
  fVertexPosition      = orig.fVertexPosition;
  fVertexKineticEnergy = orig.fVertexKineticEnergy;
  fDiskID              = orig.fDiskID;            
  fTotalEnergyDeposit  = orig.fTotalEnergyDeposit; 
  fDeltaEnergy         = orig.fDeltaEnergy;
  fTotalEnergy         = orig.fTotalEnergy;
  fHitPosition         = orig.fHitPosition;
  fKineticEnergy       = orig.fKineticEnergy;
  fN_Photons           = orig.fN_Photons;
  fEEEdeposit          = orig.fEEEdeposit;
  fLocalTime           = orig.fLocalTime;
  fGlobalTime          = orig.fGlobalTime;
}

//______________________________________________________________________________
void TargetHit::Clear(Option_t* opt)
{
  fTrackID             = 0;          
  fParentID            = 0;           
  fProcessName         = "";
  fParticleName        = "";
  fCharge              = 0.;
  fVertexPosition.SetXYZ(0.,0.,0.);
  fVertexKineticEnergy = 0.;
  fDiskID              = 0;                
  fTotalEnergyDeposit  = 0.; 
  fDeltaEnergy         = 0.;
  fTotalEnergy         = 0.;
  fHitPosition.SetXYZ(0.,0.,0.);
  fKineticEnergy       = 0.;
  fN_Photons           = 0.;
  fEEEdeposit          = 0.;
  fLocalTime           = 0.;
  fGlobalTime          = 0.;
  TObject::Clear(opt);
}

//________________________________________________________________________________
EventPrimary::EventPrimary(): TObject()
{
  fTrackID       = 0;
  fName          = ""; 
  fMass          = 0.;
  fCharge        = 0.;
  fTotalEnergy   = 0.; 
  fPolarization.SetXYZ(0.,0.,0.);
  fMomentum.SetXYZ(0.,0.,0.);
}

//______________________________________________________________________________
EventPrimary::EventPrimary(const EventPrimary& orig):TObject(orig)
{
  fTrackID       = orig.fTrackID;
  fName          = orig.fName; 
  fMass          = orig.fMass;
  fCharge        = orig.fCharge;
  fTotalEnergy   = orig.fTotalEnergy; 
  fPolarization  = orig.fPolarization;
  fMomentum      = orig.fMomentum;
}

//________________________________________________________________________________
void EventPrimary::Clear(Option_t* opt)
{
  fTrackID       = 0; 
  fName          = "";
  fMass          = 0; 
  fCharge        = 0.;
  fTotalEnergy   = 0.;
  fPolarization.SetXYZ(0.,0.,0.);
  fMomentum.SetXYZ(0.,0.,0.);
  TObject::Clear(opt);
}

//______________________________________________________________________________
MCEvent::MCEvent() : TObject()
{
  fEventName      = "";
  fEventNumber    = 0;
  fN_Primaries    = 0;
  fN_DetectorHits = 0; 
  fN_TargetHits   = 0;
  fEventPrimaries = new TClonesArray("EventPrimary", 20);
  fDetectorHits   = new TClonesArray("DetectorHit", 100);
  fTargetHits     = new TClonesArray("TargetHit", 100);
}
//______________________________________________________________________________
MCEvent::~MCEvent()
{
  Clear("all");
  if(fEventPrimaries) delete fEventPrimaries;  
  if(fTargetHits)     delete fTargetHits;
  if(fDetectorHits)   delete fDetectorHits;
}

//______________________________________________________________________________
EventPrimary* MCEvent::AddPrimary(EventPrimary* primaryPtr)
{
   TClonesArray &evPrimaries = *fEventPrimaries;
   EventPrimary *primary = new(evPrimaries[fN_Primaries++]) (EventPrimary)(*primaryPtr);
  
   return primary;
}

//______________________________________________________________________________
TargetHit *MCEvent::AddTargetHit(TargetHit *hitPtr)
{
   TClonesArray &tgtHits = *fTargetHits;
   TargetHit *hit = new(tgtHits[fN_TargetHits++]) (TargetHit)(*hitPtr);

   return hit;
}

//______________________________________________________________________________
DetectorHit *MCEvent::AddDetectorHit(DetectorHit *hitPtr)
{
   TClonesArray &detectorHits = *fDetectorHits;
   DetectorHit *hit = new(detectorHits[fN_DetectorHits++]) (DetectorHit)(*hitPtr);
  
   return hit;
}

//______________________________________________________________________________
void MCEvent::Clear(Option_t *opt)
{
  fEventName      = "";
  fEventNumber    = 0;
  fN_Primaries    = 0;
  fN_DetectorHits = 0; 
  fN_TargetHits   = 0;
  if(fEventPrimaries) fEventPrimaries->Clear(opt); //also calls EventPrimary::Clear 
  if(fTargetHits)     fTargetHits->Clear(opt);     //also calls TargetHit::Clear
  if(fDetectorHits)   fDetectorHits->Clear(opt);   //also calls DetectorHit::Clear
}



