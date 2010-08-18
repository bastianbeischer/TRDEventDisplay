/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: TrdHitRZD.hh,v 1.3 2010/08/18 18:34:19 beischer Exp $
/////////////////////////////////////////////////////////////////

#ifndef TrdHitRZD_hh
#define TrdHitRZD_hh

class TrdRawHitR;

class TrdHitRZD
{

public:
  TrdHitRZD(TrdRawHitR* hit);
  ~TrdHitRZD();
  
public:
  double r() const {return m_r;}
  double z() const {return m_z;}
  double d() const {return m_d;}

private:
  double m_r,m_z;
  int m_d;
  
};

#endif /* TrdHitRZD_hh */


