cmake_minimum_required(VERSION 3.5)

project(MControlCenterHelper LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-fPIC)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS DBus)

add_executable(mcontrolcenter-helper
  helper.h
  helper.cpp
  readwrite.h
  readwrite.cpp
  msi-ec.h
  msi-ec.cpp
)
target_link_libraries(mcontrolcenter-helper Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(mcontrolcenter-helper Qt${QT_VERSION_MAJOR}::DBus)

install(TARGETS mcontrolcenter-helper
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
