#include "GraphicsView.hh"

#include <QMouseEvent>
#include <QWheelEvent>

#include <cmath>

#include "Scene.hh"

// constructor
GraphicsView::GraphicsView(QWidget* parent) :
  QGraphicsView(parent),
  m_zoomFactor(1.2)
{
  setDragMode(ScrollHandDrag);
  setScene(new Scene());
  show();
}

// destructor
GraphicsView::~GraphicsView()
{
}

//! overloaded mouse press event, refit the scene on mid mouse button press
void GraphicsView::mousePressEvent(QMouseEvent* event)
{
  QGraphicsView::mousePressEvent(event);
  if (event->button() == Qt::MidButton)
    fitScene();
}

//! overloaded virtual function, telling the view to zoom on mouse wheel events
void GraphicsView::wheelEvent(QWheelEvent* event)
{
  centerOn(mapToScene(event->pos()));
  if (event->delta() > 0) zoomIn();
  if (event->delta() < 0) zoomOut();
}

