#include "ConfigSystem.h"

using namespace WorldArchitect;

void ConfigSystem::addParameter(std::string name, ParamType t, std::string value)
{
	mut.lock();
	Parameter p {value, t};
	params[name] = p;
	mut.unlock();
}

std::string ConfigSystem::getParameterValue(std::string name)
{
	mut.lock_shared();
	std::string ret = params[name].getValue();
	mut.unlock_shared();
	return ret;
}

void ConfigSystem::setParameterValue(std::string name, std::string newValue)
{
	mut.lock();
	if(params.count(name) > 0)
	{
		params[name].setValue(newValue);
	}
	mut.unlock();
}

std::string ConfigSystem::listParams()
{
	std::string ret = "\nName \t\t Value \n";
	mut.lock_shared();
	for (const auto & p : params)
	{
		ret += p.first;
		ret += "\t\t";
		ret += p.second.getValue();
		ret += "\n";
	}
	mut.unlock_shared();
	return ret;
}

ConfigSystem::ConfigSystem()
	: params(), mut()
{
}

ConfigSystem::~ConfigSystem()
{
}

ConfigSystem * ConfigSystem::getInstance()
{
	if( WorldArchitect::ConfigSystem::instance == nullptr)
	{
		instance = new ConfigSystem();
	}
	return instance;
}

ConfigSystem * ConfigSystem::instance = nullptr;
