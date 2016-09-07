#include "evioUtil.hxx"

const int DBI4 = 0xDB4B0000;

const int ReadOutType = 0xFFFF0000;

const int SLOT_MASK  = 0x0000001F;   // TUNL standards in special 
const int SLOT_SHIFT  = 0;           // model header word
const int CRATE_MASK = 0x000000E0;
const int CRATE_SHIFT = 5;
const int WDCNT_MASK = 0x0000FFFF;
const int WDCNT_SHIFT = 0; 

class ConfigManager;
class DataManager;
class RawData;
class HardwareData;
class RunInfo;
class RunControlEvent;

class NodeProcessor
{

public:
  NodeProcessor();
  ~NodeProcessor(){};

  bool isEventID(const evio::evioDOMNodeP nodePtr);
  bool isSyncEvent(const evio::evioDOMNodeP nodePtr);
  bool isPreStartEvent(const evio::evioDOMNodeP nodePtr);
  bool isGoEvent(const evio::evioDOMNodeP nodePtr);
  bool isPauseEvent(const evio::evioDOMNodeP nodePtr);
  bool isEndEvent(const evio::evioDOMNodeP nodePtr);
  bool isPhysicsEvent(const evio::evioDOMNodeP nodePtr);

private:
void parse_word(uint32_t longword, int DATA_MASK, 
			       int chanL, int chanU);

public:
  void ProcessNodes(const evio::evioDOMNodeP nodePtr) ;

private:
  ConfigManager* fConfigManager;
  DataManager*   fDataManager;

  RawData*         fEvent;
  RunInfo*         fRunInfo;
  RunControlEvent* fStartInfo;
  RunControlEvent* fEndInfo;
  HardwareData*    fHardwareData;

};
