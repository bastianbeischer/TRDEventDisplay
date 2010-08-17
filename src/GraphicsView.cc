#include "GraphicsView.hh"

#include <QMouseEvent>
#include <QWheelEvent>

#include <cmath>

#include "Scene.hh"

// constructor
GraphicsView::GraphicsView(QWidget* parent) :
  QGraphicsView(parent),
  m_scene(new Scene()),
  m_mousePressedAt(0),
  m_zoomRectangle(0),
  m_zoomLevel(1.0)
{
  setDragMode(ScrollHandDrag);
  setScene(m_scene);
  show();
}

// destructor
GraphicsView::~GraphicsView()
{
  delete m_mousePressedAt;
  delete m_zoomRectangle;
  delete m_scene;
}


//! set new zoom level
void GraphicsView::changeZoomLevel(double newZoomLevel) 
{
  if (newZoomLevel != m_zoomLevel) {
    scale(newZoomLevel/m_zoomLevel, newZoomLevel/m_zoomLevel);
    m_zoomLevel = newZoomLevel;
    emit zoomLevelChanged(newZoomLevel);
  }
}

//! zoom in
void GraphicsView::zoomIn() 
{
  double newZoom = 1.2*m_zoomLevel;
  changeZoomLevel(newZoom);
}

//! zoom out
void GraphicsView::zoomOut() 
{
  double newZoom = m_zoomLevel/1.2;
  changeZoomLevel(newZoom);
}

//! overloaded virtual function, telling the scene what to do with mouse clicks
void GraphicsView::mousePressEvent(QMouseEvent* mouseEvent) 
{
  QGraphicsView::mousePressEvent(mouseEvent);

  if (mouseEvent->button() == Qt::RightButton) {
    m_mousePressedAt = new QPointF(mapToScene(mouseEvent->pos()));
    m_zoomRectangle = new QGraphicsRectItem(m_mousePressedAt->x(), m_mousePressedAt->y(), 1, 1);
    m_zoomRectangle->setPen(QPen(Qt::DashLine));
    m_scene->addItem(m_zoomRectangle);
  }
}

//! overloaded virtual function, telling the scene what to do with mouse click releases
void GraphicsView::mouseReleaseEvent(QMouseEvent* mouseEvent) 
{
  QGraphicsView::mouseReleaseEvent(mouseEvent);

  if (mouseEvent->button() == Qt::RightButton) {
    fitInView(m_zoomRectangle, Qt::KeepAspectRatioByExpanding);
    if (items().contains(m_zoomRectangle)) m_scene->removeItem(m_zoomRectangle);
    if (m_mousePressedAt)  delete m_mousePressedAt;
  }  
}

//! overloaded virtual function, telling the scene what to do with mouse movements
void GraphicsView::mouseMoveEvent(QMouseEvent* mouseEvent) 
{
  QGraphicsView::mouseMoveEvent(mouseEvent);

  if (m_mousePressedAt){
    QPointF point = mapToScene(mouseEvent->pos());
    m_zoomRectangle->setRect(QRectF(*m_mousePressedAt, point));
  }
}

//! overloaded virtual function, telling the scene what to do with mouse wheel events
void GraphicsView::wheelEvent(QWheelEvent* event)
{
  centerOn(mapToScene(event->pos()));

  if (event->delta() > 0) zoomIn();
  if (event->delta() < 0) zoomOut();

  event->setAccepted(true);
}
