#ifndef ConfigElements_h 
#define ConfigElements_h 1

#include <string>

class ROModel
{
public:
  ROModel();
  ROModel(const ROModel& orig);
  ~ROModel(){};

  inline void SetIndex(int i)          { index=i;  };
  inline void SetMinCh(int i)          { ch_min=i; };
  inline void SetMaxCh(int i)          { ch_max=i; };
  inline void SetModel(std::string m)  { model=m;  };

  inline int GetIndex()         { return index;  };
  inline int GetMinCh()         { return ch_min; };
  inline int GetMaxCh()         { return ch_max; };
  inline std::string GetModel() { return model;  };
private:
  int index;
  int ch_min;
  int ch_max;
  std::string model;
};

class ROModelAttributes
{
public:
  ROModelAttributes();
  ROModelAttributes(const ROModelAttributes& orig);
  ~ROModelAttributes(){};

  void SetHeader(int i)        { header=i;    };
  void SetDataMask(int i)      { data_mask=i; };
  void SetChanMask(int i)      { chan_mask=i; };
  void SetChanShift(int i)     { chan_shift=i;};

  int GetHeader()        { return header;    };
  int GetDataMask()      { return data_mask; };
  int GetChanMask()      { return chan_mask; };
  int GetChanShift()     { return chan_shift;};

private:
  int header;
  int data_mask;
  int chan_mask;
  int chan_shift;

};

class SubSystem
{
public:
  SubSystem();
  SubSystem(const SubSystem& orig);
  ~SubSystem(){};

  inline void SetID(int i)              { id=i;           };
  inline void SetAttr(std::string attr) { attribute=attr; };
  inline void SetName(std::string m)    { name=m;         };

  inline int GetID()                { return id;        };
  inline std::string GetAttr()      { return attribute; };
  inline std::string GetName()      { return name;      };
  
private:
 
  int          id;
  std::string  attribute;
  std::string  name;

};


#endif
