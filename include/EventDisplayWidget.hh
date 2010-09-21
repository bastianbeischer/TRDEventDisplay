#ifndef EventDisplayWidget_hh
#define EventDisplayWidget_hh

#include "DataWidget.hh"
#include "ui_EventDisplayForm.h"

class DataManager;
class EventDisplayScene;
class QResizeEvent;
class ZoomableView;

/**
 * @class EventDisplayWidget
 *
 * @brief DataWidget displaying an EventDisplayScene with a ZoomableView.
 *
 * This class is a data widget which displays information on single events in the TRD. It has a zoomable view member which maintains the display of
 * the scene. A Qt designer form with some spin boxes, information labels and scale display is used to setup the basic layout of the child
 * widgets. This widget maintains the change of events and redistributes actions to be done when new files are available and when the current file is
 * closed.
 */
class EventDisplayWidget :
  public DataWidget,
  private Ui::EventDisplayForm
{
  
Q_OBJECT

public:

  /**
   * @brief Constructor setting up the properties of the child and member widgets.
   * @param dataManager Constant pointer to the data manager
   * @param parent The parent widget
   *
   * Connects all the child widgets signals and slots.
   */
  EventDisplayWidget(const DataManager* dataManager, QWidget* parent = 0);

  /**
   * @brief Destructor, deletes the view and the scene.
   */
  ~EventDisplayWidget();
  
signals:
  
  /**
   * @brief Signal emitted if the event number changed.
   * @param newNumber Transmits the new event number.
   */
  int eventNumberChanged(int newNumber);

public slots:

  /**
   * @brief What to do when a new file has been opened.
   *
   * Enable and setup all the spin boxes and labels. Show the first event in the scene.
   */
  void fileOpened(int nEvents);

  /**
   * @brief What to do if the current file has been closed
   * 
   * Disable all user interface elements.
   */
  void fileClosed();

private slots:

  /**
   * @brief Show the event with the given number (calls m_scene->processEvent())
   * @param eventNumber the number to be displayed
   */
  void showEvent(int eventNumber);

  /**
   * @brief Update the labels under the scale as well as minimum and maximum of the spin boxes.
   */
  void updateScale();

protected:

  /**
   * @brief What to do if the window size changed: Readjust the view to display the scene properly according to the new size.
   */
  void resizeEvent(QResizeEvent* event);

private:

  ZoomableView*       m_view;  /**< Zoomable view which handles the display of the scene */
  EventDisplayScene*  m_scene; /**< The event display scene in which all the graphical elements sit */
  
};

#endif /* EventDisplayWidget_hh */
