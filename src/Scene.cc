/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: Scene.cc,v 1.23 2010/08/18 18:33:23 beischer Exp $
/////////////////////////////////////////////////////////////////

#include "Scene.hh"

#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

// constructor
Scene::Scene() :
  QGraphicsScene(),
  m_mousePressedAt(0),
  m_zoomRectangle(0)
{
}

// destructor
Scene::~Scene()
{
  delete m_mousePressedAt;
}

//! overloaded virtual function, telling the scene what to do with mouse clicks
void Scene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) 
{
  QGraphicsScene::mousePressEvent(mouseEvent);

  if (mouseEvent->button() == Qt::RightButton) {
    m_mousePressedAt = new QPointF(mouseEvent->scenePos());
    m_zoomRectangle = new QGraphicsRectItem(m_mousePressedAt->x(), m_mousePressedAt->y(), 1, 1);
    m_zoomRectangle->setPen(QPen(Qt::DashLine));
    m_zoomRectangle->setBrush(QColor(0,0,255,50));
    addItem(m_zoomRectangle);
  }
}

//! overloaded virtual function, telling the scene what to do with mouse click releases
void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent) 
{
  QGraphicsScene::mouseReleaseEvent(mouseEvent);

  if (mouseEvent->button() == Qt::RightButton && m_zoomRectangle) {
    views().front()->fitInView(m_zoomRectangle, Qt::KeepAspectRatioByExpanding);
    if (items().contains(m_zoomRectangle)) removeItem(m_zoomRectangle);
    if (m_mousePressedAt) delete m_mousePressedAt;
  }  
}

//! overloaded virtual function, telling the scene what to do with mouse movements
void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) 
{
  QGraphicsScene::mouseMoveEvent(mouseEvent);

  if (m_mousePressedAt){
    QPointF point = mouseEvent->scenePos();
    m_zoomRectangle->setRect(QRectF(*m_mousePressedAt, point));
  }
}

