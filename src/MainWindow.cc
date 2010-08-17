#include "MainWindow.hh"

#include <QDebug>
#include <QFileDialog>
#include <QLinearGradient>
#include <QMessageBox>
#include <QPalette>
#include <QProcess>
#include <QResizeEvent>

#include <TFile.h>
#include <TTree.h>

#include "GraphicsView.hh"
#include "Scene.hh"
#include "TrdRawRun.hh"

// constructor
MainWindow::MainWindow(QMainWindow* parent) : 
  QMainWindow(parent),
  m_view(0),
  m_scene(0),
  m_amsRootFileDir(""),
  m_file(0),
  m_tree(0),
  m_currentRun(0)
{
  // setup designer settings
  setupUi(this);

  // create graphics view and scene
  m_view = new GraphicsView(graphicsViewFrame);
  m_scene = (Scene*)m_view->scene();
  centralLayout->addWidget(m_view, 4,0,1,1);

  // draw color legend
  QLinearGradient linGrad(QPointF(0.0, 1.0), QPointF(1.0, 1.0));
  linGrad.setCoordinateMode(QGradient::ObjectBoundingMode);
  linGrad.setColorAt(0.0, Qt::blue);
  linGrad.setColorAt(0.5, Qt::green);
  linGrad.setColorAt(1.0, Qt::red);
  QPalette palette;
  palette.setBrush(QPalette::Inactive, QPalette::Window, QBrush(linGrad));
  palette.setBrush(QPalette::Active, QPalette::Window, QBrush(linGrad));
  colorPaletteWidget->setPalette(palette);
  colorPaletteWidget->setAutoFillBackground(true);

  // connect signals and slots
  connect(quitButton, SIGNAL(pressed()), this, SLOT(close()));  
  connect(openFileButton, SIGNAL(pressed()), this, SLOT(openFileDialog()));
  connect(eventNumberSpinBox, SIGNAL(valueChanged(int)), this, SLOT(showEvent(int)));
  connect(this, SIGNAL(eventNumberChanged(int)), eventNumberSpinBox, SLOT(setValue(int)));
  connect(minAmpSpinBox, SIGNAL(valueChanged(int)), m_scene, SLOT(changeMinAmp(int)));
  connect(maxAmpSpinBox, SIGNAL(valueChanged(int)), m_scene, SLOT(changeMaxAmp(int)));
  connect(minAmpSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateScaleLabels()));
  connect(maxAmpSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateScaleLabels()));
  connect(negAmpCheckBox, SIGNAL(stateChanged(int)), m_scene, SLOT(changeDisplayNegAmps(int)));
  connect(tubesWithNoHitsCheckBox, SIGNAL(stateChanged(int)), m_scene, SLOT(changeTubeWithNoHitsVisible(int)));


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

// destructor
MainWindow::~MainWindow()
{
  delete m_view;
  delete m_file;
  delete m_tree;
  delete m_currentRun;
}

// dialog for a new file query
void MainWindow::openFileDialog()
{
  // read file name from a dialog
  QString fileName = QFileDialog::getOpenFileName(this, tr("open file"), m_amsRootFileDir, tr(""));  

  // file dialog returns emptry string for e.g. "cancel"
  if (fileName != "")
    openFile(fileName);
}

// open the file
void MainWindow::openFile(QString fileName)
{
  // if there was another file opened close it
  if (m_file) {
    m_file->Close();
    delete m_file;
  }

  // setup the tree and run pointers
  m_file = new TFile(qPrintable(fileName));
  m_tree = (TTree*) m_file->Get("TrdRawData");
  if (m_tree) {
    m_tree->SetBranchAddress("run", &m_currentRun);
    m_tree->GetEntry(0);
    if (m_currentRun) {
      minAmpSpinBox->setEnabled(true);
      maxAmpSpinBox->setEnabled(true);
      negAmpCheckBox->setEnabled(true);
      tubesWithNoHitsCheckBox->setEnabled(true);
      eventNumberSpinBox->setMinimum(1);
      eventNumberSpinBox->setMaximum(m_currentRun->GetEvents()->size());
      eventNumberSpinBox->setEnabled(true);
      showEvent(1);
    }
    else {
      QMessageBox::information(this, "TRD Event Display", "Tree does not contain any runs!");
      eventNumberSpinBox->setEnabled(false);
    }
  }
  else {
    QMessageBox::information(this, "TRD Event Display", "File does not contain a valid ROOT tree!");
    return;
  }
}

// show event
void MainWindow::showEvent(int eventNumber)
{
  if (!m_tree || !m_currentRun) {
    QMessageBox::information(this, "TRD Event Display", "Please open a valid file first!");
    return;
  }
  std::vector<TrdRawEvent>* events = m_currentRun->GetEvents();
  m_scene->processEvent(&events->at(eventNumber-1));
  m_view->fitScene();
  emit(eventNumberChanged(eventNumber));
}

// update labels under scale
void MainWindow::updateScaleLabels()
{
  double max = maxAmpSpinBox->value();
  double min = minAmpSpinBox->value();

  double value;
  QString text;

  value = min;
  text.sprintf("%.0f", value);
  scaleLabelMin->setText(text);

  value = min + 0.25*(max-min);
  text.sprintf("%.0f", value);
  scaleLabel1->setText(text);

  value = min + 0.5*(max-min);
  text.sprintf("%.0f", value);
  scaleLabel2->setText(text);

  value = min + 0.75*(max-min);
  text.sprintf("%.0f", value);
  scaleLabel3->setText(text);

  value = max;
  text.sprintf("%.0f", value);
  scaleLabelMax->setText(text);
}

// resize the view when resizing the window
void MainWindow::resizeEvent(QResizeEvent* event)
{
  QMainWindow::resizeEvent(event);
  m_view->fitScene();
}

// we can only fit the scene after the call to show
void MainWindow::show()
{
  QMainWindow::show();
  m_view->fitScene();
}
