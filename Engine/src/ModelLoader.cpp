#include "ModelLoader.h"

void ModelLoader::loadModel(const std::string& modelPath) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        throw std::runtime_error("Assimp failed to load model: " + std::string(importer.GetErrorString()));
    }

    std::unordered_map<Vertex, uint32_t> uniqueVertices{};

    for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[i];
        processMesh(mesh, scene, uniqueVertices);
    }
}

void ModelLoader::processMesh(aiMesh* mesh, const aiScene* scene, std::unordered_map<Vertex, uint32_t>& uniqueVertices) {
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex{};

        vertex.pos = {
            mesh->mVertices[i].x,
            mesh->mVertices[i].y,
            mesh->mVertices[i].z
        };

        if (mesh->HasTextureCoords(0)) {
            vertex.texCoord = {
                mesh->mTextureCoords[0][i].x,
                1.0f - mesh->mTextureCoords[0][i].y
            };
        }

        vertex.color = { 1.0f, 1.0f, 1.0f };  // Set your default color here

        if (uniqueVertices.count(vertex) == 0) {
            uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
            vertices.push_back(vertex);
        }

        indices.push_back(uniqueVertices[vertex]);
    }
}