#pragma once

#include "physical_device.h"

class LogicalDevice {
 public:
  struct QueueFamily {
    static bool IsQueueFamilySuitable(uint32_t queue_family_type,
                                      VkQueueFamilyProperties queue_family);

    QueueFamily(
        uint32_t queue_family_type,
        const std::vector<VkQueueFamilyProperties>& queue_family_properties);

    VkDeviceQueueCreateInfo GetCreateInfo() const;

    uint32_t type;
    uint32_t index;
    uint32_t count;
  };

  static LogicalDevice CreateLogicalDevice(
      PhysicalDevice gpu, const std::vector<uint32_t>& queue_family_types);

  operator VkDevice() const { return logical_device_; }

  LogicalDevice(const LogicalDevice&) = delete;
  LogicalDevice& operator=(const LogicalDevice&) = delete;
  ~LogicalDevice();

  const QueueFamily& GetQueueFamily(uint32_t type) const;

 private:
  explicit LogicalDevice(VkDevice logical_device,
                         std::vector<QueueFamily>&& queue_families);

  VkDevice logical_device_ = nullptr;
  std::vector<QueueFamily> queue_families_;
};