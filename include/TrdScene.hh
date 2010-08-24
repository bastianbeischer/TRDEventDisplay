/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: TrdScene.hh,v 1.4 2010/08/24 15:34:20 beischer Exp $
/////////////////////////////////////////////////////////////////

#ifndef TrdScene_hh
#define TrdScene_hh

#include <QGraphicsScene>

#include <QList>

class ColorScale;
class StrawTube;

/**
 * @class TrdScene
 *
 * @brief Abstract class which implements a QGraphicsScene with a pictural representation of the TRD.
 * 
 * This QGraphicsScene class is meant to provide a uniform interface for all scenes which show data on a pictural representation of the TRD and its
 * straw tubes. It maintains a list of StrawTubes, which are constructed and added to the scene in the constructor. The class has a ColorScale member
 * to colorize signals in the straw tubes.
 */
class TrdScene :
  public QGraphicsScene
{
  
Q_OBJECT

public:

  /**
   * @brief Sets up the scene with default TRD values and specifies the coordinate system of the scene. Constructs the tubes and adds them to the scene.
   */
  TrdScene();

  /**
   * @brief Destructor, deletes the color scale.
   */
  ~TrdScene();

signals:

  /**
   * @brief Notify connected classes of a change of the minimum of the scale
   * @param min The new minimum.
   */
  int scaleMinChanged(int min);

  /**
   * @brief Notify connected classes of a change of the maximum of the scale
   * @param max The new maximum.
   */
  int scaleMaxChanged(int max);

public slots:

  /**
   * @brief Emit a signal when the scale minimum changes.
   * @param min The new minimum.
   */
  virtual void changeScaleMin(int min) {emit(scaleMinChanged(min));}

  /**
   * @brief Emit a signal when the scale maximum changes.
   * @param max The new maximum.
   */
  virtual void changeScaleMax(int max) {emit(scaleMaxChanged(max));}

public:

  /**
   * @brief Return a pointer to the color scale.
   */
  const ColorScale* scale() const {return m_scale;}

private:

  /**
   * @brief Construct and add the tubes to the scene. Uses TrdHitRZD to calculate the positions for each layer, etc.
   */
  void addTubesToScene();

protected:

  /**
   * @brief Z values calculated in TrdHitRZD differ from the y values used in the scene by a constant offset.
   * @param z The z value to convert.
   */
  double z_to_y(double z) {return -(z - m_z_offset);}

protected:

  ColorScale*                      m_scale;        /**< Pointer to the color scale. */

  QList<StrawTube*>                m_tubes;        /**< List of all the straw tubes in the scene. */
  
private:
  QGraphicsRectItem*               m_boundingBox;  /**< Rectangular boundary of the TRD. */

  double                           m_width;        /**< Total width of the TRD in scene coordinates (=cm). */
  double                           m_height;       /**< Total height of the TRD in scene coordinates (=cm). */
  double                           m_z_offset;     /**< Offset in z for conversion from TrdHitRZD z values to scene y coordinates (in cm). */
  
};

#endif /* TrdScene_hh */
