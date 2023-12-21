#include "EntryBuilder.h"

namespace machine::log {
	EntryBuilder::EntryBuilder(const wchar_t* sourceFile, const wchar_t* sourceFunctionName, int sourceLine)
		:
		Entry{
			.level_ = Level::Error,
			.sourceFile_ = sourceFile,
			.sourceFunctionName_ = sourceFunctionName,
			.sourceLine_ = sourceLine,
			.timeStamp = std::chrono::system_clock::now()
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

	EntryBuilder& EntryBuilder::trace(std::wstring note)
	{
		note_ = std::move(note);
		level_ = Level::Verbose;
		return *this;
	}

	EntryBuilder& EntryBuilder::debug(std::wstring note)
	{
		note_ = std::move(note);
		level_ = Level::Debug;
		return *this;
	}

	EntryBuilder& EntryBuilder::info(std::wstring note)
	{
		note_ = std::move(note);
		level_ = Level::Info;
		return *this;
	}

	EntryBuilder& EntryBuilder::warn(std::wstring note)
	{
		note_ = std::move(note);
		level_ = Level::Warn;
		return *this;
	}

	EntryBuilder& EntryBuilder::error(std::wstring note)
	{
		note_ = std::move(note);
		level_ = Level::Error;
		return *this;
	}

	EntryBuilder& EntryBuilder::fatal(std::wstring note)
	{
		note_ = std::move(note);
		level_ = Level::Fatal;
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
			if ((int)level_ <= (int)Level::Error) {
				tracer.emplace();
			}
			dest_->Submit(*this);
		}
	}

}

