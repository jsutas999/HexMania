#pragma once
#include <SFML/Graphics.hpp>
#include "HexGrid.h"
#include "Hex.h"
class Game
{
public:
	Game();
	~Game();
	void run();

private:
	bool isRunning;
	sf::RenderWindow* window;
	sf::View view;
	HexGrid grid;
	Hex* selected;
	int wall;
};

