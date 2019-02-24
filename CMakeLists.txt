cmake_minimum_required(VERSION 2.6)

# Name of project
project(Starfox)

# Specify project files: header files and source files
set(HDRS
    Camera.h Config.h Enemy.h Entity.h EntityRenderer.h Framebuffer.h FSM.h Game.h Gatling.h GatlingEnemy.h GUI.h GUIRenderer.h GUIShader.h Laser.h LaserEnemy.h Light.h MasterRenderer.h Mesh.h Model.h Player.h Rocket.h RocketEnemy.h Shader.h Skybox.h SkyboxRenderer.h SkyboxShader.h StaticShader.h stb_image.h Terrain.h TerrainShader.h TerrainRenderer.h Texture.h Tools.h Vertex.h Water.h WaterRenderer.h WaterShader.h Weapon.h WindowManager.h
)
 
set(SRCS
    Camera.cpp Enemy.cpp Entity.cpp EntityRenderer.cpp Framebuffer.cpp FSM.cpp Game.cpp Gatling.cpp GatlingEnemy.cpp GUI.cpp GUIRenderer.cpp GUIShader.cpp Laser.cpp LaserEnemy.cpp Light.cpp MasterRenderer.cpp Mesh.cpp Model.cpp Player.cpp Rocket.cpp RocketEnemy.cpp Shader.cpp Skybox.cpp SkyboxRenderer.cpp SkyboxShader.cpp StaticShader.cpp Terrain.cpp TerrainShader.cpp TerrainRenderer.cpp Tools.cpp Water.cpp WaterRenderer.cpp WaterShader.cpp Weapon.cpp WindowManager.cpp
)

# Add executable based on the source files
add_executable(Starfox ${HDRS} ${SRCS})

# Require OpenGL library
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(Starfox ${OPENGL_gl_LIBRARY})

# Other libraries needed
set(LIBRARY_PATH "" CACHE PATH "Folder with GLEW, GLFW, GLM, ASSIMP, and SOIL libraries")
include_directories(${LIBRARY_PATH}/include)
if(NOT WIN32)
    find_library(GLEW_LIBRARY GLEW)
    find_library(GLFW_LIBRARY glfw)
    find_library(SOIL_LIBRARY SOIL)
    find_library(ASSIMP_LIBRARY assimp)
elseif(WIN32)
    find_library(GLEW_LIBRARY glew32s HINTS ${LIBRARY_PATH}/lib)
    find_library(GLFW_LIBRARY glfw3 HINTS ${LIBRARY_PATH}/lib)
    find_library(SOIL_LIBRARY SOIL HINTS ${LIBRARY_PATH}/lib)
    find_library(ASSIMP_LIBRARY assimp HINTS ${LIBRARY_PATH}/lib)
endif(NOT WIN32)
target_link_libraries(Starfox ${GLEW_LIBRARY})
target_link_libraries(Starfox ${GLFW_LIBRARY})
target_link_libraries(Starfox ${SOIL_LIBRARY})
target_link_libraries(Starfox ${ASSIMP_LIBRARY})

# The rules here are specific to Windows Systems
if(WIN32)
    # Avoid ZERO_CHECK target in Visual Studio
    set(CMAKE_SUPPRESS_REGENERATION TRUE)
 
    # This will use the proper libraries in debug mode in Visual Studio
    set_target_properties(Starfox PROPERTIES DEBUG_POSTFIX _d)
endif(WIN32)
