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
