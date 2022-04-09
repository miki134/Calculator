#include "MathOperation.h"
#include <stack>
#include <QStringList>
#include <QChar>

std::vector <std::vector <unsigned char>> MathOperation::characters{ {247,215}, {'+', '-'} };
std::set<QChar> MathOperation::symbols {QChar(247), QChar(215), '+', '-', '(', ')'};

MathOperation::MathOperation(const QString &mathOperation)
    : operation(mathOperation)
{
}

double MathOperation::execute()
{
    QList<QString> rpn = infixToRPN(operation);
    return executeRPN(rpn);
}

QList<QString> MathOperation::infixToRPN(const QString &mathOperation)
{
    QStringList tokenList = splitStringToMathOperations(mathOperation);

    std::map<QChar, unsigned int> calcActions = {
        {QChar(247), 3},
        {QChar(215), 3},
        {'+', 2},
        {'-', 2},
        {'(', 1}
    };

    std::stack<QChar> opStack;
    QList<QString> postfixList;

    QChar topToken;
    for (const QString &token : qAsConst(tokenList))
    {
     if(symbols.find(token[0]) == symbols.end())
         postfixList.push_back(token);//tutaj
     else if (token[0] == '(')
         opStack.push(token[0]);
     else if (token[0] == ')')
     {
         topToken = opStack.top();
         opStack.pop();
         while (topToken != '(')
         {
             postfixList.push_back(topToken);
             topToken = opStack.top();
             opStack.pop();
         }
     }
     else
     {
        while (!opStack.empty() && (calcActions[opStack.top()] >= calcActions[token[0]]))
        {
         postfixList.push_back(opStack.top());
         opStack.pop();
        }
        opStack.push(token[0]);
     }
    }

    while(!opStack.empty())
     {
         postfixList.push_back(opStack.top());
         opStack.pop();
     }

    return postfixList;
}

double MathOperation::executeRPN(QList<QString> &postfixNotation)
{
    QList<double> stack;
    while (!postfixNotation.empty())
    {
        if(symbols.find(postfixNotation.first()[0]) == symbols.end())
        {
            stack.push_back(postfixNotation.takeFirst().toDouble());
        }
        else
        {
            double secondOperand = stack.takeLast();
            double firstOperand = stack.takeLast();
            QString lastSymbol = postfixNotation.takeFirst();
            stack.push_back(mathOperations(firstOperand, secondOperand, lastSymbol[0].toLatin1()));
        }
    }

    return stack.at(0);
}

QStringList MathOperation::splitStringToMathOperations(const QString &mathOperation)
{
    QStringList groupOperations;
    QStringList tokenList = mathOperation.split("", Qt::SkipEmptyParts);

    while(!tokenList.isEmpty())
    {
        if(symbols.find(tokenList.first()[0]) != symbols.end())
        {
            groupOperations.append(tokenList.first());
            tokenList.removeFirst();
        }
        else if(tokenList.size() > 1)
        {
            QString longerSign = tokenList.first();
            tokenList.removeFirst();
            while (symbols.find(tokenList.first()[0]) == symbols.end()) {
                longerSign += tokenList.first();
                tokenList.removeFirst();

                if(tokenList.isEmpty())
                    break;
            }
            groupOperations.append(longerSign);
        }
        else
        {
            groupOperations.append(tokenList.first());
            tokenList.removeFirst();
        }
    }

    while(symbols.find(groupOperations.last()[0]) != symbols.end())
    {
        groupOperations.removeLast();
    }

    return groupOperations;
}

QString MathOperation::result(QString& operation)
{
	this->operation = operation;

	while (findFirstSign())
	{
		findCharacterPosition();
		setLeftNumber();
        setRightNumber();

        this->operation.replace(findLeftSeparator() + 1, findRightSeparator() - findLeftSeparator() - 1, QString::number(mathOperations(leftNumber, rightNumber, character), 'g', 16));
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
    {
        for (unsigned int y = 0; y < characters.size(); y++)
			for (unsigned char z : characters[y])
			{
				if (i == 0 && operation[i] == '-') i++;
                else if (QChar(z) == operation[i]) return true;
			}
    }
	return false;
}

void MathOperation::findCharacterPosition()
{
    for (unsigned int y = 0; y < characters.size(); y++)
		for (unsigned char z : characters[y]) 
			for (int i = 0; i < operation.length(); i++)
                if (QChar(z) == operation[i])
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
        for (unsigned int y = 0; y < characters.size(); y++)
            for (auto z : characters[y])
                if (operation[i] == QChar(z) && z!='-') return i;
	return -1;
}

int MathOperation::findRightSeparator()
{
	for (int i = position+2; i < operation.length(); i++)
        for (unsigned int y = 0; y < characters.size(); y++)
            for (auto z : characters[y])
                if (operation[i] == QChar(z)) return i;
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

double MathOperation::mathOperations(double & leftNumber, double & rightNumber, const unsigned char & token)
{
    switch (token)
	{
    case 247: return leftNumber / rightNumber;
		break;
	case 215: return leftNumber * rightNumber;
		break;
	case '+': return leftNumber + rightNumber;
		break;
	case '-': return leftNumber - rightNumber;
		break;
    default:
        exit(2);
	}
}
