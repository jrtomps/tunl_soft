
void GetRunInfo(TString in_file_name)
{
  //load the libdata_structure.so
  if(!TClassTable::GetDict("RawData"))
    gSystem->Load("libdata_structure.so");

  //open the root file in read mode
  
  TFile *inRoot_file = new TFile(in_file_name, "READ");

  //Get Run information.. RunNumber, RunStartTime, 
  //Number of event in the run etc.
  RunInfo *fRunInfo = (RunInfo*) inRoot_file->Get("RunInfo");

  TTimeStamp *fPreStartTime = new TTimeStamp(fRunInfo->GetTime());

  cout<<"Run Number = "<<fRunInfo->GetRunNumber()<<endl;
  cout<<"The PreStart event time is: ";
  fPreStartTime->Print();
  inRoot_file->Close();
}
