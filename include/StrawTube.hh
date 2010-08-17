#ifndef StrawTube_hh
#define StrawTube_hh

#include <QGraphicsRectItem>

class StrawTube :
  public QGraphicsRectItem
{
  
public:
  StrawTube(double x, double y);
  ~StrawTube();
  
  void reInit();

  void displayHit(double fraction);
  void makeInvisible();

private:
  double m_width;
  double m_height;

  double m_signalStretchFactorX;
  double m_signalStretchFactorY;

};

#endif /* StrawTube_hh */
