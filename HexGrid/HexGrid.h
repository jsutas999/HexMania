#pragma once
#include <SFML/Graphics.hpp>
#include "Hex.h"
#include <iostream>
class HexGrid : public sf::Transformable, public sf::Drawable {
public:

	HexGrid(int width, int height);
	HexGrid();
	~HexGrid();
	int getWidth();
	int getHeight();
	void center();
	sf::Vector2i getNearestTileCoordinates(sf::Vector2f localSpacePosition);
	Hex * getNearestTile(sf::Vector2f localSpacePosition);
	Hex * getTileByCoordinate(sf::Vector2i coord);
	Hex * getTileByCoordinate(int x, int y);
	Hex * getNeighbor(Hex::WALL direction, Hex* root);
	float getAngle(sf::Vector2f point, Hex * hex);
	Hex::WALL getWall(float angle);
	void toggleWall(Hex::WALL wall, Hex * root);
	void setWall(Hex::WALL wall, Hex* root, bool value);

private:
	virtual void HexGrid::draw(sf::RenderTarget& target, sf::RenderStates states) const;
	Hex * m_getByCoord(int x, int y);
	sf::Vector2i m_getHexTileByLocalSpace(sf::Vector2f localSpacePosition);
	int width, height;
	Hex** grid;
	sf::Font font;
	
};
