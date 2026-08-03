cmake_minimum_required(VERSION 3.25)

project(MControlCenterHelper LANGUAGES CXX)

include(GNUInstallDirs)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-fPIC)

find_package(Qt6 6.4 REQUIRED COMPONENTS Core DBus)

add_executable(mcontrolcenter-helper
  service.h
  helper.h
  helper.cpp
  readwrite.h
  readwrite.cpp
  msi-ec.h
  msi-ec.cpp
  fan-curve.h
  fan-curve.cpp
  ../fan_curve.h
  ../fan_curve.cpp
  authorization.h
  authorization.cpp
)
target_link_libraries(mcontrolcenter-helper Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::DBus)

install(TARGETS mcontrolcenter-helper
    RUNTIME DESTINATION ${CMAKE_INSTALL_LIBEXECDIR})
install(FILES org.mcontrolcenter.fan-control.policy
    DESTINATION ${CMAKE_INSTALL_DATADIR}/polkit-1/actions)
