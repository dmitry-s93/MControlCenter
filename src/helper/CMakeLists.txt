cmake_minimum_required(VERSION 3.25)

project(MControlCenterHelper LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-fPIC)

find_package(Qt6 6.4 REQUIRED COMPONENTS
  Core
  DBus
)

add_executable(mcontrolcenter-helper
  helper.h
  helper.cpp
  readwrite.h
  readwrite.cpp
  msi-ec.h
  msi-ec.cpp
)
target_link_libraries(mcontrolcenter-helper PRIVATE
  Qt6::Core
  Qt6::DBus
)
