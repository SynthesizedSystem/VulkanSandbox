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

  static Ptr<LogicalDevice> Create(
      Ptr<PhysicalDevice> gpu, const std::vector<uint32_t>& queue_family_types);

  operator VkDevice() const { return logical_device_; }

  explicit LogicalDevice(VkDevice logical_device,
                         const std::vector<QueueFamily>&& queue_families);
  LogicalDevice(const LogicalDevice&) = delete;
  LogicalDevice(const LogicalDevice&&) = delete;
  LogicalDevice& operator=(const LogicalDevice&) = delete;
  LogicalDevice&& operator=(const LogicalDevice&&) = delete;
  ~LogicalDevice();

  const QueueFamily& GetQueueFamily(uint32_t type) const;

 private:
  VkDevice logical_device_ = nullptr;
  std::vector<QueueFamily> queue_families_;
};