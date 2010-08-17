#ifndef Scene_hh
#define Scene_hh

#include <QGraphicsScene>
#include <QGraphicsRectItem>

#include <QVector>

class TrdRawEvent;

class Scene :
  public QGraphicsScene
{
  
Q_OBJECT

public:
  Scene();
  ~Scene();
  
public slots:
  void minAmpChanged(int min) {m_ampMin = min; processEvent(m_currentEvent);}
  void maxAmpChanged(int max) {m_ampMax = max; processEvent(m_currentEvent);}
  void changeDisplayNegAmps(int value) {m_displayHitsWithNegAmp = value; processEvent(m_currentEvent);}
  void tubeWithNoHitsVisible(int value) {m_tubeWithNoHitsVisible = value; redraw(); processEvent(m_currentEvent);}

public:
  void processEvent(TrdRawEvent* event);

private:
  double z_to_y(double z) {return -(z - m_z_offset);}

  void setDefaultsForTubeRect(QGraphicsRectItem* item);
  void addTubesToScene();
  void redraw();
  void removePreviousSignals();

private:
  TrdRawEvent*                     m_currentEvent;

  QGraphicsRectItem*               m_boundingBox;
  QList<QGraphicsRectItem*>        m_signalItems;

  double                           m_width;
  double                           m_height;
  double                           m_z_offset;

  double                           m_ampMin;
  double                           m_ampMax;
  bool                             m_displayHitsWithNegAmp;
  bool                             m_tubeWithNoHitsVisible;

  double                           m_signalStretchFactorX;
  double                           m_signalStretchFactorY;

};

#endif /* Scene_hh */
