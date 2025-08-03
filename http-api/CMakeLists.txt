find_package(Boost 1.88 REQUIRED COMPONENTS system thread json)

file(GLOB HTTP_API_SOURCES src/*.cpp)
add_executable(http_api ${HTTP_API_SOURCES})

target_link_libraries(http_api
    PRIVATE
    domain
    Boost::system 
    Boost::thread
    Boost::json
)

target_include_directories(http_api PRIVATE ${Boost_INCLUDE_DIRS})
