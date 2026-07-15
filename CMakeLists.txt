cmake_minimum_required(VERSION 3.10)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE
        "${CMAKE_CURRENT_LIST_DIR}/cmake/toolchains/arm-none-eabi.cmake"
        CACHE FILEPATH "ARM bare-metal toolchain")
endif()

project(TEST_10 LANGUAGES C)

set(CMAKE_EXECUTABLE_SUFFIX ".elf")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(project_features INTERFACE)
target_compile_features(project_features INTERFACE c_std_11)

add_library(project_warnings INTERFACE)
target_compile_options(project_warnings INTERFACE
        -Wall
        -Wextra
        -Wpedantic
        -Werror
        )

add_library(project_config INTERFACE)
target_compile_options(project_config INTERFACE
        -mcpu=cortex-m4
        -mthumb
        )

target_compile_definitions(project_config INTERFACE
        TARGET_DEVICE="STM32F401CC"
        STM32F401xC
        $<$<CONFIG:Debug>:DEBUG_BUILD>
        $<$<CONFIG:Release>:NDEBUG;RELEASE_BUILD>
        )

target_link_options(project_config INTERFACE
        -mcpu=cortex-m4
        -mthumb
        )

add_subdirectory(drivers)
add_subdirectory(diagnostics)
add_subdirectory(firmware)

add_executable(main
    ${CMAKE_CURRENT_SOURCE_DIR}/app/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/startup/startup.c)

target_link_libraries(main PRIVATE
        firmware
        project_features
        project_warnings
        project_config
        )


target_link_options(main PRIVATE
     --specs=nosys.specs
     -nostartfiles
     -T${CMAKE_SOURCE_DIR}/cmake/linker/memory.ld
     -Wl,-Map=$<TARGET_FILE_DIR:main>/$<TARGET_FILE_BASE_NAME:main>.map
     )

add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_OBJCOPY}
            -O binary
            $<TARGET_FILE:main>
            $<TARGET_FILE_DIR:main>/$<TARGET_FILE_BASE_NAME:main>.bin
    COMMAND ${CMAKE_OBJCOPY}
            -O ihex
            $<TARGET_FILE:main>
            $<TARGET_FILE_DIR:main>/$<TARGET_FILE_BASE_NAME:main>.hex
    COMMENT "Generating BIN and Intel HEX firmware images"
    VERBATIM
    )
