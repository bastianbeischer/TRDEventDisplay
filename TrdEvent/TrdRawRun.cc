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
