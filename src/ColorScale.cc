/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: ColorScale.cc,v 1.1 2010/08/19 15:40:51 beischer Exp $
/////////////////////////////////////////////////////////////////

#include "ColorScale.hh"

// constructor
ColorScale::ColorScale(double min, double max) :
  QObject(),
  QLinearGradient(QPointF(0., 1.), QPointF(1., 1.)),
  m_min(min),
  m_max(max)
{
  setCoordinateMode(QGradient::ObjectBoundingMode);
  setColorAt(0.0, Qt::blue);
  setColorAt(0.4, Qt::green);
  setColorAt(0.7, Qt::yellow);
  setColorAt(1.0, Qt::red);
}

// destructor
ColorScale::~ColorScale()
{
}

// compute color for a given value
QColor ColorScale::color(double value)
{
  // if value is outside of the scale boundaries, fix it to the minimum or maximum
  if (value < m_min) value = m_min;
  if (value > m_max) value = m_max;

  double fraction = (value - m_min) / (m_max - m_min);

  QGradientStop lower_stop = stops().first();
  foreach(QGradientStop upper_stop, stops()) {
    if (upper_stop != lower_stop && fraction >= lower_stop.first && fraction <= upper_stop.first) {
      fraction = (fraction - lower_stop.first) / (upper_stop.first - lower_stop.first);

      int lowerR, lowerG, lowerB, upperR, upperG, upperB, mixedR, mixedG, mixedB;
      lower_stop.second.getRgb(&lowerR, &lowerG, &lowerB);
      upper_stop.second.getRgb(&upperR, &upperG, &upperB);
      
      mixedR = (1. - fraction) * lowerR + fraction * upperR;
      mixedG = (1. - fraction) * lowerG + fraction * upperG;
      mixedB = (1. - fraction) * lowerB + fraction * upperB;

      return QColor(mixedR, mixedG, mixedB);
    }
    lower_stop = upper_stop;
  }

  // shouldn't happen!
  Q_ASSERT(true);
  return QColor();
}
