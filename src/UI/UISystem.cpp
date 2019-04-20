#include "UISystem.h"

using namespace WorldArchitect;

std::mutex UISystem::lock;
UISystem *UISystem::instance = NULL;
