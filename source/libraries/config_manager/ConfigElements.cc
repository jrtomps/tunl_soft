
#include "ConfigElements.hh"

ROModel::ROModel()
{
  index  = -1;
  ch_min = -1;
  ch_max = -1;
  model  = "";
}


ROModel::ROModel(const ROModel& orig)
{
  index  = orig.index;
  ch_min = orig.ch_min;
  ch_max = orig.ch_max;
  model  = orig.model;
}
//--------------------------------------------------

ROModelAttributes::ROModelAttributes()
{
  header     = -1;
  data_mask  = -1;
  chan_mask  = -1;
  chan_shift = -1;
}

ROModelAttributes::ROModelAttributes(const ROModelAttributes& orig)
{
  header     = orig.header;
  data_mask  = orig.data_mask;
  chan_mask  = orig.chan_mask;
  chan_shift = orig.chan_shift;
}

//-------------------------------------------

SubSystem::SubSystem()
{
  id        = -1;
  attribute = "";
  name      = "";
}

SubSystem::SubSystem(const SubSystem &orig)
{
  id        = orig.id;
  attribute = orig.attribute;
  name      = orig.name;
}



/*
ClassImp(Module)
ClassImp(SubSystem)

Module::Module():TObject()
{
  index  = -1;
  roc    = -1;
  crate  = -1;
  slot   = -1;
  ch_min = -1;
  ch_max = -1;
  model  = "";
}


Module::Module(const Module& orig):TObject(orig)
{
  index  = orig.index;
  roc    = orig.roc;
  crate  = orig.crate;
  slot   = orig.slot;
  ch_min = orig.ch_min;
  ch_max = orig.ch_max;
  model  = orig.model;
}

//-------------------------------------------

SubSystem::SubSystem():TObject()
{
  index     = -1;
  channel   = -1;
  id        = -1;
  attribute = "";
  name      = "";
}



SubSystem::SubSystem(const SubSystem &orig):TObject(orig)
{
  index     = orig.index;
  channel   = orig.channel;
  id        = orig.id;
  attribute = orig.attribute;
  name      = orig.name;
}
*/
