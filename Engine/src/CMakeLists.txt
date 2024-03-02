# CMakeList.txt : CMake project for src, include source and define
# project specific logic here.
#

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(assimp REQUIRED)

include_directories(C:/VulkanSDK/1.3.261.1/Include)
include_directories(${CMAKE_SOURCE_DIR}/libs/stb-master)



# Add source to this project's executable.
add_executable (src "main.cpp" "main.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET src PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
target_link_libraries(src PRIVATE Vulkan::Vulkan glfw glm::glm assimp::assimp)

target_compile_definitions(src PRIVATE
    MODEL_DIR="${CMAKE_SOURCE_DIR}/models"
    SHADER_DIR="${CMAKE_SOURCE_DIR}/shaders"
    TEXTURE_DIR="${CMAKE_SOURCE_DIR}/textures"
)