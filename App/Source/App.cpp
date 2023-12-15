#include "Core/Core.h"
#include "Core/ioc/Container.h"
#include <iostream>


struct Base
{
	virtual int Test() { return 123; }
	virtual ~Base() = default;
};

struct Derived : public Base
{
	int Test() override { return 321; }
};



int main()
{
	machine::ioc::Get().Register<Base>([] {return std::make_shared<Derived>(); });
	std::cout << machine::ioc::Get().Resolve<Base>()->Test() << std::endl;
}

