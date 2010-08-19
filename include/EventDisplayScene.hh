/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: EventDisplayScene.hh,v 1.8 2010/08/19 17:05:08 beischer Exp $
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
  void changeMinAmp(int min) {TrdScene::changeMinAmp(min); processEvent(m_currentEvent);}
  void changeMaxAmp(int max) {TrdScene::changeMaxAmp(max); processEvent(m_currentEvent);}
  void changeDisplayNegAmps(int value) {m_displayHitsWithNegAmp = value; processEvent(m_currentEvent);}
  void changeTubeWithNoHitsVisible(int value) {m_tubeWithNoHitsVisible = value; redraw(); processEvent(m_currentEvent);}

public:
  void processEvent(TrdRawEvent* event);

private:
  void redraw();
  void removePreviousSignals();

private:
  TrdRawEvent*                     m_currentEvent;

  QList<StrawTube*>                m_signalTubes;

  double                           m_signalStretchFactorX;
  double                           m_signalStretchFactorY;

  bool                             m_displayHitsWithNegAmp;
  bool                             m_tubeWithNoHitsVisible;

};

#endif /* EventDisplayScene_hh */
