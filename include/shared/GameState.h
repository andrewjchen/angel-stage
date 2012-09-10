#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <vector>
#include <map>
#include <string>

enum UnitState {
	UNIT_MOVING = 0,
	UNIT_RESTING = 1,
	UNIT_FIGHTING = 2,
	UNIT_FEEDING= 3
};

struct Unit {
	//Pose
	double x;
	double y;
	double theta;

	//Attributes
	int attackSpeed;
	int attackDamage;
	int defense;

	//
	int id;

	//State
	double health;
	UnitState state;

};

struct Player {
	std::vector<Unit> units;

	int id;
};

struct Resource {
	double x;
	double y;

};

struct GameState{
	std::map<int, Player> players;
	std::vector<Resource> resources;

	
    GameState(void);
    GameState(const GameState&);
    const GameState& operator=(const GameState&);
};

std::string serializeGameState(const GameState&);
std::string gameStateToString(const GameState&);
GameState deserializeGameState(const std::string&);

#endif



