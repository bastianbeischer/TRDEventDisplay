#ifndef DataManager_hh
#define DataManager_hh

#include <QObject>

class TFile;
class TTree;
class TrdRawEvent;
class TrdRawRun;

class DataManager :
  public QObject
{
  
Q_OBJECT

public:
  DataManager();
  ~DataManager();
  
signals:
  void fileOpened(int nEvents);
  void fileClosed();

public slots:
  void openFileDialog();

public:
  QString amsRootFileDir() const {return m_amsRootFileDir;}

  void openFile(QString fileName);
  void openFileByScheme(int dir, int file);
  TrdRawEvent* getEvent(int eventNumber);

private:
  QString       m_amsRootFileDir;

  TFile*        m_file;
  TTree*        m_tree;
  TrdRawRun*    m_currentRun;

};

#endif /* DataManager_hh */
