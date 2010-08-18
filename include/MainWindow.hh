/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: MainWindow.hh,v 1.11 2010/08/18 19:00:49 beischer Exp $
/////////////////////////////////////////////////////////////////

#ifndef MainWindow_hh
#define MainWindow_hh

#include <QMainWindow>
#include <ui_EventDisplayForm.h>

class ZoomableView;
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
  ZoomableView*      m_view;
  EventDisplayScene* m_scene;
  DataManager*       m_dataManager;

};

#endif /* MainWindow_hh */
