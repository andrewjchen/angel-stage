#include "GameState.hxx"
#include <sstream>
#include <iostream>

using std::stringstream;
using std::map;
using std::string;

GameState::GameState(void){

}

GameState::GameState(const GameState& other){
	players = other.players;
	resources = other.resources;
}

const GameState& GameState::operator=(const GameState& other){
	players = other.players;
	resources = other.resources;
	return *this;
}

std::string serializeGameState(const GameState& gs) {
	static string delim = " ";
	stringstream ret;
	// ret << gs.orb.x << delim;
	// ret << gs.orb.y << delim;
	// ret << gs.orb.id << delim;
	// ret << gs.orb.state << delim;
	// ret << gs.felhound.x << delim;
	// ret << gs.felhound.y << delim;
	// ret << gs.felhound.xvel << delim;
	// ret << gs.felhound.yvel << delim;
	// ret << gs.felhound.orientation << delim;
	// ret << gs.felhound.state << delim;
	// ret << gs.elves.size() << delim;
	// typedef std::map<int, Elf>::const_iterator it_type;
	// for(it_type iterator = gs.elves.begin(); iterator != gs.elves.end(); iterator++) {
	//     // iterator->first = key
	//     // iterator->second = value
	//     // Repeat if you also want to iterate through the second map.

	// 	ret << iterator->second.x << delim;
	// 	ret << iterator->second.y << delim;
	// 	ret << iterator->second.xvel << delim;
	// 	ret << iterator->second.yvel << delim;
	// 	ret << iterator->second.orientation << delim;
	// 	ret << iterator->second.xgoal << delim;
	// 	ret << iterator->second.ygoal << delim;
	// 	ret << iterator->second.id << delim;
	// 	ret << iterator->second.color.r << delim;
	// 	ret << iterator->second.color.g << delim;
	// 	ret << iterator->second.color.b << delim;
	// 	ret << iterator->second.state << delim;
	// }
	
	return ret.str();
}


std::string gameStateToString(const GameState& gs) {
	stringstream ret;
	ret << "{GameState:\n";
	// ret << "{FH: pos=";
	// ret << "(" << gs.felhound.x << "," << gs.felhound.y << "), vel=(" << gs.felhound.xvel << "," << gs.felhound.yvel << "), orientation=" << gs.felhound.orientation << " }\n";
	// ret << "{Orb: pos=(" << gs.orb.x << ", " << gs.orb.y << "), id=" << gs.orb.id << ", state=" << gs.orb.state <<"}\n";
	// ret << gs.elves.size() << "Elves:\n";

	// typedef std::map<int, Elf>::const_iterator it_type;
	// for(it_type iterator = gs.elves.begin(); iterator != gs.elves.end(); iterator++) {
	//     // iterator->first = key
	//     // iterator->second = value
	//     // Repeat if you also want to iterate through the second map.
	// 	ret << "[";
	// 	ret << "id=" << iterator->second.id << ", ";
	// 	ret << "pos=(" << iterator->second.x << ", " << iterator->second.y << "), ";
	// 	ret << "vel=(" << iterator->second.xvel << ", " << iterator->second.yvel << ")";
	// 	ret << "orientation=(" << iterator->second.orientation << ")";
	// 	ret << "goal=(" << iterator->second.xgoal << ", " << iterator->second.ygoal << ")";
	// 	ret << "color=(" << iterator->second.color.r << ", " << iterator->second.color.g << ", " << iterator->second.color.b << ")";
	// 	ret << "state=" << iterator->second.state << "";
	// 	ret << "]\n";
	// }
	// for(unsigned int i=0;i<gs.elves.size();i++) {
	// 	ret << "[";
	// 	ret << "id=" << gs.elves[i].id << ", ";
	// 	ret << "pos=(" << gs.elves[i].x << ", " << gs.elves[i].y << "), ";
	// 	ret << "vel=(" << gs.elves[i].xvel << ", " << gs.elves[i].yvel << ")";
	// 	ret << "orientation=(" << gs.elves[i].orientation << ")";
	// 	ret << "goal=(" << gs.elves[i].xgoal << ", " << gs.elves[i].ygoal << ")";
	// 	ret << "color=(" << gs.elves[i].color.r << ", " << gs.elves[i].color.g << ", " << gs.elves[i].color.b << ")";
	// 	ret << "state=" << gs.elves[i].state << "";
	// 	ret << "]\n";
	// }
	ret << "}";
	
	return ret.str();
}

GameState deserializeGameState(const std::string& str) {
	GameState ret;
	// stringstream read(str);
	// read >> ret.orb.x;
	// read >> ret.orb.y;
	// read >> ret.orb.id;
	// int orbState = -1;
	// // read >> ret.orb.state;
	// read >> orbState;
	// ret.orb.state = static_cast<OrbState>(orbState);
	// read >> ret.felhound.x;
	// read >> ret.felhound.y;
	// read >> ret.felhound.xvel;
	// read >> ret.felhound.yvel;
	// read >> ret.felhound.orientation;
	// // read >> ret.felhound.state;
	// int felhoundState = -1;
	// read >> felhoundState;
	// ret.felhound.state = static_cast<FelhoundState>(felhoundState);
	// int n; read >> n;
	
	// for(int i=0;i<n;i++) {
	// 	Elf e;
	// 	read >> e.x;
	// 	read >> e.y;
	// 	read >> e.xvel;
	// 	read >> e.yvel;
	// 	read >> e.orientation;
	// 	read >> e.xgoal;
	// 	read >> e.ygoal;
	// 	read >> e.id;
	// 	read >> e.color.r;
	// 	read >> e.color.g;
	// 	read >> e.color.b;
	// 	// read >> static_cast<ElfState>(e.state);
	// 	int elfState = -1;
	// 	read >> elfState;
	// 	e.state = static_cast<ElfState>(elfState);
	// 	ret.elves[e.id] = e;
	// 	// ret.elves.push_back(e);
	// }
	
	return ret;
}