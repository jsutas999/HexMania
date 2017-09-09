#include "stdafx.h"
#include "Game.h"
#define SCREEN_W 1000
#define SCREEN_H 800

Game::Game()
{
	window = new sf::RenderWindow(sf::VideoMode(SCREEN_W, SCREEN_H), "HexMan");
	sf::View view(sf::Vector2f(0, 0), sf::Vector2f(SCREEN_W, SCREEN_H));
	window->setView(view);
	grid = HexGrid(6, 4);
	grid.setPosition(0, 0);
	grid.center();
	selected = nullptr;

	wall = 0;
}

Game::~Game()
{
}

void Game::run()
{
	isRunning = true;
	Hex* n = nullptr;
	bool mouse_preset;

	while (window->isOpen())
	{
		sf::Event event;
		mouse_preset = false;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();

			if (event.type == sf::Event::Resized)
			{
				view.setSize((int)window->getSize().x,(int) window->getSize().y);
				view.setCenter(0, 0);
				
				window->setView(view);
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					mouse_preset = true;
				}
			}

		}

		sf::Vector2i mPosition = sf::Mouse::getPosition(*window);

		if (mPosition.x > 0 && mPosition.x < (int)window->getSize().x)
		{

			if (mPosition.y > 0 && mPosition.y < (int)window->getSize().y)
			{
				sf::Vector2f global = window->mapPixelToCoords(mPosition);
				sf::Vector2f local = grid.getInverseTransform()*global;

				if (selected != nullptr)
				{
					selected->paintWall(wall, sf::Color::White);
				}

				if (n != nullptr)
				{
					n->paintWall(Hex::invertWall(static_cast<Hex::WALL>(wall)), sf::Color::White);
				}

				selected = grid.getNearestTile(local);

				if (selected != nullptr)
				{
					float angle = static_cast<float> ((grid.getAngle(local, selected) * 180) / 3.14);
					wall = grid.getWall(angle);

					std::cout << wall << " " << angle <<" ";
					selected->print();
					std::cout << "\n";

					 n = grid.getNeighbor(static_cast<Hex::WALL>(wall), selected);
					if (n != nullptr)
					{
						n->paintWall(Hex::invertWall(static_cast<Hex::WALL>(wall)), sf::Color(201, 220, 2552));
					}
					selected->paintWall(wall,sf::Color(201, 220, 255));

					if (mouse_preset)
					{
						grid.toggleWall(static_cast<Hex::WALL>(wall), selected);

					}
				}
			}
		}

		window->clear(sf::Color(99,99,99));
		window->draw(grid);
		window->display();
	}
}
