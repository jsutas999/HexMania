#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Hex.h"
#include <iostream>

#define HEX_W 100.0
#define HEX_H 100.0

int mod(int a, int b)
{
	return (b + (a%b)) % b;
}


Hex::Hex()
{
	text = sf::Text();
	m_vertices.setPrimitiveType(sf::TriangleFan);
	m_vertices.resize(6);
	m_vertices[0] = sf::Vector2f(HEX_W / 2, 0);
	m_vertices[1] = sf::Vector2f(HEX_W / 4, -HEX_H / 2);
	m_vertices[2] = sf::Vector2f(-HEX_W / 4, -HEX_H / 2);
	m_vertices[3] = sf::Vector2f(-HEX_W / 2, 0);
	m_vertices[4] = sf::Vector2f(-HEX_W / 4, HEX_H / 2);
	m_vertices[5] = sf::Vector2f(HEX_W / 4, HEX_H / 2);

	m_lines.resize(12);
	m_lines.setPrimitiveType(sf::Lines);
		for (int i = 0; i < 6; i++)
		{
			m_lines[i*2] = m_vertices[mod(i,6)];
			m_lines[i*2+1] = m_vertices[mod(i + 1,6)];
			m_lines[i*2].color = sf::Color(200, 200, 200);
			m_lines[i*2+1].color = sf::Color(200, 200, 200);
			walls[i] = false;
		}
	
}

Hex::Hex(int x, int y)
{
	text.setFillColor(sf::Color::Blue);
	text.setString(x + ";" + y);
	Hex();
}

void  Hex::setColor(sf::Color color)
{
	for ( unsigned int i = 0; i < m_vertices.getVertexCount(); i++)
	{
		m_vertices[i].color = color;
	}
}

void Hex::setCoordinates(int x, int y) {
	gridPos = sf::Vector2i(x, y);
}

Hex::WALL Hex::invertWall(WALL wall)
{
	if (wall >= 0 || wall < 6)
	{
		return static_cast<WALL>(mod(wall-3,6));
	}
	throw std::invalid_argument("INCORRECT WALL");
}

void Hex::paintWall(int wall, sf::Color color)
{
	int b = m_vertices.getVertexCount();
	m_vertices[mod(wall-3, b)].color = color;
	m_vertices[mod(wall -4, b)].color = color;
}

void Hex::setWall(Hex::WALL wall, bool value)
{
	if (wall >= 0 && wall < 6)
	{
		walls[wall] = value;

		sf::Color col;
		if (value)
		{
			col = sf::Color::Black;
		}
		else
		{
			col = sf::Color(200, 200, 200);
		}

		m_lines[mod(wall - 4, 6) * 2].color = col;
		m_lines[mod(wall - 4, 6) * 2 + 1].color = col;
	}
		
	else
		throw std::invalid_argument("INCORRECT WALL");
}


Hex::WALL Hex::getWall(Hex::WALL wall) const
{
	if (wall >= 0 && wall < 6)
		return static_cast<Hex::WALL>(walls[wall]);
	else
		throw std::invalid_argument("INCORRECT WALL");
}

sf::Vector2i Hex::getCoordinates()
{
	return gridPos;
}

void Hex::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_vertices, states);
	target.draw(m_lines, states);
	target.draw(text, states);
}


Hex::~Hex()
{
}

void Hex::print()
{
	std::cout << getWall(Hex::LOWER_RIGHT) ? "1" : "0";
	std::cout << getWall(Hex::UPPER_RIGHT) ? "1" : "0";
	std::cout << getWall(Hex::TOP) ? "1" : "0";
	std::cout << getWall(Hex::BOTTOM) ? "1" : "0";
	std::cout << getWall(Hex::UPPER_LEFT) ? "1" : "0";
	std::cout << getWall(Hex::LOWER_LEFT) ? "1" : "0";
	
}

