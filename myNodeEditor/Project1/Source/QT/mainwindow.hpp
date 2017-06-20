#pragma once
#include <QMainWindow>
#include <QTextEdit>  
#include <QDockWidget>  

class MainWidget;
class occQt;

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	MainWindow(QWidget * parent = Q_NULLPTR);
	~MainWindow();

private:
	
};
