#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>
#include "Params.h"
using namespace std;
using namespace sf;

class Checker
{
private:
	struct Coordinates
	{
		int x;
		int y;
		Coordinates(int x, int y) : x(x), y(y) {};
	};
	bool color;
	bool isMove;
	Coordinates actual, prev;
	Texture textChecker;
	CircleShape shapeChecker;
public:
	Checker(int bx, int by, bool color);
	bool getIsMove(){ return isMove; }
	bool getColor() { return color; }
	int getActualX() { return actual.x; }
	int getActualY() { return actual.y; }
	int getPrevX() { return prev.x; }
	int getPrevY() { return prev.y; }
	void initialization();
	CircleShape getShape() { return shapeChecker; }
	void setPosition(int x, int y);
	void setCorrectPosition(int x, int y);
	void switchIsMove();
	void draw(RenderWindow& window);
	bool correctMotion(list<Checker>& list);
	int getBoardX() { return (actual.x - WIGTH_EDGE) / LENGTH_TILE; }
	int getBoardY() { return (actual.y - WIGTH_EDGE) / LENGTH_TILE; }
	int getPrevBoardX() { return (prev.x - WIGTH_EDGE) / LENGTH_TILE; }
	int getPrevBoardY() { return (prev.y - WIGTH_EDGE) / LENGTH_TILE; }
};
