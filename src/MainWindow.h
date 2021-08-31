#pragma once
#include <QMainWindow>

#include "Interface.h"

class MainWindow : public QMainWindow
{
private:
	Interface window;
public:
    MainWindow(QWidget *parent = 0);

	void show();
};