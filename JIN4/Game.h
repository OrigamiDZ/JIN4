#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"


class Game
{

public:
	static void Start();
	Game();
	~Game();

private:
	static bool IsExiting();
	static void GameLoop();

	static void ShowSplashScreen();
	static void ShowMenu();

	enum GameState {
		Uninitialized, ShowingSplash, Paused,
		ShowingMenu, Playing, Exiting
	};

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;
};
