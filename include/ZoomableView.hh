/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: ZoomableView.hh,v 1.2 2010/08/18 19:36:43 beischer Exp $
/////////////////////////////////////////////////////////////////

#ifndef ZoomableView_hh
#define ZoomableView_hh

#include <QGraphicsView>

class ZoomableView :
  public QGraphicsView
{
  
Q_OBJECT

public:
  ZoomableView(QWidget* parent = 0);
  ~ZoomableView();
  
public slots:
  void zoomIn()   {scale(m_zoomFactor,    m_zoomFactor);}
  void zoomOut()  {scale(1./m_zoomFactor, 1./m_zoomFactor);}
  void fitScene() {fitInView(sceneRect());}

protected:
  void mousePressEvent(QMouseEvent* mouseEvent);
  void mouseReleaseEvent(QMouseEvent* mouseEvent);
  void mouseMoveEvent(QMouseEvent* mouseEvent);
  void wheelEvent(QWheelEvent* event);
  
private:
  double             m_zoomFactor;

  QPointF*           m_mousePressedAt;
  QGraphicsRectItem* m_zoomRectangle;

};

#endif /* ZoomableView_hh */
