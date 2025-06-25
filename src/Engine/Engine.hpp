#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "utility.hpp"

#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <map>
#include <iostream>
#include <optional>
#include <set>

#include <cstdint>
#include <limits>
#include <algorithm>
#include "Data.hpp"

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;
	bool isComplete();
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

class Engine {
public:
	bool framebufferResized = false;

	void run();

private:
    // Window
    GLFWwindow* window;
    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;

    // Vulkan Core
    VkInstance instance;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;
    VkQueue graphicsQueue;
    VkSurfaceKHR surface;
	VkQueue presentQueue;

    // Swapchain
    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<VkImageView> swapChainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;

    // Pipeline
    VkRenderPass renderPass;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;

	//descriptor
	VkDescriptorSetLayout descriptorSetLayout;
	VkDescriptorPool descriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;

	// Command Buffers
    VkCommandPool commandPool;
	std::vector<VkCommandBuffer> commandBuffers;
    
	// Synchronization
	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;

    // Validation & Debug
    VkDebugUtilsMessengerEXT debugMessenger;

	// frame
	uint32_t currentFrame = 0;

	//buffer
	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	VkBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;

	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;

	std::vector<VkBuffer> uniformBuffers;
	std::vector<VkDeviceMemory> uniformBuffersMemory;
	std::vector<void*> uniformBuffersMapped;

	//image
	VkImage textureImage;
	VkDeviceMemory textureImageMemory;
	VkImageView textureImageView;
	VkSampler textureSampler;

	// const
	const int MAX_FRAMES_IN_FLIGHT = 2;

	// const std::vector<Vertex> vertices = {
	// 	{{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
	// 	{{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
	// 	{{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
	// 	{{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
	// };

	const std::vector<Vertex> vertices = {
		{{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
		{{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
		{{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
		{{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}
	};

	const std::vector<uint16_t> indices = {
    	0, 1, 2, 2, 3, 0
	};
    
	#ifdef NDEBUG
        const bool enableValidationLayers = false;
    #else
        const bool enableValidationLayers = true;
    #endif

    const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

    const std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

	// Initialization
	void initWindow();
	void initVulkan();
	void createInstance();
	void setupDebugMessenger();
	void createSurface();
	void createVertexBuffer();

	// device
	void pickPhysicalDevice();
	void createLogicalDevice();
	bool isDeviceSuitable(VkPhysicalDevice device);
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	int rateDeviceSuitability(VkPhysicalDevice device);

	// swapchain
	void createSwapChain();
	void recreateSwapChain();
	void cleanupSwapChain();
	void createImageViews();
	void createFramebuffers();
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& formats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& modes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	// Graphics Pipeline
	void createRenderPass();
	void createGraphicsPipeline();
	VkShaderModule createShaderModule(const std::vector<char>& code);

	//  Command Buffers & Sync
	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	void createCommandPool();
	void createCommandBuffers();
	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
	void createSyncObjects();
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	void createIndexBuffer();
	void createUniformBuffers();
	void updateUniformBuffer(uint32_t currentImage);
	VkCommandBuffer beginSingleTimeCommands();
	void endSingleTimeCommands(VkCommandBuffer commandBuffer);

	//descriptor
	void createDescriptorSetLayout();
	void createDescriptorPool();
	void createDescriptorSets();

	//image
	void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
	void createTextureImage();
	void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
	void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
	void createTextureImageView();
	VkImageView createImageView(VkImage image, VkFormat format);
	void createTextureSampler();
	
	// main loop
	void mainLoop();
	void drawFrame();

	// Cleanup
	void cleanup();

	//Validation & Debug
	bool checkValidationLayerSupport();
	std::vector<const char*> getRequiredExtensions();
	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
	void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData)
    {
		std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

		return VK_FALSE;
    }
	
	// other
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
};