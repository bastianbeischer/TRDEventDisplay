#ifndef GraphicsView_hh
#define GraphicsView_hh

#include <QGraphicsView>

class Scene;

class GraphicsView :
  public QGraphicsView
{
  
Q_OBJECT

public:
  GraphicsView(QWidget* parent = 0);
  ~GraphicsView();
  
protected:
  void mousePressEvent(QMouseEvent* mouseEvent);
  void mouseReleaseEvent(QMouseEvent* mouseEvent);
  void mouseMoveEvent(QMouseEvent* mouseEvent);
  void wheelEvent(QWheelEvent* event);

signals:
  void zoomLevelChanged(double);

public slots:
  void changeZoomLevel(double newLevel);
  void zoomIn();
  void zoomOut();

private:
  Scene* m_scene;

  QPointF*                         m_mousePressedAt;
  QGraphicsRectItem*               m_zoomRectangle;

  double m_zoomLevel;
  
};

#endif /* GraphicsView_hh */
