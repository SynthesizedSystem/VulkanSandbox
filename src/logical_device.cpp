#include "logical_device.h"

LogicalDevice LogicalDevice::CreateGraphicsLogicalDevice(PhysicalDevice gpu) {
  PhysicalDevice::QueueFamily graphics_queue_family =
      gpu.GetGraphicsQueueFamily();

  VkDeviceQueueCreateInfo queue_info = {
      .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0,
      .queueFamilyIndex = graphics_queue_family.index,
      .queueCount = graphics_queue_family.count,
      .pQueuePriorities = nullptr};

  VkDeviceCreateInfo device_info = {
      .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0,
      .queueCreateInfoCount = 1,
      .pQueueCreateInfos = &queue_info,
      .enabledLayerCount = 0,
      .ppEnabledLayerNames = nullptr,
      .enabledExtensionCount = 0,
      .ppEnabledExtensionNames = nullptr,
      .pEnabledFeatures = nullptr};

  VkDevice logical_device;
  vkCreateDevice(gpu, &device_info, nullptr, &logical_device);
  return LogicalDevice(logical_device);
}

LogicalDevice::~LogicalDevice() { vkDestroyDevice(logical_device_, nullptr); }

LogicalDevice::LogicalDevice(VkDevice logical_device)
    : logical_device_(logical_device) {}
