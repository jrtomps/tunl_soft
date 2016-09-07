
void GetEndInfo(TString in_file_name)
{

  //load the libdata_structure.so
  if(!TClassTable::GetDict("RawData"))
    gSystem->Load("libdata_structure.so");

  //open the root file in read mode
  
  TFile *inRoot_file = new TFile(in_file_name, "READ");

  //Get Run information.. RunEndTime, 
  //Number of event in the run etc.
  RunControlEvent *fEndInfo = (RunControlEvent*) inRoot_file->Get("EndInfo");

  TTimeStamp *fEndTime = new TTimeStamp(fEndInfo->GetTime());

  cout<<"The End event time is: ";
  fEndTime->Print();
  cout<<"There are "<<fEndInfo->GetNumEvents()<<" events in the run \n";
  inRoot_file->Close();
}
