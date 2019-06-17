
cmake_minimum_required(VERSION 3.1)

# glfw
add_subdirectory(glfw-3.4 EXCLUDE_FROM_ALL)

# glew
add_definitions(-DGLEW_STATIC)
add_subdirectory(glew-2.2.0 EXCLUDE_FROM_ALL)

# glm
add_subdirectory(glm-0.9.9 EXCLUDE_FROM_ALL)
