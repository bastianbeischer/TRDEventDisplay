/////////////////////////////////////////////////////////////////
// CVS Information
// $Id: TrdRawHitR.hh,v 1.2 2010/08/18 18:22:02 beischer Exp $
/////////////////////////////////////////////////////////////////

#ifndef __AMSTRDRhit__
#define __AMSTRDRhit__
#include "TObject.h"

class TrdRawHitR {
public:
  TrdRawHitR();
  TrdRawHitR(int lay, int lad, int tub, float amp);
  virtual ~TrdRawHitR();

public:
  int Layer;   ///< Layer 0(bottom)...19(top) 
  int Ladder;  ///< Ladder number
  int Tube;    ///< tube number
  float Amp;   ///< amplitude (adc counts)
  int Haddr;   ///< Hardware Address cufhh  c crate[0-1],u udr[0-6] f ufe [0-7] hh channel[0-63]

  ClassDef(TrdRawHitR,1)       //TrdRawHitR
};

#endif
