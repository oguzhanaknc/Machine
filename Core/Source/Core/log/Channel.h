#pragma once
#include "Entry.h"
#include "Driver.h"
#include "memory"
#include "vector"

namespace machine::log {
	struct Entry;

	class IChannel
	{
	public:
		virtual ~IChannel() = default;
		virtual void Submit(Entry&) = 0;
		virtual void AttachDriver(std::shared_ptr<IDriver>) = 0;
	};

	class Channel : public IChannel {
	public:
		Channel(std::vector<std::shared_ptr<IDriver>> driverPtrs = {});

		// Inherited via IChannel
		void Submit(Entry&) override;
		void AttachDriver(std::shared_ptr<IDriver>) override;
	private:
		std::vector<std::shared_ptr<IDriver>> driverPtrs_;

	};

}
