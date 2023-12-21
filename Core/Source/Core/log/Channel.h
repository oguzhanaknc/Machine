#pragma once
#include "Entry.h"
#include "Driver.h"
#include "memory"
#include "vector"
#include "Policy.h"
namespace machine::log {
	struct Entry;
	class IPolicy;

	class IChannel
	{
	public:
		virtual ~IChannel() = default;
		virtual void Submit(Entry&) = 0;
		virtual void AttachDriver(std::shared_ptr<IDriver>) = 0;
		virtual void AttachPolicy(std::unique_ptr<IPolicy>) = 0;
	};

	class Channel : public IChannel {
	public:
		Channel(std::vector<std::shared_ptr<IDriver>> driverPtrs = {});
		~Channel();
		// Inherited via IChannel
		void Submit(Entry&) override;
		void AttachDriver(std::shared_ptr<IDriver>) override;
		void AttachPolicy(std::unique_ptr<IPolicy>) override;
	private:
		std::vector<std::shared_ptr<IDriver>> driverPtrs_;
		std::vector<std::unique_ptr<IPolicy>> policyPtrs_;
	};

}
