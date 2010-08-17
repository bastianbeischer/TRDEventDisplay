#ifndef __AMSACCRhit__
#define __AMSACCRhit__
#include "TObject.h"

class AccRawHitR {
public:
  AccRawHitR();
  AccRawHitR(int id, int sdr, int cha, float amp);
  virtual ~AccRawHitR();

public:
  int swid;
  int SDR;   ///< SDR2 (0-3)
  int Channel;  ///< Channel number (0-3)
  float Amp;   ///< amplitude (adc counts*8)

  ClassDef(AccRawHitR,1)       //AccRawHitR
};

#endif
