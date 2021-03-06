#include "evioUtil.hxx"

const int DBI2_WA  = 0xDB2A0000; 
const int DBI2_WOA = 0xDB2B0000; 
const int DBI4_WA  = 0xDB4A0000; 
const int DBI4_WOA = 0xDB4B0000;

const int ReadOutType = 0xFFFF0000;

const int SLOT_MASK  = 0x0000001F;   // TUNL standards in special 
const int SLOT_SHIFT  = 0;           // model header word
const int CRATE_MASK = 0x000000E0;
const int CRATE_SHIFT = 5;
const int WDCNT_MASK = 0x0000FF00;
const int WDCNT_SHIFT = 8; 

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
  bool isScalerEvent(const evio::evioDOMNodeP nodePtr);

private:
  void parse_db4a(uint32_t longword, int DATA_MASK, int CHAN_MASK, int CHAN_SHIFT);
  void parse_db4b(uint32_t longword, int &ch, int DATA_MASK);
  void parse_db2a(uint32_t longword, int DATA_MASK, int CHAN_MASK,
                  int CHAN_SHIFT, int &ch, unsigned int word_num);
  void parse_db2b(uint32_t longword, int DATA_MASK,
                  int &ch, unsigned int word_num);
public:
  void ProcessNodes(const evio::evioDOMNodeP nodePtr) ;
  void SkipNodes(const evio::evioDOMNodeP nodePtr) ;

private:
  ConfigManager* fConfigManager;
  DataManager*   fDataManager;

  RawData*         fEvent;
  RunInfo*         fRunInfo;
  RunControlEvent* fStartInfo;
  RunControlEvent* fEndInfo;
  HardwareData*    fHardwareData;

  int EventNumber;
  int RunNumber;
  double RawDatArray[200];

};
