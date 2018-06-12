#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "NetworkLogic.h"


class Game
{

public:
	void Start();
	Game();
	
	bool twoPlayers;
	std::vector<std::string> data;
	std::string subject;
	NetworkLogic mNetworkLogic;


private:
	int	mPlayerNumber;

	 bool IsExiting();
	 void GameLoop();

	 void ShowSplashScreen();
	 void ShowMenu();
	 void ShowSecondMenu();
	 void ShowQuestionMenu();
	 void ShowQuestionMultiMenu();


	enum GameState {
		Uninitialized, 
		ShowingSplash, 
		Paused, 
		ShowingSecondMenu,
		PlayingSolo, 
		PlayingMulti,
		ShowingMenu, 
		Exiting
	};

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;

};
