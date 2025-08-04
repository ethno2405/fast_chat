find_package(Boost 1.88 REQUIRED COMPONENTS system thread json)
find_package(unofficial-sodium CONFIG REQUIRED)

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
    Boost::system 
    Boost::thread
    Boost::json
    unofficial-sodium::sodium
)

target_include_directories(http_api 
    PRIVATE 
    ${Boost_INCLUDE_DIRS}
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)