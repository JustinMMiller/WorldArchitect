#include "ConfigSystem.h"

using namespace WorldArchitect;

template <typename T> void ConfigSystem::addParameter(std::string name, T value)
{
	//params[name] = Parameter<T>{value};
}

template <typename T> T ConfigSystem::getParameterValue(std::string name)
{
	//return params[name].getValue();
}

template <typename T> void ConfigSystem::setParameterValue(std::string name, T newValue)
{
}

std::string ConfigSystem::listParams()
{
	return "";
}

ConfigSystem::ConfigSystem()
{
}

ConfigSystem::~ConfigSystem()
{
}
