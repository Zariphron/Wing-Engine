#pragma once

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <vector>
#include <array>
#include "VulkanSwapChain.h"

class SwapChainManager {
public:
    SwapChainManager(VulkanSwapChain& vulkanSwapChain);
    ~SwapChainManager();

    void recreateSwapChain();
    void createImageViews();
    void createDepthResources();
    VkFormat findDepthFormat();
    void createFramebuffers();
    void cleanupSwapChain();

    void setRenderPass(VkRenderPass newRenderPass);

    VulkanSwapChain& vulkanSwapChain;

    std::vector<VkImageView> getSwapChainImageViews();
    std::vector<VkFramebuffer> getSwapChainFramebuffers();

    VkDeviceMemory getDepthImageMemory();
    VkImageView getDepthImageView();
    VkFormat getDepthFormat();
    VkImage getDepthImage();
    VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
    void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);

private:

    VkImage depthImage;
    VkDeviceMemory depthImageMemory;
    VkImageView depthImageView;
    VkFormat depthFormat;

    VkRenderPass renderPass;

    

    // Additional members to store VulkanSwapChain information
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VkSurfaceKHR surface;
    VkPhysicalDevice physicalDevice;
    VkDevice device;
    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<VkImageView> swapChainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;
};