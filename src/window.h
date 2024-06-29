#pragma once

class Window {
 public:
  static constexpr const char* kName = "Vulkan Sandbox";
  static Ptr<Window> Create();

  operator HWND() const { return window_; }

  explicit Window(HINSTANCE instance, HWND window);
  Window(const Window&) = delete;
  Window(const Window&&) = delete;
  Window& operator=(const Window&) = delete;
  Window& operator=(const Window&&) = delete;
  ~Window();

  static LRESULT WindowProc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam);

  [[nodiscard]] HINSTANCE instance() const { return instance_; }

 private:
  HINSTANCE instance_ = nullptr;
  HWND window_ = nullptr;
};