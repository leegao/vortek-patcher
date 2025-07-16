#include <string.h>
#include <jni.h>
#include <vulkan/vulkan.h>
#include <dlfcn.h>
#include <android/log.h>
#include <stdio.h>
#include <__algorithm/find_if.h>
#include <assert.h>
#include <android/log.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <sys/mman.h>

const char* get_vulkan_call_name(int command_id) {
    switch (command_id) {
        case 0x67: return "vkGetPhysicalDeviceProperties";
        case 0x68: return "vkGetPhysicalDeviceQueueFamilyProperties";
        case 0x69: return "vkGetPhysicalDeviceMemoryProperties";
        case 0x6a: return "vkGetPhysicalDeviceFeatures";
        case 0x6b: return "vkGetPhysicalDeviceFormatProperties";
        case 0x6c: return "vkGetPhysicalDeviceImageFormatProperties";
        case 0x6d: return "vkCreateDevice";
        case 0x6e: return "vkDestroyDevice";
        case 0x6f: return "vkEnumerateInstanceVersion";
        case 0x71: return "vkEnumerateInstanceExtensionProperties";
        case 0x73: return "vkEnumerateDeviceExtensionProperties";
        case 0x74: return "vkGetDeviceQueue";
        case 0x75: return "vkQueueSubmit";
        case 0x76: return "vkQueueWaitIdle";
        case 0x77: return "vkDeviceWaitIdle";
        case 0x78: return "vkAllocateMemory";
        case 0x79: return "vkFreeMemory";
        case 0x7a: return "vkMapMemory";
        case 0x7b: return "vkUnmapMemory";
        case 0x7c: return "vkFlushMappedMemoryRanges";
        case 0x7d: return "vkInvalidateMappedMemoryRanges";
        case 0x7e: return "vkGetDeviceMemoryCommitment";
        case 0x7f: return "vkGetBufferMemoryRequirements";
        case 0x80: return "vkBindBufferMemory";
        case 0x81: return "vkGetImageMemoryRequirements";
        case 0x82: return "vkBindImageMemory";
        case 0x83: return "vkGetImageSparseMemoryRequirements";
        case 0x84: return "vkGetPhysicalDeviceSparseImageFormatProperties";
        case 0x85: return "vkQueueBindSparse";
        case 0x86: return "vkCreateFence";
        case 0x87: return "vkDestroyFence";
        case 0x88: return "vkResetFences";
        case 0x89: return "vkGetFenceStatus";
        case 0x8a: return "vkWaitForFences";
        case 0x8b: return "vkCreateSemaphore";
        case 0x8c: return "vkDestroySemaphore";
        case 0x8d: return "vkCreateEvent";
        case 0x8e: return "vkDestroyEvent";
        case 0x8f: return "vkGetEventStatus";
        case 0x90: return "vkSetEvent";
        case 0x91: return "vkResetEvent";
        case 0x92: return "vkCreateQueryPool";
        case 0x93: return "vkDestroyQueryPool";
        case 0x94: return "vkGetQueryPoolResults";
        case 0x95: return "vkResetQueryPool";
        case 0x96: return "vkCreateBuffer";
        case 0x97: return "vkDestroyBuffer";
        case 0x98: return "vkCreateBufferView";
        case 0x99: return "vkDestroyBufferView";
        case 0x9a: return "vkCreateImage";
        case 0x9b: return "vkDestroyImage";
        case 0x9c: return "vkGetImageSubresourceLayout";
        case 0x9d: return "vkCreateImageView";
        case 0x9e: return "vkDestroyImageView";
        case 0x9f: return "vkCreateShaderModule";
        case 0xa0: return "vkDestroyShaderModule";
        case 0xa1: return "vkCreatePipelineCache";
        case 0xa2: return "vkDestroyPipelineCache";
        case 0xa3: return "vkGetPipelineCacheData";
        case 0xa4: return "vkMergePipelineCaches";
        case 0xa5: return "vkCreateGraphicsPipelines";
        case 0xa6: return "vkCreateComputePipelines";
        case 0xa7: return "vkDestroyPipeline";
        case 0xa8: return "vkCreatePipelineLayout";
        case 0xa9: return "vkDestroyPipelineLayout";
        case 0xaa: return "vkCreateSampler";
        case 0xab: return "vkDestroySampler";
        case 0xac: return "vkCreateDescriptorSetLayout";
        case 0xad: return "vkDestroyDescriptorSetLayout";
        case 0xae: return "vkCreateDescriptorPool";
        case 0xaf: return "vkDestroyDescriptorPool";
        case 0xb0: return "vkResetDescriptorPool";
        case 0xb1: return "vkAllocateDescriptorSets";
        case 0xb2: return "vkFreeDescriptorSets";
        case 0xb3: return "vkUpdateDescriptorSets";
        case 0xb4: return "vkCreateFramebuffer";
        case 0xb5: return "vkDestroyFramebuffer";
        case 0xb6: return "vkCreateRenderPass";
        case 0xb7: return "vkDestroyRenderPass";
        case 0xb8: return "vkGetRenderAreaGranularity";
        case 0xb9: return "vkCreateCommandPool";
        case 0xba: return "vkDestroyCommandPool";
        case 0xbb: return "vkResetCommandPool";
        case 0xbc: return "vkAllocateCommandBuffers";
        case 0xbd: return "vkFreeCommandBuffers";
        case 0xbe: return "vkBeginCommandBuffer";
        case 0xbf: return "vkEndCommandBuffer";
        case 0xc0: return "vkResetCommandBuffer";
        case 0xc1: return "vkCmdBindPipeline";
        case 0xc2: return "vkCmdSetViewport";
        case 0xc3: return "vkCmdSetScissor";
        case 0xc4: return "vkCmdSetLineWidth";
        case 0xc5: return "vkCmdSetDepthBias";
        case 0xc6: return "vkCmdSetBlendConstants";
        case 0xc7: return "vkCmdSetDepthBounds";
        case 0xc8: return "vkCmdSetStencilCompareMask";
        case 0xc9: return "vkCmdSetStencilWriteMask";
        case 0xca: return "vkCmdSetStencilReference";
        case 0xcb: return "vkCmdBindDescriptorSets";
        case 0xcc: return "vkCmdBindIndexBuffer";
        case 0xcd: return "vkCmdBindVertexBuffers";
        case 0xce: return "vkCmdDraw";
        case 0xcf: return "vkCmdDrawIndexed";
        case 0xd0: return "vkCmdDrawIndirect";
        case 0xd1: return "vkCmdDrawIndexedIndirect";
        case 0xd2: return "vkCmdDispatch";
        case 0xd3: return "vkCmdDispatchIndirect";
        case 0xd4: return "vkCmdCopyBuffer";
        case 0xd5: return "vkCmdCopyImage";
        case 0xd6: return "vkCmdBlitImage";
        case 0xd7: return "vkCmdCopyBufferToImage";
        case 0xd8: return "vkCmdCopyImageToBuffer";
        case 0xd9: return "vkCmdUpdateBuffer";
        case 0xda: return "vkCmdFillBuffer";
        case 0xdb: return "vkCmdClearColorImage";
        case 0xdc: return "vkCmdClearDepthStencilImage";
        case 0xdd: return "vkCmdClearAttachments";
        case 0xde: return "vkCmdResolveImage";
        case 0xdf: return "vkCmdSetEvent";
        case 0xe0: return "vkCmdResetEvent";
        case 0xe2: return "vkCmdPipelineBarrier";
        case 0xe3: return "vkCmdBeginQuery";
        case 0xe4: return "vkCmdEndQuery";
        case 0xe5: return "vkCmdBeginConditionalRenderingEXT";
        case 0xe6: return "vkCmdEndConditionalRenderingEXT";
        case 0xe7: return "vkResetQueryPool";
        case 0xe8: return "vkCmdWriteTimestamp";
        case 0xe9: return "vkCmdCopyQueryPoolResults";
        case 0xea: return "vkCmdPushConstants";
        case 0xeb: return "vkCmdBeginRenderPass";
        case 0xec: return "vkCmdNextSubpass";
        case 0xed: return "vkCmdEndRenderPass";
        case 0xee: return "vkCmdExecuteCommands";
        case 0xf0: return "vkGetPhysicalDeviceSurfaceCapabilitiesKHR";
        case 0xf1: return "vkGetPhysicalDeviceSurfaceFormatsKHR";
        case 0xf2: return "vkGetPhysicalDeviceSurfacePresentModesKHR";
        case 0xf3: return "vkCreateSwapchainKHR";
        case 0xf4: return "vkDestroySwapchainKHR";
        case 0xf5: return "vkGetSwapchainImagesKHR";
        case 0xf6: return "vkAcquireNextImageKHR";
        case 0xf7: return "vkQueuePresentKHR";
        case 0xf8: return "vkGetPhysicalDeviceFeatures2";
        case 0xf9: return "vkGetPhysicalDeviceProperties2";
        case 0xfa: return "vkGetPhysicalDeviceFormatProperties2";
        case 0xfb: return "vkGetPhysicalDeviceImageFormatProperties2";
        case 0xfc: return "vkGetPhysicalDeviceQueueFamilyProperties2";
        case 0xfd: return "vkGetPhysicalDeviceMemoryProperties2";
        case 0xfe: return "vkGetPhysicalDeviceSparseImageFormatProperties2";
        case 0xff: return "vkUpdateDescriptorSetWithTemplate / vkCmdPushDescriptorSetWithTemplateKHR";
        case 0x100: return "vkTrimCommandPool";
        case 0x10a: return "vkEnumeratePhysicalDeviceGroups";
        case 0x10e: return "vkCmdSetDeviceMask";
        case 0x112: return "vkCmdDispatchBase";
        case 0x114: return "vkCmdSetSampleLocationsEXT";
        case 0x115: return "vkGetPhysicalDeviceMultisamplePropertiesEXT";
        case 0x116: return "vkGetDeviceBufferMemoryRequirements";
        case 0x117: return "vkGetDeviceImageMemoryRequirements";
        case 0x118: return "vkGetImageSparseMemoryRequirements2";
        case 0x119: return "vkGetBufferMemoryRequirements2";
        case 0x11a: return "vkGetDeviceImageMemoryRequirements2";
        case 0x11b: return "vkGetImageSparseMemoryRequirements2";
        case 0x11c: return "vkCreateSamplerYcbcrConversion";
        case 0x11d: return "vkDestroySamplerYcbcrConversion";
        case 0x11e: return "vkGetDeviceQueue2";
        case 0x11f: return "vkGetDescriptorSetLayoutSupport";
        case 0x120: return "vkCreateRenderPass2";
        case 0x121: return "vkCmdBeginRenderPass2";
        case 0x122: return "vkCmdNextSubpass2";
        case 0x123: return "vkCmdEndRenderPass2";
        case 0x125: return "vkWaitSemaphores";
        case 0x127: return "vkCmdDrawIndirectCount";
        case 0x128: return "vkCmdDrawIndexedIndirectCount";
        case 0x129: return "vkCmdBindTransformFeedbackBuffersEXT";
        case 0x12a: return "vkCmdBeginTransformFeedbackEXT";
        case 0x12b: return "vkCmdEndTransformFeedbackEXT";
        case 0x12c: return "vkCmdBeginQueryIndexedEXT";
        case 0x12d: return "vkCmdEndQueryIndexedEXT";
        case 0x12e: return "vkCmdDrawIndirectByteCountEXT";
        case 0x12f: return "vkGetBufferOpaqueCaptureAddress";
        case 0x130: return "vkGetBufferDeviceAddress";
        case 0x131: return "vkGetDeviceMemoryOpaqueCaptureAddress";
        case 0x132: return "vkCmdSetLineStippleEXT";
        case 0x134: return "vkCmdSetCullMode";
        case 0x135: return "vkCmdSetFrontFace";
        case 0x136: return "vkCmdSetPrimitiveTopology";
        case 0x137: return "vkCmdSetViewportWithCount";
        case 0x138: return "vkCmdSetScissorWithCount";
        case 0x139: return "vkCmdBindVertexBuffers2";
        case 0x13a: return "vkCmdSetDepthTestEnable";
        case 0x13b: return "vkCmdSetDepthWriteEnable";
        case 0x13c: return "vkCmdSetDepthCompareOp";
        case 0x13d: return "vkCmdSetDepthBoundsTestEnable";
        case 0x13e: return "vkCmdSetStencilTestEnable";
        case 0x13f: return "vkCmdSetStencilOp";
        case 0x140: return "vkCmdSetRasterizerDiscardEnable";
        case 0x141: return "vkCmdSetDepthBiasEnable";
        case 0x142: return "vkCmdSetPrimitiveRestartEnable";
        case 0x143: return "vkCmdCopyBuffer2";
        case 0x144: return "vkCmdCopyImage2";
        case 0x145: return "vkCmdBlitImage2";
        case 0x146: return "vkCmdCopyBufferToImage2";
        case 0x147: return "vkCmdCopyImageToBuffer2";
        case 0x148: return "vkCmdResolveImage2";
        case 0x149: return "vkCmdSetColorWriteEnableEXT";
        case 0x14a: return "vkCmdSetEvent2";
        case 0x14b: return "vkCmdResetEvent2";
        case 0x14c: return "vkCmdWaitEvents2";
        case 0x14d: return "vkCmdPipelineBarrier2";
        case 0x14e: return "vkQueueSubmit2";
        case 0x14f: return "vkCmdWriteTimestamp2";
        case 0x150: return "vkCmdBeginRendering";
        case 0x151: return "vkCmdEndRendering";
        case 0x152: return "vkCreateDescriptorUpdateTemplate";
        case 0x153: return "vkDestroyDescriptorUpdateTemplate";
        default:
            return "Unknown Command ID";
    }
}

extern "C" int __system_property_get(const char *name, char *value);

#define TAG "VortekPatch"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)

int is_enabled(const char* property, const char* env) {
    char value[256] = { 0 };
    if (__system_property_get(property, value) > 0) {
        return true;
    }
    const char* env_value = getenv(env);
    LOGI("is_enabled flag:%s, value:%s", env, env_value);
    if (!env_value) return false;
    return *env_value == '1';
}

typedef struct { char _p[0x27]; void* task_queue; } TextureDecoder;

typedef struct {
    char _p[0xC];
    int32_t width;
    int32_t height;
    char _p2[0xC];
    void* pixel_data_buffer;
} TaskImageParams;

typedef struct {
    int fd;
    char _p[0x24];
    size_t length;
} MmapInfo;

typedef struct {
    VkBuffer         buffer;         // 0x00: The Vulkan buffer handle.
    VkDeviceSize     offset;         // 0x08: The offset into the device memory where the buffer is bound.
    MmapInfo*        mmap_details;
} TaskDataSource;

struct ImageObject {
    VkImage        handle;        // 0x00: The Vulkan image handle (Assumed).
    VkFormat       format;        // 0x08: The format of the image.
    int32_t        width;         // 0x0c: The width of the image.
    int32_t        height;        // 0x10: The height of the image.
    int32_t        layerCount;    // 0x14: The number of layers in the image.
    uint32_t       _pad_0x18;
    uint32_t       _pad_0x1c;
    VkDeviceMemory memory;        // 0x20: The device memory bound to this image.
    VkDeviceSize   size;          // 0x28: The size of the bound memory (Assumed for munmap).
}; // Size >= 0x30

typedef struct {
    TaskDataSource* data_source;
    ImageObject* image_params;
} DecodingTask;

typedef struct ArrayDeque {
    int head;
    int tail;
    unsigned int capacity;
    unsigned int _padding;
    void** elements;
} ArrayDeque;

typedef struct VtContext {
    /* 0x00 */ int socket_fd;                                    // Socket file descriptor for IPC with the client.
    /* 0x04 */ uint32_t vkMaxVersion;                             // The maximum Vulkan API version supported by the client.
    /* 0x08 */ uint16_t maxDeviceMemory;                          // Memory limit in GB, from Java.
    /* 0x0a */ uint16_t imageCacheSize;                           // Image cache size limit in MB, from Java.
    /* 0x10 */ void* exposedDeviceExtensions;                    // ArrayList of device extension strings to expose.
    /* 0x18 */ void* exposedInstanceExtensions;                  // ArrayList of instance extension strings to expose.
    /* 0x20 */ bool isHostVisibleExternalMemoryImportSupported;               // Flag indicating if DMA_BUF with HOST_VISIBLE is supported.
    /* 0x21 */ bool isDmaBufImportExportSupported;           // Flag indicating if AndroidHardwareBuffer is supported.
    /* 0x22 */ short field_0x22_padding;                     // Padding.
    /* 0x24 */ int field_0x24_padding;                     // Padding.
    /* 0x28 */ void* pRequestData;                               // Pointer to the current command's data buffer.
    /* 0x30 */ int requestDataSize;                              // Size of the data pointed to by pRequestData.
    /* 0x34 */ int field_0x34_padding;                     // Padding.
    /* 0x38 */ void* tempBuffer;                                 // Arena allocator buffer for temporary command data.
    /* 0x40 */ int tempBufferOffset;                             // Current offset within the tempBuffer.
    /* 0x44 */ int field_0x44_padding;                     // Padding.
    /* 0x48 */ void* tempAllocations;                            // ArrayList tracking temporary allocations to be freed.
    /* 0x50 */ uint64_t field_0x50_padding;                     // Padding.
    /* 0x58 */ pthread_t workerThread;                           // Handle for the main worker thread processing commands.
    /* 0x60 */ void* serverRingBuffer;                           // RingBuffer for server-to-client communication.
    /* 0x68 */ void* clientRingBuffer;                           // RingBuffer for client-to-server communication.
    /* 0x70 */ int contextStatus;                                // Overall context status (e.g., VK_ERROR_DEVICE_LOST).
    /* 0x74 */ int graphicsQueueFamilyIndex;                     // The queue family index that supports graphics operations.
    /* 0x78 */ void* textureDecoder;                             // Pointer to the TextureDecoder context.
    /* 0x80 */ void* shaderInspector;                            // Pointer to the ShaderInspector context.
    /* 0x88 */ void* asyncPipelineCreator;                       // Pointer to the AsyncPipelineCreator context.
    /* 0x90 */ void* jniEnv;                                     // JNI Environment pointer.
    /* 0x98 */ void* javaRendererComponent;                      // JNI jobject reference to the VortekRendererComponent.
    /* 0xa0 */ void* getWindowWidth_id;                          // jmethodID for getWindowWidth.
    /* 0xa8 */ void* getWindowHeight_id;                         // jmethodID for getWindowHeight.
    /* 0xb0 */ void* getWindowHardwareBuffer_id;                 // jmethodID for getWindowHardwareBuffer.
    /* 0xb8 */ void* updateWindowContent_id;                     // jmethodID for updateWindowContent.
    /* 0xc0 */ uint64_t field_0xc0_padding;                     // Padding to 200 bytes.
} VtContext;

static_assert(offsetof(VtContext, field_0xc0_padding) == 0xc0);
static_assert(offsetof(VtContext, pRequestData) == 0x28);
static_assert(offsetof(VtContext, requestDataSize) == 0x30);

static void (*original_TextureDecoder_decodeAll)(void* self);
static void (*original_vt_handle_vkCmdCopyBufferToImage)(void* ctx);
static void (*original_vt_handle_vkCmdCopyBufferToImage2)(void* ctx);
static void (*original_vt_handle_vkEndCommandBuffer)(void* ctx);

static long (*old_Java_com_winlator_xenvironment_components_VortekRendererComponent_createVkContext)(JNIEnv* env, jobject thiz, int fd, jobject options);
static int (*ArrayDeque_isEmpty)(void* deque);
static void* (*ArrayDeque_removeFirst)(void* deque);
static void (*ArrayDeque_addLast)(void* deque, void* element);
static void (*ArrayDeque_init)(void* deque, uint);
static void* (*VkObject_fromId)(void*);
static bool (*TextureDecoder_containsImage)(void*,VkImage);
static void (*TextureDecoder_copyBufferToImage)(void*, VkCommandBuffer                             commandBuffer,
                                           VkBuffer                                    srcBuffer,
                                           VkImage                                     dstImage,
                                           VkImageLayout                               dstImageLayout);

static ArrayDeque image_regions;

#define HOOK(name, ret, params) \
static ret (*original_##name) params; \
ret my_##name params

HOOK(getHandleRequestFunc, void*, (unsigned short op)) {
    // if (op == 0x147 || op == 0xbf || op == 0xd8)
    LOGI("Handling command: %d (%s)", op, get_vulkan_call_name(op));
    return original_getHandleRequestFunc(op);
}

HOOK(initVulkanInstance, void, (long param_1,void* param_2,char *param_3,void* param_4,
                       void* param_5,void* param_6,void* param_7,void* param_8)) {
    LOGI("Inside my_initVulkanInstance");
    original_initVulkanInstance(param_1, param_2, param_3, param_4, param_5, param_6, param_7, param_8);
}

typedef struct ShaderModuleInfo {
    VkShaderModule vkShaderModule;  // The Vulkan handle for the compiled shader module.
                                    // Stored at offset 0x00.
    void*          pShaderCode;     // Pointer to the raw SPIR-V or binary shader code data.
                                    // This memory is dynamically allocated and copied.
                                    // Stored at offset 0x08.
    size_t         shaderCodeSize;  // The size of the raw shader code data in bytes.
                                    // Stored at offset 0x10.
    // Based on assembly, the total size of this struct is 0x20 bytes (32 bytes).
    // The remaining 8 bytes after `shaderCodeSize` are used for internal flags.
    bool           isValid;                  // A flag indicating if the shader module creation was successful.
                                    // Set to 0 (false) initially, then potentially to 1 (true) on success.
                                    // Stored at offset 0x18 (byte 0).
    bool           isOwnedByShaderInspector; // A flag likely indicating if this ShaderModuleInfo instance
                                    // and its associated pShaderCode should be freed by the ShaderInspector.
                                    // Stored at offset 0x19 (byte 1).
    char           _padding[6];     // Padding bytes to ensure struct size is 0x20 bytes (32 bytes)
} ShaderModuleInfo;

typedef struct ShaderInspector {
    /* 0x00 */ bool noShaderClipDistance;        // True if VK_KHR_shader_clip_distance is NOT supported (or explicitly disabled).
                                                      // Derived from VkPhysicalDeviceFeatures::shaderClipDistance.
    /* 0x01 */ bool noScaledVertexBufferConversion; // True if VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT is NOT supported for VK_FORMAT_R8G8B8A8_SSCALED.
                                                      // Indicates if a fallback for scaled vertex buffer formats is needed.
    /* 0x02 */ bool isMaliDevice;                     // True if "Mali" substring is found in the physical device name.
    /* 0x03 */ bool initialized;                      // Always true; indicates the struct has been initialized.
} ShaderInspector;


HOOK(ShaderInspector_inspectShaderStages, VkResult, 
    (ShaderInspector *param_1,void* param_2,long param_3,uint param_4,VkPipelineVertexInputStateCreateInfo* param_5,long param_6,
              void* param_7,void* param_8)) {
    LOGI("Inside ShaderInspector_inspectShaderStages");
    LOGI("  + noShaderClipDistance = %d", param_1->noShaderClipDistance);
    LOGI("  + noScaledVertexBufferConversion = %d", param_1->noScaledVertexBufferConversion);
    LOGI("  + isMaliDevice = %d", param_1->isMaliDevice);
    LOGI("  + initialized = %d", param_1->initialized);
    // param_1->noScaledVertexBufferConversion = 0;
    LOGI("param_5: %p", param_5);
    LOGI("  + sType: %x", param_5->sType);
    LOGI("  + pNext: %p", param_5->pNext);
    LOGI("  + flags: %x", param_5->flags);
    LOGI("  + vertexBindingDescriptionCount: %d", param_5->vertexBindingDescriptionCount);
    LOGI("  + pVertexBindingDescriptions: %p", param_5->pVertexBindingDescriptions);
    LOGI("  + vertexAttributeDescriptionCount: %d", param_5->vertexAttributeDescriptionCount);
    LOGI("  + pVertexAttributeDescriptions: %p", param_5->pVertexAttributeDescriptions);
    return original_ShaderInspector_inspectShaderStages(param_1, param_2, param_3, param_4, param_5, param_6, param_7, param_8);
}

HOOK(ShaderInspector_createModule, void*,
               (ShaderInspector* si, VkDevice device, const uint32_t *spirv, size_t spirvSize, ShaderModuleInfo **out)) {
    LOGI("Inside ShaderInspector_createModule");
    return original_ShaderInspector_createModule(si, device, spirv, spirvSize, out);
}

extern "C"
void my_vt_handle_vkEndCommandBuffer(VtContext* ctx) {
    // Log every command on the buffer
// #define GET(x) (*(void**)(x))
//     char* context = (char*) ctx;
//     uint8_t* commandBuffer = (uint8_t*) GET(context + 0x28);  // offset 0x50
//     int totalBufferSize = (long) GET(context + 0x30);  // offset 0x58

//     // Process commands if buffer has more than 8 bytes
//     if (totalBufferSize > 8) {
//         LOGI("Inside vt_handle_vkEndCommandBuffer with totalBufferSize: %d", totalBufferSize);
//         int currentOffset = 8;  // Skip the initial 8-byte header
//         do {
//             // Get pointer to current command
//             auto commandPtr = (uint32_t*)(commandBuffer + currentOffset);
//             // Read command ID and size
//             auto commandId = commandPtr[0];
//             auto commandSize = commandPtr[1];
//             LOGI("  + commandId: %d (%s), commandSize: %d", commandId, get_vulkan_call_name(commandId), commandSize);
//             // Move to next command (skip command header + command data)
//             currentOffset += commandSize + 8;
//         } while (currentOffset < totalBufferSize);
//     }

    original_vt_handle_vkEndCommandBuffer(ctx);
}

#define TASK_QUEUE(self) (&((char*)self)[0x28])
#define TASK_DEVICE(self) (*(VkDevice*)&((char*)self)[0x00])

// Intercepts vkCreateInstance _between_ Vortek and the underlying libvulkan.so
// and inject a single VK_LAYER_KHRONOS_validation layer
extern "C"
VkResult my_vkCreateInstance(
        VkInstanceCreateInfo*                 pCreateInfo,
        const VkAllocationCallbacks*          pAllocator,
        VkInstance*                           pInstance) {
    LOGI("Inside of my_vkCreateInstance.");

    void *libVulkan = dlopen("libvulkan.so", RTLD_NOW);
    PFN_vkCreateInstance original_vkCreateInstance_ptr = (PFN_vkCreateInstance) dlsym(
            libVulkan, "vkCreateInstance");

    // Enable just the VK_LAYER_LUNARG_api_dump layer.
    static const char *layers[] = {"VK_LAYER_LUNARG_api_dump"};

    // Get the layer count using a null pointer as the last parameter.
    uint32_t instance_layer_present_count = 0;
    vkEnumerateInstanceLayerProperties(&instance_layer_present_count, nullptr);

    // Enumerate layers with a valid pointer in the last parameter.
    VkLayerProperties layer_props[instance_layer_present_count];
    vkEnumerateInstanceLayerProperties(&instance_layer_present_count, layer_props);

    for (const VkLayerProperties layerProperties: layer_props) {
        LOGI("Layer found: %s\n%s", layerProperties.layerName, layerProperties.description);
    }

    // Set the validation layer
    // TODO: inherit the existing layers
    pCreateInfo->enabledLayerCount = 1;
    pCreateInfo->ppEnabledLayerNames = layers;

    return original_vkCreateInstance_ptr(pCreateInfo, pAllocator, pInstance);
}

// Get the base address of libvortekrenderer.so to patch the actual GOT tables (not available via
// dlsym)
void* findLibraryBase(const std::string& library_name) {
    std::ifstream maps_file("/proc/self/maps");
    if (!maps_file.is_open()) {
        LOGE("Could not open /proc/self/maps");
        return nullptr;
    }

    std::string line;
    while (std::getline(maps_file, line)) {
        // Check if the line contains the library name
        if (line.find(library_name) != std::string::npos) {
            LOGI("Map: %s", line.c_str());
            // A typical line looks like:
            // 7b1edc6000-7b1edc7000 r--p 00000000 103:0c 536  /path/to/lib.so
            uintptr_t base_address;
            // Use sscanf to parse the starting address
            if (sscanf(line.c_str(), "%lx-%*lx", &base_address) == 1) {
                return (void*) base_address;
            }
        }
    }

    return nullptr;
}

int patch_got(char* base_addr, long offset, void** original, void* next) {
    void** got_entry = (void**) &base_addr[offset];
    if (*original == *got_entry || *got_entry == next) {
        LOGI("Not patching - GOT already points to next. *got: %p, *original: %p, next: %p", *got_entry, *original, next);
        return 0;
    } else {
        *original = *got_entry;
    }

    long page_size = sysconf(_SC_PAGESIZE);
    if (page_size == -1) {
        perror("sysconf");
        return -1;
    }

    void *page_start = (void *)(((uintptr_t) got_entry) & ~(page_size - 1));
    mprotect(page_start, page_size, PROT_READ | PROT_WRITE);
    *got_entry = (void*) next;

    LOGI("Patching %p+%lx from %p to %p", base_addr, offset, *original, next);
    // TODO: reset the protection bits
    return 0;
}

extern "C"
JNIEXPORT long Java_com_winlator_xenvironment_components_VortekRendererComponent_createVkContext(JNIEnv* env, jobject thiz, int fd, jobject options){
    LOGI("Inside of VortekRendererComponent::createVkContext.");

    void* libvortekrenderer = dlopen("libvortekrenderer.so", RTLD_NOW);
#define SAVE(obj) *((void**)&obj) = dlsym(libvortekrenderer, #obj)

    // Call the original VortekRendererComponent::createVkContext first to set up the vulkanWrapper pointers
    SAVE(old_Java_com_winlator_xenvironment_components_VortekRendererComponent_createVkContext);
    long result = old_Java_com_winlator_xenvironment_components_VortekRendererComponent_createVkContext(env, thiz, fd, options);

    LOGI("Result: %ld", result);

    // int enable_logging = is_enabled("debug.vt.logging", "VT_LOGGING");
    int enable_dump_api = is_enabled("debug.vt.dump_api", "VT_DUMP");

    char* base_addr = (char*) findLibraryBase("libvortekrenderer.so");
#define GOT(func, addr) \
    patch_got(base_addr, addr, (void**) &original_##func, (void*) &my_##func)
    // 0000000482a8  010c00000402 R_AARCH64_JUMP_SL 000000000003264c initVulkanInstance + 0
    // 000000048310  00cb00000402 R_AARCH64_JUMP_SL 0000000000033b10 initVulkanDevice + 0
    GOT(initVulkanInstance, 0x482a8);
    // 0000000000048620  000000b100000402 R_AARCH64_JUMP_SLOT    0000000000041f64 ShaderInspector_inspectShaderStages + 0
    GOT(ShaderInspector_inspectShaderStages, 0x48620);
    // 0000000000048388  0000013500000402 R_AARCH64_JUMP_SLOT    0000000000041cbc ShaderInspector_createModule + 0
    GOT(ShaderInspector_createModule, 0x48388);
    // if (enable_logging)
    //     patch_got(base_addr, 0x484e0,
    //               (void**) &original_getHandleRequestFunc,
    //               (void*) &my_getHandleRequestFunc);

    // Calculate the actual address of the cache vkCreateInstance pointer within Vortek
    void* vulkanWrapper = dlsym(libvortekrenderer, "vulkanWrapper");
    // The vkCreateInstance pointer is at offset 0x18 from wrapper base
    // e388: str    x0, [x23, #0x18] ; stores the vkCreateInstance symbol from libvulkan at +0x18
    // .text:0010f464  c1ffffd0        adrp        param_2,0x109000                        
    // .text:0010f468  21f00e91        add         param_2=>...,param_2,#0x3bc             ;= "vkCreateInstance"
    // .text:0010f46c  f80300aa        mov         x24,param_1                             
    // .text:0010f470  a0d80094        bl          .plt:<EXTERNAL>::dlsym                  ;undefined dlsym()
    // .text:0010f474  c1ffffb0        adrp        param_2,0x108000                        
    // .text:0010f478  e00e00f9        str         param_1,[x23, #0x18]=>.bss:DAT_00149018 ;= ?? <--
    if (enable_dump_api)
        *(void**)((char*)vulkanWrapper + 0x18) = (void*) &my_vkCreateInstance;

    // Patch the command dispatch in the GOT
    //   Index for vkCmdCopyImageToBuffer (opcode 0xd8) is 216, but minus 100 for the dispatch table
    void** handleRequestFuncs = (void**) dlsym(libvortekrenderer, "handleRequestFuncs");

#define PATCH(sym, index) { \
    *((void**)&original_##sym) = (void*) handleRequestFuncs[index - 100]; \
    handleRequestFuncs[index - 100] = (void*) &my_##sym; }

    // if (enable_logging)
    //     PATCH(vt_handle_vkEndCommandBuffer, 0xbf);

    SAVE(VkObject_fromId);
    SAVE(TextureDecoder_containsImage);
    SAVE(TextureDecoder_copyBufferToImage);
    SAVE(ArrayDeque_init);
    SAVE(ArrayDeque_isEmpty);
    SAVE(ArrayDeque_removeFirst);
    SAVE(ArrayDeque_addLast);

    ArrayDeque_init(&image_regions, 256);

    // Return the vkContext ptr result
    dlclose(libvortekrenderer);
    return result;
}

