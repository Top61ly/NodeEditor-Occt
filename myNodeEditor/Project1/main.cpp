
#include <QApplication>
#include <QTranslator>

#include "mainwidget.hpp"
#include "mainwindow.hpp"

#include "occqt.hpp"

int
main(int argc, char *argv[])
{
  QApplication a(argc, argv);



 /* MainWindow mainwindow;
  mainwindow.show();
*/

  //occQt w;
  //w.show();


  MainWidget mainwidget;
  mainwidget.show();

  return a.exec();
}
