#ifndef GraphicsView_hh
#define GraphicsView_hh

#include <QGraphicsView>

class TrdRawEvent;
class Scene;

class GraphicsView :
  public QGraphicsView
{
  
Q_OBJECT

public:
  GraphicsView(QWidget* parent = 0);
  ~GraphicsView();
  
public slots:
  void changeZoomLevel(double newLevel);
  void zoomIn() {changeZoomLevel(1.2*m_zoomLevel);}
  void zoomOut() {changeZoomLevel(m_zoomLevel/1.2);}
  void fitScene() {fitInView(sceneRect());}

protected:
  void wheelEvent(QWheelEvent* event);

private:
  double m_zoomLevel;
  
};

#endif /* GraphicsView_hh */
