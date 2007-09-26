#ifndef CSCChamberIndex_h
#define CSCChamberIndex_h

#include "CondFormats/CSCObjects/interface/CSCMapItem.h"
#include <vector>

class CSCChamberIndex{
 public:
  CSCChamberIndex();
  ~CSCChamberIndex();

  typedef std::vector< CSCMapItem::MapItem > CSCVector;
  CSCVector ch_index;
};

#endif
