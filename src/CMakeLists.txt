cmake_minimum_required(VERSION 3.5)

project(SmartCalc VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(MACOSX_BUNDLE_ICON_FILE calc.icns)
set(app_icon_macos "icon/calc.icns")
set_source_files_properties(${app_icon_macos} PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Charts)

set(PROJECT_SOURCES
        main.cc
        model/model.cc
        model/model.h
        controller/controller.cc
        controller/controller.h
        view/graphplot.cc
        view/graphplot.h
        view/graphplot.ui
        view/mainwindow.cc
        view/mainwindow.h
        view/mainwindow.ui)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SmartCalc
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
            ${app_icon_macos}
            )
    # Define target properties for Android with Qt 6 as:
    #    set_property(TARGET SmartCalc APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(SmartCalc SHARED
                ${PROJECT_SOURCES})
        # Define properties for Android with Qt 5 after find_package() calls as:
        #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(SmartCalc
                ${PROJECT_SOURCES})
    endif()
endif()

target_link_libraries(SmartCalc PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(SmartCalc PRIVATE Qt${QT_VERSION_MAJOR}::Charts)

set_target_properties(SmartCalc PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE)

install(TARGETS SmartCalc
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SmartCalc)
endif()
