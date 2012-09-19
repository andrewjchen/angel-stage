#ifndef GAME_PHYSICS_H
#define GAME_PHYSICS_H

#include "GameState.hxx"

#include <vector>

class GamePhysics {

public:
	GamePhysics();
	~GamePhysics();
	
	const GameState& getState() { return state; }

	void addPlayer(int id);
	void moveUnit(int playerID, int unitID, double x, double y);
	void unitSplit(int playerID, int unitID);
	void unitFeed(int playerID, int unitID, int resourceID);
	void unitFight(int player1ID, int unit1ID, int player2ID, int unit2ID);
	void unitMerge(int playerID, int unit1ID, int unit2ID);
	
private:
	GamePhysics(const GamePhysics&) {}
	const GamePhysics& operator=(const GamePhysics& other) { return *this; }
	GameState state;


};


#endif
