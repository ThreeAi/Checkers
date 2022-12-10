#include "Checker.h"
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
bool Checker::correctMotion(list<Checker*>& list, bool& turn, bool& multiple, int posx, int posy)
{
	if (this->outOfBounds(posx, posy)) //проверка выхода за границы
	{
		return false;
	}
	if (this->stepOnChecker(list)) //проверка шага на шашку
	{
		return false;
	}
	if (this->cutDownChecker(list))
	{
		if (!this->possibilityStep(list, multiple)) //проверка следущего сруба 
			turn = !turn;
		return true;
	}
	else
	if (this->stepForward()) //проверка на шаг вперед
	{
		return false;
	}
	turn = !turn;
	return true;
}
bool Checker::outOfBounds(int posx, int posy)
{
	if (posx  <= 8  || posx >= (WIGTH_EDGE + 8 * LENGTH_TILE)  ||
		posy  <= 8  || posy >= (WIGTH_EDGE + 8 * LENGTH_TILE)) //проверка выхода за границы
		return true;
	else
	{
		this->setPosition(((posx - WIGTH_EDGE) / LENGTH_TILE) * LENGTH_TILE + WIGTH_EDGE, 
						  ((posy - WIGTH_EDGE) / LENGTH_TILE) * LENGTH_TILE + WIGTH_EDGE);
		return false;
	}
}
bool Checker::stepOnChecker(list<Checker*>& list)
{
	for (auto iter = list.begin(); iter != list.end(); iter++)
	{
		if (((*iter)->getPrevX() == this->getActualX()) && 
			((*iter)->getPrevY() == this->getActualY())) //покоординатная проверка заступа на шашку
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
			return  c->getColor() != this->getColor() 
				 && c->getBoardX() == (this->getBoardX() + this->getPrevBoardX()) / 2 
				 && c->getBoardY() == (this->getBoardY() + this->getPrevBoardY()) / 2;
		});
	if (find != list.end() && abs(this->getBoardX() - this->getPrevBoardX()) == 2 
		                   && abs(this->getBoardY() - this->getPrevBoardY()) == 2)   //удаление срубленной шашки 
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
		if (((*iter)->getColor() != this->getColor()) 
			&& (abs((*iter)->getBoardX() - this->getBoardX()) == 1) 
            && (abs((*iter)->getBoardY() - this->getBoardY()) == 1))  //поиск шашки которую можно срубить 
		{
			auto find = find_if(list.begin(), list.end(), [this, iter](Checker* c) //поиск шашки которая может помешать срубу
				{
					return c->getBoardX() == this->getBoardX() - (this->getBoardX() - (*iter)->getBoardX()) * 2 
						&& c->getBoardY() == this->getBoardY() - (this->getBoardY() - (*iter)->getBoardY()) * 2;
				});
			if (find == list.end() && (*iter)->getBoardX() != 0 && (*iter)->getBoardX() != 7 
								   && (*iter)->getBoardY() != 0 && (*iter)->getBoardY() != 7) //если потанциально срубленная шашка находиться не по периметру + если не нашлась шашка мешающая срубу
			{
				multiple = true;     //множественный сруб возможно передвигать только последнюю шашку
				return true;
			}
		}
	}
	multiple = false;
	return false;
}
