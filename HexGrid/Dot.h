#pragma once

class Dot : public sf::Transformable, public sf::Drawable
{
public:
	Dot();
	~Dot();

	sf::Vector2i getCoordinatesInGrid();
	sf::Vector2f getCoordinatesInWorld();
	void move(Hex::WALL wall);

private:
	sf::CircleShape dot;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

