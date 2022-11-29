#include <iostream>
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
	Coordinates actual, prev, board;
	Texture textChecker;
	CircleShape shapeChecker;
public:
	Checker(int bx, int by, bool color);
	bool getIsMove(){ return isMove; }
	int getActualX() { return actual.x; }
	int getActualY() { return actual.y; }
	int getPrevX() { return prev.x; }
	int getPrevY() { return prev.y; }
	void initialization();
	CircleShape getShape() { return shapeChecker; }
	void setPosition(int x, int y);
};
