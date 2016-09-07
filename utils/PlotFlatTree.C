void PlotFlatTree(Int_t RunNumber)
{
  const Int_t NumDetectors =6;
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
  TTree* tt = (TTree*) inRoot_file->Get("flat_tree");

  //Declare 6 histogram pointers
  TH1F* hists[NumDetectors];
 
  //Declare 6 Double_t variables to hold the values from 6 branches
  Double_t det_val[NumDetectors]={0., 0., 0., 0., 0., 0.};

  //instantiate the hitogram objects and set the TTree branch addresses  
  for(Int_t i=0; i<NumDetectors; i++)
    {
      hists[i] = new TH1F(Form("hits_%d", i), Form("Det_%d_ADC", i+1), 4097,-0.5,4096.5);
      hists[i]->SetDirectory(0);
      tt->SetBranchAddress(Form("det%d", i+1), &det_val[i]);
    }

  //Loop over the TTree entries and fill the hitograms
  for(Int_t i=0; i<tt->GetEntries(); i++)
    {
      tt->GetEntry(i);
      for(Int_t k=0; k<NumDetectors; k++)hists[k]->Fill(det_val[k]);
    }

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
