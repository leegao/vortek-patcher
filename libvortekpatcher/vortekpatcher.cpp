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

#define BGR 1;
#include "bcdec.h"

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

int is_enabled(const char* property) {
    char value[92] = { 0 };
    return __system_property_get(property, value) > 0;
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

static void (*original_TextureDecoder_decodeAll)(void* self);
static void (*original_vt_handle_vkCmdCopyBufferToImage)(void* ctx);
static void (*original_vt_handle_vkCmdCopyBufferToImage2)(void* ctx);
static void (*original_vt_handle_vkEndCommandBuffer)(void* ctx);
static void* (*original_getHandleRequestFunc)(unsigned short);

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

void* my_getHandleRequestFunc(unsigned short op) {
    if (op == 0x147 || op == 0xbf || op == 0xd8)
        LOGI("Handling command: %d (%s)", op, get_vulkan_call_name(op));
    return original_getHandleRequestFunc(op);
}

extern "C"
void my_vt_handle_vkCmdCopyBufferToImage(uint64_t command_context) {
    char* command_data = *(char**)(command_context + 0x50);

    // Parse command buffer handle
    uint64_t command_buffer_id;
    size_t offset;
    if (*command_data == 0) {
        // Direct parameter
        command_buffer_id = command_context;
        offset = 1;
    } else {
        // Indirect parameter
        command_buffer_id = *(uint64_t*)(command_data + 1);
        offset = 9;
    }

    // Parse source buffer handle
    uint64_t src_buffer_id = 0;
    if (command_data[offset] != 0) {
        src_buffer_id = *(uint64_t*)(command_data + offset + 1);
        offset += 9;
    } else {
        offset += 1;
    }

    // Parse destination image handle
    uint64_t dst_image_id = 0;
    if (command_data[offset] != 0) {
        dst_image_id = *(uint64_t*)(command_data + offset + 1);
        offset += 9;
    } else {
        offset += 1;
    }

    // Parse image layout and region count
    uint32_t image_layout = *(uint32_t*)(command_data + offset);
    offset += 4;
    uint32_t region_count = *(uint32_t*)(command_data + offset + 4);
    offset += 4;
    size_t regions_offset = offset;

    // Convert handles to VkObjects
    uint64_t vk_command_buffer = (uint64_t) VkObject_fromId((void*) command_buffer_id);
    uint64_t vk_src_buffer = (uint64_t) VkObject_fromId((void*) src_buffer_id);
    uint64_t vk_dst_image = (uint64_t) VkObject_fromId((void*) dst_image_id);

    // Check if we should use texture decoder or original Vulkan function
    uint64_t texture_decoder = *(uint64_t*)(command_context + 0x90);

    // Allocate stack space for regions array
    size_t regions_size = (region_count * sizeof(VkBufferImageCopy) + 15) & ~15;;
    VkBufferImageCopy* regions = (VkBufferImageCopy*)alloca(regions_size);

    // Copy regions data from command buffer to stack
    if (region_count > 0) {
        // There's a second regionCount because pRegions is an array, skip it
        size_t current_offset = regions_offset + 4; // Skip initial size field

        for (uint32_t i = 0; i < region_count; i++) {
            // Read region size and advance pointer
            uint32_t region_size = *(uint32_t*)(command_data + current_offset);
            char* region_data = command_data + current_offset + 4;
            current_offset += region_size;

            // Copy VkBufferImageCopy structure (56 bytes = 0x38)
            regions[i].bufferOffset = *(uint64_t*)(region_data + 0x00);
            regions[i].bufferRowLength = *(uint32_t*)(region_data + 0x08);
            regions[i].bufferImageHeight = *(uint32_t*)(region_data + 0x0C);
            regions[i].imageSubresource.aspectMask = *(uint32_t*)(region_data + 0x10);
            regions[i].imageSubresource.mipLevel = *(uint32_t*)(region_data + 0x14);
            regions[i].imageSubresource.baseArrayLayer = *(uint32_t*)(region_data + 0x18);
            regions[i].imageSubresource.layerCount = *(uint32_t*)(region_data + 0x1C);
            regions[i].imageOffset.x = *(int32_t*)(region_data + 0x20);
            regions[i].imageOffset.y = *(int32_t*)(region_data + 0x24);
            regions[i].imageOffset.z = *(int32_t*)(region_data + 0x28);
            regions[i].imageExtent.width = *(uint32_t*)(region_data + 0x2C);
            regions[i].imageExtent.height = *(uint32_t*)(region_data + 0x30);
            regions[i].imageExtent.depth = *(uint32_t*)(region_data + 0x34);
        }
    }

    if (texture_decoder == 0 ||
        !TextureDecoder_containsImage((void*) texture_decoder, (VkImage) vk_dst_image)) {
        // Use original Vulkan function
        vkCmdCopyBufferToImage((VkCommandBuffer) vk_command_buffer, (VkBuffer) vk_src_buffer, (VkImage) vk_dst_image,
                               (VkImageLayout) image_layout, region_count, regions);
    } else {
        // Use custom texture decoder (only if buffer offset is 0)
        if (region_count > 0) {
            VkBufferImageCopy* region_copy = (VkBufferImageCopy*)malloc(regions_size);
            memcpy(region_copy, regions, regions_size);
            ArrayDeque_addLast(&image_regions, region_copy);
        } else {
            LOGE("    Adding region_null");
            ArrayDeque_addLast(&image_regions, nullptr);
        }
        TextureDecoder_copyBufferToImage((void*) texture_decoder, (VkCommandBuffer) vk_command_buffer, (VkBuffer) vk_src_buffer, (VkImage) vk_dst_image,
                                         (VkImageLayout) image_layout);

    }
}

extern "C"
void my_vt_handle_vkCmdCopyBufferToImage2(void* ctx) {
    LOGE("Inside vt_handle_vkCmdCopyBufferToImage2");
    original_vt_handle_vkCmdCopyBufferToImage2(ctx);
}

extern "C"
void my_vt_handle_vkEndCommandBuffer(void* ctx) {
    // Log every command on the buffer
    LOGI("Inside vt_handle_vkEndCommandBuffer");
#define GET(x) (*(void**)(x))
    char* context = (char*) ctx;
    uint8_t* commandBuffer = (uint8_t*) GET(context + 0x50);  // offset 0x50

    // Get total size of command buffer
    int totalBufferSize = (long) GET(context + 0x58);  // offset 0x58

    // Process commands if buffer has more than 8 bytes
    if (totalBufferSize > 8) {
        int currentOffset = 8;  // Skip the initial 8-byte header
        do {
            // Get pointer to current command
            auto commandPtr = (uint32_t*)(commandBuffer + currentOffset);
            // Read command ID and size
            auto commandId = commandPtr[0];
            auto commandSize = commandPtr[1];
            LOGI("  + commandId: %d (%s), commandSize: %d", commandId, get_vulkan_call_name(commandId), commandSize);
            // Move to next command (skip command header + command data)
            currentOffset += commandSize + 8;
        } while (currentOffset < totalBufferSize);
    }

    original_vt_handle_vkEndCommandBuffer(ctx);
}

#define TASK_QUEUE(self) (&((char*)self)[0x28])
#define TASK_DEVICE(self) (*(VkDevice*)&((char*)self)[0x00])

extern "C"
void my_TextureDecoder_decodeAll(void* self) {
    if (!ArrayDeque_isEmpty(TASK_QUEUE(self)))
        LOGI("In TextureDecoder_decodeAll");

    while (!ArrayDeque_isEmpty(TASK_QUEUE(self))) {
        DecodingTask* task = (DecodingTask*) ArrayDeque_removeFirst(TASK_QUEUE(self));
        VkBufferImageCopy* regions = nullptr;
        if (!ArrayDeque_isEmpty(&image_regions)) {
            regions = (VkBufferImageCopy*) ArrayDeque_removeFirst(&image_regions);
        } else {
            LOGE("Missing pRegions");
            continue;
        }
        LOGI("  + Task = %p (src=%p, dst=%p)", task, task->data_source, task->image_params);
        LOGI("    dst->format = %d", task->image_params->format - 131);
        if (regions) {
            LOGI("    offset=%lx, rowLen=%d, imgHeight=%d", regions->bufferOffset,
                 regions->bufferRowLength, regions->bufferImageHeight);
        } else {
            LOGE("Encountered nullptr for pRegions");
            continue;
        }

        void* mappedSrcBase = mmap(
                NULL,
                task->data_source->mmap_details->length,
                PROT_READ,
                MAP_SHARED,
                task->data_source->mmap_details->fd, 0);
        if (mappedSrcBase == MAP_FAILED) {
            LOGE("Failed to mmap %d", task->data_source->mmap_details->fd);
            continue;
        }

        const uint8_t* compressedData = (const uint8_t*)mappedSrcBase + task->data_source->offset + (regions ? regions->bufferOffset : 0);

        // Map the destination image's memory to get a CPU-accessible pointer
        void* mappedDst = nullptr;
        VkResult mapResult = vkMapMemory((VkDevice) TASK_DEVICE(self), task->image_params->memory, 0, task->image_params->size, 0, &mappedDst);
        if (mapResult == VK_SUCCESS && mappedDst) {
            // Determine the block size and decoding function based on the format
            // The format values are adjusted by subtracting 0x83 (VK_FORMAT_BC1_RGB_UNORM_BLOCK)
            uint32_t format_id = task->image_params->format - 0x83;
            uint32_t block_size = 16;
            if (format_id < 4) {
                block_size = 8; // BC1
            }
            if (format_id == 8 || format_id == 9) {
                block_size = 8; // BC4
            }

            int height = regions->imageExtent.height;
            int width = regions->imageExtent.width;

            // Loop over the image in 4x4 blocks
            for (int y = regions->imageOffset.y; y < height; y += 4) {
                for (int x = regions->imageOffset.x; x < width; x += 4) {

                    // Calculate pointer to the destination 4x4 block
                    void *dstPixelBlock =
                            (uint8_t *) mappedDst + (y * width * 4) + (x * 4);
                    int pitch = 4 * regions->bufferRowLength;

                    switch (format_id) {
                        case 0: // BC1_RGB_UNORM_BLOCK
                        case 1: // BC1_RGB_SRGB_BLOCK
                        case 2: // BC1_RGBA_UNORM_BLOCK
                        case 3: // BC1_RGBA_SRGB_BLOCK
                            bcdec_bc1(compressedData, dstPixelBlock, pitch);
                            break;

                        case 4: // BC2_UNORM_BLOCK
                        case 5: // BC2_SRGB_BLOCK
                            bcdec_bc2(compressedData, dstPixelBlock, pitch);
                            break;

                        case 6: // BC3_UNORM_BLOCK
                        case 7: // BC3_SRGB_BLOCK
                            bcdec_bc3(compressedData, dstPixelBlock, pitch);
                            break;

                        case 8: // BC4_UNORM_BLOCK
                        case 9: // BC4_SNORM_BLOCK
                            bcdec_bc4(compressedData, dstPixelBlock,
                                           pitch, format_id == 9);
                            break;

                        case 10: // BC5_UNORM_BLOCK
                        case 11: // BC5_SNORM_BLOCK
                            bcdec_bc5(compressedData, dstPixelBlock,
                                           pitch, format_id == 11);
                            break;

                        default:
                            // Unknown/unsupported format, do nothing.
                            break;
                    }

                    // Advance the source pointer to the next block
                    compressedData += block_size;
                }
            }
        }
        vkUnmapMemory((VkDevice) TASK_DEVICE(self), task->image_params->memory);
        munmap(mappedSrcBase, task->data_source->mmap_details->length);
        free(regions);
    }
}


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
    *original = *got_entry;

    long page_size = sysconf(_SC_PAGESIZE);
    if (page_size == -1) {
        perror("sysconf");
        return -1;
    }

    void *page_start = (void *)(((uintptr_t) got_entry) & ~(page_size - 1));
    mprotect(page_start, page_size, PROT_READ | PROT_WRITE);
    *got_entry = (void*) next;
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

    int enable_bc = !is_enabled("debug.vt.no_decoder");
    int enable_logging = is_enabled("debug.vt.logging");
    int enable_dump_api = is_enabled("debug.vt.dump_api");

    char* base_addr = (char*) findLibraryBase("libvortekrenderer.so");
    // Patch the TextureDecoder_decodeAll, which is at +0x3bb30 from the start of the image
    if (enable_bc)
        patch_got(base_addr, 0x3bb30,
                  (void**) &original_TextureDecoder_decodeAll,
                  (void*) &my_TextureDecoder_decodeAll);
    if (enable_logging)
        patch_got(base_addr, 0x3bc68,
                  (void**) &original_getHandleRequestFunc,
                  (void*) &my_getHandleRequestFunc);

    // Calculate the actual address of the cache vkCreateInstance pointer within Vortek
    void* vulkanWrapper = dlsym(libvortekrenderer, "vulkanWrapper");
    // The vkCreateInstance pointer is at offset 0x18 from wrapper base
    // e388: str    x0, [x23, #0x18] ; stores the vkCreateInstance symbol from libvulkan at +0x18
    if (enable_dump_api)
        *(void**)((char*)vulkanWrapper + 0x18) = (void*) &my_vkCreateInstance;

    // Patch the command dispatch in the GOT
    //   Index for vkCmdCopyImageToBuffer (opcode 0xd8) is 216, but minus 100 for the dispatch table
    void** handleRequestFuncs = (void**) dlsym(libvortekrenderer, "handleRequestFuncs");

#define PATCH(sym, index) { \
    *((void**)&original_##sym) = (void*) handleRequestFuncs[index - 100]; \
    handleRequestFuncs[index - 100] = (void*) &my_##sym; }

    if (enable_bc)
        PATCH(vt_handle_vkCmdCopyBufferToImage, 0xd7);
    PATCH(vt_handle_vkCmdCopyBufferToImage2, 0x146);
    if (enable_logging)
        PATCH(vt_handle_vkEndCommandBuffer, 0xbf);

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

