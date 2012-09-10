#include "GamePhysics.hpp"
#include "GameState.hxx"
#include <cmath>
#include "Debug.hxx"
#include <stdlib.h>
#include <time.h>

using std::vector;
using std::pow;
using std::sqrt;
using std::atan2;
using std::sin;
using std::cos;
using std::min;
using std::max;
using std::abs;

inline double dist(double x1,double y1,double x2,double y2) {
	return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}

inline double clamp(double x,double minVal,double maxVal) {
	return max(minVal,min(maxVal,x));
}

GamePhysics::GamePhysics() {
	// //                          x  y  x, yvel theta, state
	// state.felhound = (Felhound){0, 0, 0, 0, 0, FELHOUND_UNSPAWNED};
	// state.orb = (Orb){0,0,-1, ORB_UNSPAWNED};
	// felhoundAcceleration = 0;
	// felhoundPlanner = new FelhoundPathPlanner(&state);
	// orbPlanner = new OrbPathPlanner(&state);
}

GamePhysics::~GamePhysics() {
	
}

GameState GamePhysics::getGameState(){
	return state;
}

void GamePhysics::addPlayer(int id){

}

void GamePhysics::moveUnit(int playerID, int unitID, double x, double y){

}

void GamePhysics::unitSplit(int playerID, int unitID){

}

void GamePhysics::unitFeed(int playerID, int unitID, int resourceID){

}

void GamePhysics::unitFight(int player1ID, int unit2ID, int player2ID, int unit2ID){

}

void GamePhysics::unitMerge(int playerID, int unit1ID, int unit2ID){
	
}