/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: Scene.hh,v 1.12 2010/08/18 18:33:23 beischer Exp $
/////////////////////////////////////////////////////////////////

#ifndef Scene_hh
#define Scene_hh

#include <QGraphicsScene>

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
