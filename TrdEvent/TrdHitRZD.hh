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


