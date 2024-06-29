#include "vulkan_wrappers/instance.h"
#include "vulkan_wrappers/logical_device.h"
#include "vulkan_wrappers/physical_device.h"
#include "vulkan_wrappers/surface.h"
#include "window.h"

int main() {
  auto window = Window::Create();

  auto instance = Instance::Create();
  auto surface = Surface::Create(instance, window);
  auto gpu = PhysicalDevice::GetBestGPU(instance);

  std::vector<uint32_t> queue_family_types{
      VK_QUEUE_GRAPHICS_BIT, VK_QUEUE_COMPUTE_BIT, VK_QUEUE_TRANSFER_BIT};
  auto device = LogicalDevice::Create(gpu, queue_family_types);

  MSG msg = {};
  while (msg.message != WM_QUIT) {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    } else {
      // Run your Vulkan rendering code here
    }
  }

  return 0;
}

void foo() {
  /*VkCommandPool command_pool;
  LogicalDevice::QueueFamily transfer_queue_family =
      device.GetQueueFamily(VK_QUEUE_TRANSFER_BIT);
  VkCommandPoolCreateInfo command_pool_info = {
      .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
      .pNext = nullptr,
      .flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT |
               VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
      .queueFamilyIndex = transfer_queue_family.index};
  vkCreateCommandPool(device, &command_pool_info, nullptr, &command_pool);

  VkCommandBuffer command_buffer;
  VkCommandBufferAllocateInfo command_buffer_info = {
      .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
      .pNext = nullptr,
      .commandPool = command_pool,
      .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
      .commandBufferCount = 1};
  vkAllocateCommandBuffers(device, &command_buffer_info, &command_buffer);

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

  VkCommandBufferBeginInfo command_buffer_begin_info = {
      .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
      .pNext = nullptr,
      .flags = 0,
      .pInheritanceInfo = nullptr};
  VkBufferCopy buffer_copy = {.srcOffset = 0, .dstOffset = 0, .size = 4};
  vkBeginCommandBuffer(command_buffer, &command_buffer_begin_info);
  vkCmdCopyBuffer(command_buffer, buffer, dst_buffer, 1, &buffer_copy);
  vkEndCommandBuffer(command_buffer);

  VkSubmitInfo submit_info = {.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
                              .pNext = nullptr,
                              .waitSemaphoreCount = 0,
                              .pWaitSemaphores = nullptr,
                              .pWaitDstStageMask = nullptr,
                              .commandBufferCount = 1,
                              .pCommandBuffers = &command_buffer,
                              .signalSemaphoreCount = 0,
                              .pSignalSemaphores = nullptr};
  VkQueue transfer_queue;
  vkGetDeviceQueue(device, transfer_queue_family.index, 0, &transfer_queue);
  vkQueueSubmit(transfer_queue, 1, &submit_info, nullptr);
  vkQueueWaitIdle(transfer_queue);

  void* read_memory;
  vkMapMemory(device, dst_memory, 0, memory_requirements.size, 0, &read_memory);
  std::cout << *reinterpret_cast<uint32_t*>(read_memory) << std::endl;
  vkUnmapMemory(device, dst_memory);

  vkFreeMemory(device, memory, nullptr);
  vkDestroyBuffer(device, buffer, nullptr);*/
}