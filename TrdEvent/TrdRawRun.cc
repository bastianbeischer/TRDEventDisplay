/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: TrdRawRun.cc,v 1.3 2010/08/18 18:34:19 beischer Exp $
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
