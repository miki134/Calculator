#pragma once
#include<qlist.h>
#include<vector>
#include<qstring.h>

class MathOperation
{

	static std::vector <std::vector <unsigned char>> characters;
private:
	QString operation;

	unsigned char character;
	int position;

	double leftNumber;
	double rightNumber;
public:
	MathOperation() = default;
	~MathOperation() = default;

public:
	QString result(QString&);
	QString deleteAll(QString&);
	QString deleteLast(QString&);

private:
	bool findFirstSign(); //checks the sign

	void findCharacterPosition(); //returns the position of the found character

	void setLeftNumber(); //sets the number to the left of the sign
	void setRightNumber(); //sets the number to the right of the sign

	int findLeftSeparator(); //returns a position of the next sign or the end of the math operation on the left of the sign
	int findRightSeparator(); //returns a position of the next sign or the end of the math operation on the right of the sign

	double mathOperations(); //performs math operations




	
};

