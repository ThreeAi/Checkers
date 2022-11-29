#include <iostream>
#include "Checker.h"

Checker::Checker(int bx, int by, bool color): actual(bx* LENGTH_TILE + WIGTH_EDGE, by* LENGTH_TILE + WIGTH_EDGE), 
											prev(bx* LENGTH_TILE + WIGTH_EDGE, by* LENGTH_TILE + WIGTH_EDGE),
											board(bx, by), isMove(false), color(color) {};
void Checker::initialization()
{
	textChecker.loadFromFile("images/checker.png");
	shapeChecker = CircleShape(CHECKERS_RADIUS);
	shapeChecker.setTexture(&textChecker);
	if(!color)
		shapeChecker.setTextureRect(IntRect(0, 0, 112, 112));
	else
		shapeChecker.setTextureRect(IntRect(226, 0, 112, 112));
	shapeChecker.setPosition(actual.x, actual.y);
}
void Checker::setPosition(int x, int y)
{
	actual.x = x;
	actual.y = y;
	shapeChecker.setPosition(x, y);
}