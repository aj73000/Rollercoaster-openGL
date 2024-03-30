cmake_minimum_required(VERSION 3.27)
project(Rollercoaster-openGL)

set(CMAKE_CXX_STANDARD 17)

add_executable(Rollercoaster-openGL main.cpp
        Model/Model.cpp
        Model/Model.h
        Vector/Vertex.cpp
        Vector/Vertex.h
        Texture/Texture.cpp
        Texture/Texture.h
        Mesh/Mesh.cpp
        Mesh/Mesh.h
        shaders/Shader.h
        shaders/Shader.cpp
        stb/stbi.cpp
        Camera/Camera.cpp
        Camera/Camera.h
        Cube/Cube.h
        Cube/Cube.cpp
        CubeMap/cubeMap.cpp
        CubeMap/cubeMap.h
        shaders/DepthMap.cpp
        shaders/DepthMap.h
        Plane/Plane.cpp
        Plane/Plane.h
        Spline/Spline.cpp
        Spline/Spline.h
        Audio/SoundDevice.cpp
        Audio/SoundDevice.h
        CoasterCart/Cart.cpp
        CoasterCart/Cart.h
        Physics/PhysicsCollision.cpp
        Physics/PhysicsCollision.h
)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(OpenAL REQUIRED)

find_package(assimp REQUIRED)

include_directories(${GLEW_INCLUDE_DIRS})
target_link_libraries(Rollercoaster-openGL ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} glm::glm assimp glfw)