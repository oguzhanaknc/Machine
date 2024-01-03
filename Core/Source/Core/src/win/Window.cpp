#include "Window.h"
#include "Utilities.h" 
#include <Core/src/ccr/GenericTaskQueue.h>
#include <format> 
#include <Core/src/log/Log.h> 
#include <Core/src/utilities/String.h> 

namespace  machine::win {
	Window::Window(std::shared_ptr<IWindowClass> pWindowClass, std::wstring title,
		spa::DimensionsI clientAreaSize, std::optional<spa::Vec2I> position)
		:
		pWindowClass_{ std::move(pWindowClass) },
		kernelThread_{ &Window::MessageKernel_, this }
	{
		auto future = tasks_.Push([=, this] {
			const DWORD styles = WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
			const DWORD exStyles = 0;
			const auto windowDims = ClientToWindowDimensions(clientAreaSize, styles);
			const auto hModule = GetModuleHandleW(nullptr);
			if (!hModule) {
				machinelog.error().hr();
				throw std::bad_function_call();
			}
			hWnd_ = CreateWindowExW(
				exStyles,
				MAKEINTATOM(pWindowClass_->GetAtom()),
				title.c_str(),
				styles,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				windowDims.width, windowDims.height,
				nullptr, nullptr, hModule,
				this
			);
			if (!hWnd_) {
				machinelog.error(L"Failed creating window").hr();
				throw std::bad_function_call();
			}
			});
		startSignal_.release();
		future.get();
	}
	HWND Window::GetHandle() const
	{
		return hWnd_;
	}
	bool Window::IsClosing() const
	{
		return closing_;
	}
	std::future<void> Window::SetTitle(std::wstring title)
	{
		return Dispatch_([=, this] {
			if (!SetWindowTextW(hWnd_, title.c_str())) {
				machinelog.warn(L"Failed setting window title").hr();
			}
			});
	}
	Window::~Window()
	{
		Dispatch_([this] {
			if (!DestroyWindow(hWnd_)) {
				machinelog.warn(L"Failed destroying window").hr();
			}
			});
		kernelThread_.join();
	}
	LRESULT Window::HandleMessage_(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
	{
		try {
			switch (msg) {
			case WM_DESTROY:
				hWnd_ = nullptr;
				PostQuitMessage(0);
				return 0;
			case WM_CLOSE:
				closing_ = true;
				return 0;
			case CustomTaskMessageId:
				tasks_.PopExecute();
				return 0;
			}
		}
		catch (const std::exception& e) {
			machinelog.error(std::format(
				L"Uncaught exception in Windows message handler: {}",
				utilities::ToWide(e.what())
			));
		}
		catch (...) {
			machinelog.error(L"Uncaught annonymous exception in Windows message handler");
		}
		return DefWindowProcW(hWnd, msg, wParam, lParam);
	}
	void Window::NotifyTaskDispatch_() const
	{
		if (!PostMessageW(hWnd_, CustomTaskMessageId, 0, 0)) {
			machinelog.error().hr();
			throw std::bad_function_call();
		}
	}
	void Window::MessageKernel_() noexcept
	{
		startSignal_.acquire();
		tasks_.PopExecute();

		MSG msg{};
		while (GetMessageW(&msg, hWnd_, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
	}
}