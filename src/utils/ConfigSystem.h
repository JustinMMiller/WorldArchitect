#ifndef CONFIGSYSTEM_H
#define CONFIGSYSTEM_H

#include <string>
#include <unordered_map>

#include "Parameter.h"

namespace WorldArchitect
{
	class ConfigSystem
	{
		public:
			template <typename T> void addParameter(std::string name, T value = T());
			template <typename T> T getParameterValue(std::string name);
			template <typename T> void setParameterValue(std::string name, T newValue);
			std::string listParams();
			ConfigSystem();
			~ConfigSystem();
		private:
			//std::unordered_map<std::string, Parameter* > params;
	};
}

#endif
