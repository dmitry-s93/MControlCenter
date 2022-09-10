cmake_minimum_required(VERSION 3.14)

project(MControlCenterHelper LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS DBus)

add_executable(mcontrolcenter_helper
  helper.h
  helper.cpp
  readwrite.h
  readwrite.cpp
)
target_link_libraries(mcontrolcenter_helper Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(mcontrolcenter_helper Qt${QT_VERSION_MAJOR}::DBus)

install(TARGETS mcontrolcenter_helper
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
