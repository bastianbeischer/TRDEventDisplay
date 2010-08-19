/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: StrawTube.hh,v 1.7 2010/08/19 15:54:09 beischer Exp $
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
  
public:
  void reInit();
  void colorize(QColor color);
  void stretch(double factorX, double factorY);
  void makeInvisible();

private:
  double m_width;
  double m_height;

  double m_signalStretchFactorX;
  double m_signalStretchFactorY;

};

#endif /* StrawTube_hh */
