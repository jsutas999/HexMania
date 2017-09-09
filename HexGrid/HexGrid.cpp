#include "stdafx.h"
#include "HexGrid.h"
#define HEX_W 100.0
#define HEX_H 100.0

HexGrid::HexGrid(int width, int height)
{
	this->width = width;
	this->height = height;

	sf::Font* font = new sf::Font();

	if (!font->loadFromFile("arial.ttf"))
	{
		std::cout << "nilaudina :(";
		return;
	}

	grid = new Hex*[this->height];

	for (int h = 0; h < this->height; h++)
	{
		grid[h] = new Hex[this->width];

		for (int w = 0; w < this->width; w++)
		{
			float moving = static_cast<float> ( (w % 2)*HEX_W*0.5f ); 
			float x = static_cast<float>(w*0.75f*HEX_W);
			float y = static_cast<float>(h*HEX_H + moving);
			grid[h][w].setCoordinates(w, h);
			grid[h][w].setPosition(x, y);
			grid[h][w].text.setFont(*font);
			grid[h][w].text.setCharacterSize(24);
			grid[h][w].text.setFillColor(sf::Color(200,200,200));
			grid[h][w].text.setPosition(0, 0);
			grid[h][w].st = (std::to_string(w) + ";" + std::to_string(h));
			grid[h][w].text.setString(grid[h][w].st);
		}
	}
}

HexGrid::HexGrid()
{
}

HexGrid::~HexGrid()
{
	for (int i = height - 1; height <= 0; i--)
	{
		delete[] grid[i];
	}
}

int HexGrid::getWidth()
{
	return width;
}

int HexGrid::getHeight()
{
	return height;
}

void HexGrid::center() {
	setPosition(-width*0.75*HEX_W/2,-HEX_W*height/2);
}

Hex* HexGrid::m_getByCoord(int x, int y)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
	{
		return nullptr;
	}
	return &grid[y][x];
}

sf::Vector2i HexGrid::getNearestTileCoordinates(sf::Vector2f localSpacePosition)
{
	return m_getHexTileByLocalSpace(localSpacePosition);
}
Hex* HexGrid::getNearestTile(sf::Vector2f localSpacePosition)
{
	return getTileByCoordinate(m_getHexTileByLocalSpace(localSpacePosition) );
}

Hex* HexGrid::getTileByCoordinate(sf::Vector2i coord)
{
	return m_getByCoord(coord.x, coord.y);
}

Hex* HexGrid::getTileByCoordinate(int x, int y)
{
	return m_getByCoord(x, y);
}

Hex * HexGrid::getNeighbor(Hex::WALL direction, Hex * root)
{
	sf::Vector2i coord = root->getCoordinates();
	if ( direction == Hex::BOTTOM)
	{
		return getTileByCoordinate(coord.x,coord.y+1);
	}
	else if (direction == Hex::TOP)
	{
		return getTileByCoordinate(coord.x, coord.y - 1);
	}
	else if (direction == Hex::UPPER_RIGHT)
	{
		if (coord.x % 2 == 1)
		{
			return getTileByCoordinate(coord.x + 1, coord.y);
		}
		else
		{
			return getTileByCoordinate(coord.x + 1, coord.y-1);
		}
		
	}
	else if (direction == Hex::LOWER_RIGHT)
	{
		if (coord.x % 2 == 1)
		{
			return getTileByCoordinate(coord.x + 1, coord.y + 1);
		}
		else
		{
			return getTileByCoordinate(coord.x + 1, coord.y);
		}
	}
	else if (direction == Hex::UPPER_LEFT)
	{
		if (coord.x % 2 == 1)
		{
			return getTileByCoordinate(coord.x - 1, coord.y);
		}
		else
		{
			return getTileByCoordinate(coord.x - 1, coord.y-1);
		}
	}
	else if (direction == Hex::LOWER_LEFT)
	{
		if (coord.x % 2 == 1)
		{
			return getTileByCoordinate(coord.x - 1, coord.y + 1);
		}
		else
		{
			return getTileByCoordinate(coord.x - 1, coord.y);
		}
	}
	return nullptr;
}

sf::Vector2i HexGrid::m_getHexTileByLocalSpace(sf::Vector2f localSpacePosition)
{
	int x = static_cast<int>((localSpacePosition.x) / (HEX_W*0.75)) ;
	int y = static_cast<int> ((localSpacePosition.y + ((x + 1) % 2)*HEX_W) / (HEX_W));

	std::cout << x << "!" << y;

	Hex* hex = m_getByCoord(x, y);
	if (hex == nullptr) {
		hex = m_getByCoord(x, height - 1);
		if (hex == nullptr)
		{
			return sf::Vector2i(-1, -1);
		}
	}

	float dist = 16 * HEX_W*HEX_H;

	int off = 2;
	int xma = x + off, xmi = x - off;
	int yma = y + off, ymi = y - off;

	xma = std::min(xma, width);
	xmi = std::max(xmi, 0);
	yma = std::min(yma, height);
	ymi = std::max(ymi, 0);

	for (int w = xmi; w < xma; w++)
	{
		for (int h = ymi; h < yma; h++)
		{

			float d = pow(grid[h][w].getPosition().x - localSpacePosition.x, 2) + pow(grid[h][w].getPosition().y - localSpacePosition.y, 2);
			if (d < dist)
			{
				dist = d;
				hex = &grid[h][w];
			}
		}
	}
	return hex->getCoordinates();
}

float HexGrid::getAngle(sf::Vector2f point, Hex* hex)
{
	sf::Vector2f pos = hex->getPosition();
	return atan2(point.y - pos.y, point.x - pos.x);
}

Hex::WALL HexGrid::getWall(float angle)
{

	if (angle > 0)
	{
		if (angle < 60)
			return Hex::LOWER_RIGHT;
		else if (angle < 120)
			return Hex::BOTTOM;
		else
			return Hex::LOWER_LEFT;
	}
	else
	{
		angle *= -1;
		if (angle < 60)
			return Hex::UPPER_RIGHT;
		if (angle < 120)
			return Hex::TOP;
		else return Hex::UPPER_LEFT;

	}
}


void HexGrid::setWall(Hex::WALL wall, Hex* root,bool value)
{
	if (root == nullptr)
	{
		throw std::invalid_argument("ROOR -> NULL POINTER");
		return;
	}
	root->setWall(wall,value);
	Hex* neighbor = getNeighbor(wall, root);

	if (neighbor != nullptr)
	{
		neighbor->setWall(Hex::invertWall(wall), value);
	}
}


void HexGrid::toggleWall(Hex::WALL wall, Hex* root)
{
	setWall(wall, root, !root->getWall(wall));
}

void HexGrid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			target.draw(grid[h][w], states);
		}
	}
}
