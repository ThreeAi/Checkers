#include <iostream>
#include "Checker.h"

Checker::Checker(int x, int y): x(x), y(y), prevX(x), prevY(y), isMove(false) {};
void Checker::Initialization()
{
	textChecker.loadFromFile("images/checker.png");
	shapeChecker = CircleShape(CHECKERS_RADIUS);
	shapeChecker.setTexture(&textChecker);
	shapeChecker.setTextureRect(IntRect(0, 0, 112, 112));
	shapeChecker.setPosition(x, y);
}
void Checker::setPosition(int X, int Y)
{
	x = X;
	y = Y;
	shapeChecker.setPosition(x, y);
}