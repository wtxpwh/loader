cmake_minimum_required(VERSION 3.10)
project(loader)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread" )

add_executable(loader main.cpp miner_config.cpp miner_config.h easy_curl.cpp easy_curl.h common.h miner_stat.cpp miner_stat.h)

target_link_libraries(loader curl)
target_link_libraries(loader jsoncpp.a)
target_link_libraries(loader boost_system.a)
target_link_libraries(loader cppnetlib-client-connections.a)
target_link_libraries(loader network-uri.a)
target_link_libraries(loader boost_thread.a)