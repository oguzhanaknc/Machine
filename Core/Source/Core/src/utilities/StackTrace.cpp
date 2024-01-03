#include "StackTrace.h"
#include "Core/third/backward.hpp"
#include "sstream"
#include "String.h"
namespace machine::utilities {
	StackTrace::StackTrace(size_t skip)
	{
		backward::TraceResolver thisIsAWorkaround; // https://github.com/bombela/backward-cpp/issues/206
		pTrace = std::make_unique<backward::StackTrace>();
		pTrace->load_here(64);
		if (skip != 0) {
			pTrace->skip_n_firsts(skip);
		}
	}
	StackTrace::StackTrace(const StackTrace& src)
		:
		pTrace{ src.pTrace ? std::make_unique<backward::StackTrace>(*src.pTrace) : std::unique_ptr<backward::StackTrace>{} }
	{}
	StackTrace::StackTrace(StackTrace&& donor) noexcept
		:
		pTrace{ std::move(donor.pTrace) }
	{}
	StackTrace& StackTrace::operator=(const StackTrace& src)
	{
		pTrace = src.pTrace ? std::make_unique<backward::StackTrace>(*src.pTrace) : std::unique_ptr<backward::StackTrace>{};
		return *this;
	}
	StackTrace& StackTrace::operator=(StackTrace&& donor) noexcept
	{
		if (&donor != this) {
			pTrace = std::move(donor.pTrace);
		}
		return *this;
	}
	StackTrace::~StackTrace() {}
	std::wstring StackTrace::Print() const
	{
		if (pTrace) {
			std::ostringstream oss;
			backward::Printer printer;
			printer.print(*pTrace, oss);
			return utilities::ToWide(oss.str());
		}
		else {
			return L"== EMPTY TRACE ==";
		}
	}
}