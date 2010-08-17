#ifndef TrdRawRun_hh
#define TrdRawRun_hh

#include <vector>
#include "TrdRawEvent.hh"

class TrdRawRun
{
public:
  TrdRawRun();
  virtual ~TrdRawRun();
  
  std::vector<TrdRawEvent> *GetEvents(){return &events;}

  void Reset();

public:
  unsigned int runid;
  unsigned int runtag;
  std::vector<TrdRawEvent> events;
  
  ClassDef(TrdRawRun,1);
};

#endif /* TrdRawRun_hh */
