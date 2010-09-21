#include "DataManager.hh"

#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QTimer>

#include <TFile.h>
#include <TTree.h>

#include "TrdRawEvent.hh"
#include "TrdRawRun.hh"

// constructor
DataManager::DataManager() :
  QObject(),
  m_dir(0),
  m_timer(new QTimer()),
  m_file(0),
  m_tree(0),
  m_currentRun(0)
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
  delete m_tree;
  delete m_currentRun;
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
    if (start) {
      emit(startedFollowing());
    }
    else {
      emit(stoppedFollowing());
    }
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
  else {
    QMessageBox::information(0, "TRD Event Display", "No file is currently open!");
  }
}

// open the file given by "fileName"
int DataManager::openFile(QString fileName)
{
  // if there was another file opened close it
  if (m_file)
    closeFile();

  // setup the tree and run pointers
  m_file = new TFile(qPrintable(fileName), "READ");
  m_tree = (TTree*) m_file->Get("TrdRawData");
  if (m_tree) {
    m_tree->SetBranchAddress("run", &m_currentRun);
    m_tree->GetEntry(0);
    if (m_currentRun) {
      int nEvents = m_currentRun->GetEvents()->size();
      emit(fileOpened(nEvents));
      return 1;
    }
    else {
      //QMessageBox::information(0, "TRD Event Display", "Tree does not contain any runs!");
      qWarning() << "DataManager::openFile() <> Tree does not contain any runs!";
      return 0;
    }
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
const TrdRawEvent* DataManager::getEvent(int eventNumber) const
{
  if (!m_tree || !m_currentRun) {
    QMessageBox::information(0, "TRD Event Display", "Please open a valid file first!");
    return 0;
  }
  const std::vector<TrdRawEvent>* events = m_currentRun->GetEvents();
  return &events->at(eventNumber-1);
}

// the run number
const QString DataManager::getRunId() const
{
  return QString("%1").arg(m_currentRun->runid);
}
