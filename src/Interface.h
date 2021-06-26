#pragma once
#include<qwidget.h>
#include<qgridlayout.h>
#include<qpushbutton.h>
#include<qlabel.h>
#include<qfile.h>
#include <QKeyEvent>

#include"MathOperation.h"

class Interface : public QWidget, MathOperation
{
	Q_OBJECT
public:
	Interface(QWidget *parent = 0);
	~Interface();

private:
	void run();
	void createButtons();
	void createLayout();
	void connectButtons();

	void loadDesign();

private:
	QVBoxLayout *layout; //main layout, contains a label and a grid
	
	QLabel *label; //Contains a operation
	QGridLayout *gridButtons, *gridBackspace; //Arrangement of buttons
	
	QString operation = ""; //operation in label, math operation

	QList <unsigned char> values; //Button values
	QPushButton *buttons, *buttonsBackspace; //Array of buttons

private slots:
	void addOperation(unsigned char);

protected:
	void keyPressEvent(QKeyEvent *event);	

};
