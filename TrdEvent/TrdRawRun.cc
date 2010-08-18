/////////////////////////////////////////////////////////////////
// CVS Information
// $Id: TrdRawRun.cc,v 1.2 2010/08/18 18:22:02 beischer Exp $
/////////////////////////////////////////////////////////////////

#include "TrdRawRun.hh"

ClassImp(TrdRawRun);

TrdRawRun::TrdRawRun()
{
}

TrdRawRun::~TrdRawRun()
{
}

void TrdRawRun::Reset()
{
  runid=0;
  runtag=0;
  events.clear();
}
