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
  m_hits(),
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
void EventDisplayScene::processHits(const std::vector<TrdRawHitR>& hits)
{
  m_hits = hits;

  // remove signal items from previous events
  removePreviousSignals();

  for (unsigned int i = 0; i < m_hits.size(); i++) {
    TrdRawHitR hit = m_hits.at(i);

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
