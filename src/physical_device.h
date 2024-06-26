#pragma once
#include "instance.h"

class PhysicalDevice {
 public:
  // Factory method to enumerate discrete GPUs
  static std::vector<PhysicalDevice> EnumerateDiscreteGPUs(
      const Instance& instance);
  static PhysicalDevice GetBestGPU(const Instance& instance);

  explicit PhysicalDevice(VkPhysicalDevice physical_device);

  operator VkPhysicalDevice() const { return physical_device_; }

  VkDeviceSize GetHeapSize() const;

 private:
  VkPhysicalDevice physical_device_ = nullptr;
  std::vector<VkQueueFamilyProperties> queue_families_;
};