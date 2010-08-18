/////////////////////////////////////////////////////////////////
// CVS Information
// $Id: View.hh,v 1.1 2010/08/18 18:22:03 beischer Exp $
/////////////////////////////////////////////////////////////////

#ifndef View_hh
#define View_hh

#include <QGraphicsView>

class View :
  public QGraphicsView
{
  
Q_OBJECT

public:
  View(QWidget* parent = 0);
  ~View();
  
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

#endif /* View_hh */
