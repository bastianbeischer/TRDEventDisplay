#include "DataManager.hh"

#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QTimer>
#include <QDateTime>

#include <cassert>

#include <TFile.h>
#include <TTree.h>

#include "TrdRawEvent.hh"
#include "TrdRawRun.hh"

#include <root.h>
#include <amschain.h>

// constructor
DataManager::DataManager() :
  QObject(),
  m_dir(0),
  m_timer(new QTimer()),
  m_file(0),
  m_tree(0),
  m_currentRun(0),
  m_amsChain(0)
{
  // setup AMS root file directory
  QStringList envVariables = QProcess::systemEnvironment();
  QStringList filteredVars = envVariables.filter(QRegExp("^AMS_ROOTFILES_DIR=*"));
  if (filteredVars.size() != 0) {
    QString amsEntry = filteredVars.first();
    QString path = amsEntry.split("=").at(1);
    m_dir = new QDir(path);
  }
  else {
    qWarning("AMS_ROOTFILES_DIR environment variable is not set!");
    m_dir = new QDir();
  }
  
  // setup timer
  m_timer->setInterval(60 * 1000); //msec
  connect(this, SIGNAL(startedFollowing()), this, SLOT(readLatestFile()));
  connect(this, SIGNAL(startedFollowing()), m_timer, SLOT(start()));
  //  connect(this, SIGNAL(stoppedFollowing()), this, SLOT(closeFile()));
  connect(this, SIGNAL(stoppedFollowing()), m_timer, SLOT(stop()));
  connect(m_timer, SIGNAL(timeout()), this, SLOT(readLatestFile()));
}

// destructor
DataManager::~DataManager()
{
  delete m_dir;
  delete m_timer;
  delete m_file;
  delete m_currentRun;
  delete m_amsChain;
}

// dialog for a new file query
void DataManager::openFileDialog()
{
  // read file name from a dialog
  QString fileName = QFileDialog::getOpenFileName(0, tr("Open ROOT File"), m_dir->path(), tr(""));  

  // file dialog returns emptry string for e.g. "cancel"
  if (fileName != "")
    openFile(fileName);
}

// follow files mode
void DataManager::followFiles(bool start)
{
  if (m_dir) {
    start ? emit(startedFollowing()) : emit(stoppedFollowing());
  }
  else {
    QMessageBox::information(0, "TRD Event Display", "Can't follow: AMS_ROOTFILES_DIR environment variable is not set!");
    emit(stoppedFollowing());
  }
}

// try to read the latest file
void DataManager::readLatestFile()
{
  QStringList filters;
  filters << "[0-9][0-9][0-9][0-9]";
  QString subdirPath = m_dir->entryList(filters, QDir::Dirs, QDir::Name).last();
  QDir subdir(m_dir->path() + "/" + subdirPath);

  if (subdir.exists()) {
    filters.clear();
    filters << "*.root";
    QString fileName = subdir.entryList(filters, QDir::Files, QDir::Name).last();

    int dirNumber = subdirPath.toInt();
    int fileNumber = fileName.remove(QRegExp("\\.root$")).toInt();
      
    openFileByScheme(dirNumber, fileNumber);
  }
}

// close the currently open file
void DataManager::closeFile()
{
  if (m_file) {
    m_file->Close();
    delete m_file;
    m_file = 0;
    m_tree = 0;
    m_currentRun = 0;
    emit(fileClosed());
  }
  else if (m_amsChain) {
    delete m_amsChain;
    m_amsChain = 0;
    emit(fileClosed());
  }
  else {
    QMessageBox::information(0, "TRD Event Display", "No file is currently open!");
  }
}

// open the file given by "fileName"
int DataManager::openFile(QString fileName)
{
  // if there was another file opened close it
  if (m_file || m_amsChain)
    closeFile();
    
  // setup the tree and run pointers
  TFile* file = TFile::Open(qPrintable(fileName), "READ");
  if (!file || file->IsZombie()) {
    qWarning() << "DataManager::openFile() <> Could not open file (or file is a zombie)!";
    return 0;
  }
  TTree* trdTree = (TTree*) file->Get("TrdRawData");
  TTree* amsRootTree = (TTree*) file->Get("AMSRoot");
  if (trdTree) {
    m_file = file;
    m_tree = trdTree;
    m_tree->SetBranchAddress("run", &m_currentRun);
    m_tree->GetEntry(0);
    if (m_currentRun) {
      int nEvents = m_currentRun->GetEvents()->size();
      emit(fileOpened(nEvents));
      return 1;
    }
    //QMessageBox::information(0, "TRD Event Display", "Tree does not contain any runs!");
    qWarning() << "DataManager::openFile() <> Tree does not contain any runs!";
    return 0;
  }
  else if (amsRootTree) {
    file->Close();
    delete file;
    m_amsChain = new AMSChain;
    int success = m_amsChain->Add(qPrintable(fileName));
    if (success) {
      m_amsChain->GetEvent(0);
      emit(fileOpened(m_amsChain->GetEntries()));
    }
    else {
      qWarning() << "DataManager::openFile() <> Not able to add the file to the AMS chain!";
    }
    return success;
  }
  else {
    //QMessageBox::information(0, "TRD Event Display", "File does not contain a valid ROOT tree!");
    qWarning() << "DataManager::openFile() <> File does not contain a valid ROOT tree!";
    return 0;
  }
}

// open file with $AMS_ROOTFILES_DIR/XXXX/YYY.root scheme
void DataManager::openFileByScheme(int dir, int file)
{
  if (m_dir) {
    QString fileString;
    fileString.sprintf("/%04d/%03d.root", dir, file);
    int success = openFile(m_dir->path() + fileString);
    if(success) {
      emit(dirNumberChanged(dir));
      emit(fileNumberChanged(file));
    }
  }
  else {
    qWarning("AMS_ROOTFILES_DIR not set: Continuing without opening files...");
  }
}
  
// return the event with number eventNumber
const std::vector<TrdRawHitR>* DataManager::getTrdHits(int eventNumber) const
{
  if (m_tree && m_currentRun) {
    const std::vector<TrdRawEvent>* events = m_currentRun->GetEvents();
    return events->at(eventNumber-1).GetHits();
  }
  else if (m_amsChain) {
    AMSEventR* event = m_amsChain->GetEvent(eventNumber-1);
    if (event)
      return &(event->TrdRawHit());
  }
  QMessageBox::information(0, "TRD Event Display", "Please open a valid file first!");
  return 0;
}

// the run number
const QString DataManager::getRunId() const
{
  if (m_currentRun)
    return QString("%1").arg(m_currentRun->runid);
  else if (m_amsChain)
    return QString("%1").arg(m_amsChain->get_run());
  assert(false);
  return 0;
}

// the event number
const QString DataManager::getEventId() const
{
  if (m_currentRun) {
    // currently not implemented!
    return QString("");
  }
  else if (m_amsChain) {
    AMSEventR* event = m_amsChain->pEvent();
    return QString("%1").arg(event->Event());
  }
  assert(false);
  return 0;
}

// the time
const QString DataManager::getTime() const
{
  if (m_currentRun) {
    // currently not implemented!
    return QString("");
  }
  else if (m_amsChain) {
    AMSEventR* event = m_amsChain->pEvent();
    QDateTime dt = QDateTime::fromTime_t(event->UTime());
    return dt.toString();
  }
  assert(false);
  return 0;
}
