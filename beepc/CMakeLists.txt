add_library(beepc STATIC
        include/beepc.h
        src/beepc.cpp
        src/BeepQueue.h
        src/BeepQueue.cpp
        src/Beeper.h
        src/Beeper.cpp
        src/BeepSynth.h
        src/BeepSynth.cpp
        src/Common.h
        src/PaException.h
        src/PaException.cpp
        src/Gain.cpp
        src/Gain.h
        src/oscillators/Oscillator.h
        src/oscillators/Oscillator.cpp
        src/oscillators/NoiseOscillator.h
        src/oscillators/NoiseOscillator.cpp
        src/oscillators/SineOscillator.cpp
        src/oscillators/SineOscillator.h
        src/voices/Voice.h
        src/voices/OscillatorVoice.h
        src/voices/OscillatorVoice.cpp)

set_target_properties(beepc PROPERTIES EXCLUDE_FROM_ALL TRUE)
target_include_directories(beepc PUBLIC include)

target_link_libraries(beepc
        PRIVATE
        portaudio_static
        readerwriterqueue)

if (BUILD_TESTS)
    add_executable(beepc_test "test/test_dummy.cpp")
    target_link_libraries(beepc_test PRIVATE Catch2::Catch2)
endif ()
