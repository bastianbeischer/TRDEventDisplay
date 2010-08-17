#include "TrdRawEvent.hh"

ClassImp(TrdRawEvent);

TrdRawEvent::TrdRawEvent()
{
}

TrdRawEvent::~TrdRawEvent()
{
}

void TrdRawEvent::Reset()
{
  evid=0;
  evbuilttime=0;
  evbuiltfinetime=0;
  evbuilterr=0;
  ftrpat=0;
  lv1pat=0;
  accpat=0;
  tofpat=0;
  evtime=0;
  hits.clear();
  acchits.clear();
}

