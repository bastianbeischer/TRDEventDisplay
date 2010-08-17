#include "StrawTube.hh"

#include <QPen>
#include <QBrush>

#include <cmath>

StrawTube::StrawTube(double x, double y) :
  m_width(0.62),
  m_height(1.2),
  m_signalStretchFactorX(1.),
  m_signalStretchFactorY(1.5)
{
  reInit();
  setPos(x,y);
}

StrawTube::~StrawTube()
{
}

void StrawTube::reInit()
{
  setRect(-m_width/2., -m_height/2., m_width, m_height);

  QPen pen(Qt::lightGray);
  QBrush brush(Qt::lightGray);

  pen.setStyle(Qt::SolidLine);
  brush.setStyle(Qt::SolidPattern);

  setPen(pen);
  setBrush(brush);
}

void StrawTube::colorize(double fraction)
{
  // interpolate colors between blue and green for the signals between lower end and middle of axis and between green and red for middle to upper end
  QColor signalColor;
  if (fraction < 0.5) {
    fraction *= 2.0;
    signalColor = QColor(0, floor(255*(fraction)), floor(255*(1.0-fraction)), 255);
  }
  else {
    fraction -= 0.5;
    fraction *= 2.0;
    signalColor = QColor(floor(255*fraction), floor(255*(1.0-fraction)),0, 255);
  }

  // apply color and add the tube to the scene
  QBrush brush(signalColor);
  setBrush(brush);

  double newLeft = m_signalStretchFactorX * rect().left();
  double newWidth = qAbs(2. * newLeft);
  double newTop = m_signalStretchFactorY * rect().top();
  double newHeight = qAbs(2. * newTop);
  setRect(QRectF(newLeft, newTop, newWidth, newHeight));

  // QPen pen(Qt::black);
  // setPen(pen);
}

void StrawTube::makeInvisible()
{
  setPen(Qt::NoPen);
  setBrush(Qt::NoBrush);
}
