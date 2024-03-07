#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <unordered_map>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "VulkanStructs.h"  // Include the header file for your Vertex struct

class ModelLoader {
public:
    ModelLoader() = default;

    void loadModel(const std::string& modelPath);

    const std::vector<Vertex>& getVertices() const {
        return vertices;
    }

    const std::vector<uint32_t>& getIndices() const {
        return indices;
    }

private:
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    void processMesh(aiMesh* mesh, const aiScene* scene, std::unordered_map<Vertex, uint32_t>& uniqueVertices);
};