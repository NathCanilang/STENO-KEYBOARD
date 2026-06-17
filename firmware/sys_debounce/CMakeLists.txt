add_library(sys_debounce
    defer_debounce.c
)
target_include_directories(sys_debounce PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(sys_debounce PUBLIC pico_stdlib)