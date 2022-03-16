cmake_minimum_required(VERSION 3.0.0)
project(subnet)

add_compile_options(-fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize-undefined-trap-on-error)
add_link_options(-fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize-undefined-trap-on-error)

add_subdirectory(subnet_lib)

add_executable(${PROJECT_NAME} src/main.c)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")

message(STATUS "Adding Sanitizers")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fsanitize=address,undefined -fno-sanitize-recover=all -fsanitize-undefined-trap-on-error")

target_include_directories(${PROJECT_NAME} PUBLIC ${SUBNET_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SUBNET_LIB_LIBRARIES})

add_subdirectory(tests)