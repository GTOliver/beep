add_library(beep STATIC
        include/beep.h
        src/beep.cpp
        src/Beeper.h
        src/Beeper.cpp
        src/BeepCollector.h
        src/BeepCollector.cpp
        src/Common.h
        src/Envelope.h
        src/Envelope.cpp
        src/PaException.h
        src/PaException.cpp
        src/Gain.cpp
        src/Gain.h
        src/voices/Voice.h
        src/voices/NoiseVoice.h
        src/voices/NoiseVoice.cpp
        src/voices/SineVoice.cpp
        src/voices/SineVoice.h)

set_target_properties(beep PROPERTIES EXCLUDE_FROM_ALL TRUE)
target_include_directories(beep PUBLIC include)

target_link_libraries(beep
        PRIVATE
        portaudio_static
        readerwriterqueue)

if (BUILD_TESTS)
    add_executable(beep_test "test/test_dummy.cpp")
    target_link_libraries(beep_test PRIVATE Catch2::Catch2)
endif ()
