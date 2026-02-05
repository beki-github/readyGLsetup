cmake_minimum_required(VERSION 3.16)
project(test VERSION 1.0.0)
cmake_policy(SET CMP0072 NEW)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/executable)
# creates an empty shader directory inside the executable directory 
#file(MAKE_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders")
project(test VERSION 1.0)
# copy the shader folder to the executable folder for portablility IF it doesn't exist there already


if(WIN32)
#if the machine was on windows
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
  find_package(OpenGL REQUIRED)
  find_package(GLFW3 REQUIRED)
else()
# if the machine was running linux 
  find_package(OpenGL REQUIRED)
  find_package(GLFW3 REQUIRED)
endif()

add_executable( 
    ${PROJECT_NAME}
    src/shaderClass.h
    src/shaderClass.cpp
    src/main.cpp
    src/glad.c
    src/VBO.h
    src/VBO.cpp
    src/EBO.h
    src/EBO.cpp
    src/VAO.h
    src/VAO.cpp
    src/stb.cpp
    src/Texture.h
    src/Texture.cpp
    src/Debugger.h
 
)


target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/dependencies)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/shaders" 
    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/shaders"
    COMMENT "Syncing shaders to executable directory..."
)

if (WIN32)
  target_link_libraries(${PROJECT_NAME} ${GLFW3_LIBRARY} OpenGL::GL)
else()
  # Linux needs extra libraries for X11/Threads
  target_link_libraries(${PROJECT_NAME} glfw OpenGL::GL X11 pthread dl)
endif()
 
if(WIN32)
   add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/dependencies/GLFW/lib-vc2022/glfw3.dll"
        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/glfw3.dll"
        COMMENT "Copying GLFW DLL to executable directory..."
    )
endif()



