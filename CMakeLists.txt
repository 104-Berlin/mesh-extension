cmake_minimum_required(VERSION 3.15)
project(MeshLoading)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_SYSTEM_VERSION 10.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/GameEngine/src/
                    ${CMAKE_CURRENT_SOURCE_DIR}/assimp/include/)

add_subdirectory(GameEngine)

set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
add_subdirectory(assimp)

if (WIN32)
	add_compile_definitions(EWIN)
elseif(APPLE)
    add_compile_definitions(EMAC)
endif()

set(CMAKE_SHARED_MODULE_SUFFIX .epl)

add_library(Meshes MODULE entry.cpp)



target_link_libraries(Meshes Engine)
target_link_libraries(Meshes assimp)