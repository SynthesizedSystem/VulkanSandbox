# CMakeList.txt : CMake project for VulkanSandbox, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("VulkanSandbox")

set(SOURCES
  "vulkan_wrappers/instance.h"
  "vulkan_wrappers/instance.cpp"
  "vulkan_wrappers/physical_device.h"
  "vulkan_wrappers/physical_device.cpp"
  "vulkan_wrappers/surface.h"
  "vulkan_wrappers/surface.cpp"
  "vulkan_wrappers/logical_device.h"
  "vulkan_wrappers/logical_device.cpp"
  "window.h"
  "window.cpp"
  "main.cpp"
  "core.h")

set(VULKAN_SDK "C:/VulkanSDK/1.3.283.0")
find_library(Vulkan_LIBRARY NAMES vulkan-1 PATHS ${VULKAN_SDK}/Lib)

add_executable (VulkanSandbox ${SOURCES})
target_precompile_headers(VulkanSandbox PRIVATE "stdafx.h")
target_link_directories(VulkanSandbox PRIVATE "${VULKAN_SDK}/Lib")
target_link_libraries(VulkanSandbox PRIVATE "${Vulkan_LIBRARY}")
target_include_directories(VulkanSandbox PRIVATE "${VULKAN_SDK}/Include" "${CMAKE_SOURCE_DIR}")


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET VulkanSandbox PROPERTY CXX_STANDARD 20)
endif()
