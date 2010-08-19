/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: MainWindow.hh,v 1.14 2010/08/19 20:55:54 beischer Exp $
/////////////////////////////////////////////////////////////////

#ifndef MainWindow_hh
#define MainWindow_hh

#include <QMainWindow>
#include "ui_MainForm.h"

#include <QList>

class DataManager;
class DataWidget;

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

  QList<DataWidget*>  m_dataWidgets;

};

#endif /* MainWindow_hh */
