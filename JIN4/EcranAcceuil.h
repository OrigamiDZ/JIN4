#pragma once

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "NetworkLogic.h"


class EcranAcceuil
{
public:
	EcranAcceuil(Game *game);
	~EcranAcceuil();
	void Show(sf::RenderWindow& window);
private:
	Game * mGame;

};