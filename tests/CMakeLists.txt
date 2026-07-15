cmake_minimum_required(VERSION 3.22)

project(fan_controller_tests LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

enable_testing()

add_executable(test_fan_controller
    test_fan_controller.c
    hardware_stubs.c
    ../firmware/fan_controller.c
)

target_include_directories(test_fan_controller PRIVATE
    ../firmware
    ../drivers
    ../diagnostics
)

if(MSVC)
    target_compile_options(test_fan_controller PRIVATE /W4)
else()
    target_compile_options(test_fan_controller PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

add_test(
    NAME fan_controller_unit_tests
    COMMAND test_fan_controller
)