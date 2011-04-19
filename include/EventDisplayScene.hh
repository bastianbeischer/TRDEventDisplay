#ifndef EventDisplayScene_hh
#define EventDisplayScene_hh

#include "TrdScene.hh"

class TrdRawHitR;

/**
 * @class EventDisplayScene
 * 
 * @brief The scene containg all the event display objects.
 *
 * This class implements what should be done with the events and how they should be displayed in the scene. It is a TrdScene and is hence able to
 * display straw tubes as little rectangles. The amplitude of each straw tube with signal is displayed in color. The color is determined from the
 * ColorScale attributed to this scene (via the TrdScene base class). Additionally signal tubes can be enlarged by two stretching factors.
 */
class EventDisplayScene :
  public TrdScene
{

Q_OBJECT
  
public:

  /**
   * @brief Constructor, setting up default values. Calls TrdScene constructor.
   */
  EventDisplayScene();

  /**
   * @brief Destructor, doing nothing.
   */
  ~EventDisplayScene();
  
public slots:

  /**
   * @brief What should be done when the scale changes: propagate the scale change to TrdScene and reprocess the current event.
   * @param min The new minimum of the scale
   */
  void changeScaleMin(int min) {TrdScene::changeScaleMin(min); processHits(m_hits);}
  
  /**
   * @brief What should be done when the scale changes: propagate the scale change to TrdScene and reprocess the current event.
   * @param max The new maximum of the scale
   */
  void changeScaleMax(int max) {TrdScene::changeScaleMax(max); processHits(m_hits);}

  /**
   * @brief Set boolean value of display hits with negative amplitudes and reprocess the current event.
   * @param value New value as an integer - will be used as a bool in the routine.
   */
  void changeDisplayNegAmps(int value) {m_displayHitsWithNegAmp = value; processHits(m_hits);}

  /**
   * @brief Set visiblity of empty tubes, redraw all tubes according to this change and reprocess the current event.
   * @param value New value as an integer - will be used as a bool in the routine.
   */
  void changeTubeWithNoHitsVisible(int value) {m_tubeWithNoHitsVisible = value; redraw(); processHits(m_hits);}

public:

  /**
   * @brief Implements what should be done with events.
   * @param hits A vector of TrdRawHitR to display
   */
  void processHits(const std::vector<TrdRawHitR>& hits);

  /**
   * @brief Removes all signals from the scene.
   */
  void removePreviousSignals();

private:

  /**
   * @brief Redraw all the tubes. This is necessary if their visibility changed. 
   */
  void redraw();

private:

  std::vector<TrdRawHitR>          m_hits;                   /**< Vector with the hits of the current event (only availabe after processHits has been called once)*/

  QList<StrawTube*>                m_signalTubes;            /**< List of tubes with signal (for more efficient removal of signals) */

  double                           m_signalStretchFactorX;   /**< Factor by which tube rectangles should be strechted in x direction if they contain signal */
  double                           m_signalStretchFactorY;   /**< Factor by which tube rectangles should be strechted in y direction if they contain signal */

  bool                             m_displayHitsWithNegAmp;  /**< Whether or not to display signals in tubes which have negative amplitudes */
  bool                             m_tubeWithNoHitsVisible;  /**< Whether or not to display tube rectangles even if they don't contain signal amplitudes */

};

#endif /* EventDisplayScene_hh */
