#pragma once
#include "Channel.h"
#include "EntryBuilder.h"
namespace machine::log {
	IChannel* GetDefaultChannel();

	void Boot();

#ifdef NDEBUG 
	inline constexpr int defaultTraceSkip = 2;
#else 
	inline constexpr int defaultTraceSkip = 6;
#endif 
}
#define machinelog log::EntryBuilder{ __FILEW__, __FUNCTIONW__, __LINE__ }.chan(log::GetDefaultChannel()).trace_skip(log::defaultTraceSkip)
