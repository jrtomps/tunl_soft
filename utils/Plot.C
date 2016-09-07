
void Plot(Int_t RunNumber)
{
  const Int_t NumDetectors =4;

  //Declare 6 histogram pointers
  TH1F* hists[NumDetectors];

  //instantiate the hitogram objects
  for(Int_t i=0; i<NumDetectors; i++)
    {
      hists[i] = new TH1F(Form("hits_%d", i), 
			  Form("Core_%d_ADC", i+1), 
			  4097,-0.5,4096.5);
      hists[i]->SetDirectory(0);
    }

  //Load the data structure shared object
  if(!TClassTable::GetDict("RawData"))
    gSystem->Load("libdata_structure.so");

  if(!TClassTable::GetDict("DetectorClass"))
    gSystem->Load("../../example_scripts/libDetectorClass.so");


  //Load GetRunInfo, GetStartInfo and GetEndInfo macros
  //make sure to use the correct path
  gROOT->ProcessLine(".L ${MY_EXPERIMENT}/../example_scripts/GetRunInfo.C");
  gROOT->ProcessLine(".L ${MY_EXPERIMENT}/../example_scripts/GetStartInfo.C");
  gROOT->ProcessLine(".L ${MY_EXPERIMENT}/../example_scripts/GetEndInfo.C");


  //Form an input file name given the run number
  TString in_file_name 
    = Form("${RELEASE_ROOT_FILE_PATH}/run%d_tree.root", RunNumber);

  //Print-out some run information
  GetRunInfo(in_file_name);
  cout<<endl<<endl;
  GetStartInfo(in_file_name);


  //Open the root file in "READ" mode
  TFile *inRoot_file = new TFile(in_file_name, "READ");

  //Get a pointer to the flat tree in the root file
  TTree* tt = (TTree*) inRoot_file->Get("event_tree");

  //Get a pointer to the EventBranch
  //!!!NOTE the difference compared to flat trees
  TBranch* event_branch = tt->GetBranch("EventBranch");

  //Declare a pointer to a RawData object
  RawData* event;// = new RawData();

  //Declare a pointer to HardwareData
  HardwareData* hd;

  //Declare a pointer to a TClonesArray
  TClonesArray* data_array;

  //Set the address of the branch to the just declared pointer
  event_branch->SetAddress(&event);


  DetectorClass * detector[4];
  for(Int_t i=0; i<4; i++)
    detector[i] = new DetectorClass(Form("detector%d", i+1));
  
  //Loop over the TTree entries and fill the hitograms
  for(Int_t i=0; i<tt->GetEntries(); i++)
    {
      //!!!NOTE getting the entry from event branch and not from the tree
      event_branch->GetEntry(i);
      //Get the data array for the current event
      data_array = event->GetRawData();
      
      for(Int_t k=0; k<4; k++)
	{
	  detector[k]->Initialize(data_array);
	  hists[k]->Fill(detector[k]->GetCoreEnergy());
	}
    }

  //Close the input ROOT file
  inRoot_file->Close();

  //Print-out RunEnd Info
  GetEndInfo(in_file_name);

  //Create a TCanvas with 6 TPads
  TCanvas *can = new TCanvas();
  can->Divide(2, 2);

  //Draw the hitograms
  for(Int_t i=0; i<NumDetectors; i++)
    {
      can->cd(i+1);
      hists[i]->Draw();
    }
}
