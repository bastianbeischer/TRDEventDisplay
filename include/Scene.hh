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
  void minAmpChanged(int min);
  void maxAmpChanged(int max);  
  void changeDisplayNegAmps(int);
  void tubeWithNoHitsVisible(int);

public:
  void processEvent(TrdRawEvent* event);

private:
  void addTubesToScene();
  void redraw();
  void removePreviousSignals();

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
  void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);
  void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
  void wheelEvent(QGraphicsSceneWheelEvent* event);

private:
  QPointF*                         m_mousePressedAt;
  QPointF*                         m_mouseReleasedAt;
  QGraphicsRectItem*               m_zoomRectangle;

  QGraphicsRectItem*               m_boundingBox;
  QVector<QGraphicsRectItem*>      m_signalItems;

  double                           m_width;
  double                           m_height;

  double                           m_ampMin;
  double                           m_ampMax;
  bool                             m_displayHitsWithNegAmp;
  bool                             m_tubeWithNoHitsVisible;

};

#endif /* Scene_hh */
