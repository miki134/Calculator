#pragma once
#include <qmainwindow.h>
#include <qwidget.h>
#include <qdialog.h>


class NewWindow : public QDialog
{
public:
	NewWindow(QWidget *parent = 0);

private:
	QWidget *window = new QWidget(this);

public:
	void on_clicked();
};



