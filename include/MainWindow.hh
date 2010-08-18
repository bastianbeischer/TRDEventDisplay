#ifndef MainWindow_hh
#define MainWindow_hh

#include <QMainWindow>
#include <ui_EventDisplayForm.h>

class DataManager;
class GraphicsView;
class QResizeEvent;
class Scene;

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
  GraphicsView* m_view;
  Scene*        m_scene;
  DataManager*  m_dataManager;

};

#endif /* MainWindow_hh */
