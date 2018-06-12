#pragma once

#define DBGPRINTF_LEVEL 6

#include "LoadBalancing-cpp/inc/Client.h"
#include <SFML/Graphics.hpp>

#include "UIListener.h"
#include "StdIO_UIListener.h"

class Game;

class NetworkLogic : public ExitGames::LoadBalancing::Listener
{
public:
	enum MessageType
	{
		PlayerChange,
		ChoixSujet,
		ReceptionScore
	};

	NetworkLogic(const ExitGames::Common::JString& appID, const ExitGames::Common::JString& appVersion, Game *game);
	void connect(void);
	void joinOrCreateRoom(const ExitGames::Common::JString& roomName);
	void disconnect(void);
	void service(void);
	void sendPlayerChange(sf::Keyboard::Key key);
	void sendSubject(int subject);
	void sendScore(int score);


	int getNumber(void);
	int getRoundTripTime(void) 	const;
	int getRoundTripTimeVariance(void) 	const;
	int getSendCount() const;
	int getReceiveCount() const;
	int getBytesOut(void) const;
	int getBytesIn(void) const;

private:
	enum State
	{
		INITIALIZED = 0,
		CONNECTING,
		CONNECTED,
		JOINING,
		JOINED,
		SENT_DATA,
		RECEIVED_DATA,
		LEAVING,
		LEFT,
		DISCONNECTING,
		DISCONNECTED
	};

	void waitForListener(const State &originalState, const State &targetState);
	ExitGames::Common::JString state2string(State state);

	//
	// All callbacks
	//

	// receive and print out debug out here
	virtual void debugReturn(int debugLevel, const ExitGames::Common::JString& string);

	// implement your error-handling here
	virtual void connectionErrorReturn(int errorCode);
	virtual void clientErrorReturn(int errorCode);
	virtual void warningReturn(int warningCode);
	virtual void serverErrorReturn(int errorCode);

	// events, triggered by certain operations of all players in the same room
	virtual void joinRoomEventAction(int playerNr, const ExitGames::Common::JVector<int>& playernrs, const ExitGames::LoadBalancing::Player& player);
	virtual void leaveRoomEventAction(int playerNr, bool isInactive);
	virtual void customEventAction(int playerNr, nByte eventCode, const ExitGames::Common::Object& eventContent);

	// callbacks for operations on PhotonLoadBalancing server
	virtual void connectReturn(int errorCode, const ExitGames::Common::JString& errorString, const ExitGames::Common::JString& cluster);
	virtual void disconnectReturn(void);
	virtual void createRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
	virtual void joinOrCreateRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
	virtual void joinRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
	virtual void joinRandomRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
	virtual void leaveRoomReturn(int errorCode, const ExitGames::Common::JString& errorString);
	virtual void joinLobbyReturn(void);
	virtual void leaveLobbyReturn(void);

private:
	ExitGames::Common::Logger mLogger; // accessed by EGLOG()
	State mState;
	Game *mGame;
	StdIO_UIListener mUIListener;
	UIListener* mpOutputListener;
	ExitGames::LoadBalancing::Client mLoadBalancingClient;
	int mSendCount;
	int mReceiveCount;
};

