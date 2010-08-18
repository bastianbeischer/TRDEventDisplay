/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: View.cc,v 1.3 2010/08/18 18:37:10 beischer Exp $
/////////////////////////////////////////////////////////////////

#include "View.hh"

#include <QMouseEvent>
#include <QWheelEvent>

// constructor
View::View(QWidget* parent) :
  QGraphicsView(parent),
  m_zoomFactor(1.2)
{
  setDragMode(ScrollHandDrag);
  show();
}

// destructor
View::~View()
{
}

// overloaded mouse press event, refit the scene on mid mouse button press
void View::mousePressEvent(QMouseEvent* event)
{
  QGraphicsView::mousePressEvent(event);
  if (event->button() == Qt::MidButton)
    fitScene();
}

// overloaded virtual function, telling the view to zoom on mouse wheel events
void View::wheelEvent(QWheelEvent* event)
{
  centerOn(mapToScene(event->pos()));
  if (event->delta() > 0) zoomIn();
  if (event->delta() < 0) zoomOut();
}

