/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: MainWindow.hh,v 1.10 2010/08/18 18:33:23 beischer Exp $
/////////////////////////////////////////////////////////////////

#ifndef MainWindow_hh
#define MainWindow_hh

#include <QMainWindow>
#include <ui_EventDisplayForm.h>

class View;
class EventDisplayScene;
class DataManager;
class QResizeEvent;

class MainWindow :
  public QMainWindow,
  private Ui::EventDisplayForm
{
  
Q_OBJECT

public:
  MainWindow(QMainWindow* parent = 0);
  ~MainWindow();
  
signals:
  int eventNumberChanged(int newNumber);

public slots:
  void fileOpened(int nEvents);
  void fileClosed();

private slots:
  void showEvent(int eventNumber);
  void updateScale();

public:
  void processCmdLineArguments(QStringList args);

protected:
  void resizeEvent(QResizeEvent* event);

private:
  View*              m_view;
  EventDisplayScene* m_scene;
  DataManager*       m_dataManager;

};

#endif /* MainWindow_hh */
