#pragma once


#include "Core/Delegate.h"
#include "Platform/Render/Vulkan/VulkanPipeline.h"
#include "Render/RenderManager.h"
#include <vector>
#include <vulkan/vulkan.h>


/*
Render Pass主导资源声明
Pipeline 需要兼容/依赖 Render Pass 的资源声明
*/
class VulkanRenderPass
{
  private:
    VkDevice         m_logicalDevice        = VK_NULL_HANDLE;
    VkPhysicalDevice m_physicalDevice       = VK_NULL_HANDLE;
    VkFormat         m_swapChainImageFormat = VK_FORMAT_UNDEFINED;
    VkFormat         m_depthFormat          = VK_FORMAT_UNDEFINED;

    VkRenderPass               m_renderPass = VK_NULL_HANDLE;
    std::vector<VkFramebuffer> m_framebuffers;

    VulkanPipelineManager m_pipelineManager;

    RenderPassCreateInfo _ci;

  public:

    Delegate<void()> onRecreated;

  public:
    VulkanRenderPass()  = default;
    ~VulkanRenderPass() = default;

    // Initialize the render pass with device and format information
    void initialize(VkDevice logicalDevice, VkPhysicalDevice physicalDevice, VkFormat swapChainImageFormat, RenderPassCreateInfo renderPassCI);


    // Create the render pass with custom configuration
    void create();

    // Create framebuffers for the render pass
    void createFramebuffers(const std::vector<VkImageView> &swapChainImageViews,
                            VkImageView                     depthImageView,
                            VkExtent2D                      swapChainExtent);

    // Cleanup resources
    void cleanup();

    // Recreate render pass and framebuffers (for swap chain recreation)
    void recreate(const std::vector<VkImageView> &swapChainImageViews,
                  VkImageView                     depthImageView,
                  VkExtent2D                      swapChainExtent);

    // Getters
    VkRenderPass                      getRenderPass() const { return m_renderPass; }
    const std::vector<VkFramebuffer> &getFramebuffers() const { return m_framebuffers; }
    VkFormat                          getDepthFormat() const { return m_depthFormat; }

    // Begin render pass
    void beginRenderPass(VkCommandBuffer commandBuffer, uint32_t frameBufferIndex, VkExtent2D extent);

    // End render pass
    void endRenderPass(VkCommandBuffer commandBuffer);


  private:
    // Find suitable depth format
    VkFormat findDepthFormat();

    // Find supported format from candidates
    VkFormat findSupportedImageFormat(const std::vector<VkFormat> &candidates,
                                      VkImageTiling                tiling,
                                      VkFormatFeatureFlags         features);
};