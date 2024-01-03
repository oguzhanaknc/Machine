#include "Core/src/Core.h"


using namespace machine;
void anathorfunc() {
	machinelog.error(L"Haydi bu calisirt Bakalim");
}

void somefunc() {
	anathorfunc();
}

int main()
{
	core::Boot();
	somefunc();

	return 0;
}

