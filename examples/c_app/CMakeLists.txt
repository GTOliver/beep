add_executable(beep_example_c main.c)
target_link_libraries(beep_example_c PRIVATE beep::beep_macros)
