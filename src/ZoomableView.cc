/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: ZoomableView.cc,v 1.3 2010/08/18 22:21:57 beischer Exp $
/////////////////////////////////////////////////////////////////

#include "ZoomableView.hh"

#include <QGraphicsRectItem>
#include <QMouseEvent>
#include <QWheelEvent>

// constructor
ZoomableView::ZoomableView(QWidget* parent) :
  QGraphicsView(parent),
  m_zoomFactor(1.2),
  m_mousePressedAt(0),
  m_zoomRectangle(0)
{
  setDragMode(ScrollHandDrag);
  show();
}

// destructor
ZoomableView::~ZoomableView()
{
  delete m_mousePressedAt;
}

// overloaded virtual function, telling the view what to do with mouse clicks
void ZoomableView::mousePressEvent(QMouseEvent* event) 
{
  QGraphicsView::mousePressEvent(event);

  if (event->button() == Qt::MidButton)
    fitScene();
  else if (event->button() == Qt::RightButton) {
    m_mousePressedAt = new QPointF(mapToScene(event->pos()));
    m_zoomRectangle = new QGraphicsRectItem(m_mousePressedAt->x(), m_mousePressedAt->y(), 1, 1);
    m_zoomRectangle->setPen(QPen(Qt::DashLine));
    m_zoomRectangle->setBrush(QColor(0,0,255,50));
    scene()->addItem(m_zoomRectangle);
  }
}

// overloaded virtual function, telling the view what to do with mouse click releases
void ZoomableView::mouseReleaseEvent(QMouseEvent* event) 
{
  QGraphicsView::mouseReleaseEvent(event);

  if (event->button() == Qt::RightButton && m_zoomRectangle) {
    fitInView(m_zoomRectangle, Qt::KeepAspectRatioByExpanding);
    if (scene()->items().contains(m_zoomRectangle)) scene()->removeItem(m_zoomRectangle);
    if (m_mousePressedAt) delete m_mousePressedAt;
  }  
}

// overloaded virtual function, telling the view what to do with mouse movements
void ZoomableView::mouseMoveEvent(QMouseEvent* event) 
{
  QGraphicsView::mouseMoveEvent(event);

  if (m_mousePressedAt){
    QPointF point = mapToScene(event->pos());
    m_zoomRectangle->setRect(QRectF(*m_mousePressedAt, point));
  }
}

// overloaded virtual function, telling the view to zoom on mouse wheel events
void ZoomableView::wheelEvent(QWheelEvent* event)
{
  if (event->delta() > 0) zoomIn();
  if (event->delta() < 0) zoomOut();
  centerOn(mapToScene(event->pos()));
}

