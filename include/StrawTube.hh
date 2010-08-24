/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: StrawTube.hh,v 1.9 2010/08/24 15:21:01 beischer Exp $
/////////////////////////////////////////////////////////////////

#ifndef StrawTube_hh
#define StrawTube_hh

#include <QGraphicsRectItem>

/**
 * @class StrawTube
 * 
 * @brief A simple rectangular representation of a straw tube
 *
 * Each instance of this class represents a straw tube in the TRD. The class doesn't differ very much from a QGraphicsRectItem, but provides some
 * member functions for convenience.
 */
class StrawTube :
  public QGraphicsRectItem
{
  
public:

  /**
   * @brief Constructs a new StrawTube at x,y
   * @param x x coordinate of tube center (in scene coordinates)
   * @param y y coordinate of tube center (in scene coordinates)
   */
  StrawTube(double x = 0., double y = 0.);

  /**
   * @brief Destructor, doing nothing.
   */
  ~StrawTube();
  
public:

  /**
   * @brief Set all properties back to initial values
   */
  void reInit();

  /**
   * @brief Apply color to inner region of the rectangle.
   * @param color Which color to apply
   */
  void colorize(QColor color);

  /**
   * @brief Scale rectangle
   * @param factorX Stretch factor in x direction
   * @param factorY Stretch factor in y direction
   */
  void stretch(double factorX, double factorY);

  /**
   * @brief Make the tube invisible, but still selectable for QGraphicsScene::itemAt(x,y)
   */
  void makeInvisible();

private:

  double m_width;  /**< The width of the tube in scene coordinates */
  double m_height; /**< The height of the tube in scene coordinates */

};

#endif /* StrawTube_hh */
