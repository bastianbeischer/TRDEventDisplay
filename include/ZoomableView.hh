#ifndef ZoomableView_hh
#define ZoomableView_hh

#include <QGraphicsView>

/**
 * @class ZoomableView
 *
 * @brief QGraphicsView with zooming capabilities
 * 
 * This class is a simple QGraphicsView which overrides the default mouse events in QGraphicsView to create zooming functionality.
 */
class ZoomableView :
  public QGraphicsView
{
  
Q_OBJECT

public:
  
  /**
   * @brief Constructor, sets the members to default values. The left-click-and-drag behavior is set to "scroll" the associated scene.
   * @param scene The scene to display (can be omitted)
   * @param parent Parent widget (if any)
   */
  ZoomableView(QGraphicsScene* scene = 0, QWidget* parent = 0);

  /**
   * @brief Destructor, deletes the zoom point and rectangle if they still exist
   */
  ~ZoomableView();
  
public slots:

  /**
   * @brief Zoom in by a constant factor
   */
  void zoomIn()   {scale(m_zoomFactor,    m_zoomFactor);}

  /**
   * @brief Zoom out by a constant factor
   */
  void zoomOut()  {scale(1./m_zoomFactor, 1./m_zoomFactor);}

  /**
   * @brief Fit the scene into the view.
   */
  void fitScene() {fitInView(sceneRect());}

protected:

  /**
   * @brief If the user pressed the right or middle mouse button, take corresponding actions.
   */
  void mousePressEvent(QMouseEvent* mouseEvent);

  /**
   * @brief If the user releases the right mouse button, zoom in to the specified rectangle.
   */
  void mouseReleaseEvent(QMouseEvent* mouseEvent);

  /**
   * @brief Update the pictural representation of the zooming rectangle in the scene.
   */
  void mouseMoveEvent(QMouseEvent* mouseEvent);

  /**
   * @brief Wheel up zooms in, wheel down zooms out.
   */
  void wheelEvent(QWheelEvent* event);
  
private:

  double             m_zoomFactor;      /**< Factor by which the scene should be zoomed when using the mouse wheel. */

  QPointF*           m_mousePressedAt;  /**< Point at which the mouse was pressed for rectangle calculation. */
  QGraphicsRectItem* m_zoomRectangle;   /**< The rectangle which represents the region to zoom into. */

};

#endif /* ZoomableView_hh */
