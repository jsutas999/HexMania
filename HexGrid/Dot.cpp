#include "stdafx.h"
#include "stdafx.h"
#include "Dot.h"
#include "Hex.h"
#include <SFML/Graphics.hpp>

Dot::Dot()
{


}

Dot::~Dot()
{
}

sf::Vector2i Dot::getCoordinatesInGrid()
{
	return sf::Vector2i();
}

sf::Vector2f Dot::getCoordinatesInWorld()
{
	return sf::Vector2f();
}

void Dot::move(Hex::WALL wall)
{
}

void Dot::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(dot, states);
}
