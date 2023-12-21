#include "Channel.h"


namespace machine::log {
	Channel::Channel(std::vector<std::shared_ptr<IDriver>> driverPtrs)
		:
		driverPtrs_(driverPtrs)
	{
	}
	Channel::~Channel()
	{
	}
	void Channel::Submit(Entry& e)
	{
		for (auto& pPolicy : policyPtrs_) {
			if (!pPolicy->TransformFilter(e)) {
				return;
			}
		}

		for (auto& pDriver : driverPtrs_)
		{
			pDriver->Submit(e);
		}
	}
	void Channel::AttachDriver(std::shared_ptr<IDriver> pDriver)
	{
		driverPtrs_.push_back(std::move(pDriver));
	}
	void Channel::AttachPolicy(std::shared_ptr<IPolicy> pPolicy)
	{
		policyPtrs_.push_back(std::move(pPolicy));
	}
}

