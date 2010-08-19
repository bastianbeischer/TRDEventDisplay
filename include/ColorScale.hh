/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: ColorScale.hh,v 1.1 2010/08/19 15:40:50 beischer Exp $
/////////////////////////////////////////////////////////////////

#ifndef ColorScale_hh
#define ColorScale_hh

#include <QLinearGradient>

class ColorScale :
  public QObject,
  public QLinearGradient
{

Q_OBJECT
  
public:
  ColorScale(double min = 0., double max = 1.);
  ~ColorScale();
  
public slots:
  void changeMin(int newValue) {m_min = newValue;}
  void changeMax(int newValue) {m_max = newValue;}

public:
  QColor color(double value);

private:
  double m_min;
  double m_max;
  
};

#endif /* ColorScale_hh */
