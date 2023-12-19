#pragma once


namespace machine::log {
	struct Entry;
	class IDriver {

	public:
		virtual ~IDriver();
		virtual void Submit(const Entry&) = 0;
	private:
	};
}
