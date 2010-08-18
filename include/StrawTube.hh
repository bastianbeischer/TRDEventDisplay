/////////////////////////////////////////////////////////////////
// CVS Information
// $Id: StrawTube.hh,v 1.4 2010/08/18 18:22:03 beischer Exp $
/////////////////////////////////////////////////////////////////

#ifndef StrawTube_hh
#define StrawTube_hh

#include <QGraphicsRectItem>

class StrawTube :
  public QGraphicsRectItem
{
  
public:
  StrawTube(double x = 0., double y = 0.);
  ~StrawTube();
  
  void reInit();

  void colorize(double fraction);
  void makeInvisible();

private:
  double m_width;
  double m_height;

  double m_signalStretchFactorX;
  double m_signalStretchFactorY;

};

#endif /* StrawTube_hh */
