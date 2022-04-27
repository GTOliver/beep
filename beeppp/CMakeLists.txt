add_library(beeppp
        INTERFACE
        include/beeppp.h
        )

target_link_libraries(beeppp INTERFACE beepc)
target_include_directories(beeppp INTERFACE include)
set_target_properties(beeppp PROPERTIES LINKER_LANGUAGE CXX)
