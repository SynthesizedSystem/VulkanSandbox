#include "logical_device.h"

LogicalDevice LogicalDevice::CreateLogicalDevice(
    PhysicalDevice gpu, const std::vector<uint32_t>& queue_family_types) {
  uint32_t queue_family_count = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(gpu, &queue_family_count, nullptr);
  std::vector<VkQueueFamilyProperties> queue_family_properties(
      queue_family_count);
  vkGetPhysicalDeviceQueueFamilyProperties(gpu, &queue_family_count,
                                           queue_family_properties.data());

  std::vector<QueueFamily> queue_families;
  for (const auto& type : queue_family_types) {
    queue_families.emplace_back(type, queue_family_properties);
  }

  std::vector<VkDeviceQueueCreateInfo> queue_family_infos;
  for (const auto& queue_family : queue_families) {
    queue_family_infos.push_back(queue_family.GetCreateInfo());
  }

  VkDeviceCreateInfo device_info = {
      .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0,
      .queueCreateInfoCount = static_cast<uint32_t>(queue_family_infos.size()),
      .pQueueCreateInfos = queue_family_infos.data(),
      .enabledLayerCount = 0,
      .ppEnabledLayerNames = nullptr,
      .enabledExtensionCount = 0,
      .ppEnabledExtensionNames = nullptr,
      .pEnabledFeatures = nullptr};

  VkDevice logical_device;
  VkResult result = vkCreateDevice(gpu, &device_info, nullptr, &logical_device);
  return LogicalDevice(logical_device, std::move(queue_families));
}

LogicalDevice::~LogicalDevice() { vkDestroyDevice(logical_device_, nullptr); }

const LogicalDevice::QueueFamily& LogicalDevice::GetQueueFamily(
    uint32_t type) const {
  for (const auto& queue_family : queue_families_) {
    if (queue_family.type == type) {
      return queue_family;
    }
  }
  return queue_families_[0];
}

LogicalDevice::LogicalDevice(VkDevice logical_device,
                             std::vector<QueueFamily>&& queue_families)
    : logical_device_(logical_device), queue_families_(queue_families) {}

bool LogicalDevice::QueueFamily::IsQueueFamilySuitable(
    uint32_t queue_family_type, VkQueueFamilyProperties queue_family) {
  bool is_bit_set = queue_family.queueFlags & queue_family_type;
  bool is_bit_disabled = !(queue_family.queueFlags & (queue_family_type >> 1));
  return is_bit_set && is_bit_disabled;
}

LogicalDevice::QueueFamily::QueueFamily(
    uint32_t queue_family_type,
    const std::vector<VkQueueFamilyProperties>& queue_family_properties)
    : type(queue_family_type),
      index(std::numeric_limits<uint32_t>::max()),
      count(0) {
  for (uint32_t i = 0; i < queue_family_properties.size(); ++i) {
    if (IsQueueFamilySuitable(type, queue_family_properties[i])) {
      index = i;
      count = queue_family_properties[i].queueCount;
    }
  }
}

VkDeviceQueueCreateInfo LogicalDevice::QueueFamily::GetCreateInfo() const {
  return VkDeviceQueueCreateInfo{
      .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0,
      .queueFamilyIndex = index,
      .queueCount = count,
      .pQueuePriorities = nullptr};
}
