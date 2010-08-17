#include <QApplication>
#include <QProcess>

#include "MainWindow.hh"

int main(int argc, char** argv)
{
  QApplication app(argc, argv);
  MainWindow* window = new MainWindow;
  window->show();

  // in case of command line arguments: open the respective files
  QStringList args = app.arguments();
  if (args.size() == 2) {
    window->openFile(args.at(1));
  }
  else if (args.size() == 3) {
    QStringList envVariables = QProcess::systemEnvironment();
    QStringList filteredVars = envVariables.filter(QRegExp("^AMS_ROOTFILES_DIR=*"));

    if (filteredVars.size() == 0) {
      qWarning("AMS_ROOTFILES_DIR environment variable is not set! Continuing without opening file...");
    }
    else {
      QString amsEntry = filteredVars.first();
      QString dir = amsEntry.split("=").at(1);

      int arg1 = args.at(1).toInt();
      int arg2 = args.at(2).toInt();

      QString fileString;
      fileString.sprintf("/%04d/%03d.root", arg1, arg2);

      window->openFile(dir + fileString);
    }
  }

  return app.exec();
}
