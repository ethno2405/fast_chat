file(GLOB DOMAIN_SOURCES src/*.cpp)
add_library(domain ${DOMAIN_SOURCES})

target_include_directories(domain PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
