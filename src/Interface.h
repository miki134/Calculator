#pragma once
#include <QLayout>
#include <QLabel>
#include <QKeyEvent>
#include <QApplication>
#include <QWidget>
#include <QPushButton>

#include "MathOperation.h"

class Interface : public QWidget
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
