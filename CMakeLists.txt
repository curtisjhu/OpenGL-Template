cmake_minimum_required(VERSION 3.21)
project(OpenGL-Template)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

include(cmake/CPM.cmake)
include(cmake/IMGUI.cmake)
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

# shaders
add_custom_target(copy_shaders ALL 
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/shaders ${PROJECT_BINARY_DIR}/shaders
)

if (UNIX)
    if (APPLE)
        target_link_libraries(${CMAKE_PROJECT_NAME}
                "-framework Cocoa"
                "-framework IOKit"
                "-framework CoreVideo"
        )
    else()
        target_link_libraries(${CMAKE_PROJECT_NAME}
                ${CMAKE_THREAD_LIBS_INIT}
                ${X11_LIBRARIES}
                ${CMAKE_DL_LIBS}
        )
    endif()
endif()

add_definitions(-DGLFW_INCLUDE_NONE)

# GLFW
find_package(GLFW REQUIRED)
cmake_print_variables(GLFW_FOUND)
target_link_libraries(${PROJECT_NAME} glfw)


# OpenGL
find_package(OpenGL REQUIRED)
cmake_print_variables(OPENGL_FOUND)
target_link_libraries(${PROJECT_NAME} OpenGL::GL ${OPEN_GL_LIBRARIES})

# GLM
target_link_libraries(${PROJECT_NAME} glm::glm)


# IMGUI (Manual linking)
set(PUBLIC_H_FILES
  ${IMGUI_SOURCE_DIR}/imgui.h
  ${IMGUI_SOURCE_DIR}/imconfig.h
  ${IMGUI_SOURCE_DIR}/imgui_internal.h
  ${IMGUI_SOURCE_DIR}/imstb_rectpack.h
  ${IMGUI_SOURCE_DIR}/imstb_textedit.h
  ${IMGUI_SOURCE_DIR}/imstb_truetype.h

# ADD all backends. Let linker handle which implementation you end up using.
#   ${IMGUI_SOURCE_DIR}/backends/imgui_impl_dx9.h
#   ${IMGUI_SOURCE_DIR}/backends/imgui_impl_dx10.h
#   ${IMGUI_SOURCE_DIR}/backends/imgui_impl_dx11.h
#   ${IMGUI_SOURCE_DIR}/backends/imgui_impl_dx12.h
#   ${IMGUI_SOURCE_DIR}/backends/imgui_impl_metal.h
#   ${IMGUI_SOURCE_DIR}/backends/imgui_impl_opengl2.h
  ${IMGUI_SOURCE_DIR}/backends/imgui_impl_opengl3.h
#   ${IMGUI_SOURCE_DIR}/backends/imgui_impl_vulkan.h
#   ${IMGUI_SOURCE_DIR}/backends/imgui_impl_wgpu.h

# ADD all platforms. Let linker handle which implementation you end up using.
#   ${IMGUI_SOURCE_DIR}/backends/imgui_impl_allegro5.h
#   ${IMGUI_SOURCE_DIR}/backends/imgui_impl_android.h
  ${IMGUI_SOURCE_DIR}/backends/imgui_impl_glfw.h
#   ${IMGUI_SOURCE_DIR}/backends/imgui_impl_glut.h
#   ${IMGUI_SOURCE_DIR}/backends/imgui_impl_osx.h
#   ${IMGUI_SOURCE_DIR}/backends/imgui_impl_sdl2.h
#   ${IMGUI_SOURCE_DIR}/backends/imgui_impl_sdl3.h
#   ${IMGUI_SOURCE_DIR}/backends/imgui_impl_sdlrenderer2.h
#   ${IMGUI_SOURCE_DIR}/backends/imgui_impl_sdlrenderer3.h
#   ${IMGUI_SOURCE_DIR}/backends/imgui_impl_win32.h
)

set(PUBLIC_CXX_FILES
  ${IMGUI_SOURCE_DIR}/imgui.cpp
  ${IMGUI_SOURCE_DIR}/imgui_draw.cpp
  ${IMGUI_SOURCE_DIR}/imgui_widgets.cpp
  ${IMGUI_SOURCE_DIR}/imgui_demo.cpp
  ${IMGUI_SOURCE_DIR}/imgui_tables.cpp
  
# ADD all backends. Let linker handle which implementation you end up using.
#   ${IMGUI_SOURCE_DIR}/backends/imgui_impl_dx9.cpp
#   ${IMGUI_SOURCE_DIR}/backends/imgui_impl_dx10.cpp
#   ${IMGUI_SOURCE_DIR}/backends/imgui_impl_dx11.cpp
#   ${IMGUI_SOURCE_DIR}/backends/imgui_impl_dx12.cpp
#   ${IMGUI_SOURCE_DIR}/backends/imgui_impl_metal.mm
#   ${IMGUI_SOURCE_DIR}/backends/imgui_impl_opengl2.cpp
  ${IMGUI_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
#   ${IMGUI_SOURCE_DIR}/backends/imgui_impl_vulkan.cpp
#   ${IMGUI_SOURCE_DIR}/backends/imgui_impl_wgpu.cpp

# ADD all platforms. Let linker handle which implementation you end up using.
#   ${IMGUI_SOURCE_DIR}/backends/imgui_impl_allegro5.cpp
#   ${IMGUI_SOURCE_DIR}/backends/imgui_impl_android.cpp
  ${IMGUI_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
#   ${IMGUI_SOURCE_DIR}/backends/imgui_impl_glut.cpp
#   ${IMGUI_SOURCE_DIR}/backends/imgui_impl_osx.mm
#   ${IMGUI_SOURCE_DIR}/backends/imgui_impl_sdl2.cpp
#   ${IMGUI_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
#   ${IMGUI_SOURCE_DIR}/backends/imgui_impl_sdlrenderer2.cpp
#   ${IMGUI_SOURCE_DIR}/backends/imgui_impl_sdlrenderer3.cpp
#   ${IMGUI_SOURCE_DIR}/backends/imgui_impl_win32.cpp
)

add_library(imgui STATIC ${PUBLIC_CXX_FILES})

target_include_directories(imgui PRIVATE ${IMGUI_SOURCE_DIR} ${IMGUI_SOURCE_DIR}/backends)
target_link_libraries(imgui glfw)

target_link_libraries(${PROJECT_NAME} imgui)
target_include_directories(${PROJECT_NAME} PRIVATE ${IMGUI_SOURCE_DIR} ${IMGUI_SOURCE_DIR}/backends)