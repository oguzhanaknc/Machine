#pragma once
#include "Entry.h"
#include "Channel.h"
namespace machine::log{

	class IChannel;

	class EntryBuilder : private Entry
	{
	public:
		EntryBuilder(const wchar_t* sourceFile, const wchar_t* sourceFunctionName, int sourceLine);
		EntryBuilder& note(std::wstring note);
		EntryBuilder& level(Level lvl);
		EntryBuilder& channel(IChannel* pChan);
		~EntryBuilder();
	private:
		IChannel* dest_ = nullptr;
	};
}


