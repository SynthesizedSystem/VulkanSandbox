#include "window.h"

Ptr<Window> Window::Create() {
  HINSTANCE instance = GetModuleHandleA(nullptr);

  WNDCLASSEXA window_class = {.cbSize = sizeof(WNDCLASSEXW),
                              .style = CS_HREDRAW | CS_VREDRAW,
                              .lpfnWndProc = &Window::WindowProc,
                              .cbClsExtra = 0,
                              .cbWndExtra = 0,
                              .hInstance = instance,
                              .hIcon = nullptr,
                              .hCursor = nullptr,
                              .hbrBackground = nullptr,
                              .lpszMenuName = nullptr,
                              .lpszClassName = Window::kName};
  RegisterClassExA(&window_class);

  HWND window =
      CreateWindowExA(0, Window::kName, Window::kName, WS_OVERLAPPEDWINDOW,
                      CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                      CW_USEDEFAULT, nullptr, nullptr, instance, nullptr);

  return std::make_shared<Window>(instance, window);
}

LRESULT Window::WindowProc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam) {
  switch (msg) {
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
    default:
      return DefWindowProcA(wnd, msg, wparam, lparam);
  }
}

Window::~Window() {
  DestroyWindow(window_);
  UnregisterClassA(Window::kName, instance_);
}

Window::Window(HINSTANCE instance, HWND window)
    : instance_(instance), window_(window) {
  ShowWindow(window_, SW_SHOWNORMAL);
}
