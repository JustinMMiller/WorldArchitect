#include "LuaBinding.h"
#include "EventSystem/EventSystem.h"
#include "EventSystem/Event.h"
#include "MapGenSystem/Map.h"
#include "MapGenSystem/GridMap.h"
#include "MapGenSystem/MapGenerator.h"
#include "SettlementSystem/SettlementSystem.h"
#include "SettlementSystem/Settlement.h"
#include "TagSystem/Tag.h"
#include "TagSystem/TagSystem.h"
#include "utils/GridPoint.h"
#include "utils/Logging.h"

using namespace WorldArchitect;

void prepareLuaState(sol::state *lua)
{
	lua->new_usertype<Map>("Map", "isWaterAt", &Map::isWaterAt, 
			"distToWater", &Map::distToWater, 
			"getHeightAt", &Map::getHeightAt, 
			"getSizeX", &Map::getSizeX, 
			"getSizeY", &Map::getSizeY);
	lua->new_usertype<GridMap>("GridMap", 
			sol::base_classes, sol::bases<Map>());
}
