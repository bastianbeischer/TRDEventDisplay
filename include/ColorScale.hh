#ifndef ColorScale_hh
#define ColorScale_hh

#include <QLinearGradient>

/** 
 * @brief Class which implements the scale according to which hits will be colorized.
 *
 * This class inherits QLinearGradient and uses the colours specified in the constructor to construct a linear scale.
 * A color can be attributed to values between m_min and m_max according to this linear scale.
 */
class ColorScale :
  public QObject,
  public QLinearGradient
{

Q_OBJECT
  
public:

  /**
   * @brief Constructor with default values for the scale minimum and maxmium of 0. and 1. Constructs the colour transitions of the scale.
   *
   * @param min Minimum of the scale
   * @param max Maximum of the scale
   *
   * By default a transition from blue to green to yellow to red. If you want to change the colours or the transition points, edit the code.
   * See the documentation of QLinearGradient and its stop points for more information. 
   * @see QLinearGradient, QGradient
   */
  ColorScale(double min = 0., double max = 1.);

  /** 
   * @brief Destructor (doing nothing) 
   */
  ~ColorScale();
  
public slots:

  /** 
   * @brief Change the minimum of the scale 
   * @param newValue the new value for the minimum
   */  
  void changeMin(int newValue) {m_min = newValue;}

  /**
   * @brief Change the maximum of the scale 
   * @param newValue the new value for the maximum
   */  
  void changeMax(int newValue) {m_max = newValue;}

public:

  /** 
   * @brief Assign a color to the value "value". If value is not in the range of m_min .. m_max, it will be set to these limiting values for the calculation of the color! 
   * @param value the value for which the color should be computed.
   */  
  QColor color(double value);

private:

  double m_min; /**< minimum of the scale */
  double m_max; /**< maximum of the scale */

};

#endif /* ColorScale_hh */
