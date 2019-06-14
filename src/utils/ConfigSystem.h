#ifndef CONFIGSYSTEM_H
#define CONFIGSYSTEM_H

#include <shared_mutex>
#include <string>
#include <unordered_map>

#include "Parameter.h"

namespace WorldArchitect
{
	class ConfigSystem
	{
		public:
			void addParameter(std::string name, ParamType t, std::string value = std::string());
			std::string getParameterValue(std::string name);
			void setParameterValue(std::string name, std::string newValue);
			std::string listParams();
			~ConfigSystem();
			static ConfigSystem * getInstance();
		private:
			ConfigSystem();
			std::unordered_map<std::string, Parameter > params;
			static ConfigSystem *instance;
			std::shared_mutex mut;
	};
}

#endif
