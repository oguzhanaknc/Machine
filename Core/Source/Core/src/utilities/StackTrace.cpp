#include "StackTrace.h"
#include "Core/third/backward.hpp"
#include "sstream"
#include "String.h"
namespace machine::utilities {
	StackTrace::StackTrace()
	{
		backward::TraceResolver thisIsAWorkaround;
		pTrace = std::make_unique<backward::StackTrace>();
		pTrace->load_here(64);
		pTrace->skip_n_firsts(4);
	}
	StackTrace::~StackTrace()
	{
	}
	StackTrace& StackTrace::operator=(const StackTrace& src)
	{
		pTrace = std::make_unique<backward::StackTrace>(*pTrace);
		return *this;
	}
	StackTrace::StackTrace(const StackTrace& src)
		: pTrace(std::make_unique<backward::StackTrace>(*pTrace))
	{
	}
	std::wstring StackTrace::Print() const
	{
		std::ostringstream oss;
		backward::Printer printer;
		printer.print(*pTrace, oss);
		return utilities::ToWide(oss.str());
	}
}