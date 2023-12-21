#pragma once
#include "memory"
#include "string"
namespace backward {
	class StackTrace;
}
namespace machine::utilities {
	class StackTrace {
	public:
		StackTrace();
		~StackTrace();
		StackTrace& operator=(const StackTrace& src);
		StackTrace(const StackTrace& src);
		std::wstring Print() const;
	private:
		std::unique_ptr<backward::StackTrace> pTrace;
	};
}