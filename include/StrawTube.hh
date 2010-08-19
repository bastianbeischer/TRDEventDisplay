/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: StrawTube.hh,v 1.8 2010/08/19 20:56:12 beischer Exp $
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

};

#endif /* StrawTube_hh */
