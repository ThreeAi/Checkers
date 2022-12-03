#include <iostream>
#include "Checker.h"
#include <list>
#include <algorithm>

//Queen::Queen(int bx, int by, bool color) : Checker(bx, by, color) {};
void Queen::initialization()
{
	textChecker.loadFromFile("images/checker.png");
	shapeChecker = CircleShape(CHECKERS_RADIUS);
	shapeChecker.setTexture(&textChecker);
	if (!color)
		shapeChecker.setTextureRect(IntRect(113, 0, 112, 112));
	else
		shapeChecker.setTextureRect(IntRect(339, 0, 112, 112));
	shapeChecker.setPosition(actual.x, actual.y);
}
bool Queen::stepForward()
{
	if (abs(this->getBoardX() - this->getPrevBoardX()) ==  abs(this->getBoardY() - this->getPrevBoardY()))
		return true;
	else
		return false;
}
bool Queen::cutDownChecker(list<Checker>& list)
{
	auto find = find_if(list.begin(), list.end(), [this](Checker c)
		{
			return c.getColor() != this->getColor() && abs(c.getBoardX() - this->getBoardX()) == abs(c.getBoardY() - this->getBoardY());
		});
	if (abs(this->getBoardX() - this->getPrevBoardX()) == abs(this->getBoardY() - this->getPrevBoardY()) && find != list.end())
	{
		if (find->getColor())
			countBlack--;
		else
			countWhite--;
		list.erase(find);
		return true;
	}
	return false;
}