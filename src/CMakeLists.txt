cmake_minimum_required(VERSION 3.5)
project(MusiDoodle VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        trackeditorwindow.h
        trackeditorwindow.cpp
        trackeditorwindow.ui
        newcomponentpicker.h
        newcomponentpicker.cpp
        newcomponentpicker.ui
        componentfactory.h
        componentfactory.cpp
        chordselector.h
        chordselector.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MusiDoodle
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        trackeditorwindow.h trackeditorwindow.cpp trackeditorwindow.ui
        newcomponentpicker.h newcomponentpicker.cpp newcomponentpicker.ui
        componentfactory.h componentfactory.cpp

        chordselector.h chordselector.cpp

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET MusiDoodle APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(MusiDoodle SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(MusiDoodle
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(MusiDoodle PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.MusiDoodle)
endif()
set_target_properties(MusiDoodle PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS MusiDoodle
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MusiDoodle)
endif()

# enable_testing()

#add_executable(
#  chord_selector_tests
#  ../tests/chord_selector_tests.cc
#  chordselector.cpp 
#)

#target_link_libraries(
#  chord_selector_tests
#  Qt${QT_VERSION_MAJOR}::Widgets
#  GTest::gtest_main
#)

#include(GoogleTest)

#gtest_discover_tests(chord_selector_tests)
