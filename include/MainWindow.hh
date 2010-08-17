#ifndef MainWindow_hh
#define MainWindow_hh

#include <QMainWindow>
#include <ui_EventDisplayForm.h>

class GraphicsView;
class Scene;
class TFile;
class TTree;
class TrdRawRun;

class MainWindow :
  public QMainWindow,
  private Ui::EventDisplayForm
{
  
Q_OBJECT

public:
  MainWindow(QMainWindow* parent = 0);
  ~MainWindow();
  
private slots:
  void openFileDialog();
  void showEvent(int eventNumber);

private:
  GraphicsView* m_view;
  Scene*        m_scene;

  TFile*        m_file;
  TTree*        m_tree;
  TrdRawRun*    m_currentRun;

};

#endif /* MainWindow_hh */
