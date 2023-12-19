#include "MsvcDebugDriver.h"

namespace machine::log {
	MsvcDebugDriver::MsvcDebugDriver(std::unique_ptr<ITextFormatter> pFormatter)
		:
		pFormatter_{ std::move(pFormatter) }
	{}
	void MsvcDebugDriver::Submit(const Entry& e)
	{
		if (pFormatter_) {
			OutputDebugStringW(pFormatter_->Format(e).c_str());
		}
		// TODO: how to log stuff from log system
	}
	void MsvcDebugDriver::SetFormatter(std::unique_ptr<ITextFormatter> pFormatter)
	{
		pFormatter_ = std::move(pFormatter);
	}
}


