#include <QApplication>

#include "MainWindow.hh"

int main(int argc, char** argv)
{
  QApplication app(argc, argv);
  MainWindow* window = new MainWindow;
  window->show();

  // in case of command line arguments: open the respective files
  QStringList args = app.arguments();

  // either directly...
  if (args.size() == 2) {
    window->openFile(args.at(1));
  }
  // or by XXXX YYY format from AMS_ROOTFILE_DIR directory
  else if (args.size() == 3) {
    QString dir = window->amsRootFileDir();
    if (dir != "") {
      int arg1 = args.at(1).toInt();
      int arg2 = args.at(2).toInt();
      QString fileString;
      fileString.sprintf("/%04d/%03d.root", arg1, arg2);
      window->openFile(dir + fileString);
    }
    else {
      qWarning("Continuing without opening files...");
    }
  }

  return app.exec();
}
