#ifndef TrdRawEvent_hh
#define TrdRawEvent_hh

#include "TrdRawHit.h"
#include "AccRawHitR.hh"
#include "TObject.h"
#include <vector>

class TrdRawEvent
{
public:
  TrdRawEvent();
  virtual ~TrdRawEvent();

  const std::vector<TrdRawHitR> *GetHits() const {return &hits;}
  const std::vector<AccRawHitR> *GetAccHits() const {return &acchits;}

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
