#include "Core/ioc/Container.h"
#include "Core/log/EntryBuilder.h"
#include "Core/log/Channel.h"
#include "Core/log/MsvcDebugDriver.h"
#include "Core/log/TextFormatter.h"
#include <iostream>

using namespace machine;
#define machinelog machine::log::EntryBuilder{__FILEW__,__FUNCTIONW__,__LINE__}.channel(pChan.get())

int main()
{
	std::unique_ptr<log::IChannel> pChan = std::make_unique<log::Channel>(std::vector<std::shared_ptr<log::IDriver>>{
		std::make_shared<log::MsvcDebugDriver>(std::make_unique<log::TextFormatter>())
	});
	machinelog.fatal(L"Haydi Bakalim");
	return 0;
}

