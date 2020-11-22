cmake_minimum_required(VERSION 3.2)

project(hello_library VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

############################################################
# Create a library
############################################################

#Generate the static library from the library sources
add_library(hello_library STATIC 
    lib/pool.cpp
    lib/task.cpp
)

target_include_directories(hello_library
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
)


############################################################
# Create an executable
############################################################


set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/../)

SET(CMAKE_CXX_STANDARD 17)

find_package (Threads)

# Add an executable with the above sources
#hello_binary = app
add_executable(app 
    src/main.cpp
)

#target_link_libraries (hello_binary Threads::Threads)
# link the new hello_library target with the hello_binary target
target_link_libraries(app
    PRIVATE 
        hello_library Threads::Threads
)

