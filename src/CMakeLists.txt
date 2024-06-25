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
  "main.cpp"
 "physical_device.h" "physical_device.cpp" "instance.h" "instance.cpp" "logical_device.h" "logical_device.cpp")

set(VULKAN_SDK "C:/VulkanSDK/1.3.283.0")
include_directories(${VULKAN_SDK}/Include)
link_directories(${VULKAN_SDK}/Lib)

find_library(Vulkan_LIBRARY NAMES vulkan-1 PATHS ${VULKAN_SDK}/Lib)

add_executable (VulkanSandbox  ${SOURCES})
target_precompile_headers(VulkanSandbox PRIVATE "stdafx.h")
target_link_libraries(VulkanSandbox ${Vulkan_LIBRARY})



if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET VulkanSandbox PROPERTY CXX_STANDARD 20)
endif()
