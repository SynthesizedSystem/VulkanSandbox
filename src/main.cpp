#include "instance.h"
#include "logical_device.h"
#include "physical_device.h"

int main() {
  Instance instance = Instance::Create();
  PhysicalDevice gpu = PhysicalDevice::GetBestGPU(instance);

  std::vector<uint32_t> queue_family_types{
      VK_QUEUE_GRAPHICS_BIT, VK_QUEUE_COMPUTE_BIT, VK_QUEUE_TRANSFER_BIT};
  LogicalDevice device =
      LogicalDevice::CreateLogicalDevice(gpu, queue_family_types);

  VkCommandPool command_pool;
  LogicalDevice::QueueFamily transfer_queue_family =
      device.GetQueueFamily(VK_QUEUE_TRANSFER_BIT);
  VkCommandPoolCreateInfo command_pool_info = {
      .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
      .pNext = nullptr,
      .flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT |
               VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
      .queueFamilyIndex = transfer_queue_family.index};
  vkCreateCommandPool(device, &command_pool_info, nullptr, &command_pool);

  VkBuffer buffer;
  VkBufferCreateInfo bci = {.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
                            .pNext = nullptr,
                            .flags = 0,
                            .size = 4,
                            .usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT |
                                     VK_BUFFER_USAGE_TRANSFER_DST_BIT,
                            .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
                            .queueFamilyIndexCount = 0,
                            .pQueueFamilyIndices = nullptr};
  vkCreateBuffer(device, &bci, nullptr, &buffer);

  VkMemoryRequirements memory_requirements;
  vkGetBufferMemoryRequirements(device, buffer, &memory_requirements);

  VkDeviceMemory memory;
  VkMemoryAllocateInfo allocate_info = {
      .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
      .pNext = nullptr,
      .allocationSize = memory_requirements.size,
      .memoryTypeIndex = 1};
  vkAllocateMemory(device, &allocate_info, nullptr, &memory);
  vkBindBufferMemory(device, buffer, memory, 0);

  uint32_t num = 4;
  void* mapped_memory;
  vkMapMemory(device, memory, 0, 4, 0, &mapped_memory);
  memcpy_s(mapped_memory, 4, &num, 4);
  vkUnmapMemory(device, memory);

  VkBuffer dst_buffer;
  VkDeviceMemory dst_memory;
  vkCreateBuffer(device, &bci, nullptr, &dst_buffer);
  vkAllocateMemory(device, &allocate_info, nullptr, &dst_memory);
  vkBindBufferMemory(device, dst_buffer, dst_memory, 0);

  /*void* read_memory;
  vkMapMemory(device, memory, 0, memory_requirements.size, 0, &read_memory);
  std::cout << *reinterpret_cast<uint32_t*>(read_memory) << std::endl;
  vkUnmapMemory(device, memory);*/

  vkFreeMemory(device, memory, nullptr);
  vkDestroyBuffer(device, buffer, nullptr);
  return 0;
}