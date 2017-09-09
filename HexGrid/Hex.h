#pragma once
class Hex : public sf::Transformable, public sf::Drawable {
public:

	Hex();
	~Hex();

	Hex(int x, int y);

	enum WALL { UPPER_LEFT, LOWER_LEFT, BOTTOM, LOWER_RIGHT, UPPER_RIGHT , TOP};
	void setColor(sf::Color color);
	void setCoordinates(int x, int y);
	static WALL invertWall(WALL wall);
	void paintWall(int wall, sf::Color color);
	void setWall(Hex::WALL wall,bool value);
	void print();
	WALL getWall(Hex::WALL wall) const;
	sf::Vector2i getCoordinates();
	sf::Text text;
	std::string st;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::VertexArray m_vertices;
	sf::VertexArray m_lines;
	sf::Vector2i gridPos;
	bool walls[6];
};