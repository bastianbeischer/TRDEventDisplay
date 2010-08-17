#include "MainWindow.hh"

#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

#include <TFile.h>
#include <TTree.h>

#include "GraphicsView.hh"
#include "Scene.hh"
#include "TrdRawRun.hh"
#include <QLinearGradient>
#include <QPalette>

MainWindow::MainWindow(QMainWindow* parent) : 
  QMainWindow(parent),
  m_file(0),
  m_tree(0),
  m_currentRun(0)
{
  // setup designer settings
  setupUi(this);

  // create graphics view and scene
  m_view = new GraphicsView(graphicsViewFrame);
  m_scene = (Scene*)m_view->scene();

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
  connect(action_Quit, SIGNAL(triggered()), this, SLOT(close()));  
  connect(action_Open_File, SIGNAL(triggered()), this, SLOT(openFileDialog()));
  connect(eventNumberSpinBox, SIGNAL(valueChanged(int)), this, SLOT(showEvent(int)));
  connect(minAmpSpinBox, SIGNAL(valueChanged(int)), m_scene, SLOT(minAmpChanged(int)));
  connect(maxAmpSpinBox, SIGNAL(valueChanged(int)), m_scene, SLOT(maxAmpChanged(int)));
  connect(negAmpCheckBox, SIGNAL(stateChanged(int)), m_scene, SLOT(changeDisplayNegAmps(int)));
  connect(tubesWithNoHitsCheckBox, SIGNAL(stateChanged(int)), m_scene, SLOT(tubeWithNoHitsVisible(int)));
}

MainWindow::~MainWindow()
{
  delete m_view;
  delete m_file;
  delete m_tree;
  delete m_currentRun;
}

void MainWindow::openFileDialog()
{
  // read file name from a dialog
  QString fileName = QFileDialog::getOpenFileName(this, tr("open file"),"", tr(""));  

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
      eventNumberSpinBox->setMaximum(m_currentRun->GetEvents()->size()-1);
      eventNumberSpinBox->setEnabled(true);
    }
    else {
      eventNumberSpinBox->setEnabled(false);
    }
  }
  else {
    QMessageBox::information(this, "Event Display Software", "File does not contain a valid ROOT tree!");
    return;
  }
}

void MainWindow::showEvent(int eventNumber)
{
  if (!m_tree || !m_currentRun) {
    QMessageBox::information(this, "Event Display Software", "Please open a file first!");
    return;
  }
  std::vector<TrdRawEvent>* events = m_currentRun->GetEvents();
  m_scene->processEvent(&events->at(eventNumber));
}
