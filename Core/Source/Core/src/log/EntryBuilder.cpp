#include "EntryBuilder.h"
#include "Core/src/win/machinewin.h"
#include "Channel.h"

namespace machine::log {
	EntryBuilder::EntryBuilder(const wchar_t* sourceFile, const wchar_t* sourceFunctionName, int sourceLine)
		:
		Entry{
			.sourceFile_ = sourceFile,
			.sourceFunctionName_ = sourceFunctionName,
			.sourceLine_ = sourceLine,
			.timestamp_ = std::chrono::system_clock::now(),
		}
	{}
	EntryBuilder& EntryBuilder::note(std::wstring note)
	{
		note_ = std::move(note);
		return *this;
	}
	EntryBuilder& EntryBuilder::level(Level level)
	{
		level_ = level;
		return *this;
	}
	EntryBuilder& EntryBuilder::verbose(std::wstring note)
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
	EntryBuilder& EntryBuilder::chan(IChannel* pChan)
	{
		pDest_ = pChan;
		return *this;
	}
	EntryBuilder& EntryBuilder::trace_skip(int depth)
	{
		traceSkipDepth_ = depth;
		return *this;
	}
	EntryBuilder& EntryBuilder::no_trace()
	{
		captureTrace_ = false;
		return *this;
	}
	EntryBuilder& EntryBuilder::trace()
	{
		captureTrace_ = true;
		return *this;
	}
	EntryBuilder& EntryBuilder::no_line()
	{
		showSourceLine_ = false;
		return *this;
	}
	EntryBuilder& EntryBuilder::line()
	{
		showSourceLine_ = true;
		return *this;
	}
	EntryBuilder& EntryBuilder::hr()
	{
		hResult_ = GetLastError();
		return *this;
	}
	EntryBuilder& EntryBuilder::hr(unsigned int hr)
	{
		hResult_ = hr;
		return *this;
	}
	EntryBuilder::~EntryBuilder()
	{
		if (pDest_) {
			if (captureTrace_.value_or((int)level_ <= (int)Level::Error)) {
				tracer.emplace(traceSkipDepth_);
			}
			pDest_->Submit(*this);
		}
	}

}

