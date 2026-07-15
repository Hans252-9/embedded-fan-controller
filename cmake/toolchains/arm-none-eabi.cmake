set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Bare-metal cross compilers
set(CMAKE_C_COMPILER arm-none-eabi-gcc)

# Binutils
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(CMAKE_SIZE arm-none-eabi-size)

# Final executable is an ELF firmware image
set(CMAKE_EXECUTABLE_SUFFIX ".elf")

# CMake cannot run an ARM executable on the Windows host.
# Compiler checks therefore create only static libraries.
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
