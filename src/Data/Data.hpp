#pragma once
#include <array>
#include <chrono>

#include "../../lib/Matrix/src/Maft.hpp"
#include "../../lib/Matrix/src/utils/hash.hpp"
#include "../../lib/Matrix/src/utils/matrix_utils.hpp"

struct UniformBufferObject {
    alignas(16) Maft::Matrix4x4f model;
    alignas(16) Maft::Matrix4x4f view;
    alignas(16) Maft::Matrix4x4f proj;


    void print()
    {
		std::cout << "model raw data : " << "\n";
        float* data = &model(0,0);
        for(int i=0;i<16;i++) std::cout << data[i] << " ";
        std::cout << "\n";
        std::cout << "model matrix layout data : \n" << model << "\n";

        std::cout << "view" << "\n";
        float* data1 = &view(0,0);
        for(int i=0;i<16;i++) std::cout << data1[i] << " ";
        std::cout << "\n";
        std::cout << "view matrix layout data : \n" << view << "\n";

        std::cout << "proj" << "\n";
        float* data2 = &proj(0,0);
        for(int i=0;i<16;i++) std::cout << data2[i] << " ";
        std::cout << "\n";
        std::cout << "proj matrix layout data : \n" << view << "\n";
    }
};

struct Vertex {
	Maft::Vector3f pos;
	Maft::Vector3f color;
	Maft::Vector2f texCoord;

	static VkVertexInputBindingDescription getBindingDescription() {
		VkVertexInputBindingDescription bindingDescription{};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(Vertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		return bindingDescription;
	}

	
    static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};

        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, color);

        attributeDescriptions[2].binding = 0;
        attributeDescriptions[2].location = 2;
        attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

        return attributeDescriptions;
    }

    bool operator==(const Vertex& other) const {
        return pos == other.pos && color == other.color && texCoord == other.texCoord;
    }
};

namespace std {
    template<> struct hash<Vertex> {
        size_t operator()(Vertex const& vertex) const {
            return ((hash<Maft::Vector3f>()(vertex.pos) ^ (hash<Maft::Vector3f>()(vertex.color) << 1)) >> 1) ^ (hash<Maft::Vector2f>()(vertex.texCoord) << 1);
        }
    };
}
