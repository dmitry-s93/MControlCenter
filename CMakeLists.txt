cmake_minimum_required(VERSION 3.25)

project(MControlCenter VERSION 0.5.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
project(MControlCenter VERSION 0.5.2 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-fPIC)
find_package(Qt6 6.4 REQUIRED COMPONENTS
    Widgets
    LinguistTools
    DBus
)

find_package(Qt6 6.4 REQUIRED COMPONENTS Widgets LinguistTools DBus)

set(PROJECT_SOURCES
    src/main.cpp
    src/mainwindow.ui
    src/mainwindow.cpp src/mainwindow.h
    src/operate.cpp src/operate.h
    src/powermonitor.cpp src/powermonitor.h
    src/helper.cpp src/helper.h
    src/msi-ec_helper.cpp src/msi-ec_helper.h
    src/settings.cpp src/settings.h
    src/resources.qrc
)

set(TS_FILES
    MControlCenter_de_DE.ts
    MControlCenter_en.ts
    MControlCenter_es.ts
    MControlCenter_eu.ts
    MControlCenter_fi_FI.ts
    MControlCenter_fr.ts
    MControlCenter_hu.ts
    MControlCenter_it.ts
    MControlCenter_nb.ts
    MControlCenter_nl_NL.ts
    MControlCenter_pt_BR.ts
    MControlCenter_pt_PT.ts
    MControlCenter_ru.ts
    MControlCenter_tr.ts
    MControlCenter_vi.ts
    MControlCenter_zh_CN.ts
)

find_program(LUPDATE_EXECUTABLE lupdate lupdate6 lupdate-qt6 PATHS /lib/qt6/bin/ REQUIRED)
find_program(LRELEASE_EXECUTABLE lrelease lrelease6 lrelease-qt6 PATHS /lib/qt6/bin/ REQUIRED)


target_link_libraries(mcontrolcenter PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::DBus)


add_subdirectory(src/helper ${CMAKE_BINARY_DIR}/helper)
add_definitions(-DMControlCenter_VERSION="${PROJECT_VERSION}")
target_link_libraries(mcontrolcenter PRIVATE
    Qt6::Widgets
    Qt6::DBus
)

target_compile_definitions(mcontrolcenter PRIVATE
    MControlCenter_VERSION="${PROJECT_VERSION}")