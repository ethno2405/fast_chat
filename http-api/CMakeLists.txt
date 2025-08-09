find_package(unofficial-sodium CONFIG REQUIRED)
find_package(drogon 1.9.11 REQUIRED)

file(GLOB HTTP_API_SOURCES src/*.cpp)
add_executable(http_api ${HTTP_API_SOURCES})

# Set output directories based on configuration
set_target_properties(http_api PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/Debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/Release"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/RelWithDebInfo"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/MinSizeRel"
)

target_link_libraries(http_api
    PRIVATE
    domain
    Drogon::Drogon
    unofficial-sodium::sodium
)

target_include_directories(http_api 
    PRIVATE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)