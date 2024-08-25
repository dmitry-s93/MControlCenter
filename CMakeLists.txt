cmake_minimum_required(VERSION 3.28.3)

project(MControlCenter VERSION 0.4.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt6 REQUIRED COMPONENTS Widgets Network LinguistTools DBus)
qt_standard_project_setup()

file(GLOB PROJECT_SOURCES
    src/*.cpp
    src/*.h
    src/*.ui
)

file(GLOB TS_FILES
    src/i18n/*.ts
)

qt_add_resources(PROJECT_RESOURCES
    src/resources.qrc
)

qt_add_executable(mcontrolcenter
    ${PROJECT_SOURCES}
    ${PROJECT_RESOURCES}
)

qt_add_translations(mcontrolcenter TS_FILES ${TS_FILES} RESOURCE_PREFIX "/translations")

target_link_libraries(mcontrolcenter PRIVATE Qt6::Widgets Qt6::DBus Qt6::Network)

install(TARGETS mcontrolcenter LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

add_subdirectory(src/helper ${CMAKE_BINARY_DIR}/helper)