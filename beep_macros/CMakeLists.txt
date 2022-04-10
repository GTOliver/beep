add_library(beep_macros
        INTERFACE
        include/beep_macros.h)

target_include_directories(beep_macros INTERFACE include)

if(BEEP)
    message("Beep macros enabled")
    target_compile_definitions(beep_macros INTERFACE BEEP_ENABLED)
    target_link_libraries(beep_macros INTERFACE beep)
else()
    message("Beep macros disabled")
endif()
