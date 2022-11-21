#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Checker
{
private:
	bool isMove;
	int x, y, prevX, prevY;
	static const int CHECKERS_RADIUS = 35;
	Texture textChecker;
	CircleShape shapeChecker;
public:
	Checker(int x, int y);
	bool getIsMove(){ return isMove; }
	int getX() { return x; }
	int getY() { return y; }
	int getPrevX() { return prevX; }
	int getPrevY() { return prevY; }
	void Initialization();
	CircleShape getShape() { return shapeChecker; }
	void setPosition(int x, int y);
};
