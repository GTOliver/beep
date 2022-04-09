add_library(beep_backend STATIC
        include/beep_backend.h
        src/beep_backend.cpp
        )
set_target_properties(beep_backend PROPERTIES EXCLUDE_FROM_ALL TRUE)
target_include_directories(beep_backend PUBLIC include)
