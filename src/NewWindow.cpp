#include "NewWindow.h"



NewWindow::NewWindow(QWidget *parent)
	:
	QDialog(parent)
{
	window->resize(1100, 600);
	window->setWindowTitle("Calculator");
    window->setWindowIcon(QIcon(":/icon.png"));
}

void NewWindow::on_clicked()
{
	window->show();

}

