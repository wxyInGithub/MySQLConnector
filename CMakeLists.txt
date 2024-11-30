cmake_minimum_required(VERSION 3.10)
project(MysqlConnector)

add_executable(sql mysqlConnector.cpp main.cpp)
target_link_libraries(sql mysqlclient)
