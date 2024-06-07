cmake_minimum_required(VERSION 3.21)
project(SocketTest C)

set(CMAKE_C_STANDARD 99)
link_libraries(ws2_32 wsock32)
#link_libraries(libpthread)
#target_link_libraries(lab4 pthread)
SET(CMAKE_CXX_FLAGS -pthread)

add_executable(SocketTest main.c server.c util.c client.c server.h client.h util.h util.h main.h)

