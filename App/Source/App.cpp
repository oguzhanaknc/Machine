#include "Core/src/ioc/Container.h"
#include "Core/src/log/EntryBuilder.h"
#include "Core/src/log/Channel.h"
#include "Core/src/log/MsvcDebugDriver.h"
#include "Core/src/log/TextFormatter.h"
#include "Core/src/log/SeverityLevelPolicy.h"
#include <iostream>

using namespace machine;
#define machinelog machine::log::EntryBuilder{__FILEW__,__FUNCTIONW__,__LINE__}.channel(pChan.get())

int main()
{
	std::unique_ptr<log::IPolicy> pPolicy = std::make_unique<log::SeverityLevelPolicy>(log::Level::Error);
	std::unique_ptr<log::IChannel> pChan = std::make_unique<log::Channel>(std::vector<std::shared_ptr<log::IDriver>>{
		std::make_shared<log::MsvcDebugDriver>(std::make_unique<log::TextFormatter>())
	});
	pChan->AttachPolicy(std::move(pPolicy));
	machinelog.info(L"Haydi Bakalim");
	machinelog.error(L"Haydi bu calisirt Bakalim");
	return 0;
}

