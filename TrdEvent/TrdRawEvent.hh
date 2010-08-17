#ifndef TrdRawEvent_hh
#define TrdRawEvent_hh

#include "TrdRawHitR.hh"
#include "AccRawHitR.hh"
#include "TObject.h"
#include <vector>

class TrdRawEvent
{
public:
  TrdRawEvent();
  virtual ~TrdRawEvent();

  std::vector<TrdRawHitR> *GetHits(){return &hits;}
  std::vector<AccRawHitR> *GetAccHits(){return &acchits;}

  void Reset();

public:
  int evid;
  int evbuilttime;
  int evbuiltfinetime;
  int evbuilterr;
  long long evtime; 
  int ftrpat;
  int lv1pat;
  int accpat;
  int tofpat;

  std::vector<TrdRawHitR> hits;
  std::vector<AccRawHitR> acchits;

  ClassDef(TrdRawEvent,1);
};

#endif /* TrdRawEvent_hh */
