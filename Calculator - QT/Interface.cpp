#include "Interface.h"
#include "MainWindow.h"

#include<qapplication.h>
#include<qwidget.h>
#include<qpushbutton.h>
#include<qdebug.h>

Interface::Interface(QWidget *parent)
	:
	QWidget(parent)
{
	run();
	loadDesign();
}

void Interface::run()
{
	values =
	{ '7', '8', '9', 247,
	  '4', '5', '6', 215,
	  '1', '2', '3', '-',
	  '0', '.', '=', '+' };

	layout = new QVBoxLayout(this);
	layout->setSpacing(2);
	
	gridButtons = new QGridLayout();	
	gridButtons->setSpacing(2);

	gridBackspace = new QGridLayout();
	gridButtons->setSpacing(2);

	createLayout();
	createButtons();
	
	connectButtons();
}

void Interface::createLayout()
{
	label = new QLabel(operation, this);
	label->setFixedHeight(label->height() * 2.5);
	label->setAlignment(Qt::AlignRight | Qt::AlignCenter);
	label->setFont(QFont("Arial", 15));
	layout->addWidget(label);
}

void Interface::createButtons()
{
	buttons = new QPushButton[16];
	buttonsBackspace = new QPushButton[2];

	buttonsBackspace[0].setText("C");
	buttonsBackspace[0].setFont(QFont("Arial", 20));
	
	buttonsBackspace[1].setIcon(QIcon("backspaceIcon.png"));
	buttonsBackspace[1].setIconSize(QSize(60, 40));

	for (int i = 0; i < 2; i++)
	{
		buttonsBackspace[i].setMinimumSize(140, 70);
		gridBackspace->addWidget(&buttonsBackspace[i], 0, i);
	}

	int position = 0;
	for (int vertical = 1; vertical < 5; vertical++)
	{
		for (int horizontal = 0; horizontal < 4; horizontal++)
		{
			buttons[position].setText((QString)values[position]);
			buttons[position].setSizePolicy(sizePolicy());
			buttons[position].setFont(QFont("Arial", 20));
			buttons[position].setMinimumSize(70, 70);

			gridButtons->addWidget(&buttons[position], vertical, horizontal);
			position++;

		}
	}

	layout->addLayout(gridBackspace);
	layout->addLayout(gridButtons);
}

void Interface::connectButtons()
{
	for(int position = 0;position<16;position++)
	{
		connect(&buttons[position], &QPushButton::clicked, this, [=]() {addOperation(values[position]); });
	}
	connect(&buttonsBackspace[0], &QPushButton::clicked, this, [=]() {addOperation('c'); });
	connect(&buttonsBackspace[1], &QPushButton::clicked, this, [=]() {addOperation('<'); });
}

void Interface::loadDesign()
{
	QFile styleSheet("StyleSheet.css");
	if (!styleSheet.open(QIODevice::ReadOnly))
		qDebug() << "Can't open file";
	qApp->setStyleSheet(styleSheet.readAll());
	styleSheet.close();
}

void Interface::addOperation(unsigned char sign)
{
	switch (sign)
	{
	case '=':
		label->setText(result(operation));
		break;
	case 'c':
		label->setText(deleteAll(operation));
		break;
	case '<':
		label->setText(deleteLast(operation));
		break;
	default:
		if (operation.length() < 16)
		{
			operation += sign;
			label->setText(operation);
			break;
		}
	}
}

void Interface::keyPressEvent(QKeyEvent *event)
{
	switch (event->key())
	{
	case Qt::Key_Escape:
		qApp->exit();
		break;
	case Qt::Key_Delete:
		addOperation('c');
		break;
	case Qt::Key_Backspace:
		addOperation('<');
		break;
	case Qt::Key_Enter:
		addOperation('=');
		break;
	case Qt::Key_Return:
		addOperation('=');
		break;
	case Qt::Key_Comma:
		addOperation('.');
		break;
	case Qt::Key_Asterisk:
		addOperation(215);
		break;
	case Qt::Key_Slash:
		addOperation(247);
		break;
	default:
		for (unsigned char i : values)
			if (event->key() == i)
				addOperation(i);
		break;
	}
}


Interface::~Interface()
{
	delete gridButtons;
	delete gridBackspace;
	delete[] buttons;
	delete[] buttonsBackspace;
	delete label;
	delete layout;

}	