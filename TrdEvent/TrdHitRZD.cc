/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: TrdHitRZD.cc,v 1.3 2010/08/18 18:34:19 beischer Exp $
/////////////////////////////////////////////////////////////////

#include "TrdHitRZD.hh"

#include "TrdRawHitR.hh"

TrdHitRZD::TrdHitRZD(TrdRawHitR* hit)
{
  int layer  = hit->Layer;
  int ladder = hit->Ladder;
  int tube   = hit->Tube;
  int dir;

  if(layer<12) ladder++;
  if(layer< 4) ladder++;

  if((layer>=16)||(layer<=3)) dir = 1;
  else                        dir = 0;

  float z = 85.275 + 2.9*(float)layer;
  if(ladder%2==0) z += 1.45;

  float x = 10.1*(float)(ladder-9);

  if((dir==1) && (ladder>=12)) x+=0.78;
  if((dir==1) && (ladder<= 5)) x-=0.78;

  x += 0.31 + 0.62*(float)tube;
  if(tube >=  1) x+=0.03;
  if(tube >=  4) x+=0.03;
  if(tube >=  7) x+=0.03;
  if(tube >=  9) x+=0.03;
  if(tube >= 12) x+=0.03;
  if(tube >= 15) x+=0.03;

  m_r = x;
  m_z = z;
  m_d = dir;
}

TrdHitRZD::~TrdHitRZD()
{
}

