#include "Scene.hh"

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include <TrdRawEvent.hh>
#include <TrdHitRZD.hh>

#include <cmath>

#include "GraphicsView.hh"

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
  m_signalStretchFactorX(1.),
  m_signalStretchFactorY(1.5)
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
}

// set up the default values for each straw tube
void Scene::setDefaultsForTubeRect(QGraphicsRectItem* item)
{
  double tubeWidth = 0.62;
  double tubeHeight = 1.2;
  item->setRect(-tubeWidth/2., -tubeHeight/2., tubeWidth, tubeHeight);

  QPen pen(Qt::lightGray);
  QBrush brush(Qt::lightGray);

  if (m_tubeWithNoHitsVisible) {
    pen.setStyle(Qt::SolidLine);
    brush.setStyle(Qt::SolidPattern);
  }
  else {
    pen.setStyle(Qt::NoPen);
    brush.setStyle(Qt::NoBrush);
  }

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

    // interpolate colors between blue and green for the signals between lower end and middle of axis and between green and red for middle to upper end
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
    item->setBrush(brush);

    QRectF rect = item->rect();
    double newLeft = m_signalStretchFactorX * rect.left();
    double newWidth = qAbs(2. * newLeft);
    double newTop = m_signalStretchFactorY * rect.top();
    double newHeight = qAbs(2. * newTop);
    item->setRect(QRectF(newLeft, newTop, newWidth, newHeight));

    // QPen pen(Qt::black);
    // item->setPen(pen);

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
