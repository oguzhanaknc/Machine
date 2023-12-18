#pragma once
#include "Entry.h"
namespace machine::log {
	struct Entry;
	class IChannel
	{
	public:
		virtual void Submit(Entry&) = 0;
	};

}
