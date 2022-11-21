#include <iostream>
#include <SFML/Graphics.hpp>
#include "Interface.h"

using namespace sf;
int main()
{
	RenderWindow window(VideoMode(LENGTH_TILE * 8 + 2 * WIGTH_EDGE, LENGTH_TILE * 8 + 2 * WIGTH_EDGE), "Checkers");
	Texture textboard, textchecker;
	textboard.loadFromFile("images/board.png");
	textchecker.loadFromFile("images/checker.png");
	Sprite spriteboard;
	spriteboard.setTexture(textboard);
	CircleShape shapeChecker(35);
	shapeChecker.setTexture(&textchecker);
	shapeChecker.setTextureRect(IntRect(0, 0, 112, 112));
	shapeChecker.setPosition(9, 9);
	RectangleShape background(Vector2f(LENGTH_TILE * 8 + 2 * WIGTH_EDGE, LENGTH_TILE * 8 + 2 * WIGTH_EDGE));
	background.setFillColor(Color(189, 183, 107));
	background.setPosition(0, 0);
	bool isMove = false;
	float dX = 0, dY = 0;

	while (window.isOpen())
	{
		Vector2i pixelPos = Mouse::getPosition(window);
		Event event;
		//std::cout << pixelPos.x << "\n";
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
				if (event.key.code == Mouse::Left)//а именно левая
				{
					float y = shapeChecker.getGlobalBounds().top + 35;
					float x = shapeChecker.getGlobalBounds().left + 35;
					if (sqrt((pixelPos.y-y)* (pixelPos.y - y) + (pixelPos.x - x)* (pixelPos.x - x)) <= 35)//и при этом координата курсора попадает в спрайт
					{
						std::cout << "isClicked!\n";//выводим в консоль сообщение об этом
						dX = pixelPos.x - shapeChecker.getPosition().x;//делаем разность между позицией курсора и спрайта.для корректировки нажатия
						dY = pixelPos.y - shapeChecker.getPosition().y;//тоже самое по игреку
						isMove = true;//можем двигать спрайт							
					}
				}
			if (event.type == Event::MouseButtonReleased)//если отпустили клавишу
				if (event.key.code == Mouse::Left) //а именно левую
					isMove = false; //то не можем двигать спрайт
			if (isMove) {//если можем двигать
				//p.setColor(Color::Green);//красим спрайт в зеленый 
				shapeChecker.setPosition(pixelPos.x - dX, pixelPos.y - dY);
			}
		}
		window.clear();
		window.draw(background);
		for (int i = 0; i < HEIGHT_BOARD; i++)
			for (int j = 0; j < WIGTH_BOARD; j++)
			{
				if (TileBoard[i][j] == '1')
				{
					spriteboard.setTextureRect(IntRect(0, 0, 71, 71));
					spriteboard.setPosition(LENGTH_TILE * i + WIGTH_EDGE, LENGTH_TILE * j + WIGTH_EDGE);
				}
				if (TileBoard[i][j] == '0')
				{
					spriteboard.setTextureRect(IntRect(72, 0, 71, 71));
					spriteboard.setPosition(LENGTH_TILE * i + WIGTH_EDGE, LENGTH_TILE * j + WIGTH_EDGE);
				}
				window.draw(spriteboard);
			}
		window.draw(shapeChecker);
		window.display();
	}

	return 0;
}
