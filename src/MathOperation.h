#pragma once
#include <QString>

#include <vector>
#include <set>
#include <map>

class MathOperation
{
public:
    MathOperation(const QString &mathOperation);
    ~MathOperation() = default;

    double execute();

    static QList<QString> infixToRPN(const QString& mathOperation);
    static QStringList splitStringToMathOperations(const QString & mathOperation);
    static double executeRPN(QList<QString> &postfixNotation);
    static double mathOperations(double & leftNumber, double & rightNumer, const unsigned char & token);

	QString result(QString&);
	QString deleteAll(QString&);
	QString deleteLast(QString&);

private:
    static std::vector <std::vector <unsigned char>> characters;
    static std::set<QChar> symbols;

    bool findFirstSign();

    void findCharacterPosition();

    void setLeftNumber();
    void setRightNumber();

    int findLeftSeparator();
    int findRightSeparator();


    QString operation;
    unsigned char character;
    int position;

    double leftNumber;
    double rightNumber;
};

