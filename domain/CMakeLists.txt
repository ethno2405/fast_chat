add_library(domain
    src/**.cpp
)

target_include_directories(domain PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
