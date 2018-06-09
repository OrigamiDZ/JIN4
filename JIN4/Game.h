#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class Game
{

public:
	static void Start();
	Game();
	~Game();

	std::vector<std::string> data;

private:
	static bool IsExiting();
	static void GameLoop();

	static void ShowSplashScreen();
	static void ShowMenu();
	static void ShowSecondMenu();
	static void ShowQuestionMenu();

	enum GameState {
		Uninitialized, ShowingSplash, Paused, ShowingSecondMenu,
		PlayingSolo, PlayingMulti,
		ShowingMenu,  Exiting
	};

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;

};
