void PlotEventTree(Int_t RunNumber)
{
  const Int_t NumDetectors =6;

  //Declare 6 histogram pointers
  TH1F* hists[NumDetectors];

  //instantiate the hitogram objects
  for(Int_t i=0; i<NumDetectors; i++)
    {
      hists[i] = new TH1F(Form("hits_%d", i), 
			  Form("Det_%d_ADC", i+1), 
			  4097,-0.5,4096.5);
      hists[i]->SetDirectory(0);
    }

  //Load the data structure shared object
  if(!TClassTable::GetDict("RawData"))
    gSystem->Load("libdata_structure.so");


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


  //Loop over the TTree entries and fill the hitograms
  for(Int_t i=0; i<tt->GetEntries(); i++)
    {
      //!!!NOTE getting the entry from event branch and not from the tree
      event_branch->GetEntry(i);
      //Get the data array for the current event
      data_array = event->GetRawData();
      
      
      //How to fill histograms #1
      //loop over the elements of the data array and pick out what's needed
      for(Int_t k=0; k<data_array->GetEntries(); k++)
	{
	   //Get an element of data_array
	  hd = (HardwareData*) data_array->At(k);

	  //we can get away with ONLY check the attribute to make sure 
	  //we are getting the right element of the data array; simple ro_config.xml
	  //if(hd->GetAttribute()=="adc"&&hd->GetName()=="det1") 
	  //would be a stricter selection rule
	  if(hd->GetAttribute()=="adc" && hd->GetID()<7)
	    hists[hd->GetID()-1]->Fill(hd->GetValue());
	}
      

      //How to fill histogram #2
      //Using the GetByName(), GetByNameId(), GetByIndexChannel() methods of the RawData class
      //to fille the histograms is equivalent to using flat trees
      //it's less stuff to type but introduces extra zeros
      /*
      for(Int_t k=0; k<NumDetectors; k++)
	hists[k]->Fill(event->GetByName(Form("det%d", k+1)));
      */
    }

  /*
      //How to fill histograms #3
      //!!!NOTE we are outside of the event loop
      //Using the TTree::Draw() method
      //Dirrect access to the memeber variables of RawData and HardwareData
      //Folloing methods of accessing data can be very useful on command line
      //where you do not have control over the event loop
      tt->Draw("fVal>>hists_3", "fAttr.fData==\"adc\"&&fID==5");
      tt->Draw("fVal>>hists_4", "fName.fData==\"det5\"");
      
      //we can mix the use of the member functions and member variables

      tt->Draw("GetValue()>>hists_5", "fName.fData==\"det6\" && GetEventNumber()<20000");
  */

  //Close the input ROOT file
  inRoot_file->Close();

  //Print-out RunEnd Info
  GetEndInfo(in_file_name);

  //Create a TCanvas with 6 TPads
  TCanvas *can = new TCanvas();
  can->Divide(3, 2);

  //Draw the hitograms
  for(Int_t i=0; i<NumDetectors; i++)
    {
      can->cd(i+1);
      hists[i]->Draw();
    }
}
