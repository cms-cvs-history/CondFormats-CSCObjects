#ifndef CSCDDUMap_h
#define CSCDDUMap_h

#include "CondFormats/CSCObjects/interface/CSCMapItem.h"
#include <map>

class CSCDDUMap{
 public:
  CSCDDUMap();
  ~CSCDDUMap();

  typedef std::map< int,CSCMapItem::MapItem > CSCMap;
  CSCMap ddu_map;
};

#endif
