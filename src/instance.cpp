#include "instance.h"

Instance Instance::Create() {
  VkApplicationInfo app_info = {
      .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
      .pNext = nullptr,
      .pApplicationName = "Tic Tac Toe",
      .applicationVersion = VK_MAKE_API_VERSION(0, 1, 0, 0),
      .pEngineName = "No Engine",
      .engineVersion = VK_MAKE_API_VERSION(0, 1, 0, 0),
      .apiVersion = VK_API_VERSION_1_3};

  VkInstanceCreateInfo instance_info = {
      .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0,
      .pApplicationInfo = &app_info,
      .enabledLayerCount = 0,
      .ppEnabledLayerNames = nullptr,
      .enabledExtensionCount = 0,
      .ppEnabledExtensionNames = nullptr};

  VkInstance instance = nullptr;
  vkCreateInstance(&instance_info, nullptr, &instance);
  return Instance(instance);
}

Instance::~Instance() { vkDestroyInstance(instance_, nullptr); }

Instance::Instance(VkInstance instance) : instance_(instance) {}
