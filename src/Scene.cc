#include "Scene.hh"

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include <TrdRawEvent.hh>
#include <TrdHitRZD.hh>

#include "GraphicsView.hh"
#include "StrawTube.hh"

// constructor
Scene::Scene() :
  QGraphicsScene(),
  m_currentEvent(0),
  m_boundingBox(new QGraphicsRectItem),
  m_width(200),
  m_height(70),
  m_z_offset(115.0),
  m_ampMin(0.),
  m_ampMax(100.),
  m_displayHitsWithNegAmp(true),
  m_tubeWithNoHitsVisible(true),
  m_mousePressedAt(0),
  m_zoomRectangle(0)
{
  QRectF rectangle(-m_width/2., -m_height/2., m_width, m_height);
  m_boundingBox->setRect(rectangle);
  addItem(m_boundingBox);

  addTubesToScene();
}

// destructor
Scene::~Scene()
{
  delete m_mousePressedAt;
}

// add the rectangular representations of the tubes to the scene
void Scene::addTubesToScene()
{
  for(int lay=0;lay!=20;lay++){
    for(int lad=0;lad!=18;lad++){
      for(int tub=0;tub!=16;tub++){
        if(lay<4&&lad>13)continue;
        else if(lay<12&&lad>15)continue;
        else if(lay>19)continue;

        TrdRawHitR hit;
        hit.Layer = lay;
        hit.Ladder = lad;
        hit.Tube = tub;
        TrdHitRZD rzd(&hit);
        
        double x = rzd.r();
        double y = z_to_y(rzd.z());
        
        StrawTube* tube = new StrawTube(x,y);
        addItem(tube);
      }
    }
  }
}

// redraw
void Scene::redraw()
{
  foreach(QGraphicsItem* item, items()) {
    StrawTube* tube = dynamic_cast<StrawTube*>(item);
    if (tube) {
      tube->reInit();
      if (!m_tubeWithNoHitsVisible)
        tube->makeInvisible();
    }
  }
}
 
// process an event and show it in the scene
void Scene::processEvent(TrdRawEvent* event)
{
  m_currentEvent = event;

  // remove signal items from previous events
  removePreviousSignals();

  std::vector<TrdRawHitR>* hits = event->GetHits();
  for (unsigned int i = 0; i < hits->size(); i++) {
    TrdRawHitR hit = hits->at(i);

    // don't display negative amplitudes if desired
    if(!m_displayHitsWithNegAmp && hit.Amp < 0)
      continue;

    // construct the visual representation of the hit
    TrdHitRZD rzd(&hit);
    double x = rzd.r();
    double y = z_to_y(rzd.z());
    StrawTube* tube = (StrawTube*) itemAt(x,y);

    Q_ASSERT(tube);

    double amplitude = hit.Amp;
    // if amp is outside of the scale boundaries, fix it to the minimum or maximum
    if (amplitude < m_ampMin) amplitude = m_ampMin;
    if (amplitude > m_ampMax) amplitude = m_ampMax;

    // determine the color to use (r,g,b,alpha)
    double fraction = (amplitude - m_ampMin) / (m_ampMax - m_ampMin);
    tube->displayHit(fraction);
    
    m_signalItems.push_back(tube);
  }

  // notify the scene that it has been updated
  update();
}

// remove the color from the last event again
void Scene::removePreviousSignals()
{
  foreach(StrawTube* tube, m_signalItems)
    tube->reInit();
  m_signalItems.clear();
}

//! overloaded virtual function, telling the scene what to do with mouse clicks
void Scene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) 
{
  QGraphicsScene::mousePressEvent(mouseEvent);

  if (mouseEvent->button() == Qt::RightButton) {
    m_mousePressedAt = new QPointF(mouseEvent->scenePos());
    m_zoomRectangle = new QGraphicsRectItem(m_mousePressedAt->x(), m_mousePressedAt->y(), 1, 1);
    m_zoomRectangle->setPen(QPen(Qt::DashLine));
    addItem(m_zoomRectangle);
  }

  //  mouseEvent->setAccepted(true);
}

//! overloaded virtual function, telling the scene what to do with mouse click releases
void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent) 
{
  QGraphicsScene::mouseReleaseEvent(mouseEvent);

  if (mouseEvent->button() == Qt::RightButton) {
    views().front()->fitInView(m_zoomRectangle, Qt::KeepAspectRatioByExpanding);
    if (items().contains(m_zoomRectangle)) removeItem(m_zoomRectangle);
    if (m_mousePressedAt)  delete m_mousePressedAt;
  }  

  //  mouseEvent->setAccepted(true);
}

//! overloaded virtual function, telling the scene what to do with mouse movements
void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) 
{
  QGraphicsScene::mouseMoveEvent(mouseEvent);

  if (m_mousePressedAt){
    QPointF point = mouseEvent->scenePos();
    m_zoomRectangle->setRect(QRectF(*m_mousePressedAt, point));
  }

  //  mouseEvent->setAccepted(true);
}

