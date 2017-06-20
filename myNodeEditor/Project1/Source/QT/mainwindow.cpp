#include "mainwindow.hpp"
#include "occqt.hpp"
#include "occview.hpp"
#include "mainwidget.hpp"

MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent) {
	QDockWidget *dock = new QDockWidget(this);
	dock->setFeatures(QDockWidget::AllDockWidgetFeatures);
	MainWidget *main = new MainWidget();
	setCentralWidget(main);
	//设置停靠窗口1  
    dock = new QDockWidget(this);
	dock->setFeatures(QDockWidget::DockWidgetMovable);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	occQt *myoccQt = new occQt();

	dock->setWidget(myoccQt);
	addDockWidget(Qt::RightDockWidgetArea, dock);
	resize(1200, 768);

}

MainWindow::~MainWindow() {
	
}
