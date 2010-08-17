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
  
  double zoomLevel() {return m_zoomLevel;}
  void setZoomLevel(double newZoomLevel) {m_zoomLevel = newZoomLevel;}

signals:
  void zoomLevelChanged(double);

public slots:
  void changeZoomLevel(double newLevel);
  void zoomIn();
  void zoomOut();

private:
  Scene* m_scene;

  double m_zoomLevel;
  
};

#endif /* GraphicsView_hh */
