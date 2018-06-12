#include "stdafx.h"
#include "EcranAcceuil.h"


EcranAcceuil::EcranAcceuil()
{
}


EcranAcceuil::~EcranAcceuil()
{
}

void EcranAcceuil::Show(sf::RenderWindow & renderWindow)
{
	sf::Texture texture;
	if (texture.loadFromFile("c:/Dev/JIN4/JIN4/images/the_muses.png") != true)
	{
		return;
	}
	sf::Sprite sprite(texture);

	renderWindow.clear();
	renderWindow.draw(sprite);
	renderWindow.display();

	sf::Event event;
	while (true)
	{

		while (renderWindow.pollEvent(event))
		{

			if (event.type == sf::Event::EventType::KeyPressed
				|| event.type == sf::Event::EventType::MouseButtonPressed
				|| event.type == sf::Event::EventType::Closed)
			{
				return;
			}
		}
	}
}