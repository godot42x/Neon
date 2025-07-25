#pragma once


#include "Core/Base.h"
#include "Core/Delegate.h"
#include "Platform/Render/Vulkan/VulkanPipeline.h"
#include "Render/RenderManager.h"
#include <vector>
#include <vulkan/vulkan.h>

struct VulkanRender;


/*
Render Pass主导资源声明
Pipeline 需要兼容/依赖 Render Pass 的资源声明
*/
class VulkanRenderPass
{
  private:
    VulkanRender *_render      = nullptr;
    VkRenderPass  m_renderPass = VK_NULL_HANDLE;

    VkFormat m_swapChainImageFormat = VK_FORMAT_UNDEFINED;
    VkFormat m_depthFormat          = VK_FORMAT_UNDEFINED;


    VulkanPipeline m_pipelineManager;

    RenderPassCreateInfo _ci;

  public:
    VulkanRenderPass(VulkanRender *render);
    ~VulkanRenderPass() { cleanup(); }

    // Initialize the render pass with device and format information

    // Create the render pass with custom configuration
    bool create(const RenderPassCreateInfo &ci);

    // Cleanup resources
    void cleanup();

    // Recreate render pass and framebuffers (for swap chain recreation)
    void recreate(const RenderPassCreateInfo &ci);

    // Getters
    [[nodiscard]] VkRenderPass getHandle() const { return m_renderPass; }
    [[nodiscard]] VkFormat     getDepthFormat() const { return m_depthFormat; }


    void begin(VkCommandBuffer commandBuffer, VkFramebuffer framebuffer, VkExtent2D extent, const std::vector<VkClearValue> &clearValues);
    void end(VkCommandBuffer commandBuffer);


  private:

    // Find supported format from candidates
    VkFormat findSupportedImageFormat(const std::vector<VkFormat> &candidates,
                                      VkImageTiling                tiling,
                                      VkFormatFeatureFlags         features);

    bool createDefaultRenderPass();
};