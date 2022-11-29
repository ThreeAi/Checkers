#include <SFML\Graphics.hpp>
#include "Params.h"
using namespace sf;


//String TileBoard[LENGTH_TILE] = {
//	"01010101",
//	"10101010",
//	"01010101",
//	"10101010",
//	"01010101",
//	"10101010",
//	"01010101",
//	"10101010",
//};
class Board
{
private:
	String TileBoard[LENGTH_TILE] = {
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