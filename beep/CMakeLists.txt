option(BEEP "Enable the BEEP macros. If OFF, the macros do nothing.")

add_library(beep
        INTERFACE
        include/beep.h)

target_include_directories(beep INTERFACE include)

if(BEEP)
    message("Beep is on")
    target_compile_definitions(beep INTERFACE USE_BEEP_BACKEND)
    add_subdirectory(backend)
    target_link_libraries(beep INTERFACE beep_backend)
else()
    message("Beep is off")
endif()
