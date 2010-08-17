#include "Scene.hh"

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

#include <TrdRawEvent.hh>
#include <TrdHitRZD.hh>

#include <cmath>

#include "GraphicsView.hh"

// constructor
Scene::Scene() :
  QGraphicsScene(),
  m_currentEvent(0),
  m_mousePressedAt(0),
  m_mouseReleasedAt(0),
  m_zoomRectangle(0),
  m_boundingBox(new QGraphicsRectItem),
  m_width(200),
  m_height(80),
  m_z_offset(115.0),
  m_ampMin(0.),
  m_ampMax(100.),
  m_displayHitsWithNegAmp(true),
  m_tubeWithNoHitsVisible(true),
  m_signalStretchFactor(2.0)
{
  QRectF rectangle(-m_width/2., -m_height/2., m_width, m_height);
  setSceneRect(rectangle);
  m_boundingBox->setRect(rectangle);
  addItem(m_boundingBox);

  addTubesToScene();
}

// destructor
Scene::~Scene()
{
  delete m_mousePressedAt;
  delete m_mouseReleasedAt;
  delete m_zoomRectangle;
  clear();
}

// set up the default values for each straw tube
void Scene::setDefaultsForTubeRect(QGraphicsRectItem* item)
{
  double tubeWidth = 0.5;
  double tubeHeight = 1.2;
  item->setRect(-tubeWidth/2., -tubeHeight/2., tubeWidth, tubeHeight);

  QPen pen(Qt::lightGray);

  if (m_tubeWithNoHitsVisible)
    pen.setStyle(Qt::SolidLine);
  else
    pen.setStyle(Qt::NoPen);
       
  QBrush brush(Qt::NoBrush);

  item->setPen(pen);
  item->setBrush(brush);
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
        
        QGraphicsRectItem* item = new QGraphicsRectItem();
        setDefaultsForTubeRect(item);
        item->setPos(x,y);
        addItem(item);
      }
    }
  }
}

// redraw
void Scene::redraw()
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

        QGraphicsRectItem* item = (QGraphicsRectItem*) itemAt(x,y);
        setDefaultsForTubeRect(item);
      }
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
    QGraphicsRectItem* item = (QGraphicsRectItem*) itemAt(x,y);

    Q_ASSERT(item);

    // interpolate colors between blue and green for the signals between 0 and 10 pe and between green and red for 10 to 20 pe
    QColor signalColor;
    double amplitude = hit.Amp;

    // if amp is outside of the scale boundaries, fix it to the minimum or maximum
    if (amplitude < m_ampMin) amplitude = m_ampMin;
    if (amplitude > m_ampMax) amplitude = m_ampMax;

    // determine the color to use (r,g,b,alpha)
    double fraction = (amplitude - m_ampMin) / (m_ampMax - m_ampMin);
    if (fraction < 0.5) {
      fraction *= 2.0;
      signalColor = QColor(0, floor(255*(fraction)), floor(255*(1.0-fraction)), 255);
    }
    else {
      fraction -= 0.5;
      fraction *= 2.0;
      signalColor = QColor(floor(255*fraction), floor(255*(1.0-fraction)),0, 255);
    }

    // apply color and add the item to the scene
    QBrush brush(signalColor);
    QPen pen(Qt::black);
    //    pen.setWidth(2);
    QRectF rect = item->rect();
    rect.setHeight(m_signalStretchFactor*rect.height());
    item->setBrush(brush);
    item->setPen(pen);
    item->setRect(rect);

    m_signalItems.push_back(item);
  }

  // notify the scene that it has been updated
  update();
}

// remove the color from the last event again
void Scene::removePreviousSignals()
{
  foreach(QGraphicsRectItem* item, m_signalItems)
    setDefaultsForTubeRect(item);
  m_signalItems.clear();
}

//! overloaded virtual function, telling the scene what to do with mouse clicks
void Scene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) 
{
  if (mouseEvent->button() == Qt::LeftButton) {
    m_mousePressedAt = new QPointF(mouseEvent->scenePos());
    m_zoomRectangle = new QGraphicsRectItem(m_mousePressedAt->x(), m_mousePressedAt->y(), 1, 1);
    m_zoomRectangle->setPen(QPen(Qt::DashLine));
    addItem(m_zoomRectangle);
  }
}

//! overloaded virtual function, telling the scene what to do with mouse click releases
void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent) 
{

  GraphicsView* gView = (GraphicsView*) views().front();

  if (mouseEvent->button() == Qt::LeftButton) {
    m_mouseReleasedAt = new QPointF(mouseEvent->scenePos());

    double x2 = m_mouseReleasedAt->x();
    double x1 = m_mousePressedAt->x();
    double y2 = m_mouseReleasedAt->y();
    double y1 = m_mousePressedAt->y();

    if (sqrt( pow(x2 - x1, 2.0) + pow(y2 - y1, 2.0) ) > 5) {

      double scale_x = sceneRect().width() / fabs((x2-x1));
      double scale_y = sceneRect().height() / fabs((y2-y1));
      double scale_factor = scale_x > scale_y ? scale_x : scale_y;

      gView->centerOn((x1+x2)/2., (y1+y2)/2.);
      gView->changeZoomLevel(1.0);
      gView->changeZoomLevel(scale_factor);

    }
    
    if (items().contains(m_zoomRectangle)) removeItem(m_zoomRectangle);

    if (m_mousePressedAt)  delete m_mousePressedAt;
    if (m_mouseReleasedAt) delete m_mouseReleasedAt;
  }  
  else if (mouseEvent->button() == Qt::RightButton) {
    gView->centerOn(mouseEvent->scenePos());
  }
}

//! overloaded virtual function, telling the scene what to do with mouse movements
void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) 
{
  if (m_mousePressedAt){
    double width  = fabs(mouseEvent->scenePos().x() - m_mousePressedAt->x());
    double height = fabs(mouseEvent->scenePos().y() - m_mousePressedAt->y());

    double x1 = mouseEvent->scenePos().x() > m_mousePressedAt->x() ? m_mousePressedAt->x() : mouseEvent->scenePos().x();
    double y1 = mouseEvent->scenePos().y() > m_mousePressedAt->y() ? m_mousePressedAt->y() : mouseEvent->scenePos().y();

    m_zoomRectangle->setRect(x1, y1, width, height);
  }
}

//! overloaded virtual function, telling the scene what to do with mouse wheel events
void Scene::wheelEvent(QGraphicsSceneWheelEvent* event)
{
  GraphicsView* gView = (GraphicsView*) views().front();
  double oldZoomLevel = gView->zoomLevel();

  gView->centerOn(event->scenePos());

  if (event->delta() > 0)
    gView->changeZoomLevel(1.2*oldZoomLevel);
  if (event->delta() < 0)
    gView->changeZoomLevel(oldZoomLevel/1.2);

  event->setAccepted(true);
}
