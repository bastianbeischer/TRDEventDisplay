#ifndef MainWindow_hh
#define MainWindow_hh

#include <QMainWindow>
#include <ui_EventDisplayForm.h>

class GraphicsView;
class Scene;
class TFile;
class TTree;
class TrdRawRun;
class QResizeEvent;

class MainWindow :
  public QMainWindow,
  private Ui::EventDisplayForm
{
  
Q_OBJECT

public:
  MainWindow(QMainWindow* parent = 0);
  ~MainWindow();
  
public:
  QString amsRootFileDir() const {return m_amsRootFileDir;}
  void openFile(QString fileName);
  void show();

signals:
  int eventNumberChanged(int newNumber);

private slots:
  void openFileDialog();
  void showEvent(int eventNumber);
  void updateScaleLabels();

protected:
  void resizeEvent(QResizeEvent* event);

private:
  GraphicsView* m_view;
  Scene*        m_scene;

  QString       m_amsRootFileDir;

  TFile*        m_file;
  TTree*        m_tree;
  TrdRawRun*    m_currentRun;

};

#endif /* MainWindow_hh */
