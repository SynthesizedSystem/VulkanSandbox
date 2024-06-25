#include "instance.h"
#include "physical_device.h"
#include "logical_device.h"

int main() {
  Instance instance = Instance::Create();
  PhysicalDevice gpu = PhysicalDevice::GetBestGPU(instance);
  LogicalDevice device = LogicalDevice::CreateGraphicsLogicalDevice(gpu);
  return 0;
}