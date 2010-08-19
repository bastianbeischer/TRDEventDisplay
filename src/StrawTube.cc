/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: StrawTube.cc,v 1.6 2010/08/19 15:40:51 beischer Exp $
/////////////////////////////////////////////////////////////////

#include "StrawTube.hh"

#include <QPen>
#include <QBrush>

#include <cmath>

// constructor
StrawTube::StrawTube(double x, double y) :
  m_width(0.62),
  m_height(1.2),
  m_signalStretchFactorX(1.),
  m_signalStretchFactorY(1.5)
{
  reInit();
  setPos(x,y);
}

// destructor
StrawTube::~StrawTube()
{
}

// reset attributes
void StrawTube::reInit()
{
  setRect(-m_width/2., -m_height/2., m_width, m_height);

  QPen pen(Qt::lightGray);
  pen.setStyle(Qt::SolidLine);
  setPen(pen);

  QBrush brush(Qt::lightGray);
  brush.setStyle(Qt::SolidPattern);
  setBrush(brush);
}

// apply color based on a linear interpolation between blue,green and red
void StrawTube::colorize(QColor color)
{
  QBrush brush(color);
  setBrush(brush);

  // stretch the rectangle so that signals are easier to make see
  double newLeft = m_signalStretchFactorX * rect().left();
  double newWidth = qAbs(2. * newLeft);
  double newTop = m_signalStretchFactorY * rect().top();
  double newHeight = qAbs(2. * newTop);
  setRect(QRectF(newLeft, newTop, newWidth, newHeight));

  // QPen pen(Qt::black);
  // setPen(pen);
}

// hide the tube (setVisible(false) would also hide it from selection with itemAt(x,y) which is not what I want)
void StrawTube::makeInvisible()
{
  setPen(Qt::NoPen);
  setBrush(Qt::NoBrush);
}
