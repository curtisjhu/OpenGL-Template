cmake_minimum_required(VERSION 3.21)
project(OpenGL-Template)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

include(cmake/CPM.cmake)
include(cmake/IMGUI.cmake)
# include(cmake/GLEW.cmake)
include(cmake/GLFW.cmake)
include(cmake/GLM.cmake)


include(CMakePrintHelpers)

########################################
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.c")
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE 
		${CMAKE_HOME_DIRECTORY}/include
)

########################################

add_definitions(-DGLFW_INCLUDE_NONE)

# GLFW
find_package(GLFW REQUIRED)
cmake_print_variables(GLFW_FOUND)
# target_include_directories(glfw PRIVATE ${GLFW_INCLUDE_DIRS}/GLFW)
target_link_libraries(${PROJECT_NAME} glfw)

# IMGUI (Manual linking)
# find_package(IMGUI REQUIRED)
# cmake_print_variables(IMGUI_FOUND)
# target_link_libraries(${PROJECT_NAME} IMGUI)

add_library(imgui ${IMGUI_SOURCE_DIR}/imgui.cpp
                  ${IMGUI_SOURCE_DIR}/imgui_demo.cpp
                  ${IMGUI_SOURCE_DIR}/imgui_draw.cpp
                  ${IMGUI_SOURCE_DIR}/imgui_tables.cpp
                  ${IMGUI_SOURCE_DIR}/imgui_widgets.cpp
                  
				  ########################################
				  # SPECFIC TO COMPILATION (REFER TO DOCS)
				  ########################################
                  ${IMGUI_SOURCE_DIR}/backends/imgui_impl_metal.mm
                  ${IMGUI_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
                  ${IMGUI_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
			)

target_include_directories(imgui PRIVATE ${IMGUI_SOURCE_DIR} ${IMGUI_SOURCE_DIR}/backends)
target_link_libraries(imgui glfw)

target_link_libraries(${PROJECT_NAME} imgui)
target_include_directories(${PROJECT_NAME} PRIVATE ${IMGUI_SOURCE_DIR} ${IMGUI_SOURCE_DIR}/backends)

# GLEW
# find_package(GLEW REQUIRED)
# target_link_libraries(${PROJECT_NAME} GLEW)

# OpenGL
find_package(OpenGL REQUIRED)
cmake_print_variables(OPENGL_FOUND)
target_link_libraries(${PROJECT_NAME} OpenGL::GL ${OPEN_GL_LIBRARIES})

# GLM
target_link_libraries(${PROJECT_NAME} glm::glm)

# shaders
# add_custom_command(TARGET ${PROJECT_NAME}
#     POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/shaders/*.vs ${PROJECT_BINARY_DIR}
#     COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/shaders/*.fs ${PROJECT_BINARY_DIR}
# )
