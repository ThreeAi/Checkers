#include <iostream>
#include "Checker.h"
#include <list>
#include <algorithm>

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
bool Queen::stepForward(list<Checker*>& list)
{
	if (!(abs(this->getBoardX() - this->getPrevBoardX()) == abs(this->getBoardY() - this->getPrevBoardY())))
		return true;
	auto find = find_if(list.begin(), list.end(), [this](Checker* c)
		{
			return c->getColor() == this->getColor() && 
				((c->getBoardX() - this->getPrevBoardX()) * (this->getBoardY() - this->getPrevBoardY()) - 
				((c->getBoardY() - this->getPrevBoardY()) * (this->getBoardX() - this->getPrevBoardX()))) == 0 &&
				((c->getBoardX() > this->getPrevBoardX() && c->getBoardX() < this->getBoardX()) || 
				 (c->getBoardX() < this->getPrevBoardX() && c->getBoardX() > this->getBoardX()));
		});
	if ( find != list.end())
	{
		return true;
	}
	return false;
}
bool Queen::cutDownChecker(list<Checker*>& list)
{
	if (!(abs(this->getBoardX() - this->getPrevBoardX()) == abs(this->getBoardY() - this->getPrevBoardY())))
		return true;
	auto find = find_if(list.begin(), list.end(), [this](Checker* c)
		{
			return c->getColor() != this->getColor() && 
				((c->getBoardX() - this->getPrevBoardX()) * (this->getBoardY() - this->getPrevBoardY()) - 
				((c->getBoardY() - this->getPrevBoardY()) * (this->getBoardX() - this->getPrevBoardX()))) == 0 &&
				((c->getBoardX() > this->getPrevBoardX() && c->getBoardX() < this->getBoardX()) || 
				 (c->getBoardX() < this->getPrevBoardX() && c->getBoardX() > this->getBoardX()));
		});
	if (  find != list.end())
	{
		if ((*find)->getColor())
			countBlack--;
		else
			countWhite--;
		delete* find;
		list.erase(find);
		return true;
	}
	return false;
}
bool Queen::correctMotion(list<Checker*>& list, bool& turn, bool& multiple, int posx, int posy)
{
	if (this->outOfBounds(posx, posy)) //проверка выхода за границы
	{
		cout << "QueenOutOfBounds" << endl;
		return false;
	}
	if (this->stepOnChecker(list)) //проверка шага на шашку
	{
		cout << "QueenStepOnChecker" << endl;
		return false;
	}
	if (this->cutDownChecker(list))
	{
		cout << "QueenCorrectCutDown" << endl;
		if (!this->possibilityStep(list, multiple)) //проверка следущего сруба 
			turn = !turn;
		return true;
	}
	else
		if (this->stepForward(list)) //проверка на шаг вперед
		{
			cout << "QueenWrongStep" << endl;
			return false;
		}
	turn = !turn;
	return true;
}
bool Queen::possibilityStep(list<Checker*>& list, bool& multiple)
{
	for (auto iter = list.begin(); iter != list.end(); iter++)
	{
		if (((*iter)->getColor() != this->getColor()) && 
			(abs((*iter)->getBoardX() - this->getBoardX()) == abs((*iter)->getBoardY() - this->getBoardY())))  //поиск шашки которую можно срубить 
		{
			auto find = find_if(list.begin(), list.end(), [this, iter](Checker* c) //поиск шашки которая может помешать срубу
				{
					return c->getBoardX() == this->getBoardX() - ((this->getBoardX() - (*iter)->getBoardX())) 
						- (this->getBoardX() - (*iter)->getBoardX()) / abs((this->getBoardX() - (*iter)->getBoardX())) 
						&& c->getBoardY() == this->getBoardY() - ((this->getBoardY() - (*iter)->getBoardY())) 
						- (this->getBoardY() - (*iter)->getBoardY()) / abs((this->getBoardY() - (*iter)->getBoardY()));
				});
			if (find == list.end() && (*iter)->getBoardX() != 0 && (*iter)->getBoardX() != 7 
								   && (*iter)->getBoardY() != 0 && (*iter)->getBoardY() != 7) //если потанциально срубленная шашка находиться не по периметру + если не нашлась шашка мешающая срубу
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