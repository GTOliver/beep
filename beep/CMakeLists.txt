add_library(beep
        INTERFACE
        include/beep.h)

target_include_directories(beep INTERFACE include)

if(BEEP)
    message("Beep macros enabled")
    target_compile_definitions(beep INTERFACE BEEP_ENABLED)
    target_link_libraries(beep INTERFACE beepc)
else()
    message("Beep macros disabled")
endif()
