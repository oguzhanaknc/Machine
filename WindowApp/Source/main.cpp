#include <Core/src/Core.h>
#include <Core/src/win/Input.h>
#include <Core/src/ioc/Container.h> 

using namespace machine;
using namespace std::chrono_literals;



int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PWSTR pCmdLine,
	int nCmdShow){
	core::Boot();
	auto keyboard = std::make_shared<win::Keyboard>();
	auto windowPtr = ioc::Get().Resolve<win::IWindow>(win::IWindow::IocParams{
					.name = L"Window main",
					.pKeySink = keyboard,
		});
	while (!windowPtr->IsClosing()) {

		while (const auto e = keyboard->GetEvent()) {
			if (e->type == win::KeyEvent::Type::Release) continue;
			switch (e->code) {
			case VK_SPACE:
				break;
			}
			if (keyboard->KeyIsPressed(win::keys::KEY_F))
			{
				windowPtr->SetTitle(L"Respect !");

			}
		}
	}
	return 0;
}

