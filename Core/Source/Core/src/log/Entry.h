#pragma once
#include "Level.h"
#include "Core/src/utilities/StackTrace.h"
#include <chrono>
namespace machine::log {
	struct Entry
	{
		Level level_ = Level::Error;
		std::wstring note_;
		const wchar_t* sourceFile_ = nullptr;
		const wchar_t* sourceFunctionName_ = nullptr;
		int sourceLine_ = -1;
		std::chrono::system_clock::time_point timeStamp;
		std::optional<utilities::StackTrace>  tracer;

		
	};
}
