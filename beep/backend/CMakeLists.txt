add_library(beep_backend STATIC
        include/beep_backend.h
        src/beep_backend.cpp
        src/Beeper.cpp src/Beeper.h)

set_target_properties(beep_backend PROPERTIES EXCLUDE_FROM_ALL TRUE)
target_include_directories(beep_backend PUBLIC include)

target_link_libraries(beep_backend PUBLIC portaudio)
# Include / Link dirs for local install of PortAudio shared lib
# TODO: Use more general solution
target_include_directories(beep_backend
        PUBLIC
        /opt/homebrew/include
        )
target_link_directories(beep_backend
        PUBLIC
        /opt/homebrew/lib
        )
