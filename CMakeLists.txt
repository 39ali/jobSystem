cmake_minimum_required(VERSION 3.5)
set (CMAKE_CXX_STANDARD 11)

project(jobSystem)

file (GLOB_RECURSE sources "src/*.cpp"  "src/*.h")

message("${sources}")
set(SOURCE   ${sources} )

add_executable(jobSystem ${SOURCE})

target_include_directories(jobSystem PRIVATE ${PROJECT_SOURCE_DIR}/src)

