cmake_minimum_required(VERSION 3.25)

project(MControlCenter VERSION 0.5.2 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS
    Widgets
    LinguistTools
    DBus
)

qt_standard_project_setup()

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

#TODO: use I18N_SOURCE_LANGUAGE in qt_standard_project_setup() for translation
#when buntu/mint ship qt6.8
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

qt_add_executable(mcontrolcenter
    ${PROJECT_SOURCES}
)

qt_add_translations(mcontrolcenter
    TS_FILES ${TS_FILES}
    LUPDATE_OPTIONS
        -no-obsolete
        -locations none
)

add_subdirectory(src/helper ${CMAKE_BINARY_DIR}/helper)

target_link_libraries(mcontrolcenter PRIVATE
    Qt6::Widgets
    Qt6::DBus
)

target_compile_definitions(mcontrolcenter PRIVATE
    MControlCenter_VERSION="${PROJECT_VERSION}")
