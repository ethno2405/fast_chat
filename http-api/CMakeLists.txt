find_package(Boost 1.88 REQUIRED COMPONENTS system thread json)

add_executable(http_api
    src/**.cpp
)

target_link_libraries(http_api
    PRIVATE
    domain
    ${Boost_LIBRARIES}
)

target_include_directories(http_api PRIVATE ${Boost_INCLUDE_DIRS})
