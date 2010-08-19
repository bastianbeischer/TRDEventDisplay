/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: EventDisplayScene.hh,v 1.7 2010/08/19 15:54:09 beischer Exp $
/////////////////////////////////////////////////////////////////

#ifndef EventDisplayScene_hh
#define EventDisplayScene_hh

#include <QGraphicsScene>

#include <QList>

class ColorScale;
class StrawTube;
class TrdRawEvent;

class EventDisplayScene :
  public QGraphicsScene
{

Q_OBJECT
  
public:
  EventDisplayScene();
  ~EventDisplayScene();
  
signals:
  int minChanged(int min);
  int maxChanged(int max);

public slots:
  void changeMinAmp(int min) {emit(minChanged(min)); processEvent(m_currentEvent);}
  void changeMaxAmp(int max) {emit(maxChanged(max)); processEvent(m_currentEvent);}
  void changeDisplayNegAmps(int value) {m_displayHitsWithNegAmp = value; processEvent(m_currentEvent);}
  void changeTubeWithNoHitsVisible(int value) {m_tubeWithNoHitsVisible = value; redraw(); processEvent(m_currentEvent);}

public:
  const ColorScale* scale() const {return m_scale;}

  void processEvent(TrdRawEvent* event);

private:
  double z_to_y(double z) {return -(z - m_z_offset);}

  void addTubesToScene();
  void redraw();
  void removePreviousSignals();

private:
  TrdRawEvent*                     m_currentEvent;

  ColorScale*                      m_scale;

  QGraphicsRectItem*               m_boundingBox;
  QList<StrawTube*>                m_tubes;
  QList<StrawTube*>                m_signalTubes;

  double                           m_width;
  double                           m_height;
  double                           m_z_offset;

  double                           m_signalStretchFactorX;
  double                           m_signalStretchFactorY;

  bool                             m_displayHitsWithNegAmp;
  bool                             m_tubeWithNoHitsVisible;

};

#endif /* EventDisplayScene_hh */
