/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: MainWindow.cc,v 1.34 2010/08/24 15:21:01 beischer Exp $
/////////////////////////////////////////////////////////////////

#include "MainWindow.hh"

#include <QResizeEvent>

#include "DataManager.hh"
#include "EventDisplayWidget.hh"

// constructor
MainWindow::MainWindow(QMainWindow* parent) : 
  QMainWindow(parent),
  m_dataManager(new DataManager())
{
  // setup designer settings
  setupUi(this);

  // construct a new event display widget
  EventDisplayWidget* eventDisplayWidget = new EventDisplayWidget(m_dataManager);
  m_dataWidgets.push_back(eventDisplayWidget);

  // connect general signals and slots
  connect(m_quitButton, SIGNAL(clicked()), this, SLOT(close()));  
  connect(m_openFileButton, SIGNAL(clicked()), m_dataManager, SLOT(openFileDialog()));
  connect(m_closeFileButton, SIGNAL(clicked()), m_dataManager, SLOT(closeFile()));

  // add data widgets to the tabs and connect the signals and slots
  m_tabWidget->clear();
  foreach(DataWidget* widget, m_dataWidgets) {
    m_tabWidget->addTab(widget, widget->windowTitle());
    connect(m_dataManager, SIGNAL(fileOpened(int)), widget, SLOT(fileOpened(int)));
    connect(m_dataManager, SIGNAL(fileClosed()), widget, SLOT(fileClosed()));
  }

  // show myself
  show();
}

// destructor
MainWindow::~MainWindow()
{
  delete m_dataManager;
  foreach(DataWidget* widget, m_dataWidgets)
    delete widget;
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
