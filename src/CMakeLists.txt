cmake_minimum_required(VERSION 3.5)

project(MControlCenter VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools DBus)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        operate.cpp
        operate.h
        helper.cpp
        helper.h
        languages.qrc
)

set(TS_FILES
    MControlCenter_en.ts
)

find_program(LUPDATE_EXECUTABLE lupdate)
find_program(LRELEASE_EXECUTABLE lrelease)

foreach(_ts_file ${TS_FILES})
    execute_process(COMMAND
        ${LUPDATE_EXECUTABLE}
        ${CMAKE_SOURCE_DIR}
        -ts ${CMAKE_SOURCE_DIR}/i18n/${_ts_file}
        -source-language en_US -no-obsolete -locations none
    )
    execute_process(COMMAND
        ${LRELEASE_EXECUTABLE}
        ${CMAKE_SOURCE_DIR}/i18n/${_ts_file}
    )
endforeach()

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(mcontrolcenter
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET mcontrolcenter APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(mcontrolcenter SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(mcontrolcenter
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(mcontrolcenter PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::DBus)

install(TARGETS mcontrolcenter
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MControlCenter)
endif()
