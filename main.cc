/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: main.cc,v 1.12 2010/08/18 18:34:20 beischer Exp $
/////////////////////////////////////////////////////////////////

#include <QApplication>

#include "MainWindow.hh"

int main(int argc, char** argv)
{
  QApplication app(argc, argv);
  MainWindow* window = new MainWindow;

  QStringList args = app.arguments();
  if (args.size() > 1)
    window->processCmdLineArguments(args);

  return app.exec();
}
