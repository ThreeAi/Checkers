#include "Board.h"
#include <SFML/Graphics.hpp>

using namespace sf;

void Board::initialization()
{
	textboard.loadFromFile("images/board.png");
	spriteboard.setTexture(textboard);
	background = RectangleShape(Vector2f(LENGTH_TILE * WIGTH_BOARD + 2 * WIGTH_EDGE, LENGTH_TILE * HEIGHT_BOARD + 2 * WIGTH_EDGE));
	background.setFillColor(Color(189, 183, 107));
}
void Board::draw(RenderWindow& window)
{
	background.setPosition(0, 0);
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
}