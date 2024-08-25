cmake_minimum_required(VERSION 3.28.3)

project(MControlCenterHelper LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core DBus)

file(GLOB PROJECT_SOURCES
    *.cpp
    *.h
)

add_executable(mcontrolcenter-helper
    ${PROJECT_SOURCES}
)

target_link_libraries(mcontrolcenter-helper Qt6::Core Qt6::DBus)
install(TARGETS mcontrolcenter-helper LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})