#include <Core/src/Core.h>
#include <Core/src/ioc/Container.h> 
using namespace machine;
using namespace std::chrono_literals;



int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PWSTR pCmdLine,
	int nCmdShow)
{
	core::Boot();
	auto windowPtr = ioc::Get().Resolve<win::IWindow>();
	windowPtr->SetTitle(L"ILLUSION ENGINE FIRST WINDOW");
	int x = 0;
	while (windowPtr && !windowPtr->IsClosing()) {
		std::this_thread::sleep_for(50ms);
	}
	return 0;
}

