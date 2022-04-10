include(FetchContent)

message(STATUS "Fetching portaudio")
FetchContent_Declare(portaudio
        GIT_REPOSITORY https://github.com/PortAudio/portaudio.git
        GIT_TAG v19.7.0
        GIT_SHALLOW TRUE
        )
FetchContent_MakeAvailable(portaudio)

if (BUILD_TESTS)
    message(STATUS "Fetching Catch2")
    FetchContent_Declare(Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG v2.13.8
            GIT_SHALLOW TRUE
            )
    FetchContent_MakeAvailable(Catch2)

endif ()