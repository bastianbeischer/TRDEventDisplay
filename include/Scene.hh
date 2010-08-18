/////////////////////////////////////////////////////////////////
// CVS Information
// $Id: Scene.hh,v 1.10 2010/08/18 18:22:02 beischer Exp $
/////////////////////////////////////////////////////////////////

#ifndef Scene_hh
#define Scene_hh

#include <QGraphicsScene>

#include <QList>

class StrawTube;
class TrdRawEvent;
class QGraphicsRectItem;

class Scene :
  public QGraphicsScene
{
  
Q_OBJECT

public:
  Scene();
  ~Scene();
  
protected:
  void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
  void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);
  void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);

private:
  QPointF*           m_mousePressedAt;
  QGraphicsRectItem* m_zoomRectangle;

};

#endif /* Scene_hh */
