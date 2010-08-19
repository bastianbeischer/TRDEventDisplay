/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: TrdRawRun.hh,v 1.4 2010/08/19 20:55:33 beischer Exp $
/////////////////////////////////////////////////////////////////

#ifndef TrdRawRun_hh
#define TrdRawRun_hh

#include <vector>
#include "TrdRawEvent.hh"

class TrdRawRun
{
public:
  TrdRawRun();
  virtual ~TrdRawRun();
  
  const std::vector<TrdRawEvent> *GetEvents() const {return &events;}

  void Reset();

public:
  unsigned int runid;
  unsigned int runtag;
  std::vector<TrdRawEvent> events;
  
  ClassDef(TrdRawRun,1);
};

#endif /* TrdRawRun_hh */
