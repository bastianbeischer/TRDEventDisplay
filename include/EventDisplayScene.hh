/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: EventDisplayScene.hh,v 1.11 2010/08/23 13:31:06 beischer Exp $
/////////////////////////////////////////////////////////////////

#ifndef EventDisplayScene_hh
#define EventDisplayScene_hh

#include "TrdScene.hh"

class TrdRawEvent;

class EventDisplayScene :
  public TrdScene
{

Q_OBJECT
  
public:
  EventDisplayScene();
  ~EventDisplayScene();
  
public slots:
  void changeScaleMin(int min) {TrdScene::changeScaleMin(min); processEvent(m_currentEvent);}
  void changeScaleMax(int max) {TrdScene::changeScaleMax(max); processEvent(m_currentEvent);}
  void changeDisplayNegAmps(int value) {m_displayHitsWithNegAmp = value; processEvent(m_currentEvent);}
  void changeTubeWithNoHitsVisible(int value) {m_tubeWithNoHitsVisible = value; redraw(); processEvent(m_currentEvent);}

public:
  void processEvent(const TrdRawEvent* event);
  void removePreviousSignals();

private:
  void redraw();

private:
  const TrdRawEvent*               m_currentEvent;

  QList<StrawTube*>                m_signalTubes;

  double                           m_signalStretchFactorX;
  double                           m_signalStretchFactorY;

  bool                             m_displayHitsWithNegAmp;
  bool                             m_tubeWithNoHitsVisible;

};

#endif /* EventDisplayScene_hh */
