/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: MainWindow.hh,v 1.12 2010/08/19 17:50:59 beischer Exp $
/////////////////////////////////////////////////////////////////

#ifndef MainWindow_hh
#define MainWindow_hh

#include <QMainWindow>
#include <ui_MainForm.h>

class DataManager;
class EventDisplayWidget;

class MainWindow :
  public QMainWindow,
  private Ui::MainForm
{
  
Q_OBJECT

public:
  MainWindow(QMainWindow* parent = 0);
  ~MainWindow();
  
public:
  void processCmdLineArguments(QStringList args);

private:
  DataManager*        m_dataManager;

  EventDisplayWidget* m_eventDisplayWidget;

};

#endif /* MainWindow_hh */
