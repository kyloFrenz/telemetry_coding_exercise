cmake_minimum_required(VERSION 3.10)
project(telemetry_practice)

set(CMAKE_CXX_STANDARD 11)

set(SOURCES main.cpp DataReader.cpp RecordWindow.cpp DataRecord.cpp Logger.cpp)

add_executable(telemetry_practice ${SOURCES})