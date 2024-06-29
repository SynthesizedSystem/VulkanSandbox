#include "surface.h"

Ptr<Surface> Surface::Create(Ptr<Instance> instance, Ptr<Window> window) {
  VkWin32SurfaceCreateInfoKHR surface_info = {
      .sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR,
      .pNext = nullptr,
      .flags = 0,
      .hinstance = window->instance(),
      .hwnd = *window};

  VkSurfaceKHR surface;
  VkResult result =
      vkCreateWin32SurfaceKHR(*instance, &surface_info, nullptr, &surface);
  return std::make_shared<Surface>(instance, surface);
}

Surface::~Surface() { vkDestroySurfaceKHR(*instance_, surface_, nullptr); }

Surface::Surface(Ptr<Instance> instance, VkSurfaceKHR surface)
    : instance_(instance), surface_(surface) {}
