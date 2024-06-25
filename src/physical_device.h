#pragma once
#include "instance.h"

class PhysicalDevice {
 public:
  struct QueueFamily {
    uint32_t index;
    uint32_t count;
  };

  // Factory method to enumerate discrete GPUs
  static std::vector<PhysicalDevice> EnumerateDiscreteGPUs(const Instance& instance);
  static PhysicalDevice GetBestGPU(const Instance& instance);

  explicit PhysicalDevice(VkPhysicalDevice physical_device);

  operator VkPhysicalDevice() const { return physical_device_; }

  VkDeviceSize GetHeapSize() const;
  QueueFamily GetGraphicsQueueFamily() const;

 private:
  VkPhysicalDevice physical_device_ = nullptr;
};