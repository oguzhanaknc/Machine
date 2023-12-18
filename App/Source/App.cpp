#include "Core/ioc/Container.h"
#include "Core/log/EntryBuilder.h"
#include "Core/log/Channel.h"
#include <iostream>


#define machinelog machine::log::EntryBuilder{__FILEW__,__FUNCTIONW__,__LINE__}

class MockChannel : public machine::log::IChannel {
public:
	void Submit(machine::log::Entry& e) override {
		e_ = e;
		std::wcout << e.sourceFile_ << "\n";
		std::wcout << e.sourceFunctionName_ << "\n";
		std::wcout << e.sourceLine_ << "\n";
		std::wcout << e.note_ << "\n";
	}
	machine::log::Entry e_;
};


int main()
{
	MockChannel mc;
	machinelog.level(machine::log::Level::Error).note(L"logging test").channel(&mc);
}

