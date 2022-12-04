#include <iostream>
#include "Checker.h"
#include <list>
#include <algorithm>

int Checker::countWhite = 12;
int Checker::countBlack = 12;
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
bool Checker::correctMotion(list<Checker*>& list, bool& turn, bool& multiple)
{
	//cout << this->getBoardX() << " " << this->getBoardY() << " " << this->getPrevBoardX() << " " << this->getPrevBoardY() << endl;
	//cout << abs(this->getBoardX() - this->getPrevBoardX()) << " " << abs(this->getBoardY() - this->getPrevBoardY()) << endl;
	if (this->outOfBounds()) //проверка выхода за границы
	{
		cout << "OutOfBounds" << endl;
		return false;
	}
	if (this->stepOnChecker(list)) //проверка шага на шашку
	{
		cout << "StepOnChecker" << endl;
		return false;
	}
	if (this->cutDownChecker(list))
	{
		cout << "CorrectCutDown" << endl;
		if (!this->possibilityStep(list, multiple)) //проверка следущего сруба 
			turn = !turn;
		return true;
	}
	else
	if (this->stepForward()) //проверка на шаг вперед
	{
		cout << "WrongStepForward" << endl;
		return false;
	}
	turn = !turn;
	return true;
}
bool Checker::outOfBounds()
{
	if (actual.x <= 0 || actual.x >= (2 * WIGTH_EDGE + 8 * LENGTH_TILE) || actual.y <= 0 || actual.y >= (2 * WIGTH_EDGE + 8 * LENGTH_TILE)) //проверка выхода за границы
		return true;
	else
		return false;
}
bool Checker::stepOnChecker(list<Checker*>& list)
{
	for (auto iter = list.begin(); iter != list.end(); iter++)
	{
		if (((*iter)->getPrevX() == this->getActualX()) && ((*iter)->getPrevY() == this->getActualY())) //покоординатная проверка заступа на шашку
			return true;
	}
	return false;
}
bool Checker::stepForward()
{
	if ((this->getColor() && !(abs(this->getBoardX() - this->getPrevBoardX()) == 1 && (this->getBoardY() - this->getPrevBoardY()) == -1))  //возможность ходить только вперед по диагоналям на 1
		|| (!this->getColor() && !(abs(this->getBoardX() - this->getPrevBoardX()) == 1 && (this->getBoardY() - this->getPrevBoardY()) == 1)))
		return true;
	else
		return false;
}
bool Checker::cutDownChecker(list<Checker*>& list)
{
	auto find = find_if(list.begin(), list.end(), [this](Checker* c)  //нахождение потанциально срубленной шашки
		{
			return c->getColor() != this->getColor() && c->getBoardX() == (this->getBoardX() + this->getPrevBoardX()) / 2 && c->getBoardY() == (this->getBoardY() + this->getPrevBoardY()) / 2;
		});
	if (find != list.end() && abs(this->getBoardX() - this->getPrevBoardX()) == 2 && abs(this->getBoardY() - this->getPrevBoardY()) == 2)   //удаление срубленной шашки 
	{
		if ((* find)->getColor())
			countBlack--;
		else
			countWhite--;
		delete* find;
		list.erase(find);
		return true;
	}
	return false;
}
bool Checker::possibilityStep(list<Checker*>& list, bool& multiple)
{
	for (auto iter = list.begin(); iter != list.end(); iter++) 
	{
		if (((*iter)->getColor() != this->getColor()) && (abs((*iter)->getBoardX() - this->getBoardX()) == 1) && (abs((*iter)->getBoardY() - this->getBoardY()) == 1))  //поиск шашки которую можно срубить 
		{
			auto find = find_if(list.begin(), list.end(), [this, iter](Checker* c) //поиск шашки которая может помешать срубу
				{
					return c->getBoardX() == this->getBoardX() - (this->getBoardX() - (*iter)->getBoardX()) * 2 && c->getBoardY() == this->getBoardY() - (this->getBoardY() - (*iter)->getBoardY()) * 2;
				});
			if (find == list.end() && (*iter)->getBoardX() != 0 && (*iter)->getBoardX() != 7 && (*iter)->getBoardY() != 0 && (*iter)->getBoardY() != 7) //если потанциально срубленная шашка находиться не по периметру + если не нашлась шашка мешающая срубу
			{
				cout << "PossibleNextStep" << endl;
				cout << (*iter)->getBoardX() << " " << (*iter)->getBoardY() << endl;
				multiple = true;     //множественный сруб возможно передвигать только последнюю шашку
				return true;
			}
		}
	}
	cout << "NotPossibleNextStep" << endl;
	multiple = false;
	return false;
}
