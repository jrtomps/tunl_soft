#include "evioUtil.hxx"
#include "ConfigManager.hh"
#include "DataManager.hh"
#include "NodeProcessor.hh"

#include "TString.h"

using namespace evio;
using namespace std;


NodeProcessor* fNodeProcessor;

void NodeParser(evioDOMNodeP nodePtr)
{
  fNodeProcessor->ProcessNodes(nodePtr);
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
      cout<<"No imput file specified... exiting"<<endl;
      exit(0);
    }

  DataManager* fDataManager =  DataManager::GetInstance();
  fDataManager->open(atoi(argv[1]));

  fNodeProcessor = new NodeProcessor();

  TString fCodaFilePath = getenv("RELEASE_CODA_FILE_PATH");
  Ssiz_t from   = fCodaFilePath.Last('/');
  Ssiz_t length = fCodaFilePath.Length() - fCodaFilePath.Last('/');
  TString fCodaFileName = fCodaFilePath(from, length);

  TString fCodaFileFullPath = fCodaFilePath+fCodaFileName+'_'+argv[1];

  try
    {
      //new evio channel object to read in the file
      evioFileChannel channel(fCodaFileFullPath.Data(), "r");
      
      //open the data file
      channel.open();
           
      //read in the events sequantially
      while(channel.read())
      {
	//create a DOM Tree from the contents of the file
	evioDOMTree event(channel);
	  
	evioDOMNodeListP NodeList = event.getNodeList();
	  
	for_each(NodeList->begin(), NodeList->end(), NodeParser);
      }    
      
      //EOF.. close the file
      channel.close();
    }
  catch(evioException e)
    {
      cerr<< endl << e.toString() << endl << endl;
      exit(EXIT_FAILURE);
    }

  fDataManager->close();
  
  delete fNodeProcessor;
  
  //finished
  exit(EXIT_SUCCESS);
}
