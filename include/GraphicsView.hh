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
  void wheelEvent(QWheelEvent* event);

public slots:
  void changeZoomLevel(double newLevel);
  void zoomIn() {changeZoomLevel(1.2*m_zoomLevel);}
  void zoomOut() {changeZoomLevel(m_zoomLevel/1.2);}
  void fitScene() {fitInView(sceneRect());}

private:
  double m_zoomLevel;
  
};

#endif /* GraphicsView_hh */
