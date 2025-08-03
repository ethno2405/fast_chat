find_package(Boost 1.88 REQUIRED COMPONENTS system thread json)
find_package(unofficial-sodium CONFIG REQUIRED)

file(GLOB HTTP_API_SOURCES src/*.cpp)
add_executable(http_api ${HTTP_API_SOURCES})

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