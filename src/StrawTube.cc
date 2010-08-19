/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: StrawTube.cc,v 1.7 2010/08/19 15:54:09 beischer Exp $
/////////////////////////////////////////////////////////////////

#include "StrawTube.hh"

#include <QPen>
#include <QBrush>

#include <cmath>

// constructor
StrawTube::StrawTube(double x, double y) :
  m_width(0.62),
  m_height(1.2)
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

// apply signal color
void StrawTube::colorize(QColor color)
{
  setBrush(color);
}

// stretch rectangle to represent signals
void StrawTube::stretch(double factorX, double factorY)
{
  double newLeft = factorX * rect().left();
  double newWidth = qAbs(2. * newLeft);
  double newTop = factorY * rect().top();
  double newHeight = qAbs(2. * newTop);
  setRect(QRectF(newLeft, newTop, newWidth, newHeight));
}

// hide the tube (setVisible(false) would also hide it from selection with itemAt(x,y) which is not what I want)
void StrawTube::makeInvisible()
{
  setPen(Qt::NoPen);
  setBrush(Qt::NoBrush);
}
