#include "Level.h"

namespace machine::log {
	std::wstring GetLevelName(Level lv) {
		switch (lv)
		{
		case machine::log::Level::Verbose:
			return L"Trace";
		case machine::log::Level::Debug:
			return L"Debug";
		case machine::log::Level::Info:
			return L"Info";
		case machine::log::Level::Warn:
			return L"Warn";
		case machine::log::Level::Error:
			return L"Error";
		case machine::log::Level::Fatal:
			return L"Fatal";
		default:
			return L"Unknown";
		}
	}
}