#include "instance.h"

Ptr<Instance> Instance::Create() {
  VkApplicationInfo app_info = {
      .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
      .pNext = nullptr,
      .pApplicationName = "Tic Tac Toe",
      .applicationVersion = VK_MAKE_API_VERSION(0, 1, 0, 0),
      .pEngineName = "No Engine",
      .engineVersion = VK_MAKE_API_VERSION(0, 1, 0, 0),
      .apiVersion = VK_API_VERSION_1_3};

  std::vector<const char*> extensions{VK_KHR_WIN32_SURFACE_EXTENSION_NAME};
  VkInstanceCreateInfo instance_info = {
      .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0,
      .pApplicationInfo = &app_info,
      .enabledLayerCount = 0,
      .ppEnabledLayerNames = nullptr,
      .enabledExtensionCount = static_cast<uint32_t>(extensions.size()),
      .ppEnabledExtensionNames = extensions.data()};

  VkInstance instance = nullptr;
  VkResult result = vkCreateInstance(&instance_info, nullptr, &instance);
  return std::make_shared<Instance>(instance);
}

Instance::~Instance() { vkDestroyInstance(instance_, nullptr); }

Instance::Instance(VkInstance instance) : instance_(instance) {}
