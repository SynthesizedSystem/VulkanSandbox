#pragma once

#include "instance.h"
#include "window.h"

class Surface {
 public:
  static Ptr<Surface> Create(Ptr<Instance> instance, Ptr<Window> window);

  operator VkSurfaceKHR() const { return surface_; }

  explicit Surface(Ptr<Instance> instance, VkSurfaceKHR surface);
  Surface(const Surface&) = delete;
  Surface(const Surface&&) = delete;
  Surface& operator=(const Surface&) = delete;
  Surface&& operator=(const Surface&&) = delete;
  ~Surface();

 private:

  Ptr<Instance> instance_;
  VkSurfaceKHR surface_ = nullptr;
};