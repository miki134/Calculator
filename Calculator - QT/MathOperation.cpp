#include "MathOperation.h"
#include<qlist.h>
#include<iostream>
#include<string>
#include<qchar.h>
#include<qdebug.h>

std::vector <std::vector <unsigned char>> MathOperation::characters{ {247,215}, {'+', '-'} };

QString MathOperation::result(QString& operation)
{
	this->operation = operation;

	while (findFirstSign())
	{
		findCharacterPosition();
		setLeftNumber();
		setRightNumber();

		//qDebug() << leftNumber << " " << character<< " " << rightNumber;

		this->operation.replace(findLeftSeparator() + 1, findRightSeparator() - findLeftSeparator() - 1, QString::number(mathOperations(), 'g', 16));
		operation = this->operation;
	}
	return this->operation;
}

QString MathOperation::deleteAll(QString& operation)
{
	return operation = "";
}

QString MathOperation::deleteLast(QString& operation)
{
	return operation.remove(operation.length() - 1, 1);
}

bool MathOperation::findFirstSign()
{
	for (int i = 0; i < operation.length(); i++)
		for (int y = 0; y < characters.size(); y++)
			for (unsigned char z : characters[y])
			{
				if (i == 0 && operation[i] == '-') i++;
				else if (z == operation[i]) return true;
			}
	return false;
}

void MathOperation::findCharacterPosition()
{
	for (int y = 0; y < characters.size(); y++)
		for (unsigned char z : characters[y]) 
			for (int i = 0; i < operation.length(); i++)
				if (z == operation[i])
				{
					if (i == 0 && operation[i] == '-') i++;
					else
					{
						position = i;
						character = operation[i].toLatin1();
						return;
					}
				}
}

int MathOperation::findLeftSeparator()
{
	for (int i = position-1; i >= 0; i--)
		for (int y = 0; y < characters.size(); y++)
			for (QChar z : characters[y])
				if (operation[i] == z && z!='-') return i;
	return -1;
}

int MathOperation::findRightSeparator()
{
	for (int i = position+2; i < operation.length(); i++)
		for (int y = 0; y < characters.size(); y++)
			for (QChar z : characters[y])
				if (operation[i] == z) return i;
	return operation.length();
}

void MathOperation::setLeftNumber()
{
	leftNumber = operation.mid(findLeftSeparator() + 1, position - findLeftSeparator()-1).toDouble();
}

void MathOperation::setRightNumber()
{
	rightNumber = operation.mid(position + 1, findRightSeparator() - position - 1).toDouble();
}

double MathOperation::mathOperations()
{
	switch (character)
	{
	case 247: return leftNumber / rightNumber;
		break;
	case 215: return leftNumber * rightNumber;
		break;
	case '+': return leftNumber + rightNumber;
		break;
	case '-': return leftNumber - rightNumber;
		break;
	}
}