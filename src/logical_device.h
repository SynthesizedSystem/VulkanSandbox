#pragma once

#include "physical_device.h"

class LogicalDevice {
 public:
  static LogicalDevice CreateGraphicsLogicalDevice(PhysicalDevice gpu);

  operator VkDevice() const { return logical_device_; }

  LogicalDevice(const LogicalDevice&) = delete;
  LogicalDevice& operator=(const LogicalDevice&) = delete;
  ~LogicalDevice();

 private:
  explicit LogicalDevice(VkDevice logical_device);

  VkDevice logical_device_ = nullptr;
};