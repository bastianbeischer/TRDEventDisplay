/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: MainWindow.cc,v 1.31 2010/08/19 17:51:00 beischer Exp $
/////////////////////////////////////////////////////////////////

#include "MainWindow.hh"

#include <QResizeEvent>

#include "DataManager.hh"
#include "EventDisplayWidget.hh"

// constructor
MainWindow::MainWindow(QMainWindow* parent) : 
  QMainWindow(parent),
  m_dataManager(new DataManager()),
  m_eventDisplayWidget(0)
{
  // setup designer settings
  setupUi(this);

  m_eventDisplayWidget = new EventDisplayWidget(m_dataManager);
  m_tabWidget->clear();
  m_tabWidget->addTab(m_eventDisplayWidget, "Event Display");

  // connect signals and slots
  
  // general
  connect(m_quitButton, SIGNAL(clicked()), this, SLOT(close()));  

  // IO
  connect(m_openFileButton, SIGNAL(clicked()), m_dataManager, SLOT(openFileDialog()));
  connect(m_dataManager, SIGNAL(fileOpened(int)), m_eventDisplayWidget, SLOT(fileOpened(int)));
  connect(m_dataManager, SIGNAL(fileClosed()), m_eventDisplayWidget, SLOT(fileClosed()));

  // show myself
  show();
}

// destructor
MainWindow::~MainWindow()
{
  delete m_dataManager;
}

// command line arguments: open the respective files
void MainWindow::processCmdLineArguments(QStringList args)
{
  // either directly...
  if (args.size() == 2)
    m_dataManager->openFile(args.at(1));

  // or by $AMS_ROOTFILES_DIR/XXXX/YYY.root format
  else if (args.size() == 3)
    m_dataManager->openFileByScheme(args.at(1).toInt(), args.at(2).toInt());
}
