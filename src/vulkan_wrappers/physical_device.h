#pragma once
#include "instance.h"

class PhysicalDevice {
 public:
  static std::vector<PhysicalDevice> EnumerateDiscreteGPUs(
      Ptr<Instance> instance);
  static Ptr<PhysicalDevice> GetBestGPU(Ptr<Instance> instance);

  explicit PhysicalDevice(VkPhysicalDevice physical_device);

  operator VkPhysicalDevice() const { return physical_device_; }

  VkDeviceSize GetHeapSize() const;

 private:
  VkPhysicalDevice physical_device_ = nullptr;
  std::vector<VkQueueFamilyProperties> queue_families_;
};