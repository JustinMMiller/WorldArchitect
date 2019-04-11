#include "LuaBinding.h"
#include "EventSystem/EventSystem.h"
#include "EventSystem/Event.h"
#include "MapGenSystem/Map.h"
#include "MapGenSystem/GridMap.h"
#include "MapGenSystem/MapGenerator.h"
#include "MapGenSystem/MapGenSystem.h"
#include "SettlementSystem/SettlementSystem.h"
#include "SettlementSystem/Settlement.h"
#include "TagSystem/Tag.h"
#include "TagSystem/TagSystem.h"
#include "utils/GridPoint.h"
#include "utils/Logging.h"


void WorldArchitect::prepareLuaState(sol::state *lua)
{
	lua->open_libraries(sol::lib::base);
	lua->new_usertype<Map>("Map", "isWaterAt", &Map::isWaterAt, 
			"new", sol::no_constructor,
			"distToWater", &Map::distToWater, 
			"getHeightAt", &Map::getHeightAt, 
			"getSizeX", &Map::getSizeX, 
			"getSizeY", &Map::getSizeY);
	lua->new_usertype<GridMap>("GridMap", 
			sol::base_classes, sol::bases<Map>());
	lua->new_usertype<MapGenSystem>("MapSys", "getMap", &MapGenSystem::getMap);
}