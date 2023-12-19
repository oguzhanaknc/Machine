#include "Channel.h"


namespace machine::log {
	Channel::Channel(std::vector<std::shared_ptr<IDriver>> driverPtrs)
		:
		driverPtrs_(driverPtrs)
	{
	}
	void Channel::Submit(Entry& e)
	{
		for (auto& pDriver : driverPtrs_)
		{
			pDriver->Submit(e);
		}
	}
	void Channel::AttachDriver(std::shared_ptr<IDriver> pDriver)
	{
		driverPtrs_.push_back(std::move(pDriver));
	}
}

