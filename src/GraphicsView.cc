#include "GraphicsView.hh"

#include <QMouseEvent>
#include <QWheelEvent>

#include <cmath>

#include "Scene.hh"

// constructor
GraphicsView::GraphicsView(QWidget* parent) :
  QGraphicsView(parent),
  m_scene(new Scene()),
  m_zoomLevel(1.0)
{
  setDragMode(ScrollHandDrag);
  setScene(m_scene);
  show();
}

// destructor
GraphicsView::~GraphicsView()
{
  delete m_scene;
}


//! overloaded virtual function, telling the scene what to do with mouse wheel events
void GraphicsView::wheelEvent(QWheelEvent* event)
{
  centerOn(mapToScene(event->pos()));

  if (event->delta() > 0) zoomIn();
  if (event->delta() < 0) zoomOut();

  event->setAccepted(true);
}

//! set new zoom level
void GraphicsView::changeZoomLevel(double newZoomLevel) 
{
  if (newZoomLevel != m_zoomLevel) {
    scale(newZoomLevel/m_zoomLevel, newZoomLevel/m_zoomLevel);
    m_zoomLevel = newZoomLevel;
  }
}

