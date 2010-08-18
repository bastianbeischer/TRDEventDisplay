/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: EventDisplayScene.hh,v 1.3 2010/08/18 18:33:23 beischer Exp $
/////////////////////////////////////////////////////////////////

#ifndef EventDisplayScene_hh
#define EventDisplayScene_hh

#include "Scene.hh"

#include <QList>

class StrawTube;
class TrdRawEvent;

class EventDisplayScene :
  public Scene
{

Q_OBJECT
  
public:
  EventDisplayScene();
  ~EventDisplayScene();
  
public slots:
  void changeMinAmp(int min) {m_ampMin = min; processEvent(m_currentEvent);}
  void changeMaxAmp(int max) {m_ampMax = max; processEvent(m_currentEvent);}
  void changeDisplayNegAmps(int value) {m_displayHitsWithNegAmp = value; processEvent(m_currentEvent);}
  void changeTubeWithNoHitsVisible(int value) {m_tubeWithNoHitsVisible = value; redraw(); processEvent(m_currentEvent);}

public:
  void processEvent(TrdRawEvent* event);

private:
  double z_to_y(double z) {return -(z - m_z_offset);}

  void addTubesToScene();
  void redraw();
  void removePreviousSignals();

private:
  TrdRawEvent*                     m_currentEvent;

  QGraphicsRectItem*               m_boundingBox;
  QList<StrawTube*>                m_signalItems;

  double                           m_width;
  double                           m_height;
  double                           m_z_offset;

  double                           m_ampMin;
  double                           m_ampMax;
  bool                             m_displayHitsWithNegAmp;
  bool                             m_tubeWithNoHitsVisible;

};

#endif /* EventDisplayScene_hh */
