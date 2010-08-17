#ifndef Scene_hh
#define Scene_hh

#include <QGraphicsScene>
#include <QGraphicsRectItem>

#include <QList>

class StrawTube;
class TrdRawEvent;

class Scene :
  public QGraphicsScene
{
  
Q_OBJECT

public:
  Scene();
  ~Scene();
  
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

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
  void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);
  void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);

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

  QPointF*                         m_mousePressedAt;
  QGraphicsRectItem*               m_zoomRectangle;
};

#endif /* Scene_hh */
