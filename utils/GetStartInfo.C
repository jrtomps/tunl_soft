
void GetStartInfo(TString in_file_name)
{

  //load the libdata_structure.so
  if(!TClassTable::GetDict("RawData"))
    gSystem->Load("libdata_structure.so");

  //open the root file in read mode
  
  TFile *inRoot_file = new TFile(in_file_name, "READ");

  //Get Run information.. RunStartTime, 
  //Number of event in the run etc.
  RunControlEvent *fStartInfo = (RunControlEvent*) inRoot_file->Get("StartInfo");

  TTimeStamp *fStartTime = new TTimeStamp(fStartInfo->GetTime());

  cout<<"The Go event time is: ";
  fStartTime->Print();
  cout<<"There are "<<fStartInfo->GetNumEvents()<<" events in the run \n";
  inRoot_file->Close();
}
