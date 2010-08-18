/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: DataManager.hh,v 1.4 2010/08/18 18:33:23 beischer Exp $
/////////////////////////////////////////////////////////////////

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
