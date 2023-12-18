#include "EntryBuilder.h"

namespace machine::log {
	EntryBuilder::EntryBuilder(const wchar_t* sourceFile, const wchar_t* sourceFunctionName, int sourceLine)
		: 
		Entry{
			.level_ = Level::Error,
			.sourceFile_ = sourceFile,
			.sourceFunctionName_ = sourceFunctionName,
			.sourceLine_ = sourceLine,
		}
	{
	}

	EntryBuilder& EntryBuilder::note(std::wstring note)
	{
		note_ = std::move(note);
		return *this;

	}

	EntryBuilder& EntryBuilder::level(Level lvl)
	{
		level_ = lvl;
		return *this;
	}

	EntryBuilder& EntryBuilder::channel(IChannel* pChan)
	{
		dest_ = pChan;
		return *this;
	}

	EntryBuilder::~EntryBuilder()
	{
		if (dest_) {
			dest_->Submit(*this);
		}
	}

}

