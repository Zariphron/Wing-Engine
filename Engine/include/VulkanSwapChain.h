#pragma once


#include <vulkan/vulkan.h>
#include "VulkanStructs.h"
#include "VulkanInstance.h"
#include <vector>
#include <stdexcept>
#include <GLFW/glfw3.h>


class VulkanSwapChain {
public:
    VulkanSwapChain(GLFWwindow* newWindow, VkInstance vulkanInstance);
    ~VulkanSwapChain();

    void createSwapChain();

    void createSurface();
    void pickPhysicalDevice();
    void createLogicalDevice();

    VkQueue getGraphicsQueue() const;
    VkQueue getPresentQueue() const;
    VkSurfaceKHR getSurface() const;
    VkPhysicalDevice getPhysicalDevice() const;
    VkDevice getDevice() const;
    VkSwapchainKHR getSwapChain() const;
    const std::vector<VkImage>& getSwapChainImages() const;
    VkFormat getSwapChainImageFormat() const;
    VkExtent2D getSwapChainExtent() const;
    GLFWwindow* getWindow() const;

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

private:
    

    VkInstance instance;
    GLFWwindow* window;
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VkSurfaceKHR surface;
    VkPhysicalDevice physicalDevice;
    VkDevice device;
    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;

    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    

    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    
    bool isDeviceSuitable(VkPhysicalDevice device);
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
};