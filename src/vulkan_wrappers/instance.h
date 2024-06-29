#pragma once

class Instance {
 public:
  static Ptr<Instance> Create();

  operator VkInstance() const { return instance_; }

  explicit Instance(VkInstance instance);
  Instance(const Instance&) = delete;
  Instance(const Instance&&) = delete;
  Instance& operator=(const Instance&) = delete;
  Instance&& operator=(const Instance&&) = delete;
  ~Instance();

 private:
  VkInstance instance_ = nullptr;
};