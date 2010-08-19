/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: EventDisplayScene.cc,v 1.7 2010/08/19 15:54:09 beischer Exp $
/////////////////////////////////////////////////////////////////

#include "EventDisplayScene.hh"

#include <QGraphicsRectItem>

#include "ColorScale.hh"
#include "StrawTube.hh"
#include "TrdHitRZD.hh"
#include "TrdRawEvent.hh"

// constructor
EventDisplayScene::EventDisplayScene() :
  QGraphicsScene(),
  m_currentEvent(0),
  m_scale(new ColorScale(0., 100.)),
  m_boundingBox(new QGraphicsRectItem()),
  m_width(200),
  m_height(70),
  m_z_offset(115.0),
  m_signalStretchFactorX(1.),
  m_signalStretchFactorY(1.5),
  m_displayHitsWithNegAmp(true),
  m_tubeWithNoHitsVisible(true)
{
  QRectF rectangle(-m_width/2., -m_height/2., m_width, m_height);
  setSceneRect(rectangle);
  m_boundingBox->setRect(rectangle);
  addItem(m_boundingBox);

  addTubesToScene();

  connect(this, SIGNAL(minChanged(int)), m_scale, SLOT(changeMin(int)));
  connect(this, SIGNAL(maxChanged(int)), m_scale, SLOT(changeMax(int)));
}

// destructor
EventDisplayScene::~EventDisplayScene()
{
  delete m_scale;
}

// add the rectangular representations of the tubes to the scene
void EventDisplayScene::addTubesToScene()
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
        m_tubes.push_back(tube);
        addItem(tube);
      }
    }
  }
}

// redraw all items (needed of visibility of non-hits changed)
void EventDisplayScene::redraw()
{
  foreach(StrawTube* tube, m_tubes) {
    tube->reInit();
    if (!m_tubeWithNoHitsVisible)
      tube->makeInvisible();
  }
}
 
// process an event and show it in the scene
void EventDisplayScene::processEvent(TrdRawEvent* event)
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

    // there should be a tube at x,y
    Q_ASSERT(tube);
    
    // calculate the color and apply it
    double amplitude = hit.Amp;
    QColor color = m_scale->color(amplitude);
    tube->colorize(color);
    tube->stretch(m_signalStretchFactorX, m_signalStretchFactorY);
    
    m_signalTubes.push_back(tube);
  }

  // notify the scene that it has been updated
  update();
}

// remove the color from the last event again
void EventDisplayScene::removePreviousSignals()
{
  foreach(StrawTube* tube, m_signalTubes) {
    tube->reInit();
    if (!m_tubeWithNoHitsVisible)
      tube->makeInvisible();
  }

  m_signalTubes.clear();
}
