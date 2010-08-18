/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: TrdRawHitR.cc,v 1.3 2010/08/18 18:34:19 beischer Exp $
/////////////////////////////////////////////////////////////////

#include "TrdRawHitR.hh"

ClassImp(TrdRawHitR)

TrdRawHitR::TrdRawHitR() :
  Layer(-1),
  Ladder(-1),
  Tube(-1),
  Amp(-1),
  Haddr(-1)
{
}

TrdRawHitR::TrdRawHitR(int lay, int lad, int tub, float amp) : 
  Layer(lay),
  Ladder(lad),
  Tube(tub),
  Amp(amp),
  Haddr(0)
{
}

TrdRawHitR::~TrdRawHitR()
{
}
