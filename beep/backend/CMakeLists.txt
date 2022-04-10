include(FetchContent)

message(STATUS "Fetching portaudio")
FetchContent_Declare(portaudio
        GIT_REPOSITORY https://github.com/PortAudio/portaudio.git
        GIT_TAG        v19.7.0
        GIT_SHALLOW    TRUE
        )
FetchContent_GetProperties(portaudio)

if (NOT portaudio_POPULATED)
    FetchContent_Populate(portaudio)
    add_subdirectory("${portaudio_SOURCE_DIR}" "${portaudio_BINARY_DIR}" EXCLUDE_FROM_ALL)
endif()

add_library(beep_backend SHARED
        include/beep_backend.h
        src/beep_backend.cpp
        src/Beeper.cpp src/Beeper.h
        src/PaException.h
        src/PaException.cpp)

set_target_properties(beep_backend PROPERTIES EXCLUDE_FROM_ALL TRUE)
target_include_directories(beep_backend PUBLIC include)

target_link_libraries(beep_backend PRIVATE portaudio_static)
