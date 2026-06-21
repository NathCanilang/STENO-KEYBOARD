# Generated Cmake Pico project file
cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================

set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(Steno-Keyboard C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable
add_executable(Steno-Keyboard 
    Steno-Keyboard.c
    usb_descriptors.c
    keyboard.c
    hardware_wrapper.c
    k_logic.c
)

pico_set_program_name(Steno-Keyboard "Steno-Keyboard")
pico_set_program_version(Steno-Keyboard "0.1")

pico_enable_stdio_uart(Steno-Keyboard 1) # Enable UART for debugging (optional)
pico_enable_stdio_usb(Steno-Keyboard 0)  # MUST BE 0!

add_subdirectory(sys_debounce)

# Add the standard library to the build (Cleaned of corrupted spaces)
target_link_libraries(Steno-Keyboard
    tinyusb_device
    tinyusb_board
    pico_stdlib
    sys_debounce
)

# Add the standard include files to the build (Cleaned of corrupted spaces)
target_include_directories(Steno-Keyboard PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_compile_options(Steno-Keyboard PRIVATE -Wno-unused-parameter)

pico_add_extra_outputs(Steno-Keyboard)