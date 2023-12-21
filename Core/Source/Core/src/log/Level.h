#pragma once
#include <string>
namespace machine::log {

		enum class Level {None,Fatal,Error,Warn,Info,Debug,Verbose};
		std::wstring GetLevelName(Level);
}
