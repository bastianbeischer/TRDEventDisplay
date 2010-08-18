#include "DataManager.hh"

#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>

#include <TFile.h>
#include <TTree.h>

#include "TrdRawEvent.hh"
#include "TrdRawRun.hh"

DataManager::DataManager() :
  QObject(),
  m_amsRootFileDir(""),
  m_file(0),
  m_tree(0),
  m_currentRun(0)
{
  // setup AMS root file directory
  QStringList envVariables = QProcess::systemEnvironment();
  QStringList filteredVars = envVariables.filter(QRegExp("^AMS_ROOTFILES_DIR=*"));
  if (filteredVars.size() == 0) {
    qWarning("AMS_ROOTFILES_DIR environment variable is not set!");
  }
  else {
    QString amsEntry = filteredVars.first();
    m_amsRootFileDir = amsEntry.split("=").at(1);
  }
}

DataManager::~DataManager()
{
  delete m_file;
  delete m_tree;
  delete m_currentRun;
}

// dialog for a new file query
void DataManager::openFileDialog()
{
  // read file name from a dialog
  QString fileName = QFileDialog::getOpenFileName(0, tr("open file"), m_amsRootFileDir, tr(""));  

  // file dialog returns emptry string for e.g. "cancel"
  if (fileName != "")
    openFile(fileName);
}

void DataManager::openFile(QString fileName)
{
  // if there was another file opened close it
  if (m_file) {
    m_file->Close();
    delete m_file;
    emit(fileClosed());
  }

  // setup the tree and run pointers
  m_file = new TFile(qPrintable(fileName));
  m_tree = (TTree*) m_file->Get("TrdRawData");
  if (m_tree) {
    m_tree->SetBranchAddress("run", &m_currentRun);
    m_tree->GetEntry(0);
    if (m_currentRun) {
      int nEvents = m_currentRun->GetEvents()->size();
      emit(fileOpened(nEvents));
    }
    else {
      QMessageBox::information(0, "TRD Event Display", "Tree does not contain any runs!");
    }
  }
  else {
    QMessageBox::information(0, "TRD Event Display", "File does not contain a valid ROOT tree!");
    return;
  }
}

// open file with XXXX/YYY.root scheme
void DataManager::openFileByScheme(int dir, int file)
{
  if (m_amsRootFileDir != "") {
    QString fileString;
    fileString.sprintf("/%04d/%03d.root", dir, file);
    openFile(m_amsRootFileDir + fileString);
  }
  else {
    qWarning("AMS_ROOTFILES_DIR not set: Continuing without opening files...");
  }
}
  
// return the event with number eventNumber
TrdRawEvent* DataManager::getEvent(int eventNumber)
{
  if (!m_tree || !m_currentRun) {
    QMessageBox::information(0, "TRD Event Display", "Please open a valid file first!");
    return 0;
  }
  std::vector<TrdRawEvent>* events = m_currentRun->GetEvents();
  return &events->at(eventNumber-1);
}
