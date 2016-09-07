#include "evioUtil.hxx"
#include "ConfigManager.hh"
#include "DataManager.hh"
#include "NodeProcessor.hh"

#include "TString.h"
#include "TBenchmark.h"

#include "TSystem.h"

using namespace evio;
using namespace std;

//#define DEBUG_CONFIG 1

NodeProcessor* fNodeProcessor;
int last_tag=-1;
void NodeParser(evioDOMNodeP nodePtr)
{
  //  printf("NodeAddress: %i\n",nodePtr);
  //  printf("Tag: %i\n",nodePtr->tag);
  last_tag=nodePtr->tag;
  fNodeProcessor->ProcessNodes(nodePtr);
}

void NodeParser2(evioDOMNodeP nodePtr)
{
  last_tag=nodePtr->tag;
  fNodeProcessor->SkipNodes(nodePtr);
}

int main(int argc, char **argv)
{

  TString fConfigFilePath = getenv("RELEASE_CONFIG_PATH");

  ConfigManager* fConfigManager = ConfigManager::GetInstance();
  fConfigManager->ReadXMLfile(fConfigFilePath);

#ifdef DEBUG_CONFIG
  fConfigManager->DumpConfig();
#endif

  if(argc<=1)
    {
      cout<<"No input file specified... exiting"<<endl;
      exit(0);
    }

  Int_t realtime_flag=0;
  if (argc==3&&strcmp(argv[2],"-rt")==0){
    realtime_flag=1;
    printf("Realtime flag\n");
  }

  DataManager* fDataManager =  DataManager::GetInstance();
  fDataManager->open(atoi(argv[1]), fConfigManager->GetFlatTreeFlag());

  fNodeProcessor = new NodeProcessor();

  TString fCodaFilePath = getenv("RELEASE_CODA_FILE_PATH");
  Ssiz_t from   = fCodaFilePath.Last('/');
  Ssiz_t length = fCodaFilePath.Length() - fCodaFilePath.Last('/');
  TString fCodaFileName = fCodaFilePath(from, length);

  TString fCodaFileFullPath = fCodaFilePath+fCodaFileName+'_'+argv[1];

  //start benchmarking
  TBenchmark* benchmark =  new TBenchmark();
  benchmark->Start("parser_benchmark");      

  //-----------------------------------------
  /*
  if (realtime_flag==1){
    //Sean's continuous reader
    Int_t evnum=0;
    Int_t last_evnum=0;
    Int_t eof_flag=0;
    //  while (eof_flag==0){
    while (1){
      try
	{
	  //	printf("Opening datafile...\n");
	  evnum=0;
	  //new evio channel object to read in the file
	  //	  evioFileChannel channel(fCodaFileFullPath.Data(), "r");
	  evioFileChannel *channel=new evioFileChannel(fCodaFileFullPath.Data(), "r");
	  
	  //open the data file
	  channel->open();
	  
	  //read in the events sequentially
	  while(channel->read())
	    {
	      //create a DOM Tree from the contents of the file
	      evioDOMTree event(channel);
	      
	      evioDOMNodeListP NodeList = event.getNodeList();
	      
	      if (evnum>=last_evnum){
		for_each(NodeList->begin(), NodeList->end(), NodeParser);
	      }
	      else {
		//Skip the event
		//	      printf("Skipping event %i\n",evnum);
		for_each(NodeList->begin(), NodeList->end(), NodeParser2);
	      }
	      evnum++;
	    }    
	  
	  //EOF.. close the file
	  channel->close();
	  delete channel;
	  last_evnum=evnum;
	  eof_flag=1;
	  //Check that the end of file is really an end event
	  //If it is, break the infinite read loop
	  if (last_tag==20){
	    break;
	  }
	  else{
	    //	  fDataManager->close();
	    //	  fDataManager->open(atoi(argv[1]), fConfigManager->GetFlatTreeFlag());
	    printf("Waiting for more events...\n");
	    gSystem->Sleep(10000);
	  }
	}
      catch(evioException e)
	{
	  cerr<< endl << e.toString() << endl << endl;
	  fDataManager->close();
	  exit(EXIT_FAILURE);
	  //	fDataManager->open(atoi(argv[1]), fConfigManager->GetFlatTreeFlag());
	  //Wait 1 second for more events to get into the file
	  //	printf("Waiting for more events...\n");
	  //	gSystem->Sleep(1000);
	}
    }
  }
  else{
  */
    //-------------------------------------------------------
    //Original, sequential reader
    try
      {
	//new evio channel object to read in the file
	//	evioFileChannel channel(fCodaFileFullPath.Data(), "r");
	evioFileChannel *channel=new evioFileChannel(fCodaFileFullPath.Data(), "r");
	
	//open the data file
	channel->open();
	
	//read in the events sequentially
	while(channel->read())
	  {
	    //create a DOM Tree from the contents of the file
	    evioDOMTree event(channel);
	    
	    evioDOMNodeListP NodeList = event.getNodeList();
	    
	    for_each(NodeList->begin(), NodeList->end(), NodeParser);
	  }    
	
	//EOF.. close the file
	channel->close();
	delete channel;
      }
    catch(evioException e)
      {
	cerr<< endl << e.toString() << endl << endl;
	exit(EXIT_FAILURE);
      }
    //xoxo 
    //  } //closes the else
  
  //---------------------------------------------
  fDataManager->close();
  
  //show benchmark
  benchmark->Show("parser_benchmark");
  cout<<endl;  //do not remove me I am needed

  delete fNodeProcessor;
  
  //finished
  exit(EXIT_SUCCESS);
}
