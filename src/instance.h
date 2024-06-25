#pragma once

class Instance {
 public:
  static Instance Create();

  operator VkInstance() const { return instance_; }

  Instance(const Instance&) = delete;
  Instance& operator=(const Instance&) = delete;
  ~Instance();

 private:
  explicit Instance(VkInstance instance);

  VkInstance instance_ = nullptr;
};