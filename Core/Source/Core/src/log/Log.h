#pragma once
#include "Channel.h"
#include "EntryBuilder.h"
namespace machine::log {
	IChannel* GetDefaultChannel();
	void Boot();
}
#define machinelog machine::log::EntryBuilder{__FILEW__,__FUNCTIONW__,__LINE__}.channel(log::GetDefaultChannel())
