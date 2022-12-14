#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>
#include "Params.h"

using namespace std;
using namespace sf;

class Checker
{
protected:
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
	static int countWhite;
	static int countBlack;
	Checker(int bx, int by, bool color);
	bool getIsMove(){ return isMove; }
	bool getColor() { return color; }
	int getActualX() { return actual.x; }
	int getActualY() { return actual.y; }
	int getPrevX() { return prev.x; }
	int getPrevY() { return prev.y; }
	virtual void initialization();
	CircleShape getShape() { return shapeChecker; }
	void setPosition(int x, int y);
	void setCorrectPosition(int x, int y);
	void switchIsMove();
	void draw(RenderWindow& window);
	virtual bool correctMotion(list<Checker*>& list, bool& turn, bool& multiple, int posx, int posy);
	int getBoardX() { return (actual.x - WIGTH_EDGE) / LENGTH_TILE; }
	int getBoardY() { return (actual.y - WIGTH_EDGE) / LENGTH_TILE; }
	int getPrevBoardX() { return (prev.x - WIGTH_EDGE) / LENGTH_TILE; }
	int getPrevBoardY() { return (prev.y - WIGTH_EDGE) / LENGTH_TILE; }
	bool outOfBounds(int posx, int posy);
	bool stepOnChecker(list<Checker*>& list);
	bool stepForward();
	virtual bool cutDownChecker(list<Checker*>& list);
	virtual bool possibilityStep(list<Checker*>& list, bool& multiple);
};
class Queen : public Checker
{
public:
	Queen(int bx, int by, bool color) : Checker(bx, by, color) {};
	void initialization();
	bool stepForward(list<Checker*>& list);
	bool cutDownChecker(list<Checker*>& list);
	bool correctMotion(list<Checker*>& list, bool& turn, bool& multiple, int posx, int posy);
	bool possibilityStep(list<Checker*>& list, bool& multiple);
};