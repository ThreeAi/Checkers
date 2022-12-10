#include <SFML\Graphics.hpp>
#include "Params.h"
using namespace sf;

class Board
{
private:
	String TileBoard[HEIGHT_BOARD] = {
	"01010101",
	"10101010",
	"01010101",
	"10101010",
	"01010101",
	"10101010",
	"01010101",
	"10101010",
	};
	Texture textboard;
	Sprite spriteboard;
	RectangleShape background;
public:
	void initialization();
	void draw(RenderWindow& window);
};