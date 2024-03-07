#pragma once

#include <vulkan/vulkan.h>
#include <stdexcept>
#include <GLFW/glfw3.h>
#include <array>

#include "SwapChainManager.h"

class VulkanDescriptor {
public:
    VulkanDescriptor(VkDevice device, VkFormat swapChainImageFormat, SwapChainManager& swapChainManager);

    ~VulkanDescriptor();

    VkRenderPass getRenderPass() const;

    VkDescriptorSetLayout getDescriptorSetLayout() const;

    void createRenderPass();

    void createDescriptorSetLayout();

private:
    VkDevice device;
    VkFormat swapChainImageFormat;

    SwapChainManager& swapChainManager;

    VkRenderPass renderPass;
    VkDescriptorSetLayout descriptorSetLayout;

    VkFormat findDepthFormat();
};