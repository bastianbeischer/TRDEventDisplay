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
