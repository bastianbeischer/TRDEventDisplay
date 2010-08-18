/////////////////////////////////////////////////////////////////
// CVS Information
// $Id: AccRawHitR.cc,v 1.2 2010/08/18 18:22:01 beischer Exp $
/////////////////////////////////////////////////////////////////

#include "AccRawHitR.hh"

ClassImp(AccRawHitR);

AccRawHitR::AccRawHitR() :
 swid(-1),
 SDR(-1),
 Channel(-1),
 Amp(-1)
{
}

AccRawHitR::AccRawHitR(int id, int sdr, int cha, float amp) : 
  swid(id),
  SDR(sdr),
  Channel(cha),
  Amp(amp)
{
}

AccRawHitR::~AccRawHitR()
{
}
