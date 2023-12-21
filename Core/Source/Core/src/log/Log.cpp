#include "Log.h"
#include "Core/src/ioc/Singletons.h"
#include "Core/src/ioc/Container.h"
#include "Core/src/log/SeverityLevelPolicy.h"
#include "MsvcDebugDriver.h"

namespace machine::log {
     IChannel* machine::log::GetDefaultChannel()
    {
        static std::shared_ptr<IChannel> channelChacePtr = ioc::Sing().Resolve<IChannel>();
        return channelChacePtr.get();
    }
     void Boot()
     {
		 // container
		 ioc::Get().Register<log::IChannel>([] {
			 std::vector drivers{ ioc::Get().Resolve<log::IDriver>() };
			 auto pChan = std::make_shared<log::Channel>(std::move(drivers));
			 pChan->AttachPolicy(ioc::Get().Resolve<log::SeverityLevelPolicy>());
			 return pChan;
			 });
		 ioc::Get().Register<log::IDriver>([] {
			 return std::make_shared<log::MsvcDebugDriver>(ioc::Get().Resolve<log::ITextFormatter>());
			 });
		 ioc::Get().Register<log::ITextFormatter>([] {
			 return std::make_shared<log::TextFormatter>();
			 });
		 ioc::Get().Register<log::SeverityLevelPolicy>([] {
			 return std::make_shared<log::SeverityLevelPolicy>(log::Level::Error);
			 });

		 // Singleton
		 ioc::Sing().RegisterPassthru<log::IChannel>();
     }
}
