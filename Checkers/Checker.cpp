#include <iostream>
#include "Checker.h"

Checker::Checker(int bx, int by, bool color): actual(bx* LENGTH_TILE + WIGTH_EDGE, by* LENGTH_TILE + WIGTH_EDGE), 
											prev(bx* LENGTH_TILE + WIGTH_EDGE, by* LENGTH_TILE + WIGTH_EDGE),
											isMove(false), color(color) {};
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
void Checker::setCorrectPosition(int x, int y)
{
	actual.x = x;
	actual.y = y;
	prev.x = x;
	prev.y = y;
	shapeChecker.setPosition(x, y);
}
void Checker::switchIsMove()
{
	isMove = !isMove;
}
void Checker::draw(RenderWindow& window)
{
	window.draw(shapeChecker);
}
bool Checker::correctMotion()
{
	cout << this->getBoardX() << " " << this->getBoardY() << " " << this->getPrevBoardX() << " " << this->getPrevBoardY() << endl;
	cout << abs(this->getBoardX() - this->getPrevBoardX()) << " " << abs(this->getBoardY() - this->getPrevBoardY()) << endl;
	if (actual.x <= 0 || actual.x >= (2 * WIGTH_EDGE + 8 * LENGTH_TILE) || actual.y <= 0 || actual.y >= (2 * WIGTH_EDGE + 8 * LENGTH_TILE)) //проверка выхода за границы
		return false;
	if (!(abs(this->getBoardX() - this->getPrevBoardX()) == 1 && abs(this->getBoardY() - this->getPrevBoardY()) == 1)) //проверка хода по вертикале 
		return false;

	return true;
}
