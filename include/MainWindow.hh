/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: MainWindow.hh,v 1.16 2010/08/27 14:42:33 beischer Exp $
/////////////////////////////////////////////////////////////////

#ifndef MainWindow_hh
#define MainWindow_hh

#include <QMainWindow>
#include "ui_MainForm.h"

#include <QList>

class DataManager;
class DataWidget;

/**
 * @class MainWindow
 *
 * @brief The QMainWindow which sets up some buttons for file IO and application control according to its form. Has a list of DataWidgets which are
 *        arranged in tabs.
 *
 * The main window maintains a QList of DataWidgets which are arranged in tabs and constructed in the constructor of this class. The MainWindow "owns"
 * the data manager and connects its signals to the corresponding slots in the data widgets. It also possesses a function to process command line
 * arguments.
 */
class MainWindow :
  public QMainWindow,
  private Ui::MainForm
{
  
Q_OBJECT

public:

  /**
   * @brief Constructor: Sets up the buttons and explicitly constructs DataWidgets and adds them to the QTabWidget. Connects signals and slots for
   *        these widgets.
   * @param parent This window's parent window (if any)
   */
  MainWindow(QMainWindow* parent = 0);

  /**
   * @brief Destructor: Deletes the data manager and all the data widgets
   */
  ~MainWindow();
  
private slots:

  /**
   * @brief Open file according to spin box values
   */
  void openFileDirectly(bool toggleState = true);

public:

  /**
   * @brief Process command line arguments (if any)
   */
  void processCmdLineArguments(QStringList args);

private:

  DataManager*        m_dataManager; /**< Pointer to the data manager, which is owned by this class */

  QList<DataWidget*>  m_dataWidgets; /**< List of (abstract) DataWidgets. Explicit derived instances of DataWidgets are constructed in the constructor and added here. */

};

#endif /* MainWindow_hh */
