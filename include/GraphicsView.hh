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
  void zoomIn() {scale(m_zoomFactor, m_zoomFactor);}
  void zoomOut() {scale(1./m_zoomFactor, 1./m_zoomFactor);}
  void fitScene() {fitInView(sceneRect());}

protected:
  void mousePressEvent(QMouseEvent* event);
  void wheelEvent(QWheelEvent* event);
  
private:
  double m_zoomFactor;

};

#endif /* GraphicsView_hh */
