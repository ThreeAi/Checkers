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
	Font font;
	font.loadFromFile("font/CyrilicOld.ttf");
	Text text("", font, 70);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	RenderWindow window(VideoMode(LENGTH_TILE * 8 + 2 * WIGTH_EDGE, LENGTH_TILE * 8 + 2 * WIGTH_EDGE), "Checkers");
	text.setPosition(window.getView().getCenter().x-230, window.getView().getCenter().y-75);
	list<Checker *> checkers;
	for (int i = 1; i <= 23; i = i + 2)										//расставляем шашки 
	{
		if((i / 8) % 2 == 1)
			checkers.push_back(new Checker(i % 8 - 1, i / 8, 0));
		else
			checkers.push_back(new Checker(i % 8, i / 8, 0));
	}
	for (int i = 40; i <= 63; i = i + 2)
	{
		if ((i / 8) % 2 == 1)
			checkers.push_back(new Checker(i % 8, i / 8, 1));
		else
			checkers.push_back(new Checker(i % 8 + 1, i / 8, 1));
	}
	for (list<Checker *>::iterator iter = checkers.begin(); iter != checkers.end(); iter++)		//инициализируем 
	{
		(* iter)->initialization();
	}
	Board d = Board();
	d.initialization();
	int dX = 0, dY = 0;
	bool turn = false;
	bool multiple = false;
	while (window.isOpen())
	{
		Vector2i pixelPos = Mouse::getPosition(window);
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left)//если нажата клавиша мыши
				if (!multiple)
				{
					for (list<Checker*>::iterator iter = checkers.begin(); iter != checkers.end(); iter++)
					{
						int y = (*iter)->getActualY() + 35;
						int x = (*iter)->getActualX() + 35;
						if (sqrt((pixelPos.y - y) * (pixelPos.y - y) + (pixelPos.x - x) * (pixelPos.x - x)) <= CHECKERS_RADIUS && turn == (*iter)->getColor())//и при этом координата курсора попадает в спрайт
						{
							checkers.splice(checkers.end(), checkers, iter); //переместим активную шашку в конец
							std::cout << "isClicked!\n";//выводим в консоль сообщение об этом
							dX = pixelPos.x - (*iter)->getActualX();//делаем разность между позицией курсора и спрайта.для корректировки нажатия
							dY = pixelPos.y - (*iter)->getActualY();//тоже самое по игреку
							(*iter)->switchIsMove();//можем двигать спрайт							
						}
					}
				}
				else
				{
					auto iter = checkers.end();
					--iter;
					int y = (*iter)->getActualY() + 35;
					int x = (*iter)->getActualX() + 35;
					if (sqrt((pixelPos.y - y) * (pixelPos.y - y) + (pixelPos.x - x) * (pixelPos.x - x)) <= CHECKERS_RADIUS && turn == (*iter)->getColor())//и при этом координата курсора попадает в спрайт
					{
						//checkers.splice(checkers.end(), checkers, iter); //переместим активную шашку в конец
						std::cout << "isClicked!\n";//выводим в консоль сообщение об этом
						dX = pixelPos.x - (*iter)->getActualX();//делаем разность между позицией курсора и спрайта.для корректировки нажатия
						dY = pixelPos.y - (*iter)->getActualY();//тоже самое по игреку
						(*iter)->switchIsMove();//можем двигать спрайт							
					}
				}
			auto iter = checkers.end();
			--iter; 
			if ((*iter)->getIsMove()) //если можем двигать
			{
				(*iter)->setPosition(pixelPos.x - dX, pixelPos.y - dY);
			}
			if ((event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left))//если отпустили клавишу
			{
				if ((*iter)->getIsMove())
				{
					//cout << ((pixelPos.x - WIGTH_EDGE) / LENGTH_TILE) * LENGTH_TILE + WIGTH_EDGE << " " << ((pixelPos.y - WIGTH_EDGE) / LENGTH_TILE) * LENGTH_TILE + WIGTH_EDGE << endl;
					(*iter)->setPosition(((pixelPos.x - WIGTH_EDGE) / LENGTH_TILE) * LENGTH_TILE + WIGTH_EDGE, ((pixelPos.y - WIGTH_EDGE) / LENGTH_TILE) * LENGTH_TILE + WIGTH_EDGE); //присвоение фактических координат с учетом магнита 
					Queen* temp = dynamic_cast<Queen*>(*iter); //если дамка 
					if (((temp == NULL) && (*iter)->correctMotion(checkers, turn, multiple)) || (temp != NULL && temp->correctMotion(checkers, turn, multiple))) //если ход правильный 
					{
						(*iter)->switchIsMove(); //то не можем двигать спрайт
						(*iter)->setCorrectPosition((*iter)->getActualX(), (*iter)->getActualY()); //ставим на фактические координаты 
						cout << "White " << Checker::countWhite << endl;
						cout << "Black " << Checker::countBlack << endl;
						if ((!(*iter)->getColor() && (*iter)->getBoardY() == 7) || ((*iter)->getColor() && (*iter)->getBoardY() == 0)) //проверка на стоановление дамки 
						{
							Queen *temp = new Queen((*iter)->getBoardX(), (*iter)->getBoardY(), (*iter)->getColor());
							temp->initialization();
							checkers.push_front(temp);
							delete *iter;
							checkers.erase(iter);								
						}
					}
					else  //если ход не правильный ставим на предыдущее место 
					{
						(*iter)->switchIsMove(); //то не можем двигать спрайт
						(*iter)->setCorrectPosition((*iter)->getPrevX(), (*iter)->getPrevY());
					}
				}
			}

		}
		window.clear();
		d.draw(window);
		for (auto iter : checkers)
		{
			(*iter).draw(window);
		}
		if (Checker::countBlack == 0)
		{
			text.setString("Победа Белых");
			text.setFillColor(Color(255, 255, 255));
			window.draw(text);
		}
		if (Checker::countWhite == 0)
		{
			text.setString("Победа Черных");
			text.setFillColor(Color(0, 0, 0));
			window.draw(text);
		}
		window.display();
	}

	return 0;
}
