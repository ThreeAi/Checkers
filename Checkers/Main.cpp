#include <iostream>
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Checker.h"

using namespace sf;
using namespace std; 
int main()
{
	RenderWindow window(VideoMode(LENGTH_TILE * 8 + 2 * WIGTH_EDGE, LENGTH_TILE * 8 + 2 * WIGTH_EDGE), "Checkers");
	//Texture textboard;
	//textboard.loadFromFile("images/board.png");
	//textchecker.loadFromFile("images/checker.png");
	//Sprite spriteboard;
	//spriteboard.setTexture(textboard);
	//CircleShape shapeChecker(CHECKERS_RADIUS);
	//shapeChecker.setTexture(&textchecker);
	//shapeChecker.setTextureRect(IntRect(0, 0, 112, 112));
	//shapeChecker.setPosition(9, 9);
	Checker c = Checker(0, 0, 0);
	Checker cb = Checker(0, 1, 10);
	c.initialization();
	cb.initialization();
	cout << cb.getActualX() << " " << cb.getActualY() << endl;
	Board d = Board();
	d.initialization();
	//RectangleShape background(Vector2f(LENGTH_TILE * 8 + 2 * WIGTH_EDGE, LENGTH_TILE * 8 + 2 * WIGTH_EDGE));
	//background.setFillColor(Color(189, 183, 107));
	//background.setPosition(0, 0);
	bool isMove = false;
	int dX = 0, dY = 0;

	while (window.isOpen())
	{
		Vector2i pixelPos = Mouse::getPosition(window);
		Event event;
		//std::cout << pixelPos.x << " " << pixelPos.y << endl;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
				if (event.key.code == Mouse::Left)//а именно левая
				{
					int y = c.getActualY() + 35;
					int x = c.getActualX() + 35;
					//cout << c.getShape().getGlobalBounds().top << endl;
					//cout << c.getShape().getGlobalBounds().left << endl;
					//cout << c.getY() << endl;
					//cout << c.getX() << endl;
					if (sqrt((pixelPos.y-y)* (pixelPos.y - y) + (pixelPos.x - x)* (pixelPos.x - x)) <= CHECKERS_RADIUS)//и при этом координата курсора попадает в спрайт
					{
						std::cout << "isClicked!\n";//выводим в консоль сообщение об этом
						dX = pixelPos.x - c.getActualX();//делаем разность между позицией курсора и спрайта.для корректировки нажатия
						dY = pixelPos.y - c.getActualY();//тоже самое по игреку
						isMove = true;//можем двигать спрайт							
					}
				}
			if ((event.type == Event::MouseButtonReleased) && isMove)//если отпустили клавишу
				if (event.key.code == Mouse::Left)
				{ //а именно левую
					//shapeChecker.setPosition((pixelPos.x - WIGTH_EDGE) / LENGTH_TILE, (pixelPos.x - WIGTH_EDGE) / LENGTH_TILE);
					isMove = false; //то не можем двигать спрайт
					c.setPosition(((pixelPos.x - WIGTH_EDGE) / LENGTH_TILE) * LENGTH_TILE + WIGTH_EDGE, ((pixelPos.y - WIGTH_EDGE) / LENGTH_TILE) * LENGTH_TILE + WIGTH_EDGE);
				}
			if (isMove) {//если можем двигать
				c.setPosition(pixelPos.x - dX, pixelPos.y - dY);
			}
		}
		window.clear();
		d.draw(window);
		//window.draw(background);
		//for (int i = 0; i < HEIGHT_BOARD; i++)
		//	for (int j = 0; j < WIGTH_BOARD; j++)
		//	{
		//		if (TileBoard[i][j] == '1')
		//		{
		//			spriteboard.setTextureRect(IntRect(0, 0, 71, 71));
		//			spriteboard.setPosition(LENGTH_TILE * i + WIGTH_EDGE, LENGTH_TILE * j + WIGTH_EDGE);
		//		}
		//		if (TileBoard[i][j] == '0')
		//		{
		//			spriteboard.setTextureRect(IntRect(72, 0, 71, 71));
		//			spriteboard.setPosition(LENGTH_TILE * i + WIGTH_EDGE, LENGTH_TILE * j + WIGTH_EDGE);
		//		}
		//		window.draw(spriteboard);
		//	}
		window.draw(cb.getShape());
		window.draw(c.getShape());
		window.display();
	}

	return 0;
}
