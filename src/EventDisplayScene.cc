/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: EventDisplayScene.cc,v 1.9 2010/08/19 17:50:59 beischer Exp $
/////////////////////////////////////////////////////////////////

#include "EventDisplayScene.hh"

#include <QGraphicsRectItem>

#include "ColorScale.hh"
#include "StrawTube.hh"
#include "TrdHitRZD.hh"
#include "TrdRawEvent.hh"
#include "TrdRawHitR.hh"

// constructor
EventDisplayScene::EventDisplayScene() :
  TrdScene(),
  m_currentEvent(0),
  m_signalStretchFactorX(1.),
  m_signalStretchFactorY(1.5),
  m_displayHitsWithNegAmp(true),
  m_tubeWithNoHitsVisible(true)
{
}

// destructor
EventDisplayScene::~EventDisplayScene()
{
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
void EventDisplayScene::processEvent(const TrdRawEvent* event)
{
  m_currentEvent = event;

  // remove signal items from previous events
  removePreviousSignals();

  const std::vector<TrdRawHitR>* hits = event->GetHits();
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
