cmake_minimum_required(VERSION 3.10)
project(MysqlConnector)

set(MySQL_DIR "C:/Program Files/MySQL/MySQL Server 8.0")
include_directories(.)
include_directories(${MySQL_DIR}/include)
link_directories(${MySQL_DIR}/lib)

add_executable(sql mysqlConnector.cpp test.cpp)
target_link_libraries(sql libmysql.lib)