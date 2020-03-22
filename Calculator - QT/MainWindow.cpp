#include<qicon.h>
#include"MainWindow.h"
#include"Interface.h"


MainWindow::MainWindow(QWidget *parent)
	:
	QMainWindow(parent)
{
	window.setWindowTitle("Calculator");
	window.setWindowIcon(QIcon("icon.png"));
}

void MainWindow::show()
{
	window.show();
}
