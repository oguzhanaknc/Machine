#pragma once
#include "memory"

namespace machine::log {
	struct Entry;
	class ITextFormatter;
	class IDriver {

	public:
		virtual ~IDriver() = default;
		virtual void Submit(const Entry&) = 0;
	private:
	};

	class ITextDriver : public IDriver {

	public:
		virtual void SetFormatter(std::unique_ptr<ITextFormatter>)=0;
	private:
	};
}
