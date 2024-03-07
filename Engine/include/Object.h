#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Transform {
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    Transform(const glm::vec3& pos = glm::vec3(0.0f), const glm::vec3& rot = glm::vec3(0.0f), const glm::vec3& scl = glm::vec3(1.0f))
        : position(pos), rotation(rot), scale(scl) {}

    glm::mat4 getModelMatrix() const {
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, position);
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        modelMatrix = glm::scale(modelMatrix, scale);
        return modelMatrix;
    }
};

class Object {
public:
    Transform transform;
    std::vector<Vertex> vertices;  // Assuming you have a Vertex struct or class
    std::vector<uint32_t> indices;

    // Add other necessary data members and methods based on your application's needs

    Object(const Transform& transform, const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
        : transform(transform), vertices(vertices), indices(indices) {}

    // Add methods to easily manipulate the object's transformation
    void move(const glm::vec3& offset) { transform.position += offset; }
    void rotate(const glm::vec3& angles) { transform.rotation += angles; }
    void scale(const glm::vec3& factors) { transform.scale *= factors; }
};