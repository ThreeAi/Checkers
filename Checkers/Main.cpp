#include <iostream>
#include <list>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Checker.h"

using namespace sf;
using namespace std; 
int main()
{
	RenderWindow window(VideoMode(LENGTH_TILE * 8 + 2 * WIGTH_EDGE, LENGTH_TILE * 8 + 2 * WIGTH_EDGE), "Checkers");
	list<Checker> checkers;
	for (int i = 1; i <= 23; i = i + 2)										//расставляем шашки 
	{
		if((i / 8) % 2 == 1)
			checkers.push_back(Checker(i % 8 - 1, i / 8, 0));
		else
			checkers.push_back(Checker(i % 8, i / 8, 0));
	}
	for (int i = 40; i <= 63; i = i + 2)
	{
		if ((i / 8) % 2 == 1)
			checkers.push_back(Checker(i % 8, i / 8, 1));
		else
			checkers.push_back(Checker(i % 8 + 1, i / 8, 1));
	}
	for (list<Checker>::iterator iter = checkers.begin(); iter != checkers.end(); iter++)		//инициализируем 
	{
		iter->initialization();
	}
	Board d = Board();
	d.initialization();
	int dX = 0, dY = 0;

	while (window.isOpen())
	{
		Vector2i pixelPos = Mouse::getPosition(window);
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left)//если нажата клавиша мыши		
				for (list<Checker>::iterator iter = checkers.begin(); iter != checkers.end(); iter++)
				{
					int y = iter->getActualY() + 35;
					int x = iter->getActualX() + 35;
					if (sqrt((pixelPos.y - y) * (pixelPos.y - y) + (pixelPos.x - x) * (pixelPos.x - x)) <= CHECKERS_RADIUS)//и при этом координата курсора попадает в спрайт
					{
						std::cout << "isClicked!\n";//выводим в консоль сообщение об этом
						dX = pixelPos.x - iter->getActualX();//делаем разность между позицией курсора и спрайта.для корректировки нажатия
						dY = pixelPos.y - iter->getActualY();//тоже самое по игреку
						iter->switchIsMove();//можем двигать спрайт							
					}
				}
			if ((event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left))//если отпустили клавишу
				for (list<Checker>::iterator iter = checkers.begin(); iter != checkers.end(); iter++)
				{
					if (iter->getIsMove())
					{
						iter->setPosition(((pixelPos.x - WIGTH_EDGE) / LENGTH_TILE)* LENGTH_TILE + WIGTH_EDGE, ((pixelPos.y - WIGTH_EDGE) / LENGTH_TILE)* LENGTH_TILE + WIGTH_EDGE);
						if (iter->correctMotion(checkers))
						{
							iter->switchIsMove(); //то не можем двигать спрайт
							iter->setCorrectPosition(iter->getActualX(), iter->getActualY());
						}
						else
						{
							iter->switchIsMove(); //то не можем двигать спрайт
							iter->setCorrectPosition(iter->getPrevX(), iter->getPrevY());
						}
					}
				}
			for (list<Checker>::iterator iter = checkers.begin(); iter != checkers.end(); iter++)
			{
				if (iter->getIsMove()) {//если можем двигать
					iter->setPosition(pixelPos.x - dX, pixelPos.y - dY);
				}
			}
		}
		window.clear();
		d.draw(window);
		//cout << checkers.front().getActualX() << " " << checkers.front().getActualY() << checkers.front().getColor() << endl;
		checkers.front().draw(window);
		window.draw(checkers.front().getShape());
		for (auto iter : checkers)
		{
			iter.draw(window);
		}
		window.display();
	}

	return 0;
}
