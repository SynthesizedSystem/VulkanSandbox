#include "physical_device.h"

std::vector<PhysicalDevice> PhysicalDevice::EnumerateDiscreteGPUs(
    const Instance& instance) {
  uint32_t physical_device_count = 0;
  vkEnumeratePhysicalDevices(instance, &physical_device_count, nullptr);

  std::vector<VkPhysicalDevice> physical_devices(physical_device_count);
  vkEnumeratePhysicalDevices(instance, &physical_device_count,
                             physical_devices.data());

  std::vector<PhysicalDevice> discrete_gpus;
  discrete_gpus.reserve(physical_device_count);

  // Filter only discrete GPUs
  for (const auto& device : physical_devices) {
    VkPhysicalDeviceProperties device_properties;
    vkGetPhysicalDeviceProperties(device, &device_properties);
    if (device_properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
      // Vulkan API's Physical Device is emplaced as PhysicalDevice wrapper
      discrete_gpus.emplace_back(device);
    }
  }

  return discrete_gpus;
}

PhysicalDevice PhysicalDevice::GetBestGPU(const Instance& instance) {
  auto discrete_gpus = PhysicalDevice::EnumerateDiscreteGPUs(instance);

  // No discrete GPUs found
  if (discrete_gpus.empty()) {
    return PhysicalDevice(nullptr);
  }

  // Calculate size of each discrete GPU
  std::vector<VkDeviceSize> discrete_gpu_sizes(discrete_gpus.size());
  for (uint32_t i = 0; i < discrete_gpus.size(); ++i) {
    discrete_gpu_sizes[i] = discrete_gpus[i].GetHeapSize();
  }

  // Get index of GPU with the biggest heap. BIGGER = BETTER
  auto best_gpu_index = std::distance(
      discrete_gpu_sizes.begin(),
      std::max_element(discrete_gpu_sizes.begin(), discrete_gpu_sizes.end()));

  return discrete_gpus[best_gpu_index];
}

PhysicalDevice::PhysicalDevice(VkPhysicalDevice physical_device)
    : physical_device_(physical_device) {}

VkDeviceSize PhysicalDevice::GetHeapSize() const {
  VkPhysicalDeviceMemoryProperties device_props;
  vkGetPhysicalDeviceMemoryProperties(physical_device_, &device_props);

  VkDeviceSize total_size = 0;
  for (uint32_t i = 0; i < device_props.memoryHeapCount; ++i) {
    if (device_props.memoryHeaps[i].flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT) {
      total_size += device_props.memoryHeaps[i].size;
    }
  }
  return total_size;
}

PhysicalDevice::QueueFamily PhysicalDevice::GetGraphicsQueueFamily() const {
  uint32_t queue_family_count = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(physical_device_,
                                           &queue_family_count, nullptr);
  std::vector<VkQueueFamilyProperties> queue_family_props(queue_family_count);
  vkGetPhysicalDeviceQueueFamilyProperties(
      physical_device_, &queue_family_count, queue_family_props.data());

  for (uint32_t i = 0; i < queue_family_props.size(); ++i) {
    if (queue_family_props[i].queueFlags &
        VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT) {
      return {.index = i, .count = queue_family_props[i].queueCount};
    }
  }
}
